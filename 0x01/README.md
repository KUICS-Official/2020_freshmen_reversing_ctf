# 0x01
## 문제 파악

주어진 바이너리의 아키텍처를 확인한다.

``` bash
pngwna@ArchPngWnA ..ithub/2020_freshmen_reversing_ctf/0x01 (git)-[Writeup/0x0x] % file 0x01

0x01: ELF 32-bit LSB pie executable, Intel 80386, version 1 (SYSV), dynamically linked, interpreter /lib/ld-linux.so.2, BuildID[sha1]=45271865ff91925820e64a4f064fef538b411c67, for GNU/Linux 3.2.0, not stripped
```

32bit ELF임을 알 수 있다. 

실행시켜보면 16바이트의 입력을 받아 내부적으로 어떤 로직을 거친 후, 16바이트의 시리얼이 valid한지를 확인하는 프로그램임을 알 수 있다. 

시리얼을 비교하는 로직을 찾아 해당 로직을 통과할 수 있는 방법을 찾으면 문제를 해결할 수 있는 것으로 보인다.

## 바이너리 분석
바이너리를 분석하는 여러가지 방법이 있지만, 이번에는 가장 보편적인 방법중 하나로 gdb를 사용한다.

`gdb ./0x01`

``` asm
(gdb) disas main
Dump of assembler code for function main:
   0x0000120d <+0>:     lea    ecx,[esp+0x4]
   0x00001211 <+4>:     and    esp,0xfffffff0
   0x00001214 <+7>:     push   DWORD PTR [ecx-0x4]
   0x00001217 <+10>:    push   ebp
   0x00001218 <+11>:    mov    ebp,esp
   0x0000121a <+13>:    push   ebx
   0x0000121b <+14>:    push   ecx
   0x0000121c <+15>:    sub    esp,0x90
   0x00001222 <+21>:    call   0x1110 <__x86.get_pc_thunk.bx>
   0x00001227 <+26>:    add    ebx,0x2dd9
   0x0000122d <+32>:    mov    eax,gs:0x14
   0x00001233 <+38>:    mov    DWORD PTR [ebp-0xc],eax
   0x00001236 <+41>:    xor    eax,eax
   0x00001238 <+43>:    sub    esp,0xc
   0x0000123b <+46>:    lea    eax,[ebx-0x1ff8]
   0x00001241 <+52>:    push   eax
   0x00001242 <+53>:    call   0x1040 <printf@plt>
   0x00001247 <+58>:    add    esp,0x10
   0x0000124a <+61>:    sub    esp,0x8
   0x0000124d <+64>:    lea    eax,[ebp-0x8c]
   0x00001253 <+70>:    push   eax
   0x00001254 <+71>:    lea    eax,[ebx-0x1fb5]
   0x0000125a <+77>:    push   eax
   0x0000125b <+78>:    call   0x10b0 <__isoc99_scanf@plt>
   0x00001260 <+83>:    add    esp,0x10
   0x00001263 <+86>:    sub    esp,0xc
   0x00001266 <+89>:    lea    eax,[ebp-0x8c]
   0x0000126c <+95>:    push   eax
   0x0000126d <+96>:    call   0x1090 <strlen@plt>
   0x00001272 <+101>:   add    esp,0x10
   0x00001275 <+104>:   cmp    eax,0x10
   0x00001278 <+107>:   je     0x1296 <main+137>
   0x0000127a <+109>:   sub    esp,0xc
   0x0000127d <+112>:   lea    eax,[ebx-0x1fb0]
   0x00001283 <+118>:   push   eax
   0x00001284 <+119>:   call   0x1060 <puts@plt>
   0x00001289 <+124>:   add    esp,0x10
   0x0000128c <+127>:   sub    esp,0xc
   0x0000128f <+130>:   push   0xffffffff
   0x00001291 <+132>:   call   0x1080 <exit@plt>
   0x00001296 <+137>:   sub    esp,0x4
   0x00001299 <+140>:   push   0xb
   0x0000129b <+142>:   lea    eax,[ebx-0x1f88]
   0x000012a1 <+148>:   push   eax
   0x000012a2 <+149>:   lea    eax,[ebp-0x8c]
   0x000012a8 <+155>:   push   eax
   0x000012a9 <+156>:   call   0x10c0 <strncmp@plt>
   0x000012ae <+161>:   add    esp,0x10
   0x000012b1 <+164>:   test   eax,eax
   0x000012b3 <+166>:   je     0x12d1 <main+196>
   0x000012b5 <+168>:   sub    esp,0xc
   0x000012b8 <+171>:   lea    eax,[ebx-0x1f7c]
   0x000012be <+177>:   push   eax
   0x000012bf <+178>:   call   0x1060 <puts@plt>
   0x000012c4 <+183>:   add    esp,0x10
   0x000012c7 <+186>:   sub    esp,0xc
   0x000012ca <+189>:   push   0xffffffff
   0x000012cc <+191>:   call   0x1080 <exit@plt>
   0x000012d1 <+196>:   sub    esp,0xc
   0x000012d4 <+199>:   lea    eax,[ebx-0x1f5c]
   0x000012da <+205>:   push   eax
   0x000012db <+206>:   call   0x1060 <puts@plt>
   0x000012e0 <+211>:   add    esp,0x10
   0x000012e3 <+214>:   sub    esp,0xc
   0x000012e6 <+217>:   lea    eax,[ebx-0x1f26]
   0x000012ec <+223>:   push   eax
   0x000012ed <+224>:   call   0x1070 <system@plt>
   0x000012f2 <+229>:   add    esp,0x10
   0x000012f5 <+232>:   mov    eax,0x0
   0x000012fa <+237>:   mov    edx,DWORD PTR [ebp-0xc]
   0x000012fd <+240>:   sub    edx,DWORD PTR gs:0x14
   0x00001304 <+247>:   je     0x130b <main+254>
   0x00001306 <+249>:   call   0x13a0 <__stack_chk_fail_local>
   0x0000130b <+254>:   lea    esp,[ebp-0x8]
   0x0000130e <+257>:   pop    ecx
   0x0000130f <+258>:   pop    ebx
   0x00001310 <+259>:   pop    ebp
   0x00001311 <+260>:   lea    esp,[ecx-0x4]
   0x00001314 <+263>:   ret
```

16바이트의 시리얼을 입력한 후에는 `0x0000126d <+96>:    call   0x1090 <strlen@plt>`에서 16바이트인지 확인하는 로직을 거쳐 `0x000012a9 <+156>:   call   0x10c0 <strncmp@plt>`에서 시리얼 비교를 진행하는 것을 알 수 있다. 

`strncmp`는 인자로 src, dst, 비교할 길이를 받는다. 인자를 확인하면 시리얼 체크를 어떤식으로 하는지 알 수 있기 때문에, 해당 함수를 실행하기 전에 스택을 확인하면 문제를 해결할 수 있을 것이다. 

strncmp 함수 호출 부근을 보면
```
   0x00001299 <+140>:   push   0xb
   0x0000129b <+142>:   lea    eax,[ebx-0x1f88]
   0x000012a1 <+148>:   push   eax
   0x000012a2 <+149>:   lea    eax,[ebp-0x8c]
   0x000012a8 <+155>:   push   eax
   0x000012a9 <+156>:   call   0x10c0 <strncmp@plt>
```
처럼 되어있는데, 함수의 인자는 역순으로 들어가기 때문에,

컴파일 하기 전의 코드 원형이 `strncmp(*???, *???, 0xb)`임을 알 수 있다.
즉, 메모리 어딘가에서 정답인 시리얼을 불러와서 11바이트만큼 비교를 한다. 

16바이트의 문자열을 입력한 후 해당 함수 부근에서 스택을 확인한다.

(실행중이라 주소가 다른 것을 참고)
``` asm
(gdb) b *0x565562a9
Breakpoint 2 at 0x565562a9

(gdb) n
Single stepping until exit from function main,
which has no line number information.
[KUICS] Please enter the serial number of Flag Print Service ^^ : AAAABBBBCCCCDDDD
```

```
0x565562a9 in main ()
(gdb) x/16xw $esp
0xffffce50:     0xffffce6c      0x56557078      0x0000000b      0x56556227
0xffffce60:     0x56555351      0xf7fdb7bd      0x565552ac      0x41414141
0xffffce70:     0x42424242      0x43434343      0x44444444      0x00000000
0xffffce80:     0x00000000      0x00000001      0xf7ffd980      0x00000002
(gdb) x/s 0x56557078
0x56557078:     "KUICS-2020-"
(gdb) x/s 0xffffce6c
0xffffce6c:     "AAAABBBBCCCCDDDD"
```

즉 해당 함수를 호출할 때의 소스코드 원형은 `strncmp('AAAABBBBCCCCDDDD', 'KUICS-2020-', 0xb)` 이었음을 알 수 있다.

## 문제 해결
바이너리 분석을 통하여 시리얼 검사를 통과하려면
* 16바이트여야 함
* 첫 11바이트는 'KUICS-2020-'
을 만족해야 함을 알 수 있다. 

해당 조건을 만족하는 문자열을 넣으면 검사를 통과하는 것을 알 수 있다.

```
pngwna@ArchPngWnA ..ithub/2020_freshmen_reversing_ctf/0x01 (git)-[Writeup/0x0x] % ./0x01    

[KUICS] Please enter the serial number of Flag Print Service ^^ : KUICS-2020-12345
[KUICS] Valid serial! Here is the flag you ordered ^^
FLAG{Basics_of_reverse_engineering}
```

FLAG : `FLAG{Basics_of_reverse_engineering}`