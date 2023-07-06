#include "funciones.h"

const char ESC= 27;
const char dim= 100;
const char usuario[]="admin";
const char contrasenia[]="admin";

///FUNCIONES DEL SISTEMA ----------------------------------------------------------------------------------
void imprimirCabecera(char cabecera[])
{
    int i;

    printf("%c", 201);

    for(i=0; i<50; i++)
    {
        printf("%c",205);
    }
    printf("%c\n", 187);
    printf("%c%32s%19c\n", 186,cabecera,186);
    printf("%c", 200);

    for(i=0; i<50; i++)
    {
        printf("%c",205);
    }
    printf("%c", 188);
}

//Funciones que nos permite capturar una opcion que seleccione el usuario por comando
int ingresarOpcion()
{
    int opcion;
    printf("Ingrese opci%cn: ",162);
    scanf("%d", &opcion);
    return opcion;
}

char ingresarOpcionChar()
{
    char opcion;
    printf("");
    fflush(stdin);
    opcion=getch();
    return opcion;
}

///CARGA CLIENTE ------------------------------------------------------------------------------------------
//CLIENTE--------------------------------------------------------------------------------------------------
int cargarUnCliente(stCelda adl[], int validos)
{
    stCliente nuevo;

    int flag=0;

    nuevo.idCliente= validos + 1000;

    printf("Carga de nuevo cliente:\n");
    printf("Nombre: ");
    fflush(stdin);
    gets(nuevo.nombre);
    printf("Apellido: ");
    fflush(stdin);
    gets(nuevo.apellido);

    do
    {
        printf("Usuario: ");
        fflush(stdin);
        gets(nuevo.userName);

        flag= validarUsuario(adl, validos, nuevo.userName);

        if(flag==1)
        {
            printf("\nEl nombre de usuario ingresado ya existe. Debera ingresar uno nuevo.\n");

        }
    }
    while(flag==1);

    printf("Contrase%ca: ", 164);
    fflush(stdin);
    gets(nuevo.password);

   do
    {
        printf("Mail: ");
        fflush(stdin);
        gets(nuevo.mail);

        flag= validarUsuario(adl, validos, nuevo.mail);

        if(flag==1)
        {
            printf("\nEl mail ingresado ya existe. Debera ingresar uno nuevo.\n");

        }
    }
    while(flag==1);

    printf("Domicilio: ");
    fflush(stdin);
    gets(nuevo.domicilio);

    do
    {
        printf("Genero (f/m/i): ");
        fflush(stdin);
        scanf("%c", &nuevo.genero);
        if(nuevo.genero!='f' && nuevo.genero!='m' && nuevo.genero!='i')
        {
            printf("\nGenero ingresado incorrecto. Debera ingresarlo nuevamente.\n");
        }
    }
    while(nuevo.genero!='f' && nuevo.genero!='m' && nuevo.genero!='i');

    nuevo.rol= 0;

    nuevo.eliminado= 0;

    printf("Su Id de Cliente es: ");
    printf("%d", nuevo.idCliente);

    validos= altaCliente(adl, validos, nuevo);

    printf("\n\nUsuario creado correctamente.\n\n");
    system("pause");

    return validos;
}

int validarUsuario(stCelda adl[], int validos, char usuario[])
{
    int i= 0;
    int flag= 0;

    while(i<validos && flag==0)
    {
        if(strcmp(usuario, adl[i].cliente.userName)==0)
        {
            flag= 1;
        }
        i++;
    }
    return flag;
}

int validarContrasenia(stCelda adl[], int validos, char contrasenia[])
{
    int i= 0;
    int flag= 0;

    while(i<validos && flag==0)
    {
        if(strcmp(contrasenia, adl[i].cliente.password)==0)
        {
            flag= 1;
        }
        i++;
    }
    return flag;
}

int validarMail(stCelda adl[], int validos, char mail[])
{
    int i= 0;
    int flag= 0;

    while(i<validos && flag==0)
    {
        if(strcmp(mail, adl[i].cliente.mail)==0)
        {
            flag= 1;
        }
        i++;
    }
    return flag;
}

///ALTA Y BAJA --------------------------------------------------------------------------------------
int altaCliente(stCelda adl[], int validos, stCliente nuevo)
{
    int pos= buscarPosCliente(adl, validos, nuevo.userName);

    if(pos==-1)
    {
        validos= agregarCliente(adl, validos, nuevo);
    }

    return validos;
}

stCliente bajaCliente (stCliente A)
{
    char opcion;

    printf("Desea usted dar de baja el usuario de nuestra plataforma? (s/n) ");
    fflush(stdin);
    scanf("%c", &opcion);
    if (opcion=='s'|| opcion=='S')
    {
        A.eliminado= 1;
        printf("El usuario fue dado de baja con %cxito.\n",130);
        system("pause");
    }
    return A;
}

///AGREGAR ---------------------------------------------------------------------------------------------
int agregarCliente (stCelda adl[], int validos, stCliente nuevo)
{
    adl[validos].cliente= nuevo;
    adl[validos].listaDeProductos= inicLista();
    validos++;
    return validos;
}

void agregarProducto(stCelda adl[], int pos, nodoArbolstProducto * arbol)
{
    int id;

    nodoArbolstProducto * buscado;
    printf("Seleccione el producto que desea agregar al pedido");
    scanf("%d", &id);
    buscado= buscarProductoArbol(arbol, id);
    buscado= inicArbol();
    adl[pos].listaDeProductos= subprogramaAgregarProductoAlFinal(adl[pos].listaDeProductos, buscado->p);
}

///BUSCAR ----------------------------------------------------------------------------------------------
int buscarPosCliente(stCelda adl[], int validos, char usuario[])
{
    int rta=-1;
    int i=0;
    while(i<validos && rta==-1)
    {
        if(strcmp(adl[i].cliente.userName,usuario)==0)
        {
            rta=i;
        }
        i++;
    }
    return rta;
}

int buscarPosClientePorId(stCelda adl[], int validos, int idCliente)
{
    int rta=-1;
    int i=0;
    while((i<validos)&&(rta==-1))
    {
        if(adl[i].cliente.idCliente == idCliente)
        {
            rta=i;
        }
        i++;
    }
    return rta;
}

///MODIFICACION ------------------------------------------------------------------------------------------------------
stCliente SubMenuDeModificacionCliente (stCelda adl[], int validos, stCliente A)
{
    char op;
    char control='s';
    int flag= 0;

    do
    {
        system("cls");
        printf("Selecci%cn el campo que desea modificar:\n",162);
        printf("1-Nombre.\n");
        printf("2-Apellido.\n");
        printf("3-Usuario.\n");
        printf("4-Contrase%ca.\n",164);
        printf("5-Mail.\n");
        printf("6-Domicilio.\n");
        printf("7-Genero.\n");

        printf("0-Salir.\n\n");
        op= ingresarOpcionChar();

        switch (op)
        {
        case '0':
            printf("\n");
            break;
        case '1':
            printf("Ingrese nuevo nombre: ");
            fflush(stdin);
            gets(A.nombre);
            break;
        case '2':
            printf("Ingrese nuevo apellido: ");
            fflush(stdin);
            gets(A.apellido);
            break;
        case '3':
            do
            {
                printf("Ingrese nuevo nombre de usuario: ");
                fflush(stdin);
                gets(A.userName);
                flag= validarUsuario(adl, validos, A.userName);

                if(flag==1)
                {
                    printf("\nEl nombre de usuario ingresado ya existe. Debera ingresar uno nuevo.\n");

                }
            }
            while(flag==1);
            break;
        case '4':
            printf("Ingrese nueva contrase%ca: ",164);
            fflush(stdin);
            gets(A.password);
            break;

            break;
        case '5':
            do
            {
                printf("Ingrese nuevo mail: ");
                fflush(stdin);
                gets(A.mail);

                flag= validarUsuario(adl, validos, A.mail);

                if(flag==1)
                {
                    printf("\nEl mail ingresado ya existe. Debera ingresar uno nuevo.\n");

                }
            }
            while(flag==1);
            break;
        case '6':
            printf("Ingrese nuevo domicilio: ");
            fflush(stdin);
            gets(A.domicilio);
            break;
        case '7':
            printf("Ingrese genero: ");
            fflush(stdin);
            scanf("%c", &A.genero);
            break;
        default:
            printf("El n%cmero ingresado no se encuentra entre las opciones por favor ingr%cselo nuevamente.\n",163,130);
            break;
        }
        if(op!='0')
        {
            printf("\nDesea modificar un nuevo dato? s/n\n");
            fflush(stdin);
            scanf("%c", &control);
        }
    }
    while (op!='0' && control=='s'|| control=='S');

    return A;
}

void ModificarCliente (stCelda adl[], int validos, char usuario[])
{

    int pos= 0;

    pos= buscarPosCliente(adl, validos, usuario);

    adl[pos].cliente= SubMenuDeModificacionCliente(adl,validos, adl[pos].cliente);
}

void cambiarRol(stCelda adl[], int validos, int pos)
{
    char aux;

    if(pos!=-1)
    {
        mostrarUnCliente(adl[pos].cliente);

        if(adl[pos].cliente.rol==0)
        {
            printf("\nDesea cambiar el rol del cliente a admin? s/n");
            fflush(stdin);
            scanf("%c", &aux);
            if(aux=='s' || aux=='S')
                adl[pos].cliente.rol= 1;
        }
        else
        {
            printf("\nDesea cambiar el rol del cliente-admin a cliente? s/n");
            fflush(stdin);
            scanf("%c", &aux);
            if(aux=='s' || aux=='S')
                adl[pos].cliente.rol= 0;
        }
    }
}

///MOSTRAR ----------------------------------------------------------------------------------------------------------------
void mostrarUnCliente(stCliente A)
{
    printf("\nId: %d", A.idCliente);
    printf("\nNombre: %s", A.nombre);
    printf("\nApellido: %s", A.apellido);
    printf("\nUsuario: %s", A.userName);
    printf("\nMail: %s", A.mail);
    printf("\nDomicilio: %s", A.domicilio);
    if(A.genero=='m')
        printf("\nGenero: Masculino");
    else if(A.genero=='f')
        printf("\nGenero: Femenino");
    else
        printf("\nGenero: Indefinido");
}

void mostrarNombreUsuario(stCliente A)
{
    printf("USUARIO: %s", A.userName);
    printf("\n---------------------------------------------------------------");
}

void recorrerYMostrarTodosLosClientes(stCelda adl[], int validos)
{
    int i;

    for(i=0; i<validos; i++)
    {
        printf("\n---------------------------------------------------------------\n");
        printf("\n---------------------------------------------------------------\n");
        printf("CLIENTE:");
        mostrarUnCliente(adl[i].cliente);
        printf("\n\nPEDIDO:");
        recorrerYMostrarLista(adl[i].listaDeProductos);
    }
}

void recorrerYMostrarListaDeUnCliente(stCelda adl[],int pos, char usuario[])
{
    int flag=0;

    if(strcmp(usuario, adl[pos].cliente.userName)==0)
    {
        mostrarUnCliente(adl[pos].cliente);
        recorrerYMostrarLista(adl[pos].listaDeProductos);
        flag=1;
    }

    if(flag==0)
        printf("\nNo se encontro el cliente.\n");
}

int contarValidos(char archPedidos[])
{
    stPedido pedido;
    int contador= 0;

    FILE *punteroPed;
    punteroPed= fopen(archPedidos,"rb");

    if(punteroPed)
    {
        while(fread(&pedido, sizeof(stPedido), 1, punteroPed)>0)
        {
            contador++;
        }
    }
    else
    {
        printf("\nNo se pudo abrir el archivo.\n");
    }

    fclose(punteroPed);
    return contador;
}

int contarValidosClientes(char archClientes[])
{
    stCliente cliente;
    int contador= 0;

    FILE *puntero;
    puntero= fopen(archClientes,"rb");

    if(puntero)
    {
        while(fread(&cliente, sizeof(stCliente), 1, puntero)>0)
        {
            contador++;
        }
    }
    else
    {
        printf("\nNo se pudo abrir el archivo.\n");
    }

    fclose(puntero);
    return contador;
}

int BuscarMayor (stPedido arregloPed[], int CantValidos)
{
    int i=0;
    stPedido mayor= arregloPed[i];
    i=1;

    while (i<CantValidos)
    {
        if(arregloPed[i].idPedido > mayor.idPedido)
        {
            mayor=arregloPed[i];
        }
        i++;
    }
    return mayor.idPedido;
}

int buscarIdClienteEnPedidos(stCliente cliente, stPedido arregloPed[], int validos)
{
    int i= 0;
    int flag= 0;

    while(flag==0 && i<validos)
    {
        if(cliente.idCliente==arregloPed[i].idCliente)
        {
            flag= 1;
        }
        i++;
    }
    return flag;
}


//ADMIN --------------------------------------------------------------------------------------------------------
//***Clientes
///MODIFICACION ------------------------------------------------------------------------------------------------
stCliente SubMenuDeModificacionAdmin (stCelda adl[], int validos, stCliente A)
{
    char op;
    char control='s';
    int flag= 0;

    do
    {
        system("cls");
        printf("Selecci%cn el campo que desea modificar:\n",162);
        printf("1-Nombre.\n");
        printf("2-Apellido.\n");
        printf("3-Usuario.\n");
        printf("4-Contrase%ca.\n",164);
        printf("5-Mail.\n");
        printf("6-Domicilio.\n");
        printf("7-Genero.\n");
        printf("8-Rol.\n");
        printf("9-Eliminado.\n");

        printf("0-Salir.\n\n");
        op= ingresarOpcionChar();

        switch (op)
        {
        case '0':
            printf("\n");
            break;
        case '1':
            printf("Ingrese nuevo nombre: ");
            fflush(stdin);
            gets(A.nombre);
            break;
        case '2':
            printf("Ingrese nuevo apellido: ");
            fflush(stdin);
            gets(A.apellido);
            break;
        case '3':
            do
            {
                printf("Ingrese nuevo nombre de usuario: ");
                fflush(stdin);
                gets(A.userName);
                flag= validarUsuario(adl, validos, A.userName);

                if(flag==1)
                {
                    printf("\nEl nombre de usuario ingresado ya existe. Debera ingresar uno nuevo.\n");

                }
            }
            while(flag==1);
            break;
        case '4':
            printf("Ingrese nueva contrase%ca: ",164);
            fflush(stdin);
            gets(A.password);
            break;

            break;
        case '5':
            do
            {
                printf("Ingrese nuevo mail: ");
                fflush(stdin);
                gets(A.mail);

                flag= validarUsuario(adl, validos, A.mail);

                if(flag==1)
                {
                    printf("\nEl mail ingresado ya existe. Debera ingresar uno nuevo.\n");

                }
            }
            while(flag==1);
            break;
        case '6':
            printf("Ingrese nuevo domicilio: ");
            fflush(stdin);
            gets(A.domicilio);
            break;
        case '7':
            printf("Ingrese genero: ");
            fflush(stdin);
            scanf("%c", &A.genero);
            break;
        case '8':
            do
            {
                printf("Ingrese el rol (1-admin / 0-cliente): ");
                scanf("%d", &A.rol);
                if(A.rol!=1 && A.rol!=0)
                {
                    printf("\nEl rol ingresado es incorrecto. Debera ingresar nuevamente el rol.\n");
                }
            }
            while(A.rol!=1 && A.rol!=0);
            break;
        case '9':
            do
            {
                printf("Eliminado o activo (1-eliminado / 0-activo): ");
                scanf("%d", &A.eliminado);
                if(A.eliminado!=1 && A.eliminado!=0)
                {
                    printf("\nEl valor ingresado es incorrecto. Debera ingresar nuevamente el valor.\n");
                }
            }
            while(A.eliminado!=1 && A.eliminado!=0);
        default:
            printf("El n%cmero ingresado no se encuentra entre las opciones por favor ingr%cselo nuevamente.\n",163,130);
            break;
        }
        if(op!='0')
        {
            printf("\nDesea modificar un nuevo dato? s/n\n");
            fflush(stdin);
            scanf("%c", &control);
        }
    }
    while ((op!='0') && (control=='s')|| (control=='S'));

    return A;
}

///MOSTRAR -------------------------------------------------------------------------------------------------------------------
void mostrarClientesActivos(stCelda adl[], int validos)
{
    int i;

    for(i=0; i<validos; i++)
    {
        if(adl[i].cliente.eliminado==0)
            mostrarUnCliente(adl[i].cliente);
    }
}

void mostrarClientesInactivos(stCelda adl[], int validos)
{
    int i;

    for(i=0; i<validos; i++)
    {
        if(adl[i].cliente.eliminado==1)
            mostrarUnCliente(adl[i].cliente);
    }
}

//***Productos
///CARGAR PRODUCTO ---------------------------------------------------------------------------------------------------------------------
///ALTA Y BAJA -------------------------------------------------------------------------------------------------------------------------
nodoArbolstProducto * cargarUnProducto(nodoArbolstProducto * A)
{
    stProducto producto;

    int masGrande= 0;

    printf("Cargar nuevo producto:\n");
    if(A)
    {
        nodoArbolstProducto * aux= nodoMasDerecho(A);
        masGrande= aux->p.idProducto;
    }

    producto.idProducto= masGrande + 1;
    printf("\nId: %d", producto.idProducto);

    nodoArbolstProducto * nombre= inicArbol();
    do
    {
        printf("\nNombre: ");
        fflush(stdin);
        gets(producto.nombre);

        nombre= buscarProductoArbolPorNombre(A, producto.nombre);

        if(nombre)
        {
            printf("\nEl producto ingresado ya existe. Debera ingresar uno nuevo.\n");

        }
    }
    while(nombre);

    printf("Marca: ");
    fflush(stdin);
    gets(producto.marca);

    printf("Precio: ");
    scanf("%f", &producto.precio);

    producto.eliminado= 0;

    A= FormarArbol(A, producto);

    printf("\n\Producto creado correctamente.\n\n");
    system("pause");

    return A;
}

nodoArbolstProducto * altaProducto (nodoArbolstProducto * A)
{
    char opcion;

    printf("Desea usted dar de alta el producto de nuestra plataforma? (s/n) ");
    fflush(stdin);
    scanf("%c", &opcion);
    if (opcion=='s'|| opcion=='S')
    {
        A->p.eliminado= 0;
        printf("El producto fue dado de alta con %cxito.\n",130);
    }
    return A;
}

nodoArbolstProducto * bajaProducto (nodoArbolstProducto * A)
{
    char opcion;

    printf("Desea usted dar de baja el producto de nuestra plataforma? (s/n) ");
    fflush(stdin);
    scanf("%c", &opcion);
    if (opcion=='s'|| opcion=='S')
    {
        A->p.eliminado= 1;
        printf("El producto fue dado de baja con %cxito.\n",130);
    }
    return A;
}

///MODIFICACION PRODUCTOS------------------------------------------------------------------------------------------------------
nodoArbolstProducto * SubMenuDeModificacionProducto (nodoArbolstProducto * A, int idProducto)
{
    char op;
    char control='s';
    char nombre[30];

    nodoArbolstProducto * aux= inicArbol();
    aux= buscarProductoArbol(A, idProducto);
    nodoArbolstProducto * aux2= inicArbol();
    do
    {
        system("cls");
        printf("Selecci%cn el campo que desea modificar:\n",162);
        printf("1-Nombre.\n");
        printf("2-Marca.\n");
        printf("3-Precio.\n");
        printf("4-Eliminado.\n");

        printf("0-Salir.\n\n");
        op= ingresarOpcionChar();

        switch (op)
        {
        case '0':
            printf("\n");
            break;
        case '1':
            do
            {
                printf("Ingrese nuevo nombre: ");
                fflush(stdin);
                gets(nombre);

                aux2= buscarProductoArbolPorNombre(A, nombre);

                if(aux2)
                {
                    printf("\nEl nombre del producto ya existe. Debera ingresar uno nuevo.\n");

                }
                else
                {
                    strcpy(aux->p.nombre, nombre);
                }
            }
            while(aux2);
            break;
        case '2':
            printf("Ingrese nueva marca: ");
            fflush(stdin);
            gets(aux->p.marca);
            break;
        case '3':
            printf("Ingrese nuevo precio: ");
            scanf("%f", &aux->p.precio);
            break;
        case '4':
            printf("Eliminado / Activo (1 - 0):");
            fflush(stdin);
            scanf("%d", &aux->p.eliminado);
            break;
        default:
            printf("El n%cmero ingresado no se encuentra entre las opciones por favor ingr%cselo nuevamente.\n",163,130);
            break;
        }
        if(op!='0')
        {
            printf("\nDesea modificar un nuevo dato? s/n\n");
            fflush(stdin);
            scanf("%c", &control);
        }
    }
    while (op!='0' && control=='s'|| control=='S');

    return A;
}

///MOSTRAR PRODUCTOS -------------------------------------------------------------------------------------------------------------------
void mostrarArbolProductos(nodoArbolstProducto * A)
{
    char op;
    char control='s';

    do
    {
        system("cls");
        printf("Como desea ver los productos: ");
        printf("\n1- InOrder.");
        printf("\n2- PreOrder.");
        printf("\n3- PostOrder.");
        printf("\n\n0- Salir. ");

        op= ingresarOpcionChar();
        switch (op)
        {
        case '0':
            printf("\n");
            break;
        case '1':
            inOrden(A);
            break;
        case '2':
            preOrden(A);
            break;
        case '3':
            postOrden(A);
            break;

        default:
            printf("El n%cmero ingresado no se encuentra entre las opciones por favor ingr%cselo nuevamente.\n",163,130);
            break;
        }
        if(op!='0')
        {
            printf("\nDesea ver los datos en otro orden? s/n\n");
            fflush(stdin);
            scanf("%c", &control);
        }
    }
    while (op!='0' && control=='s'|| control=='S');
}

char mostrarArbolProductosActivos(nodoArbolstProducto * A)
{
    char op;
    char control='s';

    do
    {
        system("cls");

        printf("Como desea ver los productos: ");
        printf("\n1- InOrder.");
        printf("\n2- PreOrder.");
        printf("\n3- PostOrder.");
        printf("\n\n0- Salir.");

        op= ingresarOpcionChar();
        switch (op)
        {
        case '0':
            printf("\n");
            break;
        case '1':
            printf("\n\nProductos Activos:\n");
            inOrdenProductosActivos(A);
            break;
        case '2':
            printf("\n\nProductos Activos:\n");
            preOrdenProductosActivos(A);
            break;
        case '3':
            printf("\n\nProductos Activos:\n");
            postOrdenProductosActivos(A);
            break;

        default:
            printf("El n%cmero ingresado no se encuentra entre las opciones por favor ingr%cselo nuevamente.\n",163,130);
            break;
        }
        if(op!='0')
        {
            printf("\nDesea ver los datos en otro orden? s/n\n");
            fflush(stdin);
            scanf("%c", &control);
        }
    }
    while (op!='0' && control=='s'|| control=='S');

    return op;
}

char mostrarArbolProductosInactivos(nodoArbolstProducto * A)
{
    char op;
    char control='s';

    do
    {
        system("cls");
        printf("Como desea ver los productos: ");
        printf("\n1- InOrder.");
        printf("\n2- PreOrder.");
        printf("\n3- PostOrder.");
        printf("\n\n0- Salir.");

        op= ingresarOpcionChar();
        switch (op)
        {
        case '0':
            printf("\n");
            break;
        case '1':
            printf("\n\nProductos Inactivos:\n");
            inOrdenProductosInactivos(A);
            break;
        case '2':
            printf("\n\nProductos Inactivos:\n");
            preOrdenProductosInactivos(A);
            break;
        case '3':
            printf("\n\nProductos Inactivos:\n");
            postOrdenProductosInactivos(A);
            break;

        default:
            printf("El n%cmero ingresado no se encuentra entre las opciones por favor ingr%cselo nuevamente.\n",163,130);
            break;
        }
        if(op!='0')
        {
            printf("\nDesea ver nuevamente los dato? s/n\n");
            fflush(stdin);
            scanf("%c", &control);
        }
    }
    while (op!='0' && control=='s'|| control=='S');

    return op;
}

void mostrarProductoPorId(nodoArbolstProducto * A, int idProducto)
{

    nodoArbolstProducto * aux= inicArbol();

    aux= buscarProductoArbol(A, idProducto);
    mostrarUnNodoArbol(aux);
}

void mostrarProductoPorNombre(nodoArbolstProducto * A, char nombreProd[])
{

    nodoArbolstProducto * aux= inicArbol();

    aux= buscarProductoArbolPorNombre(A, nombreProd);
    mostrarUnNodoArbol(aux);
}

///FUNCIONES REFERIDAS A USUARIOS Y CONTRASEÑAS -----------------------------------------------------------------------------
int ingresarUsuarioYContrasenia(stCelda adl[], int validos)
{
    char usu[30];
    char contra[30];
    int pos= 0;
    int auxUsu= 0;
    int auxContra= 0;
    char opcion;

    do
    {
        system("cls");
        printf("INICIO DE SESI%cN:\n\n",224);
        printf("Nombre de usuario: ");
        fflush(stdin);
        gets(usu);
        printf("Contrase%ca: ",164);
        fflush(stdin);
        gets(contra);
        pos= validarUsuarioYContrasenia(adl, validos, usu, contra);
        if(pos==-1)
        {
            auxUsu= validarUsuario(adl, validos, usu);
            auxContra= validarContrasenia(adl, validos, contra);
            if(auxUsu==0 && auxContra==0)
                printf("\nUsuario y contrase%ca incorrectas.\n",164);
            else if(auxUsu==1)
                printf("\nContrase%ca incorrecta.\n",164);
            else
                printf("\nUsuario y contrase%ca incorrectas.\n",164);
            printf("ESC para salir de este men%c (cualquier otra letra para volver a intentarlo).\n",163);
            fflush(stdin);
            opcion= getch();
        }
    }
    while(pos==-1 && opcion!=ESC);

    if(pos==-1)
    {
        printf("\nVolviendo al men%c de usuario...\n",163);
        system("pause");
    }
    return pos;
}

int validarUsuarioYContrasenia(stCelda adl[], int validos, char usu[], char contra[])
{
    int flag=0;
    int pos=0;

    while(flag==0 && pos<validos)
    {
        if((strcmpi(adl[pos].cliente.userName, usu)==0) && (strcmpi(adl[pos].cliente.password, contra)==0))
        {
            flag= 1;
        }
        pos++;
    }

    if(flag==0)
    {
        pos=-1;
    }
    else
    {
        pos--;
    }
    return pos;
}

int posUsuarioYContrasenia(stCelda adl[], int validos, char mail[])
{
    int flag=0;
    int pos=0;

    while(pos<validos && flag==0)
    {
        if(strcmpi(mail, adl[pos].cliente.mail)==0)
        {
            flag= 1;
        }
        pos++;
    }

    if(flag==0)
    {
        pos=-1;
    }
    else
    {
        pos--;
    }

    return pos;
}

int recuperarUsuarioYContrasenia(stCelda adl[], int validos)
{
    char mail[30];
    int pos=0;
    char opcion;

    do
    {
        system("cls");
        printf("RECUPERAR USUARIO Y CONTRASE%cA:\n", 165);
        printf("\nIngrese mail de usuario: ");
        fflush(stdin);
        gets(mail);
        pos=posUsuarioYContrasenia(adl, validos, mail);
        if(pos==-1)
        {
            printf("\nEl mail de usuario ingresado no se encuentra en nuestra base de datos.\n");
            if(pos==-1)
            {
                printf("ESC para salir de este men%c (cualquier otra letra para volver a intentarlo).\n",163);
                fflush(stdin);
                opcion= getch();
            }
        }
    }
    while(pos==-1 && opcion!=ESC);
    return pos;
}

void mostrarUsuarioYContrasenia(stCelda adl[], int pos)
{
    printf("\n--------------------------------------------------------------\n");
    printf("Nombre del usuario: %s", adl[pos].cliente.userName);
    printf("\nPassword del usuario: %s", adl[pos].cliente.password);
    printf("\n--------------------------------------------------------------\n");
}

///ARCHIVO A ARREGLOS -----------------------------------------------------------------------------------------------
int bajarArchivoClientesToArreglo(char archClientes[], stCelda adl[])
{
    stCliente cliente;
    int i= 0;

    FILE * puntero;
    puntero= fopen(archClientes, "rb");

    if(puntero)
    {
        while(fread(&cliente, sizeof(stCliente), 1, puntero)>0)
        {
            adl[i].cliente= cliente;
            adl[i].listaDeProductos= inicLista();
            adl[i].listaDeProductos= 0;
            i++;
        }
    }
    else
    {
        printf("\nNo se pudo abrir el archivo.\n");
    }
    fclose(puntero);

    return i;
}


int bajarArchivoPedidoToArreglo(char archPedidos[], stPedido arregloPedidos[])
{
    stPedido pedido;
    int i= 0;

    FILE * puntero;
    puntero= fopen(archPedidos, "rb");

    if(puntero)
    {
        while(fread(&pedido, sizeof(stPedido), 1, puntero)>0)
        {
            arregloPedidos[i]= pedido;
            i++;
        }
    }
    else
    {
        printf("\nNo se pudo abrir el archivo.\n");
    }
    fclose(puntero);

    return i;
}

void bajarArchivoPedidoToADL(char archPedidos[], stCelda adl[], int validos, nodoArbolstProducto * A)
{
    stPedido pedido;
    int i= 0;
    int pos= 0;

    nodoArbolstProducto * aux= inicArbol();

    FILE * puntero;
    puntero= fopen(archPedidos, "rb");

    if(puntero)
    {
        while(fread(&pedido, sizeof(stPedido), 1, puntero)>0 && i<dim)
        {
               pos= compararIdPedidoToADL(adl, validos, pedido.idCliente);
               if(pos!=-1)
               {
                   aux= buscarProductoArbol(A, pedido.idProducto);
                   adl[pos].listaDeProductos= agregarNodoAlPrincipio(adl[pos].listaDeProductos, crearNodoLista(aux->p));
               }
        }
    }
    else
    {
        printf("\nNo se pudo abrir el archivo.\n");
    }
    fclose(puntero);
}

int compararIdPedidoToADL(stCelda adl[], int validos, int idCliente)
{
    int i=0;
    int pos=-1;

    while(i<validos && pos==-1)
    {
        if(idCliente==adl[i].cliente.idCliente)
        {
            pos= i;
        }
        i++;
    }

    return pos;
}


nodoArbolstProducto * bajarArchivoToArbol(char archProductos[], nodoArbolstProducto * A)
{
    stProducto producto;

    FILE * puntero;
    puntero= fopen(archProductos, "rb");

    if(puntero)
    {
        while(fread(&producto, sizeof(stProducto), 1, puntero)>0)
        {
            A= FormarArbol(A, producto);
        }
    }
    else
    {
        printf("\nNo se pudo abrir el archivo.\n");
    }
    fclose(puntero);

    return A;
}


///CONTROL ELIMINADO CLIENTE -------------------------------------------------------------------------------------------
int clienteDadoDeBaja (stCelda adl[], int pos)
{
    int activo=0;

    activo= adl[pos].cliente.eliminado;

    return activo;
}

///ARCHIVO ---------------------------------------------------------------------------------------------------------------
void pasarArregloClientesToArchivo(char archCliente[], stCelda adl[], int validosCl)
{
    int i= 0;

    stCliente cliente;

    FILE * puntero;
    puntero= fopen(archCliente, "w+b");

    if(puntero)
    {
        while(i<validosCl)
        {
            cliente= adl[i].cliente;
            fwrite(&cliente, sizeof(stCliente), 1, puntero);
            i++;
        }
    }
    else
    {
        printf("\nNo se pudo abrir el archivo.\n");
    }
    fclose(puntero);
}

void actualizarPedidosToArchivo(char archPedidos[], stCelda adl[], int validos)
{
    stPedido pedido;
    int i= 0;

    int idPed= 0;

    FILE * puntero;
    puntero= fopen(archPedidos, "w+b");

    if(puntero)
    {
        while(i<validos)
        {
            while(adl[i].listaDeProductos)
            {
                pedido.idPedido= idPed + 1;
                idPed= pedido.idPedido;
                pedido.idCliente=adl[i].cliente.idCliente;
                pedido.idProducto=adl[i].listaDeProductos->p.idProducto;
                fwrite(&pedido, sizeof(stPedido), 1, puntero);
                adl[i].listaDeProductos= adl[i].listaDeProductos->siguiente;
            }
            i++;
        }
    }
    else
    {
        printf("\nNo se pudo abrir el archivo.\n");
    }
    fclose(puntero);
}

int productoMasSeRepite(nodoListaProducto * lista)
{
    int contador= 0;
    int mayor= 0;
    int id= 0;

    nodoListaProducto * aux= inicLista();
    aux= lista;
    nodoListaProducto * inicial= inicLista();
    inicial= lista;

    while(aux)
    {
        if(lista->p.idProducto==aux->p.idProducto)
        {
            contador++;
        }
        aux= aux->siguiente;
    }

    mayor= contador;
    id= lista->p.idProducto;

    contador= 0;

    aux= inicial;
    inicial= lista->siguiente;

    while(inicial)
    {
        if(inicial->p.idProducto==aux->p.idProducto)
        {
            contador++;
        }
        aux= aux->siguiente;
        if(aux==NULL)
        {
            if(mayor<contador)
            {
                id= inicial->p.idProducto;
                mayor= contador;
            }

            inicial= inicial->siguiente;
            aux= inicial;
            contador= 0;
        }
    }
    return id;
}

void mostrarProductosRecomendados(nodoArbolstProducto * A, char marca[])
{
    nodoArbolstProducto * buscado= NULL;

    if(A)
    {
        if(strcmp(A->p.marca, marca)==0)
        {
            buscado= A;

            mostrarUnNodoArbol(buscado);
            mostrarProductosRecomendados(A->izq, marca);
            mostrarProductosRecomendados(A->der, marca);
        }
        else
        {
            mostrarProductosRecomendados(A->izq, marca);
            mostrarProductosRecomendados(A->der, marca);
        }
    }
}
