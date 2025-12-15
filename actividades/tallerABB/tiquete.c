#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct pasajero {
    int documento;
    int destino;        
    int tipo_pasaje;   
    struct pasajero* izquierdo;
    struct pasajero* derecho;
} Pasajero;

Pasajero* arbol_pasajeros = NULL;

Pasajero* crear_nodo(int documento, int destino, int tipo_pasaje) {
    Pasajero* nuevo = (Pasajero*)malloc(sizeof(Pasajero));
    if (nuevo == NULL) {
        printf("Error al asignar memoria.\n");
        return NULL;
    }
    nuevo->documento = documento;
    nuevo->destino = destino;
    nuevo->tipo_pasaje = tipo_pasaje;
    nuevo->izquierdo = NULL;
    nuevo->derecho = NULL;

    return nuevo;
}

Pasajero* insertar_pasajero(Pasajero* raiz, int documento, int destino, int tipo_pasaje) {
    if (raiz == NULL) {
        return crear_nodo(documento, destino, tipo_pasaje);
    }

    if (documento == raiz->documento) {
        printf("El documento %d ya existe. No se inserta.\n", documento);
        return raiz;
    }

    if (documento < raiz->documento) {
        raiz->izquierdo = insertar_pasajero(raiz->izquierdo, documento, destino, tipo_pasaje);
    } else {
        raiz->derecho = insertar_pasajero(raiz->derecho, documento, destino, tipo_pasaje);
    }

    return raiz;
}


Pasajero* buscar_pasajero(Pasajero* raiz, int documento) {
    if (raiz == NULL || raiz->documento == documento) {
        return raiz;
    }
    if (documento < raiz->documento) {
        return buscar_pasajero(raiz->izquierdo, documento);
    }
    return buscar_pasajero(raiz->derecho, documento);
}


Pasajero* encontrar_minimo(Pasajero* raiz) {
    while (raiz->izquierdo != NULL) {
        raiz = raiz->izquierdo;
    }
    return raiz;
}


Pasajero* eliminar_pasajero(Pasajero* raiz, int documento) {
    if (raiz == NULL) {
        printf("Documento no encontrado.\n");
        return raiz;
    }

    if (documento < raiz->documento) {
        raiz->izquierdo = eliminar_pasajero(raiz->izquierdo, documento);
    } else if (documento > raiz->documento) {
        raiz->derecho = eliminar_pasajero(raiz->derecho, documento);
    } else {

        if (raiz->izquierdo == NULL) {
            Pasajero* temp = raiz->derecho;
            free(raiz);
            return temp;
        }
        if (raiz->derecho == NULL) {
            Pasajero* temp = raiz->izquierdo;
            free(raiz);
            return temp;
        }

        Pasajero* temp = encontrar_minimo(raiz->derecho);
        raiz->documento = temp->documento;
        raiz->destino = temp->destino;
        raiz->tipo_pasaje = temp->tipo_pasaje;
        raiz->derecho = eliminar_pasajero(raiz->derecho, temp->documento);
    }
    return raiz;
}

void mostrar_datos(Pasajero* p) {
    printf("Documento: %d, Destino: ", p->documento);

    switch (p->destino) {
        case 0: printf("Timbiquí"); break;
        case 1: printf("Juanchaco"); break;
        case 2: printf("Tumaco"); break;
        case 3: printf("Guapi"); break;
        default: printf("Desconocido"); break;
    }

    printf(", Pasaje: ");
    if (p->tipo_pasaje == 0)
        printf("Ida\n");
    else
        printf("Ida y Regreso\n");
}

// Recorridos
void recorrido_inorden(Pasajero* raiz) {
    if (raiz != NULL) {
        recorrido_inorden(raiz->izquierdo);
        mostrar_datos(raiz);
        recorrido_inorden(raiz->derecho);
    }
}

void recorrido_preorden(Pasajero* raiz) {
    if (raiz != NULL) {
        mostrar_datos(raiz);
        recorrido_preorden(raiz->izquierdo);
        recorrido_preorden(raiz->derecho);
    }
}

void recorrido_postorden(Pasajero* raiz) {
    if (raiz != NULL) {
        recorrido_postorden(raiz->izquierdo);
        recorrido_postorden(raiz->derecho);
        mostrar_datos(raiz);
    }
}

int contar_pasajeros(Pasajero* raiz) {
    if (raiz == NULL) return 0;
    return 1 + contar_pasajeros(raiz->izquierdo) + contar_pasajeros(raiz->derecho);
}


void registrar_pasajero() {
    int documento, destino, tipo;

    printf("\n--- Registrar Pasajero ---\n");
    printf("Documento: ");
    scanf("%d", &documento);

    if (buscar_pasajero(arbol_pasajeros, documento) != NULL) {
        printf("El documento ya existe.\n");
        return;
    }

    printf("Destino (0-Timbiquí, 1-Juanchaco, 2-Tumaco, 3-Guapi): ");
    scanf("%d", &destino);

    printf("Tipo de pasaje (0-Ida, 1-Ida y Regreso): ");
    scanf("%d", &tipo);

    arbol_pasajeros = insertar_pasajero(arbol_pasajeros, documento, destino, tipo);

    printf("Pasajero registrado.\n");
}

void eliminar_pasajero_menu() {
    int documento;

    printf("\n--- Eliminar Pasajero ---\n");
    printf("Documento: ");
    scanf("%d", &documento);

    arbol_pasajeros = eliminar_pasajero(arbol_pasajeros, documento);
}

void mostrar_pasajeros() {
    int op;
    printf("\n1. Inorden\n2. Preorden\n3. Postorden\nOpción: ");
    scanf("%d", &op);

    if (arbol_pasajeros == NULL) {
        printf("No hay pasajeros registrados.\n");
        return;
    }

    if (op == 1) recorrido_inorden(arbol_pasajeros);
    else if (op == 2) recorrido_preorden(arbol_pasajeros);
    else if (op == 3) recorrido_postorden(arbol_pasajeros);
    else printf("Opción inválida.\n");
}

int main() {
    int op;

    do {
        printf("\n--- Menú Principal ---\n");
        printf("1. Registrar pasajero\n");
        printf("2. Mostrar pasajeros\n");
        printf("3. Contar pasajeros\n");
        printf("4. Eliminar pasajero\n");
        printf("5. Salir\n");
        printf("Opción: ");
        scanf("%d", &op);

        switch (op) {
            case 1: registrar_pasajero(); break;
            case 2: mostrar_pasajeros(); break;
            case 3: printf("Total: %d pasajeros\n", contar_pasajeros(arbol_pasajeros)); break;
            case 4: eliminar_pasajero_menu(); break;
            case 5: printf("Saliendo...\n"); break;
            default: printf("Opción inválida.\n");
        }
    } while (op != 5);

    return 0;
}