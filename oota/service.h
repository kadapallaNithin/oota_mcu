#ifndef service_nithin_h
#define service__nithin_h
//#include <ArduinoJson.h>
#include <ESP8266WebServer.h>
#include "dispense.h"
#include "main.h"//for DEVICE_ID
#include "test.h"
#define FREQUENT_MES_DELAY 5000
#define WAITING_TIME 10000000
#define SERVICE_TURN 1
#define SERVICE_FINISH 2
#define INDEX_PAGE SERVER_ADDRESS //"https://nithiniot.pythonanywhere.com/" //"http://kurthi.byethost5.com/oota"
// Current time
//extern unsigned long currentTime;// = millis();
// Previous time
//extern unsigned long previousTime;// = currentTime; 
// Define timeout time in milliseconds (example: 2000ms = 2s)
//extern const long timeoutTime;// = 2000;
extern ESP8266WebServer server;
extern String header;// Variable to store the HTTP request
extern String product_key;
void server_begin();
void client_print(WiFiClient,bool,int,String);
#endif
