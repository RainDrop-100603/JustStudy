
#참고할 점
# 매개변수의 자료형을 정해줄 수 있다.
# ele in list 를 통해, ele가 list에 포함되는지 여부가 True, False로 반환된다.

#my
# def is_on_list(list,day):
#   try:
#     list.index(day)
#     return True
#   except ValueError:
#     return False
# def get_x(list,idx):
#   return list[idx]
# def add_x(list,day):
#   list.append(day)
# def remove_x(list,day):
#   list.remove(day)

#Solution
def is_on_list(a_list=[], word=""):
  return word in a_list

def get_x(a_list=[], index=0):
  return a_list[index]

def add_x(a_list=[], word=""):
  a_list.append(word)

def remove_x(a_list=[], word=""):
  a_list.remove(word)

# \/\/\/\/\/\/\  DO NOT TOUCH AREA  \/\/\/\/\/\/\ #

days = ["Mon", "Tue", "Wed", "Thu", "Fri", "Sat", "Sun"]

print("Is Wed on 'days' list?", is_on_list(days, "Wed"))

print("The fourth item in 'days' is:", get_x(days, 3))

add_x(days, "Sat")
print(days)

remove_x(days, "Mon")
print(days)


# /\/\/\/\/\/\/\ END DO NOT TOUCH AREA /\/\/\/\/\/\/\ #