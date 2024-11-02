#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <netinet/in.h>
#include <errno.h>
#include <fcntl.h>
#include "analyze.h"

void checkError(int status, int line)
{
    if (status < 0)
    {
        printf("socket error(%d)-%d: [%s]\n", getpid(), line, strerror(errno));
        exit(-1);
    }
}

char *skip_http_headers(char *response)
{
    char *body = strstr(response, "\r\n\r\n");
    if (body)
    {
        return body + 4;
    }
    return response;
}

char *readResponse(int sid)
{
    size_t sz = 8;
    char *buffer = malloc(sizeof(char) * sz);
    int done = 0, received = 0;
    while (!done)
    {
        int bytesRead = read(sid, buffer + received, sz - received);
        if (bytesRead > 0)
        {
            received += bytesRead;
        }
        else if (bytesRead == 0)
        {
            done = 1;
        }
        if (received == sz)
        {
            buffer = realloc(buffer, sz * 2);
            sz *= 2;
        }
    }
    if (received == sz)
    {
        buffer = realloc(buffer, sz + 1);
    }
    buffer[received] = 0;
    return buffer;
}

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

    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    checkError(sockfd, __LINE__);

    struct hostent *server = gethostbyname(serverName);
    if (server == NULL)
    {
        fprintf(stderr, "Error: No such host\n");
        exit(1);
    }

    struct sockaddr_in serverAddr;
    memset(&serverAddr, 0, sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(portNumber);
    memcpy(&serverAddr.sin_addr.s_addr, server->h_addr, server->h_length);

    int connectStatus = connect(sockfd, (struct sockaddr *)&serverAddr, sizeof(serverAddr));
    checkError(connectStatus, __LINE__);

    char request[2048];
    snprintf(request, sizeof(request), "GET /%s HTTP/1.0\r\nHost: %s\r\n\r\n", documentPath, serverName);
    int sendStatus = write(sockfd, request, strlen(request));
    checkError(sendStatus, __LINE__);

    char *response = readResponse(sockfd);
    char *body = skip_http_headers(response);

    int pipefd[2];
    if (pipe(pipefd) == -1)
    {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    pid_t pid = fork();
    if (pid == -1)
    {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (pid == 0)
    {
        close(pipefd[1]);
        dup2(pipefd[0], STDIN_FILENO);
        close(pipefd[0]);
        execl("/usr/bin/html2text", "html2text", (char *)NULL);
        perror("execl");
        exit(EXIT_FAILURE);
    }
    else
    {
        close(pipefd[0]);
        write(pipefd[1], body, strlen(body));
        close(pipefd[1]);
        wait(NULL);
    }

    free(response);
    close(sockfd);

    return 0;
}
