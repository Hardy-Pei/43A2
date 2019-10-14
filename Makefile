all: run

run: compile
	mpirun -n 21 ./run
	

compile:
	mpicc -c wsn.c baseStation.c nodes.c encryption.c
	mpicc -fopenmp -o run wsn.o baseStation.o nodes.o encryption.o
	


