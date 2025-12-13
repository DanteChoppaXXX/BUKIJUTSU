
assemblyRoutine.exe:     file format elf32-i386


Disassembly of section .group:

00000000 <.group>:
   0:	01 00                	add    %eax,(%eax)
   2:	00 00                	add    %al,(%eax)
   4:	06                   	push   %es
   5:	00 00                	add    %al,(%eax)
	...

Disassembly of section .text:

00000000 <myStrlen>:
   0:	55                   	push   %ebp
   1:	89 e5                	mov    %esp,%ebp
   3:	83 ec 10             	sub    $0x10,%esp
   6:	e8 fc ff ff ff       	call   7 <myStrlen+0x7>
   b:	05 01 00 00 00       	add    $0x1,%eax
  10:	c7 45 fc 00 00 00 00 	movl   $0x0,-0x4(%ebp)
  17:	8b 45 08             	mov    0x8(%ebp),%eax
  1a:	89 45 f8             	mov    %eax,-0x8(%ebp)
  1d:	eb 08                	jmp    27 <myStrlen+0x27>
  1f:	83 45 f8 01          	addl   $0x1,-0x8(%ebp)
  23:	83 45 fc 01          	addl   $0x1,-0x4(%ebp)
  27:	8b 45 f8             	mov    -0x8(%ebp),%eax
  2a:	0f b6 00             	movzbl (%eax),%eax
  2d:	84 c0                	test   %al,%al
  2f:	75 ee                	jne    1f <myStrlen+0x1f>
  31:	8b 45 fc             	mov    -0x4(%ebp),%eax
  34:	c9                   	leave
  35:	c3                   	ret

Disassembly of section .text.__x86.get_pc_thunk.ax:

00000000 <__x86.get_pc_thunk.ax>:
   0:	8b 04 24             	mov    (%esp),%eax
   3:	c3                   	ret

Disassembly of section .debug_info:

00000000 <.debug_info>:
   0:	87 00                	xchg   %eax,(%eax)
   2:	00 00                	add    %al,(%eax)
   4:	05 00 01 04 00       	add    $0x40100,%eax
   9:	00 00                	add    %al,(%eax)
   b:	00 02                	add    %al,(%edx)
   d:	06                   	push   %es
   e:	00 00                	add    %al,(%eax)
  10:	00 1d 03 47 16 03    	add    %bl,0x3164703
  16:	00 00                	add    %al,(%eax)
  18:	00 00                	add    %al,(%eax)
  1a:	00 12                	add    %dl,(%edx)
  1c:	00 00                	add    %al,(%eax)
  1e:	00 00                	add    %al,(%eax)
  20:	00 00                	add    %al,(%eax)
  22:	00 36                	add    %dh,(%esi)
  24:	00 00                	add    %al,(%eax)
  26:	00 00                	add    %al,(%eax)
  28:	00 00                	add    %al,(%eax)
  2a:	00 03                	add    %al,(%ebx)
  2c:	5f                   	pop    %edi
  2d:	00 00                	add    %al,(%eax)
  2f:	00 01                	add    %al,(%ecx)
  31:	02 05 71 00 00 00    	add    0x71,%al
  37:	00 00                	add    %al,(%eax)
  39:	00 00                	add    %al,(%eax)
  3b:	36 00 00             	add    %al,%ss:(%eax)
  3e:	00 01                	add    %al,(%ecx)
  40:	9c                   	pushf
  41:	71 00                	jno    43 <.debug_info+0x43>
  43:	00 00                	add    %al,(%eax)
  45:	04 73                	add    $0x73,%al
  47:	74 72                	je     bb <myStrlen+0xbb>
  49:	00 01                	add    %al,(%ecx)
  4b:	02 1a                	add    (%edx),%bl
  4d:	78 00                	js     4f <.debug_info+0x4f>
  4f:	00 00                	add    %al,(%eax)
  51:	02 91 00 01 00 00    	add    0x100(%ecx),%dl
  57:	00 00                	add    %al,(%eax)
  59:	04 09                	add    $0x9,%al
  5b:	71 00                	jno    5d <.debug_info+0x5d>
  5d:	00 00                	add    %al,(%eax)
  5f:	02 91 74 01 58 00    	add    0x580174(%ecx),%dl
  65:	00 00                	add    %al,(%eax)
  67:	07                   	pop    %es
  68:	11 78 00             	adc    %edi,0x0(%eax)
  6b:	00 00                	add    %al,(%eax)
  6d:	02 91 70 00 05 04    	add    0x4050070(%ecx),%dl
  73:	05 69 6e 74 00       	add    $0x746e69,%eax
  78:	06                   	push   %es
  79:	04 85                	add    $0x85,%al
  7b:	00 00                	add    %al,(%eax)
  7d:	00 07                	add    %al,(%edi)
  7f:	01 06                	add    %eax,(%esi)
  81:	68 00 00 00 08       	push   $0x8000000
  86:	7e 00                	jle    88 <.debug_info+0x88>
  88:	00 00                	add    %al,(%eax)
	...

Disassembly of section .debug_abbrev:

00000000 <.debug_abbrev>:
   0:	01 34 00             	add    %esi,(%eax,%eax,1)
   3:	03 0e                	add    (%esi),%ecx
   5:	3a 21                	cmp    (%ecx),%ah
   7:	01 3b                	add    %edi,(%ebx)
   9:	0b 39                	or     (%ecx),%edi
   b:	0b 49 13             	or     0x13(%ecx),%ecx
   e:	02 18                	add    (%eax),%bl
  10:	00 00                	add    %al,(%eax)
  12:	02 11                	add    (%ecx),%dl
  14:	01 25 0e 13 0b 90    	add    %esp,0x900b130e
  1a:	01 0b                	add    %ecx,(%ebx)
  1c:	91                   	xchg   %eax,%ecx
  1d:	01 06                	add    %eax,(%esi)
  1f:	03 1f                	add    (%edi),%ebx
  21:	1b 1f                	sbb    (%edi),%ebx
  23:	11 01                	adc    %eax,(%ecx)
  25:	12 06                	adc    (%esi),%al
  27:	10 17                	adc    %dl,(%edi)
  29:	00 00                	add    %al,(%eax)
  2b:	03 2e                	add    (%esi),%ebp
  2d:	01 3f                	add    %edi,(%edi)
  2f:	19 03                	sbb    %eax,(%ebx)
  31:	0e                   	push   %cs
  32:	3a 0b                	cmp    (%ebx),%cl
  34:	3b 0b                	cmp    (%ebx),%ecx
  36:	39 0b                	cmp    %ecx,(%ebx)
  38:	27                   	daa
  39:	19 49 13             	sbb    %ecx,0x13(%ecx)
  3c:	11 01                	adc    %eax,(%ecx)
  3e:	12 06                	adc    (%esi),%al
  40:	40                   	inc    %eax
  41:	18 7a 19             	sbb    %bh,0x19(%edx)
  44:	01 13                	add    %edx,(%ebx)
  46:	00 00                	add    %al,(%eax)
  48:	04 05                	add    $0x5,%al
  4a:	00 03                	add    %al,(%ebx)
  4c:	08 3a                	or     %bh,(%edx)
  4e:	0b 3b                	or     (%ebx),%edi
  50:	0b 39                	or     (%ecx),%edi
  52:	0b 49 13             	or     0x13(%ecx),%ecx
  55:	02 18                	add    (%eax),%bl
  57:	00 00                	add    %al,(%eax)
  59:	05 24 00 0b 0b       	add    $0xb0b0024,%eax
  5e:	3e 0b 03             	or     %ds:(%ebx),%eax
  61:	08 00                	or     %al,(%eax)
  63:	00 06                	add    %al,(%esi)
  65:	0f 00 0b             	str    (%ebx)
  68:	0b 49 13             	or     0x13(%ecx),%ecx
  6b:	00 00                	add    %al,(%eax)
  6d:	07                   	pop    %es
  6e:	24 00                	and    $0x0,%al
  70:	0b 0b                	or     (%ebx),%ecx
  72:	3e 0b 03             	or     %ds:(%ebx),%eax
  75:	0e                   	push   %cs
  76:	00 00                	add    %al,(%eax)
  78:	08 26                	or     %ah,(%esi)
  7a:	00 49 13             	add    %cl,0x13(%ecx)
  7d:	00 00                	add    %al,(%eax)
	...

Disassembly of section .debug_aranges:

00000000 <.debug_aranges>:
   0:	1c 00                	sbb    $0x0,%al
   2:	00 00                	add    %al,(%eax)
   4:	02 00                	add    (%eax),%al
   6:	00 00                	add    %al,(%eax)
   8:	00 00                	add    %al,(%eax)
   a:	04 00                	add    $0x0,%al
	...
  14:	36 00 00             	add    %al,%ss:(%eax)
	...

Disassembly of section .debug_line:

00000000 <.debug_line>:
   0:	5c                   	pop    %esp
   1:	00 00                	add    %al,(%eax)
   3:	00 05 00 04 00 2a    	add    %al,0x2a000400
   9:	00 00                	add    %al,(%eax)
   b:	00 01                	add    %al,(%ecx)
   d:	01 01                	add    %eax,(%ecx)
   f:	fb                   	sti
  10:	0e                   	push   %cs
  11:	0d 00 01 01 01       	or     $0x1010100,%eax
  16:	01 00                	add    %eax,(%eax)
  18:	00 00                	add    %al,(%eax)
  1a:	01 00                	add    %eax,(%eax)
  1c:	00 01                	add    %al,(%ecx)
  1e:	01 01                	add    %eax,(%ecx)
  20:	1f                   	pop    %ds
  21:	01 4b 00             	add    %ecx,0x0(%ebx)
  24:	00 00                	add    %al,(%eax)
  26:	02 01                	add    (%ecx),%al
  28:	1f                   	pop    %ds
  29:	02 0f                	add    (%edi),%cl
  2b:	02 84 00 00 00 00 96 	add    -0x6a000000(%eax,%eax,1),%al
  32:	00 00                	add    %al,(%eax)
  34:	00 00                	add    %al,(%eax)
  36:	05 01 00 05 02       	add    $0x2050001,%eax
  3b:	00 00                	add    %al,(%eax)
  3d:	00 00                	add    %al,(%eax)
  3f:	14 05                	adc    $0x5,%al
  41:	09 f3                	or     %esi,%ebx
  43:	05 11 77 05 0b       	add    $0xb057711,%eax
  48:	68 05 0f 30 05       	push   $0x5300f05
  4d:	0e                   	push   %cs
  4e:	4b                   	dec    %ebx
  4f:	05 0c 47 05 14       	add    $0x1405470c,%eax
  54:	66 05 0c 4f          	add    $0x4f0c,%ax
  58:	05 01 3d 02 02       	add    $0x2023d01,%eax
  5d:	00 01                	add    %al,(%ecx)
  5f:	01                   	.byte 0x1

Disassembly of section .debug_str:

00000000 <.debug_str>:
   0:	63 6f 75             	arpl   %ebp,0x75(%edi)
   3:	6e                   	outsb  %ds:(%esi),(%dx)
   4:	74 00                	je     6 <.debug_str+0x6>
   6:	47                   	inc    %edi
   7:	4e                   	dec    %esi
   8:	55                   	push   %ebp
   9:	20 43 32             	and    %al,0x32(%ebx)
   c:	33 20                	xor    (%eax),%esp
   e:	31 35 2e 32 2e 31    	xor    %esi,0x312e322e
  14:	20 32                	and    %dh,(%edx)
  16:	30 32                	xor    %dh,(%edx)
  18:	35 30 38 31 33       	xor    $0x33313830,%eax
  1d:	20 2d 6d 33 32 20    	and    %ch,0x2032336d
  23:	2d 6d 74 75 6e       	sub    $0x6e75746d,%eax
  28:	65 3d 67 65 6e 65    	gs cmp $0x656e6567,%eax
  2e:	72 69                	jb     99 <myStrlen+0x99>
  30:	63 20                	arpl   %esp,(%eax)
  32:	2d 6d 61 72 63       	sub    $0x6372616d,%eax
  37:	68 3d 78 38 36       	push   $0x3638783d
  3c:	2d 36 34 20 2d       	sub    $0x2d203436,%eax
  41:	67 20 2d             	and    %ch,(%di)
  44:	66 6e                	data16 outsb %ds:(%esi),(%dx)
  46:	6f                   	outsl  %ds:(%esi),(%dx)
  47:	2d 73 74 61 63       	sub    $0x63617473,%eax
  4c:	6b 2d 70 72 6f 74 65 	imul   $0x65,0x746f7270,%ebp
  53:	63 74 6f 72          	arpl   %esi,0x72(%edi,%ebp,2)
  57:	00 73 74             	add    %dh,0x74(%ebx)
  5a:	72 69                	jb     c5 <myStrlen+0xc5>
  5c:	6e                   	outsb  %ds:(%esi),(%dx)
  5d:	67 00 6d 79          	add    %ch,0x79(%di)
  61:	53                   	push   %ebx
  62:	74 72                	je     d6 <myStrlen+0xd6>
  64:	6c                   	insb   (%dx),%es:(%edi)
  65:	65 6e                	outsb  %gs:(%esi),(%dx)
  67:	00 63 68             	add    %ah,0x68(%ebx)
  6a:	61                   	popa
  6b:	72 00                	jb     6d <myStrlen+0x6d>

Disassembly of section .debug_line_str:

00000000 <.debug_line_str>:
   0:	61                   	popa
   1:	73 73                	jae    76 <.debug_line_str+0x76>
   3:	65 6d                	gs insl (%dx),%es:(%edi)
   5:	62 6c 79 52          	bound  %ebp,0x52(%ecx,%edi,2)
   9:	6f                   	outsl  %ds:(%esi),(%dx)
   a:	75 74                	jne    80 <.debug_line_str+0x80>
   c:	69 6e 65 2e 63 00 2f 	imul   $0x2f00632e,0x65(%esi),%ebp
  13:	68 6f 6d 65 2f       	push   $0x2f656d6f
  18:	6b 69 72 69          	imul   $0x69,0x72(%ecx),%ebp
  1c:	6b 6f 2f 47          	imul   $0x47,0x2f(%edi),%ebp
  20:	69 74 68 75 62 2f 42 	imul   $0x55422f62,0x75(%eax,%ebp,2),%esi
  27:	55 
  28:	4b                   	dec    %ebx
  29:	49                   	dec    %ecx
  2a:	4a                   	dec    %edx
  2b:	55                   	push   %ebp
  2c:	54                   	push   %esp
  2d:	53                   	push   %ebx
  2e:	55                   	push   %ebp
  2f:	2f                   	das
  30:	52                   	push   %edx
  31:	65 76 69             	gs jbe 9d <.debug_line_str+0x9d>
  34:	73 69                	jae    9f <.debug_line_str+0x9f>
  36:	6f                   	outsl  %ds:(%esi),(%dx)
  37:	6e                   	outsb  %ds:(%esi),(%dx)
  38:	2f                   	das
  39:	50                   	push   %eax
  3a:	72 6f                	jb     ab <myStrlen+0xab>
  3c:	67 72 61             	addr16 jb a0 <.debug_line_str+0xa0>
  3f:	6d                   	insl   (%dx),%es:(%edi)
  40:	6d                   	insl   (%dx),%es:(%edi)
  41:	69 6e 67 44 72 69 6c 	imul   $0x6c697244,0x67(%esi),%ebp
  48:	6c                   	insb   (%dx),%es:(%edi)
  49:	73 00                	jae    4b <.debug_line_str+0x4b>
  4b:	2f                   	das
  4c:	68 6f 6d 65 2f       	push   $0x2f656d6f
  51:	6b 69 72 69          	imul   $0x69,0x72(%ecx),%ebp
  55:	6b 6f 2f 47          	imul   $0x47,0x2f(%edi),%ebp
  59:	69 74 68 75 62 2f 42 	imul   $0x55422f62,0x75(%eax,%ebp,2),%esi
  60:	55 
  61:	4b                   	dec    %ebx
  62:	49                   	dec    %ecx
  63:	4a                   	dec    %edx
  64:	55                   	push   %ebp
  65:	54                   	push   %esp
  66:	53                   	push   %ebx
  67:	55                   	push   %ebp
  68:	2f                   	das
  69:	52                   	push   %edx
  6a:	65 76 69             	gs jbe d6 <myStrlen+0xd6>
  6d:	73 69                	jae    d8 <myStrlen+0xd8>
  6f:	6f                   	outsl  %ds:(%esi),(%dx)
  70:	6e                   	outsb  %ds:(%esi),(%dx)
  71:	2f                   	das
  72:	50                   	push   %eax
  73:	72 6f                	jb     e4 <myStrlen+0xe4>
  75:	67 72 61             	addr16 jb d9 <myStrlen+0xd9>
  78:	6d                   	insl   (%dx),%es:(%edi)
  79:	6d                   	insl   (%dx),%es:(%edi)
  7a:	69 6e 67 44 72 69 6c 	imul   $0x6c697244,0x67(%esi),%ebp
  81:	6c                   	insb   (%dx),%es:(%edi)
  82:	73 00                	jae    84 <.debug_line_str+0x84>
  84:	61                   	popa
  85:	73 73                	jae    fa <myStrlen+0xfa>
  87:	65 6d                	gs insl (%dx),%es:(%edi)
  89:	62 6c 79 52          	bound  %ebp,0x52(%ecx,%edi,2)
  8d:	6f                   	outsl  %ds:(%esi),(%dx)
  8e:	75 74                	jne    104 <myStrlen+0x104>
  90:	69 6e 65 2e 63 00 61 	imul   $0x6100632e,0x65(%esi),%ebp
  97:	73 73                	jae    10c <myStrlen+0x10c>
  99:	65 6d                	gs insl (%dx),%es:(%edi)
  9b:	62 6c 79 52          	bound  %ebp,0x52(%ecx,%edi,2)
  9f:	6f                   	outsl  %ds:(%esi),(%dx)
  a0:	75 74                	jne    116 <myStrlen+0x116>
  a2:	69                   	.byte 0x69
  a3:	6e                   	outsb  %ds:(%esi),(%dx)
  a4:	65 2e 63 00          	gs arpl %eax,%cs:(%eax)

Disassembly of section .comment:

00000000 <.comment>:
   0:	00 47 43             	add    %al,0x43(%edi)
   3:	43                   	inc    %ebx
   4:	3a 20                	cmp    (%eax),%ah
   6:	28 47 4e             	sub    %al,0x4e(%edi)
   9:	55                   	push   %ebp
   a:	29 20                	sub    %esp,(%eax)
   c:	31 35 2e 32 2e 31    	xor    %esi,0x312e322e
  12:	20 32                	and    %dh,(%edx)
  14:	30 32                	xor    %dh,(%edx)
  16:	35 30 38 31 33       	xor    $0x33313830,%eax
	...

Disassembly of section .note.gnu.property:

00000000 <.note.gnu.property>:
   0:	04 00                	add    $0x0,%al
   2:	00 00                	add    %al,(%eax)
   4:	18 00                	sbb    %al,(%eax)
   6:	00 00                	add    %al,(%eax)
   8:	05 00 00 00 47       	add    $0x47000000,%eax
   d:	4e                   	dec    %esi
   e:	55                   	push   %ebp
   f:	00 02                	add    %al,(%edx)
  11:	00 01                	add    %al,(%ecx)
  13:	c0 04 00 00          	rolb   $0x0,(%eax,%eax,1)
  17:	00 00                	add    %al,(%eax)
  19:	00 00                	add    %al,(%eax)
  1b:	00 01                	add    %al,(%ecx)
  1d:	00 01                	add    %al,(%ecx)
  1f:	c0 04 00 00          	rolb   $0x0,(%eax,%eax,1)
  23:	00 01                	add    %al,(%ecx)
  25:	00 00                	add    %al,(%eax)
	...

Disassembly of section .eh_frame:

00000000 <.eh_frame>:
   0:	14 00                	adc    $0x0,%al
   2:	00 00                	add    %al,(%eax)
   4:	00 00                	add    %al,(%eax)
   6:	00 00                	add    %al,(%eax)
   8:	01 7a 52             	add    %edi,0x52(%edx)
   b:	00 01                	add    %al,(%ecx)
   d:	7c 08                	jl     17 <.eh_frame+0x17>
   f:	01 1b                	add    %ebx,(%ebx)
  11:	0c 04                	or     $0x4,%al
  13:	04 88                	add    $0x88,%al
  15:	01 00                	add    %eax,(%eax)
  17:	00 1c 00             	add    %bl,(%eax,%eax,1)
  1a:	00 00                	add    %al,(%eax)
  1c:	1c 00                	sbb    $0x0,%al
  1e:	00 00                	add    %al,(%eax)
  20:	00 00                	add    %al,(%eax)
  22:	00 00                	add    %al,(%eax)
  24:	36 00 00             	add    %al,%ss:(%eax)
  27:	00 00                	add    %al,(%eax)
  29:	41                   	inc    %ecx
  2a:	0e                   	push   %cs
  2b:	08 85 02 42 0d 05    	or     %al,0x50d4202(%ebp)
  31:	72 c5                	jb     fffffff8 <myStrlen+0xfffffff8>
  33:	0c 04                	or     $0x4,%al
  35:	04 00                	add    $0x0,%al
  37:	00 10                	add    %dl,(%eax)
  39:	00 00                	add    %al,(%eax)
  3b:	00 3c 00             	add    %bh,(%eax,%eax,1)
  3e:	00 00                	add    %al,(%eax)
  40:	00 00                	add    %al,(%eax)
  42:	00 00                	add    %al,(%eax)
  44:	04 00                	add    $0x0,%al
  46:	00 00                	add    %al,(%eax)
  48:	00 00                	add    %al,(%eax)
	...
