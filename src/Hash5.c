/* HASH5.C */
/* Simulates creation, searching, insertion, and deletion for a hash table. */

/* Author: Sonya Goodanetz  July 1999 */
/* Modified: Mark Sattolo  July 1999, Sept 2000  */

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define HASHSIZE 37

// the struct for each node in the hash table
typedef struct hashTableEntry
  {
	long value ;			         /* value in node */
	int hashAddress ;		         /* hash address */
	struct hashTableEntry* next ;	/* next node */
  }tableEntry ;

// an array of tableEntry structs is used as the hash table
static tableEntry* myHashTable[HASHSIZE] ;

/* FUNCTION  PROTOTYPES */
	void newEntry(tableEntry*) ;
	int addNodeInRow(tableEntry*) ;
	void printWholeTable(void) ;
	int deleteNodes(void) ;

/*********************** MAIN *******************************/

void main()
	{
	int howManyNodes, i, result ;
	tableEntry* entryPtr ;

	puts("Enter as an integer how many nodes you wish to input: ") ;
	scanf("%ld", &howManyNodes) ;

	// get the input value for each node
	for ( i=1; i <= howManyNodes; i++ )
	  {
		entryPtr = (tableEntry*) malloc(sizeof(tableEntry)) ; // get memory
		newEntry(entryPtr) ;
		addNodeInRow(entryPtr) ;
	  }
	printWholeTable() ;
	deleteNodes() ;
	puts( "\n Goodbye! \n" ) ;
	}

/************************ FUNCTION DEFINITIONS *******************************/

void newEntry(tableEntry* entryPtr)
	// get the integer value and calculate the hash address
	{
	long temp ;

	puts("Enter an integer value to input into the hash table: ");
	scanf("%ld", &temp);

	entryPtr->value = temp ;
	entryPtr->hashAddress = abs(temp%HASHSIZE) ;
	printf( "Value: %5ld \t HashValue: %5d \n", entryPtr->value, entryPtr->hashAddress ) ;
	} // newEntry()

/**************************************************/
int addNodeInRow(tableEntry* entryPtr)
	/* Search for the proper position and insert the node in the row
		- the linked lists are built and organized in ascending order */
	{
	tableEntry *TempPtr,
				  *CurrentPtr = myHashTable[entryPtr->hashAddress] ;

	if ( (CurrentPtr == NULL) || (entryPtr->value < CurrentPtr->value) )
	// if no entry in the row or the new entry's value is < the first node value
		{
		// add the new node at the beginning of the row
		entryPtr->next = myHashTable[entryPtr->hashAddress] ;
		myHashTable[entryPtr->hashAddress] = entryPtr ;
		return 1 ;	// exit the function
		}
	// else, search the row for the proper position
	while (CurrentPtr->next != NULL)
		{
		TempPtr = CurrentPtr->next ;

		// continue until find a node whose value is >= the new node's value
		if ( entryPtr->value < TempPtr->value )
			break ;  // out of loop
		CurrentPtr = CurrentPtr->next ;
		}
	/* add the new node to the current position in the list */
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

	for (index = 0; index < HASHSIZE; index++)
		{
		// go through each row of the hash table
		CurrentPtr = myHashTable[index];
		// print out any rows that contain nodes
		while (CurrentPtr != NULL)
			{
			printf("%5ld \t\t %5d \n", CurrentPtr->value, CurrentPtr->hashAddress);
			CurrentPtr = CurrentPtr->next;
			}
		}
	} // printWholeTable()

/************************************************************/
int deleteNodes(void)
 {
  char response[HASHSIZE] ; // string to store the user response
  long deleteValue ;
  int delAddress, valueInTable ;
  tableEntry *TempPtr,       // pointers to traverse the hash table
				 *CurrentPtr ;

  while (1) // continue the loop until break out when input is "E"
	{
	puts( "\n Enter a value to delete from the hash table (E to exit) : " ) ;
	scanf("%s", &response) ;
	// see if the user wants to exit
	if ( !strcmp(response, "E") ) break ; // out of the outer while loop

	TempPtr = NULL ;
	valueInTable = 0 ;   // default value
	deleteValue = atol(response) ;  // convert response to a long
	delAddress = abs(deleteValue%HASHSIZE) ;  // find the hash address
	CurrentPtr = myHashTable[delAddress] ;   // set pointer to first node in the row

	// continue until the end of the row is reached
	while (CurrentPtr != NULL)
		{
		if (CurrentPtr->value == deleteValue)
		// if the first node contains the int value we are searching for
			{
			if (TempPtr == NULL)   // we are looking at the first entry in the row
				myHashTable[delAddress] = CurrentPtr->next ;
			else                   // we have used TempPtr to move along the row
				TempPtr->next = CurrentPtr->next ;
			free (CurrentPtr) ;    // delete the node
			printf( "\n DELETED VALUE: %ld \n", deleteValue ) ;
			valueInTable = 1 ;     // set the boolean indicating the value was found
			printWholeTable() ;
			break ;	// out of the inner while loop
			}
		// else move to the next node in this row
		TempPtr = CurrentPtr ;
		CurrentPtr = CurrentPtr->next ;
		}
		// print a message if the current value wasn't found
		if (!valueInTable)
			printf("\n Value %ld not found in hash table! \n", deleteValue);
  }
  return 0 ;
 } // deleteNodes()

/*********** END OF PROGRAM ************************************/

