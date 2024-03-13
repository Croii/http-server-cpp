// Online C compiler to run C program online
#include <stdio.h>
#include <string.h>
int main() {
    char string[120] = "GET /index.html HTTP/1.1\r\nHost: localhost:4221\r\nUser-Agent: curl/7.64.1";
    char *sep = "\r\n";
    char *line = strtok(string, sep);
    line = strtok(line, " ");
    line = strtok(NULL, " ");

    puts(line);


    return 0;
}