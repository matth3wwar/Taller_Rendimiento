/*
  merge_assume_list.c
  Construye filenames mmClasicaFork-<iter>-Hilos-<threads>.dat para
  iter = {1000,2000,4000} y threads = {1,2,4,8,16},
  lee hasta 30 mediciones de cada archivo y genera un CSV con:
    Configuracion,Iter1,...,Iter30

  Compilar:
    gcc -std=c11 -O2 -o merge_assume_list merge_assume_list.c

  Ejecutar:
    ./merge_assume_list [DIRECTORIO] [FICHERO_SALIDA]
  Ejemplos:
    ./merge_assume_list            -> usa directorio actual y "merged.csv"
    ./merge_assume_list datos out.csv
*/

#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

const int ITERS[] = {1000, 2000, 4000};
const int N_ITERS = sizeof(ITERS) / sizeof(ITERS[0]);
const int THREADS[] = {1, 2, 4, 8, 16};
const int N_THREADS = sizeof(THREADS) / sizeof(THREADS[0]);
const int EXPECTED = 30;     // columnas Iter1..Iter30
const int MAX_READ = 1000;   // to avoid reading insane amount; we'll cap to EXPECTED anyway

int main(int argc, char *argv[]) {
	const char *process = "mmClasicaFork";
	const char *dir = ".";
	const char *outname = "merged.csv";
	int convertToSeconds = 1;

	for (int _i = 0; _i < argc; _i++) {
		if (strcmp(argv[_i], "-c") == 0 || strcmp(argv[_i], "--convertToSeconds") == 0)
			convertToSeconds = 1;
		else {
			if (_i == 1)
				process = argv[1];
		    	if (_i == 2)
				dir = argv[2];
			if (_i == 3)
				outname = argv[3];
		}
	}
	FILE *out = fopen(outname, "w");
	if (!out) {
		fprintf(stderr, "Error: no se pudo crear '%s': %s\n", outname, strerror(errno));
		return 1;
	}
	/*Header*/
	fprintf(out, "Configuracion");
	for (int c = 1; c <= EXPECTED; ++c) fprintf(out, ",Iter%d", c);
	fprintf(out, "\n");

	char filename[4096];
	char filepath[8192];
	for (int i = 0; i < N_ITERS; ++i) {
		for (int j = 0; j < N_THREADS; ++j) {
			int iter = ITERS[i];
			int th = THREADS[j];

           		/*construir nombre y ruta*/
			snprintf(filename, sizeof(filename), "%s-%d-Hilos-%d.dat", process, iter, th);
			int n = snprintf(filepath, sizeof(filepath), "%s/%s", dir, filename);

			if (n >= (int)sizeof(filepath)) {

				fprintf(stderr, "Ruta demasiado larga para %s/%s, se omite.\n", dir, filename);

				/*Aun asi escribir fila vacía para mantener el orden*/
				fprintf(out, "%d-%d", iter, th);

				for (int c = 0; c < EXPECTED; ++c)
					fprintf(out, ",");

				fprintf(out, "\n");
				continue;
			}
			/*Abrir archivo en modo lectura*/
			FILE *f = fopen(filepath, "r");
			double values[EXPECTED];
			int count = 0;

			if (!f) {
				//Archivo no existe o no se puede abrir
				fprintf(stderr, "Aviso: no se encontró/abrir '%s' (%s). Se dejarán campos vacíos.\n", filepath, strerror(errno));
			} else {
				// leer hasta EXPECTED valores
				while (count < MAX_READ) {
					double v;
					if (fscanf(f, "%lf", &v) != 1)
						break;
					if (convertToSeconds)
						v /= 1000000;
					if (count < EXPECTED)
						values[count] = v;

					count++;

					if (count >= EXPECTED) {
						/****************************************************************
						* Aun seguimos contando en case haya más de EXPECTED, pero no almacenamos
						* solo rompemos porque no necesitamos más
						****************************************************************/
						break;
					}
				}
				if (count == 0) {
					fprintf(stderr, "Aviso: archivo '%s' no contiene valores numéricos.\n", filepath);
				} else if (count < EXPECTED) {
					fprintf(stderr, "Aviso: '%s' tiene %d valores (esperado %d). Se completará con campos vacíos.\n", filepath, count, EXPECTED);
				}
				fclose(f);
			}
			/*escribir fila: Configuracion, then up to EXPECTED values (or blanks)*/
			fprintf(out, "%d-%d", iter, th);
			for (int c = 0; c < EXPECTED; ++c) {
				if (f && c < count && count > 0 && c < EXPECTED) {
					// if file opened and we have value stored at c
					if (c < count)
						fprintf(out, ",%.10g", values[c]);

					else
						fprintf(out, ",");
				} else {
					// either file missing or not enough values -> blank
					fprintf(out, ",");
				}
			}

			fprintf(out, "\n");
		}
	}

	fclose(out);
	printf("CSV generado: %s\n", outname);
	return 0;
}

