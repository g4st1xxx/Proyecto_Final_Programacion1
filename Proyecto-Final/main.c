#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define NUM_CIUDADES 100
#define NUM_VUELOS 200

struct Horario {
    char salida[6];
    char llegada[6];
};

struct Vuelo {
    int id;
    float precio;
    struct Horario horario;
    char fecha[11];
    char origen[50];
    char destino[50];
    int duracion;
    int asientosDisponibles;
};

char *ciudades[] = {
    "Tokio", "Delhi", "Shanghai", "Sao Paulo", "Mumbai",
    "Ciudad de Mexico", "El Cairo", "Pekin", "Osaka", "Nueva York",
    "Daca", "Karachi", "Buenos Aires", "Estambul", "Rio de Janeiro",
    "Manila", "Lagos", "Los Angeles", "Calcuta", "Moscú",
    "Yakarta", "Lima", "Teherán", "Bangkok", "Chennai",
    "Bangalore", "Londres", "Bogotá", "Ho Chi Minh", "Lahore",
    "Tianjin", "Wuhan", "Chongqing", "Chengdu", "Hong Kong",
    "Shenzhen", "Suzhou", "Pune", "Jaipur", "Nagoya",
    "Kolkata", "Istanbul", "Ciudad de Mexico", "Lagos", "Lahore",
    "Lima", "Bangkok", "Seul", "Yakarta", "Bogotá",
    "Tehran", "Cairo", "Londres", "Pekin", "Shanghai",
    "Sao Paulo", "Los Angeles", "Moscú", "Nueva York", "Bombay",
    "Delhi", "Ciudad de Mexico", "Lima", "Lagos", "Ciudad de Lagos",
    "El Cairo", "Shanghai", "Karachi", "Istanbul", "Tianjin",
    "Tokio", "Delhi", "Shanghai", "Sao Paulo", "Mumbai",
    "Ciudad de Mexico", "El Cairo", "Pekin", "Osaka", "Nueva York",
    "Daca", "Karachi", "Buenos Aires", "Estambul", "Rio de Janeiro",
    "Manila", "Lagos", "Los Angeles", "Calcuta", "Moscú",
    "Yakarta", "Lima", "Teherán", "Bangkok", "Chennai",
    "Bangalore", "Londres", "Bogotá", "Ho Chi Minh", "Lahore",
    "Tianjin", "Wuhan", "Chongqing", "Chengdu", "Hong Kong"
};

void generarHoraAleatoria(char *hora) {
    int horas = rand() % 24;
    int minutos = rand() % 60;
    snprintf(hora, 6, "%02d:%02d", horas, minutos);
}

void generarFechaAleatoria(char *fecha) {
    int year = 2024;
    int month = rand() % 12 + 1;
    int day = rand() % 28 + 1;
    snprintf(fecha, 11, "%04d-%02d-%02d", year, month, day);
}

char *obtenerCiudadAleatoria() {
    return ciudades[rand() % NUM_CIUDADES];
}

struct Vuelo generarVuelo(int id) {
    struct Vuelo vuelo;
    vuelo.id = id;
    vuelo.precio = (float)(rand() % 1000 + 100);  // Precio entre 100 y 1099 USD
    generarHoraAleatoria(vuelo.horario.salida);
    generarHoraAleatoria(vuelo.horario.llegada);
    generarFechaAleatoria(vuelo.fecha);
    snprintf(vuelo.origen, sizeof(vuelo.origen), "%s", obtenerCiudadAleatoria());
    snprintf(vuelo.destino, sizeof(vuelo.destino), "%s", obtenerCiudadAleatoria());
    while(strcmp(vuelo.origen, vuelo.destino) == 0){
        snprintf(vuelo.destino, sizeof(vuelo.destino), "%s", obtenerCiudadAleatoria());
    }
    vuelo.duracion = rand() % 720 + 60;  // Duración entre 60 y 779 minutos
    vuelo.asientosDisponibles = rand() % 101;
    return vuelo;
}

void guardarVuelosEnArchivo(struct Vuelo vuelos[], int numVuelos, const char *archivo) {
    FILE *archi = fopen(archivo, "wb");
    if (archi == NULL) {
        perror("Error abriendo el archivo");
        return;
    }

    for (int i = 0; i < numVuelos; i++) {
        fprintf(archi, "ID: %d\n", vuelos[i].id);
        fprintf(archi, "Precio: %.2f USD\n", vuelos[i].precio);
        fprintf(archi, "Horario: Salida %s - Llegada %s\n", vuelos[i].horario.salida, vuelos[i].horario.llegada);
        fprintf(archi, "Fecha: %s\n", vuelos[i].fecha);
        fprintf(archi, "Origen: %s\n", vuelos[i].origen);
        fprintf(archi, "Destino: %s\n", vuelos[i].destino);
        fprintf(archi, "Duración: %d minutos\n", vuelos[i].duracion);
        fprintf(archi, "Asientos disponibles: %i \n\n", vuelos[i].asientosDisponibles);
    }

    fclose(archi);
}

void guardarVuelosEnArchivoSimplificado(struct Vuelo vuelos[], int numVuelos, const char *archivo) {
    FILE *archi = fopen(archivo, "wb");
    if (archi == NULL) {
        perror("Error abriendo el archivo");
        return;
    }

    for (int i = 0; i < numVuelos; i++) {
        fprintf(archi, "%d\n", vuelos[i].id);
        fprintf(archi, "%.2f\n", vuelos[i].precio);
        fprintf(archi, "%s %s\n", vuelos[i].horario.salida, vuelos[i].horario.llegada);
        fprintf(archi, "%s\n", vuelos[i].fecha);
        fprintf(archi, "%s\n", vuelos[i].origen);
        fprintf(archi, "%s\n", vuelos[i].destino);
        fprintf(archi, "%d\n", vuelos[i].duracion);
        fprintf(archi, "%i\n\n", vuelos[i].asientosDisponibles);
    }

    fclose(archi);
}

///Si estas funciones las puedo meter en una biblioteca va a ser mejor, lo unico que necesito es el array
///Desde aca comienzan las funciones de pasajeros



typedef struct{
    char dni[9];
    int edad;
    char nombre[25];
    char apellido[25];
}acompanante;

typedef struct{
    char dni[9];
    int edad;
    char nombre[25];
    char apellido[25];
    int acompanantesValidos;
    acompanante *acompanantes;
}pasajero;

///La recomendacion de Nico es que las dos funciones inferiores se integren y formen una, los comentarios de abajo son
///sus sugerencias:

    ///hasta q el usuario queira terminar
    ///while (flag = 0)
    /// ingresa los datos
    /// validar que los datos esten bien
    ///si estan bien, guardarlos en x cosa y la flag = 1
    ///y si no tirar un ms y q ingrese de nuevo los datos la flag sigue siendo 0
    ///pero si quiere no registrarse, regresar un pasajero con dni = 0 y que en el main no lo guarde

pasajero crearPasajero(){
    pasajero pasajerito;

    printf("\nIngrese su DNI: ");
    fflush(stdin);
    scanf("%s", &pasajerito.dni);
    printf("Ingrese su edad: ");
    fflush(stdin);
    scanf("%i", &pasajerito.edad);
    printf("Ingrese su nombre: ");
    fflush(stdin);
    scanf("%s", &pasajerito.nombre);
    printf("Ingrese su apellido: ");
    fflush(stdin);
    scanf("%s", &pasajerito.apellido);

    printf("Ingrese la cantidad de acompañantes que desea incorporar: ");
    fflush(stdin);
    scanf("%i", &pasajerito.acompanantesValidos);

    int temp = pasajerito.acompanantesValidos;
    pasajerito.acompanantesValidos = 0;

    pasajerito.acompanantesValidos = cargarArrayAcompanantes(&pasajerito.acompanantes, &pasajerito.acompanantesValidos, temp);

    printf("\n");
    return pasajerito;
}
int comprobacionDatosPasajero(pasajero pasajerito){
    if(
        strlen(pasajerito.dni) != 8 ||
        pasajerito.edad > 150 ||
        strlen(pasajerito.nombre) > 24 ||
        strlen(pasajerito.apellido) > 24 ||
        pasajerito.acompanantesValidos < 0 ||
        pasajerito.acompanantesValidos > 10){
        return 0;
    }else{
        return 1;
    }
}

pasajero crearPasajeroYComprobarDatos(){
    char seguir = 's';
    int comprobacion = 0;
    pasajero pasajerito;
    while(seguir == 's' && comprobacion != 1){
        pasajerito = crearPasajero();
        comprobacion = comprobacionDatosPasajero(pasajerito);

        if (comprobacion == 0){
            printf("Los datos ingresados son erroneos, por favor, ingrese s si desea intentarlo nuevamente: ");
            fflush(stdin);
            scanf("%c", &seguir);
        }
    }
    if(comprobacion == 0){
        strcpy(pasajerito.dni, "0");
        return pasajerito;
    }
    return pasajerito;
}

void cargarArrayPasajeros(pasajero **pasajeros, int *validos){

char seguir = 's';
    pasajero pasajerito;
    int i = 0;

    while(seguir == 's'){
        *pasajeros = (pasajero*)realloc(*pasajeros, (sizeof(pasajero) * (i + 1)));
        pasajerito = crearPasajeroYComprobarDatos();

        (*pasajeros)[i] = pasajerito;

        i++;

        if(!strcmp(pasajerito.dni, "0")){
            i--;
            eliminarPasajero(*pasajeros, validos, i);
        }

        *validos = i;

        printf("Desea seguir cargando pasajeros?: \n");
        fflush(stdin);
        scanf("%c", &seguir);
        }
}

//funciones copia para acompañantes

acompanante crearAcompanante(){
    acompanante compi;

    printf("\nIngrese el DNI del acompañante: ");
    fflush(stdin);
    scanf("%s", &compi.dni);
    printf("Ingrese la edad del acompañante: ");
    fflush(stdin);
    scanf("%i", &compi.edad);
    printf("Ingrese el nombre del acompañante: ");
    fflush(stdin);
    scanf("%s", &compi.nombre);
    printf("Ingrese el apellido del acompañante: ");
    fflush(stdin);
    scanf("%s", &compi.apellido);

    printf("\n");
    return compi;
}
int comprobacionDatosAcompanante(acompanante compi){
    if(
        strlen(compi.dni) != 8 ||
        compi.edad > 150 ||
        strlen(compi.nombre) > 24 ||
        strlen(compi.apellido) > 24){
        return 0;
    }else{
        return 1;
    }
}

acompanante crearAcompananteYComprobarDatos(){
    char seguir = 's';
    int comprobacion = 0;
    acompanante compi;
    while(seguir == 's' && comprobacion != 1){
        compi = crearAcompanante();
        comprobacion = comprobacionDatosAcompanante(compi);

        if (comprobacion == 0){
            printf("Los datos ingresados son erroneos, por favor, ingrese s si desea intentarlo nuevamente: ");
            fflush(stdin);
            scanf("%c", &seguir);
        }
    }
    if(comprobacion == 0){
        strcpy(compi.dni, "0");
        return compi;
    }
    return compi;
}

int cargarArrayAcompanantes(acompanante **acompanantes, int *validos, int dim){

    char seguir = 's';
    acompanante compi;
    int i = 0;



    *acompanantes = (acompanante*)malloc(sizeof(acompanante) * dim);

    while(seguir == 's' && *validos < dim){

        printf("\nCarga del acompañante nro: %i\n", i);

        compi = crearAcompananteYComprobarDatos();
        (*acompanantes)[i] = compi;
        i++;

        if(!strcmp(compi.dni, "0")){
            i--;
            eliminarAcompanante(*acompanantes, validos, i);
            printf("\nSe eliminó el acompañante cargado por un error en la comprobación de datos.\n");
        }
        *validos = i;

        printf("Desea seguir cargando acompañantes?: \n");
        fflush(stdin);
        scanf("%c", &seguir);
        }
        return *validos;
}

void eliminarAcompanante(acompanante acompanantes[], int *validos, int indice) {
    if (indice < 0 || indice >= *validos) {
        printf("Índice fuera de rango\n");
        return;
    }

    for (int i = indice; i < *validos - 1; i++) {
        acompanantes[i] = acompanantes[i + 1];
    }

    (*validos)--;
}

void mostrarAcompanante(acompanante compi){
    printf("\nDNI: %s\n", compi.dni);
    printf("Edad: %i\n", compi.edad);
    printf("Nombre: %s\n", compi.nombre);
    printf("Apellido: %s\n", compi.apellido);
}

void modificarElementoArrayAcompanantes(acompanante *acompanantes, int validos, int indice){

    if (indice < 0 || indice >= validos) {
        printf("Índice fuera de rango\n");
        return;
    }

    acompanante compi = crearAcompananteYComprobarDatos();
    if(!strcmp(compi.dni, "0")){
        printf("Los datos ingresados son invalidos, los cambios no seran guardados.\n");
        return;
    }
    acompanantes[indice] = compi;
}

void mostrarArrayAcompanantes(acompanante *acompanantes, int validos){

    for(int i = 0; i < validos; i++){
        mostrarAcompanante(acompanantes[i]);
    }
}

//fin copias

void eliminarPasajero(pasajero pasajeros[], int *validos, int indice) {
    if (indice < 0 || indice >= *validos) {
        printf("Índice fuera de rango\n");
        return;
    }

    for (int i = indice; i < *validos - 1; i++) {
        pasajeros[i] = pasajeros[i + 1];
    }

    (*validos)--;
}

void mostrarPasajero(pasajero pasajerito){
    puts("\n--------------------------------------\n");
    printf("\nDNI: %s\n", pasajerito.dni);
    printf("Edad: %i\n", pasajerito.edad);
    printf("Nombre: %s\n", pasajerito.nombre);
    printf("Apellido: %s\n", pasajerito.apellido);
    printf("Acompañantes: %i\n", pasajerito.acompanantesValidos);
    mostrarArrayAcompanantes(pasajerito.acompanantes, pasajerito.acompanantesValidos);
    puts("\n--------------------------------------\n");
}

void modificarElementoArray(pasajero *pasajeros, int validos, int indice){

    if (indice < 0 || indice >= validos) {
        printf("Índice fuera de rango\n");
        return;
    }

    pasajero pasajerito = crearPasajeroYComprobarDatos();
    if(!strcmp(pasajerito.dni, "0")){
        printf("Los datos ingresados son invalidos, los cambios no seran guardados.\n");
        return;
    }
    pasajeros[indice] = pasajerito;
}

void mostrarArrayPasajeros(pasajero *pasajeros, int validos){

    for(int i = 0; i < validos; i++){
        mostrarPasajero(pasajeros[i]);
    }
}

/*

    CONECTAR LOS PASAJEROS CON LOS VIAJES DE ALGUNA FORMA
    IMPRIMIR BOLETO CON TODOS ESTOS DATOS

*/

int buscarYRetornarVuelos(Vuelo vuelos[]){

    int eleccion;

    printf("¿De qué modo desea buscar un nuevo viaje?\n\n");
    printf("1: Por nombre de ciudad\n2: Por ID\n3: Por menor precio\n");

    printf("Su elección: ");
    fflush(stdin);
    scanf("%i", &eleccion);

    switch(eleccion){
    case 1:
        buscarVuelosPorNombre();
        break;
    case 2:
        buscarVuelosPorId();
        break;
    case 3:
        buscarVuelosPorMenorPrecio();
        break;
    }
}



void main()
{

    ///Generación Archivo y Array Vuelos.


    srand(time(NULL));

    struct Vuelo vuelos[NUM_VUELOS];

    for (int i = 0; i < NUM_VUELOS; i++) {
        vuelos[i] = generarVuelo(i);
    }

    guardarVuelosEnArchivoSimplificado(vuelos, NUM_VUELOS, "vuelos.bin");

    printf("Se han generado y guardado %i vuelos ficticios en 'vuelos.bin'\n", NUM_VUELOS);


    ///Prototipo generación array pasajeros con array acompañantes anidado


    pasajero *pasajeros = (pasajero*)malloc(0);

    int validos = 0;

    cargarArrayPasajeros(&pasajeros, &validos);

    printf("Se han cargado %i pasajeros", validos);

    mostrarArrayPasajeros(pasajeros, validos);

    printf("\nValidos: %i", validos);



    //prueba git
}

/*

Divagaciones acerca de la interfaz.

Tiene que ser algo visible y comodo, que permita la interaccion del usuario de forma que:

1) Permita al usuario realizar la búsqueda del vuelo que desee

2) Permita al usuario seleccionar el vuelo que desee, junto con los acompañantes que tenga. Este cambio debe verse reflejado en el array "vuelos", reduciendo los asientos disponibles

3) Permita al usuario registrarse el mismo y los acompañantes de su vuelo (casi completado)

//Implementaciones obligatorias:

3) Hay que usar una matriz para el mapeo de los asientos

4) Hay que usar una pila para almacenar los documentos de un boleto






Estoy pensando en crear la estructura "boleto" donde se pueda seleccionar el viaje en cuestion.

Este solo contendria el id del viaje y el indice del pasajero. La funcion seleccionadora restaría la cantidad de integrantes a los asientos disponibles


*/
