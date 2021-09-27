//해야할 것
노트북에서 virtual setting 다시하기

//아이디어
기능
    여러개의 todo_list 구현 
        todo_list는 stack과 같은 모습 
        각 todo_list는 사진 삽입 가능 
        todo_list의 각 todo는 제목/내용으로 구분 
    일정 calender 구현 
        주기적으로 돌아오는 일정, 시간표등을 구현함 
        통합 calender의 기초
    통합 calender 구현: 1개이상의 todo_list를 calender에 구현 
        선택한 todo_list들의 항목만 표시되도록 설정 가능 
            선택은 간편하게 
        calender에서 todo_list는 시간이 표시된 것들만 표기한다. 
        no-time이라는, 시간이 정해지지 않은 것들은 calender 우측에 todo_list 모습으로 추가한다. 
            todo_list는 합칠수도, 나눌수도(나눌경우 드래그나 버튼등을 통해 바꾸기)
            합칠경우 정렬은 기존 정렬을 따라가되, 우선순위가 같을경우 created_at기준 정렬 
        calender는 일단위, 주단위, 월단위 선택 가능 
            월단위: 그날 해야할 것의 개수만 해둠
            주단위: 시간별로 표기 가능, 제목으로 표기 
            일단위: 제목/내용 모두 표시  
        특정한 날 중요 체크 가능 

기타
    계정 별 todo_calender 구현

//구조

//required
    virtualization via pipenv 
    django