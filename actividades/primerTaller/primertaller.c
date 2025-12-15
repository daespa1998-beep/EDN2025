#include <stdio.h>

#define N 10
int ingresarNumero(int vector [N]);
int mostrarNumero(int vector [N]);
void ordenarAcendente(int arr[N], int n);
void ordenarDesendente(int arr[N], int n);

int main() {
    int arreglo[N];
    ingresarNumero(arreglo);

    printf("\nArreglo original:\n");
    mostrarNumero(arreglo);

    printf("\n---Asendente  Selection sort---\n");
    ordenarAcendente(arreglo, N);

    printf("\n---Desendente Insertion sort---\n");
    ordenarDesendente(arreglo, N);

    return 0;

}

int ingresarNumero(int vector [N]){
    for ( int i=0; i<N; i++){
        do{
            printf("digite un numero positivo, posicion %d:",i+1);
            scanf("%d ",& vector [i]);
            if(vector[i] <=0){
                printf("Error: debe ser un numero positivo");
            }
        }while(vector[i]<=0);
    }return 0;
}

int mostrarNumero(int vector [N]){
    for(int i=0; i<N; i++ ){
        printf("%d"" ", vector[i]);
    }
    printf("\n"" ");
    return 0;
}
 
void ordenarAcendente(int arr[N], int n){
    int i, j, min, temp, paso=1;
    for(i=0; i<n-1; i++){
        min = i;
        for(j=i+1; j<n; j++){
            if (arr[j] < arr[min]){
                min = j;
            }    
        }

        temp = arr[i];
        arr[i] = arr[min];
        arr[min] = temp;

        printf("Paso %d :"" ", paso++);
        mostrarNumero(arr);
    }
}

void ordenarDesendente(int arr[N], int n) {
    int i, j, key, paso=1;
    for(i=1; i<n; i++){
        key = arr[i];
        j = i - 1;

        while (j>=0  && arr[j] < key){
            arr[j+1] = arr[j];
            j--;
        }
        arr[j+1] = key;

        printf("paso %d :"" ", paso++);
        mostrarNumero(arr);
    }
}

//"prueba de guardado ya termidado2"//