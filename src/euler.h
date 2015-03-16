/**
 * @file
 * @defgroup euler Various Euler solutions
 * @addtogroup euler
 * @authors Krishna Vedala
 * @{
 */
#ifndef __EULER_H__
#define __EULER_H__

void forward_euler(double dx, double *x, double *y, double *dy);
void semi_implicit_euler(double dx, double *x, double *y, double *dy);
void midpoint_euler(double dx, double *x, double *y, double *dy);

#endif
/** @} */
