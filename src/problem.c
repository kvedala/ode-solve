/**
 * @file
 * @brief
 * @authors Krishna Vedala
 */
//#include "config.h"
#include "problem.h"
#include <math.h>


const double X0 = 0.F;		/**< initial value of @f(x=x_0@f) */
double Y0[2] = {1.F, 0.f};	/**< initial value @f(y_0=y\left(x_0\right)@f) */
const unsigned int order = 2;

/**
 * @brief Problem statement for a system with first-order differential
 * equations. Updates the system differential variables.
 * @param[in] 		x 		independent variable
 * @param[in,out]	y		dependent variable
 * @param[in,out]	y_dot	first-derivative of dependent variable
 */
void problem(double *x, double *y, double *dy)
{
	const double omega = 1.F;	// some const for the problem
	dy[0] = y[1];	// x dot
	dy[1] = -omega * omega * y[0];	// v dot
}

#if EXACT_KNOWN == 1
/**
 * @brief Exact solution of the problem. Used for solution comparison.
 * @param[in] 		x 		independent variable
 * @param[in,out]	y		dependent variable
 */
void exact_solution(double *x, double *y)
{
	double x3 = x[0] * x[0] * x[0];
	y[0] = -0.3F * cos(x3) - 0.1F * sin(x3) + 1.3F * exp(x3/3.F);
}

#endif
