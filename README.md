# Placar_via_WiFi

Projeto de Display de 7 Segmentos com LEDs WS2811 e ESP-01
Este projeto utiliza um microcontrolador ESP-01 e uma fita de LED endereçável WS2811 para criar um display de 7 segmentos controlado via uma página web. O projeto permite selecionar um número entre 0 a 9 e exibi-lo no display de LEDs, além de iniciar uma contagem regressiva a partir do número selecionado.Podendo assim ser utilizado tambem como um cronometro ,adicionando mais digitos ao esquema inicial.

Componentes Utilizados
Microcontrolador: ESP-01 (ESP8266)
Fita de LED: WS2811 (endereçável)
Servidor Web: Servidor web simples utilizando a biblioteca ESP8266WebServer
Fonte de Alimentação: A alimentação da fita de LED e do ESP-01 é feita por meio de uma fonte externa.
Funcionalidades
Seleção de Dígitos: Através da interface web, é possível selecionar um número de 0 a 9, que será exibido no display de LEDs.
Contagem Regressiva: Após a seleção do número, é possível iniciar uma contagem regressiva a partir desse valor, que será atualizada tanto na interface web quanto no display de LEDs.
Display de 7 Segmentos: Cada número selecionado é exibido no display de 7 segmentos montado com a fita de LED WS2811.
Visão Geral do Circuito
O circuito é simples e envolve a conexão da fita de LED WS2811 ao pino GPIO do ESP-01. A fita de LED é controlada utilizando a biblioteca Adafruit NeoPixel.

Diagrama de Conexões
ESP-01:

Pino GPIO0 (ou outro pino de sua escolha) conectado ao pino de dados da fita WS2811.
Alimentação de 3.3V para o ESP-01 e 5V para a fita de LED WS2811 (verifique a compatibilidade da alimentação).
Fita WS2811:

A fita de LED é conectada ao ESP-01 para controle dos segmentos do display de 7 segmentos.
Como Usar
Configuração do Ambiente:

Baixe e instale a IDE do Arduino.
Instale as bibliotecas necessárias:
Adafruit NeoPixel para controlar a fita de LEDs.
ESP8266WiFi para conectar o ESP-01 à rede Wi-Fi.
ESP8266WebServer para criar o servidor web.
Configuração do Código:

Faça o upload do código para o ESP-01.
O ESP-01 irá conectar-se automaticamente à sua rede Wi-Fi utilizando a biblioteca WiFiManager.
Acessando a Página Web:

Após o ESP-01 se conectar à rede Wi-Fi, abra o monitor serial para ver o endereço IP atribuído ao dispositivo.
Acesse esse IP em um navegador da web para controlar o display de 7 segmentos e iniciar a contagem regressiva.
Controle da Contagem:

Selecione um dígito de 0 a 9.
Pressione o botão para iniciar a contagem regressiva a partir do número selecionado.
O valor da contagem será exibido no display de LEDs e na interface web.
Como Funciona
O servidor web cria uma interface com botões para seleção dos números de 0 a 9.
Ao selecionar um número, o valor é enviado para o ESP-01, que aciona a fita de LEDs para exibir o número selecionado no display de 7 segmentos.
Ao clicar no botão de iniciar contagem regressiva, a contagem começa no número selecionado e a cada segundo o display é atualizado, até que a contagem chegue a zero.
Funcionalidades Futuras
Personalização de LEDs: Possibilidade de personalizar a cor dos LEDs para cada número ou para cada etapa da contagem regressiva.
Alarme ou Notificação: Adicionar um alarme sonoro ou uma notificação quando a contagem regressiva terminar.
Melhorias no Frontend: Melhorar o design da página web com mais interatividade e opções de controle.
Instalação e Dependências
Instale o Arduino IDE: Baixar Arduino IDE.
Instale a biblioteca Adafruit NeoPixel:
Vá para Sketch > Incluir Biblioteca > Gerenciar Bibliotecas e busque por "Adafruit NeoPixel".
Instale a biblioteca ESP8266WiFi:
Vá para Sketch > Incluir Biblioteca > Gerenciar Bibliotecas e busque por "ESP8266".
Instale a biblioteca ESP8266WebServer:
Vá para Sketch > Incluir Biblioteca > Gerenciar Bibliotecas e busque por "ESP8266WebServer".
Faça o upload do código para o ESP-01.
Licença
Este projeto está licenciado sob a MIT License. Veja o arquivo LICENSE para mais informações.

Dicas Finais:
Certifique-se de usar uma alimentação adequada para a fita de LED WS2811. Ela pode exigir mais corrente do que o ESP-01 pode fornecer diretamente.
Lembre-se de que a fita de LED WS2811 é endereçável, então cada LED pode ser controlado individualmente.
Caso queira adicionar mais recursos ao projeto, como integração com outros dispositivos ou melhorias no frontend, fique à vontade para contribuir!
