#include <Adafruit_NeoPixel.h>
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <WiFiManager.h>


#define LED_PIN 2
#define NUM_SEGMENTS 7

WiFiManager wifiManager;


Adafruit_NeoPixel pixels(NUM_SEGMENTS, LED_PIN, NEO_GRB + NEO_KHZ800);


ESP8266WebServer server(80);


const uint8_t digits[10][7] PROGMEM = {
    {1, 1, 1, 1, 1, 1, 0}, // 0
    {1, 0, 0, 0, 0, 1, 0}, // 1
    {1, 1, 0, 1, 1, 0, 1}, // 2
    {1, 1, 0, 0, 1, 1, 1}, // 3
    {1, 0, 1, 0, 0, 1, 1}, // 4
    {0, 1, 1, 0, 1, 1, 1}, // 5
    {0, 1, 1, 1, 1, 1, 1}, // 6
    {1, 1, 0, 0, 0, 1, 0}, // 7
    {1, 1, 1, 1, 1, 1, 1}, // 8
    {1, 1, 1, 0, 1, 1, 1}  // 9
};


int currentDigit = 0;
int countdownValue = 10; 

// Página HTML armazenada na memória flash
const char webpage[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html>
<head>
  <title>Controlar Digito e Contagem Regressiva</title>
  <style>
    body { font-family: Arial, sans-serif; text-align: center; margin: 20px; }
    button { padding: 15px; font-size: 20px; margin: 10px; cursor: pointer; }
    button.selected { background-color: #4CAF50; color: white; border: 2px solid #4CAF50; }
    
    #selectedDigit { 
      margin-top: 20px; 
      font-size: 70px; /* Aumenta o tamanho da fonte do dígito */
      color: #333; 
      font-weight: bold;
      text-align: center;
      display: block;
    }

    #countdown {
      font-size: 50px; /* Tamanho da fonte da contagem regressiva */
      margin-top: 30px;
      color: #FF0000;
    }
  </style>
</head>
<body>
  <h1>Controle o Digito no Display</h1>
  <div>
    <button onclick="sendDigit(0)">0</button>
    <button onclick="sendDigit(1)">1</button>
    <button onclick="sendDigit(2)">2</button>
    <button onclick="sendDigit(3)">3</button>
    <button onclick="sendDigit(4)">4</button>
    <button onclick="sendDigit(5)">5</button>
    <button onclick="sendDigit(6)">6</button>
    <button onclick="sendDigit(7)">7</button>
    <button onclick="sendDigit(8)">8</button>
    <button onclick="sendDigit(9)">9</button>
  </div>

  <div id="selectedDigit">Nenhum digito selecionado</div>
  
  <!-- Botão para iniciar a contagem regressiva -->
  <button onclick="startCountdown()">Iniciar Contagem Regressiva</button>
  
  <!-- Exibe a contagem regressiva -->
  <div id="countdown">10</div>

  <script>
    let countdownInterval; 
    let countdownValue = 10; 

    function sendDigit(digit) {
      // Envia o dígito selecionado para o servidor
      fetch(`/setDigit?value=${digit}`)
        .then(response => {
          if (!response.ok) {
            alert('Erro ao enviar o dígito.');
            return;
          }
          // Atualiza a interface ao receber sucesso
          updateSelectedDigit(digit);
        });
    }

    function updateSelectedDigit(digit) {
      // Atualiza o texto com o dígito selecionado
      const display = document.getElementById('selectedDigit');
      display.textContent = `Dígito selecionado: ${digit}`;

      // Remove o destaque de todos os botões
      const buttons = document.querySelectorAll('button');
      buttons.forEach(button => button.classList.remove('selected'));

      // Adiciona o destaque ao botão selecionado
      const selectedButton = document.querySelector(`button:nth-child(${digit + 1})`);
      if (selectedButton) {
        selectedButton.classList.add('selected');
      }
    }

    function startCountdown() {
     
      const selectedDigit = document.getElementById('selectedDigit').textContent;
      if (selectedDigit === 'Nenhum digito selecionado') {
        alert('Selecione um dígito primeiro!');
        return;
      }

      
      countdownValue = parseInt(selectedDigit.replace('Digito selecionado: ', '').trim());
      const countdownDisplay = document.getElementById('countdown');
      countdownDisplay.textContent = countdownValue;

      
      if (countdownInterval) {
        clearInterval(countdownInterval);
      }

      
      countdownInterval = setInterval(() => {
        countdownValue--;
        countdownDisplay.textContent = countdownValue;
        
        
        fetch(`/setDigit?value=${countdownValue}`); 

        if (countdownValue <= 0) {
          clearInterval(countdownInterval); 
          countdownDisplay.textContent = 'Tempo Esgotado!';
        }
      }, 1000);
    }
  </script>
</body>
</html>
)rawliteral";


void handleRoot();
void handleSetDigit();
void displayDigit(int digit);


void setup() {
  Serial.begin(115200);
  pixels.begin();
  pixels.clear();
  pixels.show();

  // Configuração WiFi
  wifiManager.autoConnect("ESP_Digito");
  Serial.println("Conectado ao WiFi. IP:");
  Serial.println(WiFi.localIP());

  
  server.on("/", handleRoot);
  server.on("/setDigit", handleSetDigit);
  server.begin();
  Serial.println("Servidor iniciado!");
}


void loop() {
  server.handleClient();
}


void handleRoot() {
  server.send_P(200, "text/html", webpage);
}

// Função para alterar o dígito exibido
void handleSetDigit() {
  if (server.hasArg("value")) {
    int digit = server.arg("value").toInt();
    if (digit >= 0 && digit <= 9) {
      currentDigit = digit;
      displayDigit(currentDigit);
      server.send(200, "text/plain", "Dígito atualizado!");
      return;
    }
  }
  server.send(400, "text/plain", "Dígito inválido!");
}

// Função para exibir um dígito na fita de LED
void displayDigit(int digit) {
  pixels.clear();

  for (int segment = 0; segment < NUM_SEGMENTS; segment++) {
    if (pgm_read_byte(&(digits[digit][segment])) == 1) { 
      pixels.setPixelColor(segment, pixels.Color(0, 150, 0)); 
    }
  }
  pixels.show();
}
