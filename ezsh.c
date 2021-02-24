//Joel Peckham
//Created Feb 14, 2020 (Valentine's Day programming. Hot, right.)
//ezsh.c
//Supports 300 char commands with up to 50 args.

#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"


int tokenizeLine(char * line, int lineSize , char ** argBuffer, int argBufferSize){
    if (line[0] == '\n') {argBuffer[0] = 0; return 0;} //Terminate argBuffer and return;
    argBuffer[0] = line;
    int argCount = 1;
    for(int i = 0; line[i] != '\0' && i < lineSize - 1; i++){
        // printf(1,"Char: %d\n", line[i]);
        if (line[i] == ' ' && argCount < argBufferSize){
            line[i] = '\0';
            argBuffer[argCount++] = &line[i+1];
        }
    }
    argBuffer[argCount] = 0; //Terminate argBuffer
    return argCount;
}

// Gets line from std input.
char* getLine(char * buf, int max){
    int i, cc;
    char c;
    for(i=0; i+1 < max;){
        cc = read(0, &c, 1);
        if(cc < 1 || c == '\n' || c == '\r') break;
        buf[i++] = c;
    }
    buf[i] = '\0'; //terminate string
    return buf;
}


// This must be done in the shell because 
// if it were done by another process, chdir() would
// change the working directory of that child process instead.
void changeDirectory(char ** argv, int argc){
    if(chdir(argv[1]) < 0)
        printf(2, "cannot cd %s\n", argv[1]);
}

void execCommand(char *command, char ** argv, int argc){
    if (fork() == 0){
        exec(command,argv);
    }
    else{
        if(argv[argc-1][0] != '&'){
            wait();
        }
    }
}

void readHistory(int lineNumber, char* commandBuffer, int promptNumber){
    memset(commandBuffer, 0, 300);
    int fd;
    if((fd = open("/.ezshHistory", 0)) < 0){
      printf(1, "Cannot open %s\n", "/.ezshHistory");
      return;
    }
    int linesRead = 0;
    if (lineNumber <= promptNumber && lineNumber >= 0){
        while(linesRead++ <= lineNumber && read(fd, commandBuffer, 300) > 0);
    }
    else{
        printf(1,"Command #%d out of history range\n",lineNumber);
    }
    close(fd);
    return;
}

void writeHistory(char* line){
    int fd;
    if((fd = open("/.ezshHistory", O_RDWR|O_CREATE)) < 0){
      printf(1, "Cannot open %s\n", "/.ezshHistory");
      return;
    }
    char trashLine[300];
    while(read(fd,trashLine,300 > 0));
    char cr[1] = "\n";
    write(fd,line,299);
    write(fd,cr,1);
    close(fd);
    return;
}

int main (void){
    int bufferSize = 300; char buffer[bufferSize];
    int argBufferSize = 50; char* argBuffer[argBufferSize];
    int promptNumber = 0;

    while(1){
        memset(buffer, 0, bufferSize);
        memset(argBuffer, 0, argBufferSize);

        printf(1,"%d EZ$ ",promptNumber++);
        
        getLine(buffer, bufferSize);

        if(buffer[0] == 0) {printf(1,"\n"); break;} //EOF

        writeHistory(buffer);

        if(buffer[0] == '#'){
            readHistory(atoi(&buffer[1]),buffer,promptNumber);
        }

        int argc = tokenizeLine(buffer, bufferSize, argBuffer, argBufferSize);
        char ** argv = argBuffer;
        char* command = argv[0];
        if (command[0] == 'c' && command[1] == 'd'){
            changeDirectory(argv,argc);
        }
        else{
            execCommand(command,argv,argc);
        }
    }
    unlink("/.ezshHistory");
    exit();
}
