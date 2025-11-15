# Multiplicación de Matrices - Implementaciones Paralelas

Esta carpeta contiene diferentes implementaciones de multiplicación de matrices utilizando diversas técnicas de paralelización.

## - Archivos del taller - 

### 1. Script de Automatización
- *lanzador.pl*: Script en Perl para ejecutar pruebas por lotes del algoritmo mmClasicaFork con diferentes configuraciones.

### 2. Implementaciones de Multiplicación de Matrices

#### *mmClasicaFork.c*
- *Algoritmo*: Multiplicación clásica de matrices
- *Paralelización*: Procesos Fork
- *Características*: Divide el trabajo entre procesos hijos que calculan diferentes filas de la matriz resultante

#### *mmClasicaOpenMP.c*
- *Algoritmo*: Multiplicación clásica de matrices  
- *Paralelización*: OpenMP
- *Características*: Utiliza directivas pragma para paralelización automática

#### *mmClasicaPosix.c*
- *Algoritmo*: Multiplicación clásica de matrices
- *Paralelización*: Pthreads (POSIX)
- *Características*: Implementación con hilos usando la biblioteca pthread

#### *mmFilasOpenMP.c*
- *Algoritmo*: Multiplicación con matriz transpuesta (Filas × Filas)
- *Paralelización*: OpenMP
- *Características*: Optimización mediante acceso a memoria más eficiente

# Organización de las ramas

El repositorio está organizado en una rama principal con los ejecutables base y una rama por cada computadora por la cual se hayan hecho las pruebas de rendimientos.

Cada rama nombrada por el id de una de las computadoras utilizadas, contiene los archivos correspondientes a las ejecuciones en archivos con el formato:

[ejecutable]-[dimension_matriz]-[hilos].dat

En cada rama correspondiente a la prueba de una computadora, se tienen un archivo .csv con el recopilado final de los datos de esa computadora en segundos con el formato:

DATOS_[computadora]_[ejecutable].csv

Para correr el código de creadorCSV.c se utilizan los siguientes comandos:

```bash
#en consola:
make creadorCSV
./creadorCSV [ejecutable]_[dirección_salida]_[nombre_salida]
```

# Compilación y ejecución de mmClasicaFork

# Editar lanzador.pl y cambiar:
$Nombre_Ejecutable = "mmClasicaFork";

```bash
# En consola:
make mmClasicaFork
chmod +x lanzador.pl
./lanzador.pl
```

# Compilación y ejecución de mmClasicaPosix

# Editar lanzador.pl y cambiar:
$Nombre_Ejecutable = "mmClasicaPosix";

```bash
# En consola:
make mmClasicaPosix
chmod +x lanzador.pl
./lanzador.pl
```

#Compilación y ejecución de mmClasicaOpenMP

# Editar lanzador.pl y cambiar:
$Nombre_Ejecutable = "mmClasicaOpenMP";

```bash
# En consola:
make mmClasicaOpenMP
chmod +x lanzador.pl
./lanzador.pl
