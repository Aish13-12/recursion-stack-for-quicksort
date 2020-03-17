#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>

//The stack has been created as a singly linked list
//Node definition for the stack
struct info
{
	int lo;
	int hi;
	struct info*addrf;
	
};	
//Array to store input elements
int array[1000000];


//Function to take input elements 
int takingarray()
{
int i;

printf("(CAUTION:Do not enter -1 as one of the numbers you want to sort)\n");
printf("\n");
printf("Enter the integers to be sorted(enter -1 to terminate the array):\n");
printf("(Click ENTER after typing each number)\n");

for(i = 0; i < 10000; i++)
{
    
    scanf("%d", &array[i]);

    
    if(array[i] == -1)//if -1,then terminate
        break;
}
return i;//Returns the number of integers entered
}

//Function to partition the array

int partition(int* array, int start, int end)
{
	
	int l = start - 1;
	srand(time(NULL));
	int pivot=rand()%(end-start+1)+start;//Random choosing of a pivot
	int temp1=array[pivot];
	array[pivot]=array[end];//Exchanging pivot element with the end element
	array[end]=temp1;
	for (int i = start; i < end; ++i)
		if (array[i] < array[end])
		{
			//Swapping the adjacent elements
			int temp = array[l + 1];
			array[l+1] = array[i];
			array[i] = temp;

			
			l++;
		}
	//Swapping A[l+1] and A[end]
	int temp = array[l + 1];
	array[l+1] = array[end];
	array[end] = temp;

	//Returning the position of pivot
	return (l + 1);
}

//Prints the instantaneous contents of the stack
void printwstack(struct info**head)
{
	struct info*temp;
	temp=*head;
	int i=1;
	while(temp->addrf!=NULL)
	{
		temp=temp->addrf;
		i++;
	
	}//reaching the last node of the stack
	//int j;
	//for(j=1;j<i-1;j++)
	//printf("\t");
	
	int k;
	struct info*p;
	p=*head;
	p=p->addrf;//Starting from the node above the head
	for(k=0;k<i-1;k++)
	{
		int u;
		for(u=1;u<i-1;u++)
	    printf("\t");
		int s;
		for(s=i-1-k;s>1;s--)
		printf("        ");
		if(i==2)
		printf("{(%d,%d)}",p->lo,p->hi);
		else if(k==i-2&&i!=2)
		printf("{(%d,%d)",p->lo,p->hi);
		else if(k==0&&i!=2)
		printf("(%d,%d)}",p->lo,p->hi);
		else
		printf("(%d,%d)",p->lo,p->hi);
		printf("\r");
		
	    
	    p=p->addrf;		
	}
	
	printf("\n");	
	
	
}

//To push a node on top of the stack
void push(struct info**head,int lop,int hip)
{
	struct info*temp;
	temp=(struct info*)malloc(sizeof(struct info));
	temp->lo=lop;//Creating the node to be pushed
	temp->hi=hip;
	temp->addrf=NULL;
	
	if(*head==NULL)
	{
		*head=temp;
	}
	else
	{
		struct info*p;
		p=*head;
		while(p->addrf!=NULL)//Reaching the end of the stack
		{
			p =p->addrf;
		}
		p->addrf=temp;//Adding the new node to the top
		
	}
	
}

//To pop out the top node of the stack
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
	
	free(p);//Deleting the last node
	
}

//Quicksort algorithm			
void quickSort(int* array, int start, int end,struct info**head)
{
	
	if (start < end)
	{
		/*Printing the stack everytime a new node is pushed*/
		int pivot_index = partition(array, start, end);//Partitioning the array
		push(head,start,pivot_index-1);
		printwstack(head);
		quickSort(array, start, pivot_index - 1,head);//Calling quicksort recursively
		pop(head);
		//printwstack(head);
		push(head,pivot_index+1,end);
		printwstack(head);
		quickSort(array, pivot_index + 1, end,head);
		pop(head);
		//printwstack(head);
		
	}		
		
	
	
		
}



//Prints the array of integers
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
	printf("Stack modification history:\n");
	struct info*head;
	head=NULL;//Initiating the stack
	push(&head,0,N-1);
	//printwstack(&head);
	quickSort(array, 0, N-1,&head);
	printf("\n");
	printf ("Sorted array: ");
	printArray(array, N);
	return 0;
}

