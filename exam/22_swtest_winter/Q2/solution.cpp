//	 The below commented functions are for your reference. If you want
//	 to use it, uncomment these functions.
/*
int mstrcmp(const char a[], const char b[])
{
        int i;
        for (i = 0; a[i] != '\0'; ++i) if (a[i] != b[i]) return a[i] - b[i];
        return a[i] - b[i];
}

void mstrcpy(char dest[], const char src[])
{
        int i = 0;
        while (src[i] != '\0') { dest[i] = src[i]; i++; }
        dest[i] = src[i];
}

int mstrlen(const char a[])
{
        int i;
        for (i = 0; a[i] != '\0'; ++i);
        return i;
}
*/

#include <map>
#include <string>
#include <vector>

using namespace std;

int MAXMEMBER = 200;

vector<vector<int>> relation;  // rel[A][B], -1: no relation, 0: couple, 1: A is B's parent, 2: A is B's child
vector<vector<int>> distance;  // distance with A and B
map<string, int> nameMapping;  // name,idx
vector<int> gender;            // 0: male, 1: female

void init(char initialMemberName[], int initialMemberSex) {
    relation = vector<vector<int>>(MAXMEMBER + 1, vector<int>(MAXMEMBER + 1, -1));
    distance = vector<vector<int>>(MAXMEMBER + 1, vector<int>(MAXMEMBER + 1, MAXMEMBER + 100));
    nameMapping = map<string, int>();
    gender = vector<int>(MAXMEMBER + 1, -1);
    nameMapping.insert(make_pair(string(initialMemberName), 0));
    gender[0] = initialMemberSex;
}

bool addMember(char newMemberName[], int newMemberSex, int relationship, char existingMemberName[]) {
    if (relationship == 0) {  // couple
        // exception: no couple, no same sex
        // additional: couple's child is my child
    } else if (relationship == 1) {  // parent
        // exception: no same sex parent
        // additional: if child have two parent, parent's become couple
    } else {  // child
        // no exception
        // additional: if parent have couple, child is couple's child
    }
    return false;
}

int getDistance(char nameA[], char nameB[]) { return -1; }

int countMember(char name[], int dist) { return -1; }
