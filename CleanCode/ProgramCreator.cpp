#include <iostream>
#include <iomanip>
#include <unistd.h>
#include <sys/types.h>
#include <string>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>

#include "mytest.h"

/****
 * @author Jonathan Tomes
 * 
 * @Description
 * A simple funciton that compiles the program, given by progname
 * in the form of a .cpp file, with g++ to default compiled program
 * a.out. The source code should be in the directory provided
 * by root.
 * 
 * @parm[in] root - directory to find the program.
 * @pram[in] progName - The name of the .cpp file for the source code.
 *                      (should include .cpp at the end.)
 *
 * @returns none
 ****/

void Compil(  char * root, char * progName )
{
  //Create the argument to send to g++
  std::string progPath;
  progPath += root;
  progPath += "/";
  progPath += progName;
  //creat the system command and execute it.
  std::string command;
  command = "g++ " + progPath;
  system( command.c_str() );
 
  return;
}
/****
 *@Author Jonathan Tomes
 *
 *@Description
 *A function to right the final results of testing to a
 * log file, with the given ofstream.
 *
 *@param[in] fout - the output stream to write to.
 *@param[in] numPassed - the number of passed test cases.
 *@param[in] numTest - the total number of test cases.
 *
 *@returns none
 ****/

void FinalLogWrite( std::ofstream & fout, int numPassed, int numTest )
{
  //Calculate the number of tests failed.
  int numFailed;
  numFailed = numTest - numPassed;
  //Calculate the percent passed.
  float perPassed;
  perPassed = (float) numPassed/numTest;
  perPassed = perPassed * 100;
  //Calculate the percent failed.
  float perFailed;
  perFailed = (float) numFailed/numTest;
  perFailed = perFailed * 100;
 
  //Write to stream.
  fout << "Percent of tests Passed: " << setprecision(2)
       << perPassed <<  "%" << std::endl;
  fout << "Percent of tests failed: " << setprecision(2)
       << perFailed << "%" << std::endl;
  return;
}
/****
 *@author Jonathan Tomes
 *
 *@description
 *A function to write the results of a test case
 * to the given file stream. 
 *
 *@param[in] fout - the output stream to write to.
 *@param[in] testNumber - the number of the test case, i.e. test #1, test #2, etc.
 *@param[in] status - The result of the test, passed or fail
 *
 *@returns none
 ****/
void LogWrite( std::ofstream & fout, int testNumber, std::string result )
{
  fout << "Test #" << testNumber << ", " << result.c_str() << std::endl;
  return;
  
}
