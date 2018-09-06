#include <stdio.h> 
#include <math.h>


void ackermann(long long int a, long long int b){

	int ack[b];
	int i=1,j=0;
	int flag=0; int pos;   
	
    while(1){
    	if(a==0){
    		b++;

    		if(pos-- == 0){
    			flag=0;
    			break;
    		}

    		a=ack[pos];
    		continue;
            
    	}

    	if(b==0){
    		a--;
    		b=1;
    		continue;
    	}

    	int value_pos=pos++;
    	ack[value_pos]=a-1;
    	b--;
    }

    printf("%lld", b);
}

main(){

	long long int a,b;

	printf("Enter the indexes: \t");

	scanf("%lld", &a);
	scanf("%lld", &b);
	ackermann(a, b);
	printf("\n");
}
