#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void analyzeURL(const char *link, char *serverName, int *portNumber, char *documentPath)
{
    const char *prefix = "http://";
    const char *hostnameBegin = link;
    const char *documentBegin;
    char *portStr;

    if (strncmp(link, prefix, strlen(prefix)) == 0)
    {
        hostnameBegin += strlen(prefix);
    }

    documentBegin = strchr(hostnameBegin, '/');
    if (documentBegin != NULL)
    {
        strcpy(documentPath, documentBegin);
    }
    else
    {
        strcpy(documentPath, "/");
    }

    portStr = strchr(hostnameBegin, ':');
    if (portStr != NULL && portStr < documentBegin)
    {
        *portStr = '\0';
        strcpy(serverName, hostnameBegin);
        *portNumber = atoi(portStr + 1);
    }
    else
    {
        *portNumber = 80;
        if (documentBegin != NULL)
        {
            strncpy(serverName, hostnameBegin, documentBegin - hostnameBegin);
            serverName[documentBegin - hostnameBegin] = '\0';
        }
        else
        {
            strcpy(serverName, hostnameBegin);
        }
    }
}
