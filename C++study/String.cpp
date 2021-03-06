/*
 * Banking System Ver 0.9
 * 작성자: rain
 * 내 용: 열혈 cpp OOP 단계별 프로젝트 
 */

//String Class 선언

#include "BankingCommonDec1.h"
#include "String.h"

String::String()
  :string(NULL),len(0){}
String::String(const char* str){
  len=strlen(str)+1;
  string=new char[len];
  strcpy(string,str);
}
String::String(const String& str){
  len=str.len;
  string=new char[len];
  strcpy(string,str.string);  
}
String& String::operator=(const String& str){
  delete[] string;
  len=str.len;
  string=new char[len];
  strcpy(string,str.string);
  return *this;
}
String::~String(){
  delete[] string;
}
String String::operator+(const String& str) const{
  int templen = len+str.len-1;
  char* tempstr = new char[templen];
  strcpy(tempstr,string);
  strcat(tempstr,str.string);

  String TempSTR(tempstr);

  delete[] tempstr;
  return TempSTR;
}
String& String::operator+=(const String& str){
  len=len+str.len-1;
  char* tmpStr = new char[len];
  strcpy(tmpStr,string);
  strcat(tmpStr,str.string);
  delete[] string;
  string = tmpStr;
  return *this;
}
bool String::operator==(const String& str) const{
  return strcmp(string,str.string)? false : true;
}
ostream& operator<<(ostream& os,const String& str){
  os<<str.string;
  return os;
}
istream& operator>>(istream& is,String& str){
  char temp[Constant::STRLENGTH];
  delete[] str.string;
  is>>temp;
  is.ignore();
  str.len=strlen(temp)+1;
  str.string=new char[str.len];
  strcpy(str.string, temp);
  return is;
}
