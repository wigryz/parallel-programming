# kompilator c
CCOMP = gcc

# konsolidator
LOADER = gcc

# opcje optymalizacji:
 OPT = -g -DDEBUG
#OPT = -O3

# zaleznosci i komendy
pub_sym_1: pub_sym_1.o
	$(LOADER) $(OPT) -pthread pub_sym_1.o -o pub_sym_1 $(LIB)

pub_sym_1.o: pub_sym_1.c
	$(CCOMP) -c $(OPT) pub_sym_1.c $(INC)

clean:
	rm -f *.o pub_sym_1
