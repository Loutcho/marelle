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
		lk = log(k);
		convert(0.0, lk, &xx1, &yy1);
		convert(lk, 0.0, &xx2, &yy2);
		line(xx1, yy1, xx2, yy2, "rgb(64,64,64)");
		lk = log(k) / 2.0;
		convert(lk, lk, &xx, &yy);
		label(xx, yy, k, "rgb(128,128,128)");
	}

	for (m = 1; m <= M; m ++)
	{
		convert(log(m), 0.0, &xx1, &yy1);
		xx2 = xx1;
		yy1 = 0;
		yy2 = HEIGHT;
		line(xx1, yy1, xx2, yy2, "rgb(128,0,0)");
		label_horizontal(xx2, yy2 - 2 * MARGIN, m, "rgb(168,40,40)");
	}

	for (n = 1; n <= N; n ++)
	{
		convert(0.0, log(n), &xx1, &yy1);
		yy2 = yy1;
		xx1 = 0;
		xx2 = WIDTH;
		line(xx1, yy1, xx2, yy2, "rgb(32,32,160)");
		label_vertical(xx1 + 2 * MARGIN, yy1, n, "rgb(72,72,200)");
	}

        for (m = 2; m <= M; m ++)
        {
                for (n = 2; n <= N; n ++)
                {
			if (m != n)
			{
				x = log(m);
				y = log(n);
				convert(x, y, &xx, &yy);
				label(xx, yy, m * n, "rgb(128,128,128)");
			}
                }
        }


	printf("</svg>\n");
}
