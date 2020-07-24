#pragma once
#include <float.h>
#include "global.h"

#define PRIOR_ERROR INT_MIN
#define POS_ERROR -1

typedef struct
{
	PQINFO* pInfo;
	int nPrior;
} PQItem;

typedef struct
{
	PQItem* pPQueue;
	int nPQSize;
	int nPQCurrSize;
} Pqueue;

Pqueue* PQInit( int size );
int PQisEmpty( Pqueue* Queue );
int PQSize( Pqueue* Queue );
int PGMaxPrior( Pqueue* Queue );
int PQEnqueue( Pqueue* Queue, PQINFO* pInfo, int nPrior );
PQINFO* PQDequeue( Pqueue* Queue );
void PQClear( Pqueue* Queue, void( __cdecl* freeInfo )( const void* ) );
void PQRelease( Pqueue** Queue, void(__cdecl* delItem)(const void*) );
void PQPrint( Pqueue* Queue, void( __cdecl* printInfo )( const void* ), int index );
int PQSetPrior( Pqueue* Queue, int( __cdecl* compareItem )( const void* p, const void* q ), PQINFO* info, int value );
int PQsetPrior( Pqueue* Queue, int index, int value);
int PQGetPrior( Pqueue* Queue, int( __cdecl* compareItem )( const void* p, const void* q ), PQINFO* info );
int PQgetPrior( Pqueue* Queue, int index );
int PQFind( Pqueue* Queue, int( __cdecl* compareItem )( const void* p, const void* q ), PQINFO* info );
