#include<stdio.h>

#define SIZE 5
int v;
int initialSoln[120][SIZE + 1];
int fireflies[10][SIZE+1];
int idx = 0;
int distances[120];
int  travelling_salesman(int n[v+1],int g[v][v],int v)
{
	int i,j,dist=0,a,b;
	/*for( i=0;i<v;i++)
	{
		for( j=0;j<v;j++)
		{
			printf("%d",g[i][j]);
		}
	}
	for( i=0;i<v+1;i++)
	{
		printf("%d\n",n[i]);
	}*/
	for( i=0;i<v;i++)
		{
			a=n[i]-1;
		     b=n[i+1]-1;
			 
			// printf("%d%d\n",a,b);
			
			
			//printf("%d\n",g[a][b]);
			dist+=g[a][b];
		}

	return dist;
}




/*long int factorial(int n){
	long int fact = 1;
	for(int i = n; i > 1; i--){
		fact *= i;
	}
	
	return fact;
}*/

void setInitialSolns(int a[], int size){
	int i = 0;
	for(i = 0; i < SIZE; i++) {
        initialSoln[idx][i] = a[i];
    }
    initialSoln[idx][i] = a[0];
    idx++;
}



//function to print the array

void printSolns() {
   	printf("Now printing saved solutions \n\n");
    for(int i = 0; i < 120; i++) {
		for(int j = 0 ; j < SIZE + 1; j++){
			printf("%d ", initialSoln[i][j]);
		}
		 printf("\n");
    }
   
}

//function to swap the variables
void swap(int *a, int *b) {
    int temp;
    temp = *a;
    *a = *b;
    *b = temp;
}

//permutation function
void permutation(int *arr, int start, int end) {
	
	
    if(start==end) {		
        setInitialSolns(arr, end + 1);
        return;
    }
   
    for(int i=start;i<=end;i++) {
        //swapping numbers
        swap((arr+i), (arr+start));
        //fixing one first digit
        //and calling permutation on
        //the rest of the digits
        permutation(arr, start+1, end);
        swap((arr+i), (arr+start));
    }
}



int main()
	{
		
		int a,b;
		int dist=0;
		int i,j;
		printf("Enter the number of vertices\n");
	scanf("%d",&v);
	    int g[v][v];
		int n[v+1];

		printf("Enter the edges\n");
	    for( i=0;i<v;i++)
	   {
		for( j=0;j<v;j++)
		{
			scanf("%d",&g[i][j]);
		}
		
	}
	int size;
    
    printf("Enter the size of array\n");
    scanf("%d",&size);
   
    int arr[size];
    for(int i=0;i<size;i++)
        scanf("%d",&arr[i]);
    //calling permutation function
    permutation(arr, 0, size-1);
	
	for(i=0;i<120;i++)
	{
		int tmp[SIZE+1];
		for(int j=0;j<SIZE+1;j++)
		{
			tmp[j]=initialSoln[i][j];
			printf("%d\t",tmp[j]);
		}
		distances[i]=travelling_salesman(tmp,g,v);
		printf("%d\n",distances[i]);
	
	}
	int index[120];
	for(int i=0;i<120;i++)
	{
		index[i]=i;
	}
	int k=0;
	for(int i=0;i<120;i++)
	{
		for(int j=i+1;j<120;j++)
		{
		if(distances[i]>distances[j])
		{
          int t=distances[i];
          distances[i]=distances[j];
          distances[j]=t;
		  int t2=index[i];
		  index[i]=index[j];
          index[j]=t2;		  
		}
		
			
			
		
	}
	//printf("%d\n",distances[i]);
	}
	for(int i=0;i<10;i++)
	{
		int ind=index[i];
		printf("%d\n",ind);
		for(int j=0;j<SIZE+1;j++)
		{
			
			fireflies[i][j]=initialSoln[ind][j];
		}
	}
	printf("Best Ten Solutions\n");
	for(i=0;i<10;i++)
	{
		int tmp[SIZE+1];
		for(int j=0;j<SIZE+1;j++)
		{
			tmp[j]=fireflies[i][j];
			printf("%d\t",tmp[j]);
		
		}
		printf("%d\n",distances[i]);
	
	}
		
	/*for(int i=0;i<120;i++)
	{
		printf("%d\n",distances[i]);
	}*/
	return 0;
	}
	
	//0 10 20 15 30 10 0 5 20 40 20 5 0 15 5 15 20 15 0 10 30 40 5 10 0
