/**
	@file
	@brief Main file implementing various algorithms to solve an ODE

	@authors Krishna Vedala (Implementation in C)
*/
/**
	@mainpage ode-solve

	A simple project implementing various algorithms to solve a set of
	ordinary differential equations (ODEs).
*/

//#include "config.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include "problem.h"
#include "euler.h"

extern double X0, Y0[];
extern const unsigned int order;

/**
	Main Function
*/
int main(int argc, char *argv[])
{
	double dx, dy[order];
	double x = X0, *y = &(Y0[0]);
	double X_MAX = 10.F;
	short type;

	printf("<<<<< ODE Solvers >>>>>\n");
	printf("1. Forward Euler Method\n");
	printf("2. Midpoint Euler Method\n");
	printf("3. Semi-implicit Euler Method\n");

	printf("Enter selection: ");
	scanf("%hu", &type);

	if (argc == 1)
	{
		printf("\nEnter the step size: ");
		scanf ("%lg", &dx);
	} else {
		dx = atof(argv[1]);
	}

	FILE *fp = NULL;

	struct timeval t1, t2;
	double total_time;
	switch(type)
	{
	case 1:
		fp = fopen("forward_euler.txt", "w+");
		if (fp == NULL)
		{
			perror ("Error! ");
			return -1;
		}
		printf("Computing using 'Forward Euler' algorithm\n");
		gettimeofday(&t1, NULL);
		do {
			fprintf(fp, "%.4g\t%.4g\n", x, y[0]);
			forward_euler(dx, &x, y, dy);
		} while(x <= X_MAX);
		gettimeofday(&t2, NULL);
		fclose(fp);
		break;
	case 2:
		fp = fopen("midpoint_euler.txt", "w+");
		if (fp == NULL)
		{
			perror ("Error! ");
			return -1;
		}
		printf("Computing using 'Mid-point Euler' algorithm\n");
		gettimeofday(&t1, NULL);
		do {
			fprintf(fp, "%.4g\t%.4g\n", x, y[0]);
			midpoint_euler(dx, &x, y, dy);
		} while(x <= X_MAX);
		gettimeofday(&t2, NULL);
		fclose(fp);
		break;
	case 3:
		fp = fopen("semi-implicit_euler.txt", "w+");
		if (fp == NULL)
		{
			perror ("Error! ");
			return -1;
		}
		printf("Computing using 'Semi-implicit Euler' algorithm\n");
		gettimeofday(&t1, NULL);
		do {
			fprintf(fp, "%.4g\t%.4g\n", x, y[0]);
			semi_implicit_euler(dx, &x, y, dy);
		} while(x <= X_MAX);
		gettimeofday(&t2, NULL);
		fclose(fp);
		break;
	default:
		fprintf(stderr, "Invalid selection! Try again.\n");
		return 0;
	}

	total_time = (t2.tv_sec - t1.tv_sec) * 1000.F;      // sec to ms
	total_time += (t2.tv_usec - t1.tv_usec) / 1000.F;   // us to ms
	printf("\tTime taken = %.6g ms\n", total_time);

#if EXACT_KNOWN == 1
	fp = fopen("exact.txt", "w+");
	if (fp == NULL)
	{
		perror ("Error! ");
		return -1;
	}
	x = X0; y = Y0;
	printf("Finding exact solution\n");
	gettimeofday(&t1, NULL);
	do {
		fprintf(fp, "%.4g\t%.4g\n", x, y);
		exact_solution(&x, &y);
		x += dx;
	} while(x <= X_MAX);
	gettimeofday(&t2, NULL);
	total_time = (t2.tv_sec - t1.tv_sec) * 1000.F;      // sec to ms
    total_time += (t2.tv_usec - t1.tv_usec) / 1000.F;   // us to ms
	printf("\tTime = %.6g ms\n", total_time);
	fclose(fp);
#endif

	return 0;
}
