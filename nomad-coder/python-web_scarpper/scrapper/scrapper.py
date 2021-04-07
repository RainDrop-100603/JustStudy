from indeed import indeed_jobs
from stackoverflow import SO_jobs
from make_csv import make_csv_dict_in_list

'''
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

job=input("what job: ")
jobs_list=[]
#jobs_list.extend(indeed_jobs(job))
#jobs_list.extend(SO_jobs(job))
make_csv_dict_in_list(jobs_list,"test")