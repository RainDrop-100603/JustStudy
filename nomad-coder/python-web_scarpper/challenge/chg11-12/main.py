import requests
from flask import Flask, render_template, request
from bs4 import BeautifulSoup

"""
When you try to scrape reddit make sure to send the 'headers' on your request.
Reddit blocks scrappers so we have to include these headers to make reddit think
that we are a normal computer and not a python script.
How to use: requests.get(url, headers=headers)
"""

headers = {'User-Agent': 'Mozilla/5.0 (Macintosh; Intel Mac OS X 10_9_3) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/35.0.1916.47 Safari/537.36'}


"""
All subreddits have the same url:
i.e : https://reddit.com/r/javascript
You can add more subreddits to the list, just make sure they exist.
To make a request, use this url:
https://www.reddit.com/r/{subreddit}/top/?t=month
This will give you the top posts in per month.
"""

db = {}

def get_data(subreddit):
  if db.get(subreddit) is None:
    req=requests.get(f"https://www.reddit.com/r/{subreddit}/top/?t=month", headers=headers)
    soup=BeautifulSoup(req.text,"html.parser")
    reddit_card=soup.find_all("div",{"class":"scrollerItem"},limit=6)
    print(f"extract {subreddit}")
    data_list=[]
    del(reddit_card[1])#del promotion 
    for card in reddit_card:
      ele={
        "upvote":card.find("div").text,
        "title":card.find("h3").text,
        "link":card.find("a",{"data-click-id":"body"})["href"],
        "keyward":f"r/{subreddit}"
      }
      data_list.append(ele)
    db[subreddit]=data_list
  return db[subreddit]

def number(upvote):
  try:
    vote=int(upvote)
  except:
    if upvote[-1] == 'k':
      vote=int(upvote[:-2])*1000
    elif  upvote[-1] == 'm':
      vote=int(upvote[:-2])*1000000
  return vote

subreddits = [
    "javascript",
    "reactjs",
    "reactnative",
    "programming",
    "css",
    "golang",
    "flutter",
    "rust",
    "django"
]

app = Flask("DayEleven")

@app.route('/')
def home():
  pass

@app.route('/read')
def read():
  data_list=[]
  keywards=""
  for subreddit in subreddits:
    is_on=request.args.get(subreddit)
    if is_on == "on":
      data_list.extend(get_data(subreddit))
    keywards+=f" {subreddit}"
  data_list=sorted(data_list,reverse=True,key=lambda item:number(item['upvote']))
  render_template("read.html",keywards=keywards,data_list=data_list)
  
app.run(host="0.0.0.0")

