#include <stdio.h>
#include <stdlib.h>
#include "btree.h"

void init(BTree **T)
{
	*T = (BTree *)malloc(sizeof(BTree));
	(*T)->n = 0;
	(*T)->leaf = 1;
	(*T)->keys = (int *)malloc((2*BT_DEGREE - 1) * sizeof(int));
	(*T)->c = (BTree **)malloc((2*BT_DEGREE) * sizeof(BTree*));
}
void search(BTree *T, int k, BTree ** res, int * index)
{
	int i;
	if (T->keys == NULL)
		return;
	for (i=0; i<T->n && k > T->keys[i]; i++);
		
	if(i<T->n && k == T->keys[i])
	{
		*res = T;
		*index = i;
		return;
	}
	else if(T->leaf == 1)
	{
		*res = NULL;
		*index = -1;
		return;
	}
	else
		search(T->c[i], k, res, index);	
}
void split_child(BTree * T, int i)
{
	BTree * y, *z;
	y = T->c[i];
	init(&z);
	z->leaf = y->leaf;
	z->n = BT_DEGREE - 1;
	
	int j;
	for(j=0; j < BT_DEGREE - 1; j++)
		z->keys[j] = y->keys[j + BT_DEGREE];
		
	if(z->leaf == 0)
	{
		for(j=0; j< BT_DEGREE; j++)
			z->c[j] = y->c[j + BT_DEGREE];
	}
	
	y->n = BT_DEGREE - 1;
	
	T->n = T->n + 1;
		
	for(j=T->n; j > i + 1; j--)
		T->c[j] = T->c[j-1];
	T->c[i + 1] = z;
	for(j=T->n - 1; j > i; j--)
		T->keys[j] = T->keys[j-1];
	T->keys[i] = y->keys[BT_DEGREE - 1];
}
void insert_non_full(BTree * T, int k)
{
	int i = T->n - 1;
	if (T->leaf == 1)
	{	 
		while(i >= 0 && k < T->keys[i])
		{
			T->keys[i + 1] = T->keys[i];
			i--;
		}
		T->keys[i + 1] = k;
		T->n = T->n + 1;
	}
	else
	{
		while(i >= 0 && k < T->keys[i]) 
			i--;
		i++;
		if(T->c[i]->n == 2*BT_DEGREE - 1)
		{
			split_child(T, i);
			if(T->keys[i] < k)
				i++;
		}
		insert_non_full(T->c[i], k);	
	}
}
void insert(BTree **T, int k)
{
	BTree *x = *T, *y;
	if((*T)->n == 2*BT_DEGREE - 1)
	{
		init(&y);
		*T = y;
		y->leaf = 0;
		y->n = 0;
		y->c[0] = x;
		split_child(y, 0);
		insert_non_full(y, k);
	}
	else
		insert_non_full(x, k); 	
}
void delete_recursive(BTree * res, int index)
{
	
	if(res->leaf == 1)
	{
		for(int i=index; i < res->n - 1 ;i++)
			res->keys[i] = res->keys[i+1];
		res->n = res->n - 1;
		return;
	}
	
	int L, R;
	BTree *l, *r;
	l = res->c[index];
	r = res->c[index+1];
	L = l->n;
	R = r->n;
	
	if (L >= BT_DEGREE)
	{
		res->keys[index] = l->keys[l->n - 1];
		delete_recursive(l, l->n - 1);
	}
	else if (R >= BT_DEGREE)
	{
		res->keys[index] = r->keys[0];
		delete_recursive(r, 0);
	}
	else
	{
		int k = res->keys[index];
		for(int i=index; i < res->n - 1 ;i++)
		{
			res->keys[i] = res->keys[i+1];
			res->c[i + 1] = res->c[i+2];
		}
		l->keys[L] = k;
		if(l->leaf == 0)
		{
			for(int i=0; i<R; i++)
				l->c[L + 1 + i] = r->c[i];
		}
		delete_recursive(l, L);
		l->n = L + R;
	}
}
void delete_node(BTree ** root, int k)
{
	BTree *T = *root;
	
	BTree *res;
	int index;
	search(T, k, &res, &index);
	
	delete_recursive(res, index);
}
void print(BTree * T)
{
	if(T->leaf == 1)
	{
		for(int i=0; i< T->n; i++)
			printf("%d ",T->keys[i]);
		return;
	}
	printf("<");	
	for(int i=0; i< T->n; i++)
		printf("%d ",T->keys[i]);
		
	printf(">");
	
	for(int i=0; i< T->n + 1; i++) {
		printf("[");
		print(T->c[i]);
		printf("]");
	}
}

