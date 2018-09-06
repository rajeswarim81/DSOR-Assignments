#include <stdio.h>

struct btree{
	int data;

	struct btree *left, *right;
};
typedef struct btree node;

Int MAX=30;

struct stack_{
	int top;
	node *arr[MAX];
};
typedef struct stack_ stack;