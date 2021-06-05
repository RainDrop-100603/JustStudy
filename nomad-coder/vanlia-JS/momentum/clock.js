const body=document.body,
  clockContainer=body.querySelector(".js-clock"),
  clockTitle=clockContainer.querySelector("h1");

function displayTime(){
  let date=new Date(),
    seconds=date.getSeconds(),
    minutes=date.getMinutes(),
    hours=date.getHours(),
    days=date.getDate(),
    months=date.getMonth()+1,
    years=date.getFullYear();
  const now= `${years}y ${months < 10 ? `0${months}` : months}m ${days < 10 ? `0${days}` : days}d 
    ${hours < 10 ? `0${hours}` : hours}h ${minutes < 10 ? `0${minutes}` : minutes}m ${seconds < 10 ? `0${seconds}` : seconds}s`;
  clockTitle.innerHTML=now;
}

function displaySimple(){
  let date=new Date(),
    seconds=date.getSeconds(),
    minutes=date.getMinutes(),
    hours=date.getHours();
  const now= `${hours < 10 ? `0${hours}` : hours}:${minutes < 10 ? `0${minutes}` : minutes}:${seconds < 10 ? `0${seconds}` : seconds}`;
  clockTitle.innerHTML=now;
}

function init(){
  displaySimple();
  setInterval(displaySimple,1000);
}

init();