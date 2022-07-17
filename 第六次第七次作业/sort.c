#include<stdio.h>
#include<stdlib.h>
#include<string.h>
int d[105], cnt, tmp[105];

void select(int n){
	int min, t, pt;
	for(int i=0;i<n;i++){
		min = d[i];
		for(int j=i+1;j<n;j++){
			cnt++;
			if(d[j] < min){
				min = d[j];
				pt = j;
			}
		}
		t = d[i];
		d[i] = d[pt];
		d[pt] = t;
	}
}

void bubble(int n){
	int t, f;
	for(int i=0;i<n;i++){
		f = 0;
		for(int j=0;j<n-1-i;j++){
			cnt++;
			if(d[j] > d[j+1]){
				t = d[j];
				d[j] = d[j+1];
				d[j+1] = t;
				f = 1;
			}
		}
		if(f == 0){
			break;
		}
	}
}

void adjust(int k[ ],int i,int n)
{
    int j,temp;
    temp=k[i];
    j=2*i+1;
    while(j<n){
        if(j<n-1 && k[j]<k[j+1])
            j++;
        cnt++;
        if(temp>=k[j]) 
            break;
        k[(j-1)/2]=k[j];
        j=2*j+1;
    }
    k[(j-1)/2]=temp;
}

void heap(int n){
	for(int i=n/2-1;i>=0;i--){
		adjust(d, i, n);
	}
	int num = n, t;
	while(num != 1){
		t = d[0];
		d[0] = d[num-1];
		d[num-1] = t;
		num--;
		adjust(d, 0, num);
	}
}

void merge(int x[ ],int tmp[ ],int left,int leftend,int rightend)
{
	if(left == rightend)
		return;
    int i=left, j=leftend+1, q=left;
    merge(d, tmp, left, (left+leftend)/2, leftend);
    merge(d, tmp, leftend+1, (leftend+1+rightend)/2, rightend);
    while(i<=leftend && j<=rightend)
    {
    	cnt++;
        if(x[i]<=x[j]) 
            tmp[q++]=x[i++];
        else
            tmp[q++]=x[j++];
    }
    while(i<=leftend)
        tmp[q++]=x[i++];
    while(j<=rightend)
        tmp[q++]=x[j++];
    for(i=left; i<=rightend; i++)
        x[i]=tmp[i];
}

void mergeSort(int n){
	merge(d, tmp, 0, (n-1)/2, n-1);
}

void swap(int *p1, int*p2){
	int t = *p1;
	*p1 = *p2;
	*p2 = t;
}

void quickSort(int k[ ],int left,int right)
{     
    int i, last;
    if(left<right){
        last=left; 
        for(i=left+1;i<=right;i++){
        	cnt++;
            if(k[i]<k[left])
                swap(&k[++last],&k[i]);
        }
        swap(&k[left],&k[last]);
        quickSort(k,left,last-1); 
        quickSort(k,last+1,right);   
    }
}

int main(){
	int n, op;
	scanf("%d %d", &n, &op);
	for(int i=0;i<n;i++){
		scanf("%d", &d[i]);
	}
	switch(op){
		case 1:
			select(n);
			break;
		case 2:
			bubble(n);
			break;
		case 3:
			heap(n);
			break;
		case 4:
			mergeSort(n);
			break;
		case 5:
			quickSort(d, 0, n-1);
			break;
	}
	for(int i=0;i<n;i++){
		printf("%d ", d[i]);
	}
	printf("\n%d",cnt);
	return 0;
}
