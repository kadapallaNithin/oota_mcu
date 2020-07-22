#include "dispense.h"
int dispensing_for = DF_NONE; // 0 for none, -1 for error @ dispense_water(ml,user,cash)
bool dispensing = false;//loop,sense_count
const byte valve = 5;
const byte output2 = 2;
const byte sensor = 4;

int count_per_ml = 400;

void sense_count(){
  if( counter >= required_count && dispensing ){
    dispensing = false;
    digitalWrite(valve,LOW);
    digitalWrite(LED_BUILTIN,HIGH);
    //stop_dispense();
  }
  counter++;
}
// global dispensing_for, count_per_ml, dispensing
//used_by:dispense_water(ml,user,cash)
int dispense_water(int ml,int user){
  if(dispensing_for == DF_NONE && !dispensing){
    int df ;//= fetch_dispensing_for();
    int count0 = fetch_counter_data(&df); 
    if(df != 0){
//      dispensing_for = df;
      stop_dispense(df,count0);
    }
      required_count = ml*count_per_ml;
      Serial.print("Required count set to ");
      Serial.print(required_count);
      Serial.print(" i.e ml = ");
      Serial.println(ml);
      store_dispensing_for(user);
      dispensing_for = user;
      dispensing = true;
      int count = counter;
      counter = 0;
      if(count > 0){
        Serial.println("Unexpected! counter = "+String(count)+" in dispense_water");
      }
      digitalWrite(valve,HIGH);
      digitalWrite(LED_BUILTIN,LOW);
      return DF_NONE;
  }else{
    return dispensing_for;
  }
}
/*
 * used_by_not_now:service/service
 * may_be_in_future
 *
 *
 */
int dispense_water(int m,int user,String cash){
  if(cash_match(cash)){
    return dispense_water(m,user);
  }else{
    return -2;// error
  }
}
// global dispensing_for, counter
/*void stop_dispense(){
  int count = counter;
  counter = 0;
  int req = required_count;
  required_count = 0;
  int user = dispensing_for;
  dispensing_for = DF_NONE;
  dispensing = false;
  digitalWrite(valve,LOW);
  digitalWrite(LED_BUILTIN,HIGH);
  Serial.println("Stop dispense"+String(req)+","+String(count));
  String address = "http://skin-lime.000webhostapp.com/api/finish.php?password=nithinPk&value="+String(count)+"&id=1&at="+String(millis())+"&user="+user;
  send_sensor_value_to(address);
  store_status(1);
}*/
/* setup {stop_dispense()}
 *  
 */
void stop_dispense(int user,unsigned long count){
  digitalWrite(valve,LOW);
  digitalWrite(LED_BUILTIN,HIGH);
  counter = 0;
  required_count = 0;
  dispensing_for = DF_NONE;
  dispensing = false;
  //renew_cash(
  browse_with_ip_id_password("http://skin-lime.000webhostapp.com/api/finish.php?value="+String(count)+"&at="+String(millis())+"&user="+user);
  //,count/count_per_ml);
  
  reset_counter_data();  
}
/* 
 * uses:
 * counter,valve,LED_BUILTIN,required_count,dispensing_for,DF_NONE,dispensing,send_sensor_value_to(address),reset_counter_data()
 * used_by:
 * stop_dispense(user) 
 */
/*

 DON'T CHANGE OR CHANGE ABOVE TOO

*/
/* assuming everything is ok after commenting inner code ..
unsigned long stop_dispense(){
  digitalWrite(valve,LOW);
  digitalWrite(LED_BUILTIN,HIGH);
  int user;
  int count = counter;
  counter = 0;
  /*int fcount = fetch_counter_data(&user);
  if( fcount > count){
    count = fcount;
    for(int i = 0; i<10; i++)
      Serial.println("*");
    //user = fetch_dispensing_for();
  }else{*
    user = dispensing_for;
  //}
  int req = required_count;
  required_count = 0;
  dispensing_for = DF_NONE;
  dispensing = false;
  Serial.println("Stop dispense"+String(req)+","+String(count));
  String address = "http://skin-lime.000webhostapp.com/api/finish.php?password=nithinPk&value="+String(count)+"&id=1&at="+String(millis())+"&user="+user;
  send_sensor_value_to(address);
  //store_status(true);
  //store_dispensing_for(0);
  //store_counter(0);
  reset_counter_data();
  return count;
}*/
/* 
 * uses:
 * counter,valve,LED_BUILTIN,required_count,dispensing_for,DF_NONE,dispensing,send_sensor_value_to(address),reset_counter_data()
 * used_by:
 * stop_dispense(user) 
 */
unsigned long stop_dispense(){
    unsigned long count = counter;
    stop_dispense(dispensing_for,counter);
    return count;
}
/*
 * uses: dispensing_for,stop_dispense()
 * used  by:
 * dispense_water,service/service 
 */
int stop_dispense(int user){
  if(user == dispensing_for ){
    return stop_dispense();
  }
  return -1;
}
