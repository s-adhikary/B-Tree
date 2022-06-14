#ifndef _BTREE_
#define _BTREE_

#define BT_DEGREE 4

struct _Btree_
{
	int n;
	int * keys;
	int leaf;
	struct _Btree_ ** c;
};

typedef struct _Btree_ BTree;

void init(BTree**);
void search(BTree*, int, BTree**, int*);
void split_child(BTree*, int);
void insert_non_full(BTree*, int);
void insert(BTree**, int);
void delete_node(BTree **, int k);
void print(BTree *);

#endif
