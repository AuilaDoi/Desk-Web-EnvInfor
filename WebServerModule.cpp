#include "WebServerModule.h"
#include <WebServer.h>
#include "DHTModule.h"

static WebServer server(80);

String htmlPage() {
    return R"rawliteral(
<!DOCTYPE html>
<html>
<head>
<meta charset='utf-8'>
<title>ESP32 温湿度</title>
<script>
function fetchData(){
  fetch('/data')
    .then(res => res.json())
    .then(d => {
      document.getElementById('t').textContent = d.temp;
      document.getElementById('h').textContent = d.humi;
    });
}
setInterval(fetchData, 2000);
window.onload = fetchData;
</script>
</head>
<body>
<h1>ESP32 温湿度</h1>
<p>温度: <span id="t">--</span> °C</p>
<p>湿度: <span id="h">--</span> %</p>
</body>
</html>
)rawliteral";
}

void initWebServer() {
    server.on("/", []() {
        server.send(200, "text/html; charset=UTF-8", htmlPage());
    });

    server.on("/data", []() {
        float t = readTemperature();
        float h = readHumidity();
        String json = "{\"temp\":" + String(t) + ",\"humi\":" + String(h) + "}";
        server.send(200, "application/json", json);
    });

    server.begin();
}

void updateWebServer() {
    server.handleClient();
}
