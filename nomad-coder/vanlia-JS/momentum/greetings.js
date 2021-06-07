const greetings=document.querySelector(".js-greetings"),
  form=greetings.querySelector("form"),
  input=form.querySelector("input"),
  sayHello=greetings.querySelector("h4");

const CN_INVISIBLE="display-none",
  LC_USER="greetings-userName";

function greetUser(user){
  sayHello.classList.remove(CN_INVISIBLE);
  sayHello.innerText=`Hello ${user}!`;
}

function handleSubmit(event){
  event.preventDefault(); //submit시 새로고침 방지
  const inputValue=input.value;
  localStorage.setItem(LC_USER,inputValue);
  form.classList.add(CN_INVISIBLE);
  greetUser(inputValue);
}

function getUser(){
  form.classList.remove(CN_INVISIBLE);
  form.addEventListener("submit",handleSubmit);
}

function init(){
  const user=localStorage.getItem(LC_USER);
  if(user){
    greetUser(user);
  }else{
    getUser();
  }
}

init();