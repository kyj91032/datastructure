#include <stdio.h>
#include <stdlib.h>


typedef struct {
	int no;
	char name[20];
} Member;

void PrintMember(const Member *x)
{
	printf("%d %s", x->no, x->name);
}

typedef struct __node {
	Member data;
	struct __node *prev;
	struct __node *next;
} Dnode;

typedef struct {
	Dnode *head;
	Dnode *crnt;
} Dlist;


static Dnode *AllocDNode (void)
{
	return calloc(1, sizeof(Dnode));
}

static void SetDNode (Dnode *n, const Member *x, const Dnode *prev, const Dnode *next){
	n->data = *x;
	n->prev = prev;
	n->next = next;
}

void Initialize (Dlist *list)
{
	Dnode *dummyNode = AllocDNode();
	list->head = list->crnt = dummyNode;
	dummyNode->prev = dummyNode->next = dummyNode;
}

static int IsEmpty (const Dlist *list)
{
	return list->head->next == list->head; //list->head->prev == list->head도 가능
}

void PrintCurrent (const Dlist *list)
{
	if(IsEmpty(list))
		printf("선택한 노드가 없습니다.");
	else
		PrintMember(&list->crnt->data);
}

void PrintLnCurrent (const Dlist *list)
{
	PrintCurrent(list);
	putchar('\n');
}

Dnode *Search (Dlist *list, const Member *x, int compare(const Member *x, const Member *y)) {
	Dnode *ptr = list->head->next;
	while(ptr != list->head)//리스트가 비어있지 않는 동안, 다 돌아서 머리 가르킬때까지
		if(compare(&ptr->data, x) == 0){
			list->crnt = ptr;
			return ptr;
		}
		ptr = ptr->next;
	return NULL;
}

void Print (const Dlist *list)
{
	if(IsEmpty(list))
		puts("노드가 없습니다.");
	else {
		Dnode *ptr = list->head->next;
		while(ptr != list->head){//리스트가 비어있지 않은 동안, 다 돌아서 머리 가르킬때까지
			PrintMember(&ptr->data);
			ptr = ptr->next;
		}
	}
}

void PrintReverse (const Dlist *list)
{
	if(IsEmpty(list))
		puts("노드가 없습니다.");
	else {
		Dnode *ptr = list->head->prev;
		while(ptr != list->head) {//리스트가 비어있지 않은 동안, 다 돌아서 머리 가르킬때까지
			PrintMember(&ptr->data);
			ptr = ptr->prev;
		}
	}
}

int next (Dlist *list)
{
	if(IsEmpty(list) || list->crnt->prev == list->head)//되돌아갈수 없음
		return 0;
	list->crnt = list->crnt->prev;
	return 1;
}

//p가 가르키는 노드 바로 다음 노드를 삽입
void InsertAfter(Dlist *list, Dnode *p, const Member *x)
{
	Dnode *ptr = AllocDNode();//메모리할당
	Dnode *nxt = p->next;
	p->next = p->next->prev = ptr;
	SetDNode(ptr, x, p, nxt);//메모리내용설정 //nxt의 정의가 굳이 필요한가?
	list->crnt = ptr;
}

void InsertFront(Dlist *list, const Member *x)
{
	InsertAfter(list, list->head, x);
}

void InsertRear(Dlist *list, const Member *x)
{
	InsertAfter(list, list->head->prev, x);
}

void Remove (Dlist *list, Dnode *p)
{
	p->prev->next = p->next;
	p->next->prev = p->prev;
	list->crnt = p->prev;
	free(p);
	if(list->crnt == list->head)
		list->crnt = list->head->next;
}

void RemoveFront (Dlist *list)
{
	if(!IsEmpty(list))
		Remove(list, list->head->next);
}

void RemoveRear (Dlist *list)
{
	if(!IsEmpty(list))
		Remove(list, list->head->prev);
}

void RemoveCurrent (Dlist *list)
{
	if(list->crnt != list->head)//선택된 노드가 더미노드가 아니면. 즉 리스트에 노드가 있으면
		Remove(list, list->crnt);
}

void Clear (Dlist *list)
{
	while(!IsEmpty(list))
		RemoveFront(list);
}

void Terminate (Dlist *list)
{
	Clear(list);
	free(list->head);
}

void Purge(Dlist *list, int compare(const Member *x, const Member *y))
{
	Dnode *ptr = list->head->next;

	while (ptr != list->head) { //리스트가 비어있지 않는 동안
		Dnode *ptr2 = ptr;
		Dnode *pre = ptr;

		while (pre->next != list->head) { //리스트가 비어있지 않는 동안
			ptr2 = pre->next;
			if (!compare(&ptr->data, &ptr2->data)) {
				pre->next = ptr2->next;
				free(ptr2);
			}
			else {
				pre = ptr2;
			}
		}
		ptr = ptr->next;
	}
	list->crnt = list->head;
}

Dnode *Retrieve(Dlist *list, int n)
{
	Dnode *ptr = list->head->next;
	
	while (n >= 0 && ptr != list->head) {
		if (n-- == 0) {
			list->crnt = ptr;
			return ptr;
		}
		ptr = ptr->next;
	}
	return NULL;
}
