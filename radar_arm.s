.text

.global VELOCIDAD_RADAR
.global disp_binary
.global system
.global getchi
.global leds
.global printf

.global radar_arm
radar_arm:
    PUSH {R4,R5,R6,R7, R8, R9, R10, LR}
    MOV R10, R0
    MOV R5, #0
    LDR R4, =array
    LDR R0, =clear 
    BL system
    
      loop:
        CMP R5, #8
        BGE end_loop

        BL getchi
        MOV R6,R0

        CMP R6, #85
        BEQ aumentar_velocidad
        CMP R6, #68
        BEQ disminuir_velocidad
        CMP R6, #79
        BEQ finalizar
        B continuar

        aumentar_velocidad:
            LDR R7, =VELOCIDAD_RADAR
            LDR R8, [R7]
            CMP R8, #60
            SUBGE R8, R8, #20
            STR R8, [R7]
            B continuar
        
        disminuir_velocidad:
            LDR R7, =VELOCIDAD_RADAR
            LDR R8, [R7]
            CMP R8, #600
            ADDGE R8, R8, #20
            STR R8, [R7]
            B continuar

        continuar:

        LDR R0, =mensaje
        BL printf

        LDRB R8, [R4, R5]
        MOV R0, R8
        BL disp_binary
        MOV R0, R8
        BL leds
        LDR R0, =VELOCIDAD_RADAR
        LDR R9, [R0]
        MOV R0, R9
        BL delay
        LDR R0, =clear
        BL system

        ADD R5, R5, #1
        B loop

        end_loop:
        MOV R5, #0

        CMP R10, R0
        BNE finalizar

        B loop

        finalizar:
        MOV R0, #0
        BL leds
        POP {R4, R5, R6, R7, R8, R9, R10, PC}
    

.data
    mensaje:
        .asciz "Ejecutando la secuencia ¡Radar!. Presione enter para salir\n"
    clear:
        .asciz "clear"
    array:
    .byte 0b10000000
    .byte 0b01000000
    .byte 0b00100000
    .byte 0b00010000
    .byte 0b00011000
    .byte 0b00010100
    .byte 0b00010010
    .byte 0b00010001
.end

.section.note.GNU-stack
