#include <string>
#include <vector>
#include <cmath>
#include <map>

using namespace std;

vector<int> get_info(string str){
    vector<int> info(2);    //번호, 시간
    info[0]=stoi(str.substr(6,4));
    info[1]=stoi(str.substr(0,2))*60 + stoi(str.substr(3,2));
    return info;
}

int get_fee(int time, vector<int> fees){
    int base(fees[0]),base_fee(fees[1]),addi(fees[2]),addi_fee(fees[3]);
    if(time<=base){
        return base_fee;
    }
    time-=base;
    return base_fee + ceil(time/double(addi))*addi_fee;
}

vector<int> solution(vector<int> fees, vector<string> records) {
        map<int,int> in_time;
        map<int,int> total_time;
    //
    for(auto& ele:records){
        auto info=get_info(ele);    // 번호, 시간
        auto tmp=in_time.insert(make_pair(info[0],info[1]));    // 입차
        int time=0;
        if(!tmp.second){    // 이미 입차해 있는경우
            time=info[1] - tmp.first->second,fees;
            in_time.erase(tmp.first);
        }
        tmp=total_time.insert(make_pair(info[0],time));
        if(!tmp.second){
            tmp.first->second+=time;
        }
    }
    for(auto& ele:in_time){
        int time=1439-ele.second;   //23:59 == 1439
        auto tmp=total_time.insert(make_pair(ele.first,time));
        if(!tmp.second){
            tmp.first->second+=time;
        }
    }
    //
    vector<int> answer;
    for(auto& ele: total_time){
        answer.push_back(get_fee(ele.second,fees));
    }
    return answer;
}