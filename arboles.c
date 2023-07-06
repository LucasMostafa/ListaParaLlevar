#include "arboles.h"

///INICIAR ARBOL-------------------------------------------------------------------
nodoArbolstProducto * inicArbol()
{
    return NULL;
}

///CREAR---------------------------------------------------------------------------
nodoArbolstProducto * crearNodoArbol (stProducto producto)
{
    nodoArbolstProducto* nuevo = (nodoArbolstProducto*) malloc(sizeof(nodoArbolstProducto));

    nuevo->p= producto;
    nuevo->fe=0;
    nuevo->izq = NULL;
    nuevo->der = NULL;

    return nuevo;
}

///BUSCAR--------------------------------------------------------------------------
nodoArbolstProducto * buscarProductoArbol(nodoArbolstProducto * A, int idProducto)
{
    nodoArbolstProducto * rta= NULL;

    if(A)
    {
        if(A->p.idProducto == idProducto)
            rta= A;
        else
        {
            if(A->p.idProducto > idProducto)
                rta= buscarProductoArbol(A->izq, idProducto);
            else
                rta= buscarProductoArbol(A->der, idProducto);
        }
    }
    return rta;
}

nodoArbolstProducto * buscarProductoArbolPorNombre(nodoArbolstProducto * A, char nombreProd[])
{
    nodoArbolstProducto * rta= NULL;

    if(A)
    {
        if(strcmp(A->p.nombre, nombreProd)==0)
            rta= A;
        else
        {
            if(A->p.nombre > nombreProd)
                rta= buscarProductoArbol(A->izq, nombreProd);
            else
                rta= buscarProductoArbol(A->der, nombreProd);
        }
    }
    return rta;
}

///INSERTAR---------------------------------------------------------------------
nodoArbolstProducto * insertarNodoArbol(nodoArbolstProducto * A, nodoArbolstProducto * nuevo)
{
    if(A==NULL)
        A= nuevo;

    else
    {
        if(nuevo->p.idProducto < A->p.idProducto)
            A->izq= insertarNodoArbol(A->izq, nuevo);
        else if(nuevo->p.idProducto > A->p.idProducto)
            A->der= insertarNodoArbol(A->der, nuevo);
    }
    return A;
}

nodoArbolstProducto * insertarCreandoNodoArbol(nodoArbolstProducto * A, stProducto producto)
{
    if(A==NULL)
        A= crearNodoArbol(producto);

    else
    {
        if(producto.idProducto < A->p.idProducto)
            A->izq= insertarCreandoNodoArbol(A->izq, producto);
        else if(producto.idProducto > A->p.idProducto)
            A->der= insertarCreandoNodoArbol(A->der, producto);
    }
    return A;
}

///MOSTRAR----------------------------------------------------------------------
void mostrarUnNodoArbol(nodoArbolstProducto * A)
{
    mostrarProducto(A->p);
}

void preOrden (nodoArbolstProducto * A)  /// R I D
{
    if(A)
    {
        mostrarUnNodoArbol(A);
        preOrden(A->izq);
        preOrden(A->der);
    }
}

void inOrden (nodoArbolstProducto * A)  ///  I R D
{
    if(A)
    {
        inOrden(A->izq);
        mostrarUnNodoArbol(A);
        inOrden(A->der);
    }
}

void postOrden (nodoArbolstProducto * A)  ///  I D R
{
    if(A)
    {
        postOrden(A->izq);
        postOrden(A->der);
        mostrarUnNodoArbol(A);
    }
}

void preOrdenProductosActivos (nodoArbolstProducto * A)
{
    if(A)
    {
        if(A->p.eliminado==0)
        {
            mostrarProducto(A->p);
        }
        preOrdenProductosActivos(A->izq);
        preOrdenProductosActivos(A->der);
    }
}

void inOrdenProductosActivos (nodoArbolstProducto * A)
{
    if(A)
    {
        inOrdenProductosActivos(A->izq);
        if(A->p.eliminado==0)
        {
            mostrarUnNodoArbol(A);
        }
        inOrdenProductosActivos(A->der);
    }
}

void postOrdenProductosActivos (nodoArbolstProducto * A)
{
    if(A)
    {
        postOrdenProductosActivos(A->izq);
        postOrdenProductosActivos(A->der);
        if(A->p.eliminado==0)
        {
            mostrarUnNodoArbol(A);
        }
    }
}

void preOrdenProductosInactivos (nodoArbolstProducto * A)
{
    if(A)
    {
        if(A->p.eliminado==1)
        {
            mostrarUnNodoArbol(A);
        }
        preOrdenProductosInactivos(A->izq);
        preOrdenProductosInactivos(A->der);
    }
}

void inOrdenProductosInactivos (nodoArbolstProducto * A)
{
    if(A)
    {
        inOrdenProductosInactivos(A->izq);
        if(A->p.eliminado==1)
        {
            mostrarUnNodoArbol(A);
        }
        inOrdenProductosInactivos(A->der);
    }
}

void postOrdenProductosInactivos (nodoArbolstProducto * A)
{
    if(A)
    {
        postOrdenProductosInactivos(A->izq);
        postOrdenProductosInactivos(A->der);
        if(A->p.eliminado==1)
        {
            mostrarUnNodoArbol(A);
        }
    }
}

///BORRAR--------------------------------------------------------------------------
nodoArbolstProducto * borrarNodoArbol (nodoArbolstProducto * A, int idProducto)
{
    if(A)
    {
        if(idProducto == A->p.idProducto)
        {
            if(A->izq!=NULL)
            {
                nodoArbolstProducto * masDerecho= nodoMasDerecho(A->izq);
                A->p= masDerecho->p;
                A->izq= borrarNodoArbol(A->izq, masDerecho->p.idProducto);
            }
            else if(A->der!=NULL)
            {
                nodoArbolstProducto * masIzquierdo = nodoMasIzquierdo(A->der);
                A->p=  masIzquierdo->p;
                A->der= borrarNodoArbol(A->der, masIzquierdo->p.idProducto);
            }
            else
            {
                free(A);
                A= NULL;
            }
        }
        else if(idProducto < A->p.idProducto)
        {
            A->izq= borrarNodoArbol(A->izq, idProducto);
        }
        else
        {
            A->der= borrarNodoArbol(A->der, idProducto);
        }
    }
    return A;
}

///BUSCAR---------------------------------------------------------------------------
nodoArbolstProducto * buscarProductoPorNombre(nodoArbolstProducto * A, char nombre[])
{
    nodoArbolstProducto * buscado= NULL;

    if(A)
    {
        if(strcmp(A->p.nombre, nombre)==0)
            buscado= A;
        else
        {
            buscado= buscarProductoPorNombre(A->izq, nombre);
            if(buscado==NULL)
                buscado= buscarProductoPorNombre(A->der, nombre);
        }
    }
    return buscado;
}

nodoArbolstProducto * nodoMasDerecho(nodoArbolstProducto * A)
{
    nodoArbolstProducto * masDerecho= NULL;

    if(A)
    {
        if(A->der!=NULL)
            masDerecho= nodoMasDerecho(A->der);
        else
            masDerecho= A;
    }
    return masDerecho;
}

nodoArbolstProducto * nodoMasIzquierdo(nodoArbolstProducto * A)
{
    nodoArbolstProducto * masIzquierdo= NULL;

    if(A)
    {
        if(A->izq!=NULL)
            masIzquierdo= nodoMasIzquierdo(A->izq);
        else
            masIzquierdo= A;
    }
    return masIzquierdo;
}

///ARCHIVO ------------------------------------------------------------------------------------------
void pasarArbolToArchivo(char archProd[], nodoArbolstProducto * A)
{
    FILE * puntero;
    puntero= fopen(archProd, "w+b");

    if(puntero)
    {
        if(A)
        {
            arbolToArchivo(A, puntero);
        }
    }
    else
    {
        printf("\nNo se pudo abrir el archivo.\n");
    }
    fclose(puntero);
}

void arbolToArchivo(nodoArbolstProducto * A, FILE * puntero)
{
    stProducto producto;

    if(A)
    {
        arbolToArchivo(A->izq, puntero);
        producto= A->p;
        fwrite(&producto, sizeof(stProducto), 1, puntero);
        arbolToArchivo(A->der, puntero);
    }
}

///ARMAR ARBOL BINARIO -----------------------------------------------------------------------------------
int maximo(int a, int b)
{
    if(a>=b)
        return a;
    else
        return b;
}

int getFE(nodoArbolstProducto *A)
{
    if(A==NULL)
        return -1;
    else
        return A->fe;
}

nodoArbolstProducto* rotacionSimpleIzquierda (nodoArbolstProducto* A)
{
    nodoArbolstProducto * aux=A->izq;
    A->izq=aux->der;
    aux->der=A;
    A->fe=maximo(getFE(A->der),getFE(A->izq))+1;
    aux->fe=maximo(getFE(aux->der),getFE(aux->izq))+1;
    return aux;
}

nodoArbolstProducto* rotacionSimpleDerecha (nodoArbolstProducto* A)
{
    nodoArbolstProducto * aux=A->der;
    A->der=aux->izq;
    aux->izq=A;
    A->fe=maximo(getFE(A->der),getFE(A->izq))+1;
    aux->fe=maximo(getFE(aux->der),getFE(aux->izq))+1;
    return aux;
}

nodoArbolstProducto* rotacionDobleIzquierda (nodoArbolstProducto* A)
{
    nodoArbolstProducto * temporal;
    A->izq=rotacionSimpleDerecha(A->izq);
    temporal=rotacionSimpleIzquierda(A);
    return temporal;
}

nodoArbolstProducto* rotacionDobleDerecha (nodoArbolstProducto* A)
{
    nodoArbolstProducto * temporal;
    A->der=rotacionSimpleIzquierda(A->der);
    temporal=rotacionSimpleDerecha(A);
    return temporal;
}

nodoArbolstProducto* insertarNodo(nodoArbolstProducto*A, nodoArbolstProducto* nuevo)
{
    nodoArbolstProducto *aux=A;

    if(A->p.idProducto < nuevo->p.idProducto)
    {
        if(A->der==NULL)
        {
            A->der=nuevo;
        }
        else
        {
            A->der=insertarNodo(A->der,nuevo);
            if((getFE(A->der)-getFE(A->izq))==2)
            {
                if(A->der->p.idProducto < nuevo->p.idProducto)
                {
                    aux=rotacionSimpleDerecha(A);
                }
                else
                {
                    aux=rotacionDobleDerecha(A);
                }
            }
        }
    }
    else if (A->p.idProducto > nuevo->p.idProducto)
    {
        if(A->izq==NULL)
        {
            A->izq=nuevo;
        }
        else
        {
            A->izq=insertarNodo(A->izq,nuevo);
            if((getFE(A->izq)-getFE(A->der))==2)
            {
                if(A->izq->p.idProducto > nuevo->p.idProducto)
                {
                    aux=rotacionSimpleIzquierda(A);
                }
                else
                {
                    aux=rotacionDobleDerecha(A);
                }
            }
        }
    }
    if(A->der==NULL && A->izq!=NULL)
    {
        A->fe=A->izq->fe+1;
    }else if (A->izq==NULL && A->der!=NULL)
    {
        A->fe=A->der->fe+1;
    }else{
    A->fe=maximo(getFE(A->izq),getFE(A->der))+1;
    }
    return aux;
}

nodoArbolstProducto * FormarArbol(nodoArbolstProducto * A, stProducto producto)
{
    if(A==NULL)
    {
        A=crearNodoArbol(producto);
    }else{
        A=insertarNodo(A,crearNodoArbol(producto));
    }
    return A;
}

///CONTAR---------------------------------------------------------------------------------------------------
int cantidadDeNodosEliminados(nodoArbolstProducto * A)
{
    int rta;

    if(A==NULL)
        rta= 0;
    else
    {
        if(A->p.eliminado==1)
            rta= 1 + cantidadDeNodosEliminados(A->izq) + cantidadDeNodosEliminados(A->der);
        else
            rta= cantidadDeNodosEliminados(A->izq) + cantidadDeNodosEliminados(A->der);
    }

    return rta;
}

int cantidadDeNodosActivos(nodoArbolstProducto * A)
{
    int rta;

    if(A==NULL)
        rta= 0;
    else
    {
        if(A->p.eliminado==0)
            rta= 1 + cantidadDeNodosActivos(A->izq) + cantidadDeNodosActivos(A->der);
        else
            rta= cantidadDeNodosActivos(A->izq) + cantidadDeNodosActivos(A->der);
    }

    return rta;
}






