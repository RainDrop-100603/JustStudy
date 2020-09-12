// #include <string>
// #include <vector>

// using namespace std;

// void Step1(string& s){
//   for(auto& ele:s){
//     if(ele>='A'&&ele<='Z'){
//       ele+=32;  //
//     }
//   }
// }
// void Step2(string &s){
//   string tmp;
//   tmp.reserve(s.size());
//   for(auto& ele: s){
//     if(ele>='a'&&ele<='z'){
//       tmp.push_back(ele);
//     }else if(ele>='0'&&ele<='9'){
//       tmp.push_back(ele);
//     }else if(ele=='.'||ele=='-'||ele=='_'){
//       tmp.push_back(ele);
//     }
//   }
//   s.swap(tmp);
// }
// void Step34(string& s){
//   string tmp;
//   tmp.reserve(s.size());
//   bool count(true);
//   for(auto& ele:s){
//     if(ele=='.'){
//       if(count){
//         continue;
//       }
//       count=true;
//     }else{
//       count=false;
//     }
//     tmp.push_back(ele);
//   }
//   if(tmp.back()=='.'){
//     s=tmp.substr(0,tmp.size()-1);
//   }else{
//     s.swap(tmp);
//   }
// }
// void Step5(string& s){
//   if(s.empty()){
//     s.push_back('a');
//   }
// }
// void Step6(string& s){
//   if(s.length()>15){
//     if(s[14]=='.'){
//       s=s.substr(0,14);
//     }else{
//       s=s.substr(0,15);
//     }
//   }
// }
// void Step7(string& s){
//   int len=s.length();
//   char tmp=s.back();
//   for(;len<3;len++){
//     s.push_back(tmp);
//   }
// }
// string solution(string new_id) {
//   string answer = "";
// //1
//   for(auto& ele:new_id){
//     if(ele>='A'&&ele<='Z'){
//       ele+=32;  //
//     }
//   }
// //2
//   string tmp;
//   tmp.reserve(new_id.size());
//   for(auto& ele: new_id){
//     if(ele>='a'&&ele<='z'){
//       tmp.push_back(ele);
//     }else if(ele>='0'&&ele<='9'){
//       tmp.push_back(ele);
//     }else if(ele=='.'||ele=='-'||ele=='_'){
//       tmp.push_back(ele);
//     }
//   }
//   new_id.swap(tmp);
// //34
//   tmp.clear();
//   bool count(true);
//   for(auto& ele:new_id){
//     if(ele=='.'){
//       if(count){
//         continue;
//       }
//       count=true;
//     }else{
//       count=false;
//     }
//     tmp.push_back(ele);
//   }
//   if(tmp.back()=='.'){
//     new_id=tmp.substr(0,tmp.size()-1);
//   }else{
//     new_id.swap(tmp);
//   }
// //5
//   if(new_id.empty()){
//     new_id.push_back('a');
//   }
// //6
//   if(new_id.length()>15){
//     if(new_id[14]=='.'){
//       new_id=new_id.substr(0,14);
//     }else{
//       new_id=new_id.substr(0,15);
//     }
//   }
// //7
//   int len=new_id.length();
//   char tmpC=new_id.back();
//   for(;len<3;len++){
//     new_id.push_back(tmpC);
//   }
//   answer.swap(new_id);
//   return answer;
// }