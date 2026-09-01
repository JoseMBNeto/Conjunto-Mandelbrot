mandelbrot: main.o base_mandelbrot.o serial.o openmp.o pthreads.o
	gcc main.o base_mandelbrot.o serial.o openmp.o pthreads.o -o mandelbrot -fopenmp -pthread

main.o: main.c base_mandelbrot.h serial.h openmp.h pthreads.h
	gcc -c main.c

openmp.o: openmp.c openmp.h base_mandelbrot.h
	gcc -c openmp.c -fopenmp

base_mandelbrot.o: base_mandelbrot.c base_mandelbrot.h
	gcc -c base_mandelbrot.c

serial.o: serial.c serial.h base_mandelbrot.h
	gcc -c serial.c

pthreads.o: pthreads.c pthreads.h base_mandelbrot.h
	gcc -c pthreads.c -pthread

log:
	script -a evidencias.log -c "date; whoami; pwd; bash"

clean:
	rm -f *.o mandelbrot

.PHONY: clean log