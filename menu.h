#ifndef MENU_H_INCLUDED
#define MENU_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <windows.h>
#include "funciones.h"

///MENUS
void inicio(char archClientes[], char archProductos[], char archPedidos[]);
void menuInicial(char archClientes[], char archProductos[], char archPedidos[]);
int menuUsuario(char archClientes[], char archPedidos[], stCelda adl[], int validosCl, nodoArbolstProducto * A);
void menuIniciarSesion(char archClientes[], char archPedidos[], stCelda adl[], int validosCl, int pos, nodoArbolstProducto * A);
int menuAdmin(char archClientes[], char archProducto[], stCelda adl[], int validosCl, nodoArbolstProducto * A);
int subMenuAdminClientes(char archClientes[], stCelda adl[], int validosCl);
void subMenuAdminProductos(char archProducto[], nodoArbolstProducto * A);

#endif // MENU_H_INCLUDED
