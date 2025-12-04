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
    
}