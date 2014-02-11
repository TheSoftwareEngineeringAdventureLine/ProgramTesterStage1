#include <iostream>
#include <iomanip>
#include <unistd.h>
#include <sys/types.h>
#include <string>
#include <fstream>


#include "mytest.h"

using namespace std;


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
/*
 fout - the output stream to write to.
 numPassed - the number of passed test cases.
 numTest - the total number of test cases
 */

void FinalLogWrite( ofstream & fout, int numPassed, int numTest )
{
  int numFailed;
  numFailed = numTest - numPassed;
  float perPassed;
  perPassed = (float) numPassed/numTest;
  perPassed = perPassed * 100;
  float perFailed;
  perFailed = (float) numFailed/numTest;
  perFailed = perFailed * 100;
 
  
  fout << "Percent of tests Passed: " << setprecision(2)
       << perPassed <<  "%" << endl;
  fout << "Percent of tests failed: " << setprecision(2)
       << perFailed << "%" << endl;
  return;
}
/*
  fout - the output stream to write to.
  testNumber - the number of the test case, i.e. test #1, test #2, etc.
  status - The result of the test, passed or fail
 */
void LogWrite( ofstream & fout, int testNumber, std::string result )
{
  fout << "Test #" << testNumber << ", " << result.c_str() << std::endl;
  return;
  
}
