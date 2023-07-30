OUT=fractal

make:
	clear
	gcc src/Attractors/attractor.c -o attractor -lm
	gcc src/fractal.c -o ${OUT} -lm `sdl2-config --cflags --libs`
