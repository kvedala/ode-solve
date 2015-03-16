/**
 * @file
 * @defgroup prob Problem Statement
 * @addtogroup prob
 * @authors Krishna Vedala
 * @{
 */
#ifndef __PROB_H__
#define __PROB_H__

void problem(double *x, double *y, double *dy);

#define EXACT_KNOWN		0	/**< set to 1 if exact solution is known for comparison */
#if EXACT_KNOWN == 1
void exact_solution(double *x, double *y);
#endif

#endif
/** @} */
