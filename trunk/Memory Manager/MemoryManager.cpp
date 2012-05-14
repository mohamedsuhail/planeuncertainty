#include "MemoryManager.h"
#include <string.h>
#include <iostream>


namespace MemoryManager
{
	const unsigned int MM_POOL_SIZE = 65535;
	const unsigned int MM_POOL_NUM = 10;
	char MM_pool[MM_POOL_NUM][MM_POOL_SIZE];

	struct Head
	{
		bool free;
		unsigned int chunkSize;
		Head(size_t size):
		free(true),chunkSize(size) {}
	};
	// Initialize set up any data needed to manage the memory pool
	void initializeMemoryManager(void)
	{
		for( int i(0); i < MM_POOL_NUM; ++i )
		{
			memset(&MM_pool[i][0],0,MM_POOL_SIZE);
			Head first(MM_POOL_SIZE-sizeof(Head));
			memcpy(&MM_pool[i][0],&first,sizeof(Head));
		}

	}



	// return a pointer inside the memory pool
	// If no chunk can accommodate aSize call onOutOfMemory()
	void* allocate(unsigned int aSize, bool bAllowUnfragmentation )
	{
		//First fit method
		for( int j(0); j < MM_POOL_NUM; ++j )
		{
			for(int i=0;i<MM_POOL_SIZE;/*NOTHING*/)
			{	
				Head* iter = (Head*)&MM_pool[j][i];
				//if we have reached a free chunk and have enough memory to satisfy the request
				if(iter->free&&iter->chunkSize>=aSize)
				{
					//set the header to being used
					iter->free=false;
					//if the chunk size is bigger than the required size and the size of the new head
					if(iter->chunkSize>aSize+sizeof(Head))
					{
						//create a new head at the end of the chunk and set its chunk size
						Head nextHead(iter->chunkSize-aSize-sizeof(Head));
						//copy it into position at the end of the chunk
						memcpy(&MM_pool[j][i+aSize+sizeof(Head)],&nextHead,sizeof(Head));
						//resize the current headers chunk to match the requested memory
						iter->chunkSize=aSize;
					}
					//return a reference to the start of the chunk
					return &MM_pool[j][i+sizeof(Head)];
				}
				else
				{
					//move i along to the next head
					i+=iter->chunkSize+sizeof(Head);
				}
			}
		}
		if( bAllowUnfragmentation )
		{
			unfragment();
			return allocate( aSize, false );
		}
		
		onOutOfMemory( aSize );
	}



	// Free up a chunk previously allocated
	void deallocate(void* aPointer)
	{
		Head* start = (Head*)((char*)aPointer-sizeof(Head));
		start->free=true;
		Head* next = (Head*)((char*)aPointer+sizeof(Head)+start->chunkSize);
	}

	//---
	//--- support routines
	//--- 

	void unfragment()
	{
		for( int j(0); j < MM_POOL_NUM; ++j )
		{
			int i=0;
			while(i<MM_POOL_SIZE)
			{	
				Head* iter = (Head*)&MM_pool[j][i];
				Head* next = (Head*)&MM_pool[j][i+iter->chunkSize+sizeof(Head)];
				if(iter->free&&next->free)
				{
					iter->chunkSize+=next->chunkSize+sizeof(Head);
					memset(next,0,sizeof(Head));
				}
				i+=iter->chunkSize+sizeof(Head);
			}
		}

	}

	// Will scan the memory pool and return the total free space remaining
	int freeRemaining(void)
	{
		unfragment();
		int total=0;
		for( int j(0); j < MM_POOL_NUM; ++j )
		{
			for(int i=0;i<MM_POOL_SIZE;/*NOTHING*/)
			{
				Head* iter = (Head*)&MM_pool[j][i];
				if(iter->free)
				{
					total+=iter->chunkSize;
				}
				i+=iter->chunkSize+sizeof(Head);
			}
		}


		return total;
	}

	// Will scan the memory pool and return the largest free space remaining
	int largestFree(void)
	{
		unfragment();
		int largest=0;
		for( int j(0); j < MM_POOL_NUM; ++j )
		{
			for(int i=0;i<MM_POOL_SIZE;/*NOTHING*/)
			{
				Head* iter = (Head*)&MM_pool[j][i];
				if(iter->free&&iter->chunkSize>largest)
				{
					largest = iter->chunkSize;
				}
				i+=iter->chunkSize+sizeof(Head);
			}
		}


		return largest;
	}

	// will scan the memory pool and return the smallest free space remaining
	int smallestFree(void)
	{
		unfragment();
		int smallest = MM_POOL_SIZE;
		for( int j(0); j < MM_POOL_NUM; ++j )
		{
			for(int i=0;i<MM_POOL_SIZE;/*NOTHING*/)
			{
				Head* iter = (Head*)&MM_pool[j][i];
				if(iter->free&&iter->chunkSize<smallest)
				{
					smallest = iter->chunkSize;
				}
				i+=iter->chunkSize+sizeof(Head);
			}
		}

		return smallest;
	}

	void onOutOfMemory( unsigned int uiSize )
	{
		std::cout<< "Allocation:" << uiSize <<  " Largest:"<< MemoryManager::largestFree() << " Smallest:" << MemoryManager::smallestFree() << "Remaining: " << MemoryManager::freeRemaining() << std::endl;
		std::cerr << "Memory pool out of memory" << std::endl;
		system("PAUSE");
		exit( 1 );
	}
}