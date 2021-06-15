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

function todo_displayElement(id,value,target){
  console.log(id,value,target);
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