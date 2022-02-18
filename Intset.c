#include <stdio.h>
#include <stdlib.h>

typedef struct {
	int max;
	int num;
	int *set;
} intset;

int initialize(intset *s, int max)
{
	s->num = 0;
	if((s->set = calloc(max, sizeof(int))) == NULL) {
		s->max = 0;
		return -1;
	}
	s->max = max;
	return 0;
}

int ismember(const intset *s, int n)
{
	int i;
	for(i=0; i < s->num; i++)
		if(s->set[i] == n)
			return i;
	return -1;
}

void add(intset *s, int n)
{
	if(s->num < s->max && ismember(s, n) == -1)
		s->set[s->num++] = n;
}

void Remove(intset *s, int n)
{
	int idx;
	if((idx = ismember(s, n)) != -1) {
		s->set[idx] = s->set[--s->num];
	}
}

int capacity(const intset *s)
{
	return s->max;
}

int size(const intset *s)
{
	return s->num;
}

void assign(intset *s1, const intset *s2)
{
	int i;
	int n = (s1->max < s2->num) ? s1->max : s2->num;
	for(i=0; i<n; i++)
		s1->set[i] = s2->set[i];
	s1->num = n;
}

int equal(const intset *s1, const intset *s2)
{
	int i, j;
	if(size(s1) != size(s2))
		return 0;
	for(i = 0; i < s1->num; i++){
		for(j = 0; j < s2->num; j++)
			if(s1->set[i] == s2->set[j])
				break;
		if(j == s2->num)
			return 0;
	}
	return 1;
}

intset *Union(intset *s1, const intset *s2, const intset *s3)
{
	int i;
	assign(s1, s2);
	for(i=0; i<s3->num; i++)
		add(s1, s3->set[i]);
	return s1;
}

intset *intersection (intset *s1, const intset *s2, const intset *s3)
{
	int i, j;
	s1->num = 0;
	for(i=0; i < s2->num; i++)
		for(i=0; j < s3->num; j++)
			if(s2->set[i] == s3->set[j])
				add(s1, s2->set[i]);
	return s1;
}

intset *difference(intset *s1, const intset *s2, const intset *s3)
{
	int i, j;
	s1->num = 0;
	for(i=0; i < s2->num; i++){
		for(j=0; j < s3->num; j++)
			if(s2->set[i] == s3->set[j])
				break;
		if(j == s3->num)
			add(s1, s2->set[i]);
	}
	return s1;
}

void print(const intset *s)
{
	int i;

	for(i=0; i < s->num; i++)
		printf("%d ", s->set[i]);
	putchar('\n');
}

int isfull(const intset *s)
{
	return s->num >= s->max;
}

void clear(intset *s)
{
	s->num = 0;
}

intset *symmetricdifference(intset *s1, const intset *s2, const intset *s3)
{
	int i;

	s1->num = 0;

	for(i=0; i < s2->num; i++)
	{
		if(ismember(s3, s2->set[i]) == -1)
			add(s1, s2->set[i]);
	}

	for(i=0; i < s3->num; i++)
	{
		if(ismember(s2, s3->set[i]) == -1)
			add(s1, s3->set[i]);
	}

	return s1;
}

intset *tounion(intset *s1, const intset *s2)
{
	int i;

	for(i=0; i < s2->num; i++)
		add(s1, s2->set[i]);
	
	return s1;
}

intset *tointersection(intset *s1, const intset *s2)
{
	int i;

	while(i < s1->num) {
		if(ismember(s2, s1->set[i]) == -1)
			Remove(s1, s1->set[i]);
		else
			i++;
	}

	return s1;
}

intset *todifference(intset *s1, const intset *s2)
{
	int i;

	for(i=0; i < s2->num; i++)
		Remove(s1, s2->set[i]);

	return s1;
}

int issubset(const intset *s1, const intset *s2)
{
	int i,j;

	for(i=0; i < s1->num; i++){
		for(j=0; j < s2->num; j++)
			if(s1->set[i] == s2->set[j])
				break;
		if(j == s2->num)
			return 0;
	}
	return 1;
}

int ispropersubset(const intset *s1, const intset *s2)
{
	if(s1->num >= s2->num)
		return 0;
	
	return issubset(s1, s2);
}

void terminate(intset *s)
{
	if(s->set != NULL) {
		free(s->set);
		s->max = s->num = 0;
	}
}
