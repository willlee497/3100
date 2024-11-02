#include "analyze.h"
#include <stdio.h>

int main(int argc, char *argv[])
{
   if (argc < 2)
   {
      printf("Usage is: wgettext <url>\n");
      return 1;
   }
   char serverName[512];
   int portNumber = 80;
   char documentPath[512];
   analyzeURL(argv[1], serverName, &portNumber, documentPath);
   printf("[%s] [%d] [%s]\n", serverName, portNumber, documentPath);
   return 0;
}
