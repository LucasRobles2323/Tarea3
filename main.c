#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"
#include "Map.h"
#include "treemap.h"

//------------------STRUCT-------------------------//

typedef struct {
	char *palabra;
	unsigned long *ocurrenciaPalabra;
}Palabra;

typedef struct {
	Palabra *palabraInBook;
	long *frecuencia;
	long *relevancia;
}PalabraEnLibro;

typedef struct {
	int *idBook;
	char *nameBook;
	unsigned long cantPalabrasBook;
	List *palabrasEnLibro;
}Libro;

//------------------FUNCIONES-------------------------//

/*
  función para comparar claves de tipo string
  retorna 1 si son iguales
*/
int is_equal_string(void * key1, void * key2) {
    if(strcmp((char*)key1, (char*)key2)==0) return 1;
    return 0;
}

/*
  función para comparar claves de tipo string
  retorna 1 si son key1<key2
*/
int lower_than_string(void * key1, void * key2) {
    if(strcmp((char*)key1, (char*)key2) < 0) return 1;
    return 0;
}

/*
  función para comparar claves de tipo int
  retorna 1 si son iguales
*/
int is_equal_int(void * key1, void * key2) {
    printf("%d\n\n", key2);
    if(*(int*)key1 == *(int*)key2) return 1;
    return 0;
}

/*
  función para comparar claves de tipo int
  retorna 1 si son key1<key2
*/
int lower_than_int(void * key1, void * key2) {
    if(*(int*)key1 < *(int*)key2) return 1;
    return 0;
}



/*------- Crear Mapa de String -------*/
TreeMap *crearMapaString() {
	// Crea y retorna un mapa adecuado para usar string como claves.
    TreeMap *mapBalanceado = createTreeMap(is_equal_string);
	return mapBalanceado;
}
//-----------------------------------------//

/*------- Advertencia -------*/
void Advertencia() {
	// Imprime una advertencia en pantalla antes de iniciar.
    printf("\n\nAntes de empezar, siempre que se le pida datos, evite usar: \n");
	printf(" Vocales con tilde, procure no poner nunca tilde \n");
	printf(" La letra '%c', de ser necesaria utilice 'ny' \n", 164);
	printf(" El simbolo de inicio de pregunta %c, simplemente no lo ponga \n", 168);
}
//-----------------------------------------//

/*------- Presionar Enter -------*/
void pressEnter(int opcion){
	// Funcion que detiene temporalmente el programa 
	// hasta que el usuario presione enter.
	printf("\n\nPresione ENTER");
	if(opcion == 1){printf(" para volver al men%c",163);}
	getchar();
	printf("\n\n");
}
//-----------------------------------------//

/*------- Mostrar Menú -------*/
void MostrarMenu(){
	//Muestra las opciones del menu y un mensaje para que seleccione una opcion,
	printf("\n\n");
	printf("1.- Cargar documentos\n");
	printf("2.- Mostrar documentos ordenados\n");
	printf("3.- Buscar un libro por titulo\n");
	printf("4.- Palabras con mayor frecuencia\n");
	printf("5.- Palabras mas relevantes\n");
	printf("6.- Buscar por palabras\n");
	printf("7.- Mostrar palabra en su contexto dentro del libro\n");
	printf("8.- Salir\n");
	printf("Introduzca una opci%cn: ", 162);
}

/*------- Copiar string en un nuevo espacio de memoria -------*/
char * _strdup(const char * str){
	// Recibe un string y la copia en una string nueva con una direccion de 
	// memoria nueva y retorna la nueva string.
    char * aux = (char *)malloc(strlen(str) + 1);
    strcpy(aux, str);
    return aux;
}
//-----------------------------------------//


//**************************  OPCIÓN 1  ***********************//

/*-------  -------*/
//-----------------------------------------//

/*----------------- OPCIÓN 1: -----------------*/
//-------------------------------------------------------------//

//**************************************************************//



//**************************  OPCIÓN 2  ***********************//

/*-------  -------*/
//-----------------------------------------//

/*----------------- OPCIÓN 2: -----------------*/
//-------------------------------------------------------------//

//**************************************************************//



//**************************  OPCIÓN 3  ***********************//

/*-------  -------*/
//-----------------------------------------//

/*----------------- OPCIÓN 3: -----------------*/
//-------------------------------------------------------------//

//**************************************************************//



//**************************  OPCIÓN 4  ***********************//

/*-------  -------*/
//-----------------------------------------//

/*----------------- OPCIÓN 4: -----------------*/
//-------------------------------------------------------------//

//**************************************************************//




//**************************  OPCIÓN 5  ***********************//

/*-------  -------*/
//-----------------------------------------//

/*----------------- OPCIÓN 5: -----------------*/
//-------------------------------------------------------------//

//**************************************************************//



//**************************  OPCIÓN 6  ***********************//

/*-------  -------*/
//-----------------------------------------//

/*----------------- OPCIÓN 6: -----------------*/
//-------------------------------------------------------------//

//**************************************************************//



//**************************  OPCIÓN 7  ***********************//

/*-------  -------*/
//-----------------------------------------//

/*----------------- OPCIÓN 7: -----------------*/
//-------------------------------------------------------------//

//**************************************************************//








//------------------MAIN-------------------------//

int main() {
	// Crea los 4 mapas que se podrian usar a lo largo del codigo
	TreeMap *palabrasGeneral = crearMapaString();
	TreeMap *librosNombre = crearMapaString();

	int option = 0; //Variable que decide la opcion del menun seleccionada

	Advertencia();
	pressEnter(0);

	while (option != 12) { // Muestra el menu y actua segun la opcion seleccionada 
		MostrarMenu();
		
		scanf("%d", &option);
		getchar(); /* Importante poner getchar luego de cada scanf pues de lo 
        contrario un futuro scanf leera un '\n' y no recibira el input */

		if (option == 8) {break;} //Sale del while si la opcion escogida en el menu era Salir

		printf("\n\n");

		switch (option){// Entra a la opcion seleccionada para llevarla a cabo
		case 1:
            /*------- Cargar documentos -------*/
			break;
            //-----------------------------------------//
        case 2:
			/*------- Mostrar documentos ordenados -------*/
			break;
			//-----------------------------------------//
        case 3:
            /*------- Buscar un libro por titulo -------*/
            break;
			//-----------------------------------------//
		case 4:
			/*------- Palabras con mayor frecuencia -------*/
			break;
			//-----------------------------------------//
		case 5:
			/*------- Palabras mas relevantes -------*/
			break;
			//-----------------------------------------//
		case 6:
			/*------- Buscar por palabra -------*/
			break;
			//-----------------------------------------//
		case 7:
			/*------- Mostrar palabra en su contexto dentro del libro -------*/
			break;
			//-----------------------------------------//
        default:
			/*------- Opcion no valida -------*/
			printf("Opci%cn inv%clida", 162, 160);
			break;
			//-----------------------------------------//
        }

		pressEnter(1);
		
	}

	return 0;
}

// Funciones que no estan en el siguiente formato:
/*------- Opcion del menu -------*/
//-----------------------------------------//
// Es porque la(s) funcion(s) necesarias 
// se crearon en la(s) funcion(es) de una opcion 
// anterior, lo mismo si falta en las funciones de la opcion