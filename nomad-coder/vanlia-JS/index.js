const title=document.getElementById("title");

console.dir(title);

title.innerHTML="Title Changed";
title.style.color="red";

function handleResize(event){
  console.log(event);
}

function titleClicked(event){
  title.style.color="black";
}

window.addEventListener("resize",handleResize);   //window(화면) 에서 resize event가 발생하면, handleResize라는 함수를 실행, event는 JS에서 자동으로 전달? 
title.addEventListener("click",titleClicked);