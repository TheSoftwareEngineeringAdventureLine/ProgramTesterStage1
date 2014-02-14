#include <fstream>
#include <string>
#include <dirent.h>
#include <iostream>
#include <cstdlib>
#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


/******************************************************************************//**
 * @author Andrew Koc
 * 
 * @Description
 * This function takes two strings, one the directory to a test case file, and
 * the second the directory to an executable program.  It assumes the name and
 * location of the .ans file related to the test file.  The function then makes
 * a system call to run the program piping the input from the .tst file and the
 * output to the .out file.  After this another system command is called
 * that compares the .out file to the .ans file and calls the function to write
 * to the log file with the appropriate data.
 *
 * @param[in] - test_file the directory of the .tst file
 * @param[in] - exec the directory of the executable program to be tested
 * @param[out] - log_file the ofstream to the log file
 *
 * @returns true - the program passed the test
 * @returns false - the program failed the test
 *
 *********************************************************************************/
bool run_test_case( std::string test_file, std::string exec, std::ofstream &log_file )
{
    std::string out_file = test_file;
    std::string ans_file = test_file;
    std::string command_string = "";
    int len;
    int result;

    //get text for .out file and .ans file
    len = out_file.length();
    out_file[len-3] = 'o';
    out_file[len-2] = 'u';
    out_file[len-1] = 't';

    ans_file[len-3] = 'a';
    ans_file[len-2] = 'n';
    ans_file[len-1] = 's';

    //command string = "executable < case.tst > case.out"
    command_string = exec + " < " + test_file + " > " + out_file;
    //execute the program
    std::system(command_string.c_str());

    //compare the programs output and the expected output
    // diff --ignore-all-space case.out case.ans > nul
    //if it == 0 the files were the same
    // the --ignore ignores whitespace on each line, so trailing spaces
    // or newlines aren't flagged as incorrect
    // > pipes the output into a file called nul
    command_string = "diff --ignore-all-space " + out_file + " " + ans_file + " > nul";
    result = std::system(command_string.c_str());

    //passed test
    if ( result == 0 )
    {
        //write_log( test_file, log_file, "passed" );
        return true;
    }
    //failed test
    else
    {
        //write_log( test_file, log_file, "failed" );
        return false;
    }
}

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

/***
 * @author Erik Hattervig
 *
 * @Description
 * A recursive file traversal that gets a root directory and traverses through
 * all sub-directories looking for .tst files. When a tst file is found the
 * function will call for it to be tested
 * 
 * @param[in] rootDir
 * @param[in,out] logFile - a filestream to the logFile so that is passed on
 * to the tester functions
 * @returns none
 ***/
void DirCrawl( std::string rootDir , std::fstream &logFile , std::string root , int &passed , int &tested )
{
	DIR* dir = opendir( rootDir.c_str() );	// Open the directory
	struct dirent* file;	// File entry structure from dirent.h
	std::string filename;	//used in finding if a file has the extention .tst

	// Read each file one at a time
	// Readdir returns next file in the directory, returns null if no other files exist
	while( ( file = readdir(dir)) != NULL )
	{
		//place file name into string filename for easier checking
		filename = file->d_name;

		// skip over the directories "." and ".."
		if ( filename != "." && filename != ".." )
		{
			// checks if the file is a subdirectory, 4 is the integer idetifyer
			// for the dirent struct on Lixux systems
			if ( (int)file->d_type == 4 )
			{
				//moves into the sub-directory
				DirCrawl( rootDir + filename + "/" , logFile , root , passed , tested );
			}
			else
			{
				// checks if the file has a .tst in it. string find returns
				// string::npos if the substring cannot be found
				if ( filename.find( ".tst") != std::string::npos )
				{
					// pass the file onto the grader 
					if (run_test_case( rootDir + '/' + filename , root , logFile ) )
					{
						passed += 1;
					}
					tested += 1;

				}
			}
		}
	}

	closedir(dir);

	return;
}

/******************************************************************************
 *
 *
 *****************************************************************************/
int main( int argc , char** argv )
{
	std::string rootPath;
	char cCurrentPath[FILENAME_MAX];

	getcwd(cCurrentPath , sizeof(cCurrentPath) );

	std::cout << cCurrentPath;
	


	return 0;
}















