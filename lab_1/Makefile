# kompilator c
CCOMP = gcc

# konsolidator
LINKER = gcc

# opcje optymalizacji:
# wersja do debugowania
# OPT = -g -DDEBUG
# wersja zoptymalizowana do mierzenia czasu
OPT = -O3

# pliki naglowkowe
INC = -I../pomiar_czasu

# biblioteki
LIB = -L../pomiar_czasu -lpomiar_czasu -lm

# zaleznosci i komendy
moj_program: moj_program.o
	$(LINKER) $(OPT) moj_program.o -o moj_program $(LIB)

# jak uzyskac plik moj_program.o ?
moj_program.o: moj_program.c ../pomiar_czasu/pomiar_czasu.h
	$(CCOMP) -c $(OPT) moj_program.c $(INC)

clean:
	rm -f *.o
