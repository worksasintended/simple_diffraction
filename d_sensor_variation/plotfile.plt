set term pdfcairo enhanced
set termoptions font ",14"
set tics out
set border 3
set key title
set key box
set xtics nomirror
set ytics nomirror
set key top right
set title "variation sensor distance"
set key width 2
set key height .3
 
set out "plot.pdf"
set ylabel "relative intensity"
set xlabel "position in mm"
plot  \
    "out.00465.dat" u ($1*1000):2 w l lc 1 t "d_s=4.65mm", "out.00465.dat" u (-$1*1000):2 w l lc 1 t "", \
    "out.00645.dat" u ($1*1000):2 w l lc 2 t "d_s=6.45mm", "out.00645.dat" u (-$1*1000):2 w l lc 2 t "", \
    "out.00845.dat" u ($1*1000):2 w l lc 3 t "d_s=8.45mm", "out.00845.dat" u (-$1*1000):2 w l lc 3 t ""
