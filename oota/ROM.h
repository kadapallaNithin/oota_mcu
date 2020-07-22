#ifndef ROM_h
#define ROM_h
#include<EEPROM.h>
#include <ESP8266WiFi.h>
#include "browser.h" //get_full_cash(), SERVER_ADDRESS
#include "main.h"// for STDERR and is_reset
const byte  KEYLEN = 128;// wifi/request()
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
#endif
