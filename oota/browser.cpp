#include "browser.h"
HTTPClient http;
/*
 * uses:
 *  wifi/ensure_connect
 *
void post(String address){
   ensure_connect();
   
}
*/
// used_by:stop_dispense(int user,unsigned long count)
// uses : wifi/my_ip()
String browse_with_ip_id_password(String address){//send_sensor_value_to
    String ip = my_ip();
//    String address = "http://skin-lime.000webhostapp.com/api/store.php?password=nithinPk&ip="+ip+"&value="+count+"&id=1&at="+at;

    address += "&ip="+ip+"&id="+DEVICE_ID+"&password=nithinPk";
    http.begin(address);//Specify request destination
    STDOUT.println("Getting from "+address);
    int httpCode = http.GET();
    while(httpCode != 200){
      httpCode = http.GET();
      STDOUT.println(httpCode);
      delay(1000);
    }
    String payload = http.getString();
    STDOUT.println(payload);
    return payload;
    http.end();   //Close connection
    STDOUT.println("HTTP END");
}
void send_sensor_value(int count,long at){//maybe optimized by sending huge data at a time.
  http.begin(SERVER_ADDRESS+"/sensor_value/?value="+String(count)+"&at="+at+"&user="+dispensing_for+"&server_key=nithin&id="+DEVICE_ID);//"/api/store.php?value="+String(count)+"&at="+at+"&user="+dispensing_for+"&password=nithinPk&id="+DEVICE_ID);
  while(http.GET() != 200){
    delay(1000);
  }
}
String get_full_cash(String old){
  browse_with_ip_id_password(SERVER_ADDRESS+"/api/cash.php?old="+old);
}
