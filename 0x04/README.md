# 0x04
## 문제 파악

아키텍처는 이전문제와 같고, 이 문제는 0x01, 0x02처럼 주어진 검증 로직을 통과하는 입력값을 찾는 문제다

## 바이너리 분석

바이너리 흐름은 이전과 비슷하고, 이번에는 `hash`함수에서 입력값을 처리한다. 분석을 하면 `hash`의 반환값이 0x0e000000와 같으면 FLAG를 얻을 수 있다.

`hash`함수를 보자.

```
(gdb) disas hash
Dump of assembler code for function hash:
   0x565562fa <+0>:     push   ebp
   0x565562fb <+1>:     mov    ebp,esp
   0x565562fd <+3>:     sub    esp,0x20
   0x56556300 <+6>:     call   0x56556435 <__x86.get_pc_thunk.ax>
   0x56556305 <+11>:    add    eax,0x2cfb
   0x5655630a <+16>:    mov    eax,DWORD PTR [ebp+0x8]
   0x5655630d <+19>:    add    eax,0x3
   0x56556310 <+22>:    movzx  eax,BYTE PTR [eax]
   0x56556313 <+25>:    movsx  eax,al
   0x56556316 <+28>:    shl    eax,0x18
   0x56556319 <+31>:    mov    edx,eax
   0x5655631b <+33>:    mov    eax,DWORD PTR [ebp+0x8]
   0x5655631e <+36>:    add    eax,0x2
   0x56556321 <+39>:    movzx  eax,BYTE PTR [eax]
   0x56556324 <+42>:    movsx  eax,al
   0x56556327 <+45>:    shl    eax,0x10
   0x5655632a <+48>:    add    edx,eax
   0x5655632c <+50>:    mov    eax,DWORD PTR [ebp+0x8]
   0x5655632f <+53>:    add    eax,0x1
   0x56556332 <+56>:    movzx  eax,BYTE PTR [eax]
   0x56556335 <+59>:    movsx  eax,al
   0x56556338 <+62>:    shl    eax,0x8
   0x5655633b <+65>:    add    edx,eax
   0x5655633d <+67>:    mov    eax,DWORD PTR [ebp+0x8]
   0x56556340 <+70>:    movzx  eax,BYTE PTR [eax]
   0x56556343 <+73>:    movsx  eax,al
   0x56556346 <+76>:    add    eax,edx
   0x56556348 <+78>:    mov    DWORD PTR [ebp-0x18],eax
   0x5655634b <+81>:    mov    eax,DWORD PTR [ebp+0x8]
   0x5655634e <+84>:    add    eax,0x7
   0x56556351 <+87>:    movzx  eax,BYTE PTR [eax]
   0x56556354 <+90>:    movsx  eax,al
   0x56556357 <+93>:    shl    eax,0x18
   0x5655635a <+96>:    mov    edx,eax
   0x5655635c <+98>:    mov    eax,DWORD PTR [ebp+0x8]
   0x5655635f <+101>:   add    eax,0x6
   0x56556362 <+104>:   movzx  eax,BYTE PTR [eax]
   0x56556365 <+107>:   movsx  eax,al
   0x56556368 <+110>:   shl    eax,0x10
   0x5655636b <+113>:   add    edx,eax
   0x5655636d <+115>:   mov    eax,DWORD PTR [ebp+0x8]
   0x56556370 <+118>:   add    eax,0x5
   0x56556373 <+121>:   movzx  eax,BYTE PTR [eax]
   0x56556376 <+124>:   movsx  eax,al
   0x56556379 <+127>:   shl    eax,0x8
   0x5655637c <+130>:   add    edx,eax
   0x5655637e <+132>:   mov    eax,DWORD PTR [ebp+0x8]
   0x56556381 <+135>:   add    eax,0x4
   0x56556384 <+138>:   movzx  eax,BYTE PTR [eax]
   0x56556387 <+141>:   movsx  eax,al
   0x5655638a <+144>:   add    eax,edx
   0x5655638c <+146>:   mov    DWORD PTR [ebp-0x14],eax
   0x5655638f <+149>:   mov    eax,DWORD PTR [ebp+0x8]
   0x56556392 <+152>:   add    eax,0xb
   0x56556395 <+155>:   movzx  eax,BYTE PTR [eax]
   0x56556398 <+158>:   movsx  eax,al
   0x5655639b <+161>:   shl    eax,0x18
   0x5655639e <+164>:   mov    edx,eax
   0x565563a0 <+166>:   mov    eax,DWORD PTR [ebp+0x8]
   0x565563a3 <+169>:   add    eax,0xa
   0x565563a6 <+172>:   movzx  eax,BYTE PTR [eax]
   0x565563a9 <+175>:   movsx  eax,al
   0x565563ac <+178>:   shl    eax,0x10
   0x565563af <+181>:   add    edx,eax
   0x565563b1 <+183>:   mov    eax,DWORD PTR [ebp+0x8]
   0x565563b4 <+186>:   add    eax,0x9
   0x565563b7 <+189>:   movzx  eax,BYTE PTR [eax]
   0x565563ba <+192>:   movsx  eax,al
   0x565563bd <+195>:   shl    eax,0x8
   0x565563c0 <+198>:   add    edx,eax
   0x565563c2 <+200>:   mov    eax,DWORD PTR [ebp+0x8]
   0x565563c5 <+203>:   add    eax,0x8
   0x565563c8 <+206>:   movzx  eax,BYTE PTR [eax]
   0x565563cb <+209>:   movsx  eax,al
   0x565563ce <+212>:   add    eax,edx
   0x565563d0 <+214>:   mov    DWORD PTR [ebp-0x10],eax
   0x565563d3 <+217>:   mov    eax,DWORD PTR [ebp+0x8]
   0x565563d6 <+220>:   add    eax,0xf
   0x565563d9 <+223>:   movzx  eax,BYTE PTR [eax]
   0x565563dc <+226>:   movsx  eax,al
   0x565563df <+229>:   shl    eax,0x18
   0x565563e2 <+232>:   mov    edx,eax
   0x565563e4 <+234>:   mov    eax,DWORD PTR [ebp+0x8]
   0x565563e7 <+237>:   add    eax,0xe
   0x565563ea <+240>:   movzx  eax,BYTE PTR [eax]
   0x565563ed <+243>:   movsx  eax,al
   0x565563f0 <+246>:   shl    eax,0x10
   0x565563f3 <+249>:   add    edx,eax
   0x565563f5 <+251>:   mov    eax,DWORD PTR [ebp+0x8]
   0x565563f8 <+254>:   add    eax,0xd
   0x565563fb <+257>:   movzx  eax,BYTE PTR [eax]
   0x565563fe <+260>:   movsx  eax,al
   0x56556401 <+263>:   shl    eax,0x8
   0x56556404 <+266>:   add    edx,eax
   0x56556406 <+268>:   mov    eax,DWORD PTR [ebp+0x8]
   0x56556409 <+271>:   add    eax,0xc
   0x5655640c <+274>:   movzx  eax,BYTE PTR [eax]
   0x5655640f <+277>:   movsx  eax,al
   0x56556412 <+280>:   add    eax,edx
   0x56556414 <+282>:   mov    DWORD PTR [ebp-0xc],eax
   0x56556417 <+285>:   mov    edx,DWORD PTR [ebp-0x18]
   0x5655641a <+288>:   mov    eax,DWORD PTR [ebp-0x10]
   0x5655641d <+291>:   add    eax,edx
   0x5655641f <+293>:   mov    DWORD PTR [ebp-0x8],eax
   0x56556422 <+296>:   mov    edx,DWORD PTR [ebp-0x14]
   0x56556425 <+299>:   mov    eax,DWORD PTR [ebp-0xc]
   0x56556428 <+302>:   add    eax,edx
   0x5655642a <+304>:   mov    DWORD PTR [ebp-0x4],eax
   0x5655642d <+307>:   mov    eax,DWORD PTR [ebp-0x8]
   0x56556430 <+310>:   xor    eax,DWORD PTR [ebp-0x4]
   0x56556433 <+313>:   leave  
   0x56556434 <+314>:   ret
```

디컴파일러등을 활용하면 알 수 있지만, 해당 바이너리의 코드 원형은 다음과 같다.
``` C
int hash(char* msg)
{   
    uint32_t p1;
    uint32_t p2;
    uint32_t p3;
    uint32_t p4;

    p1 = (uint32_t)((msg[3] << 24) + (msg[2] << 16) + (msg[1] << 8) + (msg[0] << 0));
    p2 = (uint32_t)((msg[7] << 24) + (msg[6] << 16) + (msg[5] << 8) + (msg[4] << 0));
    p3 = (uint32_t)((msg[11] << 24) + (msg[10] << 16) + (msg[9] << 8) + (msg[8] << 0));
    p4 = (uint32_t)((msg[15] << 24) + (msg[14] << 16) + (msg[13] << 8) + (msg[12] << 0));

    uint32_t s1 = p1 + p3;
    uint32_t s2 = p2 + p4;

    return (int)(s1^s2);
}
```

16바이트 문자열을 4블록으로 나눠서, 1, 3블록을 더한 값과 2, 4블록을 더한 값을 xor하는 형식이다.

그 반환값이 0x0e000000이 되려면, AAAABBBBCCCCDDDD에서 각 블록의 3번째 바이트까지 같게 문자열을 만들어주면 되고, 해당 문자열은 쉽게 만들 수 있다. 

어려워보이지만, 몇 번 계산해보면 쉽게 조건을 만족하는 값을 찾을 수 있다.

## 문제 해결

해당 문자열을 입력하면 문제를 해결할 수 있다. 물론 조건을 만족하는 다른 문자열 역시 검사를 통과한다.

``` bash
pngwna@ArchPngWnA ..ithub/2020_freshmen_reversing_ctf/0x04 (git)-[Writeup/0x0x] % ./0x04    
[KUICS] Welcome to SECURE Flag Print Service! Enter the code : 12341235qwerqwes
[KUICS] Valid serial! Here is the flag you ordered ^^
FLAG{Break_the_hash!}
```

FLAG : `FLAG{Break_the_hash!}`