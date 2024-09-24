#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define LINE_SIZE 1024

/* This function prints lines (in a file) that contain string s.Assume all lines have at most (LINE_SIZE - 2) ASCII characters. */
int print_matched_lines(const char *s, const char *filename)
{
    FILE* file = fopen(filename, "r");
    if (file == NULL) printf("Doesn't work");
    char x[LINE_SIZE];
    int z = 0;

    while(!feof(file)){
        fgets(x, LINE_SIZE, file);
        char* y = strstr(x, s);
        if (y != NULL) {
            fprintf(stdout, x);
            z++;
    }
    } 
    if (z==0) return -1;
    return 0;
    
}
    /* TODO: Open the file given in the argument and read every line till EOF. 
	     If a line contains the string s, print it on the stdout. 
             You may use strstr to determine if a string appears in another string. Check man page for strstr for details.
	     Return 0 upon successful completion. Otherwise, return -1. */


int main(int argc, char **argv)
{
    if (argc != 3) {
        printf("Usage: %s <string> <filename>\n", argv[0]);
        return -1;
    }

    if (print_matched_lines(argv[1], argv[2])) {
        printf("print_matched_lines() returned a non_zero value.\n");
	return -1;
    }
    return 0;
}
