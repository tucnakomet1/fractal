Mandelbrot set
====



$$f_{c}(z)=z^{2}+c$$

There exist a multitude of various algorithms for plotting the Mandelbrot set via a computing device. Here, the most widely used and simplest algorithm will be demonstrated, namely, the naïve "escape time algorithm". In the escape time algorithm, a repeating calculation is performed for each *x*, *y* point in the plot area and based on the behavior of that calculation, a color is chosen for that pixel.

The *x* and *y* locations of each point are used as starting values in a repeating, or iterating calculation (described in detail below). The result of each iteration is used as the starting values for the next. The values are checked during each iteration to see whether they have reached a critical "escape" condition, or "bailout". If that condition is reached, the calculation is stopped, the pixel is drawn, and the next *x*, *y* point is examined.

The color of each point represents how quickly the values reached the escape point. Often black is used to show values that fail to escape before the iteration limit, and gradually brighter colors are used for points that escape. This gives a visual representation of how many cycles were required before reaching the escape condition.

To render such an image, the region of the complex plane we are considering is subdivided into a certain number of [pixels](https://en.wikipedia.org/wiki/Pixel). To color any such pixel, let {\displaystyle c}![c](https://wikimedia.org/api/rest_v1/media/math/render/svg/86a67b81c2de995bd608d5b2df50cd8cd7d92455) be the midpoint of that pixel. We now iterate the critical point 0 under {\displaystyle f_{c}}![f_{c}](https://wikimedia.org/api/rest_v1/media/math/render/svg/d2b64a46c31800830b9fecc59b22812390e18c05), checking at each step whether the orbit point has a radius larger than 2. When this is the case, we know that {\displaystyle c}![c](https://wikimedia.org/api/rest_v1/media/math/render/svg/86a67b81c2de995bd608d5b2df50cd8cd7d92455) does not belong to the Mandelbrot set, and we color our pixel according to the number of iterations used to find out. Otherwise, we keep iterating up to a fixed number of steps, after which we decide that our parameter is "probably" in the Mandelbrot set, or at least very close to it, and color the pixel black.

In [pseudocode](https://en.wikipedia.org/wiki/Pseudocode), this algorithm would look as follows. The algorithm does not use complex numbers and manually simulates complex-number operations using two real numbers, for those who do not have a [complex data type](https://en.wikipedia.org/wiki/Complex_data_type). The program may be simplified if the programming language includes [complex-data-type](https://en.wikipedia.org/wiki/Complex_data_type) operations.
