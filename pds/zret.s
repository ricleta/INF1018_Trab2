cmpl $0, %ebx
jne L1
movl %ebx, %eax
leave
ret
L1:

movl %ebx, %eax
movl %eax, %ebx
leave 
ret
