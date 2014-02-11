#include "mytest.h"
#include <time.h>

using namespace std;

int main()
{
  char root[FILENAME_MAX];
  string pass = "Pass";
  string fail = "Fail";

  if( !getcwd( root, sizeof(root) ) )
    {
      std::cout << "Error in getting filepath" << std::endl;
      return 1;
    }
  //std::cout << "The current working directory is: " << root << std::endl;
  
  compil( root,(char *) "hello.cpp");

  srand(time(NULL) );
  
  std::ofstream fout;
  fout.open("Hello.log", std::ofstream::out);
  if( !fout.is_open() )
    {
      std::cout << "Error in opening log file." << std::endl;
    }
  else
    {
      int i = 0;
      int numPassed = 0;
      for ( i = 0; i < 10; i++ )
	{
	  int passFail = rand()%2;
	  if( passFail )
	    {
	      numPassed+=1;
	      LogWrite( fout, i+1, pass );
	    }
	  else
	    LogWrite( fout, i+1, fail );

	}
      FinalLogWrite( fout, numPassed, i+1);
    }
  
  return 0;
}
