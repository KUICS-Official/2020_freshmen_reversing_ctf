# 0x03
## 문제 파악

아키텍처는 이전 문제들과 같다.

이번 문제는 코드 흐름으로는 도달할 수 없는 `print_flag`함수에 도달하면 해결할 수 있는 문제이다. 

## 문제 해결

해당 문자열을 입력하면 문제를 해결할 수 있다. FLAG는 입력한 문자열이다.

```
Breakpoint 1, 0x565561dc in main ()
(gdb) disas main
Dump of assembler code for function main:
   0x565561cd <+0>:     lea    ecx,[esp+0x4]
   0x565561d1 <+4>:     and    esp,0xfffffff0
   0x565561d4 <+7>:     push   DWORD PTR [ecx-0x4]
   0x565561d7 <+10>:    push   ebp
   0x565561d8 <+11>:    mov    ebp,esp
   0x565561da <+13>:    push   ebx
   0x565561db <+14>:    push   ecx
=> 0x565561dc <+15>:    sub    esp,0x90
   0x565561e2 <+21>:    call   0x56556371 <__x86.get_pc_thunk.ax>
   0x565561e7 <+26>:    add    eax,0x2e19
   0x565561ec <+31>:    mov    ecx,DWORD PTR gs:0x14
   0x565561f3 <+38>:    mov    DWORD PTR [ebp-0xc],ecx
   0x565561f6 <+41>:    xor    ecx,ecx
   0x565561f8 <+43>:    mov    DWORD PTR [ebp-0x90],0x0
   0x56556202 <+53>:    cmp    DWORD PTR [ebp-0x90],0x0

(gdb) j *0x5655621f
Continuing at 0x5655621f.
FLAG{Jump_to_impossible}
*** stack smashing detected ***: terminated

Program received signal SIGABRT, Aborted.
0xf7fce569 in __kernel_vsyscall ()
```

FLAG : `FLAG{Jump_to_impossible}`