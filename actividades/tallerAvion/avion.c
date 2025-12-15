#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum {
    FEMENINO,
    MASCULINO,
    NO_BINARIO
} Genero;

typedef struct pasajero {
    Genero genero;
    char primerApellido[50];
    struct pasajero *siguiente;
} Pasajero;


Pasajero* lista_venta = NULL;
Pasajero* lista_abordados = NULL;
Pasajero* lista_no_abordados = NULL;
int capacidad_avion = 0;
int tiquetes_vendidos = 0;
int abordaje_iniciado = 0;

void establecer_capacidad() {
    if(capacidad_avion > 0) {
        printf("La capacidad ya fue establecida.\n");
        return;
    }
    printf("Ingrese la capacidad del avión: ");
    scanf("%d", &capacidad_avion);
    printf("Capacidad del avión establecida a %d pasajeros.\n", capacidad_avion);
}

void vender_tiquetes() {
    if (capacidad_avion == 0) {
        printf("Primero debe establecer la capacidad del avion.\n");
        return;
    }

    if (abordaje_iniciado) {
        printf("No se pueden vender pasajes después de que ha comenzado el abordaje.\n");
        return;
    }

    int max_vendidos = capacidad_avion + (capacidad_avion / 10);
    if (tiquetes_vendidos >= max_vendidos) {
        printf("No se pueden vender más tiquetes. Se ha alcanzado el límite de sobreventa.\n");
        return;
    }
    
    Pasajero* nuevo_pasajero = (Pasajero*)malloc(sizeof(Pasajero));
    if (!nuevo_pasajero) {
        printf("Error al asignar memoria para el nuevo pasajero.\n");
        return;
    }

    printf("\n--- Venta de tiquetes ---\n");
    printf("Genero (0-Femenino, 1-Masculino, 2-No binario): ");
    int genero;
    scanf("%d", &genero);

    if (genero < 0 || genero > 2 ){
        printf("Genero invalido. Se asignara Femenino por defecto.\n");
        genero = 0;
    }
    nuevo_pasajero->genero = (Genero)genero;

    printf("Primer apellido: ");
    scanf("%s", nuevo_pasajero->primerApellido);

    nuevo_pasajero->siguiente = NULL;

    if (lista_venta == NULL) {
        lista_venta = nuevo_pasajero;
    } else {
        Pasajero* temp = lista_venta;
        while (temp->siguiente != NULL) {
            temp = temp->siguiente;
        }
        temp->siguiente = nuevo_pasajero;
    }
    tiquetes_vendidos++;
    printf("Tiquete vendido exitosamente. Total vendidos: %d\n", tiquetes_vendidos);
}

void iniciar_abordaje() {
    if (capacidad_avion == 0) {
        printf("Primero debe establecer la capacidad del avion.\n");
        return;
    }

    if (abordaje_iniciado) {
        printf("El abordaje ya ha comenzado.\n");
        return;
    }

    abordaje_iniciado = 1;
    printf("Abordaje iniciado.\n");

    Pasajero* actual = lista_venta;
    int cont_abordados = 0;

    while (actual && cont_abordados < capacidad_avion) {
        Pasajero* nuevo_abordado = (Pasajero*)malloc(sizeof(Pasajero));
        if (!nuevo_abordado) {
            printf("Error al asignar memoria para el pasajero abordado.\n");
            return;
        }
        nuevo_abordado->genero = actual->genero;
        strcpy(nuevo_abordado->primerApellido, actual->primerApellido);
        nuevo_abordado->siguiente = NULL;

        if (!lista_abordados) {
            lista_abordados = nuevo_abordado;
        } else {
            Pasajero* temp = lista_abordados;
            while (temp->siguiente) {
                temp = temp->siguiente;
            }
            temp->siguiente = nuevo_abordado;
        }

        actual = actual->siguiente;
        cont_abordados++;
    }

    while (actual) {
        Pasajero* nuevo_no_abordado = (Pasajero*)malloc(sizeof(Pasajero));
        if (!nuevo_no_abordado) {
            printf("Error al asignar memoria para el pasajero no abordado.\n");
            return;
        }
        nuevo_no_abordado->genero = actual->genero;
        strcpy(nuevo_no_abordado->primerApellido, actual->primerApellido);
        nuevo_no_abordado->siguiente = NULL;

        if (!lista_no_abordados) {
            lista_no_abordados = nuevo_no_abordado;
        } else {
            Pasajero* temp = lista_no_abordados;
            while (temp->siguiente) {
                temp = temp->siguiente;
            }
            temp->siguiente = nuevo_no_abordado;
        }

        actual = actual->siguiente;
    }
    printf("Abordaje completado. Total abordados: %d, Total no abordados: %d\n", 
           cont_abordados, tiquetes_vendidos - cont_abordados);
}

void mostrar_pasajeros(const char* lista_nombre, Pasajero* lista) {
    printf("\n--- %s ---\n", lista_nombre);

    if (lista == NULL) {
        printf("No hay pasajeros en esta lista.\n");
        return;
    }
    Pasajero* actual = lista;
    int contador = 1;

    while (actual){
        const char* genero_str;
        switch (actual->genero) {
            case FEMENINO:
                genero_str = "Femenino";
                break;
            case MASCULINO:
                genero_str = "Masculino";
                break;
            case NO_BINARIO:
                genero_str = "No binario";
                break;
            default:
                genero_str = "Desconocido";
        }
        printf("%d. Apellido: %s, Genero: %s\n", contador, actual->primerApellido, genero_str);
        actual = actual->siguiente;
        contador++;
    }
}

void liberar_listas(Pasajero* lista) {
    Pasajero* actual = lista;
    while (actual) {
        Pasajero* temp = actual;
        actual = actual->siguiente;
        free(temp);
    }
}

int main() {
    int opcion;

    printf("Sistema de tiquetes de avion\n");

    do {
        printf("\n--- Menu principal de Tiquetes de Avion ---\n");
        printf("1. Establecer capacidad del avion\n");
        printf("2. Vender tiquetes\n");
        printf("3. Iniciar abordaje\n");
        printf("4. Ver pasajeros abordados\n");
        printf("5. Ver pasajeros no abordados\n");
        printf("6. Salir\n");
        printf("Seleccione una opcion: ");
        scanf("%d", &opcion);

        switch (opcion) {
            case 1:
                establecer_capacidad();
                break;
            case 2:
                vender_tiquetes();
                break;
            case 3:
                iniciar_abordaje();
                break;
            case 4:
                if (!abordaje_iniciado) {
                    printf("El abordaje no ha iniciado todavia.\n");
                } else {
                    mostrar_pasajeros("Pasajeros Abordados", lista_abordados);
                }
                break;
            case 5:
                if (!abordaje_iniciado) {
                    printf("El abordaje no ha iniciado todavia.\n");
                } else {
                    mostrar_pasajeros("Pasajeros No Abordados", lista_no_abordados);
                }
                break;
            case 6:
                printf("Saliendo del programa.\n");
                break;
            default:
                printf("Opcion invalida. Intente nuevamente.\n");
        }
    } while (opcion != 6);

    liberar_listas(lista_venta);
    liberar_listas(lista_abordados);
    liberar_listas(lista_no_abordados);

    return 0;
}