#include <bits/stdc++.h>

using namespace std;
int i,j,k;

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

int get_val(board *b, int k){
	cout<<"k="<<k<<"\n";

    if(k==0){

		int minval=9999;
		for(i=0;i<3;i++){
			for(j=0;j<3;j++){
				if(b->mat[i][j]==-1){
					
					b->mat[i][j]=1;

					if(b->child==NULL){
						b->child=new_board(b);
                    }
                    else{
                        board *temp=new_board(b);
                        temp->next=b->child;
                        b->child=temp;
                    }

                    int turn0=calc(b->child,0);
                    int turn1=calc(b->child,1);
                    //cout<<turn0<<turn1;

                    int turnval=turn0-turn1;
                    if(turnval<minval)
                    	minval=turnval;

                    b->mat[i][j]=-1;

				}

			}
		}

		return minval;
	}


	else{
        int minval=99999, maxval=-99999,currval;
		for(i=0;i<3;i++){
			for(j=0;j<3;j++){
				if(b->mat[i][j]==-1){
					
					b->mat[i][j]=b->turn;
					b->turn=!(b->turn);
					currval=get_val(b,k-1);
					b->turn=!(b->turn);
					b->mat[i][j]=-1;

					if(b->turn){
						if(currval <minval)
							minval=currval;

					}
					else{
						if(currval<maxval)
							maxval=currval;
					}

				}
			}
		}

		if(b->turn)
			return minval;
		else
			return maxval;
    }

}

Move lookahead(board *b, int k){
	Move bestmove={-1,-1};
	int bestval=-9999;
	int flag=0; int currval;

    for(i=0;i<3;i++){
		for(j=0;j<3;j++){
			if(b->mat[i][j]==-1){
				flag=1;
				b->mat[i][j]=1;
				b->turn= !(b->turn);
                currval=get_val(b,k-1);

                cout<<currval<<"\n";
                b->turn= (!b->turn);
				b->mat[i][j]=-1;

				if(currval>bestval){
                    cout<<"enter";
					bestval=currval;
					bestmove.x=i;
					bestmove.y=j;
				}
			}
		}
	}

	if(!flag)
		cout<<"No moves left\n";

	return bestmove;
}

main(){
	board *b=new board();
	//let the opponent play ot for 0
	//let the palyer play it for 1
	//let the empty places be -1;

	cout<<"Enter the board config:\n-1 for empty spaces\n1 for player's moves\n0 for opponent moves";
    
	for(i=0;i<3;i++){
		for(j=0;j<3;j++){
			b->mat[i][j]=-1;
		}
		cout<<"\n";
	}

    
	
	b->turn=1;
	
	b->next=NULL;
	b->child=NULL;

	int ans;
	 Move next_move;
	cout<<"Options:\n1. 2 step look ahead strategy \n2. 4 step look ahead strategy\n";
	cin>>ans;
	if(ans==1)
		next_move=lookahead(b,2);
	else
	    next_move=lookahead(b,4);

	cout<<"The best move is "<<next_move.x<<next_move.y;
}