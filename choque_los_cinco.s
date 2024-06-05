			MOV		r0, #2
			MOV		SP, #pilaptr ---> stack pointer
			BL		ChoqueLos5 ---->link
			end
			
			
ChoqueLos5
			STMFD	SP!, {r4, r5, r6, r7, r8, r9, r10, LR} ----> push stack pointer
			MOV		r10, #tabla 
			MOV		r6, #0 -----> transfer
			MOV		r9, r0 
ForChoqueLos5
			LDRB		r4, [r10, r6] ----> load register
			MOV		r0, r4
			BL		Display
			MOV		r0, r9 
			BL		Retardo
			;		MOV r0, "cls" por si la funcion system usara par�metros
			BL		SystemCLS
			ADD		r6, r6, #1  --->suma
			CMP		r6, #8     ---->compara
			BNE		ForChoqueLos5 -----> if not equal
			BL		Termino
			
			
Display
			;MOV		r5, #0x80 ; 1000 0000 o 128
			;forDisplay
			;		TST		r4, r5	
			;		MOVEQ	r0, #0x5F

			;		MOVNE	r0, #0x2A
			;		MOVS		r5, r5, LSR #1 
			;		BNE		forDisplay
			MOV		PC, LR
			
			
Termino
			LDMFD	SP!, {r4, r5, r6, r7, r8, r9, r10, LR} --->pop
			MOV		PC, LR
			
Retardo
			;SUBS	r0,r0, #1	; Resto (a--;)
			;BNE		Retardo
			MOV		PC,LR
			
SystemCLS
		
			MOV		PC,LR
			
			
			
tabla		DCB		0x0, 0x81, 0xC3, 0xE7, 0xFF, 0xE7, 0xC3, 0x81 ; 0000 0000 , 1000 0001, 1100 0011, 1110 0111, 1111 1111 , repito
			---->bytes memoria
			
pila			FILL		40
pilaptr		DCB		1
			
