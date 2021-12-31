/* 파이썬에서 queue

from collections import deque  # queue 라이브러리보다 효율적이고 간단해서 그냥 deque 씀

queue = deque()  # 큐 구현을 위해 deque 라이브러리 사용. 큐 공간 생성.

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
#include "intqueue.h"

int initialize(intqueue *q, int max)
{
	q->num = q->front = q->rear = 0;
	if((q->que = calloc(max, sizeof(int))) == NULL){
		q->max = 0;
		return -1;
	}
	q->max = max;
	return 0;
}

int enque(intqueue *q, int x)
{
	if(q->num >= q->max)
		return -1;
	else {
		q->num++;
		q->que[q->rear++] = x;
		if(q->rear == q->max)
			q->rear = 0;
		return 0;
	}
}
 
int deque(intqueue *q, int *x)
{
	if(q->num <= 0)
		return -1;
	else {
		q->num--;
		*x = q->que[q->front++];
		if(q->front == q->max)
			q->front = 0;
		return 0;
	}
}

int Peek(const intqueue *q, int *x)
{
	if(q->num <= 0)
		return -1;
	*x = q->que[q->front];
	return 0;
}
 
void clear(intqueue *q)
{
	q->num = q->front = q->rear = 0;
}
 
int capacity(const intqueue *q)
{
	return q->num;
}
 
int size(const intqueue *q)
{
	return q->num;
}
 
int isfull(const intqueue *q)
{
	return q->num >= q->max;
}
 
int search(const intqueue *q, int x)
{
	int i, idx;
	for(i=0; i < q->num; i++){
		if(q->que[idx = (i + q->front) % q->max] == x)
			return idx;
	}
	return -1;
}
 
int search2(const intqueue *q, int x)
{
	int i, idx;
 
	for(i=0; i < q->num; i++){
		if(q->que[idx = (i + q->front) % q->max == x])
			return idx - q->front;
	}
	return -1;
}
 
void print(const intqueue *q)
{
	int i;
	for(i=0; i < q->num; i++)
		printf("%d ", q->que[i + q->front % q->max]);
	putchar('\n');
}
 
void terminate(intqueue *q)
{
	if(q->que != NULL)
		free(q->que);
	q->max = q->num = q->front = q->rear = 0;
}
