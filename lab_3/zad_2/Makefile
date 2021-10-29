# kompilator c
CCOMP = gcc

# konsolidator
LOADER = gcc

# opcje optymalizacji:
 OPT = -g -DDEBUG
#OPT = -O3

# zaleznosci i komendy
program: program.o
	$(LOADER) $(OPT) -pthread program.o -o program $(LIB)

program.o: program.c
	$(CCOMP) -c $(OPT) program.c $(INC)

clean:
	rm -f *.o program
