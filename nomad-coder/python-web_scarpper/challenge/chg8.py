import os
import csv
import requests
from bs4 import BeautifulSoup

os.system("clear")
alba_url = "http://www.alba.co.kr"

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

def extract_jobs(link):
  req=requests.get(link)
  soup=BeautifulSoup(req.text,"html.parser")
  job_list=[]
  jobs=soup.find("tbody").find_all('tr')
  for job in jobs:
    if str(job['class']) =='summaryView':
      continue
    try:
      times=job.find('span',{'class':'time'}).text
    except:
      times=job.find('span',{'class':'consult'}).text
    ele={
      'location':job.find('td',{'class':'local'}).text,
      'title':job.find('span',{'class':'company'}).text,
      'time':times,
      'pay':job.find('td',{'class':'pay'}).text,
      'date':job.find('td',{'class':'regDate'}).text
    }
    print(ele)
  return job_list

def make_csv_from_list(name,dict_in_list):
  file=open(f'{name}.csv',mode='w')
  writer=csv.writer(file)
  writer.writerow(dict_in_list[0].keys())
  for dict in dict_in_list:
    writer.writerow(dict.values())
  file.close()

# brand_list=extract_brands()
# for brand in brand_list:
#   jobs=extract_jobs(brand['link'])
#   make_csv_from_list(brand['name'],jobs)

extract_jobs("http://hyundaidept.alba.co.kr/job/brand/")