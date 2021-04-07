from flask import Flask, render_template,request, redirect
from stackoverflow import SO_jobs
app = Flask('SuperScrapper')

db={}

@app.route('/')
def home():
  return render_template('potato.html')

@app.route('/report')
def contact():
  word=request.args.get("word")
  if word:
    word=word.lower()  
    if db.get(word):
      jobs=db.get(word)
    else:
      jobs=SO_jobs(word)
      db[word]=jobs
  else:
    return redirect("/")
  return render_template(
    'report.html',
    searchingBy=word,
    resultNum=len(jobs),
    jobs=jobs
  )

app.run(host='0.0.0.0')