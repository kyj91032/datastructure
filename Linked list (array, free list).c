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

#define Null -1

typedef int Index;

typedef struct {
	Member data;
	Index next;//연결리스트에서의 다음노드 커서
	Index Dnext;//프리 리스트에서의 다음노드 커서
} Node;

typedef struct {
	Node *n;//리스트 본체(배열)
	Index head;//포인터인 연결리스트는 node로 정의해서 그 주소를 가르켰지만 프리리스트에서는 index형으로 정의해서 list->head가 머리노드의 레코드를 가르키게 된다.
	Index max;//사용 중인 꼬리 레코드.. 배열의 가장 꼬리 쪽에 들어있는 레코드 번호
	Index deleted;//프리 리스트의 머리 노드
	Index crnt;
} List;


static Index GetIndex (List *list)//노드를 삽입할 때 레코드 번호를 정하는 함수
{
	if(list->deleted == Null)
		return ++(list->max);
	else {
		Index rec = list->deleted;
		list->deleted = list->n[rec].Dnext;//프리 리스트의 머리 노드의 다음 노드
		return rec;
	}
}

static void DeleteIndex (List *list, Index idx)//지정된 레코드를 삭제 리스트에 등록
{
	if(list->deleted == Null) { //삭제리스트가 비어있는 경우
		list->deleted = idx;//머리 바꾸고
		list->n[idx].Dnext = Null;//머리가 null가르키게 하기
	}
	else {//삭제리스트가 비어있지 않은 경우
		Index ptr = list->deleted;//머리 저장 해두고(이전 머리가 될 것)
		list->deleted = idx;//머리에 지정된(삭제할)레코드 넣고
		list->n[idx].Dnext = ptr;//머리가 저장해둔 이전 머리 가르키게 하기
		//왜 꼬리가 null가르키게 하는 코드는 없지?
	}
}

static void SetNode(Node *n, const Member *x, Index next)//Node *n은 리스트 본체랑 다른거임
{
	n->data = *x;
	n->next = next;
}

void Initialize (List *list, int size)
{
	list->n = calloc(size, sizeof(Node));
	list->head = Null;
	list->crnt = Null;
	list->max = Null;
	list->deleted = Null;
}

Index search (List *list, const Member *x, int compare(const Member *x, const Member *y))
{
	Index ptr = list->head;
	while(ptr != Null) {
		if(compare(&list->n[ptr].data, x) == 0) {
			list->crnt = ptr;
			return ptr;
		}
		ptr = list->n[ptr].next;
	}
	return Null;
}

void InsertFront (List *list, const Member *x)
{
	Index ptr = list->head;
	list->head = list->crnt = GetIndex(list);
	SetNode(&list->n[list->head], x, ptr);
}

void InsertRear (List *list, const Member *x)
{
	if(list->head == Null)
		InsertFront(list, x);
	else {
		Index ptr = list->head;
		while(list->n[ptr].next != Null)
			ptr = list->n[ptr].next;
		list->n[ptr].next = list->crnt = GetIndex(list);
		SetNode(&list->n[list->n[ptr].next], x, Null);
	}
}

void RemoveFront (List *list)
{
	if(list->head != Null) {
		Index ptr = list->n[list->head].next;
		DeleteIndex(list, list->head);
		list->head = list->crnt = ptr;
	}
}

void RemoveRear (List *list)
{
	if(list->head != Null) {
		if(list->n[list->head].next == Null)
			RemoveFront(list);
		else {
			Index ptr = list->head;
			Index pre;
			while(list->n[ptr].next != Null) {
				pre = ptr;
				ptr = list->n[ptr].next;
			}
			list->n[pre].next = Null;//pre의 다음. 즉 ptr이 가르키는 노드 Null로
			DeleteIndex(list, ptr);//ptr을 프리리스트로
			list->crnt = pre;//현재 노드를 꼬리노드로
		}
	}
}

void RemoveCurrent (List *list)
{
	if(list->head != Null) {
		if(list->crnt == list->head)
			RemoveFront(list);
		else {
			Index ptr = list->head;
			while(list->n[ptr].next != list->crnt)//list->n[ptr]은 이제 구조체가 아니라서 .next를 붙여서 다음 노드의 주소를 가져온다. ->next를 붙이는게 아님. 붙이려면 list->n[ptr]자체가 또 구조체라서 여기서 next를 불러오는 거여야됨.
				ptr = list->n[ptr].next;//이반복문이 끝나면 ptr은 현재노드의 바로 전 노드가 되어있을거임
			list->n[ptr].next = list->n[list->crnt].next;//이전노드를 현재의 다음노드 가르키도록
			DeleteIndex(list, list->crnt);
			list->crnt = ptr; //crnt는 삭제한 노드의 앞쪽 노드를 가르키도록 둠
		}
	}
}

void Clear (List *list)
{
	while(list->head != Null)
		RemoveFront(list);
	list->crnt = Null;
}

void PrintCurrent(const List *list)
{
	if(list->crnt == Null)
		printf("선택한 노드가 없습니다.");
	else
		PrintMember(&list->n[list->crnt].data);
}

void PrintLnCurrent(const List *list)
{
	PrintCurrent(list);
	putchar('\n');
}

void Print(const List *list)
{
	if(list->head == Null)
		puts("노드가 없습니다.");
	else {
		Index ptr = list->head;
		while(ptr != Null) {
			PrintMember(&list->n[ptr].data);
			putchar('\n');
			ptr = list->n[ptr].next;
		}
	}
}

void Terminate(List *list)
{
	Clear(list);
	free(list->n);
}

void Perge(List *list, int compare(const Member *x, const Member *y))
{
	Index ptr = list->head;

	while (ptr != Null) {//빈 리스트가 아닌 동안. 비면 종료
		Index ptr2 = ptr;
		Index pre = ptr;

		while (list->n[ptr2].next != Null) {//노드가 2개 이상일 동안
			ptr2 = list->n[pre].next;
			if (!compare(&list->n[ptr].data, &list->n[ptr2].data)) {
				list->n[pre].next = list->n[ptr2].next;
				DeleteIndex(list, ptr2);
			}
			else {
				pre = ptr2; //다음 차례 조사하기 위해 pre를 ptr2로 끌어옴. 그리고 ptr2는 다시 next로 업데이트 되게 될것임
			}
		}
		ptr = list->n[ptr].next; // ??뭐지
	}
	list->crnt = list->head;
}

Index Retrieve(List *list, int n)//n번째 노드의 커서(포인터)를 반환
{
	Index ptr = list->head;

	while (n >= 0 && ptr != Null) {
		if (n-- == 0) {
			list->crnt = ptr;
			return ptr;
		}
		ptr = list->n[ptr].next;//다음 노드 선택하며 반복되도록
	}
	return Null;
}
