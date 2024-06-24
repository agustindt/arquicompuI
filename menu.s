.global ejecutarSecuenciaAdicional1
.global ejecutarSecuenciaAdicional2

.section .data
timePrendeApaga:  .word 500
speed:            .word 500
todosEncendidos:  .byte 0xFF
todosApagados:    .byte 0x00
pares:            .byte 0xAA
impares:          .byte 0x55

.section .text

ejecutarSecuenciaAdicional1:
    push {r4, lr}                // Guardar registros

    // Prender todos los LEDs
    ldr r0, =todosEncendidos
    ldrb r0, [r0]
    bl display_binary
    ldr r0, =todosEncendidos
    ldrb r0, [r0]
    bl Leds

    // Retardo
    ldr r0, =timePrendeApaga     // Obtener la dirección de timePrendeApaga
    bl retardo

    // Apagar todos los LEDs
    ldr r0, =todosApagados
    ldrb r0, [r0]
    bl display_binary
    ldr r0, =todosApagados
    ldrb r0, [r0]
    bl Leds

    // Retardo
    ldr r0, =timePrendeApaga     // Obtener la dirección de timePrendeApaga
    bl retardo

    pop {r4, lr}                 // Restaurar registros
    bx lr

ejecutarSecuenciaAdicional2:
    push {r4, lr}                // Guardar registros

    // Encender LEDs pares
    ldr r0, =pares
    ldrb r0, [r0]
    bl display_binary
    ldr r0, =pares
    ldrb r0, [r0]
    bl Leds

    // Retardo
    ldr r0, =speed               // Obtener la dirección de speed
    bl retardo

    // Apagar LEDs
    bl apagarLuces

    // Encender LEDs impares
    ldr r0, =impares
    ldrb r0, [r0]
    bl display_binary
    ldr r0, =impares
    ldrb r0, [r0]
    bl Leds

    // Retardo
    ldr r0, =speed               // Obtener la dirección de speed
    bl retardo

    // Apagar LEDs
    bl apagarLuces

    pop {r4, lr}                 // Restaurar registros
    bx lr
