#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <windows.h>
#define MAX_ID_ELIMINADOS 100
#define PASSWORD "admin"

//DECLARACION DE FUNCONES
void gotoxy();
void recuadro();
void recuadroPequeno();
void limpiarPantalla();
void centrarTexto();

void agregar();
void imprimir();
void modificar();
void buscar();
void eliminar();
void vender();
void productos();
void limpiarLista();
int menu();

//declaracion estandar
typedef struct nodo{
    
    char nombre[20];
    int cantidad;
    float precio;
    int ID;
    float ganancias;
    
    struct nodo *siguiente;
}nodo;

//--DECLARACION DE VARIABLES GLOBALES--------------------------------------
nodo *lista = NULL;
int contID = 1;
int idsEliminados[MAX_ID_ELIMINADOS];
int contadorEliminados = 0;
//--------------------------------------------------------------------------
nodo* crearnodo(const char* nombre, int cantidad, float precio) {
    nodo* nuevonodo = (nodo*)malloc(sizeof(nodo));
    
    strcpy(nuevonodo->nombre, nombre);
    nuevonodo->cantidad = cantidad;
    nuevonodo->precio = precio;
    nuevonodo->siguiente = NULL;
    
    return nuevonodo;
}

void imprimirPagina(nodo *inicio, int elementosEnPagina);

int main(){
	int opc = 0;
	char password[sizeof(PASSWORD)];
    int attempts = 0;

	
    while(attempts < 3) {
    	recuadro(0,0,119,28);
		recuadroPequeno(10, 3, 110, 5);
        printf("\n\n\t\tPor favor, introduce la contraseña: ");
        scanf("%5s", password); // Limitamos la entrada a la longitud de la contraseña
        
        if(strcmp(password, PASSWORD) == 0) {
            printf("Contraseña correcta.\n");
            // Aquí va el resto de tu programa
           	while(opc != 9){
			system("mode con: cols=120 lines=30");
	
			recuadro(0,0,119,28);
			recuadroPequeno(10, 3, 110, 5);
	
			printf("\n\n");		
    		opc = menu();
		}
	
	recuadro(0,0,119,28);
	recuadroPequeno(10, 3, 110, 5);
	centrarTexto(60,20, "Cargando...");
	return 0;
        } else {
            attempts++;
            printf("Contraseña incorrecta. Te quedan %d intentos.\n", 3 - attempts);
        }
        
        getchar();
    	getchar();
    	limpiarPantalla();
    }
}

//FUNCION DEL MENU
int menu(){
	HWND consoleWindow = GetConsoleWindow();
    // Cambiar el título de la ventana de la consola
    SetConsoleTitle("DULCERIA HABBIBI");
	int opc;
		
		printf("\t\t\t  |====================================================================|");
		printf("\n\t\t\t  |                     La mejor dulceria del pais                    |");
		printf("\n\t\t\t  |                    Tipo de acceso: administrador                   |");
		printf("\n\t\t\t  |--------------------------------------------------------------------|");
        printf("\n\t\t\t  | 1.Agregar Mercancia              |   4.Eliminar Articulo           |");
        printf("\n\t\t\t  |                                  |                                 |");
		printf("\n\t\t\t  | 2.Modificar Inventario           |   5.Vender Producto             |");
		printf("\n\t\t\t  |                                  |                                 |");
		printf("\n\t\t\t  | 3.Buscar Articulo                |   6.Mostrar Productos           |");
		printf("\n\t\t\t  |                                                                    |");
		printf("\n\t\t\t  |                                                                    |");
		printf("\n\t\t\t  |                                                                    |");
		printf("\n\t\t\t  | 9.Salir                                                            |");
		printf("\n\t\t\t  |--------------------------------------------------------------------|");
		printf("\n\n\t\t\t  Escoja una opcion: ");
		scanf("%d",&opc);
		limpiarPantalla();
		
		recuadro(0,0,119,28);
	    recuadroPequeno(10, 3, 110, 5);
	    
		switch(opc){
			
			case 1:
			agregar();
			break;
				
			case 2:
			modificar();
			break;
					
			case 3:
			buscar();
			break;
						
			case 4:
			eliminar();
			break;
			
			case 5:
			vender();
			break;
			
			case 6:
			productos();
			break;
			
			case 9:
			break;	
			
		    default:
		    recuadro(0,0,119,28);
	        recuadroPequeno(10, 3, 110, 5);
			system("cls");
			printf("\n\nOpcion Invalida");
			break;
		    }
		    
		return opc;
		}

// Función para agregar
void agregar() {
    char nombre[20];
    int cantidad;
    float valor;

    printf("\n\n");
    printf("\n\t\t\t  |----------------------------------------------------------------------|");
    printf("\n\t\t\t  |                       agregando nuevo producto...                    |");
    printf("\n\t\t\t  |----------------------------------------------------------------------|");

    printf("\n\t\t\t   Nombre del producto: ");
    getchar();
    fgets(nombre, sizeof(nombre), stdin);
    int len = strlen(nombre);
    if (len > 0 && nombre[len - 1] == '\n') {
        nombre[len - 1] = '\0';
    }
    printf("\t\t\t  \n");
    printf("\t\t\t  \n");

    printf("\t\t\t   Cantidad del producto: ");
    scanf("%d", &cantidad);
    printf("\t\t\t  \n");
    printf("\t\t\t  \n");
    
    printf("\t\t\t   Precio del producto: ");
    scanf("%f", &valor);
    printf("\t\t\t  \n");
    printf("\t\t\t  \n");

    nodo *nuevo = crearnodo(nombre, cantidad, valor);
    
       // Asignar el próximo ID disponible
    if (contadorEliminados > 0) {
        nuevo->ID = idsEliminados[--contadorEliminados];
    } else {
        nuevo->ID = contID++;
    }

    nuevo->siguiente = NULL;

    // Si la lista está vacía, el nuevo nodo se convierte en la lista
    if (lista == NULL) {
        lista = nuevo;
    } else {
        nodo *actual = lista;
        while (actual->siguiente != NULL) {
            actual = actual->siguiente;
        }
        actual->siguiente = nuevo;
    }

    printf("\t\t\t  \n\t\t\t  \n\t\t\t  \n\t\t\t  \n");
    printf("\t\t\t  |----------------------------------------------------------------------|");
    printf("\n\t\t\t  |                    Producto agregado exitosamente                    |");
    printf("\n\t\t\t  |----------------------------------------------------------------------|");

    getchar();
    getchar();
}

// Función para modificar
void modificar(){
    nodo *actual = lista;
    int aux, menu, cantidad;
    float precio;
    char nombre[50];
    
    imprimir();
    printf("\n\t\t\t Introduzca el ID del producto a modificar ");
    scanf("%d", &aux);
    
    while(actual != NULL && aux != 0){

        if(actual -> ID == aux){
                                    
            printf("\t\t\t¿Que desea modificar?\n");
            printf("\t\t\t1)Nombre\n");
            printf("\t\t\t2)Cantidad\n");
            printf("\t\t\t3)Precio\n");
            printf("\t\t\t0)Salir\n");
            scanf("%d", &menu);
            
            switch(menu){
                
                case 1:   			
                printf("\t\t\tNuevo nombre: ");
                getchar();
                fgets(nombre, sizeof(nombre), stdin);
                int len = strlen(nombre);
                
    			if (len > 0 && nombre[len - 1] == '\n') {
        			nombre[len - 1] = '\0';
   					}
                strcpy(actual->nombre, nombre);
                break;
                
                case 2:
                printf("\t\t\tcantidad: ");
                scanf("%d", &cantidad);
                actual -> cantidad = cantidad;
                break;
                
                case 3:
                printf("\t\t\tprecio: ");
                scanf("%f", &precio);
                actual -> precio = precio;
                break;
                
                case 0:
                break;
                
                default:
                printf("opcion invalida");
                break;
            }                    
        }
        actual = actual -> siguiente;
    }
}

//funcion para eliminar productos
void eliminar() {
    nodo *actual = lista;
    nodo *anterior = NULL; // Necesitas un puntero para el nodo anterior para poder enlazar correctamente

    imprimir();
    printf("\n\t\t\t Introduzca el ID del producto a eliminar: ");
    int aux;
    scanf("%d", &aux);

    while (actual != NULL) {
        if (actual->ID == aux) {
            // Agregar el ID al arreglo de IDs eliminados
            if (contadorEliminados < MAX_ID_ELIMINADOS) {
                idsEliminados[contadorEliminados++] = actual->ID;
            }

            // Eliminar el nodo y enlazar correctamente
            if (anterior != NULL) {
                anterior->siguiente = actual->siguiente;
            } else {
                // Si el nodo a eliminar es el primero, actualiza lista
                lista = actual->siguiente;
            }

            free(actual);
            printf("\n\t\t\t Producto eliminado exitosamente\n");
            return;
        }

        anterior = actual;
        actual = actual->siguiente;
    }

    printf("\n\t\t\t Producto no encontrado\n");
}

// Función para imprimir
void imprimir(){
    
    nodo *actual = lista;
    int aux = 0;
    printf("\n");
    printf("\n\t\t  |--------------------------------------------------------------------------------|");
    printf("\n\t\t  |                               Productos almacenados                            |");
    printf("\n\t\t  |--------------------------------------------------------------------------------|");
    printf("\n\n\t\t%-20s%-20s%-20s%-10s", "Nombre", "Cantidad", "Precio", "ID");
    
    while(actual != NULL && aux < 4){
    printf("\n\t\t%-20s%-20d%-20.2f%-10d", actual->nombre, actual->cantidad, actual->precio, actual->ID);   
    actual = actual -> siguiente;
    aux = aux +1;
    }  
    printf("\n\n");
}

// Función para buscar
void buscar(){
    nodo *actual = lista;
    int buscarID;
     
    printf("\n\n\n\t\t\t\tEscriba el ID del producto a buscar: ");
    scanf("%d", &buscarID);
    printf("\n\t\t\t\tBuscando producto... ");
    
    while(actual != NULL){        
        if(actual -> ID == buscarID){
        printf("Producto encontrado\n\n");
        printf("\n\t\t\t\tNombre del productos: %s\n", actual -> nombre);
        printf("\n\t\t\t\tcantidad del productos: %d\n", actual -> cantidad);
        printf("\n\t\t\t\tPrecio del productos: %.2f\n", actual -> precio);
        printf("\n\t\t\t\tID del producto %d\n", actual -> ID);
        printf("\n\t\t\t\tGanancias totales del producto: %.2f", actual -> ganancias);      
        break;
        }
        
        actual = actual -> siguiente;
        if(actual == NULL){
        	printf("Producto no encontrado\n");
        	printf("Presione enter para regresar al menu principal");	
		}
    }
    
    getchar();
    getchar();
}

//funcion para vender productos
void vender(){
    nodo *actual = lista;
    int cantidad, ID;
	
	printf("\n\n\n\t\t\t\tEscriba el ID del producto a vender: ");
	scanf("%d", &ID);	
    
    while(actual != NULL){
        if(actual->ID == ID){        	
        	printf("\n\t\t\t\tEscriba la cantidad de producto a vender: ");
			scanf("%d", &cantidad);
			
            if(actual->cantidad >= cantidad){
                actual->cantidad -= cantidad;
                actual->ganancias = actual->precio * cantidad + actual->ganancias;
                
                printf("\n\t\t\t\t----------------------------------\n");
                printf("\t\t\t\tNombre: %s\n", actual->nombre);
                //printf("Categoria: %s\n", actual->categoria);
                printf("\n\t\t\t\tID: %d\n", actual->ID);
                printf("\n\t\t\t\tCantidad restante: %d\n", actual->cantidad);
                printf("\n\t\t\t\tPrecio: %.2f\n", actual->precio);
                printf("\n\t\t\t\tGanancia: %.2f\n", actual->precio * cantidad);
                printf("\n\t\t\t\t----------------------------------\n");
            }else{
                printf("\n\t\t\t\tNo hay suficientes unidades en existencia.\n");
                return;
            }
            
        }
        actual = actual->siguiente;
    }
    getchar();
    getchar();
}
	
// Función para imprimir una página de la lista
// Función para imprimir una página de la lista
void imprimirPagina(nodo *inicio, int elementosEnPagina) {
    nodo *actual = inicio;
    int contador = 0;
    printf("\n\n\t\t%-20s%-20s%-20s%-10s", "Nombre", "Cantidad", "Precio", "ID");
    while (actual != NULL && contador < elementosEnPagina) {
        printf("\n\t\t%-20s%-20d%-20.2f%-10d", actual->nombre, actual->cantidad, actual->precio, actual->ID);
        actual = actual->siguiente;
        contador++;
    }
}

// Función para avanzar en la lista enlazada
nodo *avanzarLista(nodo *inicio, int pasos) {
	int i;
    for ( i = 0; i < pasos && inicio != NULL; ++i) {
        inicio = inicio->siguiente;
    }
    return inicio;
}

void productos(){
    // La función imprimir ahora usa la paginación
    int elementosPorPagina = 10;
    nodo *actual = lista;
    
	if (lista == NULL) {
    printf("\n\n\n\t\t\tLa lista de productos esta vacia\n");
    printf("\n\n\t\t\tPresione enter para salir");
    getchar();
    getchar();
    return;
    }
    
    while (actual != NULL) {
    	recuadro(0,0,119,28);
		recuadroPequeno(10, 3, 110, 5);
        imprimirPagina(actual, elementosPorPagina);

        printf("\n\n\t\tOpciones:\n");
        printf("\t\t1. Avanzar\n");
        printf("\t\t2. Retroceder\n");
        printf("\t\t3. Salir\n\n");

        int opcion;
        printf("\t\tSelecciona una opcion: ");      
        scanf("%d", &opcion);
        system("cls");

        switch (opcion) {
            case 1:
                // Avanzar a la siguiente página
                actual = avanzarLista(actual, elementosPorPagina);
                break;

            case 2:
                // Retroceder a la página anterior
                actual = avanzarLista(lista, -elementosPorPagina);
                break;

            case 3:
                return;

            default:
                printf("Opción no válida. Inténtalo de nuevo.\n");
                break;
        }
    }
}

//FUNCION GOTOXY
void gotoxy(int x, int y){
	HANDLE hcon;
	hcon = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD dwPos;
	dwPos.X = x;
	dwPos.Y= y;
	SetConsoleCursorPosition(hcon,dwPos);
}

void recuadro(int xs, int ys, int xi, int yi){
	// Ajustar los valores dentro de los límites de la ventana
	if (xs < 1) xs = 1;
	if (ys < 1) ys = 1;
	if (xi > 120) xi = 120;
	if (yi > 30) yi = 30;
	
	// Dibujar el recuadro
	int i;
	
	for(i=xs;i<=xi;i++){
		gotoxy(i,ys); printf("%c",196);
		gotoxy(i,yi); printf("%c",196);
	}
	
	for(i=ys;i<=yi;i++){
		gotoxy(xs,i); printf("%c",179);
		gotoxy(xi,i); printf("%c",179);
	}
	
	gotoxy(xs, ys); printf("%c",218);
	gotoxy(xi, ys); printf("%c",191);
	gotoxy(xs, yi); printf("%c",192);
	gotoxy(xi, yi); printf("%c",217);
}

void recuadroPequeno(int xs, int ys, int xi, int yi){
	// Ajustar los valores dentro de los límites del recuadro principal
	if (xs < 1) xs = 1;
	if (ys < 1) ys = 1;
	if (xi > 119) xi = 119;
	if (yi > 28) yi = 28;
	
	// Dibujar el recuadro pequeño
	int i;
	
	for(i=xs;i<=xi;i++){
		gotoxy(i,ys); printf("%c",196);
		gotoxy(i,yi); printf("%c",196);
	}
	
	for(i=ys;i<=yi;i++){
		gotoxy(xs,i); printf("%c",179);
		gotoxy(xi,i); printf("%c",179);
	}
	
	gotoxy(xs, ys); printf("%c",218);
	gotoxy(xi, ys); printf("%c",191);
	gotoxy(xs, yi); printf("%c",192);
	gotoxy(xi, yi); printf("%c",217);
	
	// Escribir el título dentro del recuadro pequeño
	gotoxy((xi - xs + 1 - strlen("D U L C E R I A   H A B I B I")) / 2 + xs, ys + 1);
	printf("D U L C E R I A   H A B I B I");
}

void centrarTexto(int x, int y, const char* texto){
    int longitudTexto = strlen(texto);
    int anchoVentana = 120;  // Ancho de la ventana
    int posicionX = x - longitudTexto / 2;  // Calcular la posición X para centrar el texto
    
    gotoxy(posicionX, y);
    printf("%s", texto);
}

void limpiarLista(){
    nodo* actual = lista;
    nodo* siguiente;

    while (actual != NULL) {
    	
        siguiente = actual->siguiente;
		free(actual);
        actual = siguiente;
    }

    lista = NULL;
}

void limpiarPantalla() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}
