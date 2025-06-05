#include <Arduino.h>
#include <WiFi.h>
#include <PubSubClient.h>
#include <ArduinoJson.h>
#include <time.h>

// Variáveis Globais //----------------------------------------------------------



// Definindo os pinos dos potenciômetros
const int PH_PIN = 34;     // GPIO34 (entrada analógica)
const int TURBID_PIN = 35; // GPIO35 (entrada analógica)
const int NIVEL_PIN = 32;  // GPIO32 (entrada analógica)

// Identificadores
const int IdDevice = 1;
const char *moduleID = "iot-paulista-res01-001";

// Wi-Fi
const char *SSID = "Wokwi-GUEST";
const char *PASSWORD = "";

// MQTT Broker
const char *BROKER_MQTT = "broker.hivemq.com";
const int BROKER_PORT = 1883;

const char *mqttUser = "";
const char *mqttPassword = "";

// Tópico MQTT
#define TOPICO_PUBLISH "LEITURA_RESERVATORIO"

WiFiClient net;
PubSubClient cliente(net);
char buffer[256]; // Buffer para o JSON serializado

// Configuração NTP (NetWork Time Protocol)
const char* ntpServer = "pool.ntp.org";
const long gmtOffset_sec = -3 * 3600; // Fuso horário para GMT-3 convertido de horas para segundos
const int dayLightOffset_sec = 0; // Configuração para horário de verão


// Conexão WiFi //----------------------------------------------------------
void connectWifi()
{
  WiFi.begin(SSID, PASSWORD);
  Serial.println("Conectando-se ao WiFi...");

  while (WiFi.status() != WL_CONNECTED)
  {
    delay(1000);
    Serial.print("_");
  }
  Serial.println("\nWiFi Conectado!");
  Serial.println("IP: ");
  Serial.print(WiFi.localIP());
  Serial.println("MAC Address: ");
  Serial.print(WiFi.macAddress());
}

void reconnectWiFi()
{
  if (WiFi.status() != WL_CONNECTED)
  {
    Serial.println("Reconectando Wi-Fi...");
    connectWifi();
  }
}


// Conexão MQTT//----------------------------------------------------------
void connectMqtt() {
  cliente.setServer(BROKER_MQTT, BROKER_PORT);
  while (!cliente.connected()) {
    Serial.println("\nConectando ao Broker MQTT...");
    if (cliente.connect(moduleID)) {
      Serial.println("Conectado ao Broker!");
    }
  }
}

void checkConnectionsWifiAndMqtt() {
    reconnectWiFi();
    if (!cliente.connected()) {
        connectMqtt();
    }
    cliente.loop();
}

// Envio e feedback //---------------------------------------------------------

void publishBufferMqtt() {
    cliente.publish(TOPICO_PUBLISH, buffer);
}

// void piscaLed() {
//     digitalWrite(boardLED, HIGH);
//     delay(300);
//     digitalWrite(boardLED, LOW);
// }


// Setup inicial //----------------------------------------------------------

void setup()
{
  Serial.begin(115200); // Inicializa o monitor serial
  Serial.println("Simulação de sensores iniciada!");
  connectWifi();
  connectMqtt();
  // Sincronização da hora
  configTime(gmtOffset_sec, dayLightOffset_sec, ntpServer);
}

void loop()
{
  checkConnectionsWifiAndMqtt();

  JsonDocument doc;

  // Id's
  doc["Sensor"] = moduleID;
  

  // Rede
  // doc["IP"] = WiFi.localIP();

  // Data e hora atual
  struct tm timeinfo;
  char timeString[25];
  if (getLocalTime(&timeinfo)) {
    strftime(timeString, sizeof(timeString), "%Y-%m-%dT%H:%M:%S", &timeinfo);
  } else {
    strcpy(timeString, "failed");
  }

  // Aplica Data e hora ao JSON
  doc["ReadingDatetime"] = timeString;

  // Lê os valores dos potenciômetros
  float phValue = map(analogRead(PH_PIN), 0, 4095, 0.00, 14.00);
  int turbidezValue = map(analogRead(TURBID_PIN), 0, 4095, 0, 30);
  int nivelValue = map(analogRead(NIVEL_PIN), 0, 4095, 0, 100);
  
  // Dados dos sensores
  doc["LevelPct"] = nivelValue;
  doc["TurbidityNtu"] = turbidezValue;
  doc["PhLevel"] = phValue;
  doc["IdDevice"] = IdDevice;
  serializeJson(doc, buffer);

  bool ok = cliente.publish(TOPICO_PUBLISH, buffer);
  if (ok) {
    Serial.println("Dados publicados: ");
    Serial.println(buffer);
  } else {
    Serial.println("Falha ao publicar dados");
  }

  // publishBufferMqtt();

  delay(10000); // Aguarda 10 segundos para próxima leitura
}