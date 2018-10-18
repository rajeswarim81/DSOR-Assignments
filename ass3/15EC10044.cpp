#include <bits/stdc++.h>

using namespace std;
int i,j,k,row,col;

typedef struct{
	int x,y;
}Move;

struct board{
	int mat[3][3];
	int turn;
	
	struct board *child;
	struct board *next;
};typedef struct board board;

board *new_board(board *b){
	board *temp=new board();
	temp->turn=b->turn;
	//temp->val=b->val;
	temp->child=NULL;
	temp->next=NULL;

	for(i=0;i<3;i++)
		for(j=0;j<3;j++)
			temp->mat[i][j]=b->mat[i][j];

	return temp;

}

int calc(board *b, int turn){
	int count=0;

	for(i=0;i<3;i++){
		if(  (b->mat[i][0]!=(!turn)) &&
		     (b->mat[i][1]!=(!turn)) &&
		     (b->mat[i][2]!=(!turn)) )

			count++;
	}

	for(i=0;i<3;i++){
		if(  (b->mat[0][i]!=(!turn)) &&
		     (b->mat[1][i]!=(!turn)) &&
		     (b->mat[2][i]!=(!turn)) )

			count++;
	}

	if(  (b->mat[0][0]!=(!turn)) &&
		 (b->mat[1][1]!=(!turn)) &&
		 (b->mat[2][2]!=(!turn)) )
		count++;

	if(  (b->mat[0][2]!=(!turn)) &&
		 (b->mat[1][1]!=(!turn)) &&
		 (b->mat[2][0]!=(!turn)) )
		count++;

	return count;
}

int checkwin(board *b){
	// Checking for Rows for X or O victory.
    for (int i = 0; i<3; i++)
    {
        if (b->mat[i][0]==b->mat[i][1] &&
            b->mat[i][1]==b->mat[i][2])
        {
            if (b->mat[i][0]==1)
                return +10;
            else if (b->mat[i][0]==0)
                return -10;
        }
    }

 
    // Checking for Columns for X or O victory.
    for (int col = 0; col<3; col++)
    {
        if (b->mat[0][col]==b->mat[1][col] &&
            b->mat[1][col]==b->mat[2][col])
        {
            if (b->mat[0][col]==1)
                return +10;
 
            else if (b->mat[0][col]==0)
                return -10;
        }
    }
 
    // Checking for Diagonals for X or O victory.
    if (b->mat[0][0]==b->mat[1][1] && b->mat[1][1]==b->mat[2][2])
    {
        if (b->mat[0][0]==1)
            return +10;
        else if (b->mat[0][0]==0)
            return -10;
    }
 
    if (b->mat[0][2]==b->mat[1][1] && b->mat[1][1]==b->mat[2][0])
    {
        if (b->mat[0][2]==1)
            return +10;
        else if (b->mat[0][2]==0)
            return -10;
    }
 
    // Else if none of them have won then return 0
    return 0;
}

int MovesLeft(board *b){
	for(i=0;i<3;i++){
		for(j=0;j<3;j++){
			if(b->mat[i][j] != -1)
				return 1;
		}
	}

	return 0;
}

int get_val(board *b, int k){
	if(k==0){
		int turn0=calc(b, !b->turn);
		int turn1=calc(b, b->turn);
		int turn=turn0-turn1;

		return turn;
	}
    
    int check=checkwin(b);

    if(check==10){
    	cout<<"You won!";
    	return check;
    }

    else if(check==-10){
    	cout<<"You lost!";
    	return check;
    }

    if(!MovesLeft){
    	cout<<"Tie!";
    	return 0;
    }
	int minval=99999, maxval=-99999,currval=0;

	for(i=0;i<3;i++){
		for(j=0;j<3;j++){
			if(b->mat[i][j]==-1){
				if(b->child==NULL){
					b->child=new_board(b);
					b->child->mat[i][j]=b->turn;
				}
				else{
					board *temp=new_board(b);
					temp->mat[i][j]=b->turn;
					temp->next=b->child;
					b->child=temp;
				}
                b->child->turn= !(b->turn);
				currval=get_val(b->child, k-1);

                if(b->turn){
                	minval=min(minval, currval);
                }
                else{
                	maxval=max(maxval,currval);
                }


			}
		}
	}

	if(b->turn)
		return minval;
	else
		return maxval;
}

Move lookahead(board *b, int k){
	Move best={-1,-1};
	int maxval=-9999,flag=1,currval=0; 
/*
	for(i=0;i<3;i++)
		for(j=0;j<3;j++)
			cout<< b->mat[i][j];
*/
	for(i=0;i<3;i++){
		for(j=0;j<3;j++){
			//cout<<i<<j<<"\n";
			if(b->mat[i][j]==-1){
				flag=0;
				b->mat[i][j]=b->turn;
				b->turn= !(b->turn);

				currval=get_val(b,k-1);

				b->turn= !(b->turn);
				b->mat[i][j]=-1;

                if(currval>maxval){

                	maxval=currval;
                	best.x=i;
                	best.y=j;
                }
            }
		}
	}
	if(flag)
		cout<<"No moves left!\n";

	//cout<<best.x;

	return best;
}

main(){
	board *b=new board();
	//let the opponent play ot for 0
	//let the palyer play it for 1
	//let the empty places be -1;
Move next_move;
	cout<<"Enter the board config:\n-1 for empty spaces\n1 for player's moves\n0 for opponent moves";
    b->turn=1;
	b->next=NULL;
	b->child=NULL;
	for(i=0;i<3;i++){
		for(j=0;j<3;j++){
			cin>>b->mat[i][j];
		}
		cout<<"\n";
	}

	/*

    for(i=0;i<3;i++)
		for(j=0;j<3;j++)
			cout<< b->mat[i][j];
   
	
	
    cout<<"\n";
	for(i=0;i<3;i++)
		for(j=0;j<3;j++)
			cout<< b->mat[i][j];
			*/

	
		next_move=lookahead(b,2);
		cout<<"The best move with 2 step look ahead is "<<next_move.x<<next_move.y;
	
	    next_move=lookahead(b,4);

	    cout<<"\nThe best move with 4 step look ahead is "<<next_move.x<<next_move.y;
}