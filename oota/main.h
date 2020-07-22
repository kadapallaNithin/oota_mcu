#ifndef main_nithin_h
#define main_nithin_h
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#define STDERR Serial
#define STDOUT Serial
#define STDLOG Serial
//#include<arduinoJson.h>
#define DEVICE_ID 1 //used_by : wifi/request()
const bool is_reset = 1;
extern volatile unsigned long counter;// = 0;//used_by:dispense/stop_dispense()
extern unsigned long required_count;// = 0;//used_by:dispense/stop_dispense()
//String param(String);//used_by:service/service()
#endif
/*
 *                 main.h ( STDERR, STDOUT, DEVICE_ID, counter, required_count )
 *                 
 *                 
 *                 
 *                 
 *                 
 *                 
 *                 
 *                 
 *                 
 *                 
 *                 
 *                 
 *                 
 *                 
 *                 
 * 
 * 
 * 
 * 
 * 
 * 
 * 
 */
