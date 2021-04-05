import os
import requests
from bs4 import BeautifulSoup
from babel.numbers import format_currency

os.system("clear")
url_currency_code = "https://www.iban.com/currency-codes"
url_exchange= "https://wise.com/gb/currency-converter/"

"""
Use the 'format_currency' function to format the output of the conversion
format_currency(AMOUNT, CURRENCY_CODE, locale="ko_KR" (no need to change this one))
"""
'''
def ask_country(text):
  print(text)
ask_country("\nWhere are you from? Choose a country by number.\n")
target_country = ask_country("\nNow choose another country.\n")
  기능은 같은데 출력되는 문구만 다를 경우, 출력되는 문구를 변수로 보내버려서 사용할 수 있다.
'''

#my

def extract_currency_code():
  result=requests.get(url_currency_code)
  soup=BeautifulSoup(result.text,"html.parser")
  countries=soup.find('tbody').find_all('tr')
  country_list=[]
  for ele in countries:
    ele=str(ele.text).split('\n')
    if ele[2] != 'No universal currency':
      country = {
        'name':ele[1].capitalize(),
        'code': ele[3]
      }
      country_list.append(country)
  return country_list

def print_country_code(country_list):
  for idx,country in enumerate(country_list):
    print(f"#{idx} {country['name']}")

def get_currency_code(country_list):
  try:
    idx=int(input("#: "))
    if idx < len(country_list) and idx >= 0:
      country=country_list[idx]
      print(f"{country['name']}")
      return country['code']
    else:
      print("Choose a number from the list.")
  except:
    print("That wasn't a number.")
  return get_currency_code(country_list)

def currency_exchange(currency_from,currency_to):
  #get cost
  while True:
    try:
      cost=int(input(f"\nHow many {currency_from} do you want to convert to {currency_to}?\n"))
      break
    except:
      print("That wasn't a number.")
  #get soup
  result=requests.get(f"{url_exchange}{currency_from.lower()}-to-{currency_to.lower()}-rate?amount={cost}")
  soup=BeautifulSoup(result.text,"html.parser")
  try:
    exchange_rate=float(soup.find("h3",{'class':'cc__source-to-target'}).find('span',{'class':'text-success'}).text)
  except:
    print(f"Oops! we can't exchange {currency_from} or {currency_to}")
    return
  cost_exchanged=cost*exchange_rate
  #print
  print(format_currency(cost, currency_from, locale="ko_KR"), "is", format_currency(cost_exchanged, currency_to, locale="ko_KR"))

def CurrencyConverter():
  country_list=extract_currency_code()
  #get country code
  print("Welcome to CurrencyConvert PRO 2021\n")
  print_country_code(country_list)
  print('\nWhere are you from? Choose a country by a number.\n')
  currency_from=get_currency_code(country_list)
  print('\nNow choose another country.\n')
  currency_to=get_currency_code(country_list)
  #exchange
  currency_exchange(currency_from,currency_to)

CurrencyConverter()


#sol
code_url = "https://www.iban.com/currency-codes"
currency_url = "https://transferwise.com/gb/currency-converter/"


countries = []

codes_request = requests.get(code_url)
codes_soup = BeautifulSoup(codes_request.text, "html.parser")

table = codes_soup.find("table")
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


def ask_country(text):
  print(text)
  try:
    choice = int(input("#: "))
    if choice > len(countries):
      print("Choose a number from the list.")
      return ask_country(text)
    else:
      print(f"{countries[choice]['name']}")
      return countries[choice]
  except ValueError:
    print("That wasn't a number.")
    return ask_country(text)


def ask_amount(a_country, b_country):
  try:
    print(f"\nHow many {a_country['code']} do you want to convert to {b_country['code']}?")
    amount = int(input())
    return amount
  except ValueError:
    print("That wasn't a number.")
    return ask_amount(a_country, b_country)
  


print("Welcome to CurrencyConvert PRO 2000\n")
for index, country in enumerate(countries):
  print(f"#{index} {country['name']}")

user_country = ask_country("\nWhere are you from? Choose a country by number.\n")
target_country = ask_country("\nNow choose another country.\n")


amount = ask_amount(user_country, target_country)

from_code = user_country['code']
to_code = target_country['code']

currency_request = requests.get(f"{currency_url}{from_code}-to-{to_code}-rate?amount={amount}")
currency_soup = BeautifulSoup(currency_request.text, "html.parser")
result = currency_soup.find("input", {"id":"cc-amount-to"})
if result:
  result = result['value']
  amount = format_currency(amount, from_code, locale="ko_KR")
  result = format_currency(result, to_code, locale="ko_KR")
  print(f"{amount} is {result}")