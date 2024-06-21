; Archivo: menu.s

section .data
    timePrendeApaga equ 500            ; Tiempo de retardo inicial en milisegundos
    todosEncendidos equ 0xFF           ; Todos los LEDs encendidos (binario: 11111111)
    todosApagados equ 0x00             ; Todos los LEDs apagados (binario: 00000000)
    speed equ 500                      ; Tiempo de retardo inicial en milisegundos
    pares equ 0xAA                     ; 0b10101010: LEDs pares encendidos
    impares equ 0x55                   ; 0b01010101: LEDs impares encendidos

section .text
    global ejecutarSecuenciaAdicional1
    global ejecutarSecuenciaAdicional2
    extern display_binary, Leds, retardo, apagarLuces

ejecutarSecuenciaAdicional1:
    ; Prender todos los LEDs
    movzx eax, byte todosEncendidos
    push eax
    call display_binary
    add esp, 4
    
    movzx eax, byte todosEncendidos
    push eax
    call Leds
    add esp, 4
    
    push dword timePrendeApaga
    call retardo
    add esp, 4
    
    ; Apagar todos los LEDs
    movzx eax, byte todosApagados
    push eax
    call display_binary
    add esp, 4
    
    movzx eax, byte todosApagados
    push eax
    call Leds
    add esp, 4
    
    push dword timePrendeApaga
    call retardo
    add esp, 4
    
    ret

ejecutarSecuenciaAdicional2:
    ; Encender LEDs pares
    movzx eax, byte pares
    push eax
    call display_binary
    add esp, 4
    
    movzx eax, byte pares
    push eax
    call Leds
    add esp, 4
    
    push dword speed
    call retardo
    add esp, 4
    
    ; Apagar LEDs
    call apagarLuces
    
    push dword speed
    call retardo
    add esp, 4
    
    ; Encender LEDs impares
    movzx eax, byte impares
    push eax
    call display_binary
    add esp, 4
    
    movzx eax, byte impares
    push eax
    call Leds
    add esp, 4
    
    push dword speed
    call retardo
    add esp, 4
    
    ; Apagar LEDs al final
    call apagarLuces
    
    ret
