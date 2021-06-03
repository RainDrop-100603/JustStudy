// <⚠️ DONT DELETE THIS ⚠️>
import "./styles.css";
// <⚠️ /DONT DELETE THIS ⚠️>

function handleWindowWidth() {
  const body = document.querySelector("body");
  const width = window.innerWidth;
  if (width > 1200) {
    body.classList.add("big_width");
    body.classList.remove("small_width");
    body.classList.remove("mid_width");
  } else if (width > 800) {
    body.classList.remove("big_width");
    body.classList.remove("small_width");
    body.classList.add("mid_width");
  } else {
    body.classList.remove("big_width");
    body.classList.add("small_width");
    body.classList.remove("mid_width");
  }
}

window.addEventListener("resize", handleWindowWidth);


/*
css

.small_width {
  background-color: #4b7bec;
}
.mid_width {
  background-color: #a55eea;
}
.big_width {
  background-color: #fed330;
}


*/