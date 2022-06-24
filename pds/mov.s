movl -4(%rbp), %ebx
movl -8(%rbp), %ebx
movl -12(%rbp), %ebx
movl -16(%rbp), %ebx
movl -20(%rbp), %ebx

movl %ebx, -4(%rbp)
movl %ebx, -8(%rbp)
movl %ebx, -12(%rbp)
movl %ebx, -16(%rbp)
movl %ebx, -20(%rbp)