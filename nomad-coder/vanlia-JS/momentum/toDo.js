const toDo_Container=document.querySelector(".js-toDo"),
  toDo_form=toDo_Container.querySelector("form"),
  toDo_input=toDo_form.querySelector("input"),
  toDo_ul=toDo_Container.querySelector("ul");

const LS_TODOLIST = "todo-list";

function addToDo(inputValue){
  const li=document.createElement("li");
  const delBtn=document.createElement("button");
  delBtn.value="❌";
  const span=document.createElement("span");
  span.value=inputValue;
  li.appendChild(span);
  li.appendChild(delBtn);
  toDo_ul.appendChild(li);
}

function toDo_handleSubmit(event){
  event.preventDefault();
  const inputValue=toDo_input.value;
  addToDo(inputValue);
  toDo_input.value="";
}

function loadToDOList(){

}

function init(){
  //loadToDOList();
  toDo_form.addEventListener("submit",toDo_handleSubmit);
}

init();


