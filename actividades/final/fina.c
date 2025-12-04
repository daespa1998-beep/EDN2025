#include <Stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct pedido{
    char destino[50];
    int cantidad;
    struct pedido* siguiente;
}pedido;

typedef struct lote{
    int fecha_venc;
    int stock_total;
    char producto[50];
    pedido* pedidos;

    int altura;
    struct lote* izq;
    struct lote* der;
}lote;

lote* inventario = NULL;

int max(int a, int b){
    return (a > b) ? a : b;
}

int altura(lote* n){
    return n ? n->altura : 0;
}

int balance(lote* n){
    return n ? altura(n->izq) - altura(n->der) : 0;
}

lote* rotar_der(lote* y){
    lote* x = y->izq;
    lote* T2 = x->der;

    x->der = y;
    y->izq = T2;

    y->altura = max(altura(y->izq), altura(y->der)) + 1;    
    x->altura = max(altura(x->izq), altura(x->der)) + 1;

    return x;
}

lote* rotar_izq(lote* x){
    lote* y = x->der;
    lote* T2 = y->izq;

    y->izq = x;
    x->der = T2;

    x->altura = max(altura(x->izq), altura(x->der)) + 1;    
    y->altura = max(altura(y->izq), altura(y->der)) + 1;

    return y;
}

lote* crear_lote(int fecha, int stock, const char* producto){
    lote* nuevo = (lote*)malloc(sizeof(lote));
    if(!nuevo){
        printf("Error al asignar memoria.\n");
        return NULL;
    }
    nuevo->fecha_venc = fecha;
    nuevo->stock_total = stock;
    strcpy(nuevo->producto, producto, [sizeof(nuevo->producto)-1]"\0");
    nuevo->pedidos = NULL;
    nuevo->altura = 1;
    nuevo->izq = nuevo->der = NULL;
    return nuevo;
}

lote* insertar_lote(lote* raiz, int fecha, int stock, const char* producto){
    if (raiz == NULL){
        return crear_lote(fecha, stock, producto);
    }
    if (fecha < raiz->fecha_venc){
        raiz->izq = insertar_lote(raiz->izq, fecha, stock, producto);
    } else if (fecha > raiz->fecha_venc){
        raiz->der = insertar_lote(raiz->der, fecha, stock, producto);
    } else {
        printf("El lote con fecha %d ya existe. No se inserta.\n", fecha);
        return raiz;
    }
    raiz->altura = 1 + max(altura(raiz->izq), altura(raiz->der));
    int bal = balance(raiz);
    if (bal > 1 && fecha < raiz->izq->fecha_venc){
        return rotar_der(raiz);
    }
    if (bal < -1 && fecha > raiz->der->fecha_venc){
        return rotar_izq(raiz);
    }
    if (bal > 1 && fecha > raiz->izq->fecha_venc){
        raiz->izq = rotar_izq(raiz->izq);
        return rotar_der(raiz);
    }
    if (bal < -1 && fecha < raiz->der->fecha_venc){
        raiz->der = rotar_der(raiz->der);
        return rotar_izq(raiz);
    }
    return raiz;

}
lote* buscar_lote(lote* raiz, int fecha){
    if (raiz == NULL || raiz->fecha_venc == fecha){
        return raiz;
    }
    if (fecha < raiz->fecha_venc){
        return buscar_lote(raiz->izq, fecha);
    }
    return buscar_lote(raiz->der, fecha);
}

int contar_pedidos(pedido* cabeza){
    int contador = 0;
    while (cabeza){
        contador++;
        cabeza = cabeza->siguiente;
    }
    return contador;    
}

void liberar_cola(pedido* cabeza){
    pedido* temp;
    while (cabeza){
        temp = cabeza;
        cabeza = cabeza->siguiente;
        free(temp);
    }
}

void encolar_pedido(lote* l, const char* destino, int cantidad){
    if (!l)return;
    pedido* nuevo = (pedido*)malloc(sizeof(pedido));
    if (!nuevo){
        printf("Error al asignar memoria para el pedido.\n");
        return;
    }
    strncpy(nuevo->destino, destino, sizeof(nuevo->destino)-1);
    nuevo->destino[sizeof(nuevo->destino)-1] = '\0';
    nuevo->cantidad = cantidad;
    nuevo->siguiente = NULL;

    if (l->pedidos == NULL){
        l->pedidos = nuevo;
    } else {
        pedido* temp = l->pedidos;
        while (temp->siguiente){
            temp = temp->siguiente;
        }
        temp->siguiente = nuevo;
    }
    l->stock_total -= cantidad;
}

