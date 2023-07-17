// Author: Beomgeun Kim
// Date: 10 July 2023
// Reads characters from stdin and prints the number of characters
// in that string
#include <stdio.h>

#define MAXLINE 1024

int strlength(char *);

int main(void) {
    char line[MAXLINE];
    fgets(line, MAXLINE, stdin);
    printf("Strlen is %d\n", strlength(line));
}
int strlength(char *s) {
    int length = 0;
    while (s[length] != '\0' &&) {
        length = length + 1;
    }
    return length;
}
sada\n = 4글자 근데 / 0 때문에 5로 나오니비 world\n

                          EOF->getchar는 문자를 읽어서 어떤 문자인지 반환하는 함수.getchar가 더 읽을 문자가 없을 때,
    EOf(-1) 을 반환한다.'\0'->fgets 문자열의 끝을 표현하기위해서 붙는거.

    c = getchar() != EOF

        declare : int c;
initialize : c = 3;

abcd\n efg\n hji

    stdin \n

        // 문자를 입력받는다
        code
            // 문자가 aeiou 인지 확인하고 출ㄹ력한다.
            code
                // EOF나 \n 이면 끝낸다.
                code