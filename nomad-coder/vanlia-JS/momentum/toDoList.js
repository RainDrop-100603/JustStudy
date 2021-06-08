const TDL_Container=document.querySelector(".js-toDoList");
  // toDo_ul=toDo_Container.querySelector("ul");

//size of list
const LIST_SIZE=10000;
//[name of list ,placeholder], if there's no input form, placeholder is null
const TDL_name=[  
  ["TDL-todo","What to do?"],
  ["TDL-finish",null]
]; 
//map of list: [key: name, value: list(map)]
const TDL_listGroup=new Map();  

function saveToLocal(listName){
  const list=TDL_listGroup.get(listName);
  const str=JSON.stringify(Array.from(list.entries()));
  localStorage.setItem(listName,str);
}

function getFromLocal(listName){
  const str=localStorage.getItem(listName);
  return new Map(JSON.parse(str));
}

function getID(list){
  while(true){
    const rand=Math.floor(Math.random()*LIST_SIZE);
    const newID=`TDL-${rand}`;
    if(!list.has(newID)){
      return newID;
    }
  }
}

function removeChild(doc, target){
  const tmp=doc.querySelectorAll(target);
  tmp.forEach(function(element){
    doc.removeChild(element);
  });
}

function handleBtn(event,destName){
  const fromLi=event.target.parentElement;
  const fromUl=fromLi.parentElement;
  const fromName=fromUl.parentElement.className;
  const fromID=fromLi.id;
  const fromList=TDL_listGroup.get(fromName);
  if(destName){ //move
    const destList=TDL_listGroup.get(destName);
    fromLi.id=getID(destList);
    removeChild(fromLi,"button");
    destList.set(fromLi.id,fromLi.innerText);
    displayElement(destName,fromLi.id,fromLi.innerText);
    saveToLocal(destName);
  }
  fromUl.removeChild(fromLi);
  fromList.delete(fromID);
  saveToLocal(fromName);
}

function makeBtn(btnText,dest){
  const btn=document.createElement("button");
  btn.innerText=btnText;
  btn.addEventListener("click",function(event){
    handleBtn(event,dest);
  });
  return btn;
}

function displayElement(name,key,value){
  //make li
  const tmpLi=document.createElement("li");
  tmpLi.innerText=value;
  tmpLi.id=key;
  //make Btn
  if(name==="TDL-todo"){
    tmpLi.appendChild(makeBtn("✔","TDL-finish"));
  }
  if(name==="TDL-finish"){
    tmpLi.appendChild(makeBtn("♻","TDL-todo"));
  }
  tmpLi.appendChild(makeBtn("❌",null));
  //add li to ul
  const ul=TDL_Container.querySelector(`.${name}`).querySelector("ul");
  ul.appendChild(tmpLi);
}

function addElement(name,value){
  const nowList=TDL_listGroup.get(name);
  const newID=getID(nowList);
  nowList.set(newID,value);
  saveToLocal(name);
  return newID;
}

function handleSubmit(event){
  event.preventDefault();
  const parentName=event.target.parentElement.className;
  const inputValue=event.target.querySelector("input").value;
  //add element to list
  const ID=addElement(parentName,inputValue);
  //add element to html
  displayElement(parentName,ID,inputValue);
  event.target.querySelector("input").value="";
}

function buildHtmlBase(listObj){
  const tmpDiv=document.createElement("div");
  tmpDiv.classList.add(listObj[0]);
  //make title of to-do-list
  const listName=listObj[0].substr(4);
  const tmpTitle=document.createElement("h1");
  tmpTitle.innerText=listName;
  tmpDiv.appendChild(tmpTitle);
  //make input form if placeholder !== null
  if(listObj[1]){
    const tmpInput=document.createElement("input");
    tmpInput.type="text";
    tmpInput.placeholder=listObj[1];
    const tmpForm=document.createElement("form");
    tmpForm.appendChild(tmpInput);
    tmpForm.addEventListener("submit",handleSubmit);
    tmpDiv.appendChild(tmpForm);
  }
  //make ul
  const tmpUl=document.createElement("ul");
  tmpDiv.appendChild(tmpUl);
  TDL_Container.appendChild(tmpDiv);
}

function loadList(listObj){
  const name=listObj[0];
  buildHtmlBase(listObj);
  const nowList=getFromLocal(name);
  TDL_listGroup.set(name,nowList);
  for(let [key,value] of nowList){
    displayElement(name,key,value);
  }
}

function init(){
  TDL_name.forEach(loadList);
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


