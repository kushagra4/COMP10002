/* =====================================================================
   NAME:- Kushagra Gupta
   Student ID:- 804729
   Subject:- Foundations of Algorithms
   Subject code:- comp10002
  ===================================================================== */

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <assert.h>
#include <string.h>

#define MAX_CHARS 999  //maximum characters in each word
#define MAX_PAIRS  20  //maximum fdt pairs
#define INITIAL    20  //initial size of 'arr'

/*the struct will contain the word in 'word', the number of documents the word
is in 'ft' and the fdt pairs in the 'fdt' array*/
typedef struct
{
	char word[MAX_CHARS];
	int ft, fdt[MAX_PAIRS];
} index_t;

/**************************************************************/

int get_word(FILE *fp, char a[MAX_CHARS],int *spaces,int *n,
	         int *p,index_t **arr);
index_t **read_file(FILE *fp,index_t **arr,int *spaces,int *n,int *p,int *nft);
void stage1(index_t **arr,int p);
int get_word2(char W[MAX_CHARS],int *n_flag);
void stage2(index_t **arr,int p);

/**************************************************************/


int main(int argc, char *argv[])
{
	index_t **arr; //arr is the array of pointers to the sturct 'index_t'
	arr=(index_t**)malloc(INITIAL*sizeof(index_t));
	assert(arr!=NULL);
	FILE *fp;
	int spaces=0,n=0,p=0,nft=0,i=0;  /* p is a counter to number of pointers
	                                 'arr' contains*/
	fp=fopen(argv[1],"r"); /* fp contains a pointer to the file to be
	                           read from the input buffer*/  
	assert(fp!=NULL);
	
	arr=read_file(fp,arr,&spaces,&n,&p,&nft);
	
	printf("Stage 1 Output\n");
	printf("index has %d terms and %d (d,fdt) pairs\n",(p),nft);
	stage1(arr,p);
	
    printf("\n");
    printf("stage 2 output\n");
	stage2(arr,p);
	
	fclose(fp);
	/*the for loop frees all the memory allocated*/
	for(i=0;i<p;i++)
	{
		free(arr[p]);
	}
	free(arr);
	arr=NULL;
	printf("\n");
	printf("Ta da-da-daaah...\n");
	return 0;
	
}



/**************************************************************/


/*This function reads characters from the index file complies it into a word 
and puts it into oneword of read_file function*/

int get_word(FILE *fp, char a[MAX_CHARS],int *spaces,int *n,
			 int *p,index_t **arr)
{

	int i=0;
	char c;
	c=getc(fp);
	
	if(c==EOF)
	{
		return EOF;
	}
	
	/*checks if the character is an alphabet or a number then put its in 'a'*/
	while(c!=' '&& c!='\n' && c!=EOF)
	{
		a[i++]=c;
		c=getc(fp);
	}
	a[i++]='\0';
	
	if(c==' ')
	{
		*spaces=*spaces+1;
	}
	
	else if(c=='\n')
	{
		/*the \n character is treated as a space*/
		*spaces=*spaces+1;
		/*the if checks if the number of fdt pairs are less than or equal to
		10 then puts the number into the 'fdt' array at the spaces-3 position*/
		if(((*spaces)-3)<=MAX_PAIRS)
		{
			arr[(*p)]->fdt[(*spaces)-3]=atoi(a);	
		}
		
		*spaces=0;
		*n=*n+1;
		(*p)++;
	}
	return 0;
}


/**************************************************************/


/*this function reads the index file and places each distinct word
and the information associated with it into a different struct*/

index_t **read_file(FILE *fp,index_t **arr,int *spaces,int *n,int *p,int *nft)
{
	char oneword[MAX_CHARS]; //contains each word read of from the file
	size_t current_size=INITIAL; 

	while(get_word(fp,oneword,spaces,n,p,arr)!=EOF)
	{
		
			/*the if condition checks if the space is equal to one that means
			oneword has the word in it and puts into word of the corresponding 
			struct*/
			if((*spaces)==1)
			{ 
				/*if arr is filled to its capacity then allocate more
				memory to it*/
				if((*p)==current_size)
				{
					current_size *=2;
					arr=realloc(arr, current_size*sizeof(index_t));
					assert(arr!=NULL);
				}
			
				arr[(*p)]=(index_t*)malloc(sizeof(*arr[*p]));
				assert(arr[(*p)]!=NULL);
				strcpy(arr[(*p)]->word,oneword);
			}
		
			else if((*spaces)==2)
			{
				arr[(*p)]->ft=atoi(oneword);
				(*nft)+=atoi(oneword);
			}
		
			else if((*spaces)>2 && ((*spaces)-3)<=MAX_PAIRS)
			{
				/*if the spaces are greater than 2 then it makes every 
				digit on the fdt pair at (space-3) position in the 
				'fdt' array*/
				arr[(*p)]->fdt[(*spaces)-3]=atoi(oneword);
			}
	}
	return arr;
}



/**************************************************************/

/* this function prints out the stage1 1 output*/

void stage1(index_t **arr,int p)
{
	int c=0,i,j,ele=0;// 'c' keeps track of which term is to be printed
	for(i=0;i<=3;i++)
	{
		printf("term %d is \"%s\":\n",c+1,arr[c]->word);
		
		ele=(arr[c]->ft)*2;
		/*keeps a check if the fdt pairs are not greater than 10*/
		if(ele>MAX_PAIRS)
		{
			ele=MAX_PAIRS;
		}
		for(j=0;j<ele;j++)
		{
			if(j==0)
			{
				printf("%5d",arr[c]->fdt[j]);
			
			}
			else
			{
				printf("%d",arr[c]->fdt[j]);
				
			}
			
			if(j%2==0)
			{
				printf(",");
			
			}
			else if(j%2!=0 && j!=ele-1)
			{
				printf("; ");
				
			}
		}
		if(j==MAX_PAIRS)
		{
			printf("; ...");
			
		}
		printf("\n");
		
		c++;
		if(i==1)
		{
			c=p-2;
		}
	}
	
}


/**************************************************************/

/*this functions reads characters from the standard input and complies it into
a word and puts in to oneword for stage2*/


/*The code for get_word2 is taken from 'Programming, problem solving, 
and abstraction with c' by 'Alistair Moffat'*/
int get_word2(char W[MAX_CHARS],int *n_flag) 
{
	
	int c, len=0;
	/* first, skip over any non alphabetics */
	while ((c=getchar())!=EOF && !isalpha(c)) 
	{
		// do nothing
	}
	if (c==EOF) 
	{
		return EOF;
	}
	else
	{
		if((*n_flag)==1)
		{
			*n_flag=2;
		}
	}
	 
	/* ok, first character of next word has been found */
	W[len++] = c;
	while (len<MAX_CHARS && (c=getchar())!=EOF && isalpha(c))
	{
		/* another character to be stored */
		W[len++] = c;
	}
	/* now close off the string */
	W[len] = '\0';
	if(c=='\n' || c==13)
	{
		*n_flag=1;
	}
		
	return 0;
}


/**************************************************************/
/*this function searches for each word using binary search*/

void stage2(index_t **arr,int p)
{
	char oneword[MAX_CHARS];// contains each word that is to be searched for 
	int hi=p-1,lo=0,mid,found=0,n_flag=0;
	while(get_word2(oneword,&n_flag)!=EOF)
	{
		 if(n_flag==2)
		{
			printf("\n");
			printf("stage 2 output\n");
			n_flag=0;
		}
		
		found=0;
		hi=p-1;
		lo=0;
		while(lo<=hi)
		{
			mid=(lo+hi)/2;
			
			if(strcmp(arr[mid]->word,oneword)==0)
			{
				printf("    \"%s\" is term %d\n",oneword,(mid+1));
				found=1;
				break;
				
			}
			    
			/*if the oneword is smaller than the word in the
			middle struct of 'arr' that means if it is in 'arr' it
			is to left of mid*/
			else if(strcmp(oneword,arr[mid]->word)<0)
			{
				hi=mid-1;
				
			}
			/*if the oneword is not smaller than the word in the middle struct 
			of 'arr' and is not even at the middle that means that if it is in 
			'arr' it is to right of mid*/	
			else
			{
				lo=mid+1;
			}
				
		}
      if(!found)
      {
      	  printf("    \"%s\" is not indexed\n",oneword);
      }
    }
}

/* =====================================================================
   Program written by Kushagra Gupta(student id-804729) for comp10002
   assignment-2 
   Prepared October 2016
   ===================================================================== */

