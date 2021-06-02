// <⚠️ DONT DELETE THIS ⚠️>
import "./styles.css";
const colors = ["#1abc9c", "#3498db", "#9b59b6", "#f39c12", "#e74c3c"];
// <⚠️ /DONT DELETE THIS ⚠️>

/*
✅ The text of the title should change when the mouse is on top of it.
✅ The text of the title should change when the mouse is leaves it.
✅ When the window is resized the title should change.
✅ On right click the title should also change.
✅ The colors of the title should come from a color from the colors array.
✅ DO NOT CHANGE .css, or .html files.
✅ ALL function handlers should be INSIDE of "superEventHandler"
*/
const title = document.querySelector("h2");

const superEventHandler = {
  titleChange: function (message, color) {
    title.innerHTML = message;
    title.style.color = color;
  },
  titleMouseOver: function () {
    superEventHandler.titleChange("The mouse is here!", colors[0]);
  },
  titleMouseLeave: function () {
    superEventHandler.titleChange("The mouse is gone!", colors[1]);
  },
  windowResize: function () {
    superEventHandler.titleChange("You just resized!", colors[2]);
  },
  windowRightClick: function () {
    superEventHandler.titleChange("That was a right click!", colors[4]);
  }
};

title.addEventListener("mouseover", superEventHandler.titleMouseOver);
title.addEventListener("mouseleave", superEventHandler.titleMouseLeave);
window.addEventListener("resize", superEventHandler.windowResize);
window.addEventListener("contextmenu", superEventHandler.windowRightClick);
