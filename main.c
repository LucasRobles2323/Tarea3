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
	char *txtBook;
	unsigned long cantPalabrasBook;
	unsigned long long cantCaracteresBook;
	List *EnLibro; // Lista de struct PalabraEnLibro
}Libro; //Struct que guarda los datos de un libro para el mapa de libro

typedef struct{
	List *palabra;//aqui se guardan todas las palabras con la misma relevancia
	float relevancia;
}PalabraRelevante;//struct que guarda la  relevancia y una lista de palabras

typedef struct{
	Map *PalabraRelevante; 
	char *titulo;
	int numeroDocumentos;
}Relevancia;//struct que guarda total de documentos, el titulo del libro y un mapa de key "relevancia"

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
List *cantArchiveOpen(char *Archives, size_t *cant, bool quitarSaltoLinea){ 
	//Crea una lista con las palabras separadas por espacio
	List *newList = createList();
    char *Text = strtok(Archives, " ");
	while (Text != NULL)
	{
        pushBack(newList, strdup(Text));
        (*cant)++;
		Text = strtok(NULL, " ");
	}
	if (quitarSaltoLinea)
	{
		Text = lastList(newList);
		Text = strtok(Text, "\n");
	}
    return newList;
}
//-----------------------------------------//

/*------- Abrir o no el archivo -------*/
int esText(char *nombreArchivo, List *archiveToOpen, size_t *cant){ //Confirma si abrir un archivo del directorio
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
char *get_nameFile(char *archive, char *directory){
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
Libro *createBook(char *WORD, unsigned long ID, char *TITLE, char *TXT){
    Libro *new = (Libro*) malloc (sizeof(Libro));
    new->idBook = ID;
    new->nameBook = strdup(TITLE);
	new->cantPalabrasBook = 1;
	new->cantCaracteresBook = strlen(WORD);
	new->txtBook = strdup(TXT);
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
                     Map *words_Map, Map *books_Map, char *txt){
	
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
		while (auxWord2)// Revisa si el libro esta en la lista de libros donde se encuentra la palabra
		{
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
		auxBook = createBook(wordToSave, atoi(idToSave),titleToSave, txt);
		auxBook->EnLibro = createList();
		auxBook2 = createWordEnBook(wordToSave);
		pushBack(auxBook->EnLibro, auxBook2);
        insertMap(books_Map, auxBook->nameBook, auxBook);
	}
	else{
		auxBook = searchMap(books_Map, titleToSave);
		auxBook->cantCaracteresBook += strlen(wordToSave);
		auxBook2 = firstList(auxBook->EnLibro);
		while (auxBook2) // Revisa si la palabra esta en la lista de palabras del libro
		{
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
		{saveWordsInMaps(word, title, name, string_map, book_map, nameFile);}
        
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
	List *FilesToOpen = cantArchiveOpen(Archives, &cant,true);
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
	int compare_strings_advanced(char* cadena1, char *cadena2) // cadena 2 avanza, la 1 no
	{
		size_t largo = strlen(cadena2); 
		size_t letras = 0;
		while(cadena1[letras] != '\0'){letras++;}
		int j = 0; size_t cont_iguales = 0;
		
		minsuculas(cadena1); minsuculas(cadena2);

		for(int i = 0; i < largo; i++)
		{
			if(cadena2[i] != ' ')
			{
			if (cadena1[j] == cadena2[i])
			{
				j++; cont_iguales++; 
				if(cont_iguales == letras)return 0;
				
			}else{j = 0;}
			}
			
		}

		return 1;	
	}
	//-----------------------------------------//
		


	//-----------------------------------------//

	int compare_words(char* title, char* titleLibro, Libro* book)
	{
		size_t cont = 0;
		List* words = cantArchiveOpen(title, &cont, false);
		title = firstList(words);
		while(title != NULL)
		{	
			if((compare_strings_advanced(title, titleLibro) != 0))return 1;
			title = nextList(words);
		}
		return 0;
	}

	/*----------------- OPCIÓN 3: -----------------*/
	void BuscarLibroTitulo(Libro* book, Map* booksMap, char* title)
	{
		book = firstMap(booksMap); int cont = 0;
			while(book != NULL)
			{
				if(compare_words(title, book->nameBook, book) == 0)
				{	
					if(cont == 0){printf(" \n Libro encontrado: \n");printf("\n"); cont++;}
					mostrarLibro(book);	
					book = nextMap(booksMap);

				}else{book = nextMap(booksMap);}
			}
			if(cont > 0){printf("Fin libros encontrados");}
			if(cont == 0)
			{printf("\nLibro no encontrado");}
			return;
	}
	//-------------------------------------------------------------//

	void BuscarLibro(Libro* book, Map* booksMap)
	{
		printf("Ingrese el nombre de los ejemplares que desea buscar \n");
			char title[1000];
			scanf("%[0-9a-zA-Z ,-]", title);
			getchar();
			BuscarLibroTitulo(book, booksMap, title);
			return;
	}


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

/*------- Crea un struct Relevancia -------*/
Relevancia *crearLibro (char *titulo, int numeroDocumento){
	Relevancia *new = (Relevancia*) malloc (sizeof(Relevancia));
	new->titulo = strdup (titulo);
	new->numeroDocumentos = numeroDocumento;
	new->PalabraRelevante = createMap(is_equal_int);
	setSortFunction(new->PalabraRelevante, lower_than_int);
	return new;
}
//-----------------------------------------//

/*------- Crea un struct PalabraRelevante -------*/
PalabraRelevante *crearpalabra (float relevancia){
	PalabraRelevante *new = (PalabraRelevante*) malloc (sizeof(PalabraRelevante));
	new->relevancia = relevancia;
	new->palabra = createList();
	return new;
}
//-----------------------------------------//

/*------- Calcula la relevancia de la palabra -------*/
float calcularRel (unsigned long libroConPalabra, unsigned long cantPalabrasLibro, int contador, float ocurrenciasString){
	float logaritmo, division;
    
	//Se calcula el valor del logaritmo en base 10 de (cantidad de documentos/documentos con la palabra)
	logaritmo = log10 (contador/libroConPalabra);
	//Se calcula el valor de la division entre (cantidad de veces que aparece la palabra/cantidad de palabras que tiene el libro)
	division = ocurrenciasString/cantPalabrasLibro;
    
	//Retorna la multiplicacion entre logaritmo * division
	return (division * logaritmo);
}
//-----------------------------------------//

/*------- Borra completamente un mapa -------*/
void borrarMapa (Map *mapaErase){
	//Se repasa desde el primer libro hasta el ultimo
	Relevancia *borrarRelevancia = firstMap (mapaErase);
	while (borrarRelevancia != NULL){
		eraseMap (mapaErase, borrarRelevancia->titulo);//Aqui se borra el mapa de key libro
		borrarRelevancia = nextMap (mapaErase);
		if (borrarRelevancia == NULL)break;
	}

}
//-----------------------------------------//

/*------- Calcula y guarda la relevancia de todas las palabras del libro -------*/
/*Aqui se se crea el mapa para la relevancia esta es:
                   
				 Dentro del Map (titulo del libro):  
					int cantidad de documentos 
					char *titulo del libro      
					Map *(relevancia):

					 Dentro del Map (relevancia):       
                        float relevancia  
					    list *palabra:

						Dentro de la lista palabra:  
						       char *palabra
*/
void relevanciaCreate (Map *relevancia_map, Map *libros_map, Map *palabras_map){
	//Se revisa si es que el mapa libros tiene contenido dentro en caso de ser NULL se devuelve
	if ((firstMap (libros_map)) == NULL || libros_map == NULL){
		printf ("No se ha cargado ningun archivo\n");
		return;
	}
    
	//Se declara variables
	//Para los struct
	PalabraRelevante *pal;
	Relevancia *rel;

	float relevante;//relevancia
    int cont = 0;//contador de documentos
	//Aqui se recorre el mapa de libros para saber cuantos libros se cargaron
	Libro *book = firstMap (libros_map);
	while (book != NULL){
		cont ++;
		book = nextMap (libros_map);
	}
    
	//Si el contador es 1 se muestra un mensaje por pantalla
	//Esto es porque si hay solo 1 documento cuando se calcule la relevancia todas daran 0 por el log(1) = 0
	if (cont == 1){
		printf ("Si se cargo 1 solo documento todas las palabras tienen relevancia 0\n");
		return;
	}
    
	//Si el mapa de relevancia esta vacio se crea una nueva
	if (relevancia_map == NULL || (firstMap (relevancia_map)) == NULL){
		//Se inicialista en el primer libro
		Libro *book = firstMap (libros_map);
		//Se toma el primer struct de la lista del book->EnLibro
		PalabraEnLibro *wordInBook = firstList (book->EnLibro);
		//Se busca la misma el stuct correspondiente a la palabra de la firstList (book->EnLibro)
		Palabra *string = searchMap (palabras_map, wordInBook->String);
        
		//Mientras la varaible book sea distinto de NULL que representa los libros
		while (book != NULL){
			//Se crea el struct de tipo Relevancia y se inserta al Mapa con key "titulo del libro" y valor la struct Relevancia
			rel = crearLibro (book->nameBook, cont);
			insertMap (relevancia_map, rel->titulo, rel);
			//Mientras wordInBook sea distinto de NULL que representa las palabras dentro del libro
			while (wordInBook != NULL){
				//Se calcula la relevancia
				relevante = calcularRel (string->LibrosWithPalabra, book->cantPalabrasBook, cont, wordInBook->ocurrenciaString);
                //Se verifica si en el mapa(titulo)->mapa(relevancia) existe ya un mapa con la misma relevancia
				PalabraRelevante *verificar = searchMap (rel->PalabraRelevante, &relevante);
				//Si no existe se crea inserta al mapa con la relevancia no repetida
				if (verificar == NULL){
					
					pal = crearpalabra (relevante);
					pal->palabra = createList ();
					pushBack (pal->palabra, wordInBook->String);
					insertMap (rel->PalabraRelevante, &pal->relevancia, pal);
					
				}
				else{
					//Si se repite se añade a la lista de palabras con la misma relevancia
					pushBack (verificar->palabra, wordInBook->String);
				}
                
				//Se va la siguiente palabra pero si wordInBook da NULL se salta este while
				wordInBook = nextList (book->EnLibro);
				if (wordInBook == NULL)continue;
				string = searchMap (palabras_map, wordInBook->String);	
			}
			//Se  va al siguiente libro pero si book da NULL se sale del ciclo
			book = nextMap (libros_map);
			if (book == NULL) break;
			//Se ve la primera palabra del libro
			wordInBook = firstList (book->EnLibro);
			string = searchMap (palabras_map, wordInBook->String);
		}
	}else{
		//Se compara si coincide la cantidad de documentos antes y despues de ocupar esta funcion
		Relevancia *comparador = firstMap (relevancia_map);
		//En caso de que se hayan añadido mas documentos habra que recalcular la relevancia
	    if (cont > comparador->numeroDocumentos){
            //Se borra el mapa hecho
            borrarMapa (relevancia_map);
            
			//Se hace el mismo procedimiento que cuando el mapa era NULL
			//De aqui en adelante es lo mismo.
		    Libro *book = firstMap (libros_map);
		    PalabraEnLibro *wordInBook = firstList (book->EnLibro);
		    Palabra *string = searchMap (palabras_map, wordInBook->String);

		    while (book != NULL){
			    rel = crearLibro (book->nameBook, cont);
			    insertMap (relevancia_map, rel->titulo, rel);
			    while (wordInBook != NULL){
				    relevante = calcularRel (string->LibrosWithPalabra, book->cantPalabrasBook, cont, wordInBook->ocurrenciaString);
				    PalabraRelevante *verificar = searchMap (rel->PalabraRelevante, &relevante);
				    
				    if (verificar == NULL){
					
					    pal = crearpalabra (relevante);
					    pal->palabra = createList ();
					    pushBack (pal->palabra, wordInBook->String);
					    insertMap (rel->PalabraRelevante, &pal->relevancia, pal);
					
				    }
				    else{
					    pushBack (verificar->palabra, wordInBook->String);
				    }
                    
				    wordInBook = nextList (book->EnLibro);
				    if (wordInBook == NULL)continue;
				    string = searchMap (palabras_map, wordInBook->String);	
			    }
			    book = nextMap (libros_map);
			    if (book == NULL) break;
			    wordInBook = firstList (book->EnLibro);
			    string = searchMap (palabras_map, wordInBook->String);
	        }
			//Hasta aqui se repite
	    }
    }
}	
//-----------------------------------------//

/*----------------- OPCIÓN 5: -----------------*/
//Aqui se pregunta el libro y se muestra por pantalla las palabras relevantes
void mostrarRelevancia (Map * mapa){
	//Por si paso algo el mapa no se cargo bien o algo, deberia ser raro ver este printf
	Relevancia *estructura = firstMap (mapa);
	if (estructura == NULL){
		printf ("Algo paso\n");
		return;
	}
    
	//Se muestra los libros disponibles 
	printf ("Titulos a mostar:\n");
	while (estructura != NULL){
		printf ("%s\n", estructura->titulo);
		estructura = nextMap (mapa);
	}
    printf ("\n");
    
	//Se pregunta al usuario que libro quiere ver las palabras relevantes
    char titulo[101];
	printf ("Escriba el libro \n");
	scanf("%[0-9a-zA-Z ,-]", titulo);
	getchar();

    //Se busca y en caso de no encontrarlo dira que no se encuentra
	estructura = searchMap (mapa, titulo);
	if (estructura == NULL){
		printf ("No esta el libro buscado o no lo escribio bien\n");
		return;
	}
    
	//Aqui se muestra las 10 palabras relevantes
    int cont = 0;
	PalabraRelevante *word = firstMap (estructura->PalabraRelevante);
	char *lista = firstList (word->palabra);
	printf ("Libro : %s\n", estructura->titulo);
	printf ("------------------------------------------\n");
	while (word != NULL){
		printf ("Relevancia : %f\n", word->relevancia);
		lista = firstList (word->palabra);
		while (lista != NULL){
			printf ("palabra : %s \n ",lista);
			lista = nextList (word->palabra);
			cont++;
		    if (cont >= 10) break;
		}
		printf ("-----------------------------------------|\n");
		 if (cont >= 10) break;
		word = nextMap (estructura->PalabraRelevante);
	}
}
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

	double ret = aux2->relevancia - aux1->relevancia;
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
		printf("Titulo: %s \nID: %d\n\n", arrLibros[j]->nombreLibro, arrLibros[j]->idLibro, arrLibros[j]->relevancia);
	}
}
//-------------------------------------------------------------//

//**************************************************************//



//**************************  OPCIÓN 7  ***********************//

/*------- Mostrar o no Linea -------*/
bool MostrarLinea(char *line, char *worD){
	int cant = 0;
	List *lineList = cantArchiveOpen(line, &cant, true);
	char *WordOfLine = firstList(lineList);
	while (WordOfLine)
	{
		quitarNoAlfabeticos(WordOfLine, true);
		minsuculas(WordOfLine);
		if (strcmp(WordOfLine, worD) == 0)
		{
			return true;
		}
		WordOfLine = nextList(lineList);
	}
	return false;
}
//-----------------------------------------//

/*------- Abrir y leer el libro -------*/
void AbrirTxt(Map* string_map, Map* book_map, char *titulo, char *path){
	// Abre un archivo especifico y guarda sus datos
	
    FILE *F = fopen(path, "r"); // Abre el archivo con el nombre recibido en modo lectura
    
	if (!F){return;}// Si no existe el archivo, cierra el programa

    char linea[1024]; // Cadena de caracter para guardar una linea del archivo
	char wordsInput[200];
	int cont = 0;
	
	printf("Escriba la palabra a buscar con solo caracteres alfabeticos.\n");
	printf("(Si escribe dos palabras separadas por espacio solo bucara la primear)\n");
	fgets(wordsInput, 200, stdin);
	printf("\n\n");
	List* wordsList = cantArchiveOpen(wordsInput, &cont, true);
	char *wordToSearch = firstList(wordsList);
	quitarNoAlfabeticos(wordToSearch, true);
	minsuculas(wordToSearch);
	cont = 0;
	
	
	while (fgets(linea, 1023, F) != NULL) { 
        // Recorre el archivo leyendo linea por linea

		if(MostrarLinea(strdup(linea), wordToSearch)){
			if (cont == 0){
				printf("En el libro \"%s\", podemos encontrar la palabra ", titulo);
				printf("\"%s\" en los siguientes contexto:\n", wordToSearch);
			}
			
			printf("%s\n", linea); cont++;
		}
	}
	if (cont == 0)
	{
		printf("La palabra \"%s\" no esta presente en el texto \"%s\"", wordToSearch, titulo);
	}

	fclose(F);// Se cierra el archivo
}
//-----------------------------------------//

/*------- Conseguir el .txt para abrir el libro -------*/
void BuscarIdLibro(Map *book_actual, Map *word_actual,  char *title){
	Libro *aux;
	title = strtok(title, "\n");
	if ((aux =searchMap(book_actual, title)) == NULL)
	{
		printf("El libro que desea abrir no esta cargado desde el direcorio\n");
		return;
	}

	AbrirTxt(word_actual, book_actual, title, aux->txtBook);
}
//-----------------------------------------//

/*----------------- OPCIÓN 7: -----------------*/
void MostrarContexto(Map *palabrasMap, Map *librosMap){
    char tituloOpen[201];
	printf("Escriba el titulo de un libro (no utilice caracteres no alfabeticos)\n");
	fgets(tituloOpen,200,stdin);
	printf("\n");
	
	BuscarIdLibro(librosMap, librosMap, tituloOpen);
}
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
			MostrarContexto(palabrasGeneral, librosGeneral);
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