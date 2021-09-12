#include <string>
#include <vector>

using namespace std;

int peach_score(vector<int>& info){
    int score=0;
    for(int i=0;i<10;i++){
        if(info[i]>0){
            score+=10-i;
        }
    }
    return score;
}

int get_cache(vector<int>& info, vector<vector<int>>& cache, int target, int remain){
    int& ret=cache[target][remain];
    if(ret!=-1){
        return ret;
    }
    if(target==0){
        ret=0;
        return ret;
    }
    //
    int peach_shot = info[10-target];
    int noShot = get_cache(info,cache,target-1,remain);
    int winShot(0);
    if(remain>peach_shot){
        if(peach_shot==0){
            winShot= target+get_cache(info,cache,target-1,remain-1);
        }else{
            winShot = target*2+get_cache(info,cache,target-1, remain-peach_shot-1);
        }
    }
    ret= max(noShot,winShot);
    return ret;
}

vector<int> get_path(vector<vector<int>>& cache, vector<int>& info){
    vector<int> ret;
    int target(10),remain(cache[0].size()-1);
    while(target>0){
        if(remain==0){
            ret.push_back(0);
            target--;
            continue;
        }
        //
        int prevMax=cache[target][remain];
        int peach_shot=info[10-target];
        int noShot =cache[target-1][remain] ;
        int winShot(0);
        if(remain>peach_shot){
            if(peach_shot==0){
                winShot= target+cache[target-1][remain-1];
            }else{
                winShot = target*2 + cache[target-1][remain-peach_shot-1];
            }
        }
        //
        if(prevMax==noShot){
            ret.push_back(0);
        }else if(prevMax==winShot){
            ret.push_back(peach_shot+1);
            remain-=peach_shot+1;
        }
        target--;
    }
    ret.push_back(remain);
    return ret;
}

vector<int> solution(int n, vector<int> info) {
    vector<int> answer{-1};
    int peach=peach_score(info);
    vector<vector<int>> cache(11,vector<int>(n+1,-1));
    int lion=get_cache(info,cache,10,n); //0~10점 과녁기준으로 총 n발을 쏠 수 있을때의 최대점 
    if(peach<lion){
        answer=get_path(cache,info);
    }
    // 선택지는 2개, 안쏜다, +1개쏜다.
    // 어피치 점수는 일단 다 더해준다.
    // 라이언점수: 안쏜다 0점, 쏜다 2배점수(어피치가 쐈을경우) or 그냥점수 
    return answer;
}