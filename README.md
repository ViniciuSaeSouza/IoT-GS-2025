# 🌎 Global Solutions - 2025 - 1º Semestre

## 💧 +Água: Sistema IoT e Dashboard para Gestão de Água

O projeto **+Água** é uma solução integrada com tecnologia **IoT** e um **dashboard interativo** em **Node-RED**, voltada para o monitoramento inteligente do consumo e armazenamento de água em condomínios residenciais. A proposta busca incentivar o uso consciente e promover a gestão eficiente dos recursos hídricos.

---

## 📋 Funcionalidades Principais

### 🔌 IoT

* **Monitoramento em tempo real**: Coleta contínua dos níveis de água por sensores instalados em reservatórios.
* **Conectividade via MQTT e Wi-Fi**: Comunicação leve e eficiente entre sensores e o sistema.
* **Sincronização NTP**: Garantia de precisão nos registros com sincronização horária automática.

### 📊 Dashboard (Node-RED)

* **Visualização em tempo real** dos dados recebidos via MQTT.
* **Alertas visuais dinâmicos** para sinalização de níveis críticos.
* **Gráficos históricos** e indicadores de consumo para tomada de decisão.
* **Interface responsiva** e de fácil uso para síndicos e moradores.

---

## 🛠️ Tecnologias Utilizadas

### 🔧 IoT

* **C++ (Arduino Framework)**: Programação embarcada dos dispositivos.
* **ESP8266 / ESP32**: Microcontroladores para aquisição e envio de dados.
* **MQTT**: Protocolo leve e rápido para comunicação entre dispositivos.

### 🧠 Dashboard

* **Node-RED**: Plataforma de baixo código para criação do painel interativo.
* **MQTT Broker (público ou local)**: Responsável por intermediar a troca de mensagens entre dispositivos e o dashboard.

---

## 📂 Estrutura do Projeto

```txt
.
├── IOT/maisAguaV1/         # Código dos dispositivos IoT (ESP)
│   ├── src/                # main.cpp e lógicas de leitura/envio
│   └── include/            # Arquivo de configuração (Wi-Fi, MQTT, etc.)
│
├── NodeRED/                # Fluxo do Node-RED (.json)
│   └── dashboard-flux.json
│
└── Documentos/             # Especificações, atas e relatórios do projeto
```

---

## 🚀 Como Executar

### 🔧 IoT

1. Acesse `IOT/maisAguaV1/src/main.cpp`.
2. Edite as configurações em `include/config.h` com:

   * Nome da rede Wi-Fi
   * Senha da rede
   * Endereço do broker MQTT
   * Tópico e ID do dispositivo
3. Compile e envie o código para o ESP32/ESP8266 usando:

   * **PlatformIO** (VS Code) ou
   * **Arduino IDE**

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
4. Importe o fluxo `dashboard-flux.json` localizado em `NodeRED/`.
5. Acesse o dashboard final em: [http://localhost:1880/ui](http://localhost:1880/ui)

---

## 📖 Documentação Técnica

### 📡 Comunicação MQTT

* **Tópico de publicação**: Exemplo — `maisagua/reservatorio01/status`
* **Formato da mensagem (JSON)**:

  ```json
  {
    "deviceId": "reservatorio01",
    "nivelPorcentagem": 72,
    "timestamp": "2025-06-05T15:30:00Z"
  }
  ```

### 🔔 Fluxo de Dados no Dashboard

* Recepção via MQTT no Node-RED
* Atualização dos indicadores visuais
* Armazenamento opcional em banco de dados (extensível)
* Exibição de gráficos e históricos com base nos dados recebidos

---

## 📌 Notas Importantes

* Certifique-se de que o **broker MQTT está ativo** antes de ligar os dispositivos e iniciar o dashboard.
* Verifique a **calibração dos sensores** para garantir dados confiáveis.
* O código permite **expansão para múltiplos reservatórios**, bastando alterar os `deviceId` e tópicos MQTT.

---

## 📞 Contato da Equipe

Em caso de dúvidas, melhorias ou sugestões, entre em contato com a equipe do projeto:

* **Laura de Oliveira Cintra** — RM 558843
* **Maria Eduarda Alves da Paixão** — RM 558832
* **Vinícius Saes de Souza** — RM 554456

---

> “Faça o teu melhor, na condição que você tem, enquanto você não tem condições melhores, para fazer melhor ainda.” — Mario Sergio Cortella