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
	struct __node *next;
} Node;

typedef struct {
	Node *head;
	Node *crnt;
} List;



static Node *AllocNode(void)
{
	return calloc(1, sizeof(Node));
}

static void SetNode(Node *n, const Member *x, const Node *next)
{
	n->data = *x;
	n->next = next;
}

void Initialize (List *list)
{
	list->head = NULL;
	list->crnt = NULL;
}

Node *search(List *list, const Member *x, int compare(const Member *x, const Member *y))
{
	Node *ptr = list->head;
	while(ptr != NULL) {
		if(compare(&ptr->data, x) == 0) {
			list->crnt = ptr;
			return ptr;
		}
		ptr = ptr->next;
	}
	return NULL;
}

void InsertFront (List *list, const Member *x)
{
	Node *ptr = list->head;
	list->head = list->crnt = AllocNode();
	SetNode(list->head, x, ptr);
}

void InsertRear (List *list, const Member *x)
{
	if(list->head == NULL)
		InsertFront(list, x);
	else {
		Node *ptr = list->head;
		while(ptr->next != NULL)
			ptr = ptr->next;
		ptr->next = list->crnt = AllocNode();
		SetNode(ptr->next, x, NULL);
	}
}

void RemoveFront (List *list)
{
	if(list->head != NULL) {
		Node *ptr = list->head->next;
		free(list->head);
		list->head = list->crnt = ptr;
	}
}

void RemoveRear (List *list)
{
	if(list->head != NULL) {
		if((list->head)->next == NULL) //괄호 왜있는거지?
			RemoveFront(list);
		else {
			Node *ptr = list->head;
			Node *pre;
			while(ptr->next != NULL) {
				pre = ptr;
				ptr = ptr->next;
			}
			pre->next = NULL;
			free(ptr);
			list->crnt = pre;
		}
	}
}

void RemoveCurrent (List *list)
{
	if(list->head != NULL) {
		if(list->crnt == list->head)
			RemoveFront(list);
		else {
			Node *ptr = list->head;
			while(ptr->next != list->crnt)
				ptr = ptr->next;
			ptr->next = list->crnt->next;
			free(list->crnt);
			list->crnt = ptr;
		}
	}
}

void Clear (List *list)
{
	while(list->head != NULL)
		RemoveFront(list);
	list->crnt = NULL;
}

void PrintCurrent (const List *list)
{
	if(list->crnt == NULL)
		printf("선택한 노드가 없습니다.");
	else
		PrintMember(&list->crnt->data);
}

void Print (const List *list)
{
	if(list->head == NULL)
		puts("노드가 없습니다");
	else {
		Node *ptr = list->head;
		while(ptr != NULL) {
			PrintMember(&ptr->data);
			ptr = ptr->next;
		}
	}
}

void Terminate(List *list)
{
	Clear(list);
}

void Purge (List *list, int compare(const Member *x, const Member *y))
{
	Node *ptr = list->head;

	while(ptr != NULL) {	//빈 리스트가 아닌 동안. 비면 종료
		Node *ptr2 = ptr;	
		Node *pre = ptr;

		while (pre->next != NULL) {	//노드가 2개 이상일 동안
			ptr2 = pre->next;
			if (!compare(&ptr->data, &ptr2->data)) {
				pre->next = ptr2->next; //이전 노드가 현재 노드(비교하는 노드)의 다음 노드를 가르키게 됨.
				free(ptr2); //현재 노드 해제
			}
			else {
				pre = ptr2; //다음 차례 조사하기 위해 pre를 ptr2로 끌어옴. 그리고 ptr2는 다시 next로 업데이트 되게 될것임
			}
		}
		ptr = ptr->next;
	}
	list->crnt = list->head;
}

Node *Retrieve (List *list, int n)
{
	Node *ptr = list->head; //ptr의 역할은 뭐지? 노드에 대한 커서?역할인가..

	while (n >= 0 && ptr != NULL) {
		if(n-- == 0) {
			list->crnt = ptr;
			return ptr;
		}
		ptr = ptr->next;
	}
	return NULL;
}


