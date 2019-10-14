#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <unistd.h>
#include <string.h>

void xorP(char *inpString, char *output);
void xor(char *input, char *output);
char* concatenate_string(char *first, char *second, int size, int keySize);

int main(int argc, char* argv[])
{
	clock_t start, end;
	double cpu_time_used;

	// char *sample = "GeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeksGeeksforGeeks";
	char *sample = "3";
	// for (int j=0; j<1513256; j++) {
	// 	*sample += "1";
	// }
	int strLength = strlen(sample);
	char encrypted[1000];
	char decrypted[1000];
	printf("%ld\n", sizeof(encrypted));
	// char *encrypted = (char*)malloc(strLength+1);
	// char *decrypted = (char*)malloc(strLength+1);

	start = clock();
	// sample = concatenate_string(sample, sample);
	// printf("%s\n", sample);
	xor(sample, encrypted);
	printf("encrypted: %s\n", encrypted);
	xor(encrypted, decrypted);
	printf("decrypted: %s\n", decrypted);
	end = clock();
	cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
	printf("Process time (s): %lf\n", cpu_time_used);

	// start = clock();
	// xorP(sample, encrypted);
	// // printf("%s\n", encrypted);
	// xorP(encrypted, decrypted);
	// // printf("%s\n", decrypted);
	// end = clock();
	// cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
	// printf("Process time (s): %lf\n", cpu_time_used);
	return 0;
}

void xorP(char *input, char *output) {
	int nthreads, tid, i, chunk=3;
	int num = 165489551;
	char xorKey[1000]; 
	sprintf(xorKey, "%d", num);
	printf("keySize: %ld\n", sizeof(xorKey));
	#pragma omp parallel shared (nthreads, chunk, input, output, xorKey) private(i, tid) 
	{
		// tid = omp_get_thread_num();
		// if (tid == 0) {
		// 	nthreads = omp_get_num_threads();
		// 	printf("Number of thread = %d\n", nthreads);
		// }
		#pragma omp for schedule(dynamic, chunk)
		for (i=0; i<strlen(input); i++) {
			output[i] = input[i] ^ xorKey[i%sizeof(xorKey) / sizeof(char)];
		}
		output[strlen(input)] = '\0';
	}
}

void xor(char *input, char *output) {
	int num = 165489551;
	char xorKey[1000]; 
	sprintf(xorKey, "%d", num);
	printf("keySize: %ld\n", strlen(xorKey));
	int i, j, size = strlen(input), keySize = strlen(xorKey);
	// printf("input: %ld\n", strlen(input));
	// printf("output0: %ld\n", strlen(output));
	for (i=0; i<size; i++) {
		output[i] = input[i];
	}
	printf("output: %d\n", size);
	for (j = 0; j < 3; j++) {
		// printf("output: %ld\n", strlen(output));
		// printf("FFF, %s\n", output);
		for (i=0; i<size; i++) {
			output[i] = output[i] ^ xorKey[i%keySize];
		}
		printf("FF, %s\n", output);
		// printf("%d\n", size);
		output = concatenate_string(output, xorKey, size, keySize);
		size += keySize;
		// printf("%d\n", size);
		printf("HH, %s\n", output);
		// printf("%ld\n", strlen(output));
	}

	// // printf("output1: %ld\n", strlen(output));
	// output[strlen(input)] = '\0';
	// // printf("HH, %s\n", output);
	printf("Final output%s\n", output);
	output[size] = '\0';
}

char* concatenate_string(char *first, char *second, int size, int keySize) {
	char *new = (char*)malloc((size+keySize+1)*sizeof(char));
	int i, j;
	for (i = 0; i < strlen(first); i++) {
		new[i] = first[i];
	}
	for (j = 0; j < strlen(first); j++) {
		new[i+j] = second[j];
	}
	new[size+keySize] = '\0';
	return new;
}