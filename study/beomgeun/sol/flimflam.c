// Author: Beomgeun Kim
// Student ID: z5446304
// Date finished: 8 July 2023
// The coding for the Flim Flam game identifying the best rule for
// winning the game

#include <stdio.h>

int main() {
    int nums[6];
    int rules[16] = {0};
    int integers[16][6] = {0};

    // Checking the values are 6 integers.
    if (scanf("%d %d %d %d %d %d", &nums[0], &nums[1], &nums[2],
              &nums[3], &nums[4], &nums[5]) != 6) {
        printf(
            "Invalid input: 6 integers 1..9 in sorted order must be "
            "supplied.\n");
        return 0;
    }

    // Checking invalid input
    int i = 0;
    while (i < 6) {
        if (nums[i] < 1 || nums[i] > 9) {
            printf(
                "Invalid input: 6 integers 1..9 in sorted order must "
                "be supplied.\n");
            return 0;
        }
        if (i > 0 && nums[i] < nums[i - 1]) {
            printf(
                "Invalid input: 6 integers 1..9 in sorted order must "
                "be supplied.\n");
            return 0;
        }
        i = i + 1;
    }

    // alphabetical order flim flam(0) - match(1~5) - sequence(6~10) -
    // sum(11 ~ 14) - total(15) For "total" rule
    int totalScore =
        (nums[0] + nums[1] + nums[2] + nums[3] + nums[4] + nums[5]);
    rules[15] = totalScore;
    integers[15][0] = nums[0];
    integers[15][1] = nums[1];
    integers[15][2] = nums[2];
    integers[15][3] = nums[3];
    integers[15][4] = nums[4];
    integers[15][5] = nums[5];

    // For "match-2" rule
    i = 0;
    while (i < 5) {
        if (nums[i] == nums[i + 1]) {
            int possibleScore = 2 * nums[i] + 19;
            rules[1] = possibleScore;
            // Storing value of xa for output statement
            integers[1][0] = nums[i];
        }
        i = i + 1;
    }

    // For "match-3" rule
    i = 0;
    while (i < 4) {
        if (nums[i] == nums[i + 1] && nums[i] == nums[i + 2]) {
            int possibleScore = 3 * nums[i] + 21;
            rules[2] = possibleScore;
            // Storing value of xa for output statement
            integers[2][0] = nums[i];
        }
        i = i + 1;
    }

    // For "match-4" rule
    i = 0;
    while (i < 3) {
        if (nums[i] == nums[i + 1] && nums[i] == nums[i + 2] &&
            nums[i] == nums[i + 3]) {
            int possibleScore = 4 * nums[i] + 23;
            rules[3] = possibleScore;
            // Storing value of xa for output statement
            integers[3][0] = nums[i];
        }
        i = i + 1;
    }

    // For "match-5" rule
    i = 0;
    while (i < 2) {
        if (nums[i] == nums[i + 1] && nums[i] == nums[i + 2] &&
            nums[i] == nums[i + 3] && nums[i] == nums[i + 4]) {
            int possibleScore = 5 * nums[i] + 25;
            rules[4] = possibleScore;
            // Storing value of xa for output statement
            integers[4][0] = nums[i];
        }
        i = i + 1;
    }

    // For "match-6" rule
    if (nums[0] == nums[1] && nums[0] == nums[2] &&
        nums[0] == nums[3] && nums[0] == nums[4] &&
        nums[0] == nums[5]) {
        int possibleScore = 6 * nums[0] + 27;
        rules[5] = possibleScore;
        // Storing value of xa for output statement
        integers[5][0] = nums[0];
    }

    // For "sequence-2" rule
    i = 1;
    while (i < 6) {
        if (nums[i] - 1 == nums[i - 1]) {
            int possibleScore = 2 * nums[i] + 17;
            rules[6] = possibleScore;
            integers[6][0] = nums[i - 1];
            integers[6][1] = nums[i];
        }
        i = i + 1;
    }

    // For "sequence-3" rule
    i = 5;
    while (i >= 2) {
        int j = i - 1;
        while (j >= 1) {
            int k = j - 1;
            while (k >= 0) {
                // find xa, xb, xc.
                int sequence[3] = {0};  // Arrays storing xa, xb, xc.
                int cnt = 0;
                int p = 0;  // while loop.
                while (p < 6) {
                    if (p != i && p != j && p != k) {
                        sequence[cnt] = nums[p];
                        cnt = cnt + 1;
                    }
                    p = p + 1;
                }
                if (sequence[0] + 1 == sequence[1] &&
                    sequence[0] + 2 == sequence[2]) {
                    int possibleScore = 3 * sequence[2] + 18;
                    if (possibleScore > rules[7]) {
                        rules[7] = possibleScore;
                        integers[7][0] = sequence[0];
                        integers[7][1] = sequence[1];
                        integers[7][2] = sequence[2];
                    }
                }
                k = k - 1;
            }
            j = j - 1;
        }
        i = i - 1;
    }

    // For "sequence-4" rule 1 3 4 4 5 6
    i = 5;
    while (i >= 1) {
        int j = i - 1;
        while (j >= 0) {
            // find xa, xb, xc, xd.
            int sequence[4] = {0};  // Arrays storing xa, xb, xc, xd
            int cnt = 0;
            int p = 0;  // while loop.
            while (p < 6) {
                if (p != i && p != j) {
                    sequence[cnt] = nums[p];
                    cnt = cnt + 1;
                }
                p = p + 1;
            }
            if (sequence[0] + 1 == sequence[1] &&
                sequence[0] + 2 == sequence[2] &&
                sequence[0] + 3 == sequence[3]) {
                int possibleScore = 4 * sequence[3] + 19;
                if (possibleScore > rules[8]) {
                    rules[8] = possibleScore;
                    integers[8][0] = sequence[0];
                    integers[8][1] = sequence[1];
                    integers[8][2] = sequence[2];
                    integers[8][3] = sequence[3];
                }
            }
            j = j - 1;
        }
        i = i - 1;
    }

    // For "sequence-5" rule
    i = 5;
    while (i >= 0) {
        // find xa, xb, xc.
        int sequence[5] = {0};  // Arrays storing xa, xb, xc.
        int cnt = 0;
        int p = 0;  // while loop.
        while (p < 6) {
            if (p != i) {
                sequence[cnt] = nums[p];
                cnt = cnt + 1;
            }
            p = p + 1;
        }
        if (sequence[0] + 1 == sequence[1] &&
            sequence[0] + 2 == sequence[2] &&
            sequence[0] + 3 == sequence[3] &&
            sequence[0] + 4 == sequence[4]) {
            int possibleScore = 5 * sequence[4] + 20;
            if (possibleScore > rules[9]) {
                rules[9] = possibleScore;
                integers[9][0] = sequence[0];
                integers[9][1] = sequence[1];
                integers[9][2] = sequence[2];
                integers[9][3] = sequence[3];
                integers[9][4] = sequence[4];
            }
        }
        i = i - 1;
    }

    // For "sequence-6" rule
    if (nums[5] - 1 == nums[4] && nums[5] - 2 == nums[3] &&
        nums[5] - 3 == nums[2] && nums[5] - 4 == nums[1] &&
        nums[5] - 5 == nums[0]) {
        int possibleScore = 6 * nums[5] + 21;
        rules[10] = possibleScore;
        integers[10][0] = nums[0];
        integers[10][1] = nums[1];
        integers[10][2] = nums[2];
        integers[10][3] = nums[3];
        integers[10][4] = nums[4];
        integers[10][5] = nums[5];
    }

    // For "sum-2" rule
    i = 5;
    while (i >= 2) {
        int j = i - 1;
        while (j >= 1) {
            int k = j - 1;
            while (k >= 0) {
                if (nums[k] + nums[j] == nums[i]) {
                    int possibleScore = nums[k] + nums[i] + 22;
                    if (possibleScore > rules[11]) {
                        rules[11] = possibleScore;
                        integers[11][0] = nums[k];
                        integers[11][1] = nums[j];
                        integers[11][2] = nums[i];
                    }
                }
                k = k - 1;
            }
            j = j - 1;
        }
        i = i - 1;
    }

    // For "sum-3" rule
    i = 0;
    while (i < 6) {
        int j = i + 1;
        while (j < 6) {
            // find xa, xb, xc, xd.
            int left[3] = {0};  // Arrays storing xa, xb, xc.
            int right = 0;      // = xd.
            int cnt = 0;        // Number of values stored in left[3].
            int k = 0;          // while loop.
            while (k < 6) {
                if (k != i && k != j) {
                    if (cnt == 3) {
                        right = nums[k];
                    } else {
                        left[cnt] = nums[k];
                        cnt = cnt + 1;
                    }
                }
                k = k + 1;
            }
            // check xa + xb + xc = xd
            if (left[0] + left[1] + left[2] == right) {
                int possibleScore = left[0] + right + 29;
                if (possibleScore > rules[12]) {
                    rules[12] = possibleScore;
                    integers[12][0] = left[0];
                    integers[12][1] = left[1];
                    integers[12][2] = left[2];
                    integers[12][3] = right;
                }
            }
            j = j + 1;
        }
        i = i + 1;
    }

    // For "sum-4" rule
    i = 0;
    while (i < 6) {
        // find xa, xb, xc, xd, xe.
        int left[4] = {0};  // Arrays storing xa, xb, xc, xd.
        int right = 0;      // = xe.
        int cnt = 0;        // Number of values stored in left[4].
        int k = 0;          // while loop.
        while (k < 6) {
            if (k != i) {
                if (cnt == 4) {
                    right = nums[k];  // Finding xe.
                } else {
                    left[cnt] = nums[k];
                    cnt = cnt + 1;
                }
            }
            k = k + 1;
        }
        // check xa + xb + xc + xd = xe.
        if (left[0] + left[1] + left[2] + left[3] == right) {
            int possibleScore = left[0] + right + 38;
            if (possibleScore > rules[13]) {
                rules[13] = possibleScore;
                integers[13][0] = left[0];
                integers[13][1] = left[1];
                integers[13][2] = left[2];
                integers[13][3] = left[3];
                integers[13][4] = right;
            }
        }
        i = i + 1;
    }

    // For "sum-5" rule
    if (nums[0] + nums[1] + nums[2] + nums[3] + nums[4] == nums[5]) {
        int possibleScore = nums[0] + nums[5] + 49;
        rules[14] = possibleScore;
        integers[14][0] = nums[0];
        integers[14][1] = nums[1];
        integers[14][2] = nums[2];
        integers[14][3] = nums[3];
        integers[14][4] = nums[4];
        integers[14][5] = nums[5];
    }

    // For "flim flam" rule
    // alphabetical order flim flam(0) - match(1~5) - sequence(6~10) -
    // sum(11 ~ 14) - total(15)
    i = 0;
    while (i < 6) {
        int j = i + 1;
        while (j < 6) {
            int t = j + 1;
            while (t < 6) {
                // find xa, xb, xc, xd, xe, xf.
                int left[3] = {0};   // Arrays storing xa, xb, xc.
                int right[3] = {0};  // Arrays storing xd, xe, xf.
                int cnt = 0;  // Number of values stored in left[3].
                int k = 0;    // while loop.
                while (k < 6) {
                    if (k != i && k != j && k != t) {
                        left[cnt] = nums[k];
                        cnt = cnt + 1;
                    }
                    k = k + 1;
                }
                right[0] = nums[i];
                right[1] = nums[j];
                right[2] = nums[t];
                // checking the values satisfies the Flim Flam rule.
                if (left[0] + left[1] == left[2] &&
                    right[0] + right[1] == right[2]) {
                    if (left[0] <= right[0]) {
                        int possibleScore = left[0] + 2 * left[1] +
                                            3 * left[2] + 4 * right[0] +
                                            5 * right[1] + 6 * right[2];
                        if (possibleScore > rules[0]) {
                            rules[0] = possibleScore;
                            integers[0][0] = left[0];
                            integers[0][1] = left[1];
                            integers[0][2] = left[2];
                            integers[0][3] = right[0];
                            integers[0][4] = right[1];
                            integers[0][5] = right[2];
                        }
                    }
                }
                t = t + 1;
            }

            j = j + 1;
        }
        i = i + 1;
    }

    // alphabetical order flim flam(0) - match(1~5) - sequence(6~10) -
    // sum(11 ~ 14) - total(15) Output the result
    i = 0;
    int maximumScore = 0;
    int RuleNumber = 0;
    while (i < 16) {
        if (rules[i] > maximumScore) {
            maximumScore = rules[i];
            RuleNumber = i;
        }
        i = i + 1;
    }

    if (RuleNumber == 15) {
        printf("Rule total - score %d.\n", maximumScore);
    } else if (RuleNumber == 1) {
        printf("Rule match-2(%d) - score %d.\n", integers[1][0],
               maximumScore);
    } else if (RuleNumber == 2) {
        printf("Rule match-3(%d) - score %d.\n", integers[2][0],
               maximumScore);
    } else if (RuleNumber == 3) {
        printf("Rule match-4(%d) - score %d.\n", integers[3][0],
               maximumScore);
    } else if (RuleNumber == 4) {
        printf("Rule match-5(%d) - score %d.\n", integers[4][0],
               maximumScore);
    } else if (RuleNumber == 5) {
        printf("Rule match-6(%d) - score %d.\n", integers[5][0],
               maximumScore);
    } else if (RuleNumber == 6) {
        printf("Rule sequence-2(%d,%d) - score %d.\n", integers[6][0],
               integers[6][1], maximumScore);
    } else if (RuleNumber == 7) {
        printf("Rule sequence-3(%d,%d,%d) - score %d.\n",
               integers[7][0], integers[7][1], integers[7][2],
               maximumScore);
    } else if (RuleNumber == 8) {
        printf("Rule sequence-4(%d,%d,%d,%d) - score %d.\n",
               integers[8][0], integers[8][1], integers[8][2],
               integers[8][3], maximumScore);
    } else if (RuleNumber == 9) {
        printf("Rule sequence-5(%d,%d,%d,%d,%d) - score %d.\n",
               integers[9][0], integers[9][1], integers[9][2],
               integers[9][3], integers[9][4], maximumScore);
    } else if (RuleNumber == 10) {
        printf("Rule sequence-6(%d,%d,%d,%d,%d,%d) - score %d.\n",
               integers[10][0], integers[10][1], integers[10][2],
               integers[10][3], integers[10][4], integers[10][5],
               maximumScore);
    } else if (RuleNumber == 11) {
        printf("Rule sum-2(%d+%d=%d) - score %d.\n", integers[11][0],
               integers[11][1], integers[11][2], maximumScore);
    } else if (RuleNumber == 12) {
        printf("Rule sum-3(%d+%d+%d=%d) - score %d.\n", integers[12][0],
               integers[12][1], integers[12][2], integers[12][3],
               maximumScore);
    } else if (RuleNumber == 13) {
        printf("Rule sum-4(%d+%d+%d+%d=%d) - score %d.\n",
               integers[13][0], integers[13][1], integers[13][2],
               integers[13][3], integers[13][4], maximumScore);
    } else if (RuleNumber == 14) {
        printf("Rule sum-5(%d+%d+%d+%d+%d=%d) - score %d.\n",
               integers[14][0], integers[14][1], integers[14][2],
               integers[14][3], integers[14][4], integers[14][5],
               maximumScore);
    } else if (RuleNumber == 0) {
        printf("Rule flim-flam(%d+%d=%d,%d+%d=%d) - score %d.\n",
               integers[0][0], integers[0][1], integers[0][2],
               integers[0][3], integers[0][4], integers[0][5],
               maximumScore);
    }

    return 0;
}