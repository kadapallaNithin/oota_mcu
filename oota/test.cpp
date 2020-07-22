#include "test.h"
#include "serial.h"
void test_store(){
  serial(9600);
  String s = Serial.readStringUntil('\r\n');
  store(1024,s);
  String f = fetch(1024,s.length());
  Serial.print(f);
}
bool frequent(){
  return false;//frequent request attack => true
}
