#ifndef dispense_nithin_h
#define dispense_nithin_h
#include "ROM.h"
#include "main.h"
#include "browser.h"//4 browse_with_ip_id_password()
#define DF_NONE -1 // also real user should be in 1 to 2^(16)-1 and not be 0 - reserved for no pending finish
void ICACHE_RAM_ATTR sense_count();
// used_by: stop_dispense(user),browser/send_sensor_value()
extern int dispensing_for;// = DF_NONE; // 0 for none -2 for cash_mismatch error @ dispense_water(int m,int user,String cash)
extern bool dispensing;// = false;

/* Auxiliar variables to store the current output state
String valveState = "off";
String output2State = "off";
*/
//Memory mem;
// Assign output variables to GPIO pins
extern const byte valve;// = 5;
extern const byte output2;// = 2;
extern const byte sensor;// = 4;

extern int count_per_ml;// = 400;
//int dispense_water(int,int,String);
int dispense_water(int,int);
void stop_dispense(int,unsigned long);
unsigned long stop_dispense();
int stop_dispense(int);
#endif
