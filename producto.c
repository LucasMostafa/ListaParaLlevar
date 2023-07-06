#include "producto.h"

///MOSTRAR -----------------------------------------------------------------
void mostrarProducto(stProducto producto)
{
    printf("\n---------------------------------------------------------------\n");
    printf("\nId: %d", producto.idProducto);
    printf("\nNombre: %s", producto.nombre);
    printf("\nMarca: %s", producto.marca);
    printf("\nPrecio: $%.2f", producto.precio);
}

void mostrarProductoAdmin(stProducto producto)
{
    printf("\nId: %d", producto.idProducto);
    printf("\nNombre: %s", producto.nombre);
    printf("\nMarca: %s", producto.marca);
    printf("\nPrecio: $%.2f", producto.precio);
    if(producto.eliminado==0)
        printf("\nEliminado: NO");
    else
        printf("\nEliminado: SI");
}
