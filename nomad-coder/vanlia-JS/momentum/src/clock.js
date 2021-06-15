const clockContainer=document.querySelector(".js-clock"),
  clockTitle=clockContainer.querySelector("h1");

function clock_display(){
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

function clock_displaySimple(){
  let date=new Date(),
    seconds=date.getSeconds(),
    minutes=date.getMinutes(),
    hours=date.getHours();
  const now= `${hours < 10 ? `0${hours}` : hours}:${minutes < 10 ? `0${minutes}` : minutes}:${seconds < 10 ? `0${seconds}` : seconds}`;
  clockTitle.innerHTML=now;
}

function bg_init(){
  clock_displaySimple();
  setInterval(clock_displaySimple,1000);
}

bg_init();