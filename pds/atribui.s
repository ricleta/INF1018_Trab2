/*
 int n[15] = {0, 1, 2, 3, 4, 0, 1, 2, 3, 4, 0, 1, 2, 3, 4};
 int var[15] = {'v', 'v', 'v', 'v', 'v', 'p', 'p', 'p', 'p', 'p', '$', '$', '$', '$', '$'};
 int id[15] = {0, 2, 3, 4, 1, 0, 0, 0, 0, 0, 0, 1, -1, 300, -300};
*/
movl %ebx, -4(%rbp)
movl %r13d, -8(%rbp)
movl %r14d, -12(%rbp)
movl %r15d, -16(%rbp)
movl %r12d, -20(%rbp)


movl %edi, -4(%rbp)
movl %edi, -8(%rbp)
movl %edi, -12(%rbp)
movl %edi, -16(%rbp)
movl %edi, -20(%rbp)


movl $0, %ebx
movl %ebx, -4(%rbp)

movl $1, %r12d
movl %r12d, -8(%rbp)

movl $-1, %r13d
movl %r13d, -12(%rbp)

movl $300, %r14d
movl %r14d, -16(%rbp)

movl $-300, %r15d
movl %r15d, -20(%rbp)