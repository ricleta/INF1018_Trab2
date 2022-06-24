a1:
  movl $1, %eax
  ret
a2:
  call a1
  ret

b1:
  movl $1, %eax
  movl $1, %ebx
  addl %ebx, %eax
  ret
b2:
  call b1
  ret

c1:
  movl $1, %eax
  ret
c2:
  movl $1, %ebx
  call c1
  ret

movl %ebx, %esi