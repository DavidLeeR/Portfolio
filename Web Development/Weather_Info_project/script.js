//Name: David Ramirez
//Date: 7/23/17
//Description: This is a script that enables functionality for an
//              HTML page that displays the weather for a location
//              via "GET" requests to a server. The HTML page also 
//              displays data sent via "POST" to a server.

var apiKey = '4b861af8aced9bf0b28f5c836e942480';

document.addEventListener('DOMContentLoaded', bindButtons);

function bindButtons() {
    document.getElementById('sendCity').addEventListener('click', function (event) {

        event.preventDefault();
        var req = new XMLHttpRequest();
        var city = document.getElementById('city').value;

        req.open("GET", "http://api.openweathermap.org/data/2.5/weather?q=" + city + "&appid=" + apiKey, true);
        req.send(null);
        req.addEventListener('load', function () {
            if (req.status >= 200 && req.status < 400) {
                var response = JSON.parse(req.responseText);


                var cityName = response.name;
                var temp = response.main.temp;
                var weather = response.weather[0].description;
                var wind = response.wind.speed;

                document.getElementById('results').textContent = "The weather summary for " + cityName + " is........Description: " + weather + ".........Temperature: " + temp + " kelvin" + ".........Wind Speed:" + wind + "m/s";



            }
            else {

                console.log("Error in network request: " + req.statusText);

            }

        })

    })

    document.getElementById('sendZip').addEventListener('click', function (event) {

        event.preventDefault();
        var req = new XMLHttpRequest();
        var zip = document.getElementById('zip').value;

        req.open("GET", "http://api.openweathermap.org/data/2.5/weather?zip=" + zip + "&appid=" + apiKey, true);
        req.send(null);
        req.addEventListener('load', function () {
            if (req.status >= 200 && req.status < 400) {
                var response = JSON.parse(req.responseText);


                var cityName = response.name;
                var temp = response.main.temp;
                var weather = response.weather[0].description;
                var wind = response.wind.speed;

                document.getElementById('results').textContent = "The weather summary for " + cityName + " is........Description: " + weather + ".........Temperature: " + temp + " kelvin" + ".........Wind Speed:" + wind + "m/s";

            }
            else {
                console.log("Error in network request: " + req.statusText);

            }

        })

    })

    document.getElementById('sendData').addEventListener('click', function (event) {

        var req = new XMLHttpRequest();
        var payload = { data: null };
        payload.data = document.getElementById('data').value;
        req.open("POST", "http://httpbin.org/post", true);
        req.setRequestHeader("Content-Type", "application/json");
        req.addEventListener("load", function () {
            if (req.status >= 200 && req.status < 400) {
                var response = JSON.parse(req.responseText);
                document.getElementById("results2").textContent = response.data;
            }

            else {
                console.log("Error in network request: " + req.statusText);
            }
        })
        req.send(JSON.stringify(payload));
        event.preventDefault();
    })
}