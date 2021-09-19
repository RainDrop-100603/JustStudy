const game_Container=document.querySelector(".js-hw8"),
  game_description=game_Container.querySelector(".hw8-description"),
  game_rangeBar=game_Container.querySelector(".hw8-range"),
  game_answer=game_Container.querySelector(".hw8-answer"),
  game_result=game_Container.querySelector(".hw8-result"),
  game_playBtn=game_answer.querySelector("button");

const INVISIBLE="invisible";
const GAME_RANGEMAX=1000;
let nowValue=GAME_RANGEMAX;

function prepareGame(){
  game_rangeBar.querySelector("input").setAttribute("max",GAME_RANGEMAX);
  game_rangeBar.querySelector("input").setAttribute("value",GAME_RANGEMAX);
  game_description.innerText=`Generate a number between 0 and ${GAME_RANGEMAX}`;
  game_rangeBar.addEventListener("input",function(event){
    nowValue=parseInt(event.target.value);
    game_description.innerText=`Generate a number between 0 and ${nowValue}`;
  });
}

function startGame(event){
  event.preventDefault();
  const inputValue=parseInt(event.target.querySelector("input").value);
  const rand=Math.floor(Math.random()*(nowValue+1));
  const str=`You chose: ${inputValue}, the machine chose: ${rand}`;
  game_result.querySelector("span").innerText=str;
  if(inputValue===rand){
    game_result.querySelector("h3").innerText="you Won!";
  }else{
    game_result.querySelector("h3").innerText="you Lost!";
  }
  game_result.classList.remove(INVISIBLE);
}

function init(){
  prepareGame();
  game_answer.addEventListener("submit",startGame);
}

init();