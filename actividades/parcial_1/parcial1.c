#include <stdio.h>
//estrutura que estamos def
typedef struct {
    int codigo;
    float nota;
} Estudiante;
// datos de los estudiante 
Estudiante estud[]= {
    {1235138975, 4.5},
    {2545555, 2.5},
    {12556132, 3.4},//la nota me marca error 
    {215465344, 1.5},
    {1446511654, 5.0}
};
int n = 5;   
// puse la cantidad de estudiantes 
// funciones,  nota maxima
float notaMax(int i){
    if (i == n- 1)return estud[i] .nota;
    float max =notaMax (i + 1);
    return (estud[i] .nota > max) ?  estud[i] .nota: max; 
    //? if-else // esta funcion calcula la nota maxima
}
// promedio
float sumaNotas(int i){
    if (i == n- 1) return estud[i] .nota;
    return estud[i] .nota + sumaNotas(i + 1);
    // esta funcion calcula la suma de las notas
}
//select sort por codigo de estudiante
void selectionSort(Estudiante estud[], int n)// funcion para ordenar
{
    for (int i = 0; i < n - 1; i++) {
        int minIndex = i;
        for (int j = i + 1; j < n; j++) {
            if (estud[j].codigo < estud[minIndex].codigo) {
                minIndex = j;
            }
        }
        // Intercambia el elemento minimo con el primer
        Estudiante temp=estud[i];// temp es una variable temporal
        estud[i]=estud[minIndex];
        estud[minIndex]=temp;
    }
}
//mostrar lista
void mostrar(estudiantes estud[], int n) {
    printf("mostrar %d estudiantes:\n", n);
    for (int i = 0; i< n; i++) {
        printf("Codigo: %d,  Nota: %.1f\n", estud[i].codigo, estud[i].nota); 
    }
}

// menu de opciones
int main() {
    int opcion; 
    do {
        printf("\n  Menu  \n");
        printf("1. Nota Maxima \n");
        printf("2. Promedio \n");
        printf("3. Ordenar por codigo de estudiante \n");
        printf("4. Mostrar lista de estudiantes \n");
        printf("5. Salir \n");
        printf("elige opcion: ");
        scanf("%d", &opcion); // lee la opcion

        if (opcion == 1) {
            printf("la nota maxima es: %.1f\n", notaMax(0));
        }
        else if (opcion == 2) {
            float promedio = sumaNotas(0)/n;
            printf("el promedio es: %.2f\n", promedio);
        }
        else if (opcion == 3) {
            selectionSort();
            printf("Estudiantes ordenados por codigo:\n");
            for (int i = 0; i < n; i++) {
                printf("Codigo: %d, Nota: %.1f\n", estud[i].codigo, estud[i].nota);
            }// muestra la lista ordenada
        }
        else if (opcion == 4) {
            mostrar();// muestra la lista
        }
        else if (opcion == 5) {
            printf("adios :)  saliendo del programa.\n");
        }
        else {
            printf("Opcion no valida. Intente de nuevo.\n");
        }
    } while (opcion != 5); //  para q no se repita el menu
    return 0; // fin 
}                                     

