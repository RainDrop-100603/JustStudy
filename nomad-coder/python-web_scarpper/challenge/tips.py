
'''
  매개변수에  default를 사용할 수 있다.
  ele in list 
    if ele in list: 포함 여부를 True, False로 반환
    for ele in list: list의 원소를 ele로 반환
  pass
    아무련 동작을 하지 않고 넘어간다. 프로그래머에게 아무런 내용이 없다고 보여주는 용도 
  if type(ele) is not dict:
    dict, list 와 같은 자료형을 그대로 써서 type과 비교 가능
  str(input("Do you want to start over? y/n ")).lower()
    input을 str로 변형함으로서, 동시에 여러 함수들을 적용했다.
    input시 메시지를 표현할 수 있다.
  url = f"http://{url}"
    위와 같은 방식으로 string을 표현할 수도 있다.
    생각해보면 원래도 str1="blabla" 와 같이 표현했으니 당연하긴 하다.
  print(url,"is up!")
    또다른 출력방법
  def로 정의된 함수만 실행함(나는 반복문을 함수로 만들지 않았음)
    c++과 달리 main에서만 실행되는 것은 아니지만, 함수를 통해 실행하는것이 당연히 더 좋다.
  bolierplate
    미리 구현해 놓은 함수, python의 module, c++의 library등은 boilerplate를 모아놓은 것이라고 보면 된다.
  rows = table.find_all("tr")[1:]
    0번째 생략하고 가져오기
  if name and code:
    name이나 code가 비어있으면 실행되지 않음
  name.capitalize()
    첫문자 대문자
  try:
    choice = int(input("#: "))
      에러가 나면 except로 가는 것이므로, 아예 input부터 try에 넣어버림
  for index, country in enumerate(countries):
    print(f"#{index} {country['name']}")
      enumerate: idx와 element tuple형태로 반환한다.
        for tmp in enumerate(list) -> tmp = (index, ele)
        for idx,tmp in enumerate(list) -> idx = index, tmp = ele
'''