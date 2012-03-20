//////////////////////////////////////////////////////////////////
//			Computer Science 383 - Distributed Systems		//
//					Professor Homma Farian				//
//	Assignment 3 - Parallel Travelling Salesman Problem		//
//													//
//							by,						//
//			Collin Pope		&		Thomas George		//
//						3/?/2012						//
//													//
// This is a program that implements the travelling saleman		//
// problem in C using MPI commands to parallelize it. The user	//
// inputs values in to a graph which represent distances between//
// the cities which represent the corresponding row and column. //
// The program checks all possible permutations of the cites.	//
// In order to reduce needless computation we use the heuristic //
// that states that you may discard a potential path as soon as //
// its cumulative path length exceeds that of the current best	//
// answer.											//
//////////////////////////////////////////////////////////////////


#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>


#define MAX 100
#define INFINITY 999
#define MASTER 0 // taskid of the first task
#define FROM_MASTER 1 // message types
#define FROM_WORKER 2

MPI_Status status;

int tsp_dp (int c[][MAX], int tour[], int start, int n);

int main(int argc, char *argv[])
{
//////////////////////////////////////////////////////////////////
//													//
//				VARIABLE DECLARATION SECTION				//
//													//
//////////////////////////////////////////////////////////////////
	int n = atoi(argv[1]); //number of cities
	int numtasks, 	// number of tasks
	taskid, 	// a task identifier
	numworkers, // number of worker tasks
	mtype, 	//Message type
	source, 	// task id of message source
	dest, 	// task id of message destination
	cost, // Least cost
	i, j; //Loop counters
	int c[n][n]; // Cost matrix
	int tour[n]; // Tour matrix
	
	
	double t; // Timer
	struct timeval start, stop;	
	//Initialize
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &taskid);
	MPI_Comm_size(MPI_COMM_WORLD, &numtasks);
	numworkers = numtasks-1;
	
	
	

//////////////////////////////////////////////////////////////////
//													//
//						MASTER SECTION					//
//													//
//////////////////////////////////////////////////////////////////
if(taskid == MASTER){
	//Fill cost matrix
	for (i=1; i<=n; i++)
		for (j=0; j<n; j++)
			c[i][j] = c[j][i] = gen_rand();
	//Set up the first path/pathlength and set the diagonal to 0
	//signifying a move from a city to itself.
	for (i=0; i<n; i++)
	{
		tour[i] = i;
		c[i][i] = 0;
		cost = cost + c[0][i];
	}
		
		
	//Print to user all information being worked on
	printf ("Minimum cost: %d.\nTour: ", cost);
	for (i=0; i<n; i++)
		printf ("%d ", tour[i]);
	printf ("1\n");
		
	//Start timer
	gettimeofday(&start,0);
	t = MPI_Wtime();
	
	
	mtype= FROM_MASTER;
	for(dest = 1; dest <= numworkers; dest++)
	{
		
		
	}
	
	
	/* waiting for results */
	mtype = FROM_WORKER;
	for( i = 1; i <= numworkers; i++)
	{
		
	}
	
	
	
	gettimeofday(&stop, 0);
	//Print elapsed time
	printf("Time = %.6f\n", (stop.tv_sec+stop.tv_usec*1e-6) - (start.tv_sec+start.tv_usec*1e-6));
	}
	
	
//////////////////////////////////////////////////////////////////
//													//
//						MASTER SECTION					//
//													//
//////////////////////////////////////////////////////////////////
if( taskid > MASTER){
		mtype = FROM_MASTER;
		source = MASTER;	
	}
	
	MPI_Finalize();
}

//////////////////////////////////////////////////////////////////
//													//
//							HELPER METHODS SECTION		//
//													//
//////////////////////////////////////////////////////////////////

//SIMPLE RANDOM NUMBER GENERATOR
int gen_rand()
{
	int n;
	n = rand() % 100;
	return n;
}	


int tsp_dp (int c[][MAX], int tour[], int start, int n)
{
	int i, j, k; /* Loop counters. */
	int temp[MAX]; /* Temporary during calculations. */
	int mintour[MAX]; /* Minimal tour array. */
	int mincost; /* Minimal cost. */
	int ccost; /* Current cost. */
	
	/* End of recursion condition. */
	if (start == n - 2)
		return c[tour[n-2]][tour[n-1]] + c[tour[n-1]][0];
	
	/* Compute the tour starting from the current city. */
	mincost = INFINITY;
	for (i = start+1; i<n; i++)
	{ for (j=0; j<n; j++)
		temp[j] = tour[j];
		
		/* Adjust positions. */
		temp[start+1] = tour[i];
		temp[i] = tour[start+1];
		
		/* Found a better cycle? (Recurrence derivable.) */
		if (c[tour[start]][tour[i]] +
			(ccost = tsp_dp (c, temp, start+1, n)) < mincost) {
			mincost = c[tour[start]][tour[i]] + ccost;
			for (k=0; k<n; k++)
				mintour[k] = temp[k];
		}
	}
	
	/* Set the minimum-tour array. */
	for (i=0; i<n; i++)
		tour[i] = mintour[i];
	
	return mincost;
}
//////////////////////////////////////////////////////////////////
//NOTES:												//
//													//
//													//
//													//
//													//
//////////////////////////////////////////////////////////////////
