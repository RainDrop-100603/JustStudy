const title=document.querySelector(".title");

function handleWindowWidth(){
  const body=document.querySelector("body");
  const width=window.innerWidth;
  console.log(width);
  if(width>1000){
    body.classList.add("big_width");
    body.classList.remove("small_width");
    body.classList.remove("mid_width");
  }else if(width>500){
    body.classList.remove("big_width");
    body.classList.remove("small_width");
    body.classList.add("mid_width");
  }else{
    body.classList.remove("big_width");
    body.classList.add("small_width");
    body.classList.remove("mid_width");
  }
}

window.addEventListener("resize",handleWindowWidth);