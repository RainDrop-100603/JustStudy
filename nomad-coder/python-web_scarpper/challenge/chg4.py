import requests
import os

#참고할 점
'''
  str(input("Do you want to start over? y/n ")).lower()
    input을 str로 변형함으로서, 동시에 여러 함수들을 적용했다.
    input시 메시지를 표현할 수 있다.
  url = f"http://{url}"
    위와 같은 방식으로 string을 표현할 수도 있다.
    생각해보면 원래도 str1="blabla" 와 같이 표현했으니 당연하긴 하다.
  print(url,"is up!")
    또다른 출력방법
'''

#my
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

#sol
def restart():
  answer = str(input("Do you want to start over? y/n ")).lower()
  if answer == "y" or answer =="n":
    if answer == "n":
        print("k. bye!")
        return
    elif answer == "y":
      main()
  else:
    print("That's not a valid answer")
    restart()

def main():
  os.system('clear')
  print("Welcome to IsItDown.py!\nPlease write a URL or URLs you want to check. (separated by comma)")
  urls = str(input()).lower().split(",")
  for url in urls:
    url = url.strip()
    if "." not in url:
      print(url, "is not a valid URL.")
    else:
      if "http" not in url:
        url = f"http://{url}"
      try:
        request = requests.get(url)
        if request.status_code == 200:
          print(url,"is up!")
        else:
          print(url, "is down!")
      except:
          print(url, "is down!")
  restart()

main()