#include <stdio.h>
#include <stdlib.h>
#include <time.h>

	int  travelling_salesman(int size, int n[size+1],int city_graph[size][size])
{
	int i,j,dist=0,a,b;
	for( i=0;i<size;i++)
		{
			a=n[i]-1;  
		    b=n[i+1]-1;
			dist+=city_graph[a][b];
		}

	return dist;
}

void print_initial_soln(int population, int size, int (*initial_solns)[size + 1]){
	for(int i = 0; i < population; i++){
		printf("[ ");
		for(int j = 0; j < size + 1; j++)
			printf("%d ", initial_solns[i][j]);
			
		printf("]"); 
		printf("\n");
	}
}

void print_r(int size, int r[]){
	for(int x = 0; x < size + 1; x++)
		printf("%d ", r[x]);
}

int city_seen(int city_num, int size, int *pattern){
	for(int i = 0; i < size ; i++){
		if(pattern[i] == city_num)
			return 1;
	}
	return 0;
}//end of city_seen()

void random_pattern_generator(int size, int *pattern){

	int city_num;
	
	for(int x = 0; x < size; x++)
		pattern[x] = 0;	
	
	for(int x = 0; x < size; x++) {
		for(;;) {
			city_num = rand() % size + 1; 

			if(!city_seen(city_num, size, pattern)) {	
				pattern[x] = city_num;	
				break;            
			}
		}                       
	}
	pattern[size] = pattern[0]; 

}//end of random_pattern_generator()


void initial_soln_generator(int population, int size, int (*initial_solns)[size + 1], int *pattern) {
	
	int row = 0;
	while(row <= population - 1 ){
		random_pattern_generator(size, pattern);
		for(int j = 0; j < size + 1; j++){
			initial_solns[row][j] = pattern[j];
		}
		++row;
	} 
} //end of initial_soln_generator


int k;

int check(int size, int r[k],  int c) {
	int ch = 0;
	for(int i = 0; i < k; i++) {
		if(r[i] == c) {
			ch = 0;
			break;
		}
		else
			ch = 1;
	}
	return ch;
}

int left(int size, int r[k], int sol1[size + 1]) {
	int res;
	for(int i = 0; i < size; i++) {
		int found = 0;
		for(int j = 0; j < k; j++) {
			if(sol1[i] == r[j]) {
				found = 1;
				break;
			}
			else 
				continue;
		}
		if(found == 0)
			res = sol1[i];
	}
	return res;
}



void attract(int size, int r[size + 1], int sol1[size + 1], int sol2[size + 1], int (*city_graph)[size])	{
	
	
	int dis_sol1=travelling_salesman(size,sol1,city_graph);
	int dis_sol2=travelling_salesman(size,sol2,city_graph);
	int tempa = 0;
	int tempb = 0;

	k = 0;
	int next = 0; // next value to be stored in new solution
	
	// decide which initial vertex to take for new solution as per small starting edge
	
	//if(city_graph[sol1[0]-1][sol1[1]-1] < city_graph[sol2[0]-1][sol2[1]-1])
		r[k] = sol1[0];
	//else
		//r[k] = sol2[0];

	k++;
	
	// getting values for remaining vertices in the new solution 
	
	for(int i = 0; i < size; i++) {
		for(int j = 0; j < size; j++){
			if(r[i] == sol1[j])
				tempa = sol1[j+1];
			if(r[i] == sol2[j])
				tempb = sol2[j+1];
		}


		if(city_graph[r[i]-1][tempa-1] <= city_graph[r[i]-1][tempb-1])
			next = tempa;
		else
			next = tempb;

		if(check(size, r, next)) {
			r[k] = next;
			k++;
		}
		else {
			r[k] = left(size, r,  sol1);
			k++;
		}
	}
	k--;
	r[k] = r[0];
	
	/*for(int i=0;i<size+1;i++)
	{
		printf("%d\t",r[i]);
	}
	printf("\n");*/
	
	
	int dis_r=travelling_salesman(size,r,city_graph);
	if(dis_sol1<dis_r&&dis_sol1<dis_sol2)
	{
		for(int i=0;i<size+1;i++)
		r[i]=sol1[i];
	}
	else if(dis_sol2<dis_r&&dis_sol2<dis_sol1)
	{
	    for(int i=0;i<size+1;i++)
		r[i]=sol2[i];	
	}
	
}

void input_city_graph(int size, int (*city_graph)[size]) {
	for(int i = 0; i < size; i++)
		for(int j = 0; j < size; j++)
			scanf("%d", &city_graph[i][j]);
}

void print_city_graph(int size, int (*city_graph)[size]) {
	for(int i = 0; i < size; i++){
		for(int j = 0; j < size; j++)
			printf("%d ", city_graph[i][j]);
		
		printf("\n");
	}
}
int main() {

	int num_cities;
	printf("Enter Number of Cities	");
	scanf("%d", &num_cities);
	
	const int population = 20;
	
	int r[num_cities + 1];
	
	int sol1[num_cities + 1];
	int sol2[num_cities + 1];
	
	int city_graph[num_cities][num_cities];
		
	printf("Enter the graph representing cities and distances between them  ");
	input_city_graph(num_cities, city_graph);
	
	int pattern[num_cities + 1];
	
	int initial_solns[population][num_cities+ 1];

    initial_soln_generator(population,num_cities, initial_solns, pattern);
	
	printf("Initial Solutions\n");
	
	print_initial_soln(population, num_cities,initial_solns);

	
	for(int j = 0; j < num_cities + 1; j++) {
		sol1[j] = initial_solns[0][j];
	}

	int i = 1;
	while(i < population - 1) {
		for(int j = 0; j < num_cities + 1; j++) {
			sol2[j] = initial_solns[i][j];
		}	
		attract(num_cities, r,sol1, sol2, city_graph);
		
		for(int j = 0; j < num_cities + 1; j++) {
			sol1[j] = r[j];	
		}
		
		i++;
	}
	
	printf("\n");
	for(int i = 0; i < num_cities + 1; i++) {
		printf("%d\t",sol1[i]);
	}
	
	int init_dist=travelling_salesman(num_cities,sol1,city_graph);
	printf("\n");
	printf("%d\n",init_dist);
	
	int itr=1;
	while(itr<5)
	{
		printf("Iteration %d \n",itr);
		
    initial_soln_generator(population,num_cities, initial_solns, pattern);
	
	printf("Iteration %d Solutions\n",itr);
	
	print_initial_soln(population, num_cities,initial_solns);

	
	for(int j = 0; j < num_cities + 1; j++) {
		sol1[j] = initial_solns[0][j];
	}

	int i = 1;
	while(i < population - 1) {
		for(int j = 0; j < num_cities + 1; j++) {
			sol2[j] = initial_solns[i][j];
		}	
		attract(num_cities, r,sol1, sol2, city_graph);
		
		for(int j = 0; j < num_cities + 1; j++) {
			sol1[j] = r[j];	
		}
		
		i++;
	}
	
	printf("\n");
	for(int i = 0; i < num_cities + 1; i++) {
		printf("%d\t",sol1[i]);
		
	}
	printf("\n");
	
	int new_dist=travelling_salesman(num_cities,sol1,city_graph);
    printf("Distance from Iteration %d is %d \n",itr,new_dist);
	if(new_dist<init_dist)
	init_dist=new_dist;
	
	itr++;
		
	}
	
	printf("The Final Distance is %d",init_dist);
	
	
	
	return 0;
	// 0 10 20 15 30 10 0 5 20 40 20 5 0 15 5 15 20 15 0 10 30 40 5 10 0
	// 0 11 7 6 8 14 11 0 7 9 12 13 7 7 0 3 7 8 6 9 3 0 4 8 8 12 7 4 0 10 14 13 8 8 10 0  
	// 0 10 6 2 15 17 8 10 0 5 12 3 9 6 6 5 0 1 5 3 5 2 12 1 0 4 2 4 15 3 5 4 0 1 3 17 9 3 2 1 0 2 8 6 5 4 3 2 0
}

