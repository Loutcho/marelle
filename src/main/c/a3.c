#include <stdio.h>
#include <math.h>

#define WIDTH 910.0
#define HEIGHT 900.0
#define MARGIN 10.0
#define COEF 380.0
#define M 46
#define N 20
#define PTSIZE 2

static void convert(double x, double y, double *xx, double *yy)
{
	*xx = MARGIN + COEF * x;
	*yy = HEIGHT - (MARGIN + COEF * y);
}

static int valid(double xx, double yy)
{
	if (xx < 0.0) return 0;
	if (xx > WIDTH) return 0;
	if (yy < 0.0) return 0;
	if (yy > HEIGHT) return 0;
	return 1;
}

static void circle(double xx, double yy, double r, char *color)
{
	if (valid(xx, yy))
	{
		printf("<circle cx=\"%f\" cy=\"%f\" r=\"%f\" style=\"fill:black;stroke:%s;stroke-width:2\"/>\n", xx, yy, r, color, color);
	}
}

static void label(double xx, double yy, int k, char *color)
{
	if (valid(xx, yy))
	{
		printf("<text x=\"%f\" y=\"%f\" transform=\"rotate(45 %f,%f)\" fill=\"%s\" text-anchor=\"middle\" dominant-baseline=\"central\" font-size=\"%d\">%d</text>\n", xx, yy, xx, yy, color, (int) (300.0 / ((double) k)), k);
	}
}

static void label2(double xx, double yy, int m, int n, char *color)
{
	char s[20 + 1];
	sprintf(s, "%d &#215; %d", m, n);
	if (valid(xx, yy))
	{
		printf("<text x=\"%f\" y=\"%f\" transform=\"rotate(45 %f,%f)\" fill=\"%s\" text-anchor=\"middle\" dominant-baseline=\"central\" font-size=\"16\">%s</text>\n", xx, yy, xx, yy, color, s);
	}
}

static void line(double xx1, double yy1, double xx2, double yy2, char *color)
{
	printf("<line x1=\"%f\" y1=\"%f\" x2=\"%f\" y2=\"%f\" style=\"stroke:%s;stroke-width:1\"/>\n", xx1, yy1, xx2, yy2, color);
}

int main(int argc, char *argv[])
{
	int m, n, k;
	double x, y;
	double lk;
	double xx, yy;
	double xx1, yy1;
	double xx2, yy2;

	printf("<?xml version=\"1.0\" standalone=\"no\"?>\n");
	printf("<!DOCTYPE svg PUBLIC \"-//W3C//DTD SVG 1.1//EN\" \"http://www.w3.org/Graphics/SVG/1.1/DTD/svg11.dtd\">\n");
	printf("<svg xmlns=\"http://www.w3.org/2000/svg\" version=\"1.1\" width=\"%f\" height=\"%f\" background-color=\"black\">\n", WIDTH, HEIGHT);
	printf("<rect fill=\"#000000\" width=\"%f\" height=\"%f\" />\n", WIDTH, HEIGHT);

	for (k = 1; k <= M * N; k ++)
	{
		lk = log(k + 0.5);
		convert(0.0, lk, &xx1, &yy1);
		convert(lk, 0.0, &xx2, &yy2);
		line(xx1, yy1, xx2, yy2, "rgb(64,64,64)");
		lk = log(k) / 2.0;
		convert(lk, lk, &xx, &yy);
		label(xx, yy, k, "rgb(64,64,64)");
	}

	for (m = 1; m <= M; m ++)
	{
		for (n = 1; n <= N; n ++)
		{
			x = log(m);
			y = log(n);
			convert(x, y, &xx, &yy);
			circle(xx, yy, PTSIZE, "red");
			label2(xx, yy, m, n, "white");
		}
	}

	printf("</svg>\n");
}
