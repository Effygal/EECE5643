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
#include "../c_lib/rng.h"

#define N 1000000L                          /* number of replications */


   long un_Equilikely(const long* arr, long size)        
/* ------------------------------------------------
 * generate an un-Equilikely random variate from an input array, use a < b 
 * ------------------------------------------------
 */
{
  long b = size;
  long a = 1;
  long random_index =  (a + (long) ((b - a + 1) * Random())) - 1;
  //printf("%ld\n",arr[random_index]);
  return arr[random_index];
}


  int main(void)
{
  long   i;                               /* replication index      */
  long   x;                               /* sum of two dice      */
  long   count[13] = {0};                 /* histogram              */
  double p[13]     = {0.0};               /* probability estimates  */

  PutSeed(5151);
  const static long arr[14] = {1, 2, 2, 3, 3, 4, 4, 5, 5, 6, 6, 6, 6};
  for (i = 0; i < N; i++) {
    x = un_Equilikely(arr, 13) + un_Equilikely(arr, 13);
    count[x]++; //track number of occurance for each x.
    //printf("x = %ld, count_x = %ld\n",x, count[x]);
  }

  for (x = 2; x < 13; x++)                /* estimate probabilities */
    p[x] = (double) count[x] / N;
  printf("   \n Ex.2.3.4");
  printf("\nbased on %ld replications ", N);
  printf("the estimated probabilities are:\n\n");
  for (x = 2; x < 13; x++)
    printf("p[%2ld] = %5.3f\n", x, p[x]);
  printf("\n");

  return (0);
}
