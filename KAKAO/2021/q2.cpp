#include <string>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

string convert(int n ,int k){
    string result;
    while(n!=0){
        result+=to_string(n%k);
        n/=k;
    }
    return result;
}

vector<long long> get_number(string converted){
    reverse(converted.begin(),converted.end()); //idx = 0 : 최고차수 
    vector<long long> numbers;
    string tmp;
    for(auto& ele:converted){
        if(ele!='0'){
            tmp.push_back(ele);
        }else if(!tmp.empty()){
            numbers.push_back(stoll(tmp));
            tmp.clear();
        }
    }
    if(!tmp.empty()){
        numbers.push_back(stoll(tmp));
    }
    return numbers;
}

bool is_prime(long long n){
    if(n<2){
        return false;
    }
    long long sqrtn=sqrt(n);
    for(long long i=2;i<=sqrtn;i++){
        if(n%i==0){
            return false;
        }
    }
    return true;
}

int solution(int n, int k) {
    string converted=convert(n,k);
    vector<long long> numbers=get_number(converted);
    int answer = 0 ;
    for(auto& ele:numbers){
        if(is_prime(ele)){
            answer++;
        }
    }
    return answer;
}