
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
    첫문자 대문자, 나머지 소문자
  try:
    choice = int(input("#: "))
      에러가 나면 except로 가는 것이므로, 아예 input부터 try에 넣어버림
  for index, country in enumerate(countries):
    print(f"#{index} {country['name']}")
      enumerate: idx와 element tuple형태로 반환한다.
        for tmp in enumerate(list) -> tmp = (index, ele)
        for idx,tmp in enumerate(list) -> idx = index, tmp = ele
  country = {
        'name':name.capitalize(),
        'code': code
      }
      countries.append(country)
        list에 dict를 저장, 추후 ele 수정에도 용이하다.
  rows = tbody.find_all("tr", {"class": ""})
    class가 비어있으면, 위와같이 찾을 수 있다. ( <tr class> </tr> 과 같은 경우 )
  time = time.text.replace(u'\xa0', ' ')
    u"unicode" 는, unicode 문자열을 의미함, UTF-8
      python3부터는 기본 문자열이 유니코드이므로 사용하지 않아도 된다.
  if link and name
    Nonetype을 걸러주는구문. try, except 보다 나을지도 
  try except vs if else
    https://stackoverflow.com/questions/7604636/better-to-try-something-and-catch-the-exception-or-test-if-its-possible-first
    https://yesarang.tistory.com/371
      try-except가 이해하기 훨씬간편한다
      if-else의 경우 if문을 모든 경우에 확인해야하며, 경우에 따라 여러 조건을 확인해야 해 if문이 여러번 사용되거나 길어질 수 있다.->속도 감소
      except가 발생하지 않을경우, try except가 더 빠르며, except가 발생한경우(예외처리)는 if else가 더 빠르다.
        except가 지나치게 많이 발생하는 경우가 아니라면, try-except의 사용이 보기도 편하고 좋을듯 하다.  
  order_by = request.args.get('order_by', 'popular')
    popular은 왜 request?
  내 코드에서 중복된 부분을 삭제하는것도 나쁘진 않을듯
    코드가 간단해지지만 약간 읽기 어려워진다는 점은 있다.
  db에 data를 가공하지 않고 바로 저장
    data가 작을경우 나쁘지 않은 선택으로 보임 
  {% if comment.author == None%}
      [deleted]
    {% else %}
      <strong>{{comment.author}}:</strong>
      <p>{{comment.text | safe}}</p>
    {% endif %}
      api를 통해 가져온 데이ㅓㅌ가 잘 정리되어 있기 때문에, 추가적인 정리는 선택적으로 하면 된다.
        추가적인 정리: extract_data_index(or detail) 함수는 이미 정리된 데이터를 다시 정리하는 것
          저장공간이 부족하거나 데이터가 너무 크면 유용하다.
      dict에서 .을 통해 요소에 접근하는 것은 comment['text]와 같은 의미일까?
        html에서는 위와같이 사용해야 하는것이며, python에서는 적용되지 않는다.
      추가적인 정리 필요
'''

def input_number(num_from='', num_to=''):
  #get the number [from,to)
  #get number
  try:
    num=int(input())
  except:
    print("That wasn't number")
    input_number(num_from,num_to)
  #range check
  if type(num_from) is str and type(num_to) is str:
    return num
  elif type(num_to) is str:
    if num >= num_from:
      return num
    else:
      print(f"input a number in range [{num_from},inf)")
  elif type(num_from) is str:
    if num < num_to:
      return num
    else:
      print(f"input a number in range [-inf,{num_to})")
  else:
    if num_to <= num_from:
      print(f"Oops! the range [{num_from},{num_to}) is not valid, return -1.")
      return -1
    if num < num_to and num >= num_from:
      return num
    else:
      print(f"input a number in range [{num_from},{num_to})")
  input_number(num_from,num_to)
 