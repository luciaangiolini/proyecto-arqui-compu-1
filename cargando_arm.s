.text

.global VELOCIDAD_CARGANDO
.global disp_binary
.global system
.global getchi
.global leds
.global printf



.global cargando_arm
cargando_arm:
    PUSH {R4, R5, R6, R7, R8, R9, R10, LR}
    MOV R10, R0
    MOV R4, #128
    MOV R5, #128
    LDR R0, =clear 
    BL system
    
    loop:
        CMP R5, #255
        BGE end_loop

        BL getchi
        MOV R6, R0

        CMP R6, #85
        BEQ aumentar_velocidad
        CMP R6, #68
        BEQ disminuir_velocidad
        CMP R6, #79
        BEQ finalizar
        B continuar

        aumentar_velocidad:
            LDR R7, =VELOCIDAD_CARGANDO
            LDR R8, [R7]
            CMP R8, #60
            SUBGE R8, R8, #20
            STR R8, [R7]
            B continuar
        
        disminuir_velocidad:
            LDR R7, =VELOCIDAD_CARGANDO
            LDR R8, [R7]
            CMP R8, #600
            ADDLE R8, R8, #20
            STR R8, [R7]
            B continuar

        continuar:

        LDR R0, =mensaje
        BL printf
        MOV R0, R5
        BL disp_binary
        MOV R0, R5
        BL leds
        LDR R0, =VELOCIDAD_CARGANDO
        LDR R9, [R0]
        MOV R0, R9
        BL delay
        LDR R0, =clear
        BL system

        LSR R4, R4, #1
        ADD R5, R5, R4
        CMP R4, #0
        ADDEQ R4, R4, #1

        B loop

    end_loop:
        MOV R4, #128
        MOV R5, #128
        CMP R10, R0
        BNE finalizar
        B loop

    finalizar:
        MOV R0, #0
        BL leds
        POP {R4, R5, R6, R7, R8, R9, PC}

.section .data 
    mensaje: .asciz "Ejecutando la secuencia ¡Cargando...!. Presione enter para salir\n"
    clear: .asciz "clear"

