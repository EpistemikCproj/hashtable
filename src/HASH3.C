/* HASH3.C */

/* Simulates the insertion, deletion and searching of a hash table. */

/* Author: Sonya Goodanetz  July 1999 */
/* Modified: Mark Sattolo  July 1999, Sept 2000  */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define HASHSIZE 29

typedef struct hashTableEntry
  {
	long value ;			         /* value in node */
	int hashAddress ;		         /* hash address */
	struct hashTableEntry* next ;	/* next node */
  }tableEntry ;

static tableEntry* myHashTable[HASHSIZE] ;

/* FUNCTION  PROTOTYPES */

	 void newEntry(tableEntry*) ;
	 int searchRow(tableEntry*) ;
	 void addNodeToStart(tableEntry*) ;
	 int addNodeInRow(tableEntry*) ;
	 void printWholeTable(void) ;
	 int deleteNode(void) ;

/*********************** MAIN *******************************/

void main()
	{
	int howManyNodes, i, result ;
	tableEntry* entryPtr ;

	puts("Enter as an integer how many nodes you wish to input: ") ;
	scanf("%ld", &howManyNodes) ;

	for ( i=1; i <= howManyNodes; i++ )
	  {
		entryPtr = (tableEntry*) malloc(sizeof(tableEntry)) ;
		newEntry(entryPtr) ;
		result = searchRow(entryPtr) ;
		if (result == 0) addNodeToStart(entryPtr) ;
			else addNodeInRow(entryPtr) ;
		printWholeTable() ;
	  }
	deleteNode() ;
	puts( "\n Goodbye! \n" ) ;
	}

/************************ FUNCTION DEFINITIONS *******************************/

void newEntry(tableEntry* entryPtr)
	{
	long temp ;

	puts("Enter an integer value to input into the hash table: ");
	scanf("%ld", &temp);

	entryPtr->value = temp ;
	entryPtr->hashAddress = abs(temp%HASHSIZE) ;
	printf( "Value: %5ld \t HashValue: %5d \n\n", entryPtr->value, entryPtr->hashAddress ) ;
	} // newEntry()

/***************************************************/
int searchRow(tableEntry* entryPtr)
	/* searches for value in row hashAddress that's pointed to by entryPtr */
	/* the linked lists are built and organized in ascending order */
	{
	tableEntry* TempPtr ;

	for (TempPtr = myHashTable[entryPtr->hashAddress]; TempPtr != NULL; TempPtr = TempPtr->next)
		if (TempPtr->value == entryPtr->value )
			return 1 ; // value found in row hashAddress

	return 0 ; 	/* value not found in row hashAddress */
	} // searchRow()

/**************************************************/
void addNodeToStart(tableEntry* entryPtr)
	/* insert value and hashAddress at start of row */
	{
	entryPtr->next = myHashTable[entryPtr->hashAddress] ;
	myHashTable[entryPtr->hashAddress] = entryPtr ;
	} // addNewNodeToStart()

/**************************************************/
int addNodeInRow(tableEntry* entryPtr)
	/* Search for the proper position and insert the node in the row */
	{
	tableEntry *TempPtr,
				  *CurrentPtr = myHashTable[entryPtr->hashAddress] ;

	if ( (CurrentPtr == NULL) || (CurrentPtr->value >= entryPtr->value) )
		{
		addNodeToStart(entryPtr) ;
		return 1 ;		// return to exit the function
		}

	while (CurrentPtr->next != NULL)
		{
		TempPtr = CurrentPtr->next ;
		if ( TempPtr->value  >=  entryPtr->value )
			break ;  // out of loop
		CurrentPtr = CurrentPtr->next ;
		}
	/* add the new node somewhere after the start of the list */
	entryPtr->next = CurrentPtr->next ;
	CurrentPtr->next = entryPtr ;
	return 0 ;
	} // findWhereToAdd()

/**************************************************************/
void printWholeTable(void)
	{
	int index ;
	tableEntry* CurrentPtr ;

	puts("\n Value         Hash Value ");
	puts("---------   ---------------");

	for (index = 0; index< HASHSIZE; index++)
		{
		CurrentPtr = myHashTable[index];
		while (CurrentPtr != NULL)
			{
			printf("%5ld \t\t %5d \n", CurrentPtr->value, CurrentPtr->hashAddress);
			CurrentPtr = CurrentPtr->next;
			}
		}
	} // printWholeTable()

/************************************************************/
int deleteNode(void)
	{
	long deleteValue ;
	int index ;
	tableEntry *TempPtr = NULL,
				  *CurrentPtr ;

	puts( "\n Enter a value to delete from the hash table: " ) ;
	scanf("%ld", &deleteValue) ;
	index = abs(deleteValue%HASHSIZE) ;
	CurrentPtr = myHashTable[index] ;

	while (CurrentPtr != NULL)
		{
		if (CurrentPtr->value == deleteValue)
			{
			if (TempPtr == NULL)
				myHashTable[index] = CurrentPtr->next ;
			else
				TempPtr->next = CurrentPtr->next ;
			free (CurrentPtr) ;
			printf( "\n DELETED VALUE: %ld \n", deleteValue ) ;
			printWholeTable() ;
			return 0 ;	// this return is necessary to break out of the function
			}
		TempPtr = CurrentPtr ;
		CurrentPtr = CurrentPtr->next ;
		}
	printf("\n Value %ld not found in hash table! \n", deleteValue) ;
	return 0 ;
	} // deleteNode()

/*********** END OF PROGRAM ************************************/
