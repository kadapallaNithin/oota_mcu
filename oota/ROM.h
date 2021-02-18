#ifndef ROM_h
#define ROM_h
#include<EEPROM.h>
#include <ESP8266WiFi.h>
#include "browser.h" //get_full_cash(), SERVER_ADDRESS
#include "main.h"// for STDERR and is_reset
#include "wifi.h" //server_key
//const byte  KEYLEN = 128;// wifi/request()

/*
 * 160 - 163 counter(4) unsigned long
 * 167 - 168 user(2) unsigned short (0 - 65535] 0 - none //165,6 are reserved for user but not used
 * 169 - 170 cpml(2)
 * 
 */
#define PASSWORD_FROM     128 //16B
#define PASSWORD_TO       143
#define SSID_FROM         144 //16B
#define SSID_TO           159
#define PRODUCT_KEY_FROM  256 //128B
#define PRODUCT_KEY_TO    383
#define SERVER_KEY_FROM   384   //128B
#define SERVER_KEY_TO     511
/*
 * 200 - 1224 cash_bytes not now
 * 200 - 456 cash_bytes_not_now
 * 384 - 649 cash_bytes (256)
 */
String fetch(int,int);
void store(int,String);
void store_dispensing_for(unsigned short int);
void reset_counter_data();//used_by:dispense/stop_dispense()
unsigned long fetch_counter_data(int*);//used_by:dispense/
int count_per_ml_fetch();//used_by: setup
void store_count_per_ml(int cpml);//used_by:service/service
int rom_store(String,String , String);//used_by:wifi/request
String get_server_key();//used_by:wifi
void store_counter(unsigned long);//used_by:loop
bool cash_match(String);//used_by:renew_cash,dispense/dispense_water(ml,user,cash)
void renew_cash(String,int);//used_by:cash_match ( before dispense/stop_dispense)
void store_product_key(String);
#endif
