#include <stdio.h>
#include <stdlib.h>
#define PRINTF 0
#define OFFSET 1.8
#define SCALE 0.5

//prototypes for files.h
//{
int* readFile(int* sampleCount,int* sampleMax,char* filename);
double* offsetFile(int* sampleCount,int* sampleArray, double offset);
double* scaleFile(int* sampleCount,int* sampleArray, double scale);
void printArray(int Count,double* Array);
//}

int main()
{
	int Count, Max;
	char* filename="data_00.txt";

	int* Array;
	Array=readFile(&Count,&Max,filename);
	
	#if (PRINTF>1)
	printf("%d ",Count);
	printf("%d\n",Max);
	#endif

	//printArray(Count,(double*)Array);
	//printf("\n\n");
    printArray(Count,offsetFile(&Count,Array,OFFSET));
    printf("\n");
    printArray(Count,scaleFile(&Count,Array,SCALE));
    printf("\n");
    
	return 0;
	clear(Array);
}
//functions for files.c
//{
int* readFile(int* sampleCount,int* sampleMax,char* filename)
/*	input: 	address to store count
			address to store max value of data
			name of data file
	output: address of array of integer data*/
{
	FILE *fp;
	fp=fopen(filename,"r");

	#if (PRINTF>1)
	printf("1 ");
	#endif

	if(fp==NULL)
	    return NULL;

    #if (PRINTF>1)
	printf("2 ");
	#endif

	fscanf(fp,"%d %d",sampleCount,sampleMax);
	int count=*(sampleCount);

	#if (PRINTF>1)
	printf("3 ");
	#endif

	int* sampleArray;
	sampleArray=malloc(sizeof(int)*count);
	int x=0;

	#if (PRINTF>1)
	printf("4 ");
	#endif

	while(count>0)
	{
		fscanf(fp,"%d", sampleArray+x);
			#if (PRINTF>1)
			printf("%d ",*(sampleArray+x));
			#endif
		x++;
		count--;
	}
	#if (PRINTF>1)
	printf("5\n");
	#endif

	fclose(fp);
	return sampleArray;
}

double* offsetFile(int* sampleCount,int* sampleArray, double offset)
/*	input: 	address of count
			address of array of integer data
			value of offset
	output: address of array of double off-setted data*/
{
	double* offsetArray=malloc(*(sampleCount)*sizeof(double));
	int x=0;
	int count=*(sampleCount);

	while (count>0)
	{
		*(offsetArray+x)=*(sampleArray+x)+offset;
		x++;
		count--;
	}
	return offsetArray;
}

double* scaleFile(int* sampleCount,int* sampleArray, double scale)
/*	input: 	address of count
			address of array of integer data
			value of scale
	output: address of array of double scaled data*/
{
	double* scaleArray=malloc(*(sampleCount)*sizeof(double));
	int x=0;
	int count=*(sampleCount);

	while (count>0)
	{
		*(scaleArray+x)=*(sampleArray+x)*scale;
		x++;
		count--;
	}
	return scaleArray;
}

void printArray(int Count,double* Array)
/*	input: 	value of count
			address of array of double data
	output: displays double data*/
{
   	int x=0;
	while(Count>0)
	{
		printf("%.4f ", (float)*(Array+x));
		x++;
		Count--;
	}
}
//}
