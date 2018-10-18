#include <bits/stdc++.h>
using namespace std;

struct Node{
	int k;
	struct Node *next;
};typedef struct Node node;

main(){
	node *n;
	n=new node();
	n->k=5;
	n->next=NULL;

	node *p=new node();
	p=n;
	n->k=3;
	//n->next=new node();

	cout<< p->k<<"\n"<<n->k;
}