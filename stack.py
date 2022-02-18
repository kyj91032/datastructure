# 스택 자료구조: 한 쪽 끝에서만 자료를 넣고 뺄 수 있는 선형 구조로 되어 있어 선입후출의 구조를 가지는 자료구조이다.

# 스택의 기본 동작 과정
'''
1. 스택 공간을 정의한다.
2. 스택 공간의 끝에서 push와 pop이 이뤄지도록 한다.
'''

# stack 코드

''' python

stack = [] #스택 공간

삽입5 - 삽입2 - 삽입3 - 삽입7 - 삭제 - 삽입1 - 삽입4 - 삭제

stack.append(5) # append()는 리스트의 가장 뒤쪽에 데이터를 삽입한다. (후입)
stack.append(2)
stack.append(3)
stack.append(7)
stack.pop() # pop()은 리스트의 가장 뒤쪽 데이터를 꺼낸다. (선출)
stack.append(1)
stack.append(4)
stack.pop()

print(stack[::-1]) # 최상단 데이터부터 출력.
print(stack) # 최하단 데이터부터 출력.
'''

''' C

#include <stdio.h>
#include <stdlib.h>

typedef struct {
	int max; //스택의 용량
	int *stk; //스택 배열(동적 메모리)	
	int ptr; //스택 커서 (요소를 추가하고 진행시켜 놓는, 진행시키고 요소를 삭제하는), 현재 요소의 개수
} intstack;

int initialize(intstack *s, int max) //스택 초기화
{
	s->ptr = 0; //ptr 초기화
	if(s->stk = calloc(max, sizeof(int)) == NULL){ //stk 초기화
		s->max = 0;
		return -1;
	}
	s->max = max; //max 초기화
	return 0;
}

int push(intstack *s, int x) //스택에 데이터를 푸시
{
	if(s->ptr >= s->max) //오버플로 방지
		return -1;
	s->stk[s->ptr++] = x; //stk에 데이터x 푸시 한 후 커서 ptr++
	return 0;
}

int pop(intstack *s, int *x) //스택에 데이터를 팝
{
	if(s->ptr <= 0) //언더플로 방지
		return -1;
	*x = s->stk[--s->ptr]; //커서 --ptr후 stk의 데이터를 x로 팝. push와 달리 call by address임.
	return 0;
}

int Peek(const intstack *s, int *x) //스택에서 데이터를 피크
{
	if(s->ptr <= 0) //언더플로 방지
		return -1;
	*x = s->stk[s->ptr - 1]; //커서 ptr - 1의 stk의 데이터를 x로 피크.
	return 0;
}

void clear(intstack *s) //스택 청소
{
  s->ptr = 0;
}

int capacity(const intstack *s) //스택 최대 용량 리턴
{
  return s->max;
}

int size(const intstack *s) //스택 현재 데이터의 개수 리턴
{
  return s->ptr;
}

int isempty(const intstack *s) //스택이 비었는지
{
  return s->ptr <= 0;
}

int isfull(const intstack *s) //스택이 가득 찼는지
{
  return s->ptr >= s->max;
}

int search(const intstack *s, int x) //스택에서 검색
{
  int i;
  for(i = s->ptr - 1; i >= 0; i--) //최상단 -> 최하단으로 선형검색
    if(s->stk[i] == x)
      return i;
    return -1;
}

void print(const intstack *s) //스택의 모든 데이터 출력
{
  int i;
  for(i=0; i < s->ptr; i++)
    printf("%d ", s->stk[i]);
  putchar('\n');
}

void terminate(intstack *s) //스택 완전 종료 (메모리 반납)
{
  if(s->stk != NULL)
    free(s->stk);
  s->max = s->ptr = 0;
}
'''
