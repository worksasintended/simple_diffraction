set term pdfcairo
set out "plot.pdf"
set samples 1000
la=633e-9
l=1
d=0.0002
i(x)= x/sqrt(x**2+l**2)
g(x)=(pi*d/la)*i(x)
f(x)=abs(sin(g(x))/g(x))
set xrange[0:.03]
plot f(x), "out.dat" w lp
