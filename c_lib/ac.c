
/* -------------------------------------------------------------------------
 * This program simulates a single-server FIFO service node using arrival
 * times and service times read from a text file.  The server is assumed
 * to be idle when the first job arrives.  All jobs are processed completely
 * so that the server is again idle at the end of the simulation.   The
 * output statistics are the average interarrival time, average service
 * time, the average delay in the queue, and the average wait in the service 
 * node. 
 *
 * Name              : ac.c  (Single Server Queue, version 1)
 * Authors           : Steve Park & Dave Geyer (Modified by Effy)
 * Language          : ANSI C
 * Latest Revision   : N/A
 * Compile with      : gcc ac.c 
 * ------------------------------------------------------------------------- 
 */

#include <stdio.h>  
#include <stdlib.h>                          

#define FILENAME   "ac.dat"                  /* input data file */
#define START      0.0
//CODE
#define JOBNUM    500

/* =========================== */
   double GetArrival(FILE *fp)                 /* read an arrival time */
/* =========================== */
{ 
  double a;

  fscanf(fp, "%lf", &a);
  return (a);
}

/* =========================== */
   double GetDeparture(FILE *fp)                 /* read a departure time */
/* =========================== */
{ 
  double d;

  fscanf(fp, "%lf\n", &d);
  return (d);
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
  //double max_delay = 0;
  //long num_delays = 0;
  //long tc = 400;
  //long l = 0;
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
        //num_delays++;
        //CODE
        

      }
    else {
      delay      = 0.0; /* no delay          */
      }                     
    departure    =  GetDeparture(fp);             /* time of departure */
    service      = departure - arrival - delay;
    wait         = delay + service;
    sum.delay   += delay;
    sum.wait    += wait;
    sum.service += service;
  }
  sum.interarrival = arrival - START;
  double s_avg = sum.service / index;
  double x_avg = (index/departure)*s_avg;
  double rou = (departure/arrival)*x_avg;
  printf("   \nfor %ld jobs\n", index);
  printf("   average service time .... ..................= %6.2f\n", s_avg);
  printf("   server's utilization .... ..................= %6.2f\n", x_avg);
  printf("   traffic intensity .... .....................= %6.2f\n", rou);
  fclose(fp);
  return (0);
}
