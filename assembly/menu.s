

.extern display_binary
    .extern Leds
    .extern retardo

    .section .text
    .global ejecutarSecuenciaAdicional1
    .global ejecutarSecuenciaAdicional2

ejecutarSecuenciaAdicional1:
    ldr r0, =timePrendeApaga
    mov r1, #500
    str r1, [r0]

    mov r0, #0xFF
    bl display_binary
    mov r0, #0xFF
    bl Leds
    ldr r0, =timePrendeApaga
    bl retardo

    mov r0, #0x00
    bl display_binary
    mov r0, #0x00
    bl Leds
    ldr r0, =time



 .global ejecutarSecuenciaAdicional2

ejecutarSecuenciaAdicional2:
    ldr r0, =speed
    mov r1, #500
    str r1, [r0]

    ldr r3, =pares
    mov r2, #1
    ldr r4, =impares

secuencia_pares:
    ldr r0, [r3]
    bl display_binary
    ldr r0, [r3]
    bl Leds
    ldr r0, =speed
    bl retardo
    b apagar_y_esperar

apagar_y_esperar:
    bl apagarLuces
    ldr r0, =speed
    bl retardo

secuencia_impares:
    ldr r0, [r4]
    bl display_binary
    ldr r0, [r4]
    bl Leds
    ldr r0, =speed
    bl retardo
    b apagarLuces

pares:
    .byte 0xAA

impares:
    .byte 0x55