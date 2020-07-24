#include "PQueue.h"
#include <stdio.h>
#include <stdlib.h>

#define ARRAYSIZE 2

void UpdateUp( PQItem* Queue, int l, int p );
void UpdateDown( PQItem* pQueue, int l, int p );

Pqueue* PQInit( int size )
{
	if ( size < 1 )
		return NULL;
	Pqueue* Queue = ( Pqueue* )calloc( 1, sizeof( Pqueue ) );
	if ( !Queue )
		return NULL;

	Queue->nPQSize = size;

	Queue->pPQueue = (PQItem*)calloc( size, sizeof( PQItem ) );

	if ( !Queue->pPQueue )
		return NULL;

	return Queue;
}

int PQisEmpty( Pqueue* Queue )
{
	return !Queue || !Queue->nPQCurrSize;
}
int PQSize( Pqueue* Queue )
{
	 return ( Queue ) ? Queue->nPQCurrSize : PRIOR_ERROR;
}
int PGMaxPrior( Pqueue* Queue )
{
	return  ( Queue && !PQisEmpty( Queue ) ) ? Queue->pPQueue[0].nPrior : PRIOR_ERROR;
}
int PQEnqueue( Pqueue* Queue, PQINFO* pInfo, int nPrior )
{
	
	if ( !Queue )
		return 0;

	int size = PQSize(Queue);

	if ( size == Queue->nPQSize )
		return 0;

	Queue->pPQueue[ size ].nPrior = nPrior;
	Queue->pPQueue[ size ].pInfo = pInfo;


	if( !PQisEmpty( Queue ) )
		UpdateUp( Queue->pPQueue, 0, size );

	Queue->nPQCurrSize++;
	return 1;
}
int PQFind( Pqueue* Queue, int(__cdecl* compareItem)( const void* p, const void* q ), PQINFO* info )
{
	if ( !Queue || !compareItem )
		return PRIOR_ERROR;
	for ( int i = 0; i < PQSize( Queue ); i++ )
	{
		if ( !compareItem( info, Queue->pPQueue[ i ].pInfo ) )
			return i;
	}
	return POS_ERROR;
}
int PQsetPrior( Pqueue* Queue, int index, int value )
{
	if ( !Queue )
		return 0;

	int temp = PQgetPrior(Queue, index);

	if ( temp != PRIOR_ERROR && temp != POS_ERROR )
	{
		Queue->pPQueue[index].nPrior = value;

		if ( value > temp )
			UpdateUp( Queue->pPQueue, 0, index );
		else
			UpdateDown( Queue->pPQueue, index, PQSize( Queue ) );
	
	}
	return temp;
}
int PQSetPrior( Pqueue* Queue, int(__cdecl* compareItem)( const void* p, const void* q ), PQINFO* info, int value )
{
	return PQsetPrior( Queue, PQFind( Queue, compareItem, info ), value );
}
int PQgetPrior( Pqueue* Queue, int index )
{
	if ( !Queue || PQisEmpty( Queue ) )
		return PRIOR_ERROR;
	if ( index < 0 || index > PQSize( Queue ) )
		return POS_ERROR;

	return Queue->pPQueue[ index ].nPrior;
}
int PQGetPrior( Pqueue* Queue, int(__cdecl* compareItem)( const void* p, const void* q ), PQINFO* info )
{
	return PQgetPrior( Queue, PQFind( Queue, compareItem, info ) );
}
PQINFO* PQDequeue( Pqueue* Queue )
{
	if ( !Queue )
		return NULL;
	if ( PQisEmpty( Queue ) )
		return NULL;

	int ix = --Queue->nPQCurrSize;

	PQINFO* temp = Queue->pPQueue[0].pInfo;

	Queue->pPQueue[ 0 ] = Queue->pPQueue[ ix ];
	Queue->pPQueue[ ix ].nPrior = 0;
	Queue->pPQueue[ ix ].pInfo = 0;


	if( ix != 0 )
		UpdateDown( Queue->pPQueue, 0, ix - 1 );

	return temp;
}
void PQPrint( Pqueue* Queue, void(__cdecl* printInfo)(const void*), int index )
{
	if ( !Queue || PQisEmpty( Queue ) )
	{
		perror( "ERROR OCCURRED" );
		return;
	}
	if ( index >= PQSize( Queue ) )  return;

	if ( printInfo )
		printInfo( Queue->pPQueue[index].pInfo );

	printf( "POS: [%d] PRIOR: (%d) \n", index, Queue->pPQueue[index].nPrior );
	PQPrint( Queue, printInfo, index * 2 + 1 );
	PQPrint( Queue, printInfo, index * 2 + 2 );
}
void PQRelease( Pqueue** Queue, void(__cdecl* delItem)( const void* ) )
{
	if ( !Queue || !(*Queue) )
	{
		perror( "ERROR OCCURRED" );
		return;
	}
	PQClear( *Queue, delItem );
	free( ( *Queue )->pPQueue );
	free( *Queue );
	*Queue = NULL;
}
void PQClear( Pqueue* Queue, void(__cdecl* freeInfo)( const void* ) )
{
	if ( !Queue || !freeInfo )
	{
		perror( "ERROR OCCURRED" );
		return;
	}
	while ( !( PQisEmpty( Queue ) ) )
		freeInfo( PQDequeue( Queue ) );
}
void UpdateUp( PQItem* Queue, int l, int p )
{
	if ( l >= p ) return;

	int i = p;
	int j =  ( i - 1 ) / 2;

	PQItem temp = Queue[i];

	while ( j >= l && Queue[j].nPrior < temp.nPrior )
	{
		Queue[i] = Queue[j];
		i = j;
		j = ( i + 1 ) / 2 - 1;
	}
	Queue[i] = temp;
}
void UpdateDown( PQItem* Queue, int l, int p )
{
	if ( l >= p ) return;
	int i = l;
	int j = 2 * i +1 ; 

	PQItem temp = Queue[i];

	while( j<=p )
	{
		if ( j < p )
			if ( Queue[j].nPrior <= Queue[j + 1].nPrior ) j++;
		if ( Queue[j].nPrior <= temp.nPrior )
			break;
		Queue[i] = Queue[j];
		i = j;
		j = 2 * i +1;
	}
	Queue[i] = temp;
}