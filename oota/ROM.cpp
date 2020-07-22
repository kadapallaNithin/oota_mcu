#include "ROM.h"
/*
 * EEPROM 
 * 0 - 127 server_key(128)
 * 128 - 143 password(16)
 * 144 - 159 ssid(16)
 * 160 - 163 counter(4) unsigned long
 * 167 - 168 user(2) unsigned short (0 - 65535] 0 - none //165,6 are reserved for user but not used
 * 169 - 170 cpml(2)
 * 
 * 200 - 1224 cash_bytes
 */
void store_count_per_ml(int cpml){
  EEPROM.begin(256);
  EEPROM.write(169,(cpml%(256*256))/256);
  //Serial.print("cpml = "+String(cpml)+" b "+String((cpml%(256*256))/256));
  EEPROM.write(170,cpml%256);
  EEPROM.commit();
}
int count_per_ml_fetch(){
  EEPROM.begin(256);
  return EEPROM.read(169)*256 + EEPROM.read(170);
}
void store_int(int addr,unsigned int count){
    //int b[4];
    int b0 = count/(16777216);
    int b1 =(count%(16777216))/(65536);
    int b2 =(count%(65536))/256;
    int b3 = count % 256;
    Serial.print("count"+String(count));
    EEPROM.begin(512);
    EEPROM.write(addr,b0);    
    EEPROM.write(addr+1,b1);
    EEPROM.write(addr+2,b2);
    EEPROM.write(addr+3,b3);
    EEPROM.commit();
}
void store_short(int addr,int cpml){
  EEPROM.begin(512);
  EEPROM.write(addr,(cpml%(256*256))/256);
  //Serial.print("cpml = "+String(cpml)+" b "+String((cpml%(256*256))/256));
  EEPROM.write(addr+1,cpml%256);
  EEPROM.commit();
}

void store_dispensing_for(unsigned short int user){
  store_short(167,user);
}
void store_counter(unsigned long count){
  store_int(160,count);
}
unsigned long fetch_int(int addr){
  EEPROM.begin(512);
  return (EEPROM.read(addr)*16777216)+(EEPROM.read(addr+1)*65536 )+(EEPROM.read(addr+2)*256 )+(EEPROM.read(addr+3));
}
unsigned short fetch_short(int addr){
  EEPROM.begin(512);
  int x = EEPROM.read(addr);
  int y = EEPROM.read(addr+1);
  Serial.print(x);
  Serial.println(y);
  return (x*256 )+(y);
}
int fetch_dispensing_for(){
  return fetch_short(167);
}
unsigned long fetch_counter(){
  return fetch_int(160); 
}
void reset_counter_data(){
  store_dispensing_for(0);
  store_counter(0);
}
unsigned long fetch_counter_data(int* user_p){
/*  EEPROM.begin(512);
  int b = EEPROM.read(146);
  if(b > 127){
    
    return ((b-128)*16777216)+(EEPROM.read(146)*65536 )+(EEPROM.read(146)*256 )+(EEPROM.read(146));
  }
  return -1;
*/
  *user_p = fetch_dispensing_for();
  unsigned long co = fetch_counter();
  Serial.println("Counter data ");
  Serial.println("counter : ");
  Serial.println(co);
  return co;
}
String fetch(int from,int to){
  String s="";
  EEPROM.begin(1224);
  for(int addr = from; addr < to; addr++){
    s += String((char)EEPROM.read(addr));
    
  }
//  EEPROM.end();
  delay(10);
  //Serial.println(s);
  return s;
}
void store(int from,String data){
  EEPROM.begin(1224);
  //int to = from+data.length();
  int ind;
  for(ind = 0; ind < data.length(); ind++){
    EEPROM.write(from+ind,data[ind]);
    //STDOUT.print(data[ind]);
  }
  EEPROM.write(ind,'\0');
  EEPROM.end();
  STDOUT.println("commited");
}
bool cash_match(String cash){
  String my_cash = fetch(200,1224);
  Serial.println(cash.length());
  Serial.println(cash);
  for(int i = 0; i<cash.length(); i++){
    if(my_cash[i] != cash[i]){
      STDERR.print("\nCash mismatch @ ");
      STDERR.print(my_cash[i]);
      return false;
    }
  }
  
  //renew_cash(browse_with_ip_id_password(SERVER_ADDRESS+"/api/cash?cash="+cash));
  String s = browse_with_ip_id_password(SERVER_ADDRESS+"/api/cash.php?cash="+cash);
  store(200,s);
  Serial.print(fetch(200,1224));
  Serial.print(s);
  return true;
}
int rom_store(String api_key,String password , String ssid){
//  if(is_reset){
    EEPROM.begin(512);
    int addr;
    for(addr = 0;addr < 128; addr++){
      EEPROM.write(addr,api_key[addr]);
    }
  /*for(addr = 128; addr < 144 && addr < 128 + password.length(); addr++){// before it was addr < password.length()
    EEPROM.write(addr,password[addr]);
  }
  for(addr = 144; addr < 160 && addr < 144 + ssid.length(); addr++){// before it was addr < password.length()
    EEPROM.write(addr,ssid[addr]);
  }*/
    EEPROM.commit();
//    }
}
String get_server_key(){
//  if(is_reset){
    EEPROM.begin(128);
    String ke = "";
    int addr = 0;
    while(addr < 128){
//    if(addr != 51){
        ke += String((char)EEPROM.read(addr));
//    }
      addr = addr + 1; 
    }
    return ke;
//  }
//  return server_key;
//  Serial.print("fetching api_key");
//  return fetch(0,128);
}





/*
void renew_cash(String cash,int len){
    if(cash.length() != len ){
      STDERR.println("Cash count mismatch");
      STDERR.println(cash);
      STDERR.println(len);
      store(1024,get_full_cash(fetch(1024,2048)));
    }else{
      store(1024,cash);
    }
}
*/
/*
void store_status(bool done){
  if(done){
    EEPROM.begin(512);
    EEPROM.write(146,0);
    EEPROM.commit();
  }
}
byte fetch_status(){
  EEPROM.begin(512);
  return EEPROM.read(146);
}*/



/*
 * store_user, store_counter
 *//*void store_bytes(int addr,unsigned int count,int bytes){
    byte b[4];
    b[3] = count % 256;
    b[2] = (count%(65536))/256;
    if(bytes > 2){
      b[0] = count/(16777216);
      b[1] = (count%(16777216))/(65536);
    }
    EEPROM.begin(512);
/  Serial.print(b0);
  Serial.print(b1);
  Serial.print(b2);
  Serial.print(b3);
  Serial.println(count);
  
    if(b0 > 127){
      Serial.println();
      Serial.print("Unexpected value ");
      Serial.print(b0);
      Serial.print(" for b0");
    }else{/
    for(int i = addr; i < addr+bytes; i++){
      EEPROM.write(i,b[i]);//+128);
      Serial.print("at ");
      Serial.println(i);
      Serial.println(b[i]);
    }  /*EEPROM.write(147,b1);
      EEPROM.write(148,b2);
      EEPROM.write(149,b3);
    //}/
    EEPROM.commit();
}*/
