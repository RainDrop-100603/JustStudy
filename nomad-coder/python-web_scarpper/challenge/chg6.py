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
  get_currency_code(country_list)

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