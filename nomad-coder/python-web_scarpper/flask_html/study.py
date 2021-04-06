from flask import Flask, render_template,request, redirect
app = Flask('SuperScrapper')

#/ 라는 경로(route)에 들어가면, 이 page는 home라 이름짓고, Hello World를 표시한다 
# @ 는 데코레이터를 의미하는데, 데코레이터는 바로 아래의 함수를 찾아 꾸며주는 역할을 한다. 함수가 아닌 다른것이 오면 안된다.
# 아래와 같은 경우, '/'로 접속요청이 들어오면, home 함수를 실행하는 것이다.
# 172.18.0.1 - - [06/Apr/2021 01:46:38] "GET /contact HTTP/1.1" 200 - 와 같이 기록이남는다.
#render_template 는, templates 폴더에서 html을 찾는다.
#https://superscrapper.raindrop97.repl.co/report?word=tmp 와 같은 주소에서, /report 까지만 주소이다.?word=tmp&itsOkay ... 등 ?뒷부분은 query arguments, 주소에 영향을 주지 않는다.
#query arguments: ? 이후 뒷부분이며, 주소에 영향을 주지 않는다. &로 구분된다. key=value & key2=value, 
#request.args로 모든 arguments를 dict형태로 저장할 수 있다.
#request.args.get("key") 로 특정 key에 해당하는 value를 뽑아올 수 있다.
@app.route('/')
def home():
  return render_template('potato.html')
'''
@app.route('/error')
this="is error"
'''

#Dynamic URL
#placeholder: < > : <data>
@app.route('/placeholder/<test>')
def placeholder(test):
  return f"{test}"

#rendering: render_template를 통해 변수를 넘겨주면, html에서 해당 변수명에 해당하는 {{}}를 찾아서, 변수값을 할당해준다.
#rendering: html을 rendering해서 {{var}} 대신에 값을 할당해준다.
@app.route('/report')
def contact():
  word=request.args.get("word")
  if word:
    word=word.lower()  
  else:
    return redirect("/")
  return render_template('report.html',searchingBy=word, potato='sexy')

app.run(host='0.0.0.0', port=8080)
# repl.it 환경에 있으므로, host를 '0,0,0,0'으로 설정 
# / 는 웹사이트의 root를 의미한다(약속같은 것인듯), ex: google.com == google.com/