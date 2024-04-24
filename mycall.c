#include "types.h"
#include "stat.h"
#include "user.h"

int
main(int argc, char **argv)
{
  int i;

  if(argc < 2){
    printf(2, "usage: mycall pid...\n");
    exit();
  }
  for(i=1; i<argc; i++){
    int res = mycall(atoi(argv[i]));
    printf(2,"return: %d", res);
  }
    
  exit();
}