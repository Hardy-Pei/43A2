#include "wsn.h"

int nodes(MPI_Comm cartComm, int interNodeTag, int eventTag, int msgTag, int exitTag, int rank, MPI_Datatype eventInfo) {
	int cartRank;
	int dim[2], periods[2], reorder;
	int potentialAdjNodes[MAXADJ], adjNum=0;
	static int *adjNodes = NULL;
	int totalEventNum = 0, eventNum = 0;
	int nreq=0, tem, each, i, j, occurrence;
	double startIteration, endIteration, start, end, startComm, endComm, allComm, startKey, endKey, startEn, endEn;
	double encryptTime;
	event eventSend;
	long triggerNodes[infoNum];
	long pubKeys[2], priKeys[2], baseKeys[2];
	time_t triggerTime;
	char timeString[timeMsgLen];

	getKeys(rank, pubKeys, priKeys);
	MPI_Bcast(baseKeys, 2, MPI_LONG, rank, MPI_COMM_WORLD);
	// printf("%ld, %ld\n", baseKeys[0], baseKeys[1]);
	// if (rank == 1) {
	// 	start = MPI_Wtime();
	// }
	dim[0] = ROW; dim[1] = COLUMN;
	periods[0] = 0; periods[1] = 0;
	reorder = 1;
	MPI_Cart_create(cartComm, 2, dim, periods, reorder, &cartComm);
	MPI_Comm_rank(cartComm, &cartRank);
	// MPI_Cart_coords(comm, rank, 2, coord);
	// printf("Rank %d coordinates are %d %d %d %d %d\n", rank, adjNum, adjNodes[0], adjNodes[1],adjNodes[2], adjNodes[3]);
	// fflush(stdout);
	MPI_Cart_shift(cartComm, 1, 1, &potentialAdjNodes[0], &potentialAdjNodes[1]);
	MPI_Cart_shift(cartComm, 0, 1, &potentialAdjNodes[2], &potentialAdjNodes[3]);
	for (i=0; i<MAXADJ; i++) {
		if (potentialAdjNodes[i] >= 0) {
			adjNum ++;
		}
	};
	adjNodes = (int*) malloc(adjNum*sizeof(int));
	int theIndex = 0;
	for (i=0; i<MAXADJ; i++) {
		if (potentialAdjNodes[i] >= 0) {
			adjNodes[theIndex] = potentialAdjNodes[i];
			theIndex ++;
		}
	};

	long rRand[adjNum], eRand[adjNum], rNum, eNum;
	long adjKeys[adjNum*2];
	MPI_Request r[adjNum*2], req;
	MPI_Status statuses[adjNum*2], stat;
	startKey = MPI_Wtime();
	for (i=0; i<adjNum; i++) {
		MPI_Isend(pubKeys, 2, MPI_LONG, adjNodes[i], interNodeTag, cartComm, &r[nreq++]);
		MPI_Irecv(adjKeys+(2*i), 2, MPI_LONG, adjNodes[i], interNodeTag, cartComm, &r[nreq++]);
	}
	MPI_Waitall(nreq, r, statuses);
	endKey = MPI_Wtime();
	allComm += endKey - startKey;
	// if (cartRank == 5) {
	// 	printf("%ld,%ld,%ld,%ld,%ld,%ld,\n", adjKeys[0],adjKeys[1],adjKeys[2],adjKeys[3],adjKeys[4],adjKeys[5]);
	// }

	int result[rSize][adjNum];
	int window[windowSize][adjNum];
	memset(result, 0, sizeof(result[0][0])*rSize*adjNum);
	memset(window, -1, sizeof(window[0][0])*windowSize*adjNum);
	int numOccurrence[adjNum], triggerNum[adjNum];
	memset(triggerNum, 0, sizeof(triggerNum[0])*adjNum);
	srand(time(NULL)+cartRank);

	for (each=0; each<numOfIterations; each++) {
		startIteration = MPI_Wtime();
		encryptTime = 0;
		memset(triggerNodes, -1, sizeof(triggerNodes[0])*infoNum);	
		memset(numOccurrence, -1, sizeof(numOccurrence[0])*adjNum);
		// printf("%d, %d, %d, %d\n", rSize*adjNum*windowSize, result[0][0], result[1][0], result[2][0]);
		rNum = rand()%rSize;
		eNum = 0;
		nreq = 0;
		startComm = MPI_Wtime();
		for (i=0; i<adjNum; i++) {
			startEn = MPI_Wtime();
			encrypt_p(&rNum, adjKeys[i*2], adjKeys[i*2+1], &eNum, 1);
			endEn = MPI_Wtime();
			encryptTime += endEn - startEn;
			// if (cartRank == 5) {
			// 	printf("%ld\n", eNum);
			// }
			MPI_Isend(&eNum, 1, MPI_LONG, adjNodes[i], interNodeTag, cartComm, &r[nreq++]);
			MPI_Irecv(&eRand[i], 1, MPI_LONG, adjNodes[i], interNodeTag, cartComm, &r[nreq++]);
		}
		MPI_Waitall(nreq, r, statuses);
		// if (cartRank == 5) {
		// 	printf("%ld, %ld, %ld\n", eRand[0], eRand[1], eRand[2]);
		// }
		startEn = MPI_Wtime();
		decrypt_p(eRand, priKeys[0], priKeys[1], rRand, adjNum);
		endEn = MPI_Wtime();
		encryptTime += endEn - startEn;
		endComm = MPI_Wtime();
		allComm += endComm - startComm;
		// if (cartRank == 5) {
		// 	printf("%ld, %ld, %ld\n", rRand[0], rRand[1], rRand[2]);
		// }
		if (each >= windowSize) {
			for (i=0; i<adjNum; i++) {
				tem = window[each%windowSize][i];
				result[tem][i] -= 1;
			}
		}
		// for (int i=windowSize-2; i>=0; i--) {
		// 	memcpy(window[i+1],window[i],sizeof(int)*adjNum);
		// 	// for (int j=0; j<adjNum; j++) {
		// 	// 	window[i+1][j] = window[i][j]; 
		// 	// }
		// }


		for (i=0; i<adjNum; i++) {
			tem = rRand[i];
			window[each%windowSize][i] = tem;
			result[tem][i] += 1;
			for (j=0; j<adjNum; j++) {
				if (numOccurrence[j] == tem) {
					break;
				} else if (numOccurrence[j] == -1) {
					numOccurrence[j] = tem;
					break;
				}
			}
		}
		if (totalEventNum > 0) {
			MPI_Wait(&req, &stat);
		}
		eventNum = 0;
		for (i=0; i<adjNum; i++) {
			tem = numOccurrence[i];
			if (tem != -1) {
				// memset(triggerNodes, -1, sizeof(triggerNodes[0])*adjNum);
				occurrence = 0;
				for (j=0; j<adjNum; j++) {
					if (result[tem][j] > 0) {
						// triggerNodes[occurrence] = j;
						occurrence ++;
					}
				}
				if (occurrence >= 3) {
					triggerTime = time(NULL);
					sprintf(timeString, "%s", asctime(localtime(&triggerTime)));
					// printf("%d\n", stringLen);
					timeString[timeMsgLen-1] = 0;
					char2long(timeString, eventSend.timestamp, timeMsgLen);
					encrypt_p(eventSend.timestamp, baseKeys[0], baseKeys[1], eventSend.timestamp, timeMsgLen);
					memset(triggerNodes, -1, sizeof(triggerNodes[0])*infoNum);
					for (j=0; j<adjNum; j++) {
						if (result[tem][j] > 0) {
							triggerNodes[j] = adjNodes[j]+1;
							triggerNum[j] += 1;
						}
					}
					triggerNodes[MAXADJ] = rank;
					triggerNodes[MAXADJ+1] = tem;
					triggerNodes[MAXADJ+2] = each;
					if (eventNum == 0) {
						triggerNodes[MAXADJ+3] = encryptTime*scale;
						triggerNodes[MAXADJ+5] = adjNum+1;
					} else {
						triggerNodes[MAXADJ+3] = 0;
						triggerNodes[MAXADJ+5] = 1;
					}
					triggerNodes[MAXADJ+4] = 1;
					// printf("%ld\n", triggerNodes[MAXADJ+3]);
					// printf("%ld\n", triggerNodes[MAXADJ+4]);
					// printf("%ld\n", triggerNodes[MAXADJ+5]);
					encrypt_p(triggerNodes, baseKeys[0], baseKeys[1], eventSend.triggerInfo, infoNum);
					MPI_Isend(&eventSend, 1, eventInfo, 0, eventTag, MPI_COMM_WORLD, &req);
					// if (eventNum > 4) {
					// 	printf("aaaaaaa %d, %d\n", rank, each);
					// }
					// printf("bbbbbb%d, %d\n", each, rank);
					totalEventNum ++;
					eventNum ++;
				}
			} else {
				break;
			}
		}
		// if (eventNum == 0) {
		// 	memset(triggerNodes, -1, sizeof(triggerNodes[0])*infoNum);
		// 	memset(eventSend.timestamp, -1, sizeof(eventSend.timestamp[0])*maxlen);
		// 	// triggerTime = time(NULL);
		// 	// sprintf(timeString, "%s", asctime(localtime(&triggerTime)));
		// 	// // printf("%d\n", stringLen);
		// 	// timeString[timeMsgLen-1] = 0;
		// 	// char2long(timeString, eventSend.timestamp, timeMsgLen);
		// 	// encrypt_p(eventSend.timestamp, baseKeys[0], baseKeys[1], eventSend.timestamp, timeMsgLen);
		// 	triggerNodes[MAXADJ] = rank;
		// 	triggerNodes[MAXADJ+2] = each;
		// 	triggerNodes[MAXADJ+3] = encryptTime*scale;
		// 	triggerNodes[MAXADJ+5] = adjNum+1;
		// 	triggerNodes[MAXADJ+4] = 0;
		// 	// printf("NNN%ld\n", triggerNodes[MAXADJ+3]);
		// 	// printf("NNN%ld\n", triggerNodes[MAXADJ+4]);
		// 	// printf("NNN%ld\n", triggerNodes[MAXADJ+5]);
		// 	encrypt_p(triggerNodes, baseKeys[0], baseKeys[1], eventSend.triggerInfo, infoNum);
		// 	MPI_Isend(&eventSend, 1, eventInfo, 0, msgTag, MPI_COMM_WORLD, &req);
		// 	// if (each == 9) {
		// 	// 	printf("Node %d\n", rank);
		// 	// }
		// }
		// if (each == 9) {				
		// 	printf("rank, event%d, %d\n", rank, eventNum);
		// }

		// printf("%d, %d, %d\n", result[0], result[1], result[2]);
		// printf("Rank %d, %d %d %d %d\n", rank, rRand[0], rRand[1], rRand[2], rRand[3]);
		// if (cartRank == 5) {
		// 	// printf("%d\n", adjNum);
		// 	printf("%d %d %d\n", numOccurrence[0], numOccurrence[1], numOccurrence[2]);
		// 	printf("%d !! %d, %d, %d\n", cartRank, rRand[0],rRand[1],rRand[2]);
		// 	printf("%d !! %d\n", cartRank, eventNum);
		// 	printf("%d %d %d\n", adjNodes[0], adjNodes[1], adjNodes[2]);
		// 	printf("%d, %d, %d, A %d, %d, %d, A %d, %d, %d\n", result[0][0], result[0][1], result[0][2], result[1][0], result[1][1], result[1][2], result[2][0], result[2][1], result[2][2]);
		// 	// printf("%d, %d\n", result[0][0], result[0][1]);
		// 	printf("%d, %d, %d, A %d, %d, %d A %d, %d, %d\n", window[0][0], window[0][1], window[0][2], window[1][0], window[1][1], window[1][2], window[2][0], window[2][1], window[2][2]);
		// 	// printf("%d, %d, %d, %d, %d, %d, %d, %d, %d\n", result[0][0], result[0][1], result[0][2], result[1][0], result[1][1], result[1][2], result[2][0], result[2][1], result[2][2]);
		// }
		// // printf("%d, %d, %d, %d\n", rSize*adjNum*windowSize, result[0][0], result[1][0], result[2][0]);
		endIteration = MPI_Wtime();
		// printf("%f\n", endIteration-startIteration);
		// if (rank == 0) {
		// 	printf("%f\n", startIteration);
		// 	printf("%f\n", endIteration);
			// printf("%f\n", iterationTime+startIteration-endIteration);
		// }
		sleep(iterationTime+startIteration-endIteration);
	}
	triggerTime = time(NULL);
	sprintf(timeString, "%s", asctime(localtime(&triggerTime)));
	// printf("%d\n", stringLen);
	timeString[timeMsgLen-1] = 0;
	char2long(timeString, eventSend.timestamp, timeMsgLen);
	encrypt_p(eventSend.timestamp, baseKeys[0], baseKeys[1], eventSend.timestamp, timeMsgLen);

	long summary[maxlen];
	memset(summary, -1, 12);
	for (j=0; j<MAXADJ; j++) {
		if (j < adjNum) {
			summary[2*j] = adjNodes[j]+1;
			summary[2*j+1] = triggerNum[j];
		} else {
			summary[2*j] = -1;
			summary[2*j+1] = -1;
		}
	}
	summary[MAXADJ*2] = rank;
	summary[MAXADJ*2+1] = totalEventNum;
	summary[MAXADJ*2+2] = (endKey - startKey)*scale;
	summary[MAXADJ*2+3] = allComm*scale;
	// sprintf(summary,"Adjacent nodes %d, %d, %d, %d activated %d, %d, %d, %d events, %d events in total, taken %.2f seconds to exchange the keys, taken %.2f seconds to communicate between nodes", (int)dSummary[0], (int)dSummary[2], (int)dSummary[4], (int)dSummary[6], (int)dSummary[1], (int)dSummary[3], (int)dSummary[5], (int)dSummary[7], (int)dSummary[9], dSummary[10], dSummary[11]);  

	// sprintf(&summary[MAXADJ*2], "%d", rank);
	// sprintf(&summary[MAXADJ*2+1], "%d", eventNum);
	// sprintf(&summary[MAXADJ*2+2], "%f", endKey - startKey);
	// sprintf(&summary[MAXADJ*2+3], "%f", allComm);
	// printf("%d\n", summary[0]);
	// printf("%f\n", allComm);
	// sprintf(&summary[0], "%f", allComm);
	// sprintf(&summary[1], "%d", rank);
	// if (cartRank == 5) {
	// 	printf("%s\n", summary);
	// }
	// printf("%s\n", summary);
	// int summaryLen = strlen(summary);
	// summary[199] = summaryLen;
	// printf("%d\n", summaryLen);
	// char2long(dSummary, eventSend.triggerInfo, summaryLen);
	// printf("%ld, %ld, %ld, %ld\n", eventSend.triggerInfo[0], eventSend.triggerInfo[1], eventSend.triggerInfo[2], eventSend.triggerInfo[3]);
	encrypt_p(summary, baseKeys[0], baseKeys[1], eventSend.triggerInfo, 12);
	// eventSend.triggerInfo[maxlen*4-1] = summaryLen;
	// printf("%ld\n", eventSend.triggerInfo[199]);
	// printf("%ld\n", eventSend.triggerInfo[1]);
	// printf("%ld\n",eventSend.triggerInfo[maxlen*4-1] );
	MPI_Isend(&eventSend, 1, eventInfo, 0, exitTag, MPI_COMM_WORLD, &req);
	// printf("%d, %d\n", cartRank, eventNum);
	// if (rank == 1) {
	// 	end = MPI_Wtime();
	// 	printf("%f\n", end-start);
	// }
	free(adjNodes);

	return 0;
}