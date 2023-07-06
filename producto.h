#ifndef PRODUCTO_H_INCLUDED
#define PRODUCTO_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <strings.h>

typedef struct
{
    int idProducto;
    char nombre[30];
    char marca[20];
    float precio;
    int eliminado; // indica 1 o 0 si el producto fue eliminado
} stProducto;

///MOSTRAR -------------------------------------------------------------------
void mostrarProducto(stProducto producto);
void mostrarProductoAdmin(stProducto producto);


#endif // PRODUCTO_H_INCLUDED
