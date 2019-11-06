#include <Arduino.h>

#include <WiFi.h>
#include <HTTPClient.h>
#include <SPI.h>
#include <MFRC522.h>
#include <ESP32Ping.h>

#define SS_PIN 23
#define RST_PIN 5

MFRC522 mfrc522(SS_PIN, RST_PIN); // Create MFRC522 instance.



unsigned long WiFiMillis = 0;
unsigned long previousMillis = 0;
int id[4];

void setup()
{
    Serial.begin(9600);
    pinMode(25, OUTPUT);
    pinMode(33, OUTPUT);
    pinMode(14, OUTPUT);
    pinMode(27, OUTPUT);
    pinMode(26, OUTPUT);
    pinMode(4, OUTPUT);
    ledcSetup(0, 5000, 8);
    ledcSetup(1, 5000, 8);
    ledcSetup(2, 5000, 8);
    ledcSetup(3, 5000, 8);
    ledcSetup(4, 5000, 8);
    ledcAttachPin(25, 0);
    ledcAttachPin(33, 1);
    ledcAttachPin(14, 2);
    ledcAttachPin(27, 3);
    ledcAttachPin(26, 4);
    ledcWrite(2, 15); //power led

    delay(10);
    Serial.println();
    Serial.print("Connecting to network: ");


    WiFi.begin("Catchuga", "scudcatchau");
    int i =0;
    while (WiFi.status() != WL_CONNECTED)
    {
        if(i>20){
          Serial.println("restarting");
          ESP.restart();
        }
        delay(1000);
        Serial.println("Connecting to WiFi..");
        ~Serial.println(i);
        ledcWrite(0, 200); //wifi error
        ledcWrite(1, 0);   //wifi ok
        i++;
    }

    SPI.begin(21, 18, 19, SS_PIN); // Init SPI bus
    mfrc522.PCD_Init();            // Init MFRC522 card
    Serial.println("Scan PICC to see UID and type...");
    delay(50);
    mfrc522.PCD_DumpVersionToSerial();
    mfrc522.uid.uidByte[0] = 0x00;
    mfrc522.uid.uidByte[1] = 0x00;
    mfrc522.uid.uidByte[2] = 0x00;
    mfrc522.uid.uidByte[3] = 0x00;
    id[0] = 0x00;
    id[1] = 0x00;
    id[2] = 0x00;
    id[3] = 0x00;
    
  Serial.printf("\nsetup() em core: %d", xPortGetCoreID());//Mostra no monitor em qual core o setup() foi chamado
  xTaskCreatePinnedToCore(loop2, "loop2", 8192, NULL, 1, NULL, 0);//Cria a tarefa "loop2()" com prioridade 1, atribuída ao core 0
}

void loop2(void*z)//Atribuímos o loop2 ao core 0, com prioridade 1
{
  //Serial.println("\nloop2() em core: %d", xPortGetCoreID());//Mostra no monitor em qual core o loop2() foi chamado
  while (true)//Pisca o led infinitamente
  {
    Serial.println("pingando");
    if(!Ping.ping("www.google.com")){
        ESP.restart();
      }
    delay(20000);
  }
}

void loop()
{
  //Serial.printf("\nloop() em core: %d", xPortGetCoreID());//Mostra no monitor em qual core o loop() foi chamado
  //while(true){
    // wait for WiFi connection
    //if ((wifiMulti.run() == WL_CONNECTED))
    //{
    //Serial.println("loop");
    unsigned long currentMillis = millis();
    WiFiMillis = millis();

    ledcWrite(1, 15); //wifi ok
    ledcWrite(0, 0);  //wifi error
    while (WiFi.status() != WL_CONNECTED)
    {
        delay(100);
        //Serial.println("Connecting to WiFi..");
        currentMillis = millis();
        ledcWrite(0, 200); //wifi error
        ledcWrite(1, 0);   //wifi ok
        if(currentMillis-WiFiMillis > 20000){
          ESP.restart();
        }
    }
    // Look for new cards
    if (!mfrc522.PICC_IsNewCardPresent())
    {
        return;
    }

    // Select one of the cards
    if (!mfrc522.PICC_ReadCardSerial())
    {
        return;
    }

    if(currentMillis-previousMillis>60000){
      
        id[0]=0x00;
        id[1]=0x00;
        id[2]=0x00;
        id[3]=0x00;
        previousMillis = currentMillis;
    }

    // Dump debug info about the card. PICC_HaltA() is automatically called.
    //mfrc522.PICC_DumpToSerial(&(mfrc522.uid));

    if (mfrc522.uid.uidByte[0] != 0x00 &&
        mfrc522.uid.uidByte[1] != 0x00 &&
        mfrc522.uid.uidByte[2] != 0x00 &&
        mfrc522.uid.uidByte[3] != 0x00 &&
        mfrc522.uid.uidByte[0] != id[0] &&
        mfrc522.uid.uidByte[1] != id[1] &&
        mfrc522.uid.uidByte[2] != id[2] &&
        mfrc522.uid.uidByte[3] != id[3])
    {
        //if (currentMillis - previousMillis >= 60000 &&
        //    mfrc522.uid.uidByte[0] != id[0] &&
        //    mfrc522.uid.uidByte[1] != id[1] &&
        //    mfrc522.uid.uidByte[2] != id[2] &&
        //    mfrc522.uid.uidByte[3] != id[3])
        //{
        previousMillis = currentMillis;
        // turn your LED on

        HTTPClient http;

        // configure traged server and url
        String str1 = String(mfrc522.uid.uidByte[0], HEX);
        while (str1.length() < 2) {
            str1 = "0" + str1;
        }
        String str2 = String(mfrc522.uid.uidByte[1], HEX);
        while (str2.length() < 2) {
            str2 = "0" + str2;
        }
        String str3 = String(mfrc522.uid.uidByte[2], HEX);
        while (str3.length() < 2) {
            str3 = "0" + str3;
        }
        String str4 = String(mfrc522.uid.uidByte[3], HEX);
        while (str4.length() < 2) {
            str4 = "0" + str4;
        }
        delay(10);
        http.begin("http://us-central1-scuderia-controle.cloudfunctions.net/Entrada/?ID=" + str1 + str2 + str3 + str4); //HTTP
        // start connection and send HTTP header
        int httpCode = http.GET();

        // httpCode will be negative on error
        if (httpCode > 0)
        {
            // HTTP header has been send and Server response header has been handled

            // file found at server
            if (httpCode == HTTP_CODE_OK)
            {
                String payload = http.getString();
                Serial.println(payload);
                if (payload == "ok")
                {

                    ledcWrite(4, 15); //server ok
                    digitalWrite(4,HIGH);
                    delay(500);
                    ledcWrite(4, 0); //server ok
                    digitalWrite(4,LOW);
                }
                else
                {
                    for (int i = 0; i < 5; i++)
                    {
                        ledcWrite(3, 200); //server error
                        digitalWrite(4,HIGH);
                        delay(100);
                        ledcWrite(3, 0); //server error
                        digitalWrite(4,LOW);
                        delay(100);
                    }
                }
            }
        }

        http.end();
        id[0] = mfrc522.uid.uidByte[0];
        id[1] = mfrc522.uid.uidByte[1];
        id[2] = mfrc522.uid.uidByte[2];
        id[3] = mfrc522.uid.uidByte[3];

        mfrc522.uid.uidByte[0] = 0x00;
        mfrc522.uid.uidByte[1] = 0x00;
        mfrc522.uid.uidByte[2] = 0x00;
        mfrc522.uid.uidByte[3] = 0x00;
    }
    //}else{
    //    ledcWrite(0, 200);//wifi error
    //    ledcWrite(1, 0);//wifi ok
    //}
  //}
}
// editado em 15/08/2019 por Leonardo