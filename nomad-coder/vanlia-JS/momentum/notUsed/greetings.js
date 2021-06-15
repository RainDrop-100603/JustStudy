const greetContainer=document.querySelector(".js-greetings"),
  greetForm=greetContainer.querySelector("form"),
  greetInput=greetForm.querySelector("input"),
  greetSayHello=greetContainer.querySelector("h4");

const GREET_CN_INVISIBLE="display-none",
  GREET_LC_USER="greetings-userName";

function greet_user(user){
  greetSayHello.classList.remove(GREET_CN_INVISIBLE);
  greetSayHello.innerText=`Hello ${user}!`;
}

function greet_handleSubmit(event){
  event.preventDefault(); //submit시 새로고침 방지
  const inputValue=greetInput.value;
  localStorage.setItem(GREET_LC_USER,inputValue);
  greetForm.classList.add(GREET_CN_INVISIBLE);
  greet_user(inputValue);
}

function greet_getUser(){
  greetForm.classList.remove(GREET_CN_INVISIBLE);
  greetForm.addEventListener("submit",greet_handleSubmit);
}

function greet_init(){
  const user=localStorage.getItem(GREET_LC_USER);
  if(user){
    greet_user(user);
  }else{
    greet_getUser();
  }
}

greet_init();