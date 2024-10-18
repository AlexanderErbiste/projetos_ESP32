#include <WiFi.h>

#define azul 5
#define verde 18
#define vermelho 19

const char* ssid = "NET_2G984B1A";
const char* password = "68984B1A";

WiFiServer server(80);

void setup() {
  Serial.begin(115200);

  pinMode(azul, OUTPUT);      
  pinMode(verde, OUTPUT);     
  pinMode(vermelho, OUTPUT);  

  // Inicialmente desligue todos os LEDs
  digitalWrite(azul, LOW);
  digitalWrite(verde, LOW);
  digitalWrite(vermelho, LOW);

  delay(10);

  // Conectando ao WiFi
  Serial.println();
  Serial.println();
  Serial.print("Conectando à ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi conectado.");
  Serial.println("Endereço IP: ");
  Serial.println(WiFi.localIP());  // Exibir IP local no monitor serial

  server.begin();
}

void loop() {
  WiFiClient client = server.available();  // Ouve por conexões de clientes

  if (client) {
    Serial.println("Novo Cliente.");  // Indica que um cliente se conectou
    String currentLine = "";          // Armazena a linha atual de dados do cliente
    while (client.connected()) {
      if (client.available()) {
        char c = client.read();       // Lê um byte do cliente
        Serial.write(c);              // Exibe o byte no monitor serial
        if (c == '\n') {
          // Se a linha atual estiver vazia, significa que chegou ao fim da solicitação HTTP
          if (currentLine.length() == 0) {
            // Resposta HTTP
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println();

            // HTML da página com os botões
            client.println("<center>");
            client.println("<br>");
            client.println("<a href=\"/azul\"><button>Azul</button></a>");
            client.println("<br>");
            client.println("<br>");
            client.println("<a href=\"/verde\"><button>Verde</button></a>");
            client.println("<br>");
            client.println("<br>");
            client.println("<a href=\"/vermelho\"><button>Vermelho</button></a>");
            client.println("<br>");
            client.println("<br>");
            client.println("<a href=\"/branco\"><button>Branco</button></a>");
            client.println("<br>");
            client.println("<br>");
            client.println("<a href=\"/roxo\"><button>Roxo</button></a>");
            client.println("<br>");
            client.println("<br>");
            client.println("<a href=\"/amarelo\"><button>Amarelo</button></a>");
            client.println("<br>");
            client.println("<br>");
            client.println("<a href=\"/desliga\"><button>Desliga</button></a>");
            client.println("<br>");
            client.println("<br>");
            client.println("</center>");

            // Finaliza a resposta HTTP
            client.println();
            break;
          } else {  
            currentLine = "";  // Limpa a linha atual
          }
        } else if (c != '\r') {  
          currentLine += c;  // Adiciona o caractere à linha atual
        }

        // Verifica qual comando foi recebido e chama a função apropriada
        if (currentLine.endsWith("GET /azul")) {
          Serial.println("Comando: Azul");
          Azul();
        }

        if (currentLine.endsWith("GET /verde")) {
          Serial.println("Comando: Verde");
          Verde();
        }

        if (currentLine.endsWith("GET /vermelho")) {
          Serial.println("Comando: Vermelho");
          Vermelho();
        }

        if (currentLine.endsWith("GET /branco")) {
          Serial.println("Comando: Branco");
          Branco();
        }

        if (currentLine.endsWith("GET /roxo")) {
          Serial.println("Comando: Roxo");
          Roxo();
        }

        if (currentLine.endsWith("GET /amarelo")) {
          Serial.println("Comando: Amarelo");
          Amarelo();
        }

        if (currentLine.endsWith("GET /desliga")) {
          Serial.println("Comando: Desliga");
          Desliga();
        }
      }
    }
    // Fecha a conexão com o cliente
    client.stop();
    Serial.println("Cliente Desconectado.");
  }
  delay(100);  // Pequeno delay para evitar processamento rápido demais
}

// Funções para controle dos LEDs
void Vermelho() {
  digitalWrite(azul, LOW);
  digitalWrite(verde, LOW);
  digitalWrite(vermelho, HIGH);
}

void Verde() {
  digitalWrite(azul, LOW);
  digitalWrite(verde, HIGH);
  digitalWrite(vermelho, LOW);
}

void Azul() {
  digitalWrite(azul, HIGH);
  digitalWrite(verde, LOW);
  digitalWrite(vermelho, LOW);
}

void Branco() {
  digitalWrite(azul, HIGH);
  digitalWrite(vermelho, HIGH);
  digitalWrite(verde, HIGH);
}

void Roxo() {
  digitalWrite(azul, HIGH);
  digitalWrite(verde, LOW);
  digitalWrite(vermelho, HIGH);
}

void Amarelo() {
  digitalWrite(azul, LOW);
  digitalWrite(verde, HIGH);
  digitalWrite(vermelho, HIGH);
}

void Desliga() {
  digitalWrite(azul, LOW);
  digitalWrite(vermelho, LOW);
  digitalWrite(verde, LOW);
}
