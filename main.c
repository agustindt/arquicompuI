#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ncurses.h>
#include <unistd.h>
#include "EasyPIO.h" // Incluir EasyPIO

// Declaraciones de funciones
void mostrarMenu();
void leerOpcion(int *opcion);
void ejecutarSecuenciaAutoFantastico();
void ejecutarSecuenciaElChoque();
extern void ejecutarSecuenciaAdicional1();
extern void ejecutarSecuenciaAdicional2();
void leerPassword(char *password);
int compararPassword(const char *passwordIngresada, const char *passwordCorrecta);
void retardo(unsigned long int *a);
void apagarLuces();
void inicializarNcurses();
void finalizarNcurses();
void configurarPines();
int Leds(int num); // Función para controlar los LEDs

// Variables globales
const char passwordCorrecta[] = "12345"; // Contraseña correcta
unsigned long int velocidadActual = 1000;
// Definición de pines GPIO para los LEDs
const unsigned char led[] = {14, 15, 18, 23, 24, 25, 8, 7}; // Pines GPIO a los cuales están conectados los LEDs
const int numPines = 8; // Número de pines GPIO utilizados

// Función para mostrar el valor de i en binario en una sola línea
void display_binary(int i) {
    int t;
    for (t = 128; t > 0; t = t / 2) {
        if (i & t)
            printf("* ");
        else
            printf("  ");
    }
    printf("\n");
}

int main() {
    int intentos = 0;
    char passwordIngresada[6];

    // Inicialización de EasyPIO
    pioInit();
    inicializarNcurses();
    configurarPines();

    // Proceso de autenticación por contraseña
    while (intentos < 3) {
        printf("Ingrese su password de 5 dígitos: ");
        leerPassword(passwordIngresada);
        if (compararPassword(passwordIngresada, passwordCorrecta)) {
            printf("Bienvenido al Sistema\n");
            break;
        } else {
            printf("Password no válida\n");
            intentos++;
        }
    }

    if (intentos == 3) {
        printf("Ha excedido el número de intentos permitidos\n");
        finalizarNcurses();
        return 1; // Salir del programa
    }

    int opcion = 0;
    while (1) {
        mostrarMenu();
        leerOpcion(&opcion);

        switch (opcion) {
            case 1:
                ejecutarSecuenciaAutoFantastico();
                break;
            case 2:
                ejecutarSecuenciaElChoque();
                break;
            case 3:
                ejecutarSecuenciaAdicional1();
                break;
            case 4:
                ejecutarSecuenciaAdicional2();
                break;
            default:
                printf("Opción no válida. Por favor, intente de nuevo.\n");
                break;
        }
    }

    finalizarNcurses();
    return 0;
}

// Implementaciones de funciones

void mostrarMenu() {
    printf("\n--- Menú de Secuencias de Luces ---\n");
    printf("1. Auto Fantástico\n");
    printf("2. La Carrera\n");
    printf("3. Secuencia Adicional 1\n");
    printf("4. Secuencia Adicional 2\n");
    printf("Seleccione una opción: ");
}

void leerOpcion(int *opcion) { 
    scanf("%d", opcion); // Leer la opción seleccionada por el usuario
}

void leerPassword(char *password) {
    scanf("%5s", password); // Leer exactamente 5 caracteres
}

int compararPassword(const char *passwordIngresada, const char *passwordCorrecta) {
    return strcmp(passwordIngresada, passwordCorrecta) == 0;
}

void retardo(unsigned long int *a) {
    int ch = getch();

    // Detecta la tecla de flecha hacia abajo
    if (ch == KEY_DOWN) {
        *a += 50;
    }
    // Detecta la tecla de flecha hacia arriba
    if (*a > 50 && ch == KEY_UP) {
        *a -= 50;
    }

    // Espera por el tiempo especificado en *a milisegundos
    usleep(*a * 1000);
}


int Leds(int num) {
    int i, numval;
    for (i = 0; i < 8; i++) {
        numval = (num >> i) & 0x01;
        digitalWrite(led[i], numval);
    }
    delayMillis(300); 
    return 0;
}

void apagarLuces() {
    Leds(0); // Apagar todos los LEDs
}

void inicializarNcurses() {
    initscr();
    cbreak();
    noecho();
    nodelay(stdscr, TRUE); // No espera por la entrada del usuario
    keypad(stdscr, TRUE);
}

void finalizarNcurses() {
    endwin();
}

void configurarPines() {
    for (int i = 0; i < numPines; i++) {
        pinMode(led[i], OUTPUT);
    }
}

void ejecutarSecuenciaAutoFantastico() {  
    unsigned long int timeAuto = 500;  // Tiempo de retardo inicial en milisegundos
    unsigned char output = 0x80;
    
    // Ida
    for (int i = 0; i < 8; i++) {
        display_binary(output);
        Leds(output);
        retardo(&timeAuto); // Espera un momento
        output = output >> 1; // Desplazamiento a la derecha
    }
    
    // Vuelta
    for (int i = 0; i < 7; i++) {
        display_binary(output);
        Leds(output);
        retardo(&timeAuto); // Espera un momento
        output = output << 1; // Desplazamiento a la izquierda
    }
}

void ejecutarSecuenciaElChoque() {
    unsigned long int speed = 500;
    unsigned char tabla[] = { 0x81, 0x42, 0x24, 0x18, 0x18, 0x24, 0x42, 0x81 };

    printf("\t |EL CHOQUE|\n\n");
    printf("Presione E para volver al menu principal\n\n\n");
    printf("\tDelay: %ld ms\t\n", speed);
    printf("\n\n");
    
    for (int i = 0; i < 8; ++i) {
        display_binary(tabla[i]);
        Leds(tabla[i]);
        retardo(&speed); // Espera un momento
    }
}


// comentar este void para que funcione el assembly


void ejecutarSecuenciaAdicional1() {
    unsigned long int timePrendeApaga = 500; // Tiempo de retardo inicial en milisegundos
    unsigned char todosEncendidos = 0xFF; // Todos los LEDs encendidos (binario: 11111111)
    unsigned char todosApagados = 0x00;   // Todos los LEDs apagados (binario: 00000000)
    
    // Prender todos los LEDs
    display_binary(todosEncendidos);
    Leds(todosEncendidos);
    retardo(&timePrendeApaga); // Espera un momento
    
    // Apagar todos los LEDs
    display_binary(todosApagados);
    Leds(todosApagados);
    retardo(&timePrendeApaga); // Espera un momento
}

// comentar este void para que funcione el assembly

void ejecutarSecuenciaAdicional2() {
    unsigned long int speed = 500;
    unsigned char pares = 0xAA; // 0b10101010: LEDs pares encendidos
    unsigned char impares = 0x55; // 0b01010101: LEDs impares encendidos
    
    printf("\t |SECUENCIA PARES E IMPARES|\n\n");
    printf("Presione E para volver al menú principal\n\n\n");
    printf("\tDelay: %ld ms\t\n", speed);
    printf("\n\n");
    
    // Encender LEDs pares
    display_binary(pares);
    Leds(pares);
    retardo(&speed); // Espera un momento
    
    // Apagar LEDs
    apagarLuces();
    retardo(&speed); // Espera un momento
    
    // Encender LEDs impares
    display_binary(impares);
    Leds(impares);
    retardo(&speed); // Espera un momento
    
    // Apagar LEDs al final
    apagarLuces();
}