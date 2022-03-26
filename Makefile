OUT=fractal

make:
	clear
	gcc src/fractal.c -o ${OUT} -lm
