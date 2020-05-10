;-----------------------------------------------------------------------------
;               在 Quick BASIC中检查是否运行了UCDOS的特殊显示程序
;编译过程:
;       TASM    TXBASIC
;       TLINK   /t/x            TXBASIC
;       REN     TESTTX.COM      TXBASIC.BIN
;使用方法:
;       将TXBASIC.BIN的内容定义为BASIC的数据,在BASIC中装入数据,并置返回值
;       的地址. 调用这个程序, 返回值为0时不支持, 为1时支持.
;       请参见BASIC的特显示例程序TXDEMO1.BAS
;-----------------------------------------------------------------------------
code            segment                    ;显示汉字程序
		org	100h
		assume	cs:code,ds:code,es:code,ss:code
start:
                push    ax
                push    bx
                push    cx
                push    dx
                push    si
                mov     si,0

                mov     ax,word ptr cs:[si]
                mov     bx,word ptr cs:[si+2]
                mov     cx,ax
                not     cx
                test    cx,bx
                je      Exit1                    ;没有运行特殊显示
                mov     word ptr cs:[si+4],0
                jmp     exit
exit1:          mov     word ptr cs:[si+4],1
                
                ;mov     word ptr cs:[si],1      ;运行了特殊显示
Exit:
                sal     bx,1
                mov     word ptr cs:[si+2],bx
                pop     si
                pop     dx
                pop     cx
                pop     bx
                pop     ax
                retf
code		ends
		end	start

