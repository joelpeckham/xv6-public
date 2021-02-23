//Joel Peckham
//Created Jan 24, 2020
//CP Copies file to specified location.
//Based on cat.c and https://stackoverflow.com/questions/32872767/how-to-create-files-in-the-xv6

#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"

char buf[512];

void
cp(int fd, int fr)
{
  int n;

  while((n = read(fd, buf, sizeof(buf))) > 0) {
    if (write(fr, buf, n) != n) {
      printf(2, "cp: write error\n");
      exit();
    }
  }
  if(n < 0){
    printf(2, "cp: read error\n");
    exit();
  }
}

int
main(int argc, char *argv[])
{
    int fd,fr;

    if(argc < 3){
        printf(2, "cp: Specify source and destination names.\n");
        exit();
    }
    if((fd = open(argv[1], 0)) < 0){
        printf(2, "cp: cannot open %s\n", argv[1]);
        exit();
    }
    if((fr = open(argv[2], O_CREATE | O_RDWR)) < 0){
        printf(2, "error: create file failed\n");
        exit();
    }

    cp(fd,fr);
    close(fd); close(fr);
  exit();
}
