#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <stddef.h>
#include <mpi.h>
#include <omp.h>
#include <sys/socket.h>
#include <ifaddrs.h>

#define ROW 4
#define COLUMN 5
#define MAXADJ 4
#define numOfIterations 5
#define windowSize 3
#define rSize 10
#define iterationTime 0.25
#define infoNum 10
#define maxlen 40
#define timeMsgLen 25
#define summaryLen 12
#define scale 1000000

int encrypt(long *in, long exp, long mod, long *out, size_t len);
int decrypt(long * in, long exp, long mod, long * out, size_t len);
int char2long(char *in, long *out, size_t len);
int long2char(long *in, char *out, size_t len);
int decrypt_p(long * in, long exp, long mod, long * out, size_t len);
int encrypt_p(long *in, long exp, long mod, long *out, size_t len);
int baseStation(int msgTag, int exitTag, int rank, MPI_Datatype eventInfo);
int nodes(MPI_Comm cartComm, int interNodeTag, int eventTag, int msgTag, int exitTag, int rank, MPI_Datatype eventInfo);
int getKeys(int rank, long *pub, long *pri);

typedef struct event {
	long timestamp[maxlen];
	long triggerInfo[maxlen];
} event;