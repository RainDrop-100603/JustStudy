import requests
from flask import Flask, render_template, request

base_url = "http://hn.algolia.com/api/v1"

# This URL gets the newest stories.
new = f"{base_url}/search_by_date?tags=story"

# This URL gets the most popular stories
popular = f"{base_url}/search?tags=story"

# This function makes the URL to get the detail of a storie by id.
# Heres the documentation: https://hn.algolia.com/api
def make_detail_url(id):
  return f"{base_url}/items/{id}"

def extract_data_index(url):
  req=requests.get(url)
  data=req.json()
  data_list=[]
  for idx in range(0,20):
    tmp_data=data['hits'][idx]
    ele={
      'title':tmp_data['title'],
      'url':tmp_data['url'],
      'points':tmp_data['points'],
      'author':tmp_data['author'],
      'objectID':f"/{tmp_data['objectID']}",
      'num_comments':tmp_data['num_comments']
    }
    data_list.append(ele)
  return data_list

def extract_data_detail(url):
  req=requests.get(url)
  raw_data=req.json()
  data_list=[]
  #parent
  ele={
    "author":raw_data['author'],
    "title":raw_data['title'],
    "points":raw_data['points'],
    "url":raw_data['url']
  }
  data_list.append(ele)
  #children
  children=raw_data['children']
  for data in children:
    author=data['author']
    text=data['text']
    if author is None:
      author="[deleted]"
      text=""
    ele={
      "author":author,
      "text":text
    }
    data_list.append(ele)
  return data_list

db = {}
app = Flask("DayNine")

@app.route('/')
def index():
  order_by=request.args.get("order_by")
  if order_by=="new":
    db_new=db.get("new")
    if db_new is None:
      db_new=extract_data_index(new)
      db["new"]=db_new
    return render_template("index.html",data_list=db_new,orderby="New")
  else:
    db_popular=db.get("popular")
    if db_popular is None:
      db_popular=extract_data_index(popular)
      db["popular"]=db_popular
    return render_template("index.html",data_list=db_popular,orderby="Popular")
  
@app.route('/<object_id>')
def detail(object_id):
  detail_url=make_detail_url(object_id)
  db_data=db.get(object_id)
  if db_data is None:
    db_data=extract_data_detail(detail_url)
    db[object_id]=db_data
  return render_template("detail.html",data_list=db_data)

app.run(host="0.0.0.0")

