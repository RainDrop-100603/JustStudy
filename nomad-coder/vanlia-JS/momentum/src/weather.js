const weatherContainer=document.querySelector(".js-weather");

const WEATHER_API_KEY="33a4b37f047d9d66fe381f85dc77ba6f",
  WEATHER_LS_COORDS="weather-coords";

//실제 날씨 표현, 날씨 예보도 추가 
function weather_icon(str){
  if(str=="few clouds"||str=="scattered clouds"){return "⛅"+str;}
  if(str=="overcast clouds"||str=="broken clouds"){return "☁️"+str;}
  if(str=="temp"){return "🌡️";}
  if(str=="humidity"){return "💧";}
  if(str=="wind"){return "🌬️";}
  if(str=="clear sky"){return "🌞"+str;}
  if(str=="mist"){return "🌫️"+str;}
  if(str=="light intensity drizzle"){return "🌧️"+str;}
}

function weather_info(json){
  const tempNow=json.main.temp,
    tempMax=json.main.temp_max,
    tempMin=json.main.temp_min,
    tempFeel=json.main.feels_like;    
  const location=json.name;
  const weather=json.weather[0].main,
    weatherDetail=json.weather[0].description,
    wind=json.wind.speed,
    humidity=json.main.humidity;
  console.log(json);
  const str=`<strong>${location}</br>
    ${weather_icon(weatherDetail)}</br>
    ${weather_icon("temp")+Math.floor(tempNow)}°C ___ ${weather_icon("humidity")+humidity}% ___ ${weather_icon("wind")+wind}m/s</strong>`;
  weatherContainer.innerHTML=str;
}

function weather_saveToLocal(coords){
  localStorage.setItem(WEATHER_LS_COORDS,JSON.stringify(coords));
}

function weather_loadFromLocal(){
  return JSON.parse(localStorage.getItem(WEATHER_LS_COORDS));
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