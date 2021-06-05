const form=document.querySelector(".js-form"),
  greetings=document.querySelector(".js-greetings"),
  input=form.querySelector("input");

const CN_visible="showing",
  LS_User="userName";

function greetUser(user){
  form.classList.remove(CN_visible);
  greetings.classList.add(CN_visible);
  greetings.innerText=`Hello ${user}!`;
}

function handleSubmit(event){
  event.preventDefault();
  const currentValue=input.value;
  localStorage.setItem(LS_User,currentValue);
  greetUser(currentValue);
}

function getUser(){
  form.classList.add(CN_visible);
  form.addEventListener("submit",handleSubmit);
  // const user=localStorage.getItem(LS_User);
  // greetUser(user);
}

function loadUsername(){
  const user=localStorage.getItem(LS_User);
  if(user === null){
    getUser();
  }else{
    greetUser(user);
  }
}

function init(){
  loadUsername();
}

init();