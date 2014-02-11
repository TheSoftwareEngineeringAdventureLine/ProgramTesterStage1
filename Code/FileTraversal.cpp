

#include <fstream>
#include <string>
#include <dirent.h>
#include <iostream>

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
void DirCrawl( std::string rootDir , std::fstream &logFile )
{
	DIR* dir = opendir( rootDir.c_str() );	// Open the directory
	struct dirent* file;	// File entry structure from dirent.h
	std::string filename;	//used in finding if a file has the extention .tst

	// Read each file one at a time
	while( ( file = readdir(dir)) != NULL )
	{
		//place file name into string filename for easier checking
		filename = file->d_name;

		// skip over the directories "." and ".."
		if ( filename != "." && filename != ".." )
		{
			// checks if the file is a subdirectory, 16384 is the integer idetifyer
			// for the dirent struct
			if ( file->d_type == 16384 )
			{
				//Debuging purposes ####################################
				std::cout << "Moving to subdir: " << filename << "\n\n";
				// #####################################################

				//moves into the sub-directory
				DirCrawl( rootDir + filename + '\\' , logFile );

				//Debuging purposes #################################
				std::cout << "Exiting subdir " << filename << "\n\n";
				// ##################################################
			}
			else
			{
				//Debuging purposes ###############
				std::cout << filename << std::endl;
				// ################################

				// checks if the file has a .tst in it. string find returns
				// string::npos if the substring cannot be found
				if ( filename.find( ".tst") != std::string::npos )
				{
					// pass the file onto the grader
					// <-------------------------------------------- function goes here

					//Debuging purposes ################################################
					std::cout << filename << " <============= found .tst " << std::endl;
					// #################################################################
				}
			}
		}
	}

	closedir(dir);

	return;
}

/**
 * Currently for Debugging purposes only
 **/
int main()
{
	std::fstream logFile;

	DirCrawl( "c:\\users\\erik\\dropbox\\school stuff\\software engineering\\programgrader\\programgrader\\" , logFile );


	return 0;
}