// 이진탐색트리: 이진 탐색이 동작할 수 있도록 고안된 트리 자료구조이다. '왼쪽 자식노드 < 부모 노드 < 오른쪽 자식노드' 라는 대소관계를 활용한다.

#include <stdio.h>
#include <stdlib.h>

typedef struct { // 노드의 데이터. Member
	int no;
	char name[20];
} Member;

typedef struct __bnode { // 노드 정의. 데이터와 왼쪽 자식노드와 오른쪽 자식노드의 포인터 가짐. BinNode
	Member data;
	struct __bnode *left;
	struct __bnode *right;
} BinNode;


static BinNode *AllocBinNode(void) // 노드를 동적으로 할당하는 함수. BinNode형 객체를 생성한다. AllocBinNode()
{
	return calloc(1, sizeof(BinNode));
}

static void SetBinNode(BinNode *n, const Member *x, const BinNode *left, const BinNode *right) // 노드를 초기화하는 함수. SetBinNode()
{
	n->data = *x; // 노드의 데이터 초기화
	n->left = left; // 왼쪽 자식 노드의 포인터
	n->right = right; // 오른쪽 자식 노드의 포인터
}


BinNode *Binary_search (BinNode *p, const Member *x) // 이진탐색트리에서 탐색하는 함수. Binary_search(), 시작 시 루트노드 포인터 전달.
{
	int cond; 
	if(p == NULL)
		return NULL; // 재귀함수의 종료조건, 검색 실패. 반복문으로 구현한다면 while(p != NULL)이 반복조건.
	else if((cond = MemberNocmp(x, &p->data)) == 0)
		return p; // 재귀함수의 종료조건, 검색 성공
	else if(cond < 0)
		Search(p->left, x); // 왼쪽 서브 트리에서 탐색
	else
		Search(p->right, x); // 오른쪽 서브 트리에서 탐색
}

BinNode *Add (BinNode *p, const Member *x) // 이진탐색트리에 노드를 삽입. Add(), 시작 시 루트노드 포인터 전달.
{
	int cond;
	if(p == NULL) {
		p = AllocBinNode();
		SetBinNode(p, x, NULL, NULL); // 재귀함수의 종료조건, 노드가 비어있다면 삽입. 삽입 성공
	} else if((cond = MemberNocmp(x, &p->data)) == 0)
		printf("이미 있음"); // 재귀함수의 종료조건, 이미 데이터가 존재. 삽입 실패
	else if(cond < 0)
		p->left = Add(p->left, x); // 왼쪽 자식 노드에서 다시
	else
		p->right = Add(p->right, x); // 오른쪽 자식 노드에서 다시
	return p;
}

int Remove (BinNode **root, const Member *x)
{
	BinNode *next, *temp;
	BinNode **left;
	BinNode **p = root;

	while(1) {
		int cond;
		if(*p == NULL) {
			printf("노드 없음");
			return -1;
		} else if((cond = MemberNocmp(x, &(*p)->data)) == 0)
			break;
		else if(cond < 0)
			p = &((*p)->left);
		else
			p = &((*p)->right);
	}

	if((*p)->left == NULL)
		next = (*p)->right;
	else {
		left = &((*p)->left);
		while((*left)->right != NULL)
			left = &(*left)->right;
		next = *left;
		*left = (*left)->left;
		next->left = (*p)->left;
		next->right = (*p)->right;
	}
	temp = *p;
	*p = next;
	free(temp);

	return 0;
}

void PrintTree (const BinNode *p) // 이진탐색트리의 데이터를 오름차순으로 출력하려면 inorder(중위 순회) 진행.
{
	if(p != NULL) {
		PrintTree(p->left);
		PrintLnMember(&p->data);
		PrintTree(p->right);
	}
}

void PrintTreeReverse(const BinNode *p) // 내림차순은 중위 순회 반대로 진행.
{
	if(p != NULL) {
		PrintTreeReverse(p->right);
		PrintLnMember(&p->data);
		PrintTreeReverse(p->left);
	}
}

BinNode *GetMinNode(const BinNode *p) // 가장 왼쪽 자식 노드가 최솟값.
{
	if(p == NULL)
		return NULL;
	else {
		while(p->left != NULL)
			p = p->left;
		return p;
	}
}

BinNode *GetMaxNode(const BinNode *p) // 가장 오른쪽 자식 노드가 최대값.
{
	if (p == NULL)
		return NULL;
	else {
		while (p->right != NULL)
			p = p->right;
		return p;
	}
}

void FreeTree (BinNode *p) // 모든 노드를 삭제하는 함수. 자식부터 삭제하므로 postorder(후위 순회) 진행
{
	if(p != NULL){
		FreeTree(p->left);
		FreeTree(p->right);
		free(p);
	}
}
