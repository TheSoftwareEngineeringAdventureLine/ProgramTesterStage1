#include "mytest.h"

int main()
{
  char root[FILENAME_MAX];

  if( !getcwd( root, sizeof(root) ) )
    {
      std::cout << "Error in getting filepath" << std::endl;
      return 1;
    }
  //std::cout << "The current working directory is: " << root << std::endl;
  
  compil( root,(char *) "hello.cpp");
  return 0;
}
