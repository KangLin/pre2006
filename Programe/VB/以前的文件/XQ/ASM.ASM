
code segment
     assume cs: code
start:
      push bp
      mov bp,sp
      push ax
      push bx
      push dx
      mov bx,[bp+4]
      mov ax,'k'
      mov [bx],ax
      mov bx,[bp+6]
      mov ax,'l'
      mov [bx],ax
      pop dx
      pop bx
      pop ax
      pop bp
      ret 4
      code ends
      end start
