const toDo_Container=document.querySelector(".js-toDo"),
  toDo_form=toDo_Container.querySelector("form"),
  toDo_input=toDo_form.querySelector("input"),
  toDo_ul=toDo_Container.querySelector("ul");

const LS_TODOLIST = "todo-list";

let toDoList=[];

function handleDel(event){
  const li=event.target.parentNode;
  toDo_ul.removeChild(li);
  toDoList=toDoList.filter(function(toDo){
    return toDo.id !== li.id;
  });
  console.log(toDoList);
  localStorage.setItem(LS_TODOLIST,JSON.stringify(toDoList));
}

function displayToDo(inputObject){
  const li=document.createElement("li");
  const delBtn=document.createElement("button");
  delBtn.innerText="❌";
  const span=document.createElement("span");
  span.innerText=inputObject.text;
  li.id=inputObject.id;
  li.appendChild(span);
  li.appendChild(delBtn);
  toDo_ul.appendChild(li);
  delBtn.addEventListener("click",handleDel);
}

function getID(){
  let len=toDoList.length;
  while(true){
    const newID=`toDo-${len}`;
    let overlap=false;
    toDoList.forEach(function(toDo){
      if(toDo.id === newID){
        overlap=true;
      }
    });
    if(!overlap){
      return newID;
    }
    len++;
  }
}

function handleSubmit(event){
  event.preventDefault();
  const inputObject={
    text:toDo_input.value,
    id:getID()
  };
  toDoList.push(inputObject);
  displayToDo(inputObject);
  localStorage.setItem(LS_TODOLIST,JSON.stringify(toDoList));
  toDo_input.value="";
}

function loadToDOList(){
  const loadedToDoList=localStorage.getItem(LS_TODOLIST);
  if(loadedToDoList){
    toDoList=JSON.parse(loadedToDoList);
    toDoList.forEach(displayToDo);
  }
}

function init(){
  loadToDOList(); 
  toDo_form.addEventListener("submit",handleSubmit);
}

init();


