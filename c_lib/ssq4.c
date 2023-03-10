/* ------------------------------------------------------------------------- 
 * This program is a next-event simulation of a single-server FIFO service
 * node using Exponentially distributed interarrival times and Erlang 
 * distributed service times (i.e., a M/E/1 queue).  The service node is 
 * assumed to be initially idle, no arrivals are permitted after the 
 * terminal time STOP, and the node is then purged by processing any 
 * remaining jobs in the service node.
 *
 * Name            : ssq4.c  (Single Server Queue, version 4)
 * Author          : Steve Park & Dave Geyer
 * Language        : ANSI C
 * Latest Revision : 11-09-98
 * ------------------------------------------------------------------------- 
 */

#include <stdio.h>
#include <math.h>
#include "rngs.h"                      /* the multi-stream generator */
#include "rvgs.h"                      /* random variate generators  */

#define START         0.0              /* initial time                   */
#define STOP      20000.0              /* terminal (close the door) time */
#define INFINITY   (100.0 * STOP)      /* must be much larger than STOP  */


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
  return (Erlang(5, 0.3));
}  


   int main(void)
{
  struct {
    double arrival;  //a_i               /* next arrival time                   */
    double completion;    //c_i          /* next completion time                */
    double current;  //clock, next event time               /* current time                        */
    double next;                    /* next (most imminent) event time     */
    double last;  //a_n                  /* last arrival time                   */
  } t;
  struct {
    double node;  //l(t)                  /* time integrated number in the node  */
    double queue; //q(t)                  /* time integrated number in the queue */
    double service; //x(t)                /* time integrated number in service   */
  } area      = {0.0, 0.0, 0.0};
  long index  = 0;  //                /* used to count departed jobs         */
  long number = 0;  //l(t)                /* number in the node                  */

//first initialize all these times
  PlantSeeds(0);
  t.current    = START;  //0         /* set the clock                         */
  t.arrival    = GetArrival();    /* schedule the first arrival            */
  t.completion = INFINITY;        /* the first event can't be a completion */


  while ((t.arrival < STOP) || (number > 0)) { // still has jobs in the node
    t.next          = Min(t.arrival, t.completion);  /* next event time   */ //arrival event or departure event
    //update statistic area
    if (number > 0)  {                               /* update integrals  */
      area.node    += (t.next - t.current) * number;
      area.queue   += (t.next - t.current) * (number - 1);
      area.service += (t.next - t.current);
    }
    t.current       = t.next;                    /* advance the clock */

    if (t.current == t.arrival)  {               /* process an arrival */
      number++;
      t.arrival     = GetArrival();
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
      else
        t.completion = INFINITY;
    }
  } 

  printf("\nfor %ld jobs\n", index);
  printf("   average interarrival time = %6.2f\n", t.last / index);
  printf("   average wait ............ = %6.2f\n", area.node / index);
  printf("   average delay ........... = %6.2f\n", area.queue / index);
  printf("   average service time .... = %6.2f\n", area.service / index);
  printf("   average # in the node ... = %6.2f\n", area.node / t.current);
  printf("   average # in the queue .. = %6.2f\n", area.queue / t.current);
  printf("   utilization ............. = %6.2f\n", area.service / t.current);

  return (0);
}
