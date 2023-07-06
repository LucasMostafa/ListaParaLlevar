#ifndef LISTAS_H_INCLUDED
#define LISTAS_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include "producto.h"

typedef struct _nodoListaProducto
{
    stProducto p;
    struct _nodoListaProducto * siguiente;
} nodoListaProducto;

///INICIAlIZAR ---------------------------------------------------------------------------------------------------
nodoListaProducto * inicLista();

///CREAR ---------------------------------------------------------------------------------------------------------
nodoListaProducto * crearNodoLista(stProducto nuevoProducto);

///MOSTRAR -------------------------------------------------------------------------------------------------------
void mostrarUnNodoLista(nodoListaProducto * nuevo);
void recorrerYMostrarLista(nodoListaProducto * lista);

///DESVINCULAR ---------------------------------------------------------------------------------------------------
nodoListaProducto * desvincularPrimero(nodoListaProducto * * lista);

///BORRAR --------------------------------------------------------------------------------------------------------
nodoListaProducto * borrarNodosSegunParametro(nodoListaProducto * lista, int idProducto);
nodoListaProducto * borrarTodaLaListaProducto(nodoListaProducto * lista);

///BUSCAR --------------------------------------------------------------------------------------------------------
nodoListaProducto * buscarUltimoNodo(nodoListaProducto * lista);

///AGREGAR -------------------------------------------------------------------------------------------------------
nodoListaProducto * agregarNodoAlPrincipio(nodoListaProducto * lista, nodoListaProducto * nuevoNodo);
nodoListaProducto * agregarNodoAlFinal(nodoListaProducto * lista, nodoListaProducto * nuevoNodo);
nodoListaProducto * agregarEnOrdenPorNombreDeProducto(nodoListaProducto * lista, nodoListaProducto * nuevoNodo);
nodoListaProducto * subprogramaAgregarProductoAlPrincipio(nodoListaProducto * lista, stProducto p);
nodoListaProducto * subprogramaAgregarProductoAlFinal(nodoListaProducto * lista, stProducto p);

///CARGAR --------------------------------------------------------------------------------------------------------
nodoListaProducto * cargarListaPrincipio(nodoListaProducto * lista);
nodoListaProducto * cargarListaFinal(nodoListaProducto * lista);
nodoListaProducto * cargarListaOrdenada(nodoListaProducto * lista);

///SUMAR ---------------------------------------------------------------------------------------------------------
float sumarValorProductos(nodoListaProducto * lista);

#endif // LISTAS_H_INCLUDED
