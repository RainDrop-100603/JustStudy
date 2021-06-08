const TDL_Container=document.querySelector(".js-toDoList");
  TDL_form=TDL_Container.querySelector("form"),
  TDL_input=TDL_form.querySelector("input");
  // toDo_ul=toDo_Container.querySelector("ul");

//size of list
const LIST_SIZE=10000;
  //r
const TDL_name=["TDL-todo","TDL-finish"]; //name of group
const TDL_map=Map();  // name: data(map) of name



function makeList(listName){
  tmpDiv=document.createElement("div");
  tmpDiv.classList.add(listName);
  tmpForm=document.createElement("form");
}

function loadList(listName){
  let tmp_map=localStorage.getItem(listName);
  if(tmp_map){
    tmp_map=JSON.parse(tmp_map);
  }else{
    tmp_map=Map();
  }
  TDL_map.prototype.set(listName,tmp_map);
  makeList(listName);
}

function init(){
  TDL_name.forEach(loadList);
  TDL_name.forEach(addEvent);
}

init();




// function handleDel(event){
//   const li=event.target.parentNode;
//   toDo_ul.removeChild(li);
//   toDoList=toDoList.filter(function(toDo){
//     return toDo.id !== li.id;
//   });
//   console.log(toDoList);
//   localStorage.setItem(LS_TODOLIST,JSON.stringify(toDoList));
// }

// function displayToDo(inputObject){
//   const li=document.createElement("li");
//   const delBtn=document.createElement("button");
//   delBtn.innerText="❌";
//   const span=document.createElement("span");
//   span.innerText=inputObject.text;
//   li.id=inputObject.id;
//   li.appendChild(span);
//   li.appendChild(delBtn);
//   toDo_ul.appendChild(li);
//   delBtn.addEventListener("click",handleDel);
// }

// function getID(){
//   while(true){
//     const rand=Math.floor(Math.random()*LIST_SIZE);
//     const newID=`toDo-${rand}`;
//     let overlap=false;
//     toDoList.forEach(function(toDo){
//       if(toDo.id === newID){
//         overlap=true;
//       }
//     });
//     if(!overlap){
//       return newID;
//     }
//   }
// }

// function handleSubmit(event){
//   event.preventDefault();
//   const inputObject={
//     text:toDo_input.value,
//     id:getID()
//   };
//   toDoList.push(inputObject);
//   displayToDo(inputObject);
//   localStorage.setItem(LS_TODOLIST,JSON.stringify(toDoList));
//   toDo_input.value="";
// }

// function loadToDOList(){
//   const loadedToDoList=localStorage.getItem(LS_TODOLIST);
//   if(loadedToDoList){
//     toDoList=JSON.parse(loadedToDoList);
//     toDoList.forEach(displayToDo);
//   }
// }

// function init(){
//   loadToDOList(); 
//   toDo_form.addEventListener("submit",handleSubmit);
// }

// init();


