//Joel Peckham
//Created Jan 24, 2020
//Small program that says "Hello!" to the specified command-line-argument provided name.

#include "types.h"
#include "stat.h"
#include "user.h"

char buf[512];

int main(int argc, char *argv[])
{
  //Check if there is a name to greet.
  if(argc != 2){
    printf(1, "greet: Provide a name to greet. Usage: \"greet Jack\".\n");
    exit();
  }

  //Print hello and specified name
  printf(1, "Hello, %s!\n", argv[1]);    

  exit();
}
