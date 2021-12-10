//정적 메모리 할당

#include <stdio.h>

int main(void) {
    
    int n = 10;
    double d = 3.141592; //변수의 선언.
    
    printf("%d\n", n);
    printf("%f", d); //변수를 이용해 메모리 주소를 기억하지 않아도 쉽게 출력할 수 있다.
    
    int a[5]; //배열의 선언.
    int na = sizeof(a) / sizeof(a[0]); //요소의 개수.
    
    int *x; //포인터 변수 선언.
    int a = 57;
    x = &a; //포인터 초기화.
    
    int *y; //포인터 변수 선언.
    *y = 57; //포인터 값은 없는데, 그 안의 값은 57.
    int y = 57; //차라리 이렇게 씀?
  

	return 0;
}
