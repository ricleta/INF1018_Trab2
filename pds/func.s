/*
0000000000000000 <L1>:
   0:   b8 01 00 00 00          mov    $0x1,%eax
   5:   c3                      retq   

0000000000000006 <L2>:
   6:   bb 01 00 00 00          mov    $0x1,%ebx
   b:   eb f3                   jmp    0 <L1>

000000000000000d <L3>:
   d:   bb 02 00 00 00          mov    $0x2,%ebx
  12:   01 d8                   add    %ebx,%eax
  14:   c3 

L1:
  movl    $0x3,%eax

  movl    $-1,%ebx
  addl    $1,%eax

Convenções:
  v0: %ebx
  v1: %r12d
  v2: %r13d
  v3: %r14d
  v4: %r15d
*/
/********************************************************/
movl %ebx, %eax;
ret
movl %r12d, %eax;
ret
movl %r13d, %eax;
ret
movl %r14d, %eax;
ret
movl %r15d, %eax;
ret
movl %edi, %eax
ret
movl $0, %eax
ret
movl $1, %eax
ret
movl $-1, %eax
ret
movl $300, %eax
ret
movl $-300, %eax
ret
movl $70000, %eax
ret
movl $-70000, %eax
ret
movl $19000000, %eax
ret
movl $-19000000, %eax
ret