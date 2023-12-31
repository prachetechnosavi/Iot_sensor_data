const char index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Sensor Info</title>
    <style>
     html {
    font-family: Arial, Helvetica, sans-serif;
    display: inline-block;
    text-align: center;
    }
    h1 {
    font-size: 1.8rem;
    color: rgb(250, 250, 239);
   }
    p {
    font-size: 1.4rem;
   }
    .title {
    overflow: hidden;
    background-color: #295a6b;
   }
    body {
    margin: 0;
   }

    th, td {
        text-align: center;
        padding: 8px;
        border:1px solid black; ;
    }
 
  th {
      background-color: #4db0ac;
      color: white;
  }

  table {
      margin: 0 auto;
      width: 90%;
      border: 1px solid black;
  }
  
  .button-data{
      background-color: rgb(47, 96, 3);
      border-radius: 10px;
      color: aliceblue;
  }
</style>
</head>
<body>
    <div class="title">
        <h1>DHT-11 Sensor Data</h1>
    </div>
    <div class="table">
        <p>
            <table>
            <tr>
            <th>READING</th>
            <th>VALUE</th>
            </tr>
            <tr>
                <td>Distance (cm)</td>
                <td><span id="dis"></span></td>
            </tr>
            <tr>
                <td>Light intensity ADC (0 - 1024)</td>
                <td><span id="lum"></span></td>
            </tr>
            </table>
            </p>
    </div> 
    <div class="button">
        <p><button class="button-data" onclick="getstates()">Get Sensor values</button></a></p>
    </div> 
    <script>
       var gateway = `ws://${window.location.hostname}/ws`;
       var websocket;
      
       function onLoad(event) {
        initWebSocket();
      }
      
      function initWebSocket() {
       console.log('Trying to open a WebSocket connection...');
       websocket = new WebSocket(gateway);
       websocket.onopen = onOpen;
       websocket.onclose = onClose;
       websocket.onmessage = onMessage;
      }
      
      function onOpen(event) {
       console.log('Connection opened');
       
      }
      
      function onClose(event) {
       console.log('Connection closed');
       setTimeout(initWebSocket, 2000);
      }
      
      function onMessage(event) {
          var myObj = JSON.parse(event.data);
          var dis = myObj.distance;
          var lum = myObj.light;
          console.log(dis);
          console.log(lum);
          document.getElementById("dis").innerHTML = dis;
          document.getElementById("lum").innerHTML = lum;
          console.log(event.data);
      }
      
      function getstates(){
          websocket.send("give_packet");
          console.log("packet sent to server");
      }
      
      window.addEventListener('load', onLoad);
    </script>
</body>
</html>
)rawliteral";
