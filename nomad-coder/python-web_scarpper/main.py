# this is backup of https://replit.com/@RainDrop97/NiftyHotpinkDeveloper#indeed.py

import requests
from bs4 import BeautifulSoup

INDEED_URL="https://kr.indeed.com/%EC%B7%A8%EC%97%85?q=python&limit=50"

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
  jobCards= []
  for soup in pages_soup:
    jobcard=soup.find("div",{"class":"jobsearch-SerpJobCard"})
    jobCards.append(jobcard)
  return jobCards

def extract_test_soup():
  result=requests.get(INDEED_URL)
  soup=BeautifulSoup(result.text,"html.parser")
  JobCards=soup.find_all("div",{"class":"jobsearch-SerpJobCard"})
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
    print(f"===title: {str(title)},    company: {str(company)}")
  return soup


# def tmp(soup:BeautifulSoup):
#   JobCards=soup.find_all("div",{"class":"jobsearch-SerpJobCard"})
#   for jobcard in JobCards:
#     title=jobcard.find("h2",{"class":"title"}).find("a")["title"]
#     company=jobcard.find("div",{"class":"sjc1"}).find("div").find("span").string
#     print(title)
#     print(company)
