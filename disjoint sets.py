# 서로소 집합 자료구조: 서로소 부분 집합들로 나누어진 원소들의 데이터를 처리하기 위한 자료구조

# 트리 자료구조를 이용하여 집합을 표현하며 원소 B가 A에 속하는 것을 노드 B가 A를 부모 노드로 설정하는 것으로 표현한다. 최종적으로 루트 노드를 기준으로 서로소 집합을 나누게 된다.

v, e = map(int, input().split()) # 노드의 개수 v, 간선의 개수 e
parent = [0] * (v + 1) # 부모 테이블

for i in range(1, v + 1): # 모든 노드(원소)의 부모를 자기 자신으로 초기화.
  parent[i] = i

def find_parent(parent, x): # 특정 원소 x 가 속한 집합을 찾는 find 함수.
  if parent[x] != x:
    return find_parent(parent, parent[x]) # 재귀호출로 부모 노드를 거슬러서 x가 가르키는 루트만 딱 리턴함
  return x

# 경로 압축 기법: 각 노드에 대하여 find 함수를 호출한 이후에 해당 노드의 루트 노드가 바로 부모 노드가 되므로 각 원소의 루트 노드에 더 빠르게 접근할 수 있게 된다.
def find_parent(parent, x):
  if parent[x] != x:
    parent[x] = find_parent(parent, parent[x]) # 재귀호출로 부모 노드를 거스르는 과정에서 부모 테이블을 루트 테이블로 갱신하고 루트를 리턴함.
  return parent[x]

def union_parent(parent, a, b): # 두 원소가 속한 집합을 합치는 union 함수.
  a = find_parent(parent, a) # 원소 a의 루트
  b = find_parent(parent, b) # 원소 b의 루트
  if a > b:
    parent[b] = a # 루트 노드의 번호가 더 작은 집합을 부모로 합침.
  else:
    parent[a] = b

for i in range(e): # union 연산(= 간선 정보) 입력대로 수행
  a, b = map(int, input().split())
  union parent(parent, a, b)

for i in range(1, v + 1):
  print(find_parent(parent, i), end = ' ') # 각 원소가 속한 집합(루트 노드)를 출력

  
# 서로소 집합을 이용한 무방향 그래프에서의 사이클 판별 알고리즘: 간선을 확인하며 두 노드가 포함되어 있는 집합을 합치는 과정을 반복하면 사이클을 판별할 수 있다.

cycle = False # 사이클 발생 여부

for i in range(e):
  a, b = map(int input().split()) # 간선 정보 a, b
  if find_parent(parent, a) == find_parent(parent, b): # 입력받은 간선 (a, b)에서 각각의 원소의 루트 노드가 같다면, 사이클이 존재
    cycle = True
    break
  else:
    union_parent(parent, a, b) # ?? 걍 다 추가해놓고 하면 되는거 아닌가..

