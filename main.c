#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include "list.h"
#include "Map.h"
#include "treemap.h"

//------------------STRUCT-------------------------//

typedef struct {
	int idLibro;
	char *nombreLibro;
}LibrosConPalabra;

typedef struct {
	char *palabra;
	unsigned long ocurrenciaPalabra;
	List *librosConPalabra;
}Palabra;

typedef struct {
	char *String;
	unsigned long ocurrenciaString;
	long *frecuencia;
	long *relevancia;
}PalabraEnLibro;

typedef struct {
	int idBook;
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

/*------- Obtener palabras por espacio -------*/
char *get_string_noSpace(char *tmp, int k) {
	char *ret = (char *)malloc(100 * sizeof(char)); //Cadena de retorno
	int ini_i = 0, i = 0; //indice inicial e indice relativo al campo
	int j = 0; //Indice del campo en la cadena leida
	int cont = 0; //Si es 0, es el primer caracter del string
	while (tmp[i] != '\n') {
		
		if (tmp[i] != ' '){ 
			//Comprueba si tmp[i] no es un espacio o una coma
			if (k == j){
				if(cont == 0){
					ret[i - ini_i] = toupper(tmp[i]);
					//Guarda el caracter en la cadena de retorno en mayuscula
					cont = 1;
				}
				else{
					ret[i - ini_i] = towlower(tmp[i]);
					//Guarda el caracter en la cadena de retorno en minuscula
				}
			}
			i++;
			continue;
		}

		if (tmp[i] == ' '){
			if (k == j) { //Comprueba que el indice del campo coincida con el leido actualmente
				ret[i - ini_i] = '\0'; //Añade el caracter nulo
				return ret;
			}
			j++; //Se aumenta el indice del campo leido actualmente
			ini_i = i + 1;
		}
		i++;
	}

	if (k == j) { //Ultimo if seria para retornar en caso de que el campo a ser leido sea el ultimo
		ret[i - ini_i] = '\0';
		return ret;
	}

	return NULL;
}
//-----------------------------------------//


/*------- Abrir o no el archivo -------*/
int esText(char *nombreArchivo, char *archiveToOpen){
	int cont = 0;
	char *Abrir;
	while ((Abrir = get_string_noSpace(archiveToOpen,cont)) != NULL)
	{
		if (strcmp(Abrir, nombreArchivo) == 0)
		{
			return 1;
		}
		cont++;
	}

	return 0;
}
//-----------------------------------------//

/*------- Crear Struct Palabra -------*/
Palabra *get_palabra(char *cadenaCharacter, char* title, char*id){
	Palabra *String = (Palabra*) malloc(sizeof(Palabra));
	String->ocurrenciaPalabra = 1;
	String->librosConPalabra = createList();
	strcpy(String->palabra, cadenaCharacter);
	LibrosConPalabra *StrInBook = (LibrosConPalabra*) malloc(sizeof(LibrosConPalabra));
	StrInBook->idLibro = atoi(id);
	strcpy(StrInBook->nombreLibro, title);
	pushBack(String->librosConPalabra, StrInBook);
	return String;
}
//-----------------------------------------//

/*------- Leer Archivo -------*/
void ReadTxt(TreeMap* string_map, TreeMap* book_map, char*name){
	// Abre un archivo especifico y guarda sus datos
	size_t largo = strlen(name);
	char g[largo];
	strcpy(g, "./Libros/");
	largo += strlen(g);
	char *nameFile = (char*) calloc(largo, sizeof(char));
	strcpy(nameFile, strcat(g,name));
	nameFile = (char*) realloc(nameFile, sizeof(char) * largo);
    FILE *F = fopen(nameFile, "r"); // Abre el archivo con el nombre recibido en modo lectura
    
	if (!F){return;}// Si no existe el archivo, cierra el programa
	printf("abierto\n");
	char linea[1024]; // Cadena de caracter para guardar una linea del archivo
	char *palabra;
	int save = 0;
	int cont = 0;
	Palabra *aux;
	Palabra *stringSave;
	LibrosConPalabra *auxiliar;
	char titulo[500];

	while (fgets(linea, 1023, F) != NULL) { 
        // Recorre el archivo leyendo linea por linea
        // guardando los datos de cada linea en listas
		if (save == 0) {
			printf("%s", get_string_noSpace(linea,0));
			if(strcmp(get_string_noSpace(linea,0), "Title:") != 0) continue;
			for (size_t i = 6; i < strlen(linea); i++)
			{
				titulo[i] = linea[i];
			}
			printf("%s \n", titulo);
			save = 1;
			continue;
		}
		cont = 0;
		while ((palabra = get_string_noSpace(linea,cont)) != '\0')
		{
			if ((aux = searchTreeMap(string_map, palabra)) == NULL)
			{
				stringSave = get_palabra(palabra, titulo, name);
				insertTreeMap(string_map, stringSave->palabra, stringSave);
			}
			else{
				aux->ocurrenciaPalabra++;
				auxiliar = firstList(aux->librosConPalabra);
				while (auxiliar != NULL)
				{
					if (atoi(name) == auxiliar->idLibro) break;
					auxiliar = nextList(aux->librosConPalabra);
				}
				if (auxiliar == NULL)
				{
					auxiliar->idLibro = atoi(name);
					auxiliar->nombreLibro = titulo;
					pushBack(aux->librosConPalabra, auxiliar);
				}
			}


			cont++;
		}
		
		
	}
	
	fclose(F);// Se cierra el archivo
}
//-----------------------------------------//

/*----------------- OPCIÓN 1: -----------------*/
void CargarDocumento(TreeMap *palabrasMap, TreeMap *librosMap){
    DIR *carpeta;
	struct dirent *dirp;
	char *ubicacion = "c:/Users/lucas/OneDrive/Escritorio/Tarea3_Huachipato/Libros";
    printf("Escriba el nombre de los textos\n");
	char Archives[100];
	fgets(Archives,100,stdin);
	printf("\n");
    carpeta = opendir(ubicacion);
	while ((dirp = readdir(carpeta)) != NULL){
		if(esText(dirp->d_name, Archives) == 0) continue;
		ReadTxt(palabrasMap, librosMap, dirp->d_name);
	}
}
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

/*------- Mostrar palabras -------*/
void MostrarPalabras(int *mostrados, char* buscando, TreeMap *mapa){
	Palabra *aux = firstTreeMap(mapa);
	int EsIgual = 1;
	LibrosConPalabra *mostrar;
	printf("\n\n%s\n\n", aux->palabra);
	while (aux != NULL)
	{
		for (size_t i = 0; i < strlen(buscando) - 1; i++)
		{
			if (buscando[i] == ' ') {break;}
			
			if (buscando[i] != aux->palabra[i])
			{EsIgual = 0; break;}
		}
		if (EsIgual)
		{
			printf("\nLa palabra %s esta en los siguientes libros\n", aux->palabra);
			mostrar = firstList(aux->librosConPalabra);
			while (mostrar != NULL)
			{
				printf("  %s\n", mostrar->nombreLibro);
				mostrar = nextList(aux->librosConPalabra);
			}
			(*mostrados)++;
		}
		aux = nextTreeMap(mapa);
	}
}
//-----------------------------------------//

/*----------------- OPCIÓN 6: -----------------*/
void BuscarPorPalabra(TreeMap *palabras_map){
	char Frase[1000];
	while (1)
	{
		printf("Escriba la palabra a buscar (Las palabras no tienen espacios)\n");
		scanf("%[0-9a-zA-Z ,-]", Frase);
		getchar();
		if (get_string_noSpace(Frase, 1) == NULL || get_string_noSpace(Frase,1) == '\0'){
			printf("Su palabra no es viable a la busqueda");
		}
		else break;
	}
	int cont = 0;
	MostrarPalabras(&cont, get_string_noSpace(Frase, 0), palabras_map);
	if (cont = 0)
	{
		printf("No se encontro ninguna palabra");
	}
	
}
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
			CargarDocumento(palabrasGeneral, librosNombre);
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
			BuscarPorPalabra(palabrasGeneral);
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