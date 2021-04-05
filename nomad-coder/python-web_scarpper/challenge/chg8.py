import os
import csv
import math
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

def extract_max_page(link):
  req=requests.get(link)
  soup=BeautifulSoup(req.text,"html.parser")
  maxpage=soup.find('div',{'id':'NormalInfo'}).find("strong").text
  return math.ceil(int(maxpage.replace(",",""))/50)

def extract_all_pages(link):
  maxpage=extract_max_page(link)
  jobs=[]
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
  print(f"{brand['name']} is successfully saved")
