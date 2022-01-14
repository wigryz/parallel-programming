# kompilator c
CCOMP = /usr/lib64/openmpi/bin/mpicc

# konsolidator
LOADER = /usr/lib64/openmpi/bin/mpicc

MPIRUN = /usr/lib64/openmpi/bin/mpiexec 

OPT = -O2 -fopenmp

LIB =  -lm

# zaleznosci i komendy
all: mat_vec_row_MPI run

mat_vec_row_MPI: oblicz_PI.o
	$(LOADER) $(OPT) oblicz_PI.o -o oblicz_PI $(LIB)

mat_vec_row_MPI.o: oblicz_PI.c
	$(CCOMP) -c $(OPT) oblicz_PI.c $(INC)

run:
	$(MPIRUN) -np 4 --oversubscribe  ./oblicz_PI

clean:
	rm -f *.o ./oblicz_PI
