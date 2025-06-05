# 🌎 Global Solutions - 2025 - 1º Semestre

## 💧 +Água: Sistema IoT e Dashboard para Gestão de Água

O projeto **+Água** é uma solução integrada com tecnologia **IoT** e um **dashboard interativo** em **Node-RED**, voltada para o monitoramento inteligente do consumo e armazenamento de água em condomínios residenciais. A proposta busca incentivar o uso consciente e promover a gestão eficiente dos recursos hídricos, especialmente em cenários de **eventos climáticos extremos**, como **enchentes** e **períodos de seca**, onde o controle preciso da água se torna ainda mais essencial.

---

## 📋 Funcionalidades Principais

### 🔌 IoT

* **Monitoramento em tempo real**: Coleta dos dados dos sensores simulados (potenciômetros) que representam os níveis de água, pH e turbidez.
* **Conectividade via MQTT e Wi-Fi**: Comunicação leve e eficiente entre sensores e o sistema.
* **Sincronização NTP**: Garantia de precisão nos registros com sincronização horária automática.
* **Publicação de dados**: Envio das leituras para o tópico MQTT `LEITURA_RESERVATORIO` no broker público HiveMQ.

### 📊 Dashboard (Node-RED)

* **Visualização em tempo real** dos dados recebidos via MQTT.
* **Alertas visuais dinâmicos** para sinalização de níveis críticos.
* **Gráficos históricos** e indicadores de consumo para tomada de decisão.
* **Interface responsiva** e de fácil uso para síndicos e moradores.

---

## 🛠️ Tecnologias Utilizadas

### 🔧 IoT

* **ESP32**: Microcontrolador utilizado para coleta e envio de dados.
* **C++ (Arduino Framework)**: Programação embarcada do dispositivo.
* **MQTT**: Protocolo leve e rápido para comunicação entre dispositivos.
* **Bibliotecas**:

  * `PubSubClient`: Para comunicação MQTT.
  * `ArduinoJson`: Para manipulação de mensagens JSON.

### 🧠 Dashboard

* **Node-RED**: Plataforma de baixo código para criação do painel interativo.
* **Broker MQTT público**: HiveMQ (`broker.hivemq.com`, porta `1883`).

---

## 📂 Estrutura do Projeto

```txt
.
├── IOT/maisAguaV1/         # Código dos dispositivos IoT (ESP)
│   ├── src/                # main.cpp e lógicas de leitura/envio
│   ├── include/            # config.h com dados de Wi-Fi e MQTT
│   └── diagram.json        # Diagrama de simulação do Wokwi
│
├── IOT/maisAguaV1/node-red/flows/  # Fluxos do Node-RED
│   └── flows.json
│
└── Documentos/             # Especificações, atas e relatórios do projeto
```

---

## 🚀 Como Executar

### 🔧 IoT

1. Acesse `IOT/maisAguaV1/src/main.cpp`.
2. Edite `include/config.h` com:

   ```cpp
   const char *SSID = "SEU_SSID";
   const char *PASSWORD = "SUA_SENHA";
   ```
3. Compile e envie o código para o ESP32 usando:

   * **PlatformIO** (VS Code) ou
   * **Arduino IDE**
4. Abra o monitor serial para verificar as mensagens publicadas no broker MQTT.

### 🌐 Dashboard Node-RED

1. Instale o Node-RED:

   ```bash
   npm install -g node-red
   ```
2. Inicie o serviço:

   ```bash
   node-red
   ```
3. Acesse o editor via navegador: [http://localhost:1880](http://localhost:1880)
4. Importe o fluxo `flows.json` localizado em `IOT/maisAguaV1/node-red/flows/`
5. Acesse o dashboard final em: [http://localhost:1880/ui](http://localhost:1880/ui)

---

## 📖 Documentação Técnica

### 📡 Sensores Simulados

* **pH**: Potenciômetro conectado ao GPIO34.
* **Turbidez**: Potenciômetro conectado ao GPIO35.
* **Nível de água**: Potenciômetro conectado ao GPIO32.

### 📢 Comunicação MQTT

* **Tópico de publicação**: `LEITURA_RESERVATORIO`
* **Formato JSON da mensagem**:

  ```json
  {
    "deviceId": "reservatorio01",
    "nivel": 78,
    "ph": 6.8,
    "turbidez": 120,
    "timestamp": "2025-06-05T15:30:00Z"
  }
  ```

### 🔔 Fluxo de Dados no Dashboard

* Recebimento de dados via MQTT
* Atualização dos indicadores visuais
* Exibição em tempo real no painel web
* Geração de gráficos e histórico de consumo

---

### 🧭 Fluxo Node-RED
- O fluxo é composto por:
  - `mqtt in`: recebe do tópico `LEITURA_RESERVATORIO`
  - `json`: converte a mensagem para objeto
  - `function`: lógica de tratamento e separação de variáveis
  - `ui_chart`, `ui_gauge`, `ui_text`: exibem os dados
- Toda alteração no valor de pH, turbidez e nível gera atualização no dashboard.
---

## 📌 Notas Importantes

* Certifique-se de que o **broker MQTT (HiveMQ)** está ativo antes de ligar os dispositivos e iniciar o dashboard.
* Verifique a **calibração dos sensores simulados** para garantir dados confiáveis.
* O código é adaptável para **vários reservatórios** simultâneos, utilizando IDs e tópicos distintos.

---

## 📞 Contato da Equipe

Em caso de dúvidas, melhorias ou sugestões, entre em contato com a equipe do projeto:

* **Laura de Oliveira Cintra** — RM 558843
* **Maria Eduarda Alves da Paixão** — RM 558832
* **Vinícius Saes de Souza** — RM 554456

---

> “Faça o teu melhor, na condição que você tem, enquanto você não tem condições melhores, para fazer melhor ainda.” — Mario Sergio Cortella
