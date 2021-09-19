# this is backup of https://replit.com/@RainDrop97/NiftyHotpinkDeveloper#indeed.py

import requests
from bs4 import BeautifulSoup

INDEED_URL="https://kr.indeed.com/jobs?q=python&limit=50"
INDEED_VIEWJOB="https://kr.indeed.com/viewjob?"

def extract_indeed_pageNum():
  max_page=1
  now_page=1
  while now_page <= max_page:  #마지막 page에서 대소관계 바뀜
    if now_page==max_page:
      result=requests.get(f"{INDEED_URL}&start={(now_page-1)*50}")
      soup=BeautifulSoup(result.text,"html.parser")
      pagination=soup.find("div",{"class":"pagination"})
      links=pagination.find_all('a')
      pages =[]
      for link in links:
        try:
          pages.append(int(link.string))
        except:
          continue
      max_page=pages[-1]
    now_page+=1
  return max_page+1

def extract_indeed_allPage_soup():
  now_page=1
  max_page=1
  pages_soup = []
  while now_page <= max_page:
    print(f"extract soup {now_page}")
    result=requests.get(f"{INDEED_URL}&start={(now_page-1)*50}")
    soup=BeautifulSoup(result.text,"html.parser")
    pages_soup.append(soup)
    #find max_page
    if now_page == max_page:
      pagination=soup.find("div",{"class":"pagination"})
      links=pagination.find_all('a')
      pages =[]
      for link in links:
        try:
          pages.append(int(link.string))
        except:
          continue
      max_page=pages[-1]
    now_page+=1
  return pages_soup

def get_jobCard_fromSoup(pages_soup:list):
  jobs_info= []
  idx=0
  for soup in pages_soup:
    print(f"get job_info: {idx}")
    idx+=1
    jobcard=soup.find("div",{"class":"jobsearch-SerpJobCard"})
    info=get_info_fromJobcard(jobcard)
    jobs_info.append(info)
  return jobs_info

def get_info_fromJobcard(jobcard):
  title=jobcard.find("h2",{"class":"title"}).find("a")
  if title.string is None:
    title=str.strip(title["title"])
  else:
    title=str.strip(title.string)
  company=jobcard.find("span",{"class":"company"})
  if company.find("a") is not None:
    company=str.strip(company.find("a").string)
  else:
    company=str.strip(company.string)
  location=jobcard.find("div",{"class":"recJobLoc"})["data-rc-loc"]
  job_id=jobcard["data-jk"]
  return {
    "title":title,
    "company":company,
    "location":location,
    "link":f"{INDEED_VIEWJOB}jk={job_id}"
    }

def extract_test_soup():
  result=requests.get(INDEED_URL)
  soup=BeautifulSoup(result.text,"html.parser")
  return soup

def extract_test_jobs(soup):
  JobCards=soup.find_all("div",{"class":"jobsearch-SerpJobCard"})
  jobs=[]
  for jobcard in JobCards:
    title=jobcard.find("h2",{"class":"title"}).find("a")
    if title.string is None:
      title=str.strip(title["title"])
    else:
      title=str.strip(title.string)
    company=jobcard.find("span",{"class":"company"})
    if company.find("a") is not None:
      company=str.strip(company.find("a").string)
    else:
      company=str.strip(company.string)
    location=jobcard.find("div",{"class":"recJobLoc"})["data-rc-loc"]
    job_id=jobcard["data-jk"]
    jobs.append({"title":title,"company":company,"location":location,"link":f"{INDEED_VIEWJOB}jk={job_id}"})
  return jobs

def indeed_test():
  test_soup=extract_test_soup()
  test_jobs=extract_test_jobs(test_soup)
  print(test_jobs)

def indeed_get_jobs():
  indeed_soups=extract_indeed_allPage_soup()
  indeed_info_jobs=get_jobCard_fromSoup(indeed_soups)
  return indeed_info_jobs