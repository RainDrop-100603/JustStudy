import os
import csv
import math
import requests
from bs4 import BeautifulSoup

os.system("clear")
alba_url = "http://www.alba.co.kr"


'''
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
'''

def extract_brands():
  req=requests.get(alba_url)
  soup=BeautifulSoup(req.text,"html.parser")
  brand_list=[]
  brands=soup.find("div",{"id":"MainSuperBrand"}).find_all("li",{"class":"impact"})
  for brand in brands:
    ele={
      'link':brand.find('a')['href'],
      'name':brand.find('span',{'class':'company'}).text
    }
    brand_list.append(ele)
  return brand_list

def extract_max_page(link):
  req=requests.get(link)
  soup=BeautifulSoup(req.text,"html.parser")
  maxpage=soup.find('div',{'id':'NormalInfo'}).find("strong").text
  return math.ceil(int(maxpage.replace(",",""))/50)

def extract_all_pages(link):
  maxpage=extract_max_page(link)
  jobs=[]
  if "job/brand/" not in link:
    link=link+"job/brand/"
  for page in range(1,maxpage+1):
    req=requests.get(f"{link}?page={page}&pagesize=50")
    soup=BeautifulSoup(req.text,"html.parser")
    jobs.extend(soup.find("tbody").find_all('tr'))
  return jobs

def extract_jobs(link):
  jobs=extract_all_pages(link)
  job_list=[]
  for job in jobs:
    try:
      location=(job.find('td',{'class':'local'}).text).replace("\xa0", " ")
    except:
      continue
    try:
      times=job.find('span',{'class':'time'}).text
    except:
      times=job.find('span',{'class':'consult'}).text
    ele={
      'location':location,
      'title':job.find('span',{'class':'company'}).text,
      'time':times,
      'pay':job.find('td',{'class':'pay'}).text,
      'date':job.find('td',{'class':'regDate'}).text
    }
    job_list.append(ele)
  return job_list

def filename_valid_check(name):
  name=name.replace('\\','-')
  name=name.replace('/','-')
  name=name.replace(':','-')
  name=name.replace('*','-')
  name=name.replace('?','-')
  name=name.replace(':','-')
  name=name.replace('<','-')
  name=name.replace('>','-')
  name=name.replace('|','-')
  return name

def make_csv_from_list(name,dict_in_list):
  name=filename_valid_check(name)
  file=open(f'{name}.csv',mode='w')
  writer=csv.writer(file)
  if dict_in_list:
    writer.writerow(dict_in_list[0].keys())
    for dict in dict_in_list:
      writer.writerow(dict.values())
  else:
    writer.writerow(["there's no data"])
  file.close()

brand_list=extract_brands()
for brand in brand_list:
  print(f"{brand['name']} now begin")
  jobs=extract_jobs(brand['link'])
  make_csv_from_list(brand['name'],jobs)
  print(f"{brand['name']}'s {len(jobs)} jobs are successfully saved")

#sol
import os
import csv
import requests
from bs4 import BeautifulSoup

os.system("clear")


def write_company(company):
    file = open(f"{company['name']}.csv", mode="w")
    writer = csv.writer(file)
    writer.writerow(["place", "title", "time", "pay", "date"])
    for job in company["jobs"]:
      writer.writerow(list(job.values()))


alba_url = "http://www.alba.co.kr"

alba_request = requests.get(alba_url)
alba_soup = BeautifulSoup(alba_request.text, "html.parser")
main = alba_soup.find("div", {"id": "MainSuperBrand"})
brands = main.find_all("li", {"class": "impact"})
for brand in brands:
    link = brand.find("a", {"class": "goodsBox-info"})
    name = brand.find("span", {"class": "company"})
    if link and name:
        link = link["href"]
        name = name.text
        company = {'name': name, 'jobs': []}
        jobs_request = requests.get(link)
        jobs_soup = BeautifulSoup(jobs_request.text, "html.parser")
        tbody = jobs_soup.find("div", {"id": "NormalInfo"}).find("tbody")
        rows = tbody.find_all("tr", {"class": ""})
        for row in rows:
            local = row.find("td", {"class": "local"})
            if local:
                local = local.text.replace(u'\xa0', ' ')
            title = row.find("td", {"class": "title"})
            if title:
                title = title.find("a").find("span", {
                    "class": "company"
                }).text.strip()
                title = title.replace(u'\xa0', ' ')
            time = row.find("td", {"class": "data"})
            if time:
                time = time.text.replace(u'\xa0', ' ')
            pay = row.find("td", {"class": "pay"})
            if pay:
                pay = pay.text.replace(u'\xa0', ' ')
            date = row.find("td", {"class": "regDate"})
            if date:
                date = date.text.replace(u'\xa0', ' ')
            job = {
                "place": local,
                "title": title,
                "time": time,
                "pay": pay,
                "date": date
            }
            company['jobs'].append(job)
        write_company(company)