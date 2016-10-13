set terminal postscript eps color "Times-Roman" 14
set output "resultat.eps"
set key right bottom
set xlabel "n"
set ylabel "coût amorti (µs)"
# set logscale x 10
# set logscale y 10
set xrange [0:]
set yrange [0:]
plot "resultat_list.txt" using ($1):($3) with linespoints title "stack (list)", \
     "resultat_array.txt" using ($1):($3) with linespoints title "stack (array)"