#include <stdio.h>
#include <math.h>

#define MIN(X, Y) ((X) < (Y) ? (X) : (Y))
#define MAX(X, Y) ((X) > (Y) ? (X) : (Y))

#define X_MIN   0.0
#define X_MAX 900.0
#define Y_MIN   0.0
#define Y_MAX 900.0
#define WIDTH (X_MAX - X_MIN)
#define HEIGHT (Y_MAX - Y_MIN)
#define X_CENTER ((X_MIN + X_MAX) / 2.0)
#define Y_CENTER ((Y_MIN + Y_MAX) / 2.0)

#define x_min -2.01
#define x_max  2.01
#define y_min -2.01
#define y_max  2.01
#define width (x_max - x_min)
#define height (y_max - y_min)
#define x_center ((x_min + x_max) / 2.0)
#define y_center ((y_min + y_max) / 2.0)

#define COEF MIN(WIDTH / width, HEIGHT / height)

#define M 1000
#define N 1000
#define K 10000

#define C (3.141592)

static double convert_distance(double d, double *dd)
{
	*dd = COEF * d;
}

static void convert_coords(double x, double y, double *xx, double *yy)
{
	*xx = X_CENTER + COEF * (x - x_center);
	*yy = Y_CENTER - COEF * (y - y_center);
}


static void circle(double x, double y, double r, char *color, double stroke_width)
{
	double xx, yy, rr;
	convert_coords(x, y, &xx, &yy);
	convert_distance(r, &rr);
	printf("<circle cx=\"%f\" cy=\"%f\" r=\"%f\" stroke=\"%s\" stroke-width=\"%f\" fill=\"none\" />\n", xx, yy, rr, color, stroke_width);
}

static double phi(double k)
{
	return 2.0 * atan(k / C);
}

int main(int argc, char *argv[])
{
	int m, n, k;

	printf("<?xml version=\"1.0\" standalone=\"no\"?>\n");
	printf("<!DOCTYPE svg PUBLIC \"-//W3C//DTD SVG 1.1//EN\" \"http://www.w3.org/Graphics/SVG/1.1/DTD/svg11.dtd\">\n");
	printf("<svg xmlns=\"http://www.w3.org/2000/svg\" version=\"1.1\" width=\"%f\" height=\"%f\" background-color=\"black\">\n", WIDTH, HEIGHT);

	printf("<rect fill=\"#000000\" width=\"%f\" height=\"%f\" />\n", WIDTH, HEIGHT);

	for (m = 1; m <= M; m ++)
	{
		double p = phi(m);
		circle(cos(p), sin(p), 1.0, "#FF0000", 2.0 / log(m + 2.0));
	}

	for (n = 1; n <= N; n ++)
	{
		double p = phi(n);
		circle(cos(p), -sin(p), 1.0, "#0000FF", 2.0 / log(n + 2.0));
	}

	for (k = 0; k <= K; k ++)
	{
		double c = cos(phi(sqrt(k)));
		circle(c, 0.0, fabs(c), "#FFFFFF", 2.0 / log(k + 2.0));
	}

	circle(-1.0, 0.0, 1.0, "#FFFFFF", 3.0);

	printf("</svg>\n");
}
