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

static double convert_distance(double d)
{
	return COEF * d;
}

static void convert_coords(double x, double y, double *xx, double *yy)
{
	*xx = X_CENTER + COEF * (x - x_center);
	*yy = Y_CENTER - COEF * (y - y_center);
}

static int valid(double xx, double yy)
{
	if (xx < 0.0) return 0;
	if (xx > WIDTH) return 0;
	if (yy < 0.0) return 0;
	if (yy > HEIGHT) return 0;
	return 1;
}

static void circle(double xx, double yy, double r, char *color, double stroke_width)
{
	if (valid(xx, yy))
	{
		/* printf("<circle cx=\"%f\" cy=\"%f\" r=\"%f\" stroke=\"%s\" stroke-width=\"%f\" fill=\"none\" shape-rendering=\"geometricPrecision\" />\n", xx, yy, r, color, stroke_width); */
		printf("<circle cx=\"%f\" cy=\"%f\" r=\"%f\" stroke=\"%s\" stroke-width=\"%f\" fill=\"none\" />\n", xx, yy, r, color, stroke_width);
	}
}

static void label(double xx, double yy, int k, char *color)
{
	if (valid(xx, yy))
	{
		printf("<text x=\"%f\" y=\"%f\" transform=\"rotate(45 %f,%f)\" fill=\"%s\" text-anchor=\"middle\" dominant-baseline=\"central\" font-size=\"%d\">%d</text>\n", xx, yy, xx, yy, color, (int) (300.0 / ((double) k)), k);
	}
}

static void label_horizontal(double xx, double yy, int m, char *color)
{
	char s[20 + 1];
	sprintf(s, "%d", m);
	if (valid(xx, yy))
	{
		printf("<text x=\"%f\" y=\"%f\" transform=\"rotate(0 %f,%f)\" fill=\"%s\" text-anchor=\"middle\" dominant-baseline=\"central\" font-size=\"32\">%s</text>\n", xx, yy, xx, yy, color, s);
	}
}

static void label_vertical(double xx, double yy, int m, char *color)
{
	char s[20 + 1];
	sprintf(s, "%d", m);
	if (valid(xx, yy))
	{
		printf("<text x=\"%f\" y=\"%f\" transform=\"rotate(90 %f,%f)\" fill=\"%s\" text-anchor=\"middle\" dominant-baseline=\"central\" font-size=\"32\">%s</text>\n", xx, yy, xx, yy, color, s);
	}
}

static void line(double xx1, double yy1, double xx2, double yy2, char *color)
{
	printf("<line x1=\"%f\" y1=\"%f\" x2=\"%f\" y2=\"%f\" style=\"stroke:%s;stroke-width:1\"/>\n", xx1, yy1, xx2, yy2, color);
}

static double phi(double k)
{
	return 2.0 * atan(k / C);
}

int main(int argc, char *argv[])
{
	int m, n, k;
	double x, y;
	double r;
	double lk;
	double xx, yy;
	double xx1, yy1;
	double xx2, yy2;

	printf("<?xml version=\"1.0\" standalone=\"no\"?>\n");
	printf("<!DOCTYPE svg PUBLIC \"-//W3C//DTD SVG 1.1//EN\" \"http://www.w3.org/Graphics/SVG/1.1/DTD/svg11.dtd\">\n");
	printf("<svg xmlns=\"http://www.w3.org/2000/svg\" version=\"1.1\" width=\"%f\" height=\"%f\" background-color=\"black\">\n", WIDTH, HEIGHT);

	/*
	convert_coords(0.0, 0.0, &xx, &yy);
	r = convert_distance(2.0);
	circle(xx, yy, r, "#000000", 3.0);
	*/

	for (m = 1; m <= M; m ++)
	{
		convert_coords(cos(phi(m)), sin(phi(m)), &xx, &yy);
		r = convert_distance(1.0);
		circle(xx, yy, r, "#FF0000", 2.0 / log(m + 2.0));
	}

	for (n = 1; n <= N; n ++)
	{
		convert_coords(cos(phi(n)), -sin(phi(n)), &xx, &yy);
		r = convert_distance(1.0);
		circle(xx, yy, r, "#0000FF", 2.0 / log(n + 2.0));
	}

	for (k = 0; k <= K; k ++)
	{
		convert_coords(cos(phi(sqrt(k))), 0.0, &xx, &yy);
		r = convert_distance(fabs(cos(phi(sqrt(k)))));
		circle(xx, yy, r, "#000000", 2.0 / log(k + 2.0));
	}

	convert_coords(-1.0, 0.0, &xx, &yy);
	r = convert_distance(1.0);
	circle(xx, yy, r, "#000000", 3.0);

	printf("</svg>\n");
}
