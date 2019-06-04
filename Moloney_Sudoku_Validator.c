/*Student: Michael Moloney
Class: CSC 4320 MW 2:30-5:30pm
Instructor:Zhisheng Yan
Assignment:Homework 1
Due Date: 2/17/2019*/
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
//array to store sudoku
int sudoku_array[9][9];
//array to compare sudoku against
int arr[]={1,2,3,4,5,6,7,8,9};
//declare thread handles
pthread_t t[11];

// This struct is the data to be passed to the thread
struct param
{
	int row;
	int column;
};
//array of int values to check thread returns
int final_check[11];
// column thread function
void *column_worker(void *arg){
	struct param *p=(struct param*)arg;
	int test_array[9];
	int row,col,y,z,a,valid_determiner=1;
	//create array out of numbers
	for(col=p->column;col<9;col++){
		for(row=0;row<9;row++){
			test_array[row]=sudoku_array[row][col];
		}
		//sort array
	    for(y=0;y<9;y++){
			for(z=y+1;z<9;z++){
				if(test_array[y]>test_array[z]){
					a=test_array[y];
                    test_array[y]=test_array[z];
                    test_array[z]=a;
            	}
        	}
    	}
	   //print sorted array
    	printf("column sorted array %d: ",col);
	    for(y=0;y<9;y++)
	        printf("%d, ",test_array[y]);
	    printf("\n");
	    //compare arrays
    	for(y=0;y<9;y++)
    		if(test_array[y]!=arr[y])
    			valid_determiner=0;	
	}
	//return wether or not columns are all valid
	if(valid_determiner==0)
		pthread_exit((int*)0);
	pthread_exit((int*)1); 
} 
// row thread function
void *row_worker(void *arg){
	struct param *p=(struct param*)arg;
	int test_array[9];
	int row,col,y,z,a,valid_determiner=1;
	//create array out of numbers
	for(row=p->row;row<9;row++){
		for(col=0;col<9;col++){
			test_array[col]=sudoku_array[row][col];
		}
		//sort array
	    for(y=0;y<9;y++){
			for(z=y+1;z<9;z++){
				if(test_array[y]>test_array[z]){
					a=test_array[y];
                    test_array[y]=test_array[z];
                    test_array[z]=a;
            	}
        	}
    	}
	   //print sorted array
    	printf("row sorted array %d: ",row);
	    for(y=0;y<9;y++)
	        printf("%d, ",test_array[y]);
	    printf("\n");
	    //compare arrays
    	for(y=0;y<9;y++)
    		if(test_array[y]!=arr[y])
    			valid_determiner=0;	
	}
	//return wether or not columns are all valid
	if(valid_determiner==0)
		pthread_exit((int*)0);
	pthread_exit((int*)1); 
} 
// subgrid thread function
void *subgrid_worker(void *arg){
	struct param *p=(struct param*)arg;
	int test_array[9];
	int index=0;
	int row,col,row_stop=p->row+3,col_stop=p->column+3,y,z,a;
	//create array out of numbers
	for(row=p->row;row<row_stop;row++){
		for(col=p->column;col<col_stop;col++){
			test_array[index]=sudoku_array[row][col];
			index++;
		}
	}
	//sort array
	    for(y=0;y<9;++y){
			for(z=y+1;z<9;++z){
				if(test_array[y]>test_array[z]){
					a=test_array[y];
                    test_array[y]=test_array[z];
                    test_array[z]=a;
            }
        }
    }
    //print sorted array
    printf("subgrid sorted array: ");
    for(y=0;y<9;y++)
        printf("%d, ",test_array[y]);
    printf("\n");
    //compare arrays
    for(y=0;y<9;y++)
		if(test_array[y]!=arr[y])
			pthread_exit((int*)0);
	pthread_exit((int*)1);
}

int main(int argc, char *argv[])
{
	//Check that input argument was entered
	if (argc == 1) {
		fprintf(stderr,"No input argument.");		
		return -1;
	}
	//assign input argument to string
	const char *file_name;
	if(argc==2)
		file_name=argv[1];
	//open and read file
	FILE *sudoku_numbers;
	sudoku_numbers=fopen(file_name,"r");
	//read file into array
	
	int i,j,k;

	if(sudoku_numbers==NULL){
		printf("error Reading File\n");
		exit(0);
	}

	for(i=0;i<9;i++){
		for(j=0;j<9;j++){
			fscanf(sudoku_numbers,"%d",&sudoku_array[i][j]);
		}
	}
	//display the sudoku array
			for(i=0;i<9;i++){
		for(j=0;j<9;j++){
			printf("%d, ",sudoku_array[i][j]);
		}
	}
	printf("\n");
	//assign values to the structures that 
	//are to be passed to the threads
	struct param p[11];
	p[0].row=0;p[0].column=0;//column worker
	p[1].row=0;p[1].column=0;//row worker
	p[2].row=0;p[2].column=0;//subgrid 1
	p[3].row=0;p[3].column=3;//subgrid 2
	p[4].row=0;p[4].column=6;//subgrid 3
	p[5].row=3;p[5].column=0;//subgrid 4
	p[6].row=3;p[6].column=3;//subgrid 5
	p[7].row=3;p[7].column=6;//subgrid 6
	p[8].row=6;p[8].column=0;//subgrid 7
	p[9].row=6;p[9].column=3;//subgrid 8
	p[10].row=6;p[10].column=6;//subgrid 9

	//create threads
	pthread_create(&t[0],NULL,column_worker,&p[0]);
	pthread_create(&t[1],NULL,row_worker,&p[1]);
	pthread_create(&t[2],NULL,subgrid_worker,&p[2]);
	pthread_create(&t[3],NULL,subgrid_worker,&p[3]);
	pthread_create(&t[4],NULL,subgrid_worker,&p[4]);
	pthread_create(&t[5],NULL,subgrid_worker,&p[5]);
	pthread_create(&t[6],NULL,subgrid_worker,&p[6]);
	pthread_create(&t[7],NULL,subgrid_worker,&p[7]);
	pthread_create(&t[8],NULL,subgrid_worker,&p[8]);
	pthread_create(&t[9],NULL,subgrid_worker,&p[9]);
	pthread_create(&t[10],NULL,subgrid_worker,&p[10]);
	//wait for all threads to finish executing before proceeding
	pthread_join(t[0],&final_check[0]);
	pthread_join(t[1],&final_check[1]);
	pthread_join(t[2],&final_check[2]);
	pthread_join(t[3],&final_check[3]);
	pthread_join(t[4],&final_check[4]);
	pthread_join(t[5],&final_check[5]);
	pthread_join(t[6],&final_check[6]);
	pthread_join(t[7],&final_check[7]);
	pthread_join(t[8],&final_check[8]);
	pthread_join(t[9],&final_check[9]);
	pthread_join(t[10],&final_check[10]);
	//display the values of the array that houses the thread returns
	int final_result=1;
	printf("Here are the returns from all the threads:\n");
	for(k=0;k<11;k++){
		printf("%d, ",final_check[k]);
		if(final_check[k]==0)
			final_result=0;
	}
	if(final_result==1)
		printf("\nThe Sudoku solution is valid");
	else
		printf("\nThe Sudoku solution is not valid");

	return 0;
}


