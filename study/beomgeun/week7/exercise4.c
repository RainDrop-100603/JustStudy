// Author:
#include <stdio.h>

#define MAXLINE 4096

int strlength(char *);

int main(void) {
    char line[MAXLINE];
    fgets(line, MAXLINE, stdin);
    int length = strlength(line);
    for (int i = 0; i < length; i++) {
        printf("%c\n", line[i]);
    }
}

int strlength(char *s) {
    // TODO
    int len = 0;
    while (s[len] != '\n' && s[len] != '\0') {
        len += 1;
    }
    return len;
}
