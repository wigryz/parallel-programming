# prosty Makefile dla prostych programow

# nazwa pliku z kodem wykonywalnym
NAZWA = openmp_petle_simple

# kompilator C
CC = gcc
# konsolidator (linker, loader) C
LD = gcc
# archiwizator (program do tworzenia bibliotek)
AR = ar -ru

# opcje kompilacji
CFL = -pthread
LDFL = -pthread
# katalogi z bibliotekami i dolaczane biblioteki
LIB = -L. -lm
# katalogi z plikami naglowkowymi i wklejane pliki naglowkowe 
INC = -I.

petle_simple:
	gcc -fopenmp openmp_petle_simple.c -o openmp_petle_simple

petle:
	gcc -fopenmp openmp_petle.c -o openmp_petle

clean:
	rm *.o openmp_petle_simple openmp_petle
