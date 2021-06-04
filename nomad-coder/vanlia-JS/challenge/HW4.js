/*feedback
  body는 document.body로 선택할 수 있다.
  ele.classList.remove는 여러 요소를 한번에 지울 수 있다(더할수도 있을듯)
  small에서 한번에 big으로 바뀔수도 있다고 생각하므로, 정답과는 다르게 1개만 지우지는 않는다(2개 모두 지운다).
*/


// <⚠️ DONT DELETE THIS ⚠️>
import "./styles.css";
// <⚠️ /DONT DELETE THIS ⚠️>

function handleWindowWidth() {
  //const body = document.querySelector("body");
  const body=document.body;
  const width = window.innerWidth;
  if (width > 1200) {
    body.classList.add("big_width");
    //body.classList.remove("small_width");
    body.classList.remove("mid_width","small_width");
  } else if (width > 800) {
    body.classList.remove("big_width","small_width");
    //body.classList.remove("small_width");
    body.classList.add("mid_width");
  } else {
    //body.classList.remove("big_width");
    body.classList.add("small_width");
    body.classList.remove("mid_width","big_width");
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