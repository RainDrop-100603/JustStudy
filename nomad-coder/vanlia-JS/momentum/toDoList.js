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




function displayElement(name,key,value){
  //make li
  const tmpLi=document.createElement("li");
  tmpLi.innerText=value;
  tmpLi.id=key;
  //make Btn
  const ul=TDL_Container.querySelector(`.${name}`);
  ul.appendChild(tmpLi);
}

function addElement(name,value){
  let newID;
  const nowList=TDL_listGroup.get(name);
  while(true){
    const rand=Math.floor(Math.random()*LIST_SIZE);
    newID=`${name}-${rand}`;
    if(!nowList.has(newID)){
      break;
    }
  }
  nowList.set(newID,value);
  //이거 이용해서 map을 localstorage에 저장하고 불러오기 
  const str=JSON.stringify(Array.from(nowList.entries()));
  console.log(str);
  console.dir(new Map(JSON.parse(str)));
  //localStorage.setItem(name,JSON.stringify(nowList));
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

function loadListFromLC(name){
  let tmp_map=localStorage.getItem(name);
  if(tmp_map){
    tmp_map=JSON.parse(tmp_map);
  }else{
    tmp_map=new Map();
  }
  TDL_listGroup.set(name,tmp_map);
} 

function loadList(listObj){
  const name=listObj[0];
  buildHtmlBase(listObj);
  loadListFromLC(name);
  const nowList=TDL_listGroup.get(name);
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


