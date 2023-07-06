#include "menu.h"

void inicio(char archClientes[], char archProductos[], char archPedidos[])
{
    system("cls");
    printf("INGRESANDO AL SISTEMA...\n");

    Sleep(1000);
    menuInicial(archClientes, archProductos, archPedidos);
}


///MENUS -----------------------------------------------------------------------------------------------------------------
//MENU INICIAL -----------------------------------------------------------------------------------------------------------
void menuInicial(char archClientes[], char archProductos[], char archPedidos[])
{
    char opcion;

    stCelda * adl= (stCelda*)malloc(sizeof(stCelda)*contarValidosClientes(archClientes));

    int validosCl= 0;
    validosCl= bajarArchivoClientesToArreglo(archClientes, adl);

    nodoArbolstProducto * A= inicArbol();
    A= bajarArchivoToArbol(archProductos, A);

    bajarArchivoPedidoToADL(archPedidos, adl, validosCl, A);

    do
    {
        system("cls");
        imprimirCabecera("\"LISTA para llevar!\"");
        printf("\nINICIO:\n");
        printf("1)Ingresar como cliente.\n");
        printf("2)Ingresar como administrador.\n");
        printf("0)Salir.\n\n");
        opcion= ingresarOpcionChar();

        switch(opcion)
        {
        case '0':
            printf("\n\nSaliendo de \"LISTA para llevar!\"...\n");
            break;
        case '1':
            system("cls");
            validosCl= menuUsuario(archClientes, archPedidos, adl, validosCl, A);

            break;

        case '2':
            system("cls");
            validosCl= menuAdmin(archClientes, archProductos, adl, validosCl, A);

            break;

        default:
            printf("\n\nLa opci%cn ingresada es inv%clida.\n",162,160);
            system("pause");
            break;
        }
    }
    while(opcion!='0');
}

//MENU USUARIO -----------------------------------------------------------------------------------------------------------------------
int menuUsuario(char archClientes[], char archPedidos[], stCelda adl[], int validosCl, nodoArbolstProducto * A)
{
    char opcion;
    char darAlta;
    int pos= -1;
    int eliminado=0;

    do
    {
        system("cls");
        printf("Men%c de usuario:\n",163);
        printf("1)Iniciar sesi%cn.\n",162);
        printf("2)Registrarse.\n");
        printf("3)Recuperar usuario y contrase%ca.\n",164);
        printf("0)Regresar al men%c principal.\n\n",163);
        opcion= ingresarOpcionChar();

        switch(opcion)
        {
        case '0':
            printf("\n");
            break;
        case '1':
            system("cls");
            pos= ingresarUsuarioYContrasenia(adl, validosCl);
            if(pos!=-1)
                eliminado=clienteDadoDeBaja(adl, pos);
            if(eliminado==1)
            {
                printf("\nEl usuario que intenta abrir se encuentra dado de baja. Desea darle el alta? s/n: ");
                fflush(stdin);
                scanf("%c", &darAlta);
                if(darAlta=='s' || darAlta=='S')
                {
                    adl[pos].cliente.eliminado= 0;
                    eliminado=0;
                    printf("\n\nEl usuario fue dado de alta.\n\n");
                    system("pause");
                }
            }
            if(pos!=-1 && eliminado==0)
            {
                menuIniciarSesion(archClientes, archPedidos, adl, validosCl, pos, A);
            }
            break;
        case '2':
            system("cls");
            printf("REGISTRARSE.\n\n");

            adl= (stCelda*)realloc(adl,(contarValidosClientes(archClientes)+1)*sizeof(stCelda));
            validosCl= cargarUnCliente(adl, validosCl);
            pasarArregloClientesToArchivo(archClientes, adl, validosCl);
            break;
        case '3':
            system("cls");
            pos= recuperarUsuarioYContrasenia(adl, validosCl);
            if(pos!=-1)
                mostrarUsuarioYContrasenia(adl, pos);
            system("pause");
            break;
        default:
            printf("\nLa opci%cn ingresada es inv%clida.\n",162,160);
            system("pause");
            break;
        }
    }
    while(opcion>'3' || opcion<'0');

    return validosCl;
}

void menuIniciarSesion(char archClientes[], char archPedidos[], stCelda adl[], int validosCl, int pos, nodoArbolstProducto * A)
{
    float sumaTotal= 0;
    int idPed= 0;
    int idProducto;
    char opcion;
    char aux;
    char salir;

    nodoArbolstProducto * auxArbol= inicArbol();

    do
    {
        system("cls");
        mostrarNombreUsuario(adl[pos].cliente);
        printf("\n\n1)Realizar pedido.\n");
        printf("2)Ver el ultimo pedido realizado.\n");
        printf("3)Borrar mi pedido.\n");
        printf("4)Mi cuenta.\n");
        printf("5)Productos recomendados.\n");
        printf("0)Cerrar sesi%cn.\n\n",162);
        opcion= ingresarOpcionChar();

        switch(opcion)
        {
        case '0':
            printf("\n");
            break;
        case '1':
            system("cls");
            printf("PRODUCTOS:\n");
            inOrden(A);
            do
            {
                printf("\nIngrese el producto que desea cargar: ");
                scanf("%d", &idProducto);
                auxArbol= buscarProductoArbol(A, idProducto);
                if(auxArbol)
                {
                    adl[pos].listaDeProductos= subprogramaAgregarProductoAlPrincipio(adl[pos].listaDeProductos, auxArbol->p);
                    actualizarPedidosToArchivo(archPedidos, adl, validosCl);
                    bajarArchivoPedidoToADL(archPedidos, adl, validosCl, A);
                }
                else
                {
                    printf("\nLa opcion ingresada no existe.\n");
                }

                printf("\nPresione cualquier tecla para seleccionar otro producto(ESC para salir).\n");
                fflush(stdin);
                salir= getch();
            }
            while(salir!=ESC);
            break;
        case '2':
            system("cls");
            if(adl[pos].listaDeProductos)
            {
                printf("PEDIDO: ");
                sumaTotal= sumarValorProductos(adl[pos].listaDeProductos);
                recorrerYMostrarLista(adl[pos].listaDeProductos);
                printf("\n\nEl precio total del pedido es: $%.2f", sumaTotal);
            }
            else
                printf("El cliente no tiene ningun pedido realizado.\n");
            printf("\n\n");
            system("pause");
            break;
        case '3':
            system("cls");
            recorrerYMostrarLista(adl[pos].listaDeProductos);

            if(adl[pos].listaDeProductos)
            {
                printf("\nDesea eliminar el pedido? s/n: ");
                fflush(stdin);
                scanf("%c", &aux);
                if(aux=='s' || aux=='S')
                {
                    adl[pos].listaDeProductos= borrarTodaLaListaProducto(adl[pos].listaDeProductos);
                    actualizarPedidosToArchivo(archPedidos, adl, validosCl);
                    bajarArchivoPedidoToADL(archPedidos, adl, validosCl, A);
                    printf("\n\nPedido eliminado.\n\n");
                }
            }
            else
            {
                printf("Usted no realizo ningun pedido.\n\n");
            }
            system("pause");
            break;
        case '4':
            system("cls");
            printf("MIS DATOS:");
            mostrarUnCliente(adl[pos].cliente);
            printf("\n");
            printf("Desea modificar algun dato? s/n");
            fflush(stdin);
            scanf("%c", &aux);
            if(aux=='s' || aux=='S')
            {
                ModificarCliente(adl,validosCl, adl[pos].cliente.userName);
                pasarArregloClientesToArchivo(archClientes, adl, validosCl);
            }
            break;
        case '5':
            system("cls");
            if(adl[pos].listaDeProductos)
            {
                idProducto= productoMasSeRepite(adl[pos].listaDeProductos);
                auxArbol= buscarProductoArbol(A, idProducto);
                printf("PRODUCTOS RECOMENDADOS PARA USTED:\n\n");
                mostrarProductosRecomendados(A, auxArbol->p.marca);
            }
            else
            {
                printf("No hay productos para recomendar, ya que usted no cuenta con pedidos anteriores.\n");
            }
            printf("\n\n");
            system("pause");
            break;
        default:
            printf("\nLa opci%cn ingresada es inv%clida.\n",162,160);
            system("pause");
            break;
        }
    }
    while(opcion!='0');
}

//MENU ADMIN ------------------------------------------------------------------------------------------------------------
int menuAdmin(char archClientes[], char archProducto[], stCelda adl[], int validosCl, nodoArbolstProducto * A)
{
    int admi= 0;
    int pos= -1;
    char opcion;
    char salir;
    char ingresarUsuario[20];
    char ingresarContra[20];

    do
    {
        do
        {
            system("cls");
            printf("ADMINISTRADOR.\n");
            printf("\n1)Administrador principal.");
            printf("\n2)Administrador secundario");
            printf("\n\n0)Salir.\n");
            opcion= ingresarOpcionChar();

            switch(opcion)
            {
            case '0':
                printf("\n");
                break;

            case '1':
                system("cls");
                admi= 1;
                printf("INICIAR SESION.\n");
                printf("\nUsuario: ");
                fflush(stdin);
                gets(ingresarUsuario);
                printf("Contrase%ca: ",164);
                fflush(stdin);
                gets(ingresarContra);
                break;

            case '2':
                system("cls");
                pos= ingresarUsuarioYContrasenia(adl, validosCl);
                break;

            default:
                printf("\nValor incorrecto.\n");
                system("pause");
                break;
            }
        }
        while(opcion!='0' && opcion!='1' && opcion!='2');

        if(opcion=='1' || opcion=='2')
        {
            if(((strcmp(ingresarUsuario, usuario)==0) && (strcmp(ingresarContra, contrasenia)==0)) || adl[pos].cliente.rol==1)
            {
                do
                {
                    system("cls");
                    printf("OPCIONES:");
                    printf("\n1)Ingresar a clientes.");
                    printf("\n2)Ingresar a productos.");
                    printf("\n\n0)Salir.\n");
                    opcion= ingresarOpcionChar();

                    switch(opcion)
                    {
                    case '0':
                        printf("\n");
                        break;

                    case '1':
                        system("cls");
                        validosCl= subMenuAdminClientes(archClientes, adl, validosCl);
                        printf("\n");
                        system("pause");
                        break;
                    case '2':
                        system("cls");
                        subMenuAdminProductos(archProducto, A);
                        printf("\n");
                        break;

                    default:
                        printf("\nValor incorrecto.\n");
                        system("pause");
                        break;
                    }
                }
                while(opcion!='0' && opcion!='1' && opcion!='2');
            }
            else
            {
                if(admi==1)
                {
                    if(strcmp(ingresarUsuario, usuario)!=0 && strcmp(ingresarContra, contrasenia)!=0)
                    {
                        printf("\nSu usuario y contrase%ca son incorrectas.\n",164);
                        fflush(stdin);
                        salir=getch();
                    }
                    else if(strcmp(ingresarUsuario, usuario)==0)
                    {
                        printf("\nSu contrase%ca es incorrecta.\n",164);
                        fflush(stdin);
                        salir=getch();
                    }
                }
                else if(pos!=-1)
                {
                    printf("\nNo posee el rol de admin.\n",164);
                    fflush(stdin);
                    salir=getch();
                }
            }
        }
    }
    while(salir!=ESC && opcion!='0');

    return validosCl;
}

int subMenuAdminClientes(char archClientes[], stCelda adl[], int validosCl)
{
    int pos;
    int id;
    char opcion;
    char salir;

    do
    {
        system("cls");
        printf("Men%c de administrador de clientes:\n",163);

        printf("1)Dar de alta cliente.\n");
        printf("2)Dar de baja cliente.\n");
        printf("3)Cargar cliente.\n");
        printf("4)Modificar clientes.\n");
        printf("5)Listados de clientes.\n");
        printf("6)Consulta.\n");
        printf("7)Cambiar rol.\n");

        printf("0)Cerrar sesi%cn de administrador.\n\n",162);
        opcion= ingresarOpcionChar();

        switch(opcion)
        {
        case '0':
            printf("\n");
            break;

        case '1':
            system("cls");
            printf("Ingrese el id del cliente que desea dar de alta: ");
            scanf("%d", &id);
            pos= buscarPosClientePorId(adl, validosCl, id);
            if(pos!=-1)
            {
                if(adl[pos].cliente.eliminado==1)
                {
                    adl[pos].cliente.eliminado= 0;
                    printf("\nEl siguiente cliente fue dado de alta:\n");
                    mostrarUnCliente(adl[pos].cliente);
                    pasarArregloClientesToArchivo(archClientes, adl, validosCl);
                }
                else
                {
                    printf("\nEl cliente ya se encontraba activo en la plataforma.\n");
                }
            }
            else
            {
                printf("Cliente inexistente en la base de datos.\n");
            }
            printf("\n\n");
            system("pause");
            break;

        case '2':
            system("cls");
            printf("Ingrese el id del cliente que desea dar de baja: ");
            scanf("%d", &id);
            pos= buscarPosClientePorId(adl, validosCl, id);
            if(pos!=-1)
            {
                if(adl[pos].cliente.eliminado==0)
                {
                    adl[pos].cliente.eliminado= 1;
                    printf("\nEl siguiente cliente fue dado de baja:\n");
                    mostrarUnCliente(adl[pos].cliente);
                    pasarArregloClientesToArchivo(archClientes, adl, validosCl);
                }
                else
                {
                    printf("\nEl cliente ya se encontraba dado de baja en la plataforma.\n");
                }
            }
            else
            {
                printf("Cliente inexistente en la base de datos.\n");
            }
            printf("\n\n");
            system("pause");
            break;

        case '3':
            system("cls");
            adl = (stCelda*)realloc(adl,(contarValidosClientes(archClientes)+1)*sizeof(stCelda));
            validosCl= cargarUnCliente(adl, validosCl); //Se crear como cliente, luego el admin puede cambiarle el rol.
            pasarArregloClientesToArchivo(archClientes, adl, validosCl);

            break;

        case '4':
            system("cls");
            do
            {
                printf("Ingrese el id del cliente que desea modificar: ");
                scanf("%d", &id);
                pos= buscarPosClientePorId(adl, validosCl, id);
                if(pos==-1)
                {
                    printf("\nCliente no encontrado. Presione cualquier tecla para ingresar otro id (ESC para salir).\n");
                    fflush(stdin);
                    salir= getch();
                }
                else
                {
                    ModificarCliente(adl, validosCl, adl[pos].cliente.userName);
                    pasarArregloClientesToArchivo(archClientes, adl, validosCl);
                }
            }
            while(pos==-1 && salir!=ESC);
            break;

        case '5':
            system("cls");
            recorrerYMostrarTodosLosClientes(adl, validosCl);
            printf("\n");
            system("pause");
            break;

        case '6':
            system("cls");
            do
            {
                printf("Ingrese el id del cliente que desea ver: ");
                scanf("%d", &id);
                pos= buscarPosClientePorId(adl, validosCl, id);
                if(pos==-1)
                {
                    printf("\nCliente no encontrado. Presione cualquier tecla para ingresar otro id (ESC para salir).\n");
                    fflush(stdin);
                    salir= getch();
                }
                else
                {
                    mostrarUnCliente(adl[pos].cliente);
                    if(adl[pos].cliente.eliminado==0)
                        printf("\nEliminado: NO");
                    else
                        printf("\nEliminado: SI");
                }
            }
            while(pos==-1 && salir!=ESC);
            printf("\n\n");
            system("pause");
            break;
        case '7':
            system("cls");
            do
            {
                printf("Ingrese el id del cliente que desea cambiar el rol: ");
                scanf("%d", &id);
                pos= buscarPosClientePorId(adl, validosCl, id);
                if(pos==-1)
                {
                    printf("\nCliente no encontrado. Presione cualquier tecla para ingresar otro id (ESC para salir).\n");
                    fflush(stdin);
                    salir= getch();
                }
                else
                {
                    cambiarRol(adl, validosCl, pos);
                    pasarArregloClientesToArchivo(archClientes, adl, validosCl);
                }
            }
            while(pos==-1 && salir!=ESC);
            printf("\n\n");
            system("pause");
            break;

        default:
            printf("\nLa opci%cn ingresada es inv%clida.\n",162,160);
            system("pause");
            break;
        }
    }
    while(opcion!='0');

    return validosCl;
}

void subMenuAdminProductos(char archProducto[], nodoArbolstProducto * A)
{
    int pos;
    int id;
    int aux;
    char opcion;
    char salir;
    char caracter;

    nodoArbolstProducto * auxArbol= inicArbol();

    do
    {
        system("cls");
        printf("Men%c de administrador de productos:\n",163);

        printf("1)Dar de alta producto.\n");
        printf("2)Dar de baja producto.\n");
        printf("3)Cargar producto.\n");
        printf("4)Modificar producto.\n");
        printf("5)Listados de productos.\n");
        printf("6)Consulta.\n");

        printf("0)Cerrar sesi%cn de administrador.\n\n",162);
        opcion= ingresarOpcionChar();

        switch(opcion)
        {
        case '0':
            printf("\n");
            break;

        case '1':
            system("cls");
            aux= cantidadDeNodosEliminados(A);
            if(aux!=0)
            {
                caracter= mostrarArbolProductosInactivos(A);
                if(caracter!='0')
                {
                    do
                    {
                        printf("Ingrese el id del producto que desea dar de alta: ");
                        scanf("%d", &id);
                        auxArbol= buscarProductoArbol(A, id);
                        if(auxArbol==NULL)
                        {
                            printf("\nProducto no encontrado. Presione cualquier tecla para ingresar otro id (ESC para salir).\n");
                            fflush(stdin);
                            salir= getch();
                        }
                        else
                        {
                            auxArbol= altaProducto(auxArbol);
                            pasarArbolToArchivo(archProducto, A);
                        }
                    }
                    while(auxArbol==NULL && salir!=ESC);
                }
            }
            else
            {
                printf("No hay productos eliminados para dar de alta.\n");
            }
            system("pause");
            break;

        case '2':
            system("cls");
            aux= cantidadDeNodosActivos(A);
            if(aux!=0)
            {
                caracter= mostrarArbolProductosActivos(A);
                if(caracter!='0')
                {
                    do
                    {
                        printf("Ingrese el id del producto que desea dar de baja: ");
                        scanf("%d", &id);
                        auxArbol= buscarProductoArbol(A, id);
                        if(auxArbol==NULL)
                        {
                            printf("\nProducto no encontrado. Presione cualquier tecla para ingresar otro id (ESC para salir).\n");
                            fflush(stdin);
                            salir= getch();
                        }
                        else
                        {
                            auxArbol= bajaProducto(auxArbol);
                            pasarArbolToArchivo(archProducto, A);
                        }
                    }
                    while(auxArbol==NULL && salir!=ESC);
                }
            }
            else
            {
                printf("No hay productos activos para dar de baja.\n");
            }
            system("pause");
            break;

        case '3':
            system("cls");
            A= cargarUnProducto(A);
            pasarArbolToArchivo(archProducto, A);
            break;

        case '4':
            do
            {
                system("cls");
                printf("Ingrese el id del producto que desea modificar: ");
                scanf("%d", &id);
                auxArbol= buscarProductoArbol(A, id);
                if(auxArbol==NULL)
                {
                    printf("\Producto no encontrado. Presione cualquier tecla para ingresar otro id (ESC para salir).\n");
                    fflush(stdin);
                    salir= getch();
                }
                else
                {
                    A= SubMenuDeModificacionProducto(A, id);
                    pasarArbolToArchivo(archProducto, A);
                }
            }
            while(auxArbol==NULL && salir!=ESC);
            break;

        case '5':
            system("cls");
            mostrarArbolProductos(A);
            printf("\n");
            system("pause");
            break;

        case '6':
            system("cls");
            do
            {
                printf("Ingrese el id del producto que desea ver: ");
                scanf("%d", &id);
                auxArbol= buscarProductoArbol(A, id);
                if(auxArbol==NULL)
                {
                    printf("\nCliente no encontrado. Presione cualquier tecla para ingresar otro id (ESC para salir).\n");
                    fflush(stdin);
                    salir= getch();
                }
                else
                {
                    mostrarProductoAdmin(auxArbol->p);
                }
            }
            while(pos==-1 && salir!=ESC);
            printf("\n\n");
            system("pause");
            break;

        default:
            printf("\nLa opci%cn ingresada es inv%clida.\n",162,160);
            system("pause");
            break;
        }
    }
    while(opcion!='0');
}

