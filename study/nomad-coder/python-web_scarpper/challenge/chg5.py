import os
import requests
from bs4 import BeautifulSoup

os.system("clear")
url = "https://www.iban.com/currency-codes"

'''
참고할 점
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
'''

#my
def extract_currency_code():
  result=requests.get(url)
  soup=BeautifulSoup(result.text,"html.parser")
  countries=soup.find('tbody').find_all('tr')
  country_dict={}
  idx=0
  for country in countries:
    country=str(country.text).split('\n')
    if country[2] != 'No universal currency':
      country_dict[idx]=[country[1],country[3]]
      idx+=1
  return country_dict

def print_country_code(country_dict):
  print("Hello, please select a country by number: ")
  for idx in country_dict:
    print(f"# {idx} {country_dict[idx][0]}")

def get_currency_code(country_dict):
  print_country_code(country_dict)
  while True:
    input_idx=input("#: ")
    try:
      idx=int(input_idx)
      if idx in country_dict:
        print(f"You chose {country_dict[idx][0]}")
        print(f"The currency code is {country_dict[idx][1]}")
        break
      else:
        print("Choose a number from the list.")
    except:
      print("That wasn't a number.")

country_dict=extract_currency_code()
get_currency_code(country_dict)




#sol
countries = []

request = requests.get(url)
soup = BeautifulSoup(request.text, "html.parser")

table = soup.find("table")
rows = table.find_all("tr")[1:]

for row in rows:
  items = row.find_all("td")
  name = items[0].text
  code =items[2].text
  if name and code:
    if name != "No universal currency":
      country = {
        'name':name.capitalize(),
        'code': code
      }
      countries.append(country)


def ask():
  try:
    choice = int(input("#: "))
    if choice > len(countries):
      print("Choose a number from the list.")
      ask()
    else:
      country = countries[choice]
      print(f"You chose {country['name']}\nThe currency code is {country['code']}")
  except ValueError:
    print("That wasn't a number.")
    ask()


print("Hello! Please choose select a country by number:")
for index, country in enumerate(countries):
  print(f"#{index} {country['name']}")

ask()
