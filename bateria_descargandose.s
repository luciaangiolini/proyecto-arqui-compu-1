			MOV		r0, #2 
			MOV		SP, #pilaptr
			BL		BateriaBaja
			end
			
BateriaBaja
			STMFD	SP!, {r4, r5, r6, r7, LR}
			MOV		r6, r0 
			MOV		r4, #0xFF 
			MOV		r5, #8 
ForBateriaBaja
			MOV		r0, r4 
			BL		Display
			MOV		r0, r6 
			BL		Retardo
			;		MOV r0, "cls" por si la funcion system usara parámetros
			BL		SystemCLS
			MOV		r4, r4, LSL #1 
			SUBS		r5, r5, #1
			BNE		ForBateriaBaja
			BEQ		Termino
			
			
Display
			;STMFD	SP!, {r4, r5, r6, r7}
			;MOV		r7, #0x80 
			;MOV		r4, r0 	
forDisplay
			;TST		r4, r7	
			;MOVEQ	r0, #0x5F 
			;MOVNE	r0, #0x2A 
			;MOVS	r7, r7, LSR #1 
			;BNE		forDisplay
			;LDMFD	SP!, {r4, r5, r6, r7} 
			MOV		PC, LR
			
Retardo
			;SUBS	r0,r0, #1	
			;BNE		Retardo
			MOV		PC,LR
			
SystemCLS
			;		Simulo la limpieza de pantalla
			MOV		PC,LR
			
Termino
			LDMFD	SP!, {r4, r5, r6, r7, LR}
			MOV		PC, LR
			
			
pila			FILL		40
pilaptr		DCB		1
			
