/* ------------------------------------------------------------------------- 
 * A Monte Carlo simulation of Galileo's unfair three dice experiment. 
 * 
 * Name              : galileo.c 
 * Author            : Steve Park & Dave Geyer (Modified by Effy)
 * Language          : ANSI C
 * Latest Revision   : N/A
 * ------------------------------------------------------------------------- 
 */

#include <stdio.h>
#include <math.h>
#include "../c_lib/rng.h"

#define N 100000L                          /* number of replications */

double Uniform(double a, double b) {
  return (a + (b - a) * Random());
}

  int main(void)
{
  long   i;
  double theta1; 
  double theta2;                              /* replication index      */
  double   x1;
  double  x2;
  double   y1;   
  double  y2;                           /* sum of two dice      */
  long   count = 0;   
  double rou = 1.0;              /* radius             */
  double p     = 0.0;               /* probability estimates  */

  PutSeed(5050);
  for (i = 0; i < N; i++) {
    theta1  = Uniform(-M_PI, M_PI), 
    theta2 = Uniform(-M_PI, M_PI);
    x1 = rou*cos(theta1);
    x2 = rou*cos(theta2);
    y1 = rou*sin(theta1);
    y2 = rou*sin(theta2);
    double distance = sqrt(pow((x2-x1),2) + pow((y2-y1),2));
    if (distance > rou) {
      count++; 
    }
  }
               /* estimate probabilities */
  p = (double) count / N;
  printf("   \n Ex.2.3.5");
  printf("\nbased on %ld replications ", N);
  printf("the estimated probabilities are:\n\n");
  printf("p = %5.3f\n", p);
  printf("\n");
  return (0);
}
