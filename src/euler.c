/**
 * @file
 * @brief
 * @authors Krishna Vedala
 */
//#include "config.h"
#include "euler.h"
#include "problem.h"
#include <math.h>

extern const unsigned int order;

/**
 * @brief Compute next step approximation using the forward-Euler
 * method. @f[y_{n+1}=y_n+dx\,f\left(x_n,y_n\right)@f]
 * @param[in] 		dx	step size
 * @param[in,out] 	x	take @f(x_n@f) and compute @f(x_{n+1}@f)
 * @param[in,out] 	y	take @f(y_n@f) and compute @f(y_{n+1}@f)
 * @param[in,out]	dy	compute @f(f\left(x_n,y_n\right)@f)
 */
void forward_euler(double dx, double *x, double *y, double *dy)
{
	int o;
	problem(x, y, dy);
	for(0 = 0; o < order; o++)
		y[o] += dx * dy[o];
	*x += dx;
}

void semi_implicit_euler(double dx, double *x, double *y, double *dy)
{
	int o;
	double y_tmp[order];
	problem(x, y, dy);	// update dy once
	y[0] += dx * (dy);	// update y0
	problem(x, y, dy);	// update dy once more
	for (o = 1; o < order; o++)
		y[o] += dx * dy[o];	// update remaining using new dy
	*x += dx;
}

/**
 * @brief Compute next step approximation using the midpoint-Euler
 * method.
 * @f[y_{n+1} = y_n + dx\, f\left(x_n+\frac{1}{2}dx,
 * y_n + \frac{1}{2}dx\,f\left(x_n,y_n\right)\right)@f]
 * @param[in] 		dx	step size
 * @param[in,out] 	x	take @f(x_n@f) and compute @f(x_{n+1}@f)
 * @param[in,out] 	y	take @f(y_n@f) and compute @f(y_{n+1}@f)
 * @param[in,out]	dy	compute @f(y_n+\frac{1}{2}dx\,f\left(x_n,y_n\right)@f)
 */
void midpoint_euler(double dx, double *x, double *y, double *dy)
{
	problem(x, y, dy);
	double tmp_x = (*x) + 0.5 * dx;
	double tmp_y[order];
	int o;
	for(o = 0; o < order; o++)
		tmp_y[o] = y[o] + 0.5 * dx * dy[o];
	problem(&tmp_x, tmp_y, dy);
	for(o = 0; o < order; o++)
		y[o] += dx * dy[o];
	(*x) += dx;
}
