const weatherContainer=document.querySelector(".js-weather");

const WEATHER_API_KEY="33a4b37f047d9d66fe381f85dc77ba6f",
  WEATHER_LC_COORDS="weather-coords";

//실제 날씨 표현, 날씨 예보도 추가 
function weather_info(json){
  console.log(json);
  const tempNow=json.main.temp,
    tempMax=json.main.temp_max,
    tempMin=json.main.temp_min,
    tempFeel=json.main.feels_like;    
  const location=json.name;
  const weather=json.weather[0].main,
    wind=json.wind.speed,
    humidity=json.main.humidity;
  const str=`${location} ${weather} ${tempNow}°C ${humidity}% ${wind}m/s`;
  weatherContainer.innerHTML=str;
}

function weather_saveToLocal(coords){
  localStorage.setItem(WEATHER_LC_COORDS,JSON.stringify(coords));
}

function weather_loadFromLocal(){
  return JSON.parse(localStorage.getItem(WEATHER_LC_COORDS));
}

function weather_display(coords){
  fetch(`https://api.openweathermap.org/data/2.5/weather?lat=${coords.latitude}&lon=${coords.longitude}&appid=${WEATHER_API_KEY}&units=metric`
    ).then(function(response){
      return response.json();
    }).then(weather_info);
}

function weather_getCoordsSuccess(position){
  const latitude=position.coords.latitude;
  const longitude=position.coords.longitude;
  const coords={
    latitude,
    longitude
  };
  weather_saveToLocal(coords);
  weather_display(coords);
}

function weather_getCoordsFail(){
  console.log("please allow location service");
}

function weather_getCoords(){
  navigator.geolocation.getCurrentPosition(weather_getCoordsSuccess,weather_getCoordsFail);
}

function weather_init(){
  const coords=weather_loadFromLocal();
  if(coords){
    weather_display(coords);
  }else{
    weather_getCoords();
  }
} 

weather_init();