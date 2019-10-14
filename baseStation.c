#include "wsn.h"

int baseStation(int msgTag, int exitTag, int rank, MPI_Datatype eventInfo) {
	FILE* fp;
	MPI_Status stat;
	MPI_Request req;
	double start, end, startComm, endComm, startPre, endPre, startEn, endEn;
	event eventRecv;
	long pubKeys[2], priKeys[2], infoTem[maxlen], timeTemp[maxlen];
	char timeInfo[maxlen];
	time_t triggerTime;
	// char timestamp[maxlen];

	startPre = MPI_Wtime();
	fp=fopen("log.txt","w");
	getKeys(rank, pubKeys, priKeys);
	printf("%ld, %ld\n", pubKeys[0], pubKeys[1]);
	printf("%ld, %ld\n", priKeys[0], priKeys[1]);
	MPI_Bcast(pubKeys, 2, MPI_LONG, rank, MPI_COMM_WORLD);
	endPre = MPI_Wtime();
	fprintf(fp, "Preparation finished, %f seconds taken\n\n", endPre - startPre);

	start = MPI_Wtime();
	int nNodes = 20;
	double matrix[numOfIterations][4];
	memset(matrix, 0, sizeof(matrix[0][0])*4*numOfIterations);

	sleep(5);
	while (nNodes > 0) {
		startComm = MPI_Wtime();
		MPI_Irecv(&eventRecv,1,eventInfo,MPI_ANY_SOURCE,MPI_ANY_TAG,MPI_COMM_WORLD,&req);
		MPI_Wait(&req, &stat);
		endComm = MPI_Wtime();
		if (stat.MPI_TAG==exitTag) {
            nNodes -= 1;
            // stringLen = eventRecv.timestamp[maxlen-1];
            // summaryLen = (long)eventRecv.triggerInfo[maxlen*4-1];
            // printf("%ld\n", summaryLen);
            // printf("%d\n", strlen(eventRecv.timestamp));
            // summaryLen = eventRecv.triggerInfo[maxlen*10-1];
            // printf("%d\n", strlen(eventRecv.triggerInfo));
            // printf("%ld\n", eventRecv.triggerInfo[199]);
            // decrypt_p(&eventRecv.triggerInfo[maxlen*10-1], priKeys[0], priKeys[1], &summaryLen, 1);
            // printf("%ld\n", summaryLen);
            // printf("%ld\n", eventRecv.triggerInfo[1]);
		// decrypt_p(eventRecv.timestamp, priKeys[0], priKeys[1], timeTemp, timeMsgLen);
		// decrypt_p(eventRecv.triggerInfo, priKeys[0], priKeys[1], infoTem, summaryLen);
		// long2char(timeTemp, timeInfo, timeMsgLen);

		// // long2char(eventRecv.triggerInfo, summary, 12);
		// fprintf(fp, "Node %ld terminated at %s\n", infoTem[8], timeInfo);
		// // triggerTime = time(NULL);
		// // fprintf(fp, "Node %ld terminated at %s", eventRecv.triggerInfo[8], asctime(localtime(&triggerTime)));
		// fprintf(fp,"Adjacent nodes %ld, %ld, %ld, %ld activated %ld, %ld, %ld, %ld events, %ld events in total, %f seconds taken to exchange the keys, %f seconds taken to communicate with adjacent nodes\n\n", infoTem[0], infoTem[2], infoTem[4], infoTem[6], infoTem[1], infoTem[3], infoTem[5], infoTem[7], infoTem[9], (double)infoTem[10]/scale, (double)infoTem[11]/scale); 
		} else {
			
			// printf("tr%ld\n", eventRecv.triggerInfo[infoNum-1]);
			// for (int k = 0; k<infoNum; k++) {
			// 	printf("%lda\n", eventRecv.triggerInfo[k]);
			// }
			long inmsg[maxlen];
			long outmsg[maxlen];
			long decrmsg[maxlen];
			char cinmsg[maxlen];
			char coutmsg[maxlen];
			char cdecrmsg[maxlen];
			sprintf(cinmsg, "%s", "abcde");
			int len;
			printf("%ld\n", pubKeys[0]);
			printf("%ld\n", pubKeys[1]);
			len = strlen(cinmsg);
			// startEn = omp_get_wtime();
			char2long(cinmsg, inmsg, len);
			encrypt(inmsg, pubKeys[0], pubKeys[1], outmsg, len);
			// for (int i = 0; i<len; i++) {
			// 	printf("%ld\t", outmsg[i]);
			// }
			decrypt(outmsg, priKeys[0], priKeys[1], decrmsg, len);
			long2char(decrmsg, cdecrmsg, len);
			printf("%s\n", cdecrmsg);

			// endEn = omp_get_wtime();
			// printf("Process time Serial (s): %lf\n", endEn-startEn);



			// startEn = omp_get_wtime();

			char2long(cinmsg, inmsg, len);
			encrypt_p(inmsg, pubKeys[0], pubKeys[1], outmsg, len);
			// for (int i = 0; i<len; i++) {
			// 	printf("%ld\t", outmsg[i]);
			// }
			decrypt_p(outmsg, priKeys[0], priKeys[1], decrmsg, len);
			long2char(decrmsg, cdecrmsg, len);
			printf("%s\n", cdecrmsg);

			// endEn = omp_get_wtime();
			// printf("Process time Parallel (s): %lf\n", endEn-startEn);
			// endEn = MPI_Wtime();
			// printf("%f\n", endEn-startEn);
			// if (stat.MPI_TAG == msgTag) {
			// printf("%d\n", stat.MPI_TAG);
			// long tt = eventRecv.timestamp[timeMsgLen-1];
			// printf("%ld\n", tt);
			// printf("%ld\n", timeTemp[timeMsgLen-1]);
			// printf("%ld\n", eventRecv.timestamp[timeMsgLen-1]);
			// for (i = )
		// startEn = MPI_Wtime();
		// decrypt_p(eventRecv.triggerInfo, priKeys[0], priKeys[1], infoTem, infoNum);
		// decrypt_p(eventRecv.timestamp, priKeys[0], priKeys[1], timeTemp, timeMsgLen);
		// endEn = MPI_Wtime();
		// printf("Parallel: %f\n", endEn-startEn);

		// startEn = MPI_Wtime();
		// decrypt(eventRecv.triggerInfo, priKeys[0], priKeys[1], infoTem, infoNum);
		// decrypt(eventRecv.timestamp, priKeys[0], priKeys[1], timeTemp, timeMsgLen);
		// endEn = MPI_Wtime();
		// printf("Serial: %f\n", endEn-startEn);

		// long2char(timeTemp, timeInfo, timeMsgLen);
		// fprintf(fp, "Event occurred at %s\n", timeInfo);
		// // triggerTime = time(NULL);
		// // fprintf(fp, "Event occurred at %s", asctime(localtime(&triggerTime)));
		// fprintf(fp, "Event reported from Node %ld, adjacent nodes %ld, %ld, %ld, %ld, gave number %ld at iteration %ld\n", infoTem[4], infoTem[0], infoTem[1], infoTem[2], infoTem[3], infoTem[5], infoTem[6]);   
		// fprintf(fp, "This communication between the baseStation and the node took %f seconds\n\n", endComm-startComm);
		// // } else {
		// // 	endEn = MPI_Wtime();
		// // }
		// // // printf("%f\n", endEn - startEn);
		// // // printf("%s\n", timeInfo);
		// // // printf("%d\n", stringLen);
		// // // printf("%ld\n", eventRecv.triggerInfo[6]);
		// matrix[infoTem[6]][0] += (double)infoTem[7]/scale + endEn - startEn;
		// matrix[infoTem[6]][1] += infoTem[8];
		// matrix[infoTem[6]][2] += infoTem[9];
		// matrix[infoTem[6]][3] += endEn - startEn;
			// printf("%f\n", endEn-startEn);
			// // int aaaa= 0, bbb=0;
			// // if (eventRecv.triggerInfo[6] == 9) {
			// // 	aaaa += eventRecv.triggerInfo[9];
			// // 	printf("%ld\n", eventRecv.triggerInfo[4]);
			// // }
			// // printf("%ld, %ld\n", eventRecv.triggerInfo[6], eventRecv.triggerInfo[9]);
		}
	// 	// memset(eventRecv.triggerInfo, 0, sizeof(eventRecv.triggerInfo[0])*maxlen);
	// 	// memset(eventRecv.timestamp, 0, sizeof(eventRecv.timestamp[0])*maxlen);
	}
	// MPI_Wait(&req, &stat);
	// double totalTime = 0;
	// double totalTimeNB = 0;
	// fprintf(fp, "Iteration\tEncryption Time\tNumber of Events\tNumber of Messages\tBaseStation Encryption Time\n");
	// int each;
	// for (each = 0; each < numOfIterations; each++) {
	// 	fprintf(fp, "%d\t\t%f\t\t%d\t\t%d\t\t%f\n", each+1, matrix[each][0], (int)matrix[each][1], (int)matrix[each][2], matrix[each][3]);
	// 	totalTime += matrix[each][0];
	// 	totalTimeNB += matrix[each][3];
	// }
	// // printf("%f\n", totalTime);
	// // printf("%f\n", totalTimeNB);
	// fprintf(fp, "Average Encryption Time: %f\n", totalTime/numOfIterations);
	// fprintf(fp, "Average Encryption Time in the BaseStation: %f\n", totalTimeNB/numOfIterations);
	// end = MPI_Wtime();
	// fprintf(fp, "\nThe program finished correctly, it has taken %f seconds in total\n", end-start);
	// fclose(fp);

	return 0;
}