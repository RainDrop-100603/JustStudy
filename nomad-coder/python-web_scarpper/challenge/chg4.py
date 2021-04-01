import requests
import os

def get_URL():
  print("Welcome to IsItDown.py!")
  print("Please write a URL or URLs you want to check. (separated by comma)")
  raw_str=input()
  list_str=raw_str.split(',')
  for ele in list_str:
    ele=ele.strip()
    if '.' not in ele:
      print(f"{ele} is not a valid URL.")
      continue
    if "http://" not in ele:
      ele="http://"+ele
    ele=ele.lower()
    try:
      requests.get(ele)
      print(f"{ele} is up!")
    except:
      print(f"{ele} is down!")

get_URL()
while True:
  print("Do you want to start over? y/n")
  ans=input()
  if(ans=='y'):
    os.system('clear')
    get_URL()
  elif(ans=='n'):
    print("k. Bye!")
    break
  else:
    print("That's not a valid answer")