#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct pedido {
    char destino[50];
    int cantidad_solicitada;
    struct pedido* siguiente;
} Pedido;

typedef struct lote {
    int fecha_vencimiento;
    int stock_total;
    char producto[50];
    Pedido* cabeza_pedidos;

    int altura;    
    struct lote* izq;
    struct lote* der;
} Lote;

Lote* inventario = NULL;

int max(int a, int b) {
    return (a > b) ? a : b; }
int altura(Lote* n) {
    return n ? n->altura : 0; }
int balance(Lote* n) {
    return n ? altura(n->izq) - altura(n->der) : 0; }

Lote* rotacion_derecha(Lote* y) {
    Lote* x = y->izq;
    Lote* T2 = x->der;

    x->der = y;
    y->izq = T2;

    y->altura = max(altura(y->izq), altura(y->der)) + 1;
    x->altura = max(altura(x->izq), altura(x->der)) + 1;

    return x;
}

Lote* rotacion_izquierda(Lote* x) {
    Lote* y = x->der;
    Lote* T2 = y->izq;

    y->izq = x;
    x->der = T2;

    x->altura = max(altura(x->izq), altura(x->der)) + 1;
    y->altura = max(altura(y->izq), altura(y->der)) + 1;

    return y;
}

Lote* crear_lote(int fecha, int stock, const char* producto) {
    Lote* n = (Lote*)malloc(sizeof(Lote));
    if (!n) {
        printf("Error al asignar memoria\n");
        return NULL;
    }
    n->fecha_vencimiento = fecha;
    n->stock_total = stock;
    strncpy(n->producto, producto, sizeof(n->producto)-1);
    n->producto[sizeof(n->producto)-1] = '\0';
    n->cabeza_pedidos = NULL;
    n->altura = 1;
    n->izq = n->der = NULL;
    return n;
}

Lote* insertar_lote(Lote* raiz, int fecha, int stock, const char* producto) {
    if (raiz == NULL) {
        return crear_lote(fecha, stock, producto);
    }

    if (fecha < raiz->fecha_vencimiento){
        raiz->izq = insertar_lote(raiz->izq, fecha, stock, producto);
    }
    else if (fecha > raiz->fecha_vencimiento){
        raiz->der = insertar_lote(raiz->der, fecha, stock, producto);
    }
    else {
        printf("La fecha %d ya existe. No se inserta.\n", fecha);
        return raiz;
    }

    raiz->altura = 1 + max(altura(raiz->izq), altura(raiz->der));

    int fb = balance(raiz);

    if (fb > 1 && fecha < raiz->izq->fecha_vencimiento){
        return rotacion_derecha(raiz);
    }

    if (fb < -1 && fecha > raiz->der->fecha_vencimiento){
        return rotacion_izquierda(raiz);
    }

    if (fb > 1 && fecha > raiz->izq->fecha_vencimiento) {
        raiz->izq = rotacion_izquierda(raiz->izq);
        return rotacion_derecha(raiz);
    }

    if (fb < -1 && fecha < raiz->der->fecha_vencimiento) {
        raiz->der = rotacion_derecha(raiz->der);
        return rotacion_izquierda(raiz);
    }

    return raiz;
}

Lote* encontrar_minimo(Lote* raiz) {
    Lote* actual = raiz;
    while (actual && actual->izq != NULL)
        actual = actual->izq;
    return actual;
}

Lote* buscar_lote(Lote* raiz, int fecha) {
    if (raiz == NULL || raiz->fecha_vencimiento == fecha) return raiz;
    if (fecha < raiz->fecha_vencimiento) return buscar_lote(raiz->izq, fecha);
    return buscar_lote(raiz->der, fecha);
}

int contar_pedidos(Pedido* cabeza) {
    int c = 0;
    while (cabeza) { c++; cabeza = cabeza->siguiente; }
    return c;
}

void liberar_cola(Pedido* cabeza) {
    Pedido* tmp;
    while (cabeza) {
        tmp = cabeza;
        cabeza = cabeza->siguiente;
        free(tmp);
    }
}

void encolar_pedido(Lote* lote, const char* destino, int cantidad) {
    if (!lote) return;
    Pedido* nuevo = (Pedido*)malloc(sizeof(Pedido));
    if (!nuevo) { 
        printf("Error pedido\n"); return; 
    }

    strncpy(nuevo->destino, destino, sizeof(nuevo->destino)-1);
    nuevo->destino[sizeof(nuevo->destino)-1] = '\0';
    nuevo->cantidad_solicitada = cantidad;
    nuevo->siguiente = NULL;

    if (lote->cabeza_pedidos == NULL) {
        lote->cabeza_pedidos = nuevo;
    } 
    
    else {
        Pedido* p = lote->cabeza_pedidos;
        while (p->siguiente) p = p->siguiente;
        p->siguiente = nuevo;
    }
    lote->stock_total -= cantidad;
}

int cancelar_pedido_en_lote(Lote* lote, const char* destino, int cantidad) {
    if (!lote || !lote->cabeza_pedidos) 
    return 0;
   
    Pedido* prev = NULL;
    Pedido* cur = lote->cabeza_pedidos;
    while (cur) {
        if (strcmp(cur->destino, destino) == 0 && cur->cantidad_solicitada == cantidad) {
            if (prev == NULL) lote->cabeza_pedidos = cur->siguiente;
            else prev->siguiente = cur->siguiente;
            lote->stock_total += cur->cantidad_solicitada;
            free(cur);
            return 1; 
        }
        prev = cur;
        cur = cur->siguiente;
    }
    return 0; 
}

Lote* eliminar_lote(Lote* raiz, int fecha) {
    if (raiz == NULL) {
        printf("Fecha %d no encontrada.\n", fecha);
        return raiz;
    }

    if (fecha < raiz->fecha_vencimiento) {
        raiz->izq = eliminar_lote(raiz->izq, fecha);
    } 
    
    else if (fecha > raiz->fecha_vencimiento) {
        raiz->der = eliminar_lote(raiz->der, fecha);
    } 
    
    else {
        liberar_cola(raiz->cabeza_pedidos);
        raiz->cabeza_pedidos = NULL;

        if (raiz->izq == NULL || raiz->der == NULL) {
            Lote* temp = raiz->izq ? raiz->izq : raiz->der;
            if (temp == NULL) {
                temp = raiz;
                raiz = NULL;
            } 
            
            else {
                *raiz = *temp;
            }
            free(temp);
        } 
        
        else {
            Lote* temp = encontrar_minimo(raiz->der);
            raiz->fecha_vencimiento = temp->fecha_vencimiento;
            raiz->stock_total = temp->stock_total;
            strncpy(raiz->producto, temp->producto, sizeof(raiz->producto)-1);
            raiz->producto[sizeof(raiz->producto)-1] = '\0';
            liberar_cola(raiz->cabeza_pedidos); 
            raiz->cabeza_pedidos = temp->cabeza_pedidos;
            temp->cabeza_pedidos = NULL;
            raiz->der = eliminar_lote(raiz->der, temp->fecha_vencimiento);
        }
    }

    if (raiz == NULL) return raiz;

    raiz->altura = 1 + max(altura(raiz->izq), altura(raiz->der));

    int fb = balance(raiz);

    if (fb > 1 && balance(raiz->izq) >= 0){
        return rotacion_derecha(raiz);
    }

    if (fb > 1 && balance(raiz->izq) < 0) {
        raiz->izq = rotacion_izquierda(raiz->izq);
        return rotacion_derecha(raiz);
    }

    if (fb < -1 && balance(raiz->der) <= 0){
        return rotacion_izquierda(raiz);
    }

    if (fb < -1 && balance(raiz->der) > 0) {
        raiz->der = rotacion_derecha(raiz->der);
        return rotacion_izquierda(raiz);
    }

    return raiz;
}

void reporte_inorden(Lote* raiz) {
    if (!raiz) return;
    reporte_inorden(raiz->izq);
    printf("Fecha: %d | Producto: %s | Stock: %d | Pedidos: %d\n",
           raiz->fecha_vencimiento, raiz->producto, raiz->stock_total, contar_pedidos(raiz->cabeza_pedidos));
    reporte_inorden(raiz->der);
}

Lote* fecha_mas_cercana(Lote* raiz) {
    return encontrar_minimo(raiz);
}

void liberar_arbol(Lote* raiz) {
    if (!raiz) return;
    liberar_arbol(raiz->izq);
    liberar_arbol(raiz->der);
    liberar_cola(raiz->cabeza_pedidos);
    free(raiz);
}

void recepcion_mercancia() {
    int fecha, cantidad;
    char producto[50];

    printf("\n--- Recepcion de Mercancia ---\n");
    printf("Fecha de vencimiento (AAAAMMDD): ");
    if (scanf("%d", &fecha) != 1) { 
        printf("Entrada invalida.\n"); while(getchar()!='\n'); 
        return; 
    }

    printf("Cantidad (unidades): ");
    if (scanf("%d", &cantidad) != 1) { 
        printf("Entrada invalida.\n"); while(getchar()!='\n'); 
        return; 
    }

    printf("Nombre producto (sin espacios): ");
    scanf("%39s", producto);

    if (buscar_lote(inventario, fecha) != NULL) {
        printf("No se puede procesar: ya existe lote con fecha %d\n", fecha);
        return;
    }

    inventario = insertar_lote(inventario, fecha, cantidad, producto);
    printf("Lote registrado.\n");
}

void registrar_pedido_menu() {
    if (inventario == NULL) {
        printf("No hay lotes registrados.\n");
        return;
    }

    Lote* lote = fecha_mas_cercana(inventario);
    if (!lote) { 
        printf("No hay lotes validos.\n"); 
        return; 
    }

    char destino[50];
    int cantidad;

    printf("\n--- Registrar Pedido (se usara lote que vence mas pronto: %d - %s) ---\n", lote->fecha_vencimiento, lote->producto);
    printf("Destino (sin espacios): ");
    scanf("%39s", destino);
    printf("Cantidad solicitada: ");
    if (scanf("%d", &cantidad) != 1) { 
        printf("Entrada invalida.\n"); while(getchar()!='\n'); 
        return; 
    }

    if (cantidad <= 0) { 
        printf("Cantidad invalida.\n"); 
        return; 
    }

    if (cantidad > lote->stock_total) { 
        printf("Stock insuficiente. Stock disponible: %d\n", lote->stock_total); 
        return; 
    }

    encolar_pedido(lote, destino, cantidad);
    printf("Pedido encolado en lote %d. Stock restante: %d\n", lote->fecha_vencimiento, lote->stock_total);
}

void cancelacion_lote_menu() {
    int fecha;
    printf("\n--- Cancelar lote (por daño/pudricion) ---\n");
    printf("Fecha (AAAAMMDD): ");
    if (scanf("%d", &fecha) != 1) { 
        printf("Entrada invalida.\n"); while(getchar()!='\n'); 
        return; 
    }

    inventario = eliminar_lote(inventario, fecha);
    printf("Si existia, el lote fue eliminado.\n");
}

void cancelacion_pedido_menu() {
    int fecha, cantidad;
    char destino[50];

    printf("\n--- Cancelar Pedido ---\n");
    printf("Fecha del lote donde esta el pedido (AAAAMMDD): ");
    if (scanf("%d", &fecha) != 1) { 
        printf("Entrada invalida.\n"); 
        while(getchar()!='\n'); 
        return; 
    }

    Lote* lote = buscar_lote(inventario, fecha);
    if (!lote) { 
        printf("Lote no encontrado.\n"); 
        return; 
    }

    printf("Destino del pedido: ");
    scanf("%39s", destino);
    printf("Cantidad exacta del pedido a cancelar: ");
    if (scanf("%d", &cantidad) != 1) { 
        printf("Entrada invalida.\n"); 
        while(getchar()!='\n'); 
        return; 
    }

    int ok = cancelar_pedido_en_lote(lote, destino, cantidad);
    if (ok) printf("Pedido cancelado. Stock restaurado a %d.\n", lote->stock_total);
    else printf("Pedido no encontrado con esos datos.\n");
}

void reporte_estado_menu() {
    printf("\n--- Reporte de Estado  ---\n");
    if (inventario == NULL) {
        printf("Inventario vacío.\n");
        return;
    }
    reporte_inorden(inventario);
}

int main() {
    int op;
    do {
        printf("\n--- Menú Principal ---\n");
        printf("1. Recepcion de Mercancia\n");
        printf("2. Registrar Pedido de Despacho\n");
        printf("3. Cancelacion\n");
        printf("4. Reporte de Estado \n");
        printf("5. Salir\n");
        printf("Opcion: ");
        if (scanf("%d", &op) != 1) { 
            printf("Entrada invalida.\n"); 
            while(getchar()!='\n'); 
            op = 0; 
            continue; 
        }

        switch(op) {
            case 1: recepcion_mercancia(); break;
            case 2: registrar_pedido_menu(); break;
            case 3: {
                int sub;
                printf("1. Eliminar lote completo\n  2. Cancelar pedido específico\n  Opcion: ");
                if (scanf("%d", &sub) != 1) { 
                    printf("Entrada invalida.\n"); 
                    while(getchar()!='\n'); 
                    break; 
                }

                if (sub == 1) {
                    cancelacion_lote_menu();
                }
                
                else if (sub == 2) {
                    cancelacion_pedido_menu();
                }
                
                else {
                    printf("Opcion invalida.\n");
                }
                
                break;
            }
            case 4: reporte_estado_menu(); break;
            case 5:
                printf("Saliendo... liberando memoria.\n");
                liberar_arbol(inventario);
                inventario = NULL;
                break;
            default: printf("Opcion invalida.\n");
        }
    } while(op != 5);

    return 0;
}