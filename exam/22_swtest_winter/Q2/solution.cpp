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

vector<vector<int>> relations;  // rel[FROM][TO] means TO is FROM's: noting(-1), couple(0), parent(1), child(2)
vector<vector<int>> distances;  // distance
map<string, int> nameMapping;   // name, idx
vector<int> sex;                // 0: male, 1: female
int memberNum;

int SOL_COUPLE = 0;
int SOL_PARENTS = 1;
int SOL_CHILD = 2;

int insertToMap(char newName[], int newSex) {
    nameMapping.insert(make_pair(string(newName), memberNum));
    sex[memberNum] = newSex;
    memberNum++;
    return memberNum - 1;
}
int findIdxFromName(char name[]) { return nameMapping.find(string(name))->second; }
vector<int> findRelations(int relationship, int fromIdx) {
    vector<int> ret;
    for (int i = 0; i < memberNum; i++) {
        if (relations[fromIdx][i] == relationship) ret.push_back(i);
    }
    return ret;
}
void updateRelations(int fromIdx, int toIdx, int relationShip) {
    if (relationShip == SOL_COUPLE) {
        relations[fromIdx][toIdx] = relations[toIdx][fromIdx] = SOL_COUPLE;
    } else if (relationShip == SOL_PARENTS) {
        relations[fromIdx][toIdx] = SOL_PARENTS;
        relations[toIdx][fromIdx] = SOL_CHILD;
    } else if (relationShip == SOL_CHILD) {
        relations[fromIdx][toIdx] = SOL_CHILD;
        relations[toIdx][fromIdx] = SOL_PARENTS;
    }
}
void updateDistances(int existIdx, int newIdx, int dist) {
    distances[existIdx][newIdx] = distances[newIdx][existIdx] = dist;
    for (int i = 0; i < memberNum; i++) {
        auto& target = distances[newIdx][i];
        target = min(target, dist + distances[i][existIdx]);
        distances[i][newIdx] = target;
    }
}
void addCouple(int existIdx, int newIdx) {
    updateRelations(newIdx, existIdx, SOL_COUPLE);
    // additional: couple's child is my child
    auto children = findRelations(SOL_CHILD, existIdx);
    for (auto& child : children) {
        updateRelations(newIdx, child, SOL_CHILD);
    }
    // update distances
    updateDistances(existIdx, newIdx, 0);
}

void init(char initialMemberName[], int initialMemberSex) {
    relations = vector<vector<int>>(MAXMEMBER + 1, vector<int>(MAXMEMBER + 1, -1));
    distances = vector<vector<int>>(MAXMEMBER + 1, vector<int>(MAXMEMBER + 1, MAXMEMBER + 100));
    nameMapping = map<string, int>();
    sex = vector<int>(MAXMEMBER + 1, -1);
    memberNum = 0;
    insertToMap(initialMemberName, initialMemberSex);
}

bool addMember(char newMemberName[], int newMemberSex, int relationship, char existingMemberName[]) {
    int existMemberIdx = findIdxFromName(existingMemberName);
    int existMemberSex = sex[existMemberIdx];
    if (relationship == SOL_COUPLE) {
        auto couple = findRelations(SOL_COUPLE, existMemberIdx);
        // exception: no couple, no same sex
        if (newMemberSex == existMemberSex || !couple.empty()) return false;
        // add couple
        int newIdx = insertToMap(newMemberName, newMemberSex);
        addCouple(existMemberIdx, newIdx);
        return true;
    } else if (relationship == SOL_PARENTS) {
        auto parents = findRelations(SOL_PARENTS, existMemberIdx);
        if (parents.size() == 2) {
            return false;
        } else if (parents.size() == 1) {
            // exception: no same sex parent
            if (sex[parents.front()] == newMemberSex) return false;
            // additional: if child have two parent, parent's become couple
            int newIdx = insertToMap(newMemberName, newMemberSex);
            addCouple(parents.front(), newIdx);
        } else if (parents.empty()) {
            int newIdx = insertToMap(newMemberName, newMemberSex);
            updateRelations(existMemberIdx, newIdx, SOL_PARENTS);
            // update distances
            updateDistances(existMemberIdx, newIdx, 1);
        }
        return true;
    } else if (relationship == SOL_CHILD) {  // child
        int newIdx = insertToMap(newMemberName, newMemberSex);
        updateRelations(existMemberIdx, newIdx, SOL_CHILD);
        updateDistances(existMemberIdx, newIdx, 1);
        // additional: if parent have couple, child is couple's child
        auto couple = findRelations(SOL_COUPLE, existMemberIdx);
        if (!couple.empty()) {
            updateRelations(couple.front(), newIdx, SOL_CHILD);
            updateDistances(couple.front(), newIdx, 1);
        }
        return true;
    }
    return false;
}

int getDistance(char nameA[], char nameB[]) {
    int idxA = nameMapping.find(string(nameA))->second;
    int idxB = nameMapping.find(string(nameB))->second;
    return distances[idxA][idxB];
}

int countMember(char name[], int dist) {
    int idx = nameMapping.find(string(name))->second;
    int cnt = 0;
    for (int i = 0; i < memberNum; i++) {
        if (i == idx) continue;  // dist[i][i]==0 from updateDistances, so do not count it
        if (distances[idx][i] == dist) cnt++;
    }
    return cnt;
}
