#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "../c_lib/rngs.h"    
#include "../c_lib/rvgs.h"                   /* the multi-stream generator */

#define START         0.0              /* initial time                   */
#define STOP      20000.0              /* terminal (close the door) time */
#define INFITY   (100.0 * STOP)      /* must be much larger than STOP  */

   double Min(double a, double c)
/* ------------------------------
 * return the smaller of a, b
 * ------------------------------
 */
{ 
  if (a < c)
    return (a);
  else
    return (c);
} 


//    double Exponential(double m)
// /* ---------------------------------------------------
//  * generate an Exponential random variate, use m > 0.0 
//  * ---------------------------------------------------
//  */
// {
//   return (-m * log(1.0 - Random()));
// }


//    double Uniform(double a, double b)
// /* --------------------------------------------
//  * generate a Uniform random variate, use a < b 
//  * --------------------------------------------
//  */
// {
//   return (a + (b - a) * Random());
// }


   double GetArrival()
/* ---------------------------------------------
 * generate the next arrival time, with rate 1/2
 * ---------------------------------------------
 */ 
{
  static double arrival = START;

  SelectStream(0); 
  arrival += Exponential(2.0);
  return (arrival);
} 


   double GetService()
/* --------------------------------------------
 * generate the next service time with rate 2/3
 * --------------------------------------------
 */ 
{
  SelectStream(1);
  return (Uniform(1.0, 2.0));
}  

struct {
    double arrival;                 /* next arrival time                   */
    double completion;              /* next completion time                */
    double current;                 /* current time                        */
    double next;                    /* next (most imminent) event time     */
    double last;                    /* last arrival time                   */
  } t;
  struct {
    double node;                    /* time integrated number in the node  */
    double queue;                   /* time integrated number in the queue */
    double service;                 /* time integrated number in service   */
  } area      = {0.0, 0.0, 0.0};

  void simulate(capacity)
{
    long index  = 0;                  /* used to count departed jobs         */
    long number = 0;                  /* number in the node                  */
    long reject = 0;
    PlantSeeds(123456789);
    t.current    = START;           /* set the clock                         */
    t.arrival    = GetArrival();    /* schedule the first arrival            */
    t.completion = INFITY;        /* the first event can't be a completion */

    while ((t.arrival < STOP) || (number > 0)) {
      t.next          = Min(t.arrival, t.completion);  /* next event time   */
      if (number > 0)  {                               /* update integrals  */
        area.node    += (t.next - t.current) * number;
        area.queue   += (t.next - t.current) * (number - 1);
        area.service += (t.next - t.current);
      }
      t.current       = t.next;                    /* advance the clock */

      if (t.current == t.arrival)  {               /* process an arrival */
        number++;
        t.arrival     = GetArrival();
        if (number > capacity+1){
          reject++;
          number--;
        }
        if (t.arrival > STOP)  {
          t.last      = t.current;
          t.arrival   = INFINITY;
        }
        if (number == 1)
          t.completion = t.current + GetService();
    }

      else {                                        /* process a completion */
        index++;
        number--;
        if (number > 0)
          t.completion = t.current + GetService();
        else //number == 0
          t.completion = INFITY;
      }
    
    } 

    printf("\nfor %ld jobs with queue capacity %d\n", index, capacity);
    printf("   average rejection rate ...= %f\n", (double) reject / (reject+index));
    printf("   average interarrival time = %6.2f\n", t.last / index);
    printf("   average wait ............ = %6.2f\n", area.node / index);
    printf("   average delay ........... = %6.2f\n", area.queue / index);
    printf("   average service time .... = %6.2f\n", area.service / index);
    printf("   average # in the node ... = %6.2f\n", area.node / t.current);
    printf("   average # in the queue .. = %6.2f\n", area.queue / t.current);
    printf("   utilization ............. = %6.2f\n", area.service / t.current);
  
}
int main (int argc, char** argv){
  simulate(atoi(argv[1]));

}