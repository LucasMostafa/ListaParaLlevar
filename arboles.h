#ifndef ARBOLES_H_INCLUDED
#define ARBOLES_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include "producto.h"

typedef struct _nodoArbolstProducto
{
    stProducto p;
    int fe;
    struct _nodoArbolstProducto * izq;
    struct _nodoArbolstProducto * der;
} nodoArbolstProducto;

///INICIAR--------------------------------------------------------------------
nodoArbolstProducto * inicArbol();

///CREAR----------------------------------------------------------------------
nodoArbolstProducto * crearNodoArbol(stProducto producto);

///BUSCAR---------------------------------------------------------------------
nodoArbolstProducto * buscarProductoArbol(nodoArbolstProducto * A, int idProducto);
nodoArbolstProducto * buscarProductoArbolPorNombre(nodoArbolstProducto * A, char nombreProd[]);

///INSERTAR-------------------------------------------------------------------
nodoArbolstProducto * insertarNodoArbol(nodoArbolstProducto * A, nodoArbolstProducto * nuevo);
nodoArbolstProducto * insertarCreandoNodoArbol(nodoArbolstProducto * A, stProducto producto);

///MOSTRAR--------------------------------------------------------------------
void mostrarUnNodoArbol(nodoArbolstProducto * A);
void preOrden (nodoArbolstProducto * A);  /// R I D
void inOrden (nodoArbolstProducto * A);  ///  I R D
void postOrden (nodoArbolstProducto * A);  ///  I D R

void preOrdenProductosActivos (nodoArbolstProducto * A);
void inOrdenProductosActivos (nodoArbolstProducto * A);
void postOrdenProductosActivos (nodoArbolstProducto * A);

void preOrdenProductosInactivos (nodoArbolstProducto * A);
void inOrdenProductosInactivos (nodoArbolstProducto * A);
void postOrdenProductosInactivos (nodoArbolstProducto * A);

///BORRAR---------------------------------------------------------------------
nodoArbolstProducto * borrarNodoArbol (nodoArbolstProducto * A, int idProducto);

///BUSCAR---------------------------------------------------------------------
nodoArbolstProducto * buscarProductoPorNombre(nodoArbolstProducto * A, char nombre[]);
nodoArbolstProducto * nodoMasDerecho(nodoArbolstProducto * A);
nodoArbolstProducto * nodoMasIzquierdo(nodoArbolstProducto * A);

///ARCHIVO--------------------------------------------------------------------
void pasarArbolToArchivo(char archProd[], nodoArbolstProducto * A);
void arbolToArchivo(nodoArbolstProducto * A, FILE * puntero);

///ARMAR ARBOL BINARIO--------------------------------------------------------
int maximo(int a, int b);
int getFE(nodoArbolstProducto *A);
nodoArbolstProducto* rotacionSimpleIzquierda (nodoArbolstProducto* A);
nodoArbolstProducto* rotacionSimpleDerecha (nodoArbolstProducto* A);
nodoArbolstProducto* rotacionDobleIzquierda (nodoArbolstProducto* A);
nodoArbolstProducto* rotacionDobleDerecha (nodoArbolstProducto* A);
nodoArbolstProducto* insertarNodo(nodoArbolstProducto*A, nodoArbolstProducto* nuevo);
nodoArbolstProducto * FormarArbol(nodoArbolstProducto * A, stProducto producto);

///CONTAR---------------------------------------------------------------------
int cantidadDeNodosActivos(nodoArbolstProducto * A);
int cantidadDeNodosEliminados(nodoArbolstProducto * A);

/*
///SUMAR----------------------------------------------------------------------
int sumarArbol(nodoArbol * A);
int sumarArbolValoresPares(nodoArbol * A);
*/


#endif // ARBOLES_H_INCLUDED
