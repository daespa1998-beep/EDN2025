## parcial de programacion en C
Este programa guarda las notas  de un grupo de estudiantes, se calcula nota maxima, promedio, ordena de menor a mayor  implementando recursividad y  selection  Sort.
-----------------------------------------------------------------------------------------------------
## Feciones o menu con 5 opciones 
+ 1.  calcular la nota maxima:
- usa una funcion recursiva  uqe compara nota una a una  para encontrar el mayor
+ 2.  calcula el promedio:
- suma todas las nota  con una funcion recursiva y luego se divide por "n" que esta definido como 5 que es la cantidad de estudiantes 
+ 3.  ordena estudiantes por codigo de select sort:
- sse aplica el algoritmo de selection sort  para reordenar  la lista,  recorre el arreglo buscando el mas pequeño, lo coloca en primera posicion luego el siguiente mas pequeño y lo coloca e segundo y lo va poniendo en orden
+ 4.  mostrar lista :
- imprime  en pantalla el codigo y la nota del estudiante 
+ 5.  salir:
- finaliza la ejecucion del programa 
+ -- si pone un numero diferente de las opciones se muestra  que no es valida y indica que lo intente de nuevo 
-----------------------------------------------------------------------------------------------------
## ejemplos  del codigo en ejecucion
----  Menu---
+ 1. Nota Maxima
+ 1. Nota Maxima
+ 2. Promedio
+ 3. Ordenar por codigo de estudiante
+ 4. Mostrar lista de estudiantes
+ 5. Salir
+ elige opcion:
--------------------------------------
+ elige opcion: 1
+ la nota maxima es: 5.0
------------------------------
+ elige opcion: 2
+ el promedio es: 3.38
----------------------------------------------
+ elige opcion: 3
+ Estudiantes ordenados por codigo:
+ Codigo: 2545555, Nota: 2.5
+ Codigo: 12556132, Nota: 3.4
+ Codigo: 215465344, Nota: 1.5
+ Codigo: 1235138975, Nota: 4.5
+ Codigo: 1446511654, Nota: 5.0
------------------------------------------
+ elige opcion: 4
+ Codigo: 2545555, Nota: 2.5
+ Codigo: 12556132, Nota: 3.4
+ Codigo: 215465344, Nota: 1.5
+ Codigo: 1235138975, Nota: 4.5
+ Codigo: 1446511654, Nota: 5.0
---------------------------------------
+ elige opcion: 15
+ Opcion no valida. Intente de nuevo.
----------------------------------------
+ elige opcion: 5
+ adios :)  saliendo del programa.