#include <iostream>
#include <iomanip>
#include <unistd.h>
#include <sys/types.h>
#include <string>
#include "mytest.h"
/*
Compiles the specified program to a.out
*/
void compil(  char * root, char * progName )
{

  //File path to g++
  char * GPlusPlus = "/bin/g++";

  //Create the argument to send to g++
  std::string progPath;
  progPath += root;
  progPath += "/";
  progPath += progName;
  char * arg1 = new char[ progPath.length() + 1];
  strcpy( arg1, progPath.c_str() );
  
  //Create the argument list.
  char * argsv[] = { GPlusPlus, arg1, 0};

  //Fork off and compile the program.
  pid_t pid;
  if( ( pid = fork() ) == -1)
    {
      perror("fork error");
    }
  else if( pid == 0 )
    {
      execv( GPlusPlus, argsv );
      std::cout << "Return not expected. Must be an execv error.n" << std::endl;
    }

  delete arg1;
  return;
}
