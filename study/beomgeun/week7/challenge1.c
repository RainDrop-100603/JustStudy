// Author:
#include <ctype.h>
#include <stdio.h>

#define MAXLINE 4096

int strlength(char *);
int isLetter(char);

int main(void) {
    // get string
    char line[MAXLINE];
    printf("Enter a string: ");
    fgets(line, MAXLINE, stdin);
    // check Palindrome
    int front = 0;
    int back = strlength(line) - 1;
    while (1) {
        // check if character is letter
        while (isLetter(line[front]) != 1) {
            front += 1;
        }
        while (isLetter(line[back]) != 1) {
            back -= 1;
        }
        // no error means this is palindrome
        if (back < front) {
            printf("String is a palindrome\n");
            return 0;
        }
        // check palindrome
        if (tolower(line[front]) != tolower(line[back])) {
            printf("String is not a palindrome\n");
            return 0;
        }
        // idx update
        front += 1;
        back -= 1;
    }
    return 0;
}

int strlength(char *s) {
    // TODO
    int length = 0;
    while (s[length] != '\0' && s[length] != '\n') {
        length = length + 1;
    }
    return length;
}

int isLetter(char s) {
    if ((s >= 'a' && s <= 'z') || (s >= 'A' && s <= 'Z')) {
        return 1;
    } else {
        return 0;
    }
}
