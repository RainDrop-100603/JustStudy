/*
  ver1: basic
  ver2: basic, just add later
  ver3: structure optimize, if you want to add task, just add task_name to TODO_tasks
  ver4: structure optimize, if yoe want to use icon, just add task_icon to TODO_icon
  ver5: structure optimize, you can freely change the task name
  ver6: structure optimize, remove TODO_icon, just use one object
*/ 

const todoContainer=document.querySelector(".js-todo");

//key of localStorage
const TODO_LS_LIST="todo-list";

//if you want to add task, add name to here
//if you want to make Btn, add Btn to todo_displayElement function
const TODO_tasks=["pending","later","finished"];
const TODO_icon={
  pending:"⌛",
  later:"🟢",
  finished:"🏁"
}

const TODO_list={}

function todo_saveToLocal(){
  localStorage.setItem(TODO_LS_LIST,JSON.stringify(TODO_list));
}

function todo_loadFromLocal(){
  const tmpObj=JSON.parse(localStorage.getItem(TODO_LS_LIST));
  if(tmpObj){
    TODO_tasks.forEach(ele => TODO_list[ele]=tmpObj[ele]);
  }
}

function todo_handleBtn(event,target){
  const li=event.target.parentElement; 
  const fromUl=li.parentElement;
  //remove
  fromUl.removeChild(li);
  const fromTask=fromUl.className.substring(5); //remove todo-
  const id=li.id;
  const value=li.querySelector("span").innerText;
  delete TODO_list[fromTask][id];
  //add to target ul (if exist)
  if(target){
    const targetTask=target.substring(5);
    TODO_list[targetTask][id]=value;
    todo_displayElement(id,value,target);
  }
  todo_saveToLocal();
}

function todo_makeBtn(target){
  const button=document.createElement("button");
  if(target){
    button.innerText=TODO_icon[target.slice(5)];
  }else{
    button.innerText="❌";
  }
  button.addEventListener("click",function(event){todo_handleBtn(event,target)});
  return button;
}

function todo_displayElement(id,value,property){
  const ul=todoContainer.querySelector("."+property);
  const li=document.createElement("li");
  const span=document.createElement("span");
  li.id=id; span.innerText=value; 
  li.appendChild(span); 
  //makeBtn
  if(property=="todo-pending"){
    li.appendChild(todo_makeBtn("todo-finished")); //finishedBtn
    li.appendChild(todo_makeBtn("todo-later"));  //laterBtn
  }  
  if(property=="todo-later"){
    li.appendChild(todo_makeBtn("todo-pending")); //nowBtn
  }  
  if(property=="todo-finished"){
    li.appendChild(todo_makeBtn("todo-pending"));  //restoreBtn
  }  
  li.appendChild(todo_makeBtn(null)); //delBtn
  //append to html
  ul.appendChild(li);
}
  
function todo_display(){
  TODO_tasks.forEach(function(taskName){
    obj=TODO_list[taskName];
    for([id,value] of Object.entries(obj)){
      todo_displayElement(id,value,"todo-"+taskName);
    }
  });
}

function todo_handleSubmit(event){
  event.preventDefault();
  const inputValue=event.target.querySelector("input").value;
  event.target.querySelector("input").value="";
  //save to list
  const newID=String(new Date());
  TODO_list.pending[newID]=inputValue;
  todo_saveToLocal();
  //display a element
  todo_displayElement(newID,inputValue,"todo-pending");
}

function todo_buildEachHtml(listName){
  const listNameCapital=TODO_icon[listName]+listName.charAt(0).toUpperCase() + listName.slice(1);
  const ul=document.createElement("ul"); ul.classList.add("todo-"+listName);
  const span=document.createElement("span"); span.innerHTML=`<strong>${listNameCapital}</strong>`;
  todoContainer.appendChild(span); todoContainer.appendChild(ul);
}

function todo_buildBase(){
  //build todo-list base
  TODO_tasks.forEach(ele => TODO_list[ele]={}); 
  //build input
  const input=document.createElement("input"); input.type="text"; input.placeholder="to do task";
  const form=document.createElement("form"); form.addEventListener("submit",todo_handleSubmit);
  form.appendChild(input); todoContainer.appendChild(form);
  //build pending task, finished task
  TODO_tasks.forEach(ele => todo_buildEachHtml(ele));
}

function todo_init(){
  todo_buildBase();
  todo_loadFromLocal();
  todo_display();
}

todo_init();