// <⚠️ DONT DELETE THIS ⚠️>
import "./styles.css";
// <⚠️ /DONT DELETE THIS ⚠️>

const selectElement = document.querySelector(".js-country");

const LS_userCountry = "userCountry";

function handleChange(event) {
  const country = event.target.value;
  localStorage.setItem(LS_userCountry, country);
}

function chooseUserCountry() {
  selectElement.addEventListener("change", handleChange);
}

function init() {
  chooseUserCountry();
  const country = localStorage.getItem(LS_userCountry);
  if (country !== null) {
    const choosed = selectElement.querySelector(`option[value=${country}]`);
    choosed.setAttribute("selected", "");
  }
}

init();
