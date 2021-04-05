import csv

jobs=[{'name':'IU','company':'loen','location':'kr','popularity':'new'},
{'name':'IU','company':'EDAM','location':'world','popularity':'celebrity'}]

'''
open: 파일을 열어준다, 없으면 생성해서 연다.
mode:
  'w': 쓰기전용, 파일이 존재하면 내용을 비우고 연다.
  'r': 읽기전용, default
  'x': 새로운 파일을 생성, 이미 존재한다면 IOError 예외
  'a': Append모드, 파일이 존재하지 않으면 새로 생성(존재하면?)
  '+': 읽고 쓰기용으로 열기
  'b': binary mode로 열기
  't': text mode로 열기, default
'''

def save_to_file(jobs):
  file=open('jobs.csv',mode='w')
  writer=csv.writer(file)
  writer.writerow(["job","company","location","link"])
  for job in jobs:
    writer.writerow(job.values())
  print(file)

save_to_file(jobs)