from flask import Flask, render_template, request, redirect,send_file
from stackoverflow import SO_jobs
from remoteok import ROK_jobs
from weworkremotely import WWR_jobs
from makeCSV import make_csv_dict_in_list
"""
These are the URLs that will give you remote jobs for the word 'python'

https://stackoverflow.com/jobs?r=true&q=python
https://weworkremotely.com/remote-jobs/search?term=python
https://remoteok.io/remote-dev+python-jobs

Good luck!
"""

headers = {
    'User-Agent':
    'Mozilla/5.0 (Macintosh; Intel Mac OS X 10_9_3) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/35.0.1916.47 Safari/537.36'
}

db = {}

def get_data(keyward):
  if db.get(keyward) is None:
    data_list = []
    data_list.extend(SO_jobs(keyward))
    data_list.extend(WWR_jobs(keyward))
    data_list.extend(ROK_jobs(keyward))
    db[keyward] = data_list
  return db[keyward]


app = Flask("JobScrapper")


@app.route('/')
def home():
  return render_template("home.html")


@app.route('/read')
def read():
  try:
    keyward=request.args.get("keyward").lower()
    if not keyward:
      raise Exception
  except:
    return redirect("/")
  data_list=get_data(keyward)
  return render_template("read.html", result_num=len(data_list),keyward=keyward, data_list=data_list)

@app.route('/export')
def export():
  try:
    keyward=request.args.get("keyward").lower()
    if not keyward:
      raise Exception
  except:
    return redirect("/")
  get_data(keyward)
  make_csv_dict_in_list(get_data(keyward),f"{keyward}_jobs")
  return send_file(f"{keyward}_jobs.csv",mimetype='text/csv',as_attachment=True)

app.run(host="0.0.0.0")
