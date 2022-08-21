.MODEL SMALL
.STACK 100H

.DATA

.CODE

PRINTLN PROC 
    POP BX  ; IP POPPED
    POP AX  ; NUMBER POPPED
    PUSH BX ; IP PUSHED
    CMP AX,0
    JGE POS
    NEG AX
    MOV BX,AX
    MOV AH,2
    MOV DX,'-'
    INT 21H
    MOV AX,BX
POS:
    XOR CX,CX
    MOV BX,10
    MOV DX,0
WHILE_LOOP:
    MOV DX,0
    DIV BX
    INC CX
    PUSH DX
    CMP AX,0
    JE END_WHILE
    JMP WHILE_LOOP
END_WHILE:
    MOV AH,2
TOP:
    POP DX
    ADD DX,'0'
    INT 21H
    LOOP TOP
    MOV DX,0AH
    INT 21H
    MOV DX,0DH
    INT 21H
    RET
PRINTLN ENDP


PRINTCHAR PROC
    POP BX  ; IP POPPED
    POP AX  ; NUMBER POPPED
    PUSH BX ; IP PUSHED
    MOV DX,AX
    MOV AH,2
    INT 21H
    RET
PRINTCHAR ENDP

foo PROC

PUSH AX
MOV BP,SP
MOV AX,[BP+4]
PUSH AX
MOV AX,0
PUSH AX
POP AX
POP BX
CMP AX,BX
JNE L2
PUSH 1
JMP L1
L2: 
PUSH 0
L1: 
POP AX
CMP AX,0
JE L3
MOV AX,1
PUSH AX
POP BX
POP AX
POP AX
PUSH BX
PUSH AX
RET
JMP L4
L3:

L4:

MOV BP,SP
MOV AX,[BP+4]
PUSH AX
POP AX
MOV BP,SP
MOV [BP+0],AX
PUSH AX
POP BX
MOV BP,SP
MOV AX,[BP+4]
PUSH AX
MOV AX,1
PUSH AX
POP AX
POP BX
SUB BX,AX
PUSH BX
CALL foo
POP BX
POP AX
PUSH BX
MOV BP,SP
MOV AX,[BP+2]
PUSH AX
POP AX
POP BX
ADD AX,BX
PUSH AX
POP BX
POP AX
POP AX
PUSH BX
PUSH AX
RET

foo ENDP

main PROC

MOV AX,@DATA
MOV DS,AX
PUSH AX
MOV AX,7
PUSH AX
CALL foo
POP BX
POP AX
PUSH BX
POP AX
MOV BP,SP
MOV [BP+0],AX
PUSH AX
POP BX
MOV BP,SP
MOV AX,[BP+0]
PUSH AX
CALL PRINTLN
MOV AX,0
PUSH AX
MOV AX,4CH
INT 21H

main ENDP

END main

