#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#define MAX_PIXEL_X 950.0
#define MAX_PIXEL_Y 450.0

#define MIN_POINT_X (-9.5)
#define MAX_POINT_X   9.5
#define MIN_POINT_Y (-4.5)
#define MAX_POINT_Y   4.5

#define RADIUS_POINT 0.03

/*
 * Ce programme génère un SVG qui trace point par point
 * la trajectoire de points représentant les paramètres (t, u)
 * de marelles définies par :
 *     D_m  : y = (1 - a[m])/(1 + a[m])x + b[m]
 *     D'_n : x = (1 - a[n])/(1 + a[n])y + b[n]
 *     Delta_k : x + y = b[k]
 *     t = a[+1]
 *     u = a[-1]
 *
 * Utilisé pour illustrer mon site web perso, page "Recherche sur les marelles", §19.3
 */

struct pixel
{
	double x;
	double y;
};

struct point
{
	double x;
	double y;
};

/* racine carree positive */
void f(struct point *P, struct point *Q, int *problem)
{
	double x = P->x;
	double y = P->y;
	double s = x + y + 2.0;
	double t = 0.0;
	if (s < 0.0)
	{
		*problem = 1;
		return;
	}
	s = sqrt(s);
	if (s == 0.0)
	{
		*problem = 1;
		return;
	}
	t = (x - y) / s;
	Q->x = 0.5 * (s + t);
	Q->y = 0.5 * (s - t);
	*problem = 0;
}

/* racine carree negative */
void ff(struct point *P, struct point *Q, int *problem)
{
	f(P, Q, problem);
	if (! (*problem))
	{
		Q->x = -Q->x;
		Q->y = -Q->y;
	}
}

/* carre */
void g(struct point *P, struct point *Q, int *problem)
{
	double x = P->x;
	double y = P->y;
	Q->x = x * (x + y) - 1;
	Q->y = y * (x + y) - 1;
	*problem = 0;
}

/* cube */
void h(struct point *P, struct point *Q, int *problem)
{
	/*
	 * 1       . 1           -1 . 1               .  -2  .  1
	 *         .                1                 -1     2 
	 *                                                1
	 */           
	double x = P->x;
	double y = P->y;
	Q->x = x*x*x + 2*x*x*y + x*y*y - 2*x - y;
	Q->y = y*y*y + 2*y*y*x + y*x*x - 2*y - x;
	*problem = 0;
}

void point_to_pixel(struct point *T, struct pixel *L)
{
	L->x = (T->x - MIN_POINT_X) / (MAX_POINT_X - MIN_POINT_X) * MAX_PIXEL_X;
	L->y = (T->y - MAX_POINT_Y) / (MIN_POINT_Y - MAX_POINT_Y) * MAX_PIXEL_Y;
}

void line(struct point *A, struct point *B, char *color, int thickness)
{
	struct pixel AA;
	struct pixel BB;
	point_to_pixel(A, &AA);
	point_to_pixel(B, &BB);
	printf("\t<line x1='%f' y1='%f' x2='%f' y2='%f' style='stroke:%s;stroke-width:%d' />\n", AA.x, AA.y, BB.x, BB.y, color, thickness);
}

void circle(struct point *C, double R, char *color)
{
	struct pixel CC;
	double RR;
	point_to_pixel(C, &CC);
	RR = R * MAX_PIXEL_X / (MAX_POINT_X - MIN_POINT_X);
	printf("\t<circle cx='%f' cy='%f' r='%f' fill='%s' />\n", CC.x, CC.y, RR, color);
}

void text(struct point *P, int fontsize, char *color, char *msg)
{
	struct pixel PP;
	point_to_pixel(P, &PP);
	printf("\t<text font-size='%d' x='%f' y='%f' fill='%s'>%s</text>\n", fontsize, PP.x, PP.y, color, msg);
}

void header()
{
	printf("<svg xmlns='http://www.w3.org/2000/svg' version='1.1' width='%f' height='%f' xmlns:xlink='http://www.w3.org/1999/xlink'>\n", MAX_PIXEL_X, MAX_PIXEL_Y);
}

void background()
{
	printf("\t<rect fill='#000000' width='%f' height='%f' />\n", MAX_PIXEL_X, MAX_PIXEL_Y);
}

void grid()
{
	int i, j;
	int i_min, i_max;
	int j_min, j_max;
	struct point N, S, E, W, P;
	char *color;
	int thick;
	char s[10 + 1];
	i_min = (int) round(MIN_POINT_X);
	i_max = (int) round(MAX_POINT_X);
	for (i = i_min; i <= i_max; i ++)
	{
		P.x = i;
		P.y = 0;
		sprintf(s, "%d", i);
		text(&P, 24, "gray", s);
		color = (i == 0) ? "white" : "gray";
		thick = (i == 0) ? 2 : 1;
		N.x = i;
		N.y = MAX_POINT_Y;
		S.x = i;
		S.y = MIN_POINT_Y;
		line(&N, &S, color, thick);
	}
	j_min = (int) round(MIN_POINT_Y);
	j_max = (int) round(MAX_POINT_Y);
	for (j = j_min; j <= j_max; j ++)
	{
		P.x = 0;
		P.y = j;
		sprintf(s, "%d", j);
		text(&P, 24, "gray", s);
		color = (j == 0) ? "white" : "gray";
		thick = (j == 0) ? 2 : 1;
		W.x = MIN_POINT_X;
		W.y = j;
		E.x = MAX_POINT_X;
		E.y = j;
		line(&W, &E, color, thick);
	}
}

void frontiers()
{
	struct point P, Q;
	/* x + y = +2 */
	P.x = -10;
	P.y =  12;
	Q.x =  12;
	Q.y = -10;
	line(&P, &Q, "pink", 1);
	/* x + y = -2 */
	P.x = -12;
	P.y =  10;
	Q.x =  10;
	Q.y = -12;
	line(&P, &Q, "pink", 1);
}

void orbit(struct point *P, int nb_iterations, int nb_iterations_label)
{
	struct point Q;
	struct point QQ;
	int i = 0;
	char s[10 + 1];
	int problem = 0;
	int can_continue = 1;
	char *color_can = "lightgreen";
	char *color_cant = "red";
	char *color = color_can;
	Q.x = P->x;
	Q.y = P->y;
	while ((i <= nb_iterations) && (can_continue))
	{
		g(&Q, &QQ, &problem);
		if (problem)
		{
			can_continue = 0;
			color = color_cant;
		}
		if (i <= nb_iterations_label)
		{
			struct point T;
			T.x = Q.x + 0.0;
			T.y = Q.y + 0.2;
			sprintf(s, "%d", i);
			text(&T, 12, "yellow", s);
		}
		circle(&Q, RADIUS_POINT, color);
		i ++;
		Q.x = QQ.x;
		Q.y = QQ.y;
	}
}

void footer()
{
	printf("</svg>\n");
}

int main(int argc, char *argv[])
{
	struct point P;
	int n;
	P.x = atof(argv[1]);
	P.y = atof(argv[2]);
	n = atoi(argv[3]);
	header();
	background();
	grid();
	frontiers();
	orbit(&P, n, n);
	footer();
}
