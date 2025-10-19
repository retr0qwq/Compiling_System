
test1.o:     file format elf64-x86-64


Disassembly of section .text:

0000000000000000 <add>:
   0:	55                   	push   %rbp
   1:	48 89 e5             	mov    %rsp,%rbp
   4:	89 7d f8             	mov    %edi,-0x8(%rbp)
   7:	89 75 fc             	mov    %esi,-0x4(%rbp)
   a:	8b 45 f8             	mov    -0x8(%rbp),%eax
   d:	03 45 fc             	add    -0x4(%rbp),%eax
  10:	5d                   	pop    %rbp
  11:	c3                   	ret    
  12:	66 66 2e 0f 1f 84 00 	data16 cs nopw 0x0(%rax,%rax,1)
  19:	00 00 00 00 
  1d:	0f 1f 00             	nopl   (%rax)

0000000000000020 <main>:
  20:	55                   	push   %rbp
  21:	48 89 e5             	mov    %rsp,%rbp
  24:	48 83 ec 10          	sub    $0x10,%rsp
  28:	c7 45 f0 00 00 00 00 	movl   $0x0,-0x10(%rbp)
  2f:	48 bf 00 00 00 00 00 	movabs $0x0,%rdi
  36:	00 00 00 
  39:	b0 00                	mov    $0x0,%al
  3b:	e8 00 00 00 00       	call   40 <main+0x20>
  40:	c7 45 f8 03 00 00 00 	movl   $0x3,-0x8(%rbp)
  47:	8b 75 f8             	mov    -0x8(%rbp),%esi
  4a:	8b 55 f8             	mov    -0x8(%rbp),%edx
  4d:	0f af 55 f8          	imul   -0x8(%rbp),%edx
  51:	48 bf 00 00 00 00 00 	movabs $0x0,%rdi
  58:	00 00 00 
  5b:	b0 00                	mov    $0x0,%al
  5d:	e8 00 00 00 00       	call   62 <main+0x42>
  62:	bf 05 00 00 00       	mov    $0x5,%edi
  67:	be 07 00 00 00       	mov    $0x7,%esi
  6c:	e8 00 00 00 00       	call   71 <main+0x51>
  71:	89 45 f4             	mov    %eax,-0xc(%rbp)
  74:	8b 75 f4             	mov    -0xc(%rbp),%esi
  77:	48 bf 00 00 00 00 00 	movabs $0x0,%rdi
  7e:	00 00 00 
  81:	b0 00                	mov    $0x0,%al
  83:	e8 00 00 00 00       	call   88 <main+0x68>
  88:	c7 45 fc 00 00 00 00 	movl   $0x0,-0x4(%rbp)
  8f:	83 7d fc 05          	cmpl   $0x5,-0x4(%rbp)
  93:	7d 1c                	jge    b1 <main+0x91>
  95:	8b 45 fc             	mov    -0x4(%rbp),%eax
  98:	03 04 25 00 00 00 00 	add    0x0,%eax
  9f:	89 04 25 00 00 00 00 	mov    %eax,0x0
  a6:	8b 45 fc             	mov    -0x4(%rbp),%eax
  a9:	83 c0 01             	add    $0x1,%eax
  ac:	89 45 fc             	mov    %eax,-0x4(%rbp)
  af:	eb de                	jmp    8f <main+0x6f>
  b1:	8b 34 25 00 00 00 00 	mov    0x0,%esi
  b8:	48 bf 00 00 00 00 00 	movabs $0x0,%rdi
  bf:	00 00 00 
  c2:	b0 00                	mov    $0x0,%al
  c4:	e8 00 00 00 00       	call   c9 <main+0xa9>
  c9:	31 c0                	xor    %eax,%eax
  cb:	48 83 c4 10          	add    $0x10,%rsp
  cf:	5d                   	pop    %rbp
  d0:	c3                   	ret    
