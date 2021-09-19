#include <string>
#include <vector>
#include <map>

using namespace std;

vector<int> solution(vector<string> id_list, vector<string> report, int k) {
    //전처리
    int idNum=id_list.size();
    map<string,int> id_map;
    for(int i=0;i<idNum;i++){
        id_map.insert(make_pair(id_list[i],i));
    }
    //report 처리
    vector<vector<int>> reports(idNum,vector<int>(idNum,0));
    for(auto& ele: report){
        int pos=ele.find(" ");
        int from=id_map[ele.substr(0,pos)];
        int to=id_map[ele.substr(pos+1)];
        reports[to][from]++;
    }
    //report 처리결과 계산 및 반환
    vector<int> answer(idNum);
    for(int i=0;i<idNum;i++){
        int count=0;
        for(auto& ele:reports[i]){
            if(ele){
                count++;
            }
        }
        if(count>=k){
            int idx=0;
            for(auto& ele:reports[i]){
                if(ele){
                    answer[idx]++;
                }
                idx++;
            }
        }
    }
    return answer;
}