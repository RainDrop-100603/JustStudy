const todoContainer=document.querySelector(".js-todo");

const TODO_LS_LIST="todo-list";

const TODO_list={
  pending:{},
  finished:{}
}

function todo_saveToLocal(){
  localStorage.setItem(TODO_LS_LIST,JSON.stringify(TODO_list));
}

function todo_loadFromLocal(){
  const tmpObj=JSON.parse(localStorage.getItem(TODO_LS_LIST));
  if(tmpObj){
    TODO_list.pending=tmpObj.pending;
    TODO_list.finished=tmpObj.finished;
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

function todo_makeBtn(target,icon){
  const button=document.createElement("button");
  button.innerText=icon;
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
  if(property=="todo-pending"){li.appendChild(todo_makeBtn("todo-finished","✔"));}  //finishedBtn
  if(property=="todo-finished"){li.appendChild(todo_makeBtn("todo-pending","♻"));}  //restoreBtn
  li.appendChild(todo_makeBtn(null,"❌")); //delBtn
  //append to html
  ul.appendChild(li);
}
  
function todo_display(){
  for ([id,value] of Object.entries(TODO_list.pending)){
    todo_displayElement(id,value,"todo-pending");
  }
  for ([id,value] of Object.entries(TODO_list.finished)){
    todo_displayElement(id,value,"todo-finished");
  }
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

function todo_buildHtmlBase(){
  //build input
  const input=document.createElement("input"); input.type="text"; input.placeholder="to do task";
  const form=document.createElement("form"); form.addEventListener("submit",todo_handleSubmit);
  form.appendChild(input); todoContainer.appendChild(form);
  //build pending task, finished task
  const ulPending=document.createElement("ul"); ulPending.classList.add("todo-pending");
  const spanPending=document.createElement("span"); spanPending.innerHTML="<strong>Pending</strong>";
  todoContainer.appendChild(spanPending); todoContainer.appendChild(ulPending);
  const ulFinished=document.createElement("ul");ulFinished.classList.add("todo-finished");
  const spanFinished=document.createElement("span"); spanFinished.innerHTML="<strong>Finished</strong>";
  todoContainer.appendChild(spanFinished); todoContainer.appendChild(ulFinished);
}

function todo_init(){
  todo_buildHtmlBase();
  todo_loadFromLocal();
  todo_display();
}

todo_init();