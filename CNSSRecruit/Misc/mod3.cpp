#include <bits/stdc++.h>
using namespace std;

/*
mod3(int): // x86-64 gcc
        movsx   rax, edi
        mov     edx, edi
        imul    rax, rax, 1431655766
        sar     edx, 31
        shr     rax, 32
        sub     eax, edx
        lea     eax, [rax+rax*2]
        sub     edi, eax
        mov     eax, edi
        ret
mulMagic(long long): // MIPS64
        dsll    $3,$4,2
        daddu   $3,$3,$4
        dsll    $2,$3,4
        daddu   $3,$3,$2
        dsll    $2,$3,8
        daddu   $3,$3,$2
        dsll    $2,$3,16
        daddu   $2,$3,$2
        j       $31
        daddu   $2,$2,$4
*/

int mod3(int x) { // 20 operators
	int edi = x;
	int edx = x;
	long long lx = x;
	long long rax = 0;
	long long _3 = lx << 2;
	_3 = _3 + lx;
	long long _2 = _3 << 4;
	_3 = _3 + _2;
	_2 = _3 << 8;
	_3 = _3 + _2;
	_2 = _3 << 16;
	_2 = _3 + _2;
	rax = _2 + lx;
	edx = edx >> 31;
	rax = rax & 0xFFFFFFFF00000000LL;
	rax = rax >> 32;
	rax = rax + (~edx) + 1;
	rax = rax + (rax << 1);
	x = x + (~rax) + 1;
	int ans = x;
	return ans;
}

int main()
{
	for (int i=1<<31;i<=(1<<31)+10000;i++)
		assert(mod3(i)==i%3);
	return 0;
}