//#include "ROM.h" //count_per_ml_fetch()
//#include "wifi.h"// included in serial.h //for request in setup, ensure_connect() in loop
//"main.h" //in serial.h //for STDLOG

#include "service.h"      //for DEVICE_ID, product_id in setup
#include "serial.h"       //for serial_config()
extern String product_key;

const int period = 5000;//used_by:loop
unsigned long t0 = millis();//currentTime;//used_by:loop
int prevCount = 0;//used_by:loop                                      //int owner_lock = -1;

void setup() {
  Serial.begin(9600);
  serial_configure();
 // Initialize the output variables as outputs
  pinMode(valve,OUTPUT);
  pinMode(output2,OUTPUT);
  pinMode(sensor,INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(sensor),sense_count,FALLING);
  // Set outputs to LOW
  digitalWrite(valve, LOW);
  digitalWrite(output2, HIGH);
  count_per_ml = count_per_ml_fetch();
  //server_key = 
  STDLOG.print(count_per_ml);
  request(1);
  product_key = "nithinkumar";//fetch(PRODUCT_KEY_FROM,PRODUCT_KEY_TO);
  server_begin();
  //store(200,"nithinkumarkadapallanithinkumarkadapallannnnnnnnnnn");
  //String s = fetch(200,1224);
  //Serial.println(s);//
  
}
void loop(){
  //test_store();

  ensure_connect();
//  WiFiClient client = server.available();
//  if (client) {
//    service(client);
//  }
  server.handleClient();
  if(dispensing_for != DF_NONE){
    if( (millis() - t0 > period) && prevCount != counter){// && dispensing
      store_counter(counter);
      send_sensor_value(counter,millis());
      prevCount = counter;
      t0 = millis();
      STDLOG.println(counter);
      STDLOG.println(required_count);
    }
    if(!dispensing){stop_dispense();}
  }
}
