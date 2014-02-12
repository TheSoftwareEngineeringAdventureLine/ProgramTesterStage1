#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>

using namespace std;

bool run_test_case( string test_file, string exec, ofstream log_file )
{
	string out_file = test_file;
	string ans_file = test_file;
	string command_string = "";
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
	system(command_string.c_str());

	//compare the programs output and the expected output
	// diff case.out case.ans      if it == 0 the files were the same
	command_string = "diff " + out_file + " " + ans_file;
	result = system(command_string.c_str());

	//passed test
	if ( result == 0 )
	{
		write_log( test_file, log_file, "passed" );
		return true;
	}
	//failed test
	else
	{
		write_log( test_file, log_file, "failed" );
		return false;
	}
}
