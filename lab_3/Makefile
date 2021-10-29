# kompilator c
CCOMP = gcc

# konsolidator
LOADER = gcc

# opcje optymalizacji:
 OPT = -g -DDEBUG
#OPT = -O3

# zaleznosci i komendy
pthreads_detach_kill: pthreads_detach_kill.o
	$(LOADER) $(OPT) -pthread pthreads_detach_kill.o -o pthreads_detach_kill $(LIB)

pthreads_detach_kill.o: pthreads_detach_kill.c
	$(CCOMP) -c $(OPT) pthreads_detach_kill.c $(INC)

clean:
	rm -f *.o
