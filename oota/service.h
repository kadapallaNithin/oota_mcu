#ifndef service_nithin_h
#define service__nithin_h
//#include <ArduinoJson.h>
#include <ESP8266WebServer.h>
#include "ROM.h"//for KEY_LEN
#include "dispense.h"
#include "main.h"//for DEVICE_ID
#include "test.h"
#define FREQUENT_MES_DELAY 5000
#define WAITING_TIME 10000000
#define SERVICE_TURN 1
#define SERVICE_FINISH 2
#define INDEX_PAGE "https://nithiniot.pythonanywhere.com/" //"http://kurthi.byethost5.com/oota"
// Current time
extern unsigned long currentTime;// = millis();
// Previous time
extern unsigned long previousTime;// = currentTime; 
// Define timeout time in milliseconds (example: 2000ms = 2s)
extern const long timeoutTime;// = 2000;
extern String header;// Variable to store the HTTP request
extern String server_key;// = "3f82bff4c736d594b2f74e99939c015ff5d44a1e32679b0d33479b0984d5f83577d61c958a6703bcbcec3f706d6e3c17bac11e688a118cac6b54c2030e8ed6bc";//wifi


//void refresh_client(client,page,St);
void service(WiFiClient);//uses:rom.h/store_count_per_ml
void client_print(WiFiClient,bool,int,String);
#endif
