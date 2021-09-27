//해야할 것
노트북에서 virtual setting 다시하기
md파일 작성법 ? 
이것이 과연 장고와 맞는가? react가 적절하지 않은가? 

//아이디어
기능
    여러개의 todo_list 구현 
        todo_list는 stack과 같은 모습 
        각 todo_list는 사진 삽입 가능 
        todo_list의 각 todo는 제목/내용으로 구분 
        대기중, 하는중, 완료 로 구분 
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
            주단위: 시간별로 표기 가능, Shortcut: 제목으로 표기 
            일단위: 제목/내용 모두 표시  
        특정한 날 중요 체크 가능 
기타
    계정 별 todo_calender 구현
    다양한 login 
    email verify
    Search
        todolist, todo, schedule 검색 
    priority control: int범위에서 1단위 설정, 함수가 결정 
    shortcut: name도 길다고 생각될 때


//구조
    users
        Model
            User(AbstractUser)
                login_via (kakao, naver, email, ...)
        Func
            Login, Logout, SignUp,
    todos
        Model
            Todo
                ForeignKey: TodoList
                name: CharField
                description: TextField
                time_at:
                importance: BooleanField
                priority: IntegerField
                    Calculated by method
                done: BooleanField
            TodoList
                user: ForeignKey
                name: CharField
                description: TextField
                shortcut: CharField 
        Func
            Add/Update/Remove Todo, Add/Update/Remove TodoList, 
            priority control, todo/done control
    schedules
        BaseSchedule
            ForeignKey: ScheduleCalender
            name: CharField
            description: TextField
            time_begin: 
            time_end: 
        OneTimeSchedule(BaseSchedule)
            date: 
        DailySchedule(BaseSchedule)
            pass
        WeeklySchedule(BaseSchedule)
            day:
        MonthlySchedule(BaseSchedule)
            date:
        YearlySchedule(BaseSchedule)
            date:
    calenders
        BaseCalender
            OneToOne: User
        ScheduleCalender(BaseCalender)
        ToDoCalender(BaseCalender)
            ManyToManyField: TodoList
        TotalCalender(BaseCalender)
            추가바람
    search
        Search
//required
    virtualization via pipenv 
    django == version
    tailwind css == version 