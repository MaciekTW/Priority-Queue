#include <stdio.h>
#include <stdlib.h>
#include "global.h"
#include "PQueue.h"

#define SIZE 20
#define LOWPRIORITY 1
#define NORMALPRIORITY 2
#define HIGHPRIORITY 3
#define VERYHIGHPRIORITY 12
#define ZEROPRIORITY 0
#define VERYVERYHIGHPRIORITY 17
#define NEWPRIORITY 20
#define NEWPRIORITY2 5
#define PRINT

int compareItem( const void* p, const void* q );
void printInfo( const void* p );
void freeItem( const void* p );

int main()
{
	PQINFO* item1 = ( PQINFO* )calloc( 2, sizeof( PQINFO ) ); 		item1->pTab = ( int* )calloc( 2, sizeof( int ) );
	PQINFO* item2 = ( PQINFO* )calloc( 2, sizeof( PQINFO ) );		item2->pTab = ( int* )calloc( 2, sizeof( int ) );
	PQINFO* item3 = ( PQINFO* )calloc( 2, sizeof( PQINFO ) );		item3->pTab = ( int* )calloc( 2, sizeof( int ) );
	PQINFO* item4 = ( PQINFO* )calloc( 2, sizeof( PQINFO ) );		item4->pTab = ( int* )calloc( 2, sizeof( int ) );
	PQINFO* item5 = ( PQINFO* )calloc( 2, sizeof( PQINFO ) );		item5->pTab = ( int* )calloc( 2, sizeof( int ) );
	PQINFO* item6 = ( PQINFO* )calloc( 2, sizeof( PQINFO ) );		item6->pTab = ( int* )calloc( 2, sizeof( int ) );
	PQINFO* item7 = ( PQINFO* )calloc( 2, sizeof( PQINFO ) );		item7->pTab = ( int* )calloc( 2, sizeof( int ) );
	PQINFO* item8 = ( PQINFO* )calloc( 2, sizeof( PQINFO ) );		item8->pTab = ( int* )calloc( 2, sizeof( int ) );

	item1->nKey = 6;	item8->nKey = 8;
	item2->nKey = 4;	item7->nKey = 2;
	item3->nKey = 7;	item6->nKey = 1;
	item4->nKey = 9;	item5->nKey = 1;

	Pqueue* Queue = PQInit( SIZE );
	PQEnqueue( Queue, item2, HIGHPRIORITY );
	PQEnqueue( Queue, item5, LOWPRIORITY );
	PQEnqueue( Queue, item3, VERYVERYHIGHPRIORITY );
	PQEnqueue( Queue, item6, ZEROPRIORITY );
	PQEnqueue( Queue, item1, NORMALPRIORITY );
	PQEnqueue( Queue, item4, VERYHIGHPRIORITY );					//Adding 6 new elements

#ifdef PRINT
	PQPrint( Queue, printInfo, 0 );
#endif

	PQDequeue( Queue );												//Deleting element with highest piority
#ifdef PRINT

	printf( "\n" );
	PQPrint( Queue, printInfo, 0 ) ;

#endif

	PQEnqueue( Queue, item7, VERYVERYHIGHPRIORITY );
	PQEnqueue( Queue, item8, ZEROPRIORITY );						//Adding 2 new elements

#ifdef PRINT

	printf( "\n" );
	PQPrint( Queue, printInfo, 0 );

#endif

	PQSetPrior( Queue, compareItem, item5, NEWPRIORITY );			//Increasing the priority of item5

#ifdef PRINT

	printf( "\n" );
	PQPrint( Queue, printInfo, 0 );			

#endif

	PQSetPrior( Queue, compareItem, item1, NEWPRIORITY2 );		//Decreasing the priority of element1

#ifdef PRINT

	printf( "\n" );
	PQPrint( Queue, printInfo, 0 );
	

#endif
	PQRelease( &Queue, freeItem );
}
int compareItem( const void* p, const void* q ) 
{ 
	if ( ( (PQINFO*)p )->nKey > ( (PQINFO*)q )->nKey )
		return 1;
	else if ( ( (PQINFO*)p )->nKey < ( (PQINFO*)q )->nKey )
		return -1;
	return 0;
}
void printInfo( const void* p )
{
	printf( "VALUE: %d ", ( (PQINFO*)p )->nKey );
}
void freeItem( const void* p )
{
	if ( !p )
		return;
	free( ( (PQINFO*)p )->pTab );
	free( (PQINFO*)p );
}