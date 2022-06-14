#include <stdio.h>
#include <stdlib.h>
#include "btree.h"

int main()
{
	BTree * T;
	init(&T);
	for(int i=0; i<30; i++) {
		insert(&T, rand()%100);
	}
	printf("\n\n");
	print(T);
	printf("\n\n");
	delete_node(&T, 83);
	printf("\n\n");
	print(T);
	printf("\n\n");
	
}
