import requests
from bs4 import BeautifulSoup

'''
get job about keyward(ex: python, java, ...) from weworkremotely.com

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

WWR_URL="https://weworkremotely.com"
  
def get_jobs(keyward):
  req=requests.get(f"{WWR_URL}/remote-jobs/search?term={keyward}")
  soup=BeautifulSoup(req.text,"html.parser")
  jobcard_section=soup.find_all("section",{"class":"jobs"})
  job_list=[]
  for section in jobcard_section:
    jobcard_list=section.find_all("li")
    introduction=section.find("h2").find("a").text
    for jobcard in jobcard_list:
      dummy=jobcard["class"]
      if dummy and dummy[0]=="view-all":
        continue
      try:
        date__=jobcard.find("span",{"class":"date"}).text
      except:
        date__=jobcard.find("span",{"class":"featured"}).text
      job={
        "title":jobcard.find("span",{"class":"title"}).text,
        "company":jobcard.find("span",{"class":"company"}).text,
        "location":jobcard.find("span",{"class":"region"}).text,
        "introduction":introduction,
        "date":date__,
        "link":WWR_URL+jobcard.find("a")["href"]
      }
      job_list.append(job)    
  return job_list

def WWR_jobs(keyward):
  all_jobs=get_jobs(keyward)
  print(f"keyward: {keyward}, website: weworkremotely, page: 1, extracted")
  return all_jobs
