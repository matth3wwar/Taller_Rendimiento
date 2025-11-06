GCC = gcc
CFLAGS = -lm
FOPENMP = -fopenmp -O3
POSIX = -lpthread

PROGRAMAS = mmClasicaFork mmClasicaPosix mmClasicaOpenMP creadorCSV

All: $(PROGRAMAS)

mmClasicaFork:
	$(GCC) $(CLFAGS) $@.c -o $@

mmClasicaPosix:
	$(GCC) $(CLFAGS) $@.c -o $@ $(POSIX)

mmClasicaOpenMP:
	$(GCC) $(CLFAGS) $@.c -o $@ $(FOPENMP)

creadorCSV:
	$(GCC) $(CLFAGS) $@.c -o $@

clean:
	$(RM) $(PROGRAMAS)
