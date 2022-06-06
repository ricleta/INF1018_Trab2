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
*/

/********************************************************/

movl $1, %eax
movl $100, %eax
movl $10000, %eax
movl $2345, %eax
movl $0xffffffff, %eax
