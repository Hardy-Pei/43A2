//////////////////////////////////////////////////////////////////////////////////////
// Student Name: Zhihao Pei
// Student ID: 28294335
// Student Email: zpei0001@student.monash.edu
//////////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <mpi.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>

#define ROW 4
#define COLUMN 5
#define MAXADJ 4
#define numOfIterations 3
#define windowSize 3
#define rSize 1
#define iterationTime 0.1

int main(int argc, char* argv[])
{
	int rank, size;
	int dim[2], periods[2], reorder;
	int potentialAdjNodes[MAXADJ], adjNum=0;
	static int *adjNodes = NULL;
	int rNum;
	int interNodeTag = 0;
	int baseTag = 1;
	double startIteration, endIteration;

	MPI_Status stat;
	MPI_Comm comm;
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);

	dim[0] = ROW; dim[1] = COLUMN;
	periods[0] = 0; periods[1] = 0;
	reorder = 1;
	srand(time(NULL)+rank);
	MPI_Cart_create(MPI_COMM_WORLD, 2, dim, periods, reorder, &comm);
	// MPI_Cart_coords(comm, rank, 2, coord);
	// printf("Rank %d coordinates are %d %d %d %d %d\n", rank, adjNum, adjNodes[0], adjNodes[1],adjNodes[2], adjNodes[3]);
	// fflush(stdout);
	MPI_Cart_shift(comm, 1, 1, &potentialAdjNodes[0], &potentialAdjNodes[1]);
	MPI_Cart_shift(comm, 0, 1, &potentialAdjNodes[2], &potentialAdjNodes[3]);
	for (int i=0; i<MAXADJ; i++) {
		if (potentialAdjNodes[i] >= 0) {
			adjNum ++;
		}
	};
	adjNodes = (int*) malloc(adjNum*sizeof(int));
	int theIndex = 0;
	for (int i=0; i<MAXADJ; i++) {
		if (potentialAdjNodes[i] >= 0) {
			adjNodes[theIndex] = potentialAdjNodes[i];
			theIndex ++;
		}
	};

	MPI_Request r[adjNum*2];
	int rRand[adjNum];
	MPI_Status statuses[adjNum*2];

	int result[rSize][adjNum*windowSize];
	int window[windowSize][adjNum];
	for (int i=0; i<rSize; i++) {
		for (int j=0; j<adjNum*windowSize; j++) {
			result[i][j] = -1;
		}
	}
	for (int i=0; i<windowSize; i++) {
		for (int j=0; j<adjNum; j++) {
			window[i][j] = -1;
		}
	}


	for (int each=0; each<numOfIterations; each++) {
		// printf("%d, %d, %d, %d\n", rSize*adjNum*windowSize, result[0][0], result[1][0], result[2][0]);
		startIteration = MPI_Wtime();
		rNum = rand()%rSize;
		int nreq = 0;
		for (int i=0; i<adjNum; i++) {
			MPI_Isend(&rNum, 1, MPI_INT, adjNodes[i], interNodeTag, comm, &r[nreq++]);
			MPI_Irecv(&rRand[i], 1, MPI_INT, adjNodes[i], interNodeTag, comm, &r[nreq++]);
		}
		MPI_Waitall(nreq, r, statuses);
		if (each > 1) {
			for (int j=0; j<adjNum; j++) {
				value = window[0][j];
				for (int index=0; )
			} 
		}
		for (int i=0; i<windowSize-1; i++) {
			for (int j=0; j<adjNum; j++) {
				window[i][j] = window[i+1][j];
			}
		}
		for (int i=0; i<adjNum; i++) {
			int target = adjNodes[i];
			window[windowSize-1][i] = target;
			for(int j=0; j<adjNum*windowSize; j++){
				int current = result[rRand[i]][j];
				if (current == -1) {
					result[rRand[i]][j] = target;
					break;
				}
				if (current%100 == target) {
					result[rRand[i]][j] = current*100+target;
					break;
				}
			}
		}


		// printf("%d, %d, %d\n", result[0], result[1], result[2]);
		// printf("Rank %d, %d %d %d %d\n", rank, rRand[0], rRand[1], rRand[2], rRand[3]);
		if (rank == 0) {

			printf("%d, %d\n", rRand[0],rRand[1]);
			printf("%d, %d, %d, %d, %d, %d\n", result[0][0], result[0][1], result[0][2], result[0][3], result[0][4], result[0][5]);
			printf("%d, %d, %d, %d, %d, %d\n", window[0][0], window[0][1], window[1][0], window[1][1], window[2][0], window[2][1]);
			// printf("%d, %d, %d, %d, %d, %d, %d, %d, %d\n", result[0][0], result[0][1], result[0][2], result[1][0], result[1][1], result[1][2], result[2][0], result[2][1], result[2][2]);
		}
		// printf("%d, %d, %d, %d\n", rSize*adjNum*windowSize, result[0][0], result[1][0], result[2][0]);
		endIteration = MPI_Wtime();
		// if (rank == 0) {
		// 	printf("%f\n", startIteration);
		// 	printf("%f\n", endIteration);
		// 	printf("%f\n", iterationTime+startIteration-endIteration);
		// }
		sleep(iterationTime+startIteration-endIteration);
	}



	free(adjNodes);
	MPI_Finalize();
	return 0;
}