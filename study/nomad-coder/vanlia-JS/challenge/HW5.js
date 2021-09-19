import "./styles.css";

const dateOfMonth = [-1, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31, -1];

// You're gonna need this
function getTime() {
  // Don't delete this.
  const xmasDay = new Date("2021-12-24:00:00:00+0900");
  const today = new Date();
  const target = document.querySelector(".js-clock").querySelector("h2");
  //get each date
  const xmasMonth = xmasDay.getMonth() + 1,
    xmasDate = xmasDay.getDate(),
    xmasHours = xmasDay.getHours(),
    xmasMinutes = xmasDay.getMinutes(),
    xmasSeconds = xmasDay.getSeconds();
  const todayMonth = today.getMonth() + 1,
    todayDate = today.getDate(),
    todayHours = today.getHours(),
    todayMinutes = today.getMinutes(),
    todaySeconds = today.getSeconds();
  //calculate difference
  let remainSeconds = xmasSeconds - todaySeconds,
    remainMinutes = xmasMinutes - todayMinutes,
    remainHours = xmasHours - todayHours,
    remainDate = xmasDate - todayDate;
  for (let count = todayMonth; count < xmasMonth; count++) {
    remainDate += dateOfMonth[count];
  }
  while (remainSeconds < 0) {
    remainSeconds += 60;
    remainMinutes--;
  }
  while (remainMinutes < 0) {
    remainMinutes += 60;
    remainHours--;
  }
  while (remainHours < 0) {
    remainHours += 24;
    remainDate--;
  }
  //print
  const remainTime = `${remainDate}d 
    ${remainHours < 10 ? `0${remainHours}` : remainHours}h 
    ${remainMinutes < 10 ? `0${remainMinutes}` : remainMinutes}m
    ${remainSeconds < 10 ? `0${remainSeconds}` : remainSeconds}s`;
  target.innerHTML = remainTime;
}

function init() {
  getTime();
  setInterval(getTime, 1000);
}
init();
