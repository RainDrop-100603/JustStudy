#include <stdio.h>

int main() {
    // get box size
    int boxSize;
    printf("How many boxes: ");
    scanf("%d", &boxSize);

    // make box
    int height = boxSize * 4 - 1;
    for (int h = 0; h < height; h++) {
        // get nthBox
        int nthBox = h < boxSize * 2 ? h / 2 : boxSize * 2 - (h + 1) / 2 - 1;
        // left side
        printf("#");
        for (int i = 0; i < nthBox; i++) {
            printf(" #");
        }
        // main
        int mainSize = height - 2 * (1 + nthBox * 2);
        char symbol = h % 2 == 0 ? '#' : ' ';
        for (int i = 0; i < mainSize; i++) {
            printf("%c", symbol);
        }
        // right side
        for (int i = 0; i < nthBox; i++) {
            printf("# ");
        }
        printf("#\n");
    }

    return 0;
}