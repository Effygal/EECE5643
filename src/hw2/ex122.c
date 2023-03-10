
/* -------------------------------------------------------------------------
 * This program simulates a single-server FIFO service node using arrival
 * times and service times read from a text file.  The server is assumed
 * to be idle when the first job arrives.  All jobs are processed completely
 * so that the server is again idle at the end of the simulation.   The
 * output statistics are the average interarrival time, average service
 * time, the average delay in the queue, and the average wait in the service 
 * node. 
 *
 * Name              : ssq1.c  (Single Server Queue, version 1)
 * Authors           : Steve Park & Dave Geyer
 * Language          : ANSI C
 * Latest Revision   : 9-01-98
 * Compile with      : gcc ssq1.c 
 * ------------------------------------------------------------------------- 
 */

#include <stdio.h>  
#include <stdlib.h>                          

#define FILENAME   "../c_lib/ssq1.dat"                  /* input data file */
#define START      0.0
//CODE
#define JOBNUM    1000

/* =========================== */
   double GetArrival(FILE *fp)                 /* read an arrival time */
/* =========================== */
{ 
  double a;

  fscanf(fp, "%lf", &a);
  return (a);
}

/* =========================== */
   double GetService(FILE *fp)                 /* read a service time */
/* =========================== */
{ 
  double s;

  fscanf(fp, "%lf\n", &s);
  return (s);
}

/* ============== */
   int main(void)
/* ============== */
{
  FILE   *fp;                                  /* input data file      */
  long   index     = 0;                        /* job index            */
  double arrival   = START;                    /* arrival time         */
  double delay;                                /* delay in queue       */
  
  double service;                              /* service time         */
  double wait;                                 /* delay + service      */
  double departure = START;                    /* departure time       */
  struct {                                     /* sum of ...           */
    double delay;                              /*   delay times        */
    double wait;                               /*   wait times         */
    double service;                            /*   service times      */
    double interarrival;                       /*   interarrival times */
  } sum = {0.0, 0.0, 0.0};
//CODE
  double max_delay = 0;
  long num_delays = 0;
  long tc = 400;
  long l = 0;
  fp = fopen(FILENAME, "r");
  if (fp == NULL) {
    fprintf(stderr, "Cannot open input file %s\n", FILENAME);
    return (1);
  }

  while (!feof(fp)) {
    index++;
    arrival      = GetArrival(fp);
    if (arrival < departure) 
      {
        delay = departure - arrival;        /* delay in queue    */
        num_delays++;
        //CODE
        if (delay > max_delay) {
          max_delay = delay;
        }
        //max_delay = max(max_delay, delay);

      }
    else 
      delay      = 0.0;                        /* no delay          */
    service      = GetService(fp);
    wait         = delay + service;
    departure    = arrival + wait;             /* time of departure */
    //CODE
    if (arrival < tc && tc < departure) {
      l++;
    }

    sum.delay   += delay;
    sum.wait    += wait;
    sum.service += service;
  }
  printf("%6.2f\n", departure);
  sum.interarrival = arrival - START;
  printf("   \n Ex.1.2.2");
  printf("   \nfor %ld jobs\n", index);
  printf("   average interarrival time ..................= %6.2f\n", sum.interarrival / index);
  printf("   average service time .... ..................= %6.2f\n", sum.service / index);
  printf("   average delay ........... ..................= %6.2f\n", sum.delay / index);
  printf("   average wait .............................. = %6.2f\n", sum.wait / index);

  printf("   maximum delay ............................. = %6.2f\n", max_delay);
  printf("   num of jobs in the service node at (t=400)  = %ld\n", l);
  printf("   proportion of jobs delayed ...............  = %6.2f\n", (double) num_delays / (double) index);

  fclose(fp);
  return (0);
}
