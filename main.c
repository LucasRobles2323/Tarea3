#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <dirent.h>
#include <math.h>
#include <sys/types.h>
#include <sys/stat.h>
#include "list.h"
#include "Map.h"

//------------------STRUCT-------------------------//

typedef struct {
	int idLibro;
	char *nombreLibro;
	unsigned long ocurrenciaEnLibro;
	double relevancia;
}LibrosConPalabra; // Struct que guarda los datos de cada libro para una palabra especifica

typedef struct {
	char *palabra;
	unsigned long ocurrenciaPalabra;
	unsigned long LibrosWithPalabra;
	List *ConPalabra;// Lista de struct LibrosConPalabras
}Palabra; //Struct que guarda los datos de una palabra para el mapa de palabras

typedef struct {
	char *String;
	float ocurrenciaString;
	double frecuencia;
	double relevancia;
}PalabraEnLibro; // Struct que guarda los datos de cada palabra para un libro especifico

typedef struct {
	int idBook;
	char *nameBook;
	unsigned long cantPalabrasBook;
	unsigned long long cantCaracteresBook;
	List *EnLibro; // Lista de struct PalabraEnLibro
}Libro; //Struct que guarda los datos de un libro para el mapa de libro

typedef struct{
	List *palabra;
	float relevancia;
}PalabraRelevante;

typedef struct{
	Map *PalabraRelevante; 
	char *titulo;
	int numeroDocumentos;
}Relevancia;

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
    if(*(float*)key1 == *(float*)key2) return 1;
    return 0;
}

/*
  función para comparar claves de tipo long
  retorna 1 si son key1<key2
*/
int lower_than_int(void * key1, void * key2) {
    if(*(float*)key1 > *(float*)key2) return 1;
    return 0;
}

/*
  función para comparar claves de tipo long
  retorna 1 si son iguales
*/
long is_equal_long(void * key1, void * key2) {
    if(*(long*)key1 == *(long*)key2) return 1;
    return 0;
}

/*
  función para comparar claves de tipo int
  retorna 1 si son key1<key2
*/
long lower_than_long(void * key1, void * key2) {
    if(*(long*)key1 < *(long*)key2) return 1;
    return 0;
}


/*
función que retorna negativo si queremos que key1 vaya antes que key2 
en el mapa, retorna 0 si consideramos que las dos claves son iguales 
y positivo si key1 debe ir antes.
*/
int compare(void * key1, void * key2) {
    const int* Key1 = key1;
    const int* Key2 = key2;
    return (*Key1 - *Key2);
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
	printf("  ");
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

/*----------------- Lista con los text a abrir -----------------*/
List *cantArchiveOpen(char *Archives, size_t *cant){ //Crea una lista con las palabras separadas por espacio
	List *newList = createList();
    char *Text = strtok(Archives, " ");
	while (Text != NULL)
	{
        pushBack(newList, strdup(Text));
        (*cant)++;
		Text = strtok(NULL, " ");
	}
	Text = lastList(newList);
	Text = strtok(Text, "\n");
    return newList;
}
//-----------------------------------------//

/*------- Abrir o no el archivo -------*/
int esText(char *nombreArchivo, List *archiveToOpen, size_t *cant){//Confirma si abrir un archivo del directorio
    char *OpenYoN = (char*)firstList(archiveToOpen);
	while (OpenYoN != NULL)
    {
        if (strcmp(OpenYoN, nombreArchivo) == 0){
            (*cant)--;
            return 1;
        }
        OpenYoN = (char*)nextList(archiveToOpen);
    }
    
	return 0;
}
//-----------------------------------------//

/*------- Conseguir path al txt -------*/
char *get_nameFile(char *archive, char *directory){ // Crea el path para el fopen y abrir bien el archivo
	char aux[200];
	strcpy(aux, directory);
	strcat(aux, "/");
	strcat(aux, archive);
	char *new = strdup(aux);
	return new;
}
//-----------------------------------------//

/*------- Elimina caracteres no alfabeticos -------*/
void quitarNoAlfabeticos(char *beforeString, bool quitarSpaces){
	if (is_equal_string(beforeString, "Title:")){return;}
	int largo = strlen(beforeString);
	char newString[largo];
	int indice = 0;
	
	for (size_t i = 0; i < largo; i++){
		
		if (beforeString[i] == ' ' && !quitarSpaces){ // Para guardar el titulo no borra los espacios
			newString[indice] = beforeString[i];
			indice++; continue;
		}
		
		if ((beforeString[i] >= 'A' && beforeString[i] <= 'Z' && beforeString[i] != ':')||
		    (beforeString[i] >= 'a' && beforeString[i] <= 'z' && beforeString[i] != ':')){
			newString[indice] = beforeString[i];
			indice++;
		}
	}
	if (indice != largo-1)
	{
		newString[indice] = 0;
	}
	strcpy(beforeString, newString);
}
//-----------------------------------------//

/*------- separar palabras del file -------*/
char* nextWord (FILE *f) {
    char WORD[1024];
    if (fscanf(f, " %1023s", WORD) == 1){
		quitarNoAlfabeticos(WORD, true);
		return strdup(WORD);
	}
    else {return NULL;}
}
//-----------------------------------------//

/*------- separar palabras del file -------*/
char* get_title(FILE *f) {
    char TITLE[1024];
    if (fscanf(f, " %1023[^\n]", TITLE) == 1){
		quitarNoAlfabeticos(TITLE, false);
		return strdup(TITLE);
	}
    else {return NULL;}
}
//-----------------------------------------//

/*------- Crear struct LibrosConPalabra -------*/
LibrosConPalabra *createBookConWord(unsigned long idToBook, char* titleToBook){
	LibrosConPalabra *newHere = (LibrosConPalabra*) malloc (sizeof(LibrosConPalabra));
    newHere->idLibro = idToBook;
    newHere->nombreLibro = titleToBook;
    newHere->ocurrenciaEnLibro = 1;
    return newHere;
}
//-----------------------------------------//

/*------- Crear struct Palabra -------*/
Palabra *createWord(char *WORD){
    Palabra *new = (Palabra*) malloc (sizeof(Palabra));
    new->ocurrenciaPalabra = 1;
    new->palabra = strdup(WORD);
	new->LibrosWithPalabra = 1;
    return new;
}
//-----------------------------------------//

/*------- Crear struct PalabraEnLibro -------*/
PalabraEnLibro *createWordEnBook(char* nameToWord){
	PalabraEnLibro *newHere = (PalabraEnLibro*) malloc (sizeof(PalabraEnLibro));
    newHere->ocurrenciaString = 1;
    newHere->String = strdup(nameToWord);
    newHere->frecuencia = 0;
	newHere->relevancia = 0;
    return newHere;
}
//-----------------------------------------//

/*------- Crear struct Palabra -------*/
Libro *createBook(char *WORD, unsigned long ID, char *TITLE){
    Libro *new = (Libro*) malloc (sizeof(Libro));
    new->idBook = ID;
    new->nameBook = strdup(TITLE);
	new->cantPalabrasBook = 1;
	new->cantCaracteresBook = strlen(WORD);
    return new;
}
//-----------------------------------------//

/*------- Transforma en minuscula los caracteres alfabeticos -------*/
void minsuculas(char *cadena){
	for (size_t i = 0; cadena[i]; i++){
		if(isalpha(cadena[i]) != 0){cadena[i] = tolower(cadena[i]);}
	}
}
//-----------------------------------------//

/*------- Guardar en los mapas la informacion -------*/
void saveWordsInMaps(char *wordToSave, char* titleToSave, char *idToSave, 
                     Map *words_Map, Map *books_Map){
	
	minsuculas(wordToSave); // Transforma en minusculas las palabras a guardar


	// Guarda los datos en el mapa Palabras
	Palabra *auxWord = NULL;
	LibrosConPalabra *auxWord2 = NULL;
	if (searchMap(words_Map, wordToSave) == NULL)
	{// Si no estaba guardado el dato, lo guarda. Si existia aumentara ocurrencias
		auxWord = createWord(wordToSave);
		auxWord->ConPalabra = createList();
		auxWord2 = createBookConWord(atoi(idToSave), titleToSave);
		pushBack(auxWord->ConPalabra, auxWord2);
        insertMap(words_Map, auxWord->palabra, auxWord);
	}
	else{
		auxWord = searchMap(words_Map, wordToSave);
        auxWord->ocurrenciaPalabra++;
        auxWord2 = firstList(auxWord->ConPalabra);
		while (auxWord2)
		{// Revisa si el libro esta en la lista de libros donde se encuentra la palabra
			if (is_equal_string(titleToSave, auxWord2->nombreLibro) == 1)
			{
				auxWord2->ocurrenciaEnLibro++;
				break;
			}
			auxWord2 = nextList(auxWord->ConPalabra);
		}
		if (!auxWord2)
		{
			auxWord2 = createBookConWord(atoi(idToSave), titleToSave);
			pushBack(auxWord->ConPalabra, auxWord2);
		}
	}

	// Guarda los datos en el mapa Libros
	Libro *auxBook = NULL;
	PalabraEnLibro *auxBook2 = NULL;
	if (searchMap(books_Map, titleToSave) == NULL)
	{// Si no estaba guardado el dato, lo guarda. Si existia aumentara ocurrencias
		auxBook = createBook(wordToSave, atoi(idToSave),titleToSave);
		auxBook->EnLibro = createList();
		auxBook2 = createWordEnBook(wordToSave);
		pushBack(auxBook->EnLibro, auxBook2);
        insertMap(books_Map, auxBook->nameBook, auxBook);
	}
	else{
		auxBook = searchMap(books_Map, titleToSave);
		auxBook->cantCaracteresBook += strlen(wordToSave);
		auxBook2 = firstList(auxBook->EnLibro);
		while (auxBook2)
		{// Revisa si la palabra esta en la lista de palabras del libro
			if (is_equal_string(auxBook2->String, wordToSave))
			{
				auxBook2->ocurrenciaString++;
				break;
			}
			auxBook2 = nextList(auxBook->EnLibro);
		}
		if (!auxBook2)
		{
			auxBook->cantPalabrasBook++;
			auxBook2 = createWordEnBook(wordToSave);
			pushBack(auxBook->EnLibro, auxBook2);
		}
	}
}
//-----------------------------------------//

/*------- Leer Archivo -------*/
void ReadTxt(Map* string_map, Map* book_map, char *name, char *nameDirectory, int *docTotal){
	// Abre un archivo especifico y guarda sus datos
	char *nameFile = get_nameFile(name, nameDirectory);
	
    FILE *F = fopen(nameFile, "r"); // Abre el archivo con el nombre recibido en modo lectura
    
	if (!F){return;}// Si no existe el archivo, cierra el programa
	(*docTotal)++;

    char *title;
	bool save = false;
	char *word = nextWord(F); // Cadena de caracter para guardar cada palabra del archivo
    while (word != NULL)
    {
		
		if (is_equal_string(word, "Title:")){ // Guarda el Titulo
			title = get_title(F);
			word = nextWord(F);
			save = true; // Indica que a partir de ahora se pueden guardar las palabras
		}

		if (save)
		{saveWordsInMaps(word, title, name, string_map, book_map);}
        
		word = nextWord(F);
    }
	fclose(F);// Se cierra el archivo
}

/*----------------- OPCIÓN 1: -----------------*/
void CargarDocumento(Map *palabrasMap, Map *librosMap, int *dTotal){
    DIR *carpeta;
	struct dirent *dirp;
	char *ubicacion = "./Libros";
    printf("Escriba las id de los libros que desea cargar con .txt al final\n");
	printf("(Si desea ingresar dos o mas, separe con estacios despues de cada .txt)\n");
	char Archives[200];
	fgets(Archives,200,stdin);
	printf("\n");
    size_t cant = 0;
	List *FilesToOpen = cantArchiveOpen(Archives, &cant);
    carpeta = opendir(ubicacion);
	while ((dirp = readdir(carpeta)) != NULL && cant > 0){
        if(esText(dirp->d_name, FilesToOpen, &cant) == 0) continue;
		ReadTxt(palabrasMap, librosMap, dirp->d_name, ubicacion, dTotal);
	}
	closedir(carpeta);
}
//-------------------------------------------------------------//

//**************************************************************//



//**************************  OPCIÓN 2  ***********************//

/*------- Mostrar Libro -------*/
void mostrarLibro(Libro* aux){
	printf("Titulo: %s\n", aux->nameBook);
	printf("    Id: %lu\n", aux->idBook);
	printf("  Cantidad de Palabras: %lu\n", aux->cantPalabrasBook);
	printf("Cantidad de Caracteres: %lu\n\n", aux->cantCaracteresBook);
}
//-----------------------------------------//

/*----------------- OPCIÓN 2: -----------------*/
void MostrarDocumentosOrdenados(Map *allBooks){
	printf("A continuacion se mostraran los libros ordenados con sus id \n\n");
	Libro *imprimir = firstMap(allBooks);
	while (imprimir != NULL)
	{
		mostrarLibro(imprimir);
		imprimir = nextMap(allBooks);
	}
	printf("\n");
}
//-------------------------------------------------------------//

//**************************************************************//



//**************************  OPCIÓN 3  ***********************//

/*------- Comparar Strings -------*/
int compare_strings(char cadena1[101], char *cadena2)
{   size_t largo = sizeof(cadena2)/sizeof(char); // SIRVE PARA ENCONTRAR EL LARGO DE LA CADENA DINAMICA
    for(int i = 0; i < largo; i++){
		if (tolower(cadena1[i]) != tolower(cadena2[i])) {return 1;}
	}return 0;
}
//-----------------------------------------//

/*------- Busca y muestra libro por el titulo -------*/
void BuscarLibroTitulo(Libro* book, Map* booksMap, char* title)
{
	book = firstMap(booksMap);
		while(book != NULL)
		{
			if(compare_strings(title, book->nameBook) == 0)
			{	
				printf("\n");
				printf("Libro encontrado: \n");
				printf("\n");
				mostrarLibro(book);	return;

			}else{book = nextMap(booksMap);}
		}

		printf("Libro no encontrado\n");
		return;
}
//-----------------------------------------//

/*----------------- OPCIÓN 3: -----------------*/
void BuscarLibro(Libro* book, Map* booksMap)
{
	printf("Ingrese el nombre de los ejemplares que desea buscar \n");
	char title[1000];
	scanf("%[0-9a-zA-Z ,-]", title);
	getchar();
	BuscarLibroTitulo(book, booksMap, title);
	return;
}
//-------------------------------------------------------------//

//**************************************************************//



//**************************  OPCIÓN 4  ***********************//

/*------- Calcula la frecuencia de cada una -------*/
void calcularFrecuencia(PalabraEnLibro *aux, double cantWords){
	aux->frecuencia = (double) aux->ocurrenciaString / cantWords;
}
//-----------------------------------------//

/*------- Funcion comparar para ordenar con qsort por relevancia -------*/
int compararFrecuencia (const void *a,const void *b)
{
	PalabraEnLibro *aux1 = *(PalabraEnLibro **) a;
	PalabraEnLibro *aux2 = *(PalabraEnLibro **) b;

	double frecA = aux1->frecuencia;
	double frecB = aux2->frecuencia;

	if (frecA < frecB){return 1;}
	else if (frecB < frecA){return -1;}
	

	return 0;
}
//-----------------------------------------//

/*------- Muestra la palabraDelLibro con su frecuencia y ocurrencia -------*/
void mostrarWordDelLibro(PalabraEnLibro *see, int num){
	printf("  ");

	if (num < 10){printf(" ");}//Para que los numeros esten a la misma altura
	printf("%d.- ", num);

	printf("La palabra \"%s\" se repite", see->String);
	printf(" %.0f y tiene como frecuencia %lf\n", see->ocurrenciaString, see->frecuencia);
}
//-----------------------------------------//

/*------- Crear Arreglo en el orden requerido -------*/
void MostrarMasFrecuentes(Libro *BOOK){
	PalabraEnLibro **array = (PalabraEnLibro**) calloc(11, sizeof(PalabraEnLibro*));
	PalabraEnLibro *aux = firstList(BOOK->EnLibro);
	int ocupados = 0; //Es para saber si ya se ha ocupado todo el arreglo para que el nuevo dato se ordene
	while (aux)
	{
		calcularFrecuencia(aux, BOOK->cantPalabrasBook);

		if (ocupados < 10){
			array[ocupados] = aux;
			ocupados++;
		}
		else{
			array[10] = aux;
			qsort(array, 10, sizeof(LibrosConPalabra*), compararFrecuencia);
		}
		
		aux = nextList(BOOK->EnLibro);
	}

	printf("\nLas palabras mas relevantes en el libro \"%s\" son:\n", BOOK->nameBook);
	for (size_t i = 0; i < 10; i++)
	{
		mostrarWordDelLibro(array[i], i+1);
	}
}
//-----------------------------------------//

/*----------------- OPCIÓN 4: -----------------*/
void PalabrasConMayotFrecuencia(Map* allBooks){
	int id;
	printf("Ingrese el id de un libro: ");
	fscanf(stdin, "%d", &id);
	getchar();

	Libro *aux = firstMap(allBooks);
	while (aux != NULL)
	{
		if (aux->idBook == id)
		{
			break;
		}
		aux = nextMap(allBooks);
	}
	if (aux == NULL){
		printf("El libro no existe o no ha sido cargado");
		return;
	}

	MostrarMasFrecuentes(aux);
}
//-------------------------------------------------------------//

//**************************************************************//




//**************************  OPCIÓN 5  ***********************//

/*-------  -------*/
//-----------------------------------------//

/*----------------- OPCIÓN 5: -----------------*/
//-------------------------------------------------------------//


//**************************************************************//



//**************************  OPCIÓN 6  ***********************//

/*------- Calcula Relevancia -------*/
double calcularRelevancia(unsigned long ocurrenciaP,
	unsigned long palabrasD, int docs, unsigned long librosConP)
{
	//Se calcula en dos instrucciones por cuestion de legibilidad
	double ret = (double) ocurrenciaP/palabrasD;
	ret = ret * (double) log(docs/librosConP);

	return ret;
}
//-----------------------------------------//

/*------- Funcion comparar para ordenar con qsort por relevancia -------*/
int cmpfunc (const void *a,const void *b)
{
	//a y b son punteros a un array de punteros por lo tanto se debe hacer esto para acceder a los datos:
	LibrosConPalabra *aux1 = *(LibrosConPalabra **) a;
	LibrosConPalabra *aux2 = *(LibrosConPalabra **) b;

	double ret = aux1->relevancia - aux2->relevancia;
	return (int) (ret * 100); //Ya que la func retorna un int se multiplica ret por 100 y se hace el casting
}
//-----------------------------------------//

/*----------------- OPCIÓN 6: -----------------*/
void *buscarPorPalabra(Map *mapaLibros, Map *mapaPalabras, int docs)
{
	char stringPalabra[101];
	Palabra *palabra;
	LibrosConPalabra **arrLibros, *libroPalabra; //El array sirve para usar qsort()
	Libro *libro;
	int i = 0; //contador para ir rellenando el array

	//Recibe el input del usuario
	printf("Ingrese la palabra a buscar: ");
	scanf("%[0-9a-zA-Z ,-]", stringPalabra);
	getchar();

	//Buscar la palabra, crear el array de libros e inicializar libroPalabra como el primer elemento de la lista
	palabra = (Palabra *) searchMap(mapaPalabras, stringPalabra);
	arrLibros = (LibrosConPalabra **) malloc(palabra->LibrosWithPalabra * sizeof(LibrosConPalabra *));
	libroPalabra = (LibrosConPalabra *) firstList(palabra->ConPalabra);

	while(libroPalabra)
	{
		libro = (Libro *) searchMap(mapaLibros, libroPalabra->nombreLibro); //Se busca el libro en el mapa de libros
		libroPalabra->relevancia = calcularRelevancia(libroPalabra->ocurrenciaEnLibro, libro->cantPalabrasBook, docs, palabra->LibrosWithPalabra); //Se calcula la relevancia
		arrLibros[i] = libroPalabra; //Se inserta el libroPalabra en el array
		libroPalabra = nextList(palabra->ConPalabra);
		i++;
	}

	qsort(arrLibros, i, sizeof(LibrosConPalabra *), cmpfunc); //Se realiza el qsort

	printf("\nLibros con la palabra \"%s\": \n\n", palabra->palabra);

	for(int j = 0; j < i; j++)
	{
		printf("Titulo: %s \nID: %d\n\n", arrLibros[j]->nombreLibro, arrLibros[j]->idLibro);
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
    Map *palabrasGeneral = createMap(is_equal_string);
    setSortFunction(palabrasGeneral,lower_than_string);
	Map *librosGeneral = createMap(is_equal_string);
    setSortFunction(librosGeneral,lower_than_string);
	Map *titulo_relevante = createMap(is_equal_string);
	setSortFunction(titulo_relevante, lower_than_string);

	int option = 0; //Variable que decide la opcion del menun seleccionada
	int documentosTotales = 0;

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
			CargarDocumento(palabrasGeneral, librosGeneral, &documentosTotales);
			break;
            //-----------------------------------------//
        case 2:
			/*------- Mostrar documentos ordenados -------*/
			MostrarDocumentosOrdenados(librosGeneral);
			break;
			//-----------------------------------------//
        case 3:
            /*------- Buscar un libro por titulo -------*/
			;Libro* book;
			BuscarLibro(book, librosGeneral);
			break;;
			//-----------------------------------------//
		case 4:
			/*------- Palabras con mayor frecuencia -------*/
			PalabrasConMayotFrecuencia(librosGeneral);
			break;
			//-----------------------------------------//
		case 5:
			/*------- Palabras mas relevantes -------*/
			relevanciaCreate(titulo_relevante, librosGeneral, palabrasGeneral);
			mostrarRelevancia(titulo_relevante);
			break;
			//-----------------------------------------//
		case 6:
			/*------- Buscar por palabra -------*/
			buscarPorPalabra(librosGeneral, palabrasGeneral, documentosTotales);
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
