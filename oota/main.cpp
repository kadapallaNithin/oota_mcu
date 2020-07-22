#include "main.h"
volatile unsigned long counter;// = 0;//used_by:dispense/stop_dispense()
unsigned long required_count;// = 0;//used_by:dispense/stop_dispense()

String substringUntil(String s,char del){
  /*String r = "";
  for(int i=0; i<s.length(); i++){
    if(s[i] == del){
      break;
    }
  }*/
  return s.substring(0,s.indexOf(del));//r;
}
/*JsonObject param(String s){
  StaticJsonDocument doc(s.length());
  String k = "";
  for(int i=0; i<s.length(); i++){
    if(s[i] == '&'){
      
    }else if(s[i] == '='){
      
    }
  }
}
*/
