#!/opt/homebrew/bin/gnuplot -persist

reset

set terminal svg size 1280, 720 font "Times New Roman,18"
set output 'plot1.svg'
set size ratio 0.56
set pointsize 0.9

set key right bottom
set xlabel "Кол-во запросов, шт."
set ylabel "Время прохождения тестирования, с"
set grid

plot "./table10.txt" using 1:2 with lines title "Nginx", \
     "./table10.txt" using 1:3 with lines title "Разработанный сервер"

set output 'plot2.svg'

plot "./table100.txt" using 1:2 with lines title "Nginx", \
     "./table100.txt" using 1:3 with lines title "Разработанный сервер"
