#include <stdio.h>

int main() {
    // get box size
    int boxNum;
    printf("How many boxes: ");
    scanf("%d", &boxNum);

    // make box
    int size = boxNum * 4 - 1;
    for (int r = 0; r < size; r++) {
        for (int c = 0; c < size; c++) {
            // find row-base Box info, col-base Box info
            int rowBox = r < boxNum * 2 - 1 ? r / 2 : (size - 1 - r) / 2;
            int colBox = c < boxNum * 2 - 1 ? c / 2 : (size - 1 - c) / 2;
            // print Box
            if (r % 2 == 0 && (c >= rowBox * 2 && c < size - rowBox * 2)) {
                // check box-row
                printf("#");
            } else if (c % 2 == 0 && (r >= colBox * 2 && r < size - colBox * 2)) {
                // check box-column
                printf("#");
            } else {
                // non-box area
                printf(" ");
            }
        }
        // row change
        printf("\n");
    }
    return 0;
}