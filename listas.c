#include "listas.h"

///INICIALIZAR ------------------------------------------------------------------------------------------------
nodoListaProducto * inicLista()
{
    return NULL;
}

///CREAR NODO -------------------------------------------------------------------------------------------------
nodoListaProducto * crearNodoLista(stProducto nuevoProducto)
{
    nodoListaProducto * aux;

    aux = (nodoListaProducto*)malloc(sizeof(nodoListaProducto));

    aux->p = nuevoProducto;
    aux->siguiente = NULL;

    return aux;
}

///MOSTRAR ----------------------------------------------------------------------------------------------------
void mostrarUnNodoLista(nodoListaProducto * nuevo)
{
    mostrarProducto(nuevo->p);
}

void recorrerYMostrarLista(nodoListaProducto * lista)
{
    nodoListaProducto * seg= lista;

    while(seg!=NULL)
    {
        mostrarUnNodoLista(seg);
        seg=seg->siguiente;
    }
}

///DESVINCULAR ---------------------------------------------------------------------------------------------------
nodoListaProducto * desvincularPrimero(nodoListaProducto * * lista)
{
    nodoListaProducto * primero=NULL;

    if(*lista!=NULL)
    {
        primero=*lista;

        *lista=(*lista)->siguiente;

        primero->siguiente=NULL;
    }

    return primero;
}

///BORRAR --------------------------------------------------------------------------------------------------------

nodoListaProducto * borrarNodosSegunParametro(nodoListaProducto * lista, int idProducto)
{
    nodoListaProducto * aux, * seg, * ante;
    if(lista)
    {
        while (lista!=NULL && lista->p.idProducto<idProducto)
        {
            aux=lista;
            lista=lista->siguiente;
            free(aux);
        }

        ante=lista;
        seg=lista->siguiente;

        while(seg!=NULL)
        {
            if(seg->p.idProducto<idProducto)
            {
                aux=seg;
                ante->siguiente=seg->siguiente;
                seg=seg->siguiente;
                free(aux);
            }
            else
            {
                ante=seg;
                seg=seg->siguiente;
            }
        }
    }
    return lista;
}

nodoListaProducto * borrarTodaLaListaProducto(nodoListaProducto * lista)
{
    nodoListaProducto * seg;
    nodoListaProducto * proximo;

    seg= lista;

    while(seg!=NULL)
    {
        proximo=seg->siguiente;
        free(seg);
        seg=proximo;
    }
    return seg;
}

///BUSCAR -----------------------------------------------------------------------------------------------------------
nodoListaProducto * buscarUltimoNodo(nodoListaProducto * lista) //Necesaria para agregar nodo al final
{
    nodoListaProducto * seg;
    seg = lista;

    if(seg!=NULL)
    {
        while(seg->siguiente!=NULL)
        {
            seg=seg->siguiente;
        }
    }
    return seg;
}

///AGREGAR ----------------------------------------------------------------------------------------------------------
nodoListaProducto * agregarNodoAlPrincipio(nodoListaProducto * lista, nodoListaProducto * nuevoNodo)
{
    if(lista==NULL)
    {
        lista= nuevoNodo;
    }
    else
    {
        nuevoNodo->siguiente=lista;
        lista= nuevoNodo;
    }
    return lista;
}


nodoListaProducto * agregarNodoAlFinal(nodoListaProducto * lista, nodoListaProducto * nuevoNodo)
{
    if(lista==NULL)
    {
        lista= nuevoNodo;
    }
    else
    {
        nodoListaProducto * ultimo= buscarUltimoNodo(lista);
        ultimo->siguiente= nuevoNodo;
    }
    return lista;
}

//Agrego nodo en orden a traves de un char (nombre)
nodoListaProducto * agregarEnOrdenPorNombreDeProducto(nodoListaProducto * lista, nodoListaProducto * nuevoNodo)
{
    if(lista==NULL)
    {
        lista= nuevoNodo;
    }
    else
    {
        if(strcmp(nuevoNodo->p.nombre, lista->p.nombre)<0)
        {
            lista= agregarNodoAlPrincipio(lista, nuevoNodo);
        }
        else
        {
            nodoListaProducto * ante;
            nodoListaProducto *seg;

            ante=lista;
            seg=lista->siguiente;
            while(seg!=NULL && strcmp(nuevoNodo->p.nombre, seg->p.nombre)>0)
            {
                ante=seg;
                seg=seg->siguiente;
            }
            nuevoNodo->siguiente= seg;
            ante->siguiente=nuevoNodo;
        }
    }
    return lista;
}

nodoListaProducto * subprogramaAgregarProductoAlPrincipio(nodoListaProducto * lista, stProducto p)
{
    lista= agregarNodoAlPrincipio(lista, crearNodoLista(p));

    return lista;
}
nodoListaProducto * subprogramaAgregarProductoAlFinal(nodoListaProducto * lista, stProducto p)
{
    lista= agregarNodoAlFinal(lista, crearNodoLista(p));

    return lista;
}

///SUMAR ---------------------------------------------------------------------------------------
float sumarValorProductos(nodoListaProducto * lista)
{
    float suma=0;
    nodoListaProducto * seg;

    seg= lista;

    while(seg!=NULL)
    {
        suma= suma + seg->p.precio;
        seg=seg->siguiente;
    }
    return suma;
}
