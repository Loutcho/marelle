#include <stdio.h>
#include <math.h>

#define WIDTH 1900.0
#define HEIGHT 900.0

#define X_MIN -475.0
#define X_MAX +475.0
#define Y_MIN   0.0
#define Y_MAX +450.0
#define X_LEN ((X_MAX) - (X_MIN))
#define Y_LEN ((Y_MAX) - (Y_MIN))
#define MARGIN 0.05

static void rect(double x, double y, double width, double height, char *color)
{
	printf("<rect x=\"%f\" y=\"%f\" width=\"%f\" height=\"%f\" style=\"fill:%s;stroke:%s;stroke-width:0\"/>\n", x, y, width, height, color, color);
}

int main(int argc, char *argv[])
{
	printf("<?xml version=\"1.0\" standalone=\"no\"?>\n");
	printf("<!DOCTYPE svg PUBLIC \"-//W3C//DTD SVG 1.1//EN\" \"http://www.w3.org/Graphics/SVG/1.1/DTD/svg11.dtd\">\n");
	printf("<svg xmlns=\"http://www.w3.org/2000/svg\" version=\"1.1\" width=\"%f\" height=\"%f\" style=\"background-color:gray\" viewBox=\"%f %f %f %f\" >\n", WIDTH, HEIGHT, X_MIN, Y_MIN, X_LEN, Y_LEN);

	double m = 1.0;
	double x, y;
	int fini, i;

	while (m <= X_MAX) {
		i = 0;
		fini = 0;
		while (! fini) {
			x = -m + i     + MARGIN;
			y = m * i + MARGIN;
			fini = (x >= X_MAX) || (x < X_MIN) || (y >= Y_MAX) || (y < Y_MIN);
			if (! fini) {
				rect(x, y, 1.0 - 2.0 * MARGIN, m - 2.0 * MARGIN, "white");
			}
			i = i + 1;
		}

		i = 0;
		fini = 0;
		while (! fini) {
			x = m - i - 1 + MARGIN;
			y = m * i + MARGIN;
			fini = (x >= X_MAX) || (x < X_MIN) || (y >= Y_MAX) || (y < Y_MIN);
			if (! fini) {
				rect(x, y, 1.0 - 2.0 * MARGIN, m - 2.0 * MARGIN, "black");
			}
			i = i + 1;
		}
		m = m + 1.0;
	}

	printf("</svg>\n");
}
