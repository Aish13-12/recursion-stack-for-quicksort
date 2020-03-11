#include <stdio.h>
#include <stdlib.h>


struct info
{
	int lo;
	int hi;
	struct info*addrf;
	struct info*addrb;
};	

int array[10000];

int takingarray()
{
int i;


printf("Enter the integers to be sorted(enter -1 to terminate the array):\n");
printf("(CAUTION:Do not enter -1 as one of the numbers you want to sort)\n");


for(i = 0; i < 10000; i++)
{
    
    scanf("%d", &array[i]);

    
    if(array[i] == -1)
        break;
}
return i;
}



int partition(int* array, int start, int end){
	
	int l = start - 1;
	int pivot=rand()%(end-start+1)+start;
	int temp1=array[pivot];
	array[pivot]=array[end];
	array[end]=temp1;
	for (int i = start; i < end; ++i)
		if (array[i] < array[end]){
			
			int temp = array[l + 1];
			array[l+1] = array[i];
			array[i] = temp;

			
			l++;
		}
	
	int temp = array[l + 1];
	array[l+1] = array[end];
	array[end] = temp;

	
	return (l + 1);
}

void printwstack(struct info**head)
{
	struct info*temp;
	temp=*head;
	int i=1;
	while(temp->addrf!=NULL)
	{
		temp=temp->addrf;
		i++;
	
	}
	int j;
	for(j=0;j<i-1;j++)
	printf("\t");
	printf("{");
	int k;
	for(k=i-1;k>=0;k--)
	{
		printf("(%d,%d)",temp->lo,temp->hi);
		if(temp!=*head)
		printf(", ");
		temp=temp->addrb;
	}
	printf("}");
	printf("\n");	
	
	
}

void push(struct info**head,int lop,int hip)
{
	struct info*temp;
	temp=(struct info*)malloc(sizeof(struct info));
	temp->lo=lop;
	temp->hi=hip;
	temp->addrf=NULL;
	temp->addrb=NULL;
	if(*head==NULL)
	{
		*head=temp;
	}
	else
	{
		struct info*p;
		p=*head;
		while(p->addrf!=NULL)
		{
			p =p->addrf;
		}
		p->addrf=temp;
		temp->addrb=p;
	}
	
}


void pop(struct info**head)
{
	struct info*p;
	p=*head;
	struct info*prev;
	while(p->addrf!=NULL)
	{
		
		prev=p;
		p=p->addrf;
	}
	prev->addrf=NULL;
	p->addrb=NULL;
	free(p);
	
}

			
void quickSort(int* array, int start, int end,struct info**head)
{
	
	if (start < end)
	{
		
		int pivot_index = partition(array, start, end);
		push(head,start,pivot_index-1);
		printwstack(head);
		quickSort(array, start, pivot_index - 1,head);
		pop(head);
		
		push(head,pivot_index+1,end);
		printwstack(head);
		quickSort(array, pivot_index + 1, end,head);
		pop(head);
		
	}		
		
	
	
		
}




void printArray(int* array, int N){
	for (int i = 0 ; i < N; ++i)
		printf ("%d ", array[i]);
	printf ("\n");
}




int main()
{
	int N;
	N=takingarray();
	printf ("Original array: ");
	printArray(array, N);
	printf("Stack modification history\n");
	struct info*head;
	head=NULL;
	push(&head,0,N-1);
	printwstack(&head);
	quickSort(array, 0, N-1,&head);
	printf("\n");
	printf ("Sorted array: ");
	printArray(array, N);
	return 0;
}
