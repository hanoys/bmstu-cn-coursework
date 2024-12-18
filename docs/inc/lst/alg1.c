int wait_client(server_t *server) {
  server->clients[0].fd = server->listen_sock;
  server->clients[0].events = POLLIN;
  int numfds = 0, maxcl = 0;
  int first = 0;
  while (1) {
    numfds = poll(server->clients, maxcl + 1, 5000);
    if (numfds < 0) {
      LOG_ERROR("poll error");
      continue;
    }
    if (server->clients[0].revents & POLLIN) {
      int client_sock = accept(server->listen_sock, NULL, NULL);
      if (client_sock < 0) {
        continue;
      }
      long i = 0;
      for (i = 1; i < server->cl_num; ++i) {
        if (server->clients[i].fd < 0) {
          server->clients[i].fd = client_sock;
          server->clients[i].events = POLLIN;
          break;
        }
      }
      if (i == server->cl_num) {
        LOG_ERROR("too many connections");
        continue;
      }

      if (i > maxcl) {
        maxcl = i;
        LOG_INFO("Max clients: %d", maxcl);
      }
      if (--numfds <= 0) {
        continue;
      }
    }
    for (int i = 1; i <= maxcl; ++i) {
      if (server->clients[i].fd >= 0 &&
          server->clients[i].revents & (POLLIN | POLLERR)) {
        worker_sock_t worker_sock;
        worker_sock.clientfd = &server->clients[i].fd;
        worker_sock.wd = server->wd;

        tpool_add_work(server->pool, worker, &worker_sock);

        if (--numfds < 0) {
          break;
        }
      }
    }
    tpool_wait(server->pool);
  }
}
