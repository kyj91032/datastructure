//정적 메모리 할당

#include <stdio.h>

int main(void) {
    
    int n = 10; //변수의 선언.
    double d = 3.141592;
    printf("%d\n", n);
    printf("%f", d); //변수를 이용해 메모리 주소를 기억하지 않아도 메모리 데이터를 쉽게 호출할 수 있다.
    
    int a[5]; //배열의 선언.
    int na = sizeof(a) / sizeof(a[0]); //요소의 개수.
    printf("%d", a[1]); //배열의 호출.
    
    int a = 57;
    int *x; //포인터 선언.
    x = &a; //포인터 초기화. x와 a의 자료형은 같아야 한다.
    int *x = &a; //포인터 선언과 초기화. 포인터 변수에 대입할 수 있는 값은 1. NULL(아직 초기화되지 않은 포인터) 2. 다른 변수의 주소나 배열명, 함수명 3. malloc()이나 calloc()에 의해 반환되는 주소값
    printf("%p\n", x);
    printf("%p", &a); //둘의 주소값은 같음. x와 &a.
	
    int *y; //초기화 안된 포인터.
    *y = 57; //포인터가 가르키는 주소는 없는데, 그 안의 값은 57?
    printf("%d", *y); //C99에서 variable is used uninitialized in this function 오류 발생. 변수가 초기화가 안된 상태에서 사용될 때 발생하는 오류.
	
	
    return 0;
}


//동적 메모리 할당 (필요할 때 메모리를 할당하고, 불필요해지면 메모리를 해제하면 필요한 요소 개수의 배열을 언제든지 자유롭게 만들 수 있다.)

#include <stdio.h>
#include <stdlib.h>

int main(void) {

    int *x, *y;
	
    x = malloc(sizeof(int) * 10); //int형 [10]크기의 메모리 할당. 메모리 값은 쓰레기값. x가 int형 포인터이므로 알아서 배열처럼 메모리 공간이 나뉘며 x는 첫 4byte 공간을 가르킨다.
	
    y = calloc(10, sizeof(int)); //int형 [10]크기의 메모리 할당. 메모리 값은 0으로 초기화.
	
    printf("%p %p\n", x, &x[0]); //확보한 메모리의 첫번째 주소 반환. 0x55abadb26260
    printf("%p\n", x+1); //0x558bde0e5264
	
    //‘%p’ expects argument of type ‘void *’ ?? (void*)로 캐스팅 하면 됨.

    printf("%d\n", x[0]); //쓰레기 값
    printf("%d\n", y[0]); //0 반환
	
    free(x);
    free(y); //메모리 할당 해제
	
    return 0;
}


// 함수 포인터

double func(int a); //int형 인수를 받고 double형 값을 반환하는 func라는 이름의 함수 선언.

double(*func_p)(int a); //int형 인수를 받고 double형 값을 반환하는 함수를 가르킬 수 있는 포인터 함수 func_p 선언.

func_p = func; //포인터 함수 func_p가 func를 가르키도록 func_p를 초기화.
func_p(); //함수 포인터로 func함수 호출. 원래는 (*func_p)();임.


int sum(int x1, int x2) {
	return x1 + x2;
}
int mul(int x1, int x2) {
	return x1, x2;
}

void calc(int(*summul)(int, int), int a, int b) //함수 calc에 매개변수로 함수포인터 summul 선언. 함수 포인터를 매개변수로 선언할 경우 (*)를 생략하여 int summul(int, int)로 선언 가능.
{
	printf("%d", (*summul)(a, b)); //(*summul)(a, b)는 summul(a, b)로 호출해도 됨.
}


