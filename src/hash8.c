/* Hash8.c */
/* Creation, searching, insertion, and deletion in a hash table. */
/* Author: Sonya Goodanetz, July 1999 */
/* Modified: Mark Sattolo, Dec 2000  */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define HASHSIZE 37

// the struct for each node in the hash table
typedef struct hashTableEntry
  {
	long value ;			         /* value in node */
	int hashAddress ;		         /* hash address */
	struct hashTableEntry* next ;	/* next node */
  }
  tableEntry ;

// an array of tableEntry pointers is used as the hash table
static tableEntry* myHashTable[ HASHSIZE ] ;

/* FUNCTION  PROTOTYPES */
	void newEntry		  ( tableEntry* ) ;
	int  addNode		  ( tableEntry* ) ;
	void printWholeTable( void	   	 ) ;
	int  deleteNodes	  ( int			 ) ;


/*********************** MAIN *******************************/

int main( void )
{
  char howMany[ HASHSIZE ] ; // string to store the user response
  unsigned int howManyNodes, i ;
  tableEntry* entryPtr ;

  printf( "Enter as an integer how many nodes you wish to input: " ) ;
  scanf( "%s", &howMany ) ;

  // Error checking for bad input
  for( i=0; i < strlen( howMany ); i++ )
	{
	 if( (howMany[i] < '0') || (howMany[i] > '9') )
	  {
		printf( "\n '%s' is not a proper value! \n", howMany ) ;
		return 0 ;
	  }
	}

  howManyNodes = (unsigned int)atoi( howMany ) ;
  // get the input value for each node
  for( i=1; i <= howManyNodes; i++ )
	{
	 entryPtr = (tableEntry*)malloc( sizeof(tableEntry) ) ; // get memory
	 newEntry( entryPtr ) ;
	 addNode( entryPtr ) ;
	}

  printWholeTable() ;
  deleteNodes( howManyNodes ) ;
  // should delete any remaining nodes before exiting the program
  puts( "\n Goodbye! \n" ) ;
  return 1 ;
}

/************************ FUNCTION DEFINITIONS *******************************/

void newEntry( tableEntry* entryPtr )
// get the integer value and calculate the hash address
{
  char value[ HASHSIZE ] ; // string to store the user response
  unsigned int i, success = 0 ;
  long temp ;

  while( !success )
	{
	 printf( "Enter an integer to put into the hash table: " ) ;
	 scanf( "%s", &value ) ;

	 // Error checking for bad input
	 if( (value[0] < '0') || (value[0] > '9') )
		if( !( (value[0] == '-') && (strlen(value) > 1) ) )
		 {
		  printf( "\n '%s' is not a proper value! \n", value ) ;
		  continue ; // restart the while loop
		 }
	 for( i=1; i < strlen( value ); i++ )
	  {
		if( (value[i] < '0') || (value[i] > '9') )
		 {
		  printf( "\n '%s' is not a proper value! \n", value ) ;
		  break ; // out of the for loop
		 }
		else
			 success = 1 ;
	  }// for( i=1; i < strlen( value ); i++ )

	}// while( !success )

  temp = atol( value ) ;
  entryPtr->value = temp ;
  entryPtr->hashAddress = abs( temp%HASHSIZE ) ;

  printf( "Value: %5ld \t HashValue: %5d \n",
			 entryPtr->value, entryPtr->hashAddress ) ;
}
// newEntry()

/**************************************************/
int addNode( tableEntry* entryPtr )
	/* Search for the proper position and insert the node in the row
		- the linked lists are built and organized in ascending order */
{
  tableEntry *TempPtr,
				 *CurrentPtr = myHashTable[ entryPtr->hashAddress ] ;

  // if no entry in the row or the new entry's value is lt the first node value
  if( (CurrentPtr == NULL) || (entryPtr->value < CurrentPtr->value) )
	{
	 // add the new node at the beginning of the row
	 entryPtr->next = myHashTable[entryPtr->hashAddress] ;
	 myHashTable[entryPtr->hashAddress] = entryPtr ;
	 return 1 ;	// exit the function
	}

  // else, search the row for the proper position
  while( CurrentPtr->next != NULL )
	 {
	  TempPtr = CurrentPtr->next ;
	  // continue until find a node whose value is gte the new node's value
	  if( entryPtr->value < TempPtr->value )
		 break ;  // out of loop
	  CurrentPtr = CurrentPtr->next ;
	 }

  /* add the new node to the current position in the list */
  entryPtr->next = CurrentPtr->next ;
  CurrentPtr->next = entryPtr ;
  return 0 ;
}
// addNode()

/**************************************************************/
void printWholeTable( void )
{
  int index ;
  tableEntry* CurrentPtr ;

  puts( "\n Value\t\t Hash Value " ) ;
  puts(   "-------\t\t------------" ) ;

  for( index = 0; index < HASHSIZE; index++ )
	{
	 // go through each row of the hash table
	 CurrentPtr = myHashTable[index];
	 // print out any rows that contain nodes
	 while( CurrentPtr != NULL )
		{
		 printf( "%5ld \t\t %5d \n", CurrentPtr->value, CurrentPtr->hashAddress ) ;
		 CurrentPtr = CurrentPtr->next ;
		}
	}//for
}
// printWholeTable()

/************************************************************/
int deleteNodes( int numNodes )
{
  char response[ HASHSIZE ] ; // string to store the user response
  long deleteValue ;
  int delAddress, valueInTable ;
  tableEntry *TempPtr,       // pointers to traverse the hash table
				 *CurrentPtr ;

  while( numNodes > 0 ) // continue the loop until all nodes have been deleted
	 {
	  printf( "\n Enter a value to delete from the table ['e' to exit]: " ) ;
	  scanf( "%s", &response ) ;

	  // see if the user wants to exit
	  if( (response[0] == 'E') || (response[0] == 'e') )
		 break ; // out of the while loop
	  else
			if( ((response[0] < '0') || (response[0] > '9')) && (response[0] != '-') )
				{
				 printf( "\n '%s' is not a proper value! \n", response ) ;
				 continue ; //restart the while loop
				}

	  TempPtr = NULL ;   // reset this pointer
	  valueInTable = 0 ; // set default value
	  deleteValue = atol( response ) ;  // convert response to a long
	  delAddress = abs( deleteValue%HASHSIZE ) ; // find the hash address
	  CurrentPtr = myHashTable[delAddress] ;     // set pointer to first node in the row

	  // continue until the end of the row is reached
	  while( CurrentPtr != NULL )
		 {
		  if( CurrentPtr->value == deleteValue )
			// if the first node contains the int value we are searching for
			{
			 if( TempPtr == NULL )   // we are looking at the first entry in the row
				myHashTable[delAddress] = CurrentPtr->next ;
			 else                   // we have used TempPtr to move along the row
				  TempPtr->next = CurrentPtr->next ;

			 free( CurrentPtr ) ;  // delete the node
			 numNodes-- ;  // decrement the number of nodes left in the table

			 printf( "\n DELETED VALUE: %ld \n", deleteValue ) ;
			 valueInTable = 1 ;   // set the boolean indicating the value was found
			 printWholeTable() ;
			 break ;	// out of the inner while loop
			}

		  // else move to the next node in this row
		  TempPtr = CurrentPtr ;
		  CurrentPtr = CurrentPtr->next ;

		 }// while( CurrentPtr != NULL )

	  // print a message if the current value wasn't found
	  if( !valueInTable )
		 printf( "\n Value %ld not found in hash table! \n", deleteValue ) ;

	 }// while( numNodes > 0 )

  if( numNodes == 0 )
	 puts( "\n Table is now empty!" ) ;
  return 0 ;
}
// deleteNodes()

/*********** END OF PROGRAM ************************************/
