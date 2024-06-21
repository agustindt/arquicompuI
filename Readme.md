Instrucciones para Compilar y Ejecutar el Código
Este repositorio contiene un programa escrito en C que utiliza funciones definidas en ensamblador para controlar LEDs a través de la librería EasyPIO. Sigue los pasos a continuación para compilar y ejecutar el programa en un entorno Linux.

Requisitos Previos
Asegúrate de tener instalados los siguientes requisitos previos:

GCC (GNU Compiler Collection): Para compilar código C.
NASM (Netwide Assembler): Para ensamblar el código en ensamblador.
EasyPIO: Biblioteca para controlar pines GPIO en Raspberry Pi (incluida en este repositorio como EasyPIO.h).
Puedes instalar GCC y NASM en Ubuntu u otras distribuciones Linux con:

bash
Copiar código
sudo apt update
sudo apt install build-essential  # Instala GCC y otras herramientas de compilación
sudo apt install nasm              # Instala NASM (ensamblador)
Pasos para Compilar y Ejecutar
Clonar el Repositorio

Clona este repositorio en tu máquina local:

bash
Copiar código
git clone <url-del-repositorio>
cd <nombre-del-repositorio>
Compilar el Código

Compila primero el código en ensamblador (menu.s) a un archivo objeto:

bash
Copiar código
nasm -f elf64 menu.s -o menu.o   # Para arquitecturas de 64 bits (x86_64)
Compila luego el código en C (main.c) enlazando con el objeto generado:

bash
Copiar código
gcc main.c menu.o -o mi_programa -lncurses
-o mi_programa: Especifica el nombre del ejecutable.
-lncurses: Enlaza con la biblioteca ncurses para soporte de interfaz de usuario.
Ejecutar el Programa

Ejecuta el programa compilado:

bash
Copiar código
./mi_programa
Uso del Programa

El programa solicitará ingresar una contraseña de 5 dígitos para autenticarse.
Después de la autenticación, mostrará un menú con diferentes opciones de secuencias de luces.
Selecciona una opción para ejecutar la secuencia correspondiente.
Terminar la Ejecución

Para salir del programa, presiona la tecla correspondiente según las instrucciones que muestra el menú de cada secuencia.