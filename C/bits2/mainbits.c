#include"bits.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int main(int argc, char const *argv[])
{

	int n, p,  option,flag=1;
	unsigned char x, y;
	unsigned int start, end, value, res;
	unsigned char tmpC[SIZE_BYTE];
	char tmpI[SIZE_INT];
	 char intToChar[SIZE_BYTE];




	while(flag){
		printf("\n--------MENU--------\n");
		printf("1 to complement\n");
		printf("2: Rotate \n");
		printf("3: SetBits_1 \n");
		printf("4: SetBits_2 \n\n");
		printf("please choose an option : ");
		scanf("%d",&option);


		switch(option)
		{
		
			case 1:
				printf("please enter char x: ");
				scanf("%d",&x);
				IntToBin(x, intToChar);
				printf("%s\n", intToChar);
				res = complement(x);
				CharToBin(res,tmpC);
				printf("%s\n", tmpC );
				break;
			case 2:
				printf("please enter char x: ");
				scanf("%d",&x);
				IntToBin(x, intToChar);
				printf("%s\n", intToChar);
				printf("please enter how many bit to rotate: ");
				scanf("%d",&n);
				res=rotate(n,x);
				CharToBin(res,tmpC);
				printf("%s\n", tmpC );
				break;

			case 3:
				printf("please enter char x: ");
				scanf("%d",&x);
				IntToBin(x, intToChar);
				printf("%s\n", intToChar);
				printf("please enter char y: ");
				scanf("%d",&y);
				IntToBin(x, intToChar);
				printf("%s\n", intToChar);
				if (y>255 || x>255)
				{
					printf("ERROR INVALID INPUT\n");
					return 0;
				}
				printf("please enter amount of bits to take from y: ");
				scanf("%d",&n);
				printf("how many bits from the right you want to start from: ");
				scanf("%d",&p);
				res=SetBits_1(x,n,p,y);
				CharToBin(res,tmpC);
				printf("%s\n", tmpC );
				break;

			case 4:
				printf("please enter char x: ");
				scanf("%d",&x);
				IntToBin(x, intToChar);
				printf("%s\n", intToChar);
				
				printf("please enter the start index :");
				scanf("%u",&start);
				printf("please enter the end index :");
				scanf("%u",&end);
				printf("please enter the bit to insert :");
				scanf("%u",&value);
				res = SetBits_2(x,start,end,value);
				IntToBin(res,tmpI);
				printf("%s\n", tmpI);
				break;

			default:
				flag=0;
				break;
		}	

	}

	return 0;
}
