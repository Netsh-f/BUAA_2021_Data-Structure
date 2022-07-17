#include<stdio.h>
int chess[20][20];
int i=0,j=0,flag=0;

void move(int direction,int n)
{
	if(direction==1)//水平方向
	{
		if(chess[i][j+1]==n && chess[i][j+2]==n && chess[i][j+3]==n && (chess[i][j-1]==0 || chess[i][j+4]==0))
			flag=n; 
	}
	else if(direction==2)//上下方向 
	{
		if(chess[i+1][j]==n && chess[i+2][j]==n && chess[i+3][j]==n && (chess[i-1][j]==0 || chess[i+4][j]==0))
			flag=n;
	}
	else if(direction==3)//斜右方向 
	{
		if(chess[i+1][j+1]==n && chess[i+2][j+2]==n && chess[i+3][j+3]==n && (chess[i-1][j-1]==0 || chess[i+4][j+4]==0))
			flag=n;
	}
	else if(direction==4)//斜左方向 
	{
		if(chess[i+1][j-1]==n && chess[i+2][j-2]==n && chess[i+3][j-3]==n && (chess[i-1][j+1]==0 || chess[i+4][j-4]==0))
			flag=n;
	}
}
int main()
{
	for(i=1;i<=19;i++)
	{
		for(j=1;j<=19;j++)
			scanf("%d",&chess[i][j]);
	}
	for(i=1;i<=19;i++)
	{
		for(j=1;j<=19;j++)
		{
			if(chess[i][j]==1)
			{
				if(j==1)
				{
					move(1,1);
					move(2,1);
					move(3,1);
					if(flag!=0)
						break;
				}
				else if(j==19)
				{
					move(2,1);
					move(4,1);
					if(flag!=0)
						break;
				}
				else
				{
					move(1,1);
					move(2,1);
					move(3,1);
					move(4,1);
					if(flag!=0)
						break;
				}
			}
			if(chess[i][j]==2)
			{
				if(j==1)
				{
					move(1,2);
					move(2,2);
					move(3,2);
					if(flag!=0)
						break;
				}
				else if(j==19)
				{
					move(2,2);
					move(4,2);
					if(flag!=0)
						break;
				}
				else
				{
					move(1,2);
					move(2,2);
					move(3,2);
					move(4,2);
					if(flag!=0)
						break;
				}
			}
			if(flag!=0)
				break;
		}
	}
	if(flag!=0)
		printf("%d:%d,%d",flag,i,j);
	else
		printf("No");
	return 0;
}
