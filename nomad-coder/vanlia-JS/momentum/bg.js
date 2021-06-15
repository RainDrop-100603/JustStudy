const bgBody=document.bgBody;

function bg_handleLoad(image){
  image.classList.add("bg-image");
  bgBody.appendChild(image);
}

function bg_init(){
  const image=new Image();
  imgNum=Math.floor(Math.random()*2)+4;
  image.src=`images/${imgNum}.jpg`
  image.addEventListener("load",bg_handleLoad(image),{once:true})
}

bg_init();