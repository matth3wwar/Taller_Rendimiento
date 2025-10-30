/*#######################################################################################
 #* Fecha:
 #* Autor: J. Corredor, PhD
 #* Programa:
 #*      Multiplicación de Matrices algoritmo matriz Transpuesta (Filas x Filas) 
 #* Versión:
 #*      Paralelismo con OpenMP
 #######################################################################################*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/time.h>
#include <omp.h>


struct timeval inicio, fin; 

void InicioMuestra(){
	gettimeofday(&inicio, (void *)0);
}

void FinMuestra(){
	gettimeofday(&fin, (void *)0);
	fin.tv_usec -= inicio.tv_usec;
	fin.tv_sec  -= inicio.tv_sec;
	double tiempo = (double) (fin.tv_sec*1000000 + fin.tv_usec); 
	printf("%9.0f \n", tiempo);
}

void impMatrix(double *matrix, int D, int t){
	int aux = 0;
	if(D < 6)
		switch(t){
			case 0:
				for(int i=0; i<D*D; i++){
					if(i%D==0) printf("\n");
						printf("%.2f ", matrix[i]);
				}
				printf("\n  - \n");
				break;
			case 1:
				while(aux<D){
					for(int i=aux; i<D*D; i+=D)
						printf("%.2f ", matrix[i]);
					aux++;
					printf("\n");
				}	
				printf("\n  - \n");
				break;
			default:
				printf("Sin tipo de impresión\n");
		}
}

void iniMatrix(double *m1, double *m2, int D){
	for(int i=0; i<D*D; i++, m1++, m2++){
		*m1 = (double)rand()/RAND_MAX*(5.0-1.0);	
		*m2 = (double)rand()/RAND_MAX*(9.0-5.0);		
	}
}

void multiMatrixTrans(double *mA, double *mB, double *mC, int D){
	double Suma, *pA, *pB;
	#pragma omp parallel
	{
	#pragma omp for
	for(int i=0; i<D; i++){
		for(int j=0; j<D; j++){
			pA = mA+i*D;	
			pB = mB+j*D;	
			Suma = 0.0;
			for(int k=0; k<D; k++, pA++, pB++){
				Suma += *pA * *pB;
			}
			mC[i*D+j] = Suma;
		}
	}
	}
}

int main(int argc, char *argv[]){
	if(argc < 3){
		printf("\n Use: $./clasicaOpenMP SIZE Hilos \n\n");
		exit(0);
	}


	int N = atoi(argv[1]);
	int TH = atoi(argv[2]);
	double *matrixA  = (double *)calloc(N*N, sizeof(double));
	double *matrixB  = (double *)calloc(N*N, sizeof(double));
	double *matrixC  = (double *)calloc(N*N, sizeof(double));
	srand(time(NULL));

	omp_set_num_threads(TH);

	iniMatrix(matrixA, matrixB, N);

	impMatrix(matrixA, N, 0);
	impMatrix(matrixB, N, 1);

	InicioMuestra();
	multiMatrixTrans(matrixA, matrixB, matrixC, N);
	FinMuestra();

	impMatrix(matrixC, N, 0);

	/*Liberación de Memoria*/
	free(matrixA);
	free(matrixB);
	free(matrixC);
	
	return 0;
}
