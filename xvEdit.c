#include "types.h"
#include "user.h"
#include "fcntl.h"

typedef struct Line{
    char* text, prev, next;
    int size;
} Line;

Line CreateLine(void){
    Line l;
    l.text = "\0";
    l.prev = l.next = '\0'; l.size = 0;
    return l;
}

// typedef struct LineList{
//     char* head, tail; 
//     int size;
// } LineList;

// Gets line from std input.
// char* gets(){
//     char buf[80];
//     int i, cc; char c;
//     for(i=0; i+1 < sizeof(buf);){
//         cc = read(0, &c, 1);
//         if(cc < 1 || c == '\n' || c == '\r') break;
//         buf[i++] = c;
//     }
//     buf[i] = '\0'; //terminate string
//     return buf;
// }

line getInput(Line l){
    char* start = &l.text[l.size];
    char buf[80];
    
}

int main (void){
    // Line line = CreateLine()

    printf(1,"Welcome to xvEdit!\n");
    exit(); return 0;
}

