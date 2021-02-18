#ifndef browser_nithin_h
#define browser_nithin_h
#include "main.h"//4 DEVICE_ID
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include "wifi.h"// for my_ip() in browse_with_ip_id_password()
#include "dispense.h"
#include "ROM.h" //get_server_key()
//used_by : wifi/request()
#define SERVER_ADDRESS String("http://192.168.43.85:8000/") //String("http://nithiniot.pythonanywhere.com/")//http://nithiniot.pythonanywhere.com/")//http://skin-lime.000webhostapp.com
//#define REDIRECT_LINK String("http://nithinkadapalla.pythonanywhere.com/") defined as INDEX_PAGE @ service.h
extern HTTPClient http; //used_by: wifi/request()
String browse_with_ip_id_password(String);//dispense/stop_dispense()
String browse(String);//dispense_water(int,int)
void send_sensor_value(int,long );
String get_full_cash(String);//ROM/renew_cash
#endif
