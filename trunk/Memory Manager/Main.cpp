#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <iostream>
#include <vector>

#include "MemoryManager.h"

int main(void)
{
  using namespace MemoryManager;

  initializeMemoryManager();

  srand(1);
  std::vector<char*> m_Memory;
  bool dealloc = true;
  for(int i(0); i < 100000; ++i )
  {
	  dealloc = !dealloc;
	  std::cout<<i<<std::endl;
	  m_Memory.push_back((char*)MemoryManager::allocate( 128 ) );

	  if(dealloc)
	  {

		  MemoryManager::deallocate( (void*)(*m_Memory.begin()) );
		  m_Memory.erase(m_Memory.begin());
	  }
  }

  system("PAUSE");
}

namespace MemoryManager
{

  // Call if a pointer over run condition is detected
  void onOverrunDetected(void)
  {
    std::cerr << "Pointer overrun detected" << std::endl;
    exit( 1 );
  }

  // call for any other error condition, providing meaningful error messages are appreciated
  void onIllegalOperation(const char* fmt,...)
  {
    if ( fmt == NULL )
    {
      std::cerr << "Unknown illegal operation" << std::endl;
      exit( 1 );
    }
    else
    {
      char	buf[8192];

      va_list argptr;
      va_start (argptr,fmt);
      vsprintf (buf,fmt,argptr);
      va_end (argptr);

      std::cerr << "Illegal operation: \"" << buf << "\"" << std::endl;
      exit( 1 );
    }
  }
}

