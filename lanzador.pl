#**************************************************************
#         		Pontificia Universidad Javeriana
#     Autor: Elier Ibarra
#     Fecha: 01/11/2025
#     Materia: Sistemas Operativos
#     Tema: Taller de Evaluación de Rendimiento
#     Fichero: script automatización ejecución por lotes 
#****************************************************************/

$Path = `pwd`;
chomp($Path);

$Nombre_Ejecutable = "mmClasicaOpenMP";
@Size_Matriz = ("1000","2000","4000");
@Num_Hilos = (1,2,4,8,16);
$Repeticiones = 30;

foreach $size (@Size_Matriz){
	foreach $hilo (@Num_Hilos) {
		$file = "$Path/$Nombre_Ejecutable-".$size."-Hilos-".$hilo.".dat";
		for ($i=0; $i<$Repeticiones; $i++) {
system("$Path/$Nombre_Ejecutable $size $hilo  >> $file");
			printf("$Path/$Nombre_Ejecutable $size $hilo \n");
		}
		close($file);
	$p=$p+1;
	}
}
