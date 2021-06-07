const toDo_Container=document.querySelector(".js-toDo"),
  toDo_form=toDo_Container.querySelector("form"),
  toDo_input=toDo_form.querySelector("input"),
  toDo_ul=toDo_Container.querySelector("ul");

const LS_TODOLIST = "todo-list";

const toDoList=[];

function addToDo(inputObject){
  const li=document.createElement("li");
  const delBtn=document.createElement("button");
  delBtn.innerText="❌";
  const span=document.createElement("span");
  span.innerText=inputObject.text;
  li.id=inputObject.id;
  li.appendChild(span);
  li.appendChild(delBtn);
  toDo_ul.appendChild(li);
  toDoList.push(inputObject);
}

function handleSubmit(event){
  event.preventDefault();
  const inputObject={
    text:toDo_input.value,
    id:toDoList.length
  };
  addToDo(inputObject);
  localStorage.setItem(LS_TODOLIST,JSON.stringify(toDoList));
  toDo_input.value="";
}

function loadToDOList(){
  const loadedToDoList=localStorage.getItem(LS_TODOLIST);
  if(loadedToDoList){
    parsedToDoList=JSON.parse(loadedToDoList);
    parsedToDoList.forEach(addToDo);
  }
}

function init(){
  loadToDOList(); 
  toDo_form.addEventListener("submit",handleSubmit);
}

init();


