#ifndef wifi_nithin_h
#define wifi_nithin_h
#include <ESP8266WiFi.h>
#include <ArduinoJson.h>

#include "ROM.h"
//#include "browser.h"
#include "service.h" //for server_key
//extern const byte PRODUCT_ID;// = 1;
//extern String api_key;
//used_by:serial/serial_config()
extern String ssid;//  = "kadapalla";//"NITAP-Boys Hostel";////"NITAP-Hostels";//"AndroidAP";//"Sathy@";//
//used_by:serial/serial_config()
extern String password;// = "12345678";// "nitap@campus@321";//"nitap@campus123";//"12345678nit";//"sathish@123";//
extern String server_key;
String WiFiConnect();
String request(int);//used_by: setup
void ensure_connect();//used_by: loop()
String my_ip();//used_by:broswer/browse_with_ip_id_password()
//String IpAddress2String(const IPAddress& );//used_by:wifi/WiFiConnect(),ensure_connect(),my_ip()
#endif
