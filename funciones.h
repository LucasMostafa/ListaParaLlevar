#ifndef FUNCIONES_H_INCLUDED
#define FUNCIONES_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include "listas.h"
#include "arboles.h"

extern const char ESC;
extern const char dim;
extern const char usuario[];
extern const char contrasenia[];

typedef struct
{
    int idCliente;
    char nombre[30];
    char apellido[30];
    char userName[20];
    char password[20];
    char mail[30];
    char domicilio[30];
    char genero;
    int rol; // 1: es admin - 0: cliente
    int eliminado; // indica 1 o 0 si el cliente fue eliminado
} stCliente;

typedef struct
{
    stCliente cliente;
    nodoListaProducto * listaDeProductos;
    float costoTotalDelPedido;
} stCelda;

typedef struct
{
    int idPedido;
    int idCliente;
    int idProducto;
} stPedido;

///FUNCIONES DEL SISTEMA -------------------------------------------------------------------------------------------
void imprimirCabecera(char cabecera[]);
int ingresarOpcion();
char ingresarOpcionChar();

///CLIENTE ---------------------------------------------------------------------------------------------------------
int cargarUnCliente(stCelda adl[], int validos);
int validarUsuario(stCelda adl[], int validos, char usuario[]);
int validarContrasenia(stCelda adl[], int validos, char contrasenia[]);
int validarMail(stCelda adl[], int validos, char mail[]);
int altaCliente(stCelda adl[], int validos, stCliente nuevo);
stCliente bajaCliente (stCliente A);
int agregarCliente (stCelda adl[], int validos, stCliente nuevo);
void agregarProducto(stCelda adl[], int pos, nodoArbolstProducto * arbol);
int buscarPosCliente(stCelda adl[], int validos, char usuario[]);
int buscarPosClientePorId(stCelda adl[], int validos, int idCliente);
stCliente SubMenuDeModificacionCliente(stCelda adl[], int validos, stCliente A);
void ModificarCliente (stCelda adl[], int validos, char usuario[]);
void cambiarRol(stCelda adl[], int validos, int pos);
void mostrarUnCliente(stCliente A);
void mostrarNombreUsuario(stCliente A);
void recorrerYMostrarTodosLosClientes(stCelda adl[], int validos);
void recorrerYMostrarListaDeUnCliente(stCelda adl[],int pos, char usuario[]);
int contarValidos(char archPedidos[]);
int contarValidosClientes(char archClientes[]);
int BuscarMayor (stPedido arregloPed[], int CantValidos);
int buscarIdClienteEnPedidos(stCliente cliente, stPedido arregloPed[], int validos);

///ADMIN ----------------------------------------------------------------------------------------------------------
//***Pedidos
stCliente SubMenuDeModificacionAdmin (stCelda adl[], int validos, stCliente A);
void mostrarClientesActivos(stCelda adl[], int validos);
void mostrarClientesInactivos(stCelda adl[], int validos);

//***Productos
nodoArbolstProducto * cargarArbolDesdeArchivo(nodoArbolstProducto * arbol, char archProductos[]);
nodoArbolstProducto * cargarUnProducto(nodoArbolstProducto * A);
nodoArbolstProducto * altaProducto (nodoArbolstProducto * A);
nodoArbolstProducto * bajaProducto (nodoArbolstProducto * A);
nodoArbolstProducto * SubMenuDeModificacionProducto (nodoArbolstProducto * A, int idProducto);
nodoArbolstProducto * ModificarProducto (nodoArbolstProducto * A, int idProducto);
void mostrarArbolProductos(nodoArbolstProducto * A);
char mostrarArbolProductosActivos(nodoArbolstProducto * A);
char mostrarArbolProductosInactivos(nodoArbolstProducto * A);
void mostrarProductoPorId(nodoArbolstProducto * A, int idProducto);
void mostrarProductoPorNombre(nodoArbolstProducto * A, char nombreProd[]);

///USERNAME Y PASSWORD -------------------------------------------------------------------------------------------
int ingresarUsuarioYContrasenia(stCelda adl[], int validos);
int validarUsuarioYContrasenia(stCelda adl[], int validos, char usu[], char contra[]);
int posUsuarioYContrasenia(stCelda adl[], int validos, char mail[]);
int recuperarUsuarioYContrasenia(stCelda adl[], int validos);
void mostrarUsuarioYContrasenia(stCelda adl[], int pos);

///ARCHIVO A ARREGLO ---------------------------------------------------------------------------------------------
int bajarArchivoClientesToArreglo(char archClientes[], stCelda adl[]);
int bajarArchivoPedidoToArreglo(char archPedidos[], stPedido arregloPedidos[]);
void bajarArchivoPedidoToADL(char archPedidos[], stCelda adl[], int validos, nodoArbolstProducto * A);
int compararIdPedidoToADL(stCelda adl[], int validos, int idCliente);
nodoArbolstProducto * bajarArchivoToArbol(char archProductos[], nodoArbolstProducto * A);

int clienteDadoDeBaja (stCelda adl[], int pos);

///ARCHIVOS -----------------------------------------------------------------------------------------------------
void pasarArregloClientesToArchivo(char archCliente[], stCelda adl[], int validosCl);
void actualizarPedidosToArchivo(char archPedidos[], stCelda adl[], int validos);

///RECOMENDADO --------------------------------------------------------------------------------------------------
int productoMasSeRepite(nodoListaProducto * lista);
void mostrarProductosRecomendados(nodoArbolstProducto * A, char marca[]);


#endif // FUNCIONES_H_INCLUDED
