const button = document.getElementById("searchBtn");
const input = document.getElementById("locationInput");
const resultsContainer = document.getElementById("results");

button.addEventListener("click", () => {
    const location = input.value.trim();
    if (!location) {
        alert("Please enter a location");
        return;
    }

    resultsContainer.innerHTML = "<p>Loading...</p>";

    const xhr = new XMLHttpRequest();
    const weatherUrl = `https://api.openweathermap.org/data/2.5/weather?q=${location}&appid=${API_KEY}&units=metric`;

    xhr.open("GET", weatherUrl);
    xhr.onload = () => {
        if (xhr.status === 200) {
            const data = JSON.parse(xhr.responseText);
            displayCurrentWeather(data);
        } else {
            resultsContainer.innerHTML =
                "<p>Error fetching current weather.</p>";
        }
    };
    xhr.onerror = () => {
        resultsContainer.innerHTML = "<p>Request failed.</p>";
    };
    xhr.send();

    const forecastUrl = `https://api.openweathermap.org/data/2.5/forecast?q=${location}&appid=${API_KEY}&units=metric`;

    fetch(forecastUrl)
        .then((response) => response.json())
        .then((data) => displayForecast(data))
        .catch(() => {
            resultsContainer.innerHTML += "<p>Error fetching forecast.</p>";
        });
});

function displayCurrentWeather(data) {
    const card = document.createElement("div");
    card.className = "card";
    card.innerHTML = `
        <h2>Current Weather in ${data.name}</h2>
        <p>${data.weather[0].description}</p>
        <p><strong>Temperature:</strong> ${data.main.temp}°C</p>
        <p><strong>Humidity:</strong> ${data.main.humidity}%</p>
    `;
    resultsContainer.innerHTML = "";
    resultsContainer.appendChild(card);
}

function displayForecast(data) {
    const card = document.createElement("div");
    card.className = "card";

    const dailyForecasts = data.list.filter((item) =>
        item.dt_txt.includes("12:00:00")
    );

    const forecastsHTML = dailyForecasts
        .map((item) => {
            const date = item.dt_txt.split(" ")[0];
            const temp = Math.round(item.main.temp);
            const desc = item.weather[0].description;

            return `
            <div class="forecast-box">
                <p><strong>${date}</strong></p>
                <p>${temp}°C</p>
                <p>${desc}</p>
            </div>
        `;
        })
        .join("");

    card.innerHTML = `
        <h3>5 Day Forecast</h3>
        <div class="forecast-container">
            ${forecastsHTML}
        </div>
    `;
    resultsContainer.appendChild(card);
}
