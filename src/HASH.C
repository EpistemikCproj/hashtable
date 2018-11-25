/* HASH.C */

/* This C implementation simulates the insertion, deletion and searching of a hash table. */

/* Author: Sonya Goodanetz  July 1999 */

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define HASHSIZE 11

typedef struct hashtable
{
	int value;			/* value in node */
	int hashVal;			/* hash address */
	struct hashtable* next;	/* next node */
}Table;

static Table* Hashtab[HASHSIZE];

void NewEntry(Table *);
Table* searchRow(Table *);
void addNewNodeToStart(Table *);
int findWhereToAdd(Table *);
void PrintWholeTable(void);
int deleteANode(void);

/*********************** MAIN *******************************/

void main()
	{
	int HowManyNodes, i;
	Table *structPtr = NULL;
	puts("Enter as an integer how many nodes you wish to input: ");
	scanf("%d", &HowManyNodes);

	for (i=1; i <= HowManyNodes; i++)
		{
		structPtr = (Table *) malloc(sizeof(*structPtr));
		NewEntry(structPtr);
		findWhereToAdd(structPtr);
		}
	PrintWholeTable();
	deleteANode();
	puts( "\n Goodbye! \n" );
	}

/************************ FUNCTION DEFINITIONS *******************************/

void NewEntry(Table *structPtr)
	{
	int temp;

	puts("Enter an integer value to input into the hash table: ");
	scanf("%d", &temp);
	structPtr->value = temp;
	structPtr->hashVal = temp%HASHSIZE;
	printf( "Value: %5ld \t HashValue: %5ld \n\n", structPtr->value, structPtr->hashVal );
	}

/***************************************************/
Table *searchRow(Table *structPtr)
	/* searches for value in row hashVal that's pointed to by structPtr */
	/* the linked lists are built and organized in ascending order */
	{
	Table *TempPtr = NULL;
	for (TempPtr = Hashtab[structPtr->hashVal]; TempPtr != NULL; TempPtr = TempPtr->next)
		if (TempPtr->value == structPtr->value ) return TempPtr;
	return NULL; 	/* value not found in row hashVal */
	}

/**************************************************/
void addNewNodeToStart(Table *structPtr)
	/* insert  value and hashVal at start of list */
	{
	structPtr->next = Hashtab[structPtr->hashVal];
	Hashtab[structPtr->hashVal] = structPtr;
	}

/**************************************************/
int findWhereToAdd(Table *structPtr)
	{
	Table *TempPtr = NULL, *CurrentPtr = NULL;
	if ((Hashtab[structPtr->hashVal] == NULL)
		|| (Hashtab[structPtr->hashVal]->value >= structPtr->value))
		{
		structPtr->next = Hashtab[structPtr->hashVal];
		Hashtab[structPtr->hashVal] = structPtr;
		return 0;
		}
	CurrentPtr = Hashtab[structPtr->hashVal];
	while (CurrentPtr->next != NULL)
		{
		TempPtr = CurrentPtr->next;
		if (TempPtr->value >= structPtr->value)
			break;
		CurrentPtr = CurrentPtr->next;
		}
	/* add the new node somewhere after the start of the list */
	structPtr->next = CurrentPtr->next;
	CurrentPtr->next = structPtr;
	return 0;
	}

/**************************************************************/
void PrintWholeTable(void)
	{
	int index;
	Table* CurrentPtr = NULL;

	puts("\n Value \t Hashing Value ");
	puts("---------\t---------------");

	for (index=0; index < HASHSIZE; index++)
		{
		CurrentPtr = Hashtab[index];
		while (CurrentPtr != NULL)
			{
			printf("%5d \t\t %5d \n", CurrentPtr->value, CurrentPtr->hashVal);
			CurrentPtr = CurrentPtr->next;
			}
		}
	}

/************************************************************/
int deleteANode(void)
	{
	Table *TempPtr = NULL, *CurrentPtr = NULL;
	int deleteValue, index;

	puts( "\n Now, enter an integer value to delete from the hash table: ");
	scanf("%d", &deleteValue);

	index = deleteValue%HASHSIZE;
	CurrentPtr = Hashtab[index];
	while (CurrentPtr != NULL)
		{
		if (CurrentPtr->value == deleteValue)
			{
			if (TempPtr == NULL)	Hashtab[index] = CurrentPtr->next;
				else TempPtr->next = CurrentPtr->next;
			free (CurrentPtr);
			printf( "\n DELETED VALUE  %ld \n", deleteValue );
			PrintWholeTable();
			return 0;
			}
		TempPtr = CurrentPtr;
		CurrentPtr = CurrentPtr->next;
		}
	printf("\n Value not found in hash table!\n");
	return 0;
	}

/*********** END OF PROGRAM ************************************/
