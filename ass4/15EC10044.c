#include<stdio.h>
#include<stdlib.h>

struct tree{
	int data;
	struct tree *left, *right;
};

struct tree *rotateright(struct tree *root);
struct tree *rotateleft(struct tree *root);
int height(struct tree *root);
struct tree *insert(struct tree *root, int n,int k);
struct tree *delete(struct tree *root, int n, int k);

struct tree *getnode(int n){
	struct tree *temp=(struct tree *)malloc(sizeof(struct tree));
	temp->data=n;
	temp->right=NULL;
	temp->left=NULL;
	return temp;
}

int height(struct tree *root){
	int hl, hr;

	if(root==NULL)
		return -1;
	hl=height(root->left);
	hr=height(root->right);

	if(hl>hr)
		return hl+1;
	else
		return hr+1;
}

int minelement(struct tree* root)
{
	while(root->left)
	{
		root=root->left;
	}
	return root->data;
}

struct tree *rotateright(struct tree *root){
	struct tree *temp=root->left;
	root->left=temp->right;
	temp->right=root;

	return temp;
}

struct tree *rotateleft(struct tree *root){
	struct tree *temp=root->right;
	root->right=temp->left;
	temp->left=root;

	return temp;
}

struct tree *delete(struct tree *root, int n, int k){
	struct tree* temp;
	int minele;
	if(root==NULL)
		return NULL;
	if(n<root->data)
		root->left=delete(root->left,n,k);
	else if(n>root->data)
		root->right=delete(root->right,n,k);
	else
	{
		if(root->left==NULL&&root->right==NULL)
		  return NULL;
		if(root->left==NULL)
		{
			temp=root->right;
			return temp;
		}
		if(root->right==NULL)
		{
			temp=root->left;
			return temp;
		}
		else
		{
			minele=minelement(root->right);
			root->data=minele;
			root->right=delete(root->right,minele,k);
		}
	}
	
	int balance;
	balance=height(root->left)-height(root->right);
	if(balance>1)
	{
		if(height(root->left->left)>=height(root->left->right))
			return rotateright(root);
		else
			{
				root->left=rotateleft(root->left);
                return rotateright(root);
            }
	}
	if(balance<-1)
	{
		if(height(root->right->right)>=height(root->right->left))
			return rotateleft(root);
		else
			{
				root->right=rotateright(root->right);
                return rotateleft(root);
            }
	}
	return root;

}

struct tree *insert(struct tree *root, int n, int k){
	if(root==NULL)
		root=getnode(n);
	else if(n <= root->data)
		root->left=insert(root->left, n,k);
	else
		root->right=insert(root->right, n,k);

	int balance;
	balance=height(root->left)-height(root->right);
	
	if(balance>1)
	{
		if(height(root->left->left)>=height(root->left->right))
			return rotateright(root);
		else
			{
				root->left=rotateleft(root->left);
                return rotateright(root);
            }
	}
	if(balance<-1)
	{
		if(height(root->right->right)>=height(root->right->left))
			return rotateleft(root);
		else
			{
				root->right=rotateright(root->right);
                return rotateleft(root);
            }
	}
    
    return root;
}

void inorder(struct tree *root){

	if(root==NULL)
		return;
	
		inorder(root->left);
		printf("%d\t", root->data);
		inorder(root->right);
	
}


int main(){
	struct tree *root=NULL;
	int n=10;
	int i, val;
	printf("\nEnter elements:\n");
	int a[n];
	for(i=0;i<n;i++){
		scanf("%d", &a[i]);
		root=insert(root, a[i],0);
	}

	inorder(root);
    printf("\n");
	root=delete(root, a[6],0);
	inorder(root);
	printf("\n");

}