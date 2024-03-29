#include "ROM.h" // for KEYLEN_not_using, rom_store
#include "browser.h" // for SEVER_ADDRESS, http in request, IpAddress2String() in WiFiConnect(),my_ip()
#include "main.h"  // for DEVICE_ID in request
//String api_key;//required only for request
//used_by : wifi/request()
String ssid  = "kadapalla";//"NITAP-Boys Hostel";////"NITAP-Hostels";//"AndroidAP";//"Sathy@";//
//used_by : wifi/request()
String password = "12345678";// "nitap@campus@321";//"nitap@campus123";//"12345678nit";//"sathish@123";//
String server_key = "nithinPk";//3f82bff4c736d594b2f74e99939c015ff5d44a1e32679b0d33479b0984d5f83577d61c958a6703bcbcec3f706d6e3c17bac11e688a118cac6b54c2030e8ed6bc";

String IpAddress2String(const IPAddress& ipAddress)
{
  return String(ipAddress[0]) + String(".") +\
  String(ipAddress[1]) + String(".") +\
  String(ipAddress[2]) + String(".") +\
  String(ipAddress[3]);
}

// used by : wifi/request()
//uses : IpAddress2String(), ssid, password
String WiFiConnect(){
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  String ip = IpAddress2String(WiFi.localIP());
  // Print local IP address // and start web server
  Serial.println("");
  Serial.println("WiFi connected.");
  Serial.println("IP address: ");
  Serial.println(ip);
  return ip;
}

// used by : ensure_connect(), my_ip(), setup()
// uses WiFiConnect(), SERVER_ADDRESS, DEVICE_ID, http, KEYLEN, ssid, password, server_key, rom_store
String request(int is_reset){
  String ip ;
//  if(WiFi.status() != WL_CONNECTED){// removed this bcz without assigning ip, get params in address would be wrong
    ip = WiFiConnect();
//    Serial.println("Reconnecting ");
//  }
    if(is_reset){
      server_key = get_server_key();
      Serial.println(String("server key is")+server_key);
    }
    String address = SERVER_ADDRESS+"product_ip/?key="+server_key+"&ip="+ip+"&id="+DEVICE_ID;//"product_ip/?key="+"nithinPk"+"&ip="+ip+"&prod="+DEVICE_ID;//"api/index.php?password=nithinPk&ip="+ip+"&my_ip="+ip+"&prod="+DEVICE_ID;//"request/?password=nithinPk&ip="+ip+"&my_ip="+ip+"&prod="+DEVICE_ID;//"http://skin-lime.000webhostapp.com/api/index.php?password=nithinPk&ip="+ip+"&my_ip="+ip+"&prod="+DEVICE_ID;
    if(is_reset){
      address += "&is_reset=1";
    }
    http.begin(address);//Specify request destination
    Serial.println("Getting from "+address);
    int httpCode = http.GET();
    while(httpCode != 200){
      httpCode = http.GET();
      Serial.println(httpCode);
      delay(1000);
    }
    //Serial.println();
    //Serial.print("HTTP Code is ");
    //Serial.print(httpCode);
    //Send the request
    if (httpCode > 0) { //Check the returning code
      String payload = http.getString();   //Get the request response payload
      Serial.println(payload);                    //Print the response payload
      Serial.println();
      int return_error = 0;
      StaticJsonDocument<250> doc;
      DeserializationError error = deserializeJson(doc, payload);
      String key;
      if (error) {
        Serial.print(F("deserializeJson() failed: "));
        Serial.println(error.c_str());
        return_error += 8;
      }else{
        key = doc["server_key"].as<String>();
        ssid = doc["ssid"].as<String>();
        password = doc["password"].as<String>();
        if(key == "null"){
          return_error++;
        }
        if(ssid == "null"){
          return_error += 2;
        }
        if(password == "null"){
          return_error += 4;
        }
      }
      if(return_error == 0){
        server_key = get_server_key();
        rom_store(key,password,ssid);
        Serial.println(key);
      }else{
        Serial.print("WiFiConnection error code : ");
        Serial.println(return_error);
        //report error
      }

    }else{
      Serial.println("Unexpected");
    }
    http.end();   //Close connection
    Serial.println("HTTP END");
    return ip;
}
// used_by: browser/post, loop()
void ensure_connect(){
 if(WiFi.status() !=  WL_CONNECTED){
  request(0);
 }
}

//used_by : browser/
String my_ip(){
  if(WiFi.status() != WL_CONNECTED){
      return request(0);
  }else{
    return IpAddress2String(WiFi.localIP());
  }
}


/*
 * 
 *       /*int k = payload.indexOf("\"key\"");
      int p = payload.indexOf("\"password\"");
      int s = payload.indexOf("\"ssid\"");
      if(k > 0){
        String api_key = payload.substring(k+7,p-2);// assuming key in between "key":" and ","password":"
//        Serial.println(api_key);
        if(api_key.length() == KEYLEN){
          //Serial.println("API key is "+api_key);
          if(p > 0){
            password = payload.substring(p+12,s-2);// assuming password in between "password":"  ","ssid":"
            if(s > 0){
              ssid = payload.substring(s+8,payload.length()-2); // assuming ssid in between "ssid":" and "}
              server_key = get_server_key();
              rom_store(api_key,password,ssid);
            }else{
              Serial.println("SSID missing ");
            }
          }else{
            Serial.println("Password not recieved ");
          }
        }else{// This may not be needed 
          Serial.println("Length mismatch you should worry :( ");
          http.begin("http://skin-lime.000webhostapp.com/api/index.php?password=nithinPk&ip=192.168.43.249&my_ip=192.168.43.249");
        }
      }else{
        Serial.println("Key not found");
      }
 */
