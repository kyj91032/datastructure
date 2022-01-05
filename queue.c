/* 파이썬에서 queue

from collections import deque  # queue 라이브러리보다 효율적이고 간단해서 그냥 deque 씀

queue = deque()  # 큐 구현을 위해 deque 라이브러리 사용. 큐 공간 생성. queue를 deque 객체로 정의. deque([list]) 리스트를 매개변수로 받아서 시작 데이터 설정 가능.

삽입5 - 삽입2 - 삽입3 - 삽입7 - 삭제 - 삽입1 - 삽입4 - 삭제

queue.append(5)
queue.append(2)
queue.append(3)
queue.append(7)
queue.popleft()  # 덱의 왼쪽에서 데이터 삭제
queue.append(1)
queue.append(4)
queue.popleft()

print(queue)  # 먼저 들어온 순서대로 출력.
deque([3, 7, 1, 4])  # 리스트로 변환하려면 list().

*/


#include <stdio.h>
#include <stdlib.h>

typedef struct {
	int max; //큐의 용량
	int *que; //큐 배열(동적 메모리)
	//불변
	
	int num; //큐에 있는 현재 요소의 개수
	int rear; //큐의 리어 커서. (요소를 추가하고 진행시켜 놓는)
	int front; //큐의 프런트 커서. (요소를 삭제하고 진행시켜 놓는)
	//가변
} intqueue;


int initialize(intqueue *q, int max) //큐 초기화
{
	q->num = q->front = q->rear = 0; //num, front, rear 초기화
	if((q->que = calloc(max, sizeof(int))) == NULL){ /* que 초기화. **que의 호출에 대하여. que의 메모리 주소값을 호출할 때는 q->que 와 (*q).que 둘 다 가능하며,
							    que의 메모리 내용 값을 호출할 때는 *(q->que), *((*q).que) 그리고 q->que[], (*q).que[]이 가능하다.
							    보통 보다 직관적인 -> 연산자를 사용한다. */
		q->max = 0;
		return -1;
	}
	q->max = max; //max 초기화
	return 0;
}

int enque(intqueue *q, int x) //큐에 데이터를 인큐
{
	if(q->num >= q->max) //오버플로 방지
		return -1;
	else {
		q->num++; //요소 개수 +1
		q->que[q->rear++] = x; //que에 데이터 x 푸시 한 후 rear커서(추가하며 진행하는)++
		if(q->rear == q->max) //추가 후에 rear커서 == max(rear커서가 다시 돌아왔을 때)인지 확인 후 rear커서 다시 0 으로 초기화. 커서 벗어나지 않고 계속 진행할 수 있도록
			q->rear = 0;
		return 0;
	}
}
 
int deque(intqueue *q, int *x) //큐에 데이터를 디큐
{
	if(q->num <= 0) //언더플로 방지
		return -1;
	else {
		q->num--; //요소개수 -1
		*x = q->que[q->front++]; //que의 최하단 요소를 *x에 디큐. **enque와 달리 call by address(stack 영역?)
		if(q->front == q->max) //삭제 후에 front 커서 == max(front 커서가 다시 돌아왔을 때)인지 확인 후 front 커서 다시 0으로 초기화. 커서 벗어나지 않고 계속 진행할 수 있도록.
			q->front = 0;
		return 0;
	}
}

int Peek(const intqueue *q, int *x) //큐에서 데이터를 피크
{
	if(q->num <= 0) //언더플로 방지
		return -1;
	*x = q->que[q->front]; //front는 진행되어 있기 때문에, *x에 피크만 하면 됨.
	return 0;
}
 
void clear(intqueue *q) //큐를 청소
{
	q->num = q->front = q->rear = 0;
}
 
int capacity(const intqueue *q) //큐의 용량 리턴
{
	return q->num;
}
 
int size(const intqueue *q) //큐의 현재 요소 개수 리턴
{
	return q->num;
}
 
int isfull(const intqueue *q) //큐가 가득찼는지
{
	return q->num >= q->max;
}

int search(const intqueue *q, int x) //큐에서 선형검색. que 메모리에서 인덱스를 반환.
{
	int i, idx;
	for(i=0; i < q->num; i++){
		if(q->que[idx = (i + q->front) % q->max] == x) /* 최하단 -> 최상단으로 검색. 인덱스가 max를 초과할 것 방지해서 idx = (i + q->front) % q->max로 설정.
								  커서가 max 도달 시 0부터 진행되게 함. */
			return idx; //i + 1 이면 큐 내에서 몇번째 요소인지를 반환함.
	}
	return -1;
}

 
void print(const intqueue *q) //큐의 모든 데이터 출력
{
	int i;
	for(i=0; i < q->num; i++)
		printf("%d ", q->que[(i + q->front) % q->max]);
	putchar('\n');
}
 
void terminate(intqueue *q) //큐 완전 종료 (메모리 반납)
{
	if(q->que != NULL)
		free(q->que);
	q->max = q->num = q->front = q->rear = 0;
}
