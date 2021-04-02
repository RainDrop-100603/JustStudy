import os
import requests
from bs4 import BeautifulSoup

os.system("clear")
url = "https://www.iban.com/currency-codes"

'''
참고할 점
  bolierplate
    미리 구현해 놓은 함수, python의 module, c++의 library등은 boilerplate를 모아놓은 것이라고 보면 된다.
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
    idx+=1

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