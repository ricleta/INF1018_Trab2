cmpl $0, %ebx
jne L1
movl %ebx, %eax
ret
L1:

cmpl $0, %r12d
jne L2
movl %edi, %eax
ret
L2:

cmpl $0, %r13d
jne L3
movl $0, %eax
ret
L3:

cmpl $0, %r14d
jne L4
movl $17000000, %eax
ret
L4:

cmpl $0, %r15d
jne L5
movl $-18000000, %eax
ret
L5:

cmpl $0, %edi
jne L6
movl %r12d, %eax
ret
L6:

cmpl $0, %edi
jne L7
movl %edi, %eax
ret
L7:

cmpl $0, %edi
jne L8
movl $1, %eax
ret
L8:

movl %r14d, %eax
ret

movl %edi, %eax
ret

movl $1, %eax
ret