#include <stdio.h>

typedef unsigned long bitset;

#define bitsetnull (bitset)0
#define bitsetbits 32
#define setof(no) ((bitset)1 <<(no))

int ismember(bitset s, int n)
{
	return s & setof(n);
}

void add(bitset *s, int n)
{
	*s |= setof(n);
}

void Remove(bitset *s, int n)
{
	*s &= ~setof(n);
}

int size(bitset s)
{
	int n = 0;
	for(; s != bitsetnull; n++)
		s &= s-1;
	return n;
}

void print(bitset s)
{
	int i;
	printf("{ ");
	for(i=0; i < bitsetbits; i++)
		if(ismember(s, i))
			printf("%d ", i);
	printf("}");
}

void printLn(bitset s)
{
	print(s);
	putchar('\n');
}

bitset symmetricdifference(bitset *s1, const bitset *s2, const bitset *s3) 
{
	bitset s4, s5;
	
	s4 = *s2 & ~*s3;
	s5 = *s3 & ~*s2;

	*s1 = s4 | s5;

	return *s1;
}

int main(void) {

	/// 추가 비트벡터 연산 ///

	bitset s1, s2;

	//s1 == s2; //서로 같은지//
	//s1 != s2; //서로 다른지//

	//s1 & s2 //교집합(ismember와 유사)//

	//s1 | s2 //합집합(add와 유사)//

	//s1 & ~s2 //차집합(remove와 유사)//

	return 0;
}
