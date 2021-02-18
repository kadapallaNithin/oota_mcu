#include "ROM.h"
 /*
  * cash_bytes (actually can't bcz attacker can get all the cash along with key) help when attacker gets key and don't use it.
  * Server gives same key to user. 
  * After user starts transaction, if only product_key is used to authenticate, 
  * attacker can finish the transaction.
  * 
  * 
  * 
  */
#define MAX_MISMATCH 5
unsigned int mismatch_count = 0;


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

void store_product_key(String key){
  EEPROM.begin(PRODUCT_KEY_TO);
  for(int i=PRODUCT_KEY_FROM; i<PRODUCT_KEY_TO; i++){
    EEPROM.write(i,key[i]);
  }
  EEPROM.commit();
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
void store(int from,String data,bool end_char){
  EEPROM.begin(1224);
  //int to = from+data.length();
  int ind;
  for(ind = 0; ind < data.length(); ind++){
    EEPROM.write(from+ind,data[ind]);
    //STDOUT.print(data[ind]);
  }
  if(end_char){
    EEPROM.write(ind,'\0');
  }
  EEPROM.end();
}
bool cash_match(String cash){
  String my_cash = fetch(384,649);//1224
  Serial.println(cash.length());
  Serial.println(cash);
  for(int i = 0; i<cash.length(); i++){
    if(my_cash[i] != cash[i]){
      STDERR.print("\nCash mismatch @ ");
      STDERR.print(my_cash[i]);
      mismatch_count++;
      if(mismatch_count == MAX_MISMATCH){// required only if cash is stored inconsistently
          String s = browse_with_ip_id_password(SERVER_ADDRESS+"cash_recover/?cash="+cash);
          mismatch_count = 0;
          if(s.length() > 0){
              store(384,s,false);
              Serial.print(fetch(384,649));//1224
              Serial.print(s);
              return true;
          }
      }
      return false;
    }
  }
  //renew_cash(browse_with_ip_id_password(SERVER_ADDRESS+"/api/cash?cash="+cash));
  String s = browse_with_ip_id_password(SERVER_ADDRESS+"cash/?cash="+cash);
  store(384,s,false);
//  if(mismatch_count == MAX_MISMATCH){
//    mismatch_count = 0;
//    return false;
//  }
//  mismatch_count = 0;
  return true;
}
int rom_store(String server_key,String password , String ssid){
//  if(is_reset){
    EEPROM.begin(1024);
    int addr;
    for(addr = SERVER_KEY_FROM;addr <= SERVER_KEY_TO; addr++){
      EEPROM.write(addr,server_key[addr-SERVER_KEY_FROM]);
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
  if(is_reset){
    EEPROM.begin(1024);
    String ke = "";
    int addr = SERVER_KEY_FROM;
    while(addr <= SERVER_KEY_TO){
//    if(addr != 51){
        ke += String((char)EEPROM.read(addr));
//    }
      addr = addr + 1; 
    }
    server_key = ke;
//    return ke;
  }
  return server_key;
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
