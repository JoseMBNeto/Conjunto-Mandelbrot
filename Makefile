mandelbrot: main.o base_mandelbrot.o
	gcc main.o base_mandelbrot.o -o mandelbrot

main.o: main.c base_mandelbrot.h
	gcc -c main.c

base_mandelbrot.o: base_mandelbrot.c base_mandelbrot.h
	gcc -c base_mandelbrot.c

log:
	script -a evidencias.log -c "date; whoami; pwd; bash"

clean:
	rm -f *.o mandelbrot

.PHONY: clean log