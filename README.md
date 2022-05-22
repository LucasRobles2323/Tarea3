# Tarea3 Huachipato

Estudiantes PUCV curso: ICI2240-1  ESTRUCTURA DE DATOS

## **_Integrantes_**

- ### Ademir Muñoz: 
    Pts premio/castigo: 0.

   Subestime el tiempo que tenia al principio no le di importancia y de pronto habian prubeas, controles y una trabajo/disertacion que coicidieron con la tarea 3, le fui dejando restandole prioridad debido a que las otras eran pruebas y cuando todo finalizo quedaban pocos dias para hacer algo y nisiquiera habia pensado en como hacer la tarea, tuve 0 organizacion de mi tiempo y ese fue mi error.


- ### Lucas Robles: 
    Pts premio/castigo: 0.

    Siento que en el momento que supe que trabajariamos con directorios, deberia haber investigado como era posible, fue dificil lograr abrir bien el directorio, ademas de que empece a hacer esta tarea mas tarde de lo que deberia. Ademas subi como 5 commit con otro correo que no sale en colaboradres e hice un commit mal y lo resubi con el mismo mensaje commit


- ### Sebastián Aguilera: 
    Pts premio/castigo: 0.

    Creo que debería organizar mejor mi manera de trabajar ya que tarde bastante en hacer las funciones que se me designaron debido a que no tenia un planeado bien como hacerlo.

- ### Gerard Espinoza: 
    Pts premio/castigo: 0.

    Siento que a pesar de tener ya experiencia con las funciones de búsqueda demore más de lo debido en implementar las de esta tarea, además de que en un principio no utilice las maneras más eficientes de búsqueda en las funciones por lo que tuve que rehacerlas y reeinterpretarlas.

### ¡Grande Huachipato!

![Grande Huachipato](https://pbs.twimg.com/profile_images/1494832822099451910/NgCFzNKt_400x400.jpg)


## 1. Como compilar y ejecutar la tarea:
Clonar el repositorio en Desktop

![Clonar Repositorio](https://drive.google.com/uc?id=1rLlpu7gNdPBWC2hlTGqLEKTb_JHMI1qj)

Abrir el clon del repositorio con VSCode. Una vez abierto se debe abrir terminal powershell.

Con la terminal powershell abierta se escribe lo siguiente:

![gcc](https://drive.google.com/uc?id=14duVxmEGVqfAFJMAqufBglbaP5Eg8Ipf)

De esa forma se creo o modifico el ejecutable, que se ejecuta de la siguiente manera:

![Ejecutable](https://drive.google.com/uc?id=1gy5nyPzsGwZ1MPQUfp6-T_ZctNViaxq9)

Despues de una advertencia al ejecutar el Test, se desplegaria el menu

Este sería el menú.

![Menú](https://drive.google.com/uc?id=1RBcblajhABoDbq8zqfqWFJ58gxsX5STi)


## 2. Las opciones que funcionan correctamente y las que no lo hacen indicando posibles causas
Hasta ahora todas las funciones están funcionales en casos normales ósea sin que el usuario intente apretar letras al azar o colocando datos sin pensar.


## Structs:
Contiene 2 struct, una para las canciones y otra destinada a las listas de reproducción

![Structs](https://drive.google.com/uc?id=1NvzTyFpgU4nEvHODGwUkh-O3uSvGLImu)
![Structs](https://drive.google.com/uc?id=17L4OZK1pDPhVDA8M67yJr-5CIrnVDEJ8)


## Funciones:
---
~~~
int is_equal_string(void * key1, void * key2)
{
Función para comparar claves de tipo string retorna 1 si son iguales y 0 en caso contrario.
}


int lower_than_string(void * key1, void * key2)
{
Función para comparar claves de tipo string retorna 1 si son key1<key2 y, en caso de no ser asi retorna 0.
}


int is_equal_int(void * key1, void * key2)
{
Función para comparar claves de tipo int retorna 1 si son iguales y 0 si no lo son.
}


int lower_than_int(void * key1, void * key2)
{
Función para comparar claves de tipo int retorna 1 si son key1<key2.
}


long is_equal_long(void * key1, void * key2)
{
Función para comparar claves de tipo long retorna 1 si son iguales
}


long lower_than_long(void * key1, void * key2) 
{
Función para comparar claves de tipo long retorna 1 si son key1<key2
}

int compare(void * key1, void * key2)
{
Función que retorna negativo si queremos que key1 vaya antes que key2 
en el mapa, retorna 0 si consideramos que las dos claves son iguales 
y positivo si key1 debe ir antes.
}
~~~
---
~~~
/*------- Advertencia -------*/
void Advertencia()
{
Muestra en pantalla una advertencia sobre que tipo de caracteres no se pueden ingresar.
}
//-----------------------------------------//



/*------- Presionar Enter -------*/
void pressEnter()
{
Solicita que se presione Enter, deteniendo el programa hasta que se cumpla lo solicitado.
}
//-----------------------------------------//



/*------- Mostrar Menú -------*/
void MostrarMenu()
{
Muestra en pantalla las 8 opciones disponibles en el menu y nos solicitan escoger 1.
}
//-----------------------------------------//


/*------- Copiar string en un nuevo espacio de memoria -------*/
char * _strdup(const char * str)
{
Crea un string con una nueva direccion de memoria, donde copiara el string recibido y retornara el string creado.
}
//-----------------------------------------//
~~~
---
~~~
//**************************  OPCIÓN 1  ***********************//

/*----------------- Lista con los text a abrir -----------------*/
List *cantArchiveOpen(char *Archives, size_t *cant, bool quitarSaltoLinea))
{
Recibe un string de mas de una palabra separadas por espacio, separa las palabras en distintas cadenas, las guarda en una lista y retorna la lista con las palabras, y si la booleana recibida es verdadero, quitara el salto de linea de la ultima palabra, ademas de aumentar el contador conforme guarda palabras en la direccion de memoria del entero que recibio, haciendo que el entero recibido se convierta en la cantidad de palabras guardadas en la lista.
}
//-----------------------------------------//

/*------- Abrir o no el archivo -------*/
int esText(char *nombreArchivo, List *archiveToOpen, size_t *cant)
{
Coprueba si el archivo en el que estamos del directorio concuerda con uno de los archivos que debemos arbrir, si no debemos abrir el archivo en el que estamos del directorio retorna 0, si debemos abrirlo retorna 1.
}
//-----------------------------------------//

/*------- Conseguir path al txt -------*/
char *get_nameFile(char *archive, char *directory)
{
Crea el camino necesario para entrar al archivo txt dentro del directorio y lo retorna.
}
//-----------------------------------------//

/*------- Elimina caracteres no alfabeticos -------*/
void quitarNoAlfabeticos(char *beforeString, bool quitarSpaces)
{
Recibe una cadena de caracteres y una variable tipo bool para saber si quitar o no los escpacios de la cadena de caracteres. Elimina los valores que no son alfabeticos de la cadena, si se quita o no el espacio depende del booleano recibido.
}
//-----------------------------------------//

/*------- separar palabras del file -------*/
char* nextWord (FILE *f)
{
Toma la siguiente palabra del archivo f, deja solo los caracteres alfabeticos con quitarNoAlfabeticos() y la retorna. O retorna Null si no existe palabra siguiente.
}
//-----------------------------------------//

/*------- separar palabras del file -------*/
char* get_title(FILE *f)
{
Lee el titulo del archivo f, deja solo los caracteres alfabeticos y los espacios con quitarNoAlfabeticos() y lo retorna. En caso de  que no exista, retorna NULL.
}
//-----------------------------------------//

/*------- Crear struct LibrosConPalabra -------*/
LibrosConPalabra *createBookConWord(unsigned long idToBook, char* titleToBook){
Crea un dato tipo struct LibrosConPalabra con los valores que recibe guardandolos donde corresponden. Y retorna la struct LibrosConPalabra creada.
}
//-----------------------------------------//

/*------- Crear struct Palabra -------*/
Palabra *createWord(char *WORD){
Crea un dato tipo struct Palabra con los valores que recibe guardandolos donde corresponden. Y retorna la struct LibrosConPalabra creada.
}
//-----------------------------------------//

/*------- Crear struct PalabraEnLibro -------*/
PalabraEnLibro *createWordEnBook(char* nameToWord)
{
Crea un dato tipo struct PalabraEnLibro con los valores que recibe guardandolos donde corresponden. Y retorna la struct LibrosConPalabra creada.
}
//-----------------------------------------//

/*------- Crear struct Libro -------*/
Libro *createBook(char *WORD, unsigned long ID, char *TITLE, char *TXT){
{
Crea un dato tipo struct Libro con los valores que recibe guardandolos donde corresponden. Y retorna la struct LibrosConPalabra creada.
}
//-----------------------------------------//

/*------- Transforma en minuscula los caracteres alfabeticos -------*/
void minsuculas(char *cadena)
{
Recibe una cadena de caracteres y deja todas las letras alfabetiacas en minuscula.
}
//-----------------------------------------//

/*------- Guardar en los mapas la informacion -------*/
void saveWordsInMaps(char *wordToSave, char* titleToSave, char *idToSave, 
                     Map *words_Map, Map *books_Map, char *txt){
{

}
//-----------------------------------------//

/*------- Leer Archivo -------*/
void ReadTxt(Map* string_map, Map* book_map, char *name, char *nameDirectory, int *docTotal)
{

}

/*----------------- OPCIÓN 1: -----------------*/
void CargarDocumento(Map *palabrasMap, Map *librosMap, int *dTotal)
{

}
//-------------------------------------------------------------//

//**************************************************************//
~~~
***
~~~
//**************************  OPCIÓN 2  ***********************//

/*------- Mostrar Libro -------*/
void mostrarLibro(Libro* aux)
{

}
//-----------------------------------------//

/*----------------- OPCIÓN 2: -----------------*/
void MostrarDocumentosOrdenados(Map *allBooks)
{

}
//-------------------------------------------------------------//

//**************************************************************//
~~~
---
~~~
//**************************  OPCIÓN 3  ***********************//

/*------- Comparar Strings -------*/
int compare_strings(char cadena1[101], char *cadena2)
{

}
//-----------------------------------------//

/*------- Busca y muestra libro por el titulo -------*/
void BuscarLibroTitulo(Libro* book, Map* booksMap, char* title)
{

}
//-----------------------------------------//

/*----------------- OPCIÓN 3: -----------------*/
void BuscarLibro(Libro* book, Map* booksMap)
{

}
//-------------------------------------------------------------//

//**************************************************************//
~~~
---
~~~
//**************************  OPCIÓN 4  ***********************//

/*------- Calcula la frecuencia de cada una -------*/
void calcularFrecuencia(PalabraEnLibro *aux, double cantWords){
Calcula y guarda la frecuencias en el dato tipo struct PalabraEnLibro
}
//-----------------------------------------//

/*------- Funcion comparar para ordenar con qsort por relevancia -------*/
int compararFrecuencia (const void *a,const void *b)
{
Funcion comparar necesaria para el qsort, en este caso ordena las frecuencias de mayor a menor.
}
//-----------------------------------------//

/*------- Muestra la palabraDelLibro con su frecuencia y ocurrencia -------*/
void mostrarWordDelLibro(PalabraEnLibro *see, int num){
Muestra por pantalla la palabra recibida, sus repeticiones y su frecuencia, ademas de un numero inicial con la que contiene mayor frecuencia con un numero 1 precedente
}
//-----------------------------------------//

/*------- Crear Arreglo en el orden requerido -------*/
void MostrarMasFrecuentes(Libro *BOOK)
{
Crea un arreglo del struct PalabraEnLibro con 11 de largo.
Crea un aux con la primera palabra guardada del libro.
Crea un contador que se usara para saber si el libro esta lleno.

Crea un while para recorrer la lista de palabras dentro del libro.
    - Calcula y guarda la frecuencia de la palabra en el libro con la funcion CalcularFrecuencia().
    - Usa if con el contador para saber si se han guardado todos menos el ultimo espacio del arreglo
        Si contador < 10, entonces:
        - Guarda las primeras 10 palabras con sus frecuencias calculadas en los espacios del 0-9 del arreglo.
        - Aumenta el tamaño del contador
        Si no, entonces:
        - Guarda una nueva palabra en la posicion [10] del arreglo con su frecuencia calculada.
        - Utiliza qsort mandando una la funcion compararFrecuencia() para ordenar las palabras por su frecuencia de mayor a menor, dejando en 
          la posicion [10] al menor, que seria el menor de los 11 y se podria remplazar, ya que buscamos los 10 mayores.
    Pasa a la siguiente palabra de la lista con nextList().

Utiliza for para recorrer el arreglo con las 10 palabras con mayor frecuencia del arreglo.
    Muestra la palabra guardada en el arreglo, su posicion (si es la primera o la segunda mas frecuente), la cantidad de veces que aparece en el libro y su frecuencia con la funcion mostrarWordDelLibro().
}
//-----------------------------------------//

/*----------------- OPCIÓN 4: -----------------*/
void PalabrasConMayotFrecuencia(Map* allBooks)
{
    Recibe el mapa con los (libros cargados.

    Solicita la id del libro.

    Revisa con un if searchMap() si hay un libro con la id ingresada por el usuario.
        Si no existe, imprime un mensaje explicando la situacion.
    
    Si existe, mostraria las 10 palabras mas frecuentes en el libro con la funcion MostrarMasFrecuentes().
}
//-------------------------------------------------------------//

//**************************************************************//
~~~
---
~~~
//**************************  OPCIÓN 5  ***********************//

/*------- Crea un struct Relevancia -------*/
Relevancia *crearLibro (char *titulo, int numeroDocumento)
{
Se reserva Memoria
se añaden los valores
Y se crea el mapa con una funcion para que esta se ordene de mayor a menor
}
//-----------------------------------------//

/*------- Crea un struct PalabraRelevante -------*/
PalabraRelevante *crearpalabra (float relevancia)
{
Se reserva memoria.
se añade los valores
y se crea una lista.
}
//-----------------------------------------//

/*------- Calcula la relevancia de la palabra -------*/
float calcularRel (unsigned long libroConPalabra, unsigned long cantPalabrasLibro, int contador, float ocurrenciasString)
{
Se calcula el logaritmo de (contador/libroConPalabra)
Se calcula la division entre (ocurrenciasString/CantPalabrasLibro)

Esto lo hice asi para ver donde me daba problemas una vez solucionado lo deje asi por si hacia un cambio dejaba de funcionar xd

Returna la multiplicacion entre logaritmo y division
}
//-----------------------------------------//

/*------- Borra completamente un mapa -------*/
void borrarMapa (Map *mapaErase)
{
Recorre el mapa y los va borrando.
}
//-----------------------------------------//

/*------- Calcula y guarda la relevancia de todas las palabras del libro -------*/
void relevanciaCreate (Map *relevancia_map, Map *libros_map, Map *palabras_map)
{

Se pregunta si el mapa libro_map existe
/en caso de no ser asi se envia un mensaje y se sale de la funcion

se declaran las variables necesarias

se hace un ciclo while para saber cuantos libros hay en el mapa libros_map
-Si el contador es 1 se envia un mensaje y se sale de la funcion.
    -Esto es porque si es solo 1 documento sera un logatimo (1/1) ya que todas las palabras se repiten por ser 1 solo documento y log (1) es 0 por lo cual todas las palabras dan 0
    
un if donde se pregunta si el mapa de relevancia es NULL o no

si es NULL:
           -La idea aqui es hacer un mapa de key "titulo del libro" que tenga de  valor otro mapa de key "relevancia",
	   un char para el titulo y un int para la cantidad de documentos.
	   -Despues al mapa de key relevancia tendra valor una lista de palabras y un float para la relevancia
	   -La lista es para guardar muchas palabras en caso de que 2 o mas palabras tengan la misma relevancia
	   
	   Con esto para la busqueda deberia ser asi.
	   -Se pide el nombre del titulo al usuario.
	   -searchmap (maparelevancia, titulo del libro) // para buscar la relevancia de un libro en especifico
	   -despues el mapa (relevancia) esta ordenada por defecto asique el firstMap contendra la/las palabras mas relevantes
	   y dentro de ese mapa estaran la lista con las palabras
	   
Si no es NULL:
                -Se compara si se ha añadido nuevos docuementos en caso de ser asi entrara en el if
		-dentro del if se borrara el mapa de relevancia
		-Y se hace uno nuevo apartir de los nuevos documentos hechos de la misma manera que anteriormente explicado.
		-esto porque al añadir mas documentos cambia el valor de la relevancia en una gran cantidad de palabras.
		
		-En caso de que no se haya añadido nuevos documentos no se ejecutara nada.
		
}
//-----------------------------------------//

/*----------------- OPCIÓN 5: -----------------*/
void mostrarRelevancia (Map * mapa)
{

Primero se ve si el mapa existe
/En caso de que no existe se dice por pantalla y se sale de la funcion.

recorre el mapa y muestra los libros disponibles

Despues se le pregunta al usuario cual libro quiere ver las palabras

Busca la palabra dentro del mapa con key titulo del libro
/Si escribe mal o coloca algo nada que ver se le mandara un mensaje diciendo que algo ocurrio y se sale de la funcion

Despues muestra por pantalla las 10 palabras del libro escrito por el usuario.

}
//-------------------------------------------------------------//

//**************************************************************//
~~~
---
~~~
//**************************  OPCIÓN 6  ***********************//

/*------- Calcula Relevancia -------*/
double calcularRelevancia(unsigned long ocurrenciaP,
	unsigned long palabrasD, int docs, unsigned long librosConP)
{

}
//-----------------------------------------//

/*------- Funcion comparar para ordenar con qsort por relevancia -------*/
int cmpfunc (const void *a,const void *b)
{

}
//-----------------------------------------//

/*----------------- OPCIÓN 6: -----------------*/
void *buscarPorPalabra(Map *mapaLibros, Map *mapaPalabras, int docs)
{

}
//-------------------------------------------------------------//

//**************************************************************//
~~~
---
~~~

//**************************  OPCIÓN 7  ***********************//

/*------- Mostrar o no Linea -------*/
bool MostrarLinea(char *line, char *worD)
{
Recibe la linea y la palabra.

Separa la linea por espacios y cada palabra de la linea la guarda en una lista.

Utiliza un while para recorrer la lista con las palabras de la linea, que no termina hasta que recorra todas las palabras de la linea.
    - Quita los caracteres no alfabeticos de la palabra de la linea con la funcion quitarNoAlfabeticos.
    - Ponea en minuscula la palabra de la linea con la funcion minusculas().
    - Utiliza un if para comprobar si la palabra de la linea es igual a la palabra buscada.
        Si es igual, retorna true.
    -Usa nextList() para pasar a la siguiente palabra de la linea

Si recorrio todo la linea sin retornanr true, retorna false
}
//-----------------------------------------//

/*------- Abrir y leer el libro -------*/
void AbrirTxt(Map* string_map, Map* book_map, char *titulo, char *path)
{
Recibe los mapas de palabras y libros, el titulo y el camino que se usa para abrir el libro con el titulo correspondiente.

Abre el archivo del libro con el path recibido.

Solicita y guarda la palabra a buscar en una variable.

La separa por espacio en caso de que haya puesto mas de una, se queda solo con la primera si hay mas de una.
	
Quita los caracteres no alfabeticos de la palabra a buscar y deja la palabra a buscar en minuscula.

Define un contador = 0 para saber si se encontro la palabra en el libro.

Utiliza un while que lee lineas del archivo y se detiene cuando el archivo termina.
    - Utiliza un if con la funcion MostrarLinea() que retorna un booleano para saber si la palabra esta en la
      linea leida
        Si entra pasa lo siguiente:
          - Si cont es 0 entonces imprime un mensaje de comienzo antes de imprimir los contextos de la palabra.
          - Imprime la linea.

Utiliza un if para ver si no se imprimio ninguna linea.
    Si no se imprimio ninguna linea, manda un mensaje explicando que la palabra no se encuentra en el texto

Cierra el archivo.
}
//-----------------------------------------//

/*------- Conseguir el .txt para abrir el libro -------*/
void BuscarIdLibro(Map *book_actual, Map *word_actual,  char *title)
{
Recibe 2 mapas y el titulo.

Le quita el salto de linea al titulo.

Comprueba si el libro fue previeamente cargado con un el mapa de libros if y la funcion searchMap()
	Si no existe el libro, imprime un mensaje con la situacion.

Manda a la funcion AbrirTxt() los 2 mapas, el titulo, y el path del archivo del libro
	Esta funcion abre el archivo, solicita la palabra y muestra su contexto.
}
//-----------------------------------------//

/*----------------- OPCIÓN 7: -----------------*/
void MostrarContexto(Map *palabrasMap, Map *librosMap)
{
Lee el titulo ingresado por el usuario.

Envia los mapas recibidos y el titulo a la funcion BuscarIdLibro()
    En esta funcion nos mostraria el contexto de una palabra en el libro si existe-
}
//-------------------------------------------------------------//

//**************************************************************//
~~~
---
~~~
---

////////////////////////////////////////////////////////
////////////////////////////////////////////////////////
////////////////////////////////////////////////////////
////////////////////////////////////////////////////////

## Codigo:

Parte creando 2 mapas, uno para las palabras y otro para los libros

Crea una variable int 'option' en 0.

Imprime una advertencia con la función Advertencia() y solicita enter para continuar con la funcion pressEnter().

Crea un while con la condicion 'option != 8'.
- Dentro del while imprime un menu en pantalla con la funcion MostrarMenu().
- Solicita escoger una opcion y guarda la respuesta en la variable 'option'.
- Usa un if('option == 8') donde si se cumple, se sale del while con break.
- Crea un switch con 'option de condicion', con casos del 1 al 11, mas un default que realizara el proceso que corresponde de acuerdo a los numeros de cada opción en el menu mostrado previamente.
- Solicita que el usuario presione Enter para continuar con la funcion pressEnter().
---

#### A continuacion se explicaran cada caso del switch que esta presente dentro del while:
~~~
/--------------------------------------------------------------------------------------------------------------/

 option =  1:
 Carga los archivos del directorio con los nombres ingresados por el usuarion y guarda informacion en los mapas de palabras y libros. Utiliza la funcion CargarDocumento() para realizar sus funciones.

/--------------------------------------------------------------------------------------------------------------/

 option =  2:
 

/--------------------------------------------------------------------------------------------------------------/

 option =  3:
 
 
/--------------------------------------------------------------------------------------------------------------/

 option =  4:
 
 
/--------------------------------------------------------------------------------------------------------------/

 option =  5:
 
 La primera funcion calcula la relevancia y esta tiene 5 opciones:
 
 1.Si el mapa no fue creado se crea una y se calcula la relevancia.
 
 2.Si se añaden nuevos documentos y el mapa ya fue creado, se borra el mapa y se crea uno nuevo con los nuevos datos.
 
 3.Si el mapa de libros no existe devuelve un mensaje diciendo que no se ha cargado documentos.
 
 4.Si la cantidad de documentos es igual a 1 se dice al usuario que todas las palabras tendran relevancia 0.
 
 5.Si el mapa existe y no se han cargado nuevos documentos no se hara nada.
 
 La segunda funcion pregunta al usuario sobre que libro quiere saber las palabras relevantes
 una vez escrito si existe se muestra por pantalla las 10 palabras mas relevantes
 si no existe se le dice al usuario que no escribio bien .
 
/--------------------------------------------------------------------------------------------------------------/

 option =  6:
 
 
/--------------------------------------------------------------------------------------------------------------/

 option =  7:
 Solicita un titulo de libro, si no fue cargado previamente termina su funcion imprimiendo un mensaje de explicacion, si fue cargado correctamente, solicita una palabra para despues mostrarla en el contexto.
 Utiliza la funcion MostrarContexto() para cumplir su cometido.

/--------------------------------------------------------------------------------------------------------------/

 option =  8:
 
 exit.
 
/--------------------------------------------------------------------------------------------------------------/

 default:
 

/--------------------------------------------------------------------------------------------------------------/
~~~
