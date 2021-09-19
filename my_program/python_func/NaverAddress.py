import requests,csv
from bs4 import BeautifulSoup

# csv에서 지명을 추출하고, naver에서 지명을 검색하여 주소를 가져와 다시 csv에 저장한다.
# 지명은 csv파일의 첫번째 행이다.
# 주소는 해당 csv파일의 두번째 행에 저장한다.
# 주소를 찾지 못할경우 None을 반환한다, 입력 데이터를 적절히 수정하자.

NAVER_SEARCH_URL = "https://search.naver.com/"
NAVER_SEARCH_URL2 = "https://search.naver.com/search.naver?where=nexearch&sm=top_hty&fbm=1&ie=utf8&query="

HEADERS_DEFAULT = {
    'User-Agent':
        'Mozilla/5.0 (Macintosh; Intel Mac OS X 10_9_3) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/35.0.1916.47 '
        'Safari/537.36 '
}


def extract_address(keyward):
    req = requests.get(NAVER_SEARCH_URL2 + keyward, headers=HEADERS_DEFAULT)
    soup = BeautifulSoup(req.text, "html.parser")
    try:
        address = soup.find("span", {"class": "txt_ellipsis"}).text
    except:
        address="None"
    return address

def get_csv_to_list(filename):
    f=open(filename,"r")
    reader=csv.reader(f)
    data=list(reader)
    return data

def make_csv_from_list(filename,lists):
    f=open(filename,"w",newline="\n")
    writer=csv.writer(f)
    writer.writerows(lists)
    f.close()

def test_func(filename):
    keywards = get_csv_to_list(filename)
    address_list = []
    for ele in keywards:
        keyward = ele[0]
        address_list.append([keyward,keyward])
    make_csv_from_list(filename, address_list)
    print("test finished!!")

def main_func(filename):
    keywards=get_csv_to_list(filename)
    address_list=[]
    for ele in keywards:
        keyward=ele[0]
        address_list.append([keyward,extract_address(keyward)])
    make_csv_from_list(filename,address_list)
    print("extract finished!!")

test_func("address.csv")