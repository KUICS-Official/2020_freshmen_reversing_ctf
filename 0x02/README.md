# 0x02
## 문제 파악

주어진 바이너리의 아키텍처를 확인한다.

``` bash
pngwna@ArchPngWnA ..ithub/2020_freshmen_reversing_ctf/0x02 (git)-[Writeup/0x0x] % file ./0x02

./0x02: ELF 32-bit LSB pie executable, Intel 80386, version 1 (SYSV), dynamically linked, interpreter /lib/ld-linux.so.2, BuildID[sha1]=ef0e8c6d0980f23213b41dd314146d72f67c77ae, for GNU/Linux 3.2.0, not stripped
```

32bit ELF임을 알 수 있다. 

이전 문제와 비슷하게, 내부 로직을 통과하는 문자열을 찾는 문제임을 알 수 있다.

## 바이너리 분석

바이너리를 disassemble한 후 로직을 확인한다.

``` asm
Breakpoint 1, 0x565561fc in main ()
(gdb) disas
Dump of assembler code for function main:
   0x565561ed <+0>:     lea    ecx,[esp+0x4]
   0x565561f1 <+4>:     and    esp,0xfffffff0
   0x565561f4 <+7>:     push   DWORD PTR [ecx-0x4]
   0x565561f7 <+10>:    push   ebp
   0x565561f8 <+11>:    mov    ebp,esp
   0x565561fa <+13>:    push   ebx
   0x565561fb <+14>:    push   ecx
=> 0x565561fc <+15>:    sub    esp,0x90
   0x56556202 <+21>:    call   0x565560f0 <__x86.get_pc_thunk.bx>
   0x56556207 <+26>:    add    ebx,0x2df9
   0x5655620d <+32>:    mov    eax,gs:0x14
   0x56556213 <+38>:    mov    DWORD PTR [ebp-0xc],eax
   0x56556216 <+41>:    xor    eax,eax
   0x56556218 <+43>:    sub    esp,0xc
   0x5655621b <+46>:    lea    eax,[ebx-0x1fe0]
   0x56556221 <+52>:    push   eax
   0x56556222 <+53>:    call   0x56556040 <printf@plt>
   0x56556227 <+58>:    add    esp,0x10
   0x5655622a <+61>:    sub    esp,0x8
   0x5655622d <+64>:    lea    eax,[ebp-0x8c]
   0x56556233 <+70>:    push   eax
   0x56556234 <+71>:    lea    eax,[ebx-0x1faf]
   0x5655623a <+77>:    push   eax
   0x5655623b <+78>:    call   0x565560a0 <__isoc99_scanf@plt>
   0x56556240 <+83>:    add    esp,0x10
   0x56556243 <+86>:    mov    eax,DWORD PTR [ebx+0x30]
   0x56556249 <+92>:    sub    esp,0x8
   0x5655624c <+95>:    push   eax
   0x5655624d <+96>:    lea    eax,[ebp-0x8c]
   0x56556253 <+102>:   push   eax
   0x56556254 <+103>:   call   0x565562af <compare>
   0x56556259 <+108>:   add    esp,0x10
   0x5655625c <+111>:   cmp    eax,0xffffffff
   0x5655625f <+114>:   jne    0x5655627d <main+144>
   0x56556261 <+116>:   sub    esp,0xc
   0x56556264 <+119>:   lea    eax,[ebx-0x1fac]
   0x5655626a <+125>:   push   eax
   0x5655626b <+126>:   call   0x56556060 <puts@plt>
   0x56556270 <+131>:   add    esp,0x10
   0x56556273 <+134>:   sub    esp,0xc
   0x56556276 <+137>:   push   0xffffffff
   0x56556278 <+139>:   call   0x56556070 <exit@plt>
   0x5655627d <+144>:   sub    esp,0xc
   0x56556280 <+147>:   lea    eax,[ebx-0x1f8c]
   0x56556286 <+153>:   push   eax
   0x56556287 <+154>:   call   0x56556060 <puts@plt>
   0x5655628c <+159>:   add    esp,0x10
   0x5655628f <+162>:   mov    eax,0x0
   0x56556294 <+167>:   mov    edx,DWORD PTR [ebp-0xc]
   0x56556297 <+170>:   sub    edx,DWORD PTR gs:0x14
   0x5655629e <+177>:   je     0x565562a5 <main+184>
   0x565562a0 <+179>:   call   0x565563d0 <__stack_chk_fail_local>
   0x565562a5 <+184>:   lea    esp,[ebp-0x8]
   0x565562a8 <+187>:   pop    ecx
   0x565562a9 <+188>:   pop    ebx
   0x565562aa <+189>:   pop    ebp
   0x565562ab <+190>:   lea    esp,[ecx-0x4]
   0x565562ae <+193>:   ret
```

몇 번 실행시켜보면 알듯이, 시리얼 검증 로직은 `compare` 함수에서 이뤄진다. `compare`함수를 확인해보자.

```
(gdb) disas compare
Dump of assembler code for function compare:
   0x565562af <+0>:     push   ebp
   0x565562b0 <+1>:     mov    ebp,esp
   0x565562b2 <+3>:     push   esi
   0x565562b3 <+4>:     push   ebx
   0x565562b4 <+5>:     sub    esp,0x10
   0x565562b7 <+8>:     call   0x565560f0 <__x86.get_pc_thunk.bx>
   0x565562bc <+13>:    add    ebx,0x2d44
   0x565562c2 <+19>:    sub    esp,0xc
   0x565562c5 <+22>:    push   DWORD PTR [ebp+0x8]
   0x565562c8 <+25>:    call   0x56556080 <strlen@plt>
   0x565562cd <+30>:    add    esp,0x10
   0x565562d0 <+33>:    mov    esi,eax
   0x565562d2 <+35>:    sub    esp,0xc
   0x565562d5 <+38>:    push   DWORD PTR [ebp+0xc]
   0x565562d8 <+41>:    call   0x56556080 <strlen@plt>
   0x565562dd <+46>:    add    esp,0x10
   0x565562e0 <+49>:    cmp    esi,eax
   0x565562e2 <+51>:    je     0x565562eb <compare+60>
   0x565562e4 <+53>:    mov    eax,0xffffffff
   0x565562e9 <+58>:    jmp    0x56556343 <compare+148>
   0x565562eb <+60>:    mov    DWORD PTR [ebp-0xc],0x17
   0x565562f2 <+67>:    mov    DWORD PTR [ebp-0x10],0x0
   0x565562f9 <+74>:    jmp    0x56556329 <compare+122>
   0x565562fb <+76>:    mov    edx,DWORD PTR [ebp-0x10]
   0x565562fe <+79>:    mov    eax,DWORD PTR [ebp+0x8]
   0x56556301 <+82>:    add    eax,edx
   0x56556303 <+84>:    movzx  eax,BYTE PTR [eax]
   0x56556306 <+87>:    movsx  edx,al
   0x56556309 <+90>:    mov    ecx,DWORD PTR [ebp-0x10]
   0x5655630c <+93>:    mov    eax,DWORD PTR [ebp+0xc]
   0x5655630f <+96>:    add    eax,ecx
   0x56556311 <+98>:    movzx  eax,BYTE PTR [eax]
   0x56556314 <+101>:   movsx  eax,al
   0x56556317 <+104>:   xor    eax,DWORD PTR [ebp-0xc]
   0x5655631a <+107>:   cmp    edx,eax
   0x5655631c <+109>:   je     0x56556325 <compare+118>
   0x5655631e <+111>:   mov    eax,0xffffffff
   0x56556323 <+116>:   jmp    0x56556343 <compare+148>
   0x56556325 <+118>:   add    DWORD PTR [ebp-0x10],0x1
   0x56556329 <+122>:   sub    esp,0xc
   0x5655632c <+125>:   push   DWORD PTR [ebp+0xc]
   0x5655632f <+128>:   call   0x56556080 <strlen@plt>
   0x56556334 <+133>:   add    esp,0x10
   0x56556337 <+136>:   mov    edx,DWORD PTR [ebp-0x10]
   0x5655633a <+139>:   cmp    eax,edx
   0x5655633c <+141>:   ja     0x565562fb <compare+76>
   0x5655633e <+143>:   mov    eax,0x0
   0x56556343 <+148>:   lea    esp,[ebp-0x8]
   0x56556346 <+151>:   pop    ebx
   0x56556347 <+152>:   pop    esi
   0x56556348 <+153>:   pop    ebp
   0x56556349 <+154>:   ret
```

지금 Writeup을 작성하는 컴퓨터에 디컴파일러가 없지만, 실제로 디컴파일러를 사용해서 확인해보면 특정 문자열을 0x17로 xor한 후 한글자씩 비교하는 로직임을 알 수 있다. `compare`를 호출하기 전에 들어가는 인자를 확인하자.

```
Breakpoint 2, 0x56556254 in main ()
(gdb) x/10x $esp
0xffffce50:     0xffffce6c      0x56557008      0xf7ffdb40      0x56556207
0xffffce60:     0x56555322      0xf7fdb7bd      0x5655529c      0x44434241
0xffffce70:     0x44434241      0x44434241
(gdb) x/s 0xffffce6c
0xffffce6c:     "ABCDABCDABCDABCD"
(gdb) x/s 0x56557008
0x56557008:     "Q[VPl^yaredrHxqHOXEj"
```

해당 문자열을 무엇으로 xor하는지는 `compare`의 어셈블리에서 확인할 수 있다. 

```
(gdb) disas compare
Dump of assembler code for function compare:
...
   0x565562eb <+60>:    mov    DWORD PTR [ebp-0xc],0x17
...
   0x56556317 <+104>:   xor    eax,DWORD PTR [ebp-0xc]
```

0x17로 한글자씩 xor을 수행하는데, xor의 역연산은 xor이기 때문에 해당 문자열을 다시 xor해주면 된다.

``` python
>>> res = []
>>> for i in "Q[VPl^yaredrHxqHOXEj":
...     res.append(chr(ord(i)^0x17))
... 
>>> res
['F', 'L', 'A', 'G', '{', 'I', 'n', 'v', 'e', 'r', 's', 'e', '_', 'o', 'f', '_', 'X', 'O', 'R', '}']
>>> "".join(res)
'FLAG{Inverse_of_XOR}'
```
## 문제 해결

해당 문자열을 입력하면 문제를 해결할 수 있다. FLAG는 입력한 문자열이다.

``` bash
pngwna@ArchPngWnA ..ithub/2020_freshmen_reversing_ctf/0x02 (git)-[Writeup/0x0x] % ./0x02
[KUICS] Serial number for Flag Print Service? : FLAG{Inverse_of_XOR}
[KUICS] Valid serial! The flag is the answer you typed! ^^
```

FLAG : `FLAG{Inverse_of_XOR}`