# Chaos in stb

C library that simulates fractals and attractors. You can generate them into terminal as ASCII art or into image (using [stb library](https://github.com/nothings/stb)).

## Cantor set

- [x] In ASCII
- [x] In stb

A Cantor set is a fractal that is formed by removing the middle thirds of a line. It is named after Georg Cantor, who introduced it in 1883.

We get it by removing the interval $(\frac{1}3,\frac{2}3)$ of the content from the line $[0,1]$ . The open middle third of each of these remaining segments is deleted, and there are left these four segments: $[0,\frac{1}9] \cup [\frac{2}9,\frac{1}3] \cup [\frac{2}3,\frac{7}9] \cup [\frac{8}9,1]$.

The length of the Cantor line converges to $0$.

$$\frac{1}3 + \frac{2}9 + \frac{4}{27} + \frac{8}{81} + ... = \sum_{n=0}^{\infty} \frac{2^n}{3^{n+1}} = \frac{1}3 
 \sum_{n=0}^{\infty} \frac{2^n}{3^n} = \frac{1}3 (\frac{1}{1 - \frac{2}3 } ) = 1$$
 

The Cantor set gas a fractal dimension equal to $\frac{ln(2)}{ln(3)} \approx 0.6309...$.


|                              ASCII                              |                             stb                              |
| --------------------------------------------------------------- | ------------------------------------------------------------ |
| ![cantor setin ASCII](src/Cantor/examples/cantor_set_ascii.png) | ![cantor set in stb](src/Cantor/examples/cantor_set_stb.png) |


## Sierpiński carpet

- [x] Available in ASCII
- [x] Available in stb

A Sierpiński carpet is a fractal formed by recursively removing squares from a surface. It is named after Wacław Sierpiński, who described it in 1916 and it's a generalization of Cantor's set into two dimensions.

The area of a Sierpiński carpet converges to $0$.

$$S = 1 - \sum_{n=0}^\infty \frac{8^n}{9^{n+1}} \Longrightarrow a_1 = \frac{1}9, q = \frac{8}9 \Longrightarrow S = 1 - s = 1-\frac{\frac{1}9}{1-\frac{8}9} = 1 - 1 = 0$$

The Sierpiński carpet has a fractal dimension equal to $\frac{log(8)}{log(3)} \approx 1.8928...$ .


|                                       ASCII                                        |                                      stb                                       |
| ---------------------------------------------------------------------------------- | ------------------------------------------------------------------------------ |
| ![sierpinski carpet in ASCII](src/Sierpinski/examples/sierpinski_carpet_ascii.png) | ![sierpinski carpet in stb](src/Sierpinski/examples/sierpinski_carpet_stb.png) |

## Sierpiński triangle

- [ ] Available in ASCII
- [ ] Available in stb

## Lorenz attractor

- [ ] Available in ASCII
- [x] Available in stb

Lorenz attractor is a strange attractor named after Edward Lorenz who described it in 1963. The system is described by the following three equations:

$$\frac{dx}{dt} = \sigma (y-x)$$
$$\frac{dy}{dt} = x (\rho -z) -y$$
$$\frac{dz}{dt} = xy-\beta x$$

|                                                   stb                                                    |
| ---------------------------------------------------------------------------------------- |
| ![lorenz attractor in stb](src/Lorenz/examples/lorenz_attractor.png) |

## Mandelbrot set

- [x] Available in ASCII
- [x] Available in stb
- [x] Available in SDL

|                                       ASCII                                        |                                    stb                                     |                                 SDL                                  |
| ---------------------------------------------------------------------------------- | -------------------------------------------------------------------------- | -------------------------------------------------------------------- |
| ![mandelbrot in ASCII](src/Mandelbrot/examples/mandelbrot_ascii_incolor_small.png) | ![mandelbrot in stb](src/Mandelbrot/examples/mandelbrot_stb_red_small.png) | ![mandelbrot in sdl](src/Mandelbrot/examples/mandelbrot_SDL_gui.gif) |


## Koch snowflake

- [ ] Available in ASCII
- [ ] Available in stb

## Barnsley fern

- [ ] Available in ASCII
- [ ] Available in stb

## Bifurcation graph

- [ ] Available in ASCII
- [ ] Available in stb

## TODO
- [ ] ASCII User interface

| Sierpinski triangle | Lonenz attractor | Koch snowflake | Barnsley fern | Bifurcation graph |
| ------------------- | ---------------- | -------------- | ------------- | ----------------- |
| ASCII               | ASCII            | ASCII          | ASCII         | ASCII             |
| stb                 | stb              | stb            | stb           | stb               |


## Done

| Cantor set | Sierpinski carpet | Mandelbrot set |
| ---------- | ----------------- | -------------- |
| ASCII      | ASCII             | ASCII          |
| stb        | stb               | stb, SDL       |
