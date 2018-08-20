/* =====================================================================
   NAME:- Kushagra Gupta
   Student ID:- 804729
   Subject:- Foundations of Algorithms
   Subject code:- comp10002
  ===================================================================== */
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>


#define MAX_ROWS 1000
#define MAX_COLS 30
#define MAX_CHARS 51

typedef char arr_t[MAX_CHARS];

/****************************************************************/

void f1(arr_t a[MAX_ROWS][MAX_COLS],int row, int col);
void row_swap(arr_t a[MAX_ROWS][MAX_COLS], int r2,int r1,int row,int col);
void arr_sort(arr_t a[MAX_ROWS][MAX_COLS],int row,int col,
	          int arr_argv[],int argc);
void f2(arr_t a[MAX_ROWS][MAX_COLS],int row,int col, int argc, int arr_argv[]);
/*void f3(arr_t a[MAX_ROWS][MAX_COLS],int row,int col,
          int argc, int arr_argv[]);
void distinct_words(arr_t a[MAX_ROWS][MAX_COLS],int row,int col);*/


/****************************************************************/


int main(int argc,char *argv[])
{
	
	arr_t arr[MAX_ROWS][MAX_COLS];  /* arr stores all the data from the 
	tsv file*/
	
	int i=0,j=0,c,t=0,k=0,n=0,*row,*col,arr_argv[argc];
	
	/*array 'arr_argv' stores all the values from the command line except
	for the name of the excutable*/
	
	
	row=&n;/*row points at the address of the counter variable n that counts
	the numbers of rows*/
	
	col=&t;/*row points at the address of the counter variable t that counts
	the numbers of columns*/
	
	/*the while loop iterates over each character of the tsv file and places 
	it in arr and terminates as soon as we reach end of the file*/
	while((c=getchar())!=EOF)
	{
		/*variable 'c' stores each character in the file as the while 
		loop iterates over it*/
		/*'i' takes care of the rows, 'j' the columns, and 'k' the length of 
		the string*/
		if(isalpha(c) || c==' ' || isdigit(c) || c==':')
		{
			arr[i][j][k++]=c;
		}
		/*if it is a tab character we increment the column by 1 and 
		set a null byte at the end of the previous string*/
		else if(c=='\t')
		{
			
			
			arr[i][j][k++]='\0';
			if(i==0)
			{
				t++;
			}
			j++;
			k=0;
			
		}
		/*if it the newline character we increment the rows by 1 and set 'k'
		again to 0 to fill in a new row*/
		else if(c=='\n')
		{
			arr[i][j][k++]='\0';
			j++;
			k=0;
			arr[i][j][k]=c;
			
			
			
			i++;
			k=0;
			j=0;
			n++;
		}
	}
	*col=*col+1;
	*row=*row-1;
	
	printf("Stage 1 Output\n");
	printf("input tsv data has %d rows and %d columns\n",*row,*col); 
	f1(arr,*row,*col); 
	/*print_array(arr,*row,*col);*/

	/*if we have values for sorting of the command line the for loop fills
	in 'arr_argv' with the values*/
	
	if(argc>1)
	{
	for(i=1;i<argc;i++)
	{
		arr_argv[i-1]=atoi(argv[i]);
	}
	f2(arr,*row,*col,argc,arr_argv);
	}
	
	/*f3(arr,*row,*col,argc,arr_argv);*/
	
	return 0;
}


/****************************************************************/



/* this function prints the stage 1 output*/
void f1(arr_t a[MAX_ROWS][MAX_COLS],int row, int col)
{
	/* 'row' contains the row you want to print*/
	printf("row %d is:\n",row);
	int c=1,i; /*c just helps in printing the numeric bullets*/
	for(i=0;i<col;i++)
	{
		printf("%4d:%-10s %s\n",(c++),a[0][i],a[row][i]);
	}
	
}

/****************************************************************/


/*this function swaps two rows*/
void row_swap(arr_t a[MAX_ROWS][MAX_COLS], int r2,int r1,int row,int col)
{
	
	char temp[MAX_CHARS]; 
	int i;
	for(i=0;i<col;i++)
	{
		strcpy(temp,a[r1][i]); 
		strcpy(a[r1][i],a[r2][i]);
		strcpy(a[r2][i],temp);
	}
	
	
}

/****************************************************************/


/*This function sorts the array according to the values given on the
command line using insertion sort*/


/*The code for insertion sorting is taken from 'Programming, problem solving, 
and abstraction with c' by 'Alistair Moffat'*/

void arr_sort(arr_t a[MAX_ROWS][MAX_COLS],int row,int col,
	          int arr_argv[],int argc)
{
	int i,j,c=0;
	
	for(c=argc-2;c>=0;c--)
	{
	
		for(i=2; i<=row; i++)
		{
		
			for(j=i-1; j>0; j--)
			{
			
			    /*if the string at the 'j+1'th row and the concerned column is
				smaller than the string at the 'j'th row and the concerned
				column it swaps the two rows*/
				if(strcmp(a[j+1][(arr_argv[c])-1], a[j][(arr_argv[c])-1])==-1)
				{
					row_swap(a,j+1,j,row,col);
				}
			}
		}
	}
}
	


/****************************************************************/

/*this function prints the stage 2 output*/

void f2(arr_t a[MAX_ROWS][MAX_COLS],int row,int col, int argc, int arr_argv[])
{
	printf("\n");
	printf("Stage 2 Output\n");
	arr_sort(a,row,col,arr_argv,argc);
	f1(a,1,col);
	if(row%2==0)
	{
	f1(a,(row/2),col);
	}
	else
	{
		f1(a,(row/2)+1,col);
	}
	f1(a,row,col);
	
}

/****************************************************************/

/* last two functions are for stage 3 i could not comeplete it and debug it,
please go through them if thats matches the checking criteria, thankyou*/

/*void distinct_words(arr_t a[1000][30],int row,int col)
{
	printf("inside dis_words\n");
	arr_t words[1000][30];
	int i,c,r,j;
	strcpy(words[0][0],a[1][col]);
	c=1;
	for(i=2;i<=row;i++)
	{
		r=0;
		for(j=0;j<c;j++)
		{
			if(strcmp(a[i][col],words[0][j])==0)
			{
				r++;
			}
			
		}
		if(r==0)
		{
			strcpy(words[i][c],a[i][col]);
				c++;
		}	
	}
	print_array(words,0,c);
}

void f3(arr_t a[1000][30],int row,int col, int argc, int arr_argv[])
{
	
	

	printf("inside f3\n");
	char *count="count";
	
	int c,num=5;
	
	for(c=0;c<=argc-2;c++)
	{     
		
		
		if(c==(argc-2))
		{
			
			printf("%-*s ",num,a[0][arr_argv[c]-1]);
			printf("%-*s \n",num,count);
		}
		else
		{
			printf("%-*s \n",num,a[0][arr_argv[c]-1]);
		}
		num+=5;
		
	}
	
	distinct_words(a,row,(arr_argv[1]-1));
	
}*/




/*"algorithms are fun"*/

/* =====================================================================
   Program written by Kushagra Gupta(student id-804729) for comp10002
   assignment-1 
   Prepared September 2016
   ===================================================================== */
   
