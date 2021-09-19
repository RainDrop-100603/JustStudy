import requests
from bs4 import BeautifulSoup

INDEED_URL="https://kr.indeed.com/jobs?limit=50&q="
INDEED_VIEWJOB="https://kr.indeed.com"

'''
get job about keyward(ex: python, java, ...) from indeed.com

all_job=[job1_dict,job2_dict]
job1_dict={
  "title":title,
  "company":company,
  "location":location,
  "introduction":introduction,
  "date":date
  "link":link
}
'''

def get_maxpage(keyward):
  #start가 전체 갯수보다 크면, 제일 마지막 페이지로 이동하는것 이용 
  req=requests.get(f"{INDEED_URL}{keyward}&start=100000")
  soup=BeautifulSoup(req.text,"html.parser")
  pagination=soup.find("ul",{"class":"pagination-list"}).find_all("li")
  pages=[]
  for page in pagination:
    pages.append(page.text)
  return int(pages[-1])

def get_jobs(keyward,page):
  req=requests.get(f"{INDEED_URL}{keyward}&start={page*50}")
  soup=BeautifulSoup(req.text,"html.parser")
  jobcard_list=soup.find_all("div",{"class":"jobsearch-SerpJobCard"})
  job_list=[]
  for jobcard in jobcard_list:
    company=jobcard.find("span",{"class":"company"})
    if company is not None:
      company=company.text.replace("\n","")
    job={
      "title":jobcard.find("h2",{"class":"title"}).text.replace("\n",""),
      "company":company,
      "location":jobcard.find("span",{"class":"location"}).text.replace("\n",""),
      "introduction":jobcard.find("div",{"class":"summary"}).text.replace("\n",""),
      "date":jobcard.find("span",{"class":"date"}).text,
      "link":INDEED_VIEWJOB+jobcard.find("h2",{"class":"title"}).find("a")["href"]
    }
    job_list.append(job)
  return job_list

def indeed_jobs(keyward=""):
  maxpage=get_maxpage(keyward)
  all_jobs=[]
  #all_jobs.extend(get_jobs(keyward,0))#for test
  for page in range(0,maxpage):
    all_jobs.extend(get_jobs(keyward,page))
    print(f"{keyward} job from indeed page{page+1} is finished")
  return all_jobs
