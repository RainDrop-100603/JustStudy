import requests
from bs4 import BeautifulSoup

'''
get job about keyward(ex: python, java, ...) from remoteok.com

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

HEADERS_DEFAULT = {
    'User-Agent':
    'Mozilla/5.0 (Macintosh; Intel Mac OS X 10_9_3) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/35.0.1916.47 Safari/537.36'
}

ROK_URL="https://remoteok.io"
  
def get_jobs(keyward,headers):
  req=requests.get(f"{ROK_URL}/remote-dev+{keyward}-jobs",headers=headers)
  soup=BeautifulSoup(req.text,"html.parser")
  jobcard_list=soup.find_all("tr",{"class":"job"})
  job_list=[]
  for jobcard in jobcard_list:
    #remove closed 
    if jobcard.find("td",{"class":"company"}).find("span",{"class":"closed"}) is not None:
      continue
    #introduction
    introduction_list=jobcard.find("td",{"class":"tags"}).find_all('a')
    introduction="develop tool:"
    for info in introduction_list:
      tag=info.text.replace("\xa0","")
      introduction+=f" [{tag}]"
    #location
    try:
      location=jobcard.find("td",{"class":"company"}).find("div",{"class":"location"}).text
    except:
      location=None
    job={
      "title":jobcard.find("td",{"class":"company"}).find("h2",{"itemprop":"title"}).text,
      "company":jobcard.find("td",{"class":"company"}).find("h3",{"itemprop":"name"}).text,
      "location":location,
      "introduction":introduction,
      "date":jobcard.find("td",{"class":"time"}).find("time").text,
      "link":ROK_URL+jobcard.find("td",{"class":"source"}).find("a")["href"]
    }
    job_list.append(job)
  return job_list

def ROK_jobs(keyward,headers=HEADERS_DEFAULT):
  all_jobs=get_jobs(keyward,headers)
  print(f"keyward: {keyward}, website: remoteok, page: 1, extracted")
  return all_jobs
