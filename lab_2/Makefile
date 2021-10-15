# kompilator c
CCOMP = gcc

# konsolidator
LOADER = gcc

# opcje optymalizacji:
# wersja do debugowania
 OPT = -g -DDEBUG
# wersja zoptymalizowana do mierzenia czasu
#OPT = -O3

# pliki naglowkowe
INC = -I../pomiar_czasu

# biblioteki
LIB = -L../pomiar_czasu -lpomiar_czasu -lm

# zaleznosci i komendy
fork: fork.o 
	$(LOADER) $(OPT) fork.o -o fork $(LIB)

# jak uzyskac plik fork.o ?
fork.o: fork.c ../pomiar_czasu/pomiar_czasu.h
	$(CCOMP) -c $(OPT) fork.c $(INC) 

# zaleznosci i komendy
clone: clone.o
	$(LOADER) $(OPT) clone.o -o clone $(LIB)

# jak uzyskac plik clone.o ?
clone.o: clone.c ../pomiar_czasu/pomiar_czasu.h
	$(CCOMP) -c $(OPT) clone.c $(INC)

# zaleznosci i komendy
program: program.o
	$(LOADER) $(OPT) program.o -o program $(LIB)

# jak uzyskac plik clone.o ?
program.o: program.c ../pomiar_czasu/pomiar_czasu.h
	$(CCOMP) -c $(OPT) program.c $(INC)


# zaleznosci i komendy
program_clone: program_clone.o
	$(LOADER) $(OPT) program_clone.o -o program_clone

# jak uzyskac plik clone.o ?
program_clone.o: program_clone.c ../pomiar_czasu/pomiar_czasu.h
	$(CCOMP) -c $(OPT) program_clone.c


clean:
	rm -f *.o clone fork program
