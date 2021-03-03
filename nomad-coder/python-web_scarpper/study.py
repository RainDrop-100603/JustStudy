python standard library
  파이썬에 대한 정보들
  https://docs.python.org/3/library/

type
  mutable(수정 가능한 것들) vs immutable(수정 불가능한 것들)
  var: int, float, str, bool, none(NULL과 유사)
    var 표기 약속
      camel case: 대분자를 이용하여 단어 구분 (superLongVar), js, c++ 
      snake case: "-" 를 이용하여 단어 구분 (super_long_var), py
  sequence type(열거형)
    list
      list=["var1","var2","var3","var4"]
      mutable sequence
    tuple
      tuple=("var1","var2","var3","var4")
      immutable sequence
  dictionary
    dict={"key1":value1,"key2":value2}
      key search: dict["key1"] -> value1
      append: dict["key3"]=value3
    value can be any type (or most type)

function
  built_in_functions
    var type change: var 형식 변환, var1(var2_name)
