#include <stdio.h>
#include <getopt.h>
#include <stdlib.h> 

typedef struct options{
    int b;
    int e;
    int n;
    int s;
    int t;
    int v;
}opt;



void parser(int argc, char *argv[],  opt* options) {
int opt = 0;
int option_index = 0;

static struct option long_option[] = {
    {"number-nonblank",0,0,'b'},
     {"squeeze",0,0,'s'},
     {"number",0,0,'n'}
};

while ((opt = getopt_long(argc, argv,"+benstvTE", long_option, &option_index)) != -1) {
   
switch (opt)
{
case 'b':
   options -> b = 1;
    options -> n = 0;
    break;
case 'n':
   options -> n = 1;
    break;
case 'E':
   options -> n = 1;
    break;
case 's':
   options -> s = 1;
    break;
case 't':
   options -> t = 1;
   options -> v = 1;
    break;
case 'v':
   options -> v = 1;
    break;
case 'e':
   options -> e = 1;
   options -> v = 1;
    break;
case 'T':
   options -> t = 1;
    break;
default:    
    fprintf(stderr, "cat: illegal option -- %c \nusage: cat [-benstvTE] [file ...]", opt);
    exit (1);
}
}
}

void reader(char *argv[], opt* options, int argc) {
 for( int  argvCounter = 1; argvCounter < argc; argvCounter++, optind++) {
    int next = '\n';
FILE * f = fopen(argv[optind], "r");

if (f) {
int temp = 0;
int cur = 0;
int strCounter = 0;
// int counter = 0;

while((cur = fgetc(f)) != EOF) {
     if (options -> s) {

     while (cur == '\n' && next == '\n' && temp == '\n') { 
       cur = fgetc(f);
       
     } if (cur == EOF) {
        break;
     }
 } if (options -> b) { 
        if (cur != '\n' && next == '\n') {
           printf("%6d\t", ++strCounter);
    }
 } if (options -> n && (options -> b != 1)) { 
       if( next == '\n') {
        printf("%6d\t", ++strCounter);
    }  
        }   if (options -> v) {
        if (cur < 32 && cur != 10 && cur != 9 && cur != '\t' && cur != '\n') { 
         printf("^%c", cur+64); 
         cur = fgetc(f);
        } if (cur == 127) {
            printf("^?");
            cur = fgetc(f);
        }
    } 
     
if (options -> t) { 
     while (cur == '\t') {
        cur = fgetc(f);
         printf("^I");
    }
 }
   if (options -> e) {
     if (cur == '\n') {
    printf("$");
    }
 } 
 temp = next;
 next = cur;
 if ( cur != EOF) {
 fprintf(stdout,"%c", cur);
 }
}
fclose(f);
} 
// else if (!f && (argv[argvCounter][0] != '-')) {
//     fprintf(stderr, "Cat: %s: no such file or directory", argv[argC])
// } 
}
}

int main(int argc, char **argv) {
if (argc > 1) {
    if (argv) {

 opt options = {0};
parser(argc, argv, &options);
reader(argv, &options, argc);
}
} 
}