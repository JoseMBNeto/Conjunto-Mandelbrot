mandelbrot: main.o base_mandelbrot.o serial.o openmp.o
	gcc main.o base_mandelbrot.o serial.o openmp.o -o mandelbrot -fopenmp

main.o: main.c base_mandelbrot.h serial.h
	gcc -c main.c

openmp.o: openmp.c openmp.h base_mandelbrot.h
	gcc -c openmp.c -fopenmp

base_mandelbrot.o: base_mandelbrot.c base_mandelbrot.h
	gcc -c base_mandelbrot.c

serial.o: serial.c serial.h base_mandelbrot.h
	gcc -c serial.c

log:
	script -a evidencias.log -c "date; whoami; pwd; bash"

clean:
	rm -f *.o mandelbrot

.PHONY: clean log