# Tarea3 Huachipato

Estudiantes PUCV curso: ICI2240-1  ESTRUCTURA DE DATOS

## **_Integrantes_**

- ### Ademir Muñoz: 
    Pts premio/castigo: 0.

    Siento que deberia mejorar la forma de hacer los algoritmos siempre encuentro una falla en estos y tengo que modificarlo para que despues aparesca otro originado por el cambio anterior y asi.


- ### Lucas Robles: 
    Pts premio/castigo: 0.

    Siento que en el momento que supe que trabajariamos con directorios, deberia haber investigado como era posible, fue dificil lograr abrir bien el directorio, ademas de que empece a hacer esta tarea mas tarde de lo que deberia


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

![Clonar Repositorio](https://drive.google.com/uc?id=1R42hQG_1DG673nJbgIc5LBCiScYoAu3g)

Abrir el clon del repositorio con VSCode. Una vez abierto se debe abrir terminal powershell.

Con la terminal powershell abierta se escribe lo siguiente:

![gcc](https://drive.google.com/uc?id=1nEugVI19nlxOMiG2Rjv-kGEOZiIAbafy)

De esa forma se creo o modifico el ejecutable, que se ejecuta de la siguiente manera:

![Ejecutable](https://drive.google.com/uc?id=1QEmvjK3MmqGN9h4Ow203dbGWbx2zi7JZ)

Despues de una advertencia al ejecutar el Test, se desplegaria el menu

Este sería el menú.

![gcc](https://drive.google.com/uc?id=1OxVB_gnCHkasXMonj8im3nPW8chb5co8)


## 2. Las opciones que funcionan correctamente y las que no lo hacen indicando posibles causas
Hasta ahora todas las funciones están funcionales en casos normales ósea sin que el usuario intente apretar letras al azar o colocando datos sin pensar.


## Structs:
Contiene 2 struct, una para las canciones y otra destinada a las listas de reproducción

![Menú](https://drive.google.com/uc?id=1O5O7Lz_MY8g0kLvSteIbZcGueSIJsLyr)


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
Función para comparar claves de tipo int retorna 1 si son key1<key2
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
List *cantArchiveOpen(char *Archives, size_t *cant)
{

}
//-----------------------------------------//

/*------- Abrir o no el archivo -------*/
int esText(char *nombreArchivo, List *archiveToOpen, size_t *cant)
{

}
//-----------------------------------------//

/*------- Conseguir path al txt -------*/
char *get_nameFile(char *archive, char *directory)
{

}
//-----------------------------------------//

/*------- separar palabras del file -------*/
char* nextWord (FILE *f)
{

}
//-----------------------------------------//

/*------- separar palabras del file -------*/
char* get_title(FILE *f)
{

}
//-----------------------------------------//

/*------- Crear struct LibrosConPalabra -------*/
LibrosConPalabra *createBookConWord(unsigned long idToBook, char* titleToBook){

}
//-----------------------------------------//

/*------- Crear struct Palabra -------*/
Palabra *createWord(char *WORD){

}
//-----------------------------------------//

/*------- Crear struct PalabraEnLibro -------*/
PalabraEnLibro *createWordEnBook(char* nameToWord)
{

}
//-----------------------------------------//

/*------- Crear struct Palabra -------*/
Libro *createBook(char *WORD, unsigned long ID, char *TITLE)
{

}
//-----------------------------------------//

/*------- Guardar en los mapas la informacion -------*/
void saveWordsInMaps(char *wordToSave, char* titleToSave, char *idToSave, 
                     Map *words_Map, Map *books_Map)
{

}
//-----------------------------------------//

/*------- Leer Archivo -------*/
void ReadTxt(Map* string_map, Map* book_map, char *name, char *nameDirectory)
{

}

/*----------------- OPCIÓN 1: -----------------*/
void CargarDocumento(Map *palabrasMap, Map *librosMap)
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

/*----------------- OPCIÓN 3: -----------------*/
void BuscarLibroTitulo(Libro* book, Map* booksMap, char* title)
{

}
//-------------------------------------------------------------//

//**************************************************************//
~~~
---
~~~
//**************************  OPCIÓN 4  ***********************//

/*------- Calcula la frecuencia de cada una -------*/
void calcularFrecuencia(Libro *onlyBook)
{

}
//-----------------------------------------//

/*----------------- OPCIÓN 4: -----------------*/
void PalabrasConMayotFrecuencia(Map* allBooks)
{

}
//-------------------------------------------------------------//

//**************************************************************//
~~~
---
~~~
//**************************  OPCIÓN 5  ***********************//

//-------------------------------------------------------------//

//**************************************************************//
~~~
---
~~~
//**************************  OPCIÓN 6  ***********************//

/*------- Muestra un libro y una id -------*/
void mostrarLibroConPalabra(LibrosConPalabra *libro)
{

}

//-----------------------------------------//

/*----------------- OPCIÓN 6: -----------------*/
void *buscarPorPalabra(Map *mapaLibros, Map *mapaPalabras)
{

}
//-------------------------------------------------------------//

//**************************************************************//
~~~
---
~~~
//**************************  OPCIÓN 7  ***********************//

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


/--------------------------------------------------------------------------------------------------------------/

 option =  2:
 

/--------------------------------------------------------------------------------------------------------------/

 option =  3:
 
 
/--------------------------------------------------------------------------------------------------------------/

 option =  4:
 
 
/--------------------------------------------------------------------------------------------------------------/

 option =  5:
 

/--------------------------------------------------------------------------------------------------------------/

 option =  6:
 
 
/--------------------------------------------------------------------------------------------------------------/

 option =  7:
 

/--------------------------------------------------------------------------------------------------------------/

 option =  8:
 
 
/--------------------------------------------------------------------------------------------------------------/

 option =  9:
 

/--------------------------------------------------------------------------------------------------------------/

 option = 10:
 

/--------------------------------------------------------------------------------------------------------------/

 option = 11:
 

/--------------------------------------------------------------------------------------------------------------/

 default:
 

/--------------------------------------------------------------------------------------------------------------/
~~~
