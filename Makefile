OUT=fractal

make:
	clear
	gcc src/fractal.c -o ${OUT} -lm `sdl2-config --cflags --libs`
	./fractal
