'''
order_by = request.args.get('order_by', 'popular')
  popular은 왜 request?
내 코드에서 중복된 부분을 삭제하는것도 나쁘진 않을듯
  코드가 간단해지지만 약간 읽기 어려워진다는 점은 있다.
db에 data를 가공하지 않고 바로 저장
  data가 작을경우 나쁘지 않은 선택으로 보임 
{% if comment.author == None%}
    [deleted]
  {% else %}
    <strong>{{comment.author}}:</strong>
    <p>{{comment.text | safe}}</p>
  {% endif %}
    api를 통해 가져온 데이ㅓㅌ가 잘 정리되어 있기 때문에, 추가적인 정리는 선택적으로 하면 된다.
      추가적인 정리: extract_data_index(or detail) 함수는 이미 정리된 데이터를 다시 정리하는 것
        저장공간이 부족하거나 데이터가 너무 크면 유용하다.
    dict에서 .을 통해 요소에 접근하는 것은 comment['text]와 같은 의미일까?
      html에서는 위와같이 사용해야 하는것이며, python에서는 적용되지 않는다.
    추가적인 정리 필요
'''


#my
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

#sol
import requests
from flask import Flask, render_template, request

base_url = "http://hn.algolia.com/api/v1"
new = f"{base_url}/search_by_date?tags=story"
popular = f"{base_url}/search?tags=story"

def make_detail_url(id):
  return f"{base_url}/items/{id}"

db = {}
app = Flask("DayNine")

@app.route("/")
def home():
  order_by = request.args.get('order_by', 'popular')
  if order_by not in db:
    print("Requesting")
    if order_by == 'popular':
      news = requests.get(popular)
    elif order_by == 'new':
      news = requests.get(new)
    results = news.json()['hits']
    db[order_by] = results
  results = db[order_by]
  return render_template("index.html", order_by=order_by, results=results)


@app.route("/<id>")
def detail(id):
  detail_request = requests.get(make_detail_url(id))
  result = detail_request.json()
  return render_template("detail.html",result=result)

app.run(host="0.0.0.0")