from flask import Flask, render_template
app = Flask('SuperScrapper')

#/ 라는 경로(route)에 들어가면, 이 page는 home라 이름짓고, Hello World를 표시한다 
# @ 는 데코레이터를 의미하는데, 데코레이터는 바로 아래의 함수를 찾아 꾸며주는 역할을 한다. 함수가 아닌 다른것이 오면 안된다.
# 아래와 같은 경우, '/'로 접속요청이 들어오면, home 함수를 실행하는 것이다.
# 172.18.0.1 - - [06/Apr/2021 01:46:38] "GET /contact HTTP/1.1" 200 - 와 같이 기록이남는다.
#render_template 는, templates 폴더에서 html을 찾는다.
@app.route('/')
def home():
  return render_template('potato.html')
'''
@app.route('/error')
this="is error"
'''

#Dynamic URL
#placeholder: < > 
@app.route('/<username>')
def contact(username):
  return f'Your name is {username}'

app.run(host='0.0.0.0', port=8080)
# repl.it 환경에 있으므로, host를 '0,0,0,0'으로 설정 
# / 는 웹사이트의 root를 의미한다(약속같은 것인듯), ex: google.com == google.com/