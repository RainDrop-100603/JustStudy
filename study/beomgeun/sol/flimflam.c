// Author: Beomgeun Kim
// Student ID: z5446304
// Date finished: 8 July 2023
// The coding for the Flim Flam game identifying the best rule for
// winning the game

#include <stdio.h>

#define FALSE 0
#define TRUE (!FALSE)

int getInput(int* nums);
void totalScore(int* nums, int* rules, int* integers, int priority);
void match2(int* nums, int* rules, int* integers, int priority);
void match3(int* nums, int* rules, int* integers, int priority);
void match4(int* nums, int* rules, int* integers, int priority);
void match5(int* nums, int* rules, int* integers, int priority);
void match6(int* nums, int* rules, int* integers, int priority);
void sequence2(int* nums, int* rules, int* integers, int priority);
void sequence3(int* nums, int* rules, int* integers, int priority);
void sequence4(int* nums, int* rules, int* integers, int priority);
void sequence5(int* nums, int* rules, int* integers, int priority);
void sequence6(int* nums, int* rules, int* integers, int priority);
void sum2(int* nums, int* rules, int* integers, int priority);
void sum3(int* nums, int* rules, int* integers, int priority);
void sum4(int* nums, int* rules, int* integers, int priority);
void sum5(int* nums, int* rules, int* integers, int priority);
void filmFlam(int* nums, int* rules, int* integers, int priority);
int findHighest(int* rules);
void makeOutput(int* rules, int* integers, int highest);

int main(void) {
    int nums[6];                // input numbers
    int rules[16] = {0};        // highest score of each rules
    int integers[16][6] = {0};  // integer sets of each rules

    // get input and check if input is valid
    if (getInput(nums) == FALSE) {
        printf(
            "Invalid input: 6 integers 1..9 in sorted order must "
            "be supplied.\n");
        return 0;
    }

    // alphabetical order flim flam(0) - match(1~5) - sequence(6~10) -
    // sum(11 ~ 14) - total(15)

    // For "total score" rule
    totalScore(nums, rules, integers[15], 15);

    // For "match-2" rule
    match2(nums, rules, integers[1], 1);

    // For "match-3" rule
    match3(nums, rules, integers[2], 2);

    // For "match-4" rule
    match4(nums, rules, integers[3], 3);

    // For "match-5" rule
    match5(nums, rules, integers[4], 4);

    // For "match-6" rule
    match6(nums, rules, integers[5], 5);

    // For "sequence-2" rule
    sequence2(nums, rules, integers[6], 6);

    // For "sequence-3" rule
    sequence3(nums, rules, integers[7], 7);

    // For "sequence-4" rule 1 3 4 4 5 6
    sequence4(nums, rules, integers[8], 8);

    // For "sequence-5" rule
    sequence5(nums, rules, integers[9], 9);

    // For "sequence-6" rule
    sequence6(nums, rules, integers[10], 10);

    // For "sum-2" rule
    sum2(nums, rules, integers[11], 11);

    // For "sum-3" rule
    sum3(nums, rules, integers[12], 12);

    // For "sum-4" rule
    sum4(nums, rules, integers[13], 13);

    // For "sum-5" rule
    sum5(nums, rules, integers[14], 14);

    // For "flim flam" rule
    filmFlam(nums, rules, integers[0], 0);

    // find highest score and output
    int highest = findHighest(rules);
    makeOutput(rules, integers[highest], highest);

    return 0;
}

int getInput(int* nums) {
    // Checking the values are 6 integers.
    if (scanf("%d %d %d %d %d %d", &nums[0], &nums[1], &nums[2],
              &nums[3], &nums[4], &nums[5]) != 6) {
        return FALSE;
    }
    // Checking invalid input
    int i = 0;
    while (i < 6) {
        if (nums[i] < 1 || nums[i] > 9) {
            return FALSE;
        }
        if (i > 0 && nums[i] < nums[i - 1]) {
            return FALSE;
        }
        i = i + 1;
    }
    // no problem, return TRUE
    return TRUE;
}
void totalScore(int* nums, int* rules, int* integers, int priority) {
    // check total score
    int totalScore =
        (nums[0] + nums[1] + nums[2] + nums[3] + nums[4] + nums[5]);
    rules[priority] = totalScore;
    integers[0] = nums[0];
    integers[1] = nums[1];
    integers[2] = nums[2];
    integers[3] = nums[3];
    integers[4] = nums[4];
    integers[5] = nums[5];
}

void match2(int* nums, int* rules, int* integers, int priority) {
    // check match2
    int i = 0;
    while (i < 5) {
        if (nums[i] == nums[i + 1]) {
            int possibleScore = 2 * nums[i] + 19;
            rules[priority] = possibleScore;
            // Storing value of xa for output statement
            integers[0] = nums[i];
        }
        i = i + 1;
    }
}
void match3(int* nums, int* rules, int* integers, int priority) {
    // check match3
    int i = 0;
    while (i < 4) {
        if (nums[i] == nums[i + 1] && nums[i] == nums[i + 2]) {
            int possibleScore = 3 * nums[i] + 21;
            rules[priority] = possibleScore;
            // Storing value of xa for output statement
            integers[0] = nums[i];
        }
        i = i + 1;
    }
}
void match4(int* nums, int* rules, int* integers, int priority) {
    // check match4
    int i = 0;
    while (i < 3) {
        if (nums[i] == nums[i + 1] && nums[i] == nums[i + 2] &&
            nums[i] == nums[i + 3]) {
            int possibleScore = 4 * nums[i] + 23;
            rules[priority] = possibleScore;
            // Storing value of xa for output statement
            integers[0] = nums[i];
        }
        i = i + 1;
    }
}
void match5(int* nums, int* rules, int* integers, int priority) {
    // check match5
    int i = 0;
    while (i < 2) {
        if (nums[i] == nums[i + 1] && nums[i] == nums[i + 2] &&
            nums[i] == nums[i + 3] && nums[i] == nums[i + 4]) {
            int possibleScore = 5 * nums[i] + 25;
            rules[priority] = possibleScore;
            // Storing value of xa for output statement
            integers[0] = nums[i];
        }
        i = i + 1;
    }
}
void match6(int* nums, int* rules, int* integers, int priority) {
    // check match6
    if (nums[0] == nums[1] && nums[0] == nums[2] &&
        nums[0] == nums[3] && nums[0] == nums[4] &&
        nums[0] == nums[5]) {
        int possibleScore = 6 * nums[0] + 27;
        rules[priority] = possibleScore;
        // Storing value of xa for output statement
        integers[0] = nums[0];
    }
}
void sequence2(int* nums, int* rules, int* integers, int priority) {
    // check sequence2 for near number
    int i = 1;
    while (i < 6) {
        if (nums[i] - 1 == nums[i - 1]) {
            int possibleScore = 2 * nums[i] + 17;
            rules[priority] = possibleScore;
            integers[0] = nums[i - 1];
            integers[1] = nums[i];
        }
        i = i + 1;
    }
}
void sequence3(int* nums, int* rules, int* integers, int priority) {
    // eliminate 3 numbers(i,j,k) and check sequence3
    int i = 5;
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
                    if (possibleScore > rules[priority]) {
                        rules[priority] = possibleScore;
                        integers[0] = sequence[0];
                        integers[1] = sequence[1];
                        integers[2] = sequence[2];
                    }
                }
                k = k - 1;
            }
            j = j - 1;
        }
        i = i - 1;
    }
}
void sequence4(int* nums, int* rules, int* integers, int priority) {
    // eliminate 2 numbers(i,j) and check sequence4
    int i = 5;
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
                if (possibleScore > rules[priority]) {
                    rules[priority] = possibleScore;
                    integers[0] = sequence[0];
                    integers[1] = sequence[1];
                    integers[2] = sequence[2];
                    integers[3] = sequence[3];
                }
            }
            j = j - 1;
        }
        i = i - 1;
    }
}
void sequence5(int* nums, int* rules, int* integers, int priority) {
    // eliminate 1 numbers(i) and check sequence5
    int i = 5;
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
            if (possibleScore > rules[priority]) {
                rules[priority] = possibleScore;
                integers[0] = sequence[0];
                integers[1] = sequence[1];
                integers[2] = sequence[2];
                integers[3] = sequence[3];
                integers[4] = sequence[4];
            }
        }
        i = i - 1;
    }
}
void sequence6(int* nums, int* rules, int* integers, int priority) {
    // check sequence6
    if (nums[5] - 1 == nums[4] && nums[5] - 2 == nums[3] &&
        nums[5] - 3 == nums[2] && nums[5] - 4 == nums[1] &&
        nums[5] - 5 == nums[0]) {
        int possibleScore = 6 * nums[5] + 21;
        rules[priority] = possibleScore;
        integers[0] = nums[0];
        integers[1] = nums[1];
        integers[2] = nums[2];
        integers[3] = nums[3];
        integers[4] = nums[4];
        integers[5] = nums[5];
    }
}
void sum2(int* nums, int* rules, int* integers, int priority) {
    // select 3 numbers(i,j,k) and check sum2
    int i = 5;
    while (i >= 2) {
        int j = i - 1;
        while (j >= 1) {
            int k = j - 1;
            while (k >= 0) {
                if (nums[k] + nums[j] == nums[i]) {
                    int possibleScore = nums[k] + nums[i] + 22;
                    if (possibleScore > rules[priority]) {
                        rules[priority] = possibleScore;
                        integers[0] = nums[k];
                        integers[1] = nums[j];
                        integers[2] = nums[i];
                    }
                }
                k = k - 1;
            }
            j = j - 1;
        }
        i = i - 1;
    }
}
void sum3(int* nums, int* rules, int* integers, int priority) {
    // eliminate 2 numbers(i,j) and check sum3
    int i = 0;
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
                if (possibleScore > rules[priority]) {
                    rules[priority] = possibleScore;
                    integers[0] = left[0];
                    integers[1] = left[1];
                    integers[2] = left[2];
                    integers[3] = right;
                }
            }
            j = j + 1;
        }
        i = i + 1;
    }
}
void sum4(int* nums, int* rules, int* integers, int priority) {
    // eliminate 1 numbers(i) and check sum4
    int i = 0;
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
            if (possibleScore > rules[priority]) {
                rules[priority] = possibleScore;
                integers[0] = left[0];
                integers[1] = left[1];
                integers[2] = left[2];
                integers[3] = left[3];
                integers[4] = right;
            }
        }
        i = i + 1;
    }
}
void sum5(int* nums, int* rules, int* integers, int priority) {
    // check sum5
    if (nums[0] + nums[1] + nums[2] + nums[3] + nums[4] == nums[5]) {
        int possibleScore = nums[0] + nums[5] + 49;
        rules[priority] = possibleScore;
        integers[0] = nums[0];
        integers[1] = nums[1];
        integers[2] = nums[2];
        integers[3] = nums[3];
        integers[4] = nums[4];
        integers[5] = nums[5];
    }
}
void filmFlam(int* nums, int* rules, int* integers, int priority) {
    // select 3 numbers(i,j,k) and check film-flam
    int i = 0;
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
                        if (possibleScore > rules[priority]) {
                            rules[priority] = possibleScore;
                            integers[0] = left[0];
                            integers[1] = left[1];
                            integers[2] = left[2];
                            integers[3] = right[0];
                            integers[4] = right[1];
                            integers[5] = right[2];
                        }
                    }
                }
                t = t + 1;
            }

            j = j + 1;
        }
        i = i + 1;
    }
}
int findHighest(int* rules) {
    // find highest - score idx

    // alphabetical order flim flam(0) - match(1~5) - sequence(6~10) -
    // sum(11 ~ 14) - total(15)
    int maximumScore = 0;
    int highest = 0;
    int i = 0;
    while (i < 16) {
        if (rules[i] > maximumScore) {
            maximumScore = rules[i];
            highest = i;
        }
        i = i + 1;
    }
    return highest;
}
void makeOutput(int* rules, int* integers, int highest) {
    // output result

    // alphabetical order flim flam(0) - match(1~5) - sequence(6~10) -
    // sum(11 ~ 14) - total(15)

    int maximumScore = rules[highest];
    if (highest == 15) {
        printf("Rule total - score %d.\n", maximumScore);
    } else if (highest == 1) {
        printf("Rule match-2(%d) - score %d.\n", integers[0],
               maximumScore);
    } else if (highest == 2) {
        printf("Rule match-3(%d) - score %d.\n", integers[0],
               maximumScore);
    } else if (highest == 3) {
        printf("Rule match-4(%d) - score %d.\n", integers[0],
               maximumScore);
    } else if (highest == 4) {
        printf("Rule match-5(%d) - score %d.\n", integers[0],
               maximumScore);
    } else if (highest == 5) {
        printf("Rule match-6(%d) - score %d.\n", integers[0],
               maximumScore);
    } else if (highest == 6) {
        printf("Rule sequence-2(%d,%d) - score %d.\n", integers[0],
               integers[1], maximumScore);
    } else if (highest == 7) {
        printf("Rule sequence-3(%d,%d,%d) - score %d.\n", integers[0],
               integers[1], integers[2], maximumScore);
    } else if (highest == 8) {
        printf("Rule sequence-4(%d,%d,%d,%d) - score %d.\n",
               integers[0], integers[1], integers[2], integers[3],
               maximumScore);
    } else if (highest == 9) {
        printf("Rule sequence-5(%d,%d,%d,%d,%d) - score %d.\n",
               integers[0], integers[1], integers[2], integers[3],
               integers[4], maximumScore);
    } else if (highest == 10) {
        printf("Rule sequence-6(%d,%d,%d,%d,%d,%d) - score %d.\n",
               integers[0], integers[1], integers[2], integers[3],
               integers[4], integers[5], maximumScore);
    } else if (highest == 11) {
        printf("Rule sum-2(%d+%d=%d) - score %d.\n", integers[0],
               integers[1], integers[2], maximumScore);
    } else if (highest == 12) {
        printf("Rule sum-3(%d+%d+%d=%d) - score %d.\n", integers[0],
               integers[1], integers[2], integers[3], maximumScore);
    } else if (highest == 13) {
        printf("Rule sum-4(%d+%d+%d+%d=%d) - score %d.\n", integers[0],
               integers[1], integers[2], integers[3], integers[4],
               maximumScore);
    } else if (highest == 14) {
        printf("Rule sum-5(%d+%d+%d+%d+%d=%d) - score %d.\n",
               integers[0], integers[1], integers[2], integers[3],
               integers[4], integers[5], maximumScore);
    } else if (highest == 0) {
        printf("Rule flim-flam(%d+%d=%d,%d+%d=%d) - score %d.\n",
               integers[0], integers[1], integers[2], integers[3],
               integers[4], integers[5], maximumScore);
    }
}
