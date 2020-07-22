#include "serial.h"
void serial(int baud){
  Serial.begin(baud);
  Serial.setTimeout(5);
  while(!Serial){
    ;
  }
}
void read_token(){
  char sz[] = "Here; is some; sample;100;data;1.414;1020";
  String serialResponse = Serial.readStringUntil('\r\n');
  if ( Serial.available()) {
    serialResponse = Serial.readStringUntil('\r\n');

    // Convert from String Object to String.
    char buf[sizeof(sz)];
    serialResponse.toCharArray(buf, sizeof(buf));
    char *p = buf;
    char *str;
    while ((str = strtok_r(p, ";", &p)) != NULL) // delimiter is the semicolon
      Serial.println(str);
  }
}
void serial_send(String s){
  //for
}
String readln(){
  String temp = "";
  char c = ' ';
  while(Serial.available() >0 ){//&& c != '\n' ){
    c = Serial.read();
    if(c != '\n'){
      temp += c;
    }else{
      break;
    }
  }
  return temp;
}
void serial_configure(){
  if(Serial.available()){
    if(Serial.parseInt() == 1){
      ssid = readln();
      password = readln();
    }
  }
}
