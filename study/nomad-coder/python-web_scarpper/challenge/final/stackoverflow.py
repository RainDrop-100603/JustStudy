import requests
from bs4 import BeautifulSoup

SO_URL="https://stackoverflow.com"

'''
get job about keyward(ex: python, java, ...) from stackoverflow.com

all_job=[job1_dict,job2_dict]
job1_dict={
  "title":title,
  "company":company,
  "location":location,
  "introduction":introduction,
  "date":date,
  "link":link
}
'''

def get_maxpage(keyward):
  result=requests.get(f"{SO_URL}/jobs?r=true&q={keyward}")
  soup=BeautifulSoup(result.text,"html.parser")
  pagination=soup.find("div",{"class":"s-pagination"}).find_all("span")
  pages=[]
  for page in pagination:
    pages.append(page.text)
  return int(pages[-2])
  
def get_jobs(keyward,page):
  req=requests.get(f"{SO_URL}/jobs?r=true&q={keyward}&pg={page+1}")
  soup=BeautifulSoup(req.text,"html.parser")
  jobcard_list=soup.find_all("div",{"class":"grid--cell fl1"})
  job_list=[]
  for jobcard in jobcard_list:
    introduction_list=jobcard.find("div",{"class":"ps-relative"}).find_all('a')
    introduction="develop tool:"
    for info in introduction_list:
      introduction+=f" [{info.text}]"
    job={
      "title":jobcard.find("h2").text.strip(),
      "company":jobcard.find("h3").find("span",{"class":""}).text.strip(),
      "location":jobcard.find("h3").find("span",{"class":"fc-black-500"}).text.strip(),
      "introduction":introduction,
      "date":jobcard.find("ul",{"class":"mt4"}).find("li").text,
      "link":SO_URL+jobcard.find("h2").find("a")["href"]
    }
    job_list.append(job)
  return job_list

def SO_jobs(keyward):
  max_page=get_maxpage(keyward)
  all_jobs=[]
  #all_jobs.extend(get_jobs(keyward,0))#for test
  for page in range(0,max_page):
    all_jobs.extend(get_jobs(keyward,page))
    print(f"keyward: {keyward}, website: stackoverflow, page: {page}, extracted")
  return all_jobs
