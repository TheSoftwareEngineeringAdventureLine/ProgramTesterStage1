#include "run_test_case.h"

using namespace std;

//just a simple test function
void write_log( string test_file, ofstream &log_file, string result )
{
    log_file << test_file << " " << result << endl;
}


int main()
{
    ofstream log;
    string test_case = "case1.tst";
    string prgm = "a.out";

    log.open("log.txt");
    if (!log)
        return 0;
    run_test_case(test_case, prgm, log);
    return 0;
}
