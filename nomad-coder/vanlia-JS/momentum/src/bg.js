const bgBody=document.body;

function bg_handleLoad(image){
  image.classList.add("bg-image");
  bgBody.appendChild(image);
}

function bg_init(){
  const image=new Image();
  imgNum=0;
  image.src=`images/${imgNum}.jpg`
  image.addEventListener("load",bg_handleLoad(image),{once:true})
}

bg_init();