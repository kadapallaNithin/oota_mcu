//Need to change 
// in is_authenticated, ESPSESSIONID
#include "service.h"
#define DOC_SIZE 200
// Define timeout time in milliseconds (example: 2000ms = 2s)
const long timeoutTime = 2000;
String header;// Variable to store the HTTP request //used_by:clent_refresh
String product_key = "nithin";
ESP8266WebServer server(80);
#define NAV_BAR "<nav class='center blue'> OOTA </nav>"
//Check if header is present and correct
bool is_authenticated() {
  if (server.hasHeader("Cookie")) {
    String cookie = server.header("Cookie");
    if (cookie.indexOf("ESPSESSIONID=1") != -1) {
      Serial.println("Authentication Successful");
      return true;
    }
  }
  Serial.println("Authentication Failed");
  return false;
}
void handleMyLogin(int x){
  //not understood, may need to implement
}

//login page, also called for disconnect
void handleLogin() {
  String msg;
  if (server.hasHeader("Cookie")) {
    Serial.print("Found cookie: ");
    String cookie = server.header("Cookie");
    Serial.println(cookie);
  }
  if (server.hasArg("DISCONNECT")) {
    Serial.println("Disconnection");
    server.sendHeader("Location", "/login");
    server.sendHeader("Cache-Control", "no-cache");
    server.sendHeader("Set-Cookie", "ESPSESSIONID=0");
    server.send(301);
    return;
  }
  if (server.hasArg("USERNAME") && server.hasArg("PASSWORD")) {
    if (server.arg("USERNAME") == "admin" &&  server.arg("PASSWORD") == "admin") {
      server.sendHeader("Location", "/");
      server.sendHeader("Cache-Control", "no-cache");
      server.sendHeader("Set-Cookie", "ESPSESSIONID=1");
      server.send(301);
      Serial.println("Log in Successful");
      return;
    }
    msg = "Wrong username/password! try again.";
    Serial.println("Log in Failed");
  }
  String content = "<html><body><form action='/login' method='POST'>To log in, please use : admin/admin<br>";
  content += "User:<input type='text' name='USERNAME' placeholder='user name'><br>";
  content += "Password:<input type='password' name='PASSWORD' placeholder='password'><br>";
  content += "<input type='submit' name='SUBMIT' value='Submit'></form>" + msg + "<br>";
  content += "You also can go <a href='/inline'>here</a></body></html>";
  server.send(200, "text/html", content);
}

void handleNotFound() {
  String message = "File Not Found\n\n";
  message += "URI: ";
  message += server.uri();
  message += "\nMethod: ";
  message += (server.method() == HTTP_GET) ? "GET" : "POST";
  message += "\nArguments: ";
  message += server.args();
  message += "\n";
  for (uint8_t i = 0; i < server.args(); i++) {
    message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
  }
  server.send(404, "text/pain", message);
}

/*
 *used_by:
 *client_print()
 */
void client_wait(unsigned long sec,String curr_page,String next_page){//,float anim_dur
    String message = "";
    //message += "<link href='/css/drop.css' rel='stylesheet' /></head><body onload='countDownDelay(delay);'><nav class='center'>Oota</nav><div class='row'><div class='col s3 offset-s1 card'>Automatically retry  <br/>after <b id='countdown'>0</b></div><div class='col s3 offset-s1 card'><div class='row'><div id='bottle'><div class='drop'></div></div></div></div><div class='col s2 offset-s1 orange card' onclick='retry()'>Retry Right Now</div></div><script>function countDownDelay(delay){var now = new Date().getTime();delay = delay + now;var x = setInterval(function(){var now = new Date().getTime();var distance = delay - now;var days = Math.floor(distance / (1000 * 60 * 60 * 24));var hours = Math.floor((distance % (1000 * 60 * 60 * 24)) / (1000 * 60 * 60));var minutes = Math.floor((distance % (1000 * 60 * 60)) / (1000 * 60));var seconds = Math.floor((distance % (1000 * 60)) / 1000);document.getElementById('countdown').innerHTML = days + 'd ' + hours + 'h '+ minutes + 'm ' + seconds + 's ';if(distance < 0){clearInterval(x);var hr = window.location.href;window.location.assign(hr.slice(0,hr.indexOf("+curr_page+"))+'"+next_page+"');}},1000);} delay="+sec+";</script></body></html>";
    message += String("<style>\n#bottle{\nbackground:#3498DB;\nwidth:100%;\nmax-width:150px;\nheight:200px;\nborder-radius:15% ;\n}\ndiv {\n  margin: 17px auto;\n}\n\n.drop {\n  position: relative;\n  width: 10px;\n  height: 10px;\n  top: 0px;\n  margin: 0 auto;\n background: #fff;\n -moz-border-radius: 10px;\n -webkit-border-radius: 10px;\n  border-radius: 10px;\n  -moz-animation-name: drip;\n  -webkit-animation-name: drip;\n  animation-name: drip;\n  -moz-animation-timing-function: cubic-bezier(1,0,.91,.19);\n  -webkit-animation-timing-function: cubic-bezier(1,0,.91,.19);\n  animation-timing-function: cubic-bezier(1,0,.91,.19);\n  -moz-animation-duration: 0.9s;\n  -webkit-animation-duration: 0.9s;\n  animation-duration: ")+sec/10+"s;\n  -moz-animation-iteration-count: infinite;\n  -webkit-animation-iteration-count: infinite;\n  animation-iteration-count: infinite;\n}\n\n.drop:before {\n  content: "";\n  position: relative;/*absolute;*/\n  width: 0;\n height: 0;\n  border-left: 5px solid transparent;\n border-right: 5px solid transparent;\n  border-bottom: 30px solid rgba(255,255,255,1);\n  top: -40px;\n}\n\n@keyframes drip {\n    to {\n      top: 190px;\n    }\n}</style>";
    message += "</head><body onload='countDownDelay(delay);'><nav class='center'>Oota</nav><div class='row'><div class='col s3 offset-s1 card'>Automatically retry<input type='checkbox' id='automat'><br/> after <b id='countdown'>0</b></div><div class='col s3 offset-s1 card'><div class='row'><div id='bottle'><div class='drop'></div></div></div></div><div class='col s2 offset-s1 orange card' onclick='retry()'>Retry Right Now</div></div><script>\nfunction retry(){\nvar hr = window.location.href;window.location.assign(hr.replace(current_page,next_page));\n}\nfunction countDownDelay(delay){var now = new Date().getTime();delay = delay + now;var x = setInterval(function(){var now = new Date().getTime();var distance = delay - now;var days = Math.floor(distance / (1000 * 60 * 60 * 24));var hours = Math.floor((distance % (1000 * 60 * 60 * 24)) / (1000 * 60 * 60));var minutes = Math.floor((distance % (1000 * 60 * 60)) / (1000 * 60));var seconds = Math.floor((distance % (1000 * 60)) / 1000);document.getElementById('countdown').innerHTML = days + 'd ' + hours + 'h '+ minutes + 'm ' + seconds + 's ';if(distance < 0){clearInterval(x);if (document.getElementById('automat').checked === true){retry();}},1000);}\nnext_page = '/turn';current_page = '/turn';delay = 100000;//param = '';\n</script>\n";//slice(0,hr.indexOf(current_page))+
    //  client.print(String("<link rel='stylesheet' href='http://kurthi.byethost5.com/css/drop.css' /><script src='http://kurthi.byethost5.com/js/countDown.js'></script></head><body onload='countDownDelay('countdown',")+3000000+");'><nav class='center'>Oota</nav><div class='row'><div class='col s3 offset-s1 card'>Automatically retry after <br/><b id='countdown'>0</b></div><div class='col s3 offset-s1 card'><div class='row'><div id='bottle'><div class='drop'></div></div></div></div><div class='col s2 offset-s1 orange card' onclick='retry()'>Retry Right Now</div></div><script>delay = 6000;</script></body></html>";
  server.send(200,"text/html",message);
}
/*
 * uses:
 * SERVICE_TURN,SERVICE_FINISH
 * used by:
 * service()
 */
void client_print(bool json,int service,StaticJsonDocument<DOC_SIZE> response,short step){
  if(json){
    String op;
    serializeJson(response,op);
    server.send(200,"application/json",op);
  }else{
    String message = "<html><head><link rel='stylesheet' href='https://cdnjs.cloudflare.com/ajax/libs/materialize/1.0.0/css/materialize.min.css'>";//<link href='https://raw.githubusercontent.com/kadapallaNithin/nitandhra/master/temp/drop.css' rel='stylesheet' /><script src='https://raw.githubusercontent.com/kadapallaNithin/nitandhra/master/temp/countDown.js'></script>
    if(service == SERVICE_TURN){
      if(step == 3){//response.indexOf("{\"rem\":") >= 0
        client_wait(response["rem"],"/turn?","/turn?");//,10,response.substring(7, response.length()-2 ).toInt()
      }else if(step == 1){//response.indexOf("{\"req\":")>= 0
        message += "</head><body>";
      //client_refresh(client,"/refresh","");
        //int ha = response.indexOf("has_dispensed_for\":")+19;
        if(response["has_dispensed_for"] == "null" || response["has_dispensed_for"] == -2){//response.substring(ha,ha+2).toInt() == -2
          message += "Sorry, Invalid credentials";
        }else{
          //message += response[ha]);
          message += String(NAV_BAR)+"<div class='row' style='padding-top:10px'><div ><form action='/finish/'><input type='submit' value='finish' class='btn s2 offset-s8 red' /></form></div></div>";//doesn't work if not /turn<button class='btn col red offset-s8 s2'  onclick='f()'>Finish</button></div></div><script>function f(){window.location.assign(window.location.href.replace(\"turn\",\"finish\"));}</script>";//<a class='btn col red offset-s8 s2' href='"+SERVER_ADDRESS+"dispense/"+response["txn"].as<String>()+"/' >";
        }
      }else if(step == 2){//response.indexOf("{\"error\":") >= 0
        message += "</head><body>";
        message += "<strong>Error : </strong>Invalid Parameters";//response.substring(1,response.length()-1);
      }
    }else if(service == SERVICE_FINISH){
      message += "</head><body>";
      message +="<script>alert('";
      if(step == 1){
        if(response["finish"] == -1){
          message +="Already finished!";//"You can finish only your task");
        }else{
          message +=String("Dispensed ")+response["finish"].as<int>()/count_per_ml+" ml of water. Thanks for using our service";//.substring(10, response.length()-2 ).toInt()
        }
      }else{
        message += "Error has occured! ";
      }
      message += String("');window.location.assign('")+INDEX_PAGE+"');</script>";//window.close();
    }
    message += "</body></html>";
    server.send(200,"text/html",message);
  }
}
//uses:server,product_key,required_count,counter,
void handleTurn(){
  bool json = false;
  StaticJsonDocument<DOC_SIZE> doc;
  if(server.args()==5 && server.argName(4)=="json"){
    json = true;
  }
  if(required_count - counter <= 0){
    if(server.argName(0) == "key" && server.arg(0)==product_key && server.argName(1)=="req" && server.argName(2) == "txn" && server.argName(3)=="cash"){
      doc["req"] = server.arg(1);
      doc["txn"] = server.arg(2);
      doc["has_dispensed_for"] = dispense_water(server.arg(1).toInt(),server.arg(2).toInt());
      handleMyLogin(1);
//      client_print(json,SERVICE_TURN,doc,1);
      //client_print(,SERVICE_TURN,String("{\"req\":")++",\"user\":"++",\"has_dispensed_for\":"++"}");//,cash
    }else{
      String message = "";
      Serial.println(product_key);
      for(int i=0; i<server.args(); i++){
         Serial.print(server.argName(i));
         Serial.println(server.arg(i));
      }
      doc["error"]= "Invalid Parameters";
      client_print(json,SERVICE_TURN,doc,2);
    }
  }else{
    doc["rem"] = required_count - counter;
    client_print(json,SERVICE_TURN,doc,3);
  }
}

void handleWatch(){
  StaticJsonDocument<DOC_SIZE> doc;
  handleMyLogin(0);
  client_print(false,SERVICE_TURN,doc,1);
}
void handleCpml(){
  String message = "";
  if(server.args()>1 && server.argName(0) == "key" && server.arg(0) == product_key && server.argName(1) == "cpml"){
    message += server.arg(1).toInt();
    store_count_per_ml(server.arg(1).toInt());
    message += count_per_ml;
    count_per_ml = server.arg(1).toInt();
    message += count_per_ml_fetch();
  }
}
//uses:server,WAITING_TIME
//used_by:server_begin()
void handleRefresh(){
  String message = "";
  if (server.method() != HTTP_POST) {
    server.send(405, "text/plain", "Method Not Allowed");
  } else {
  /*    String message = "POST form was:\n";
    for (uint8_t i = 0; i < server.args(); i++) {
      message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
    }*/
    //hr.slice(0,hr.indexOf('"+page+"'))+
    String param = "";//not implemented it is assumed to be post request but following is get change to post accordingly.
    message = "<script>var hr = window.location.href;var x = setInterval(function(){window.location.assign('/refresh"+param+");},"+WAITING_TIME+");</script>";
    server.send(200, "text/html", message);
  }
}
//uses:server,required_count,counter
void handleStatus(){
  server.send(200,"text/plain",String(required_count - counter));
}
void handleFinish(){
  Serial.println("finish");
  if (!is_authenticated()) {
    server.sendHeader("Location", "http://192.168.43.91:8000/");
    server.sendHeader("Cache-Control", "no-cache");
//    server.send(301);
//    return;
  }
  bool json = false;
  if(server.args() > 2){
    json = server.arg(2);
  }
  StaticJsonDocument<DOC_SIZE> doc;
  if(server.args() > 1 && server.argName(0)=="key" && server.arg(0) == product_key && server.argName(1)=="txn"){
    Serial.println("finish_doc");
    doc["finish"] = stop_dispense(server.arg(1).toInt());
    client_print(json,SERVICE_FINISH,doc,1);
  }else{
    client_print(json,SERVICE_FINISH,doc,2);
  }
}

void handleRoot() {
  Serial.println("Enter handleRoot");
  String header;
  if (!is_authenticated()) {
    server.sendHeader("Location", "/login");
    server.sendHeader("Cache-Control", "no-cache");
    server.send(301);
    return;
  }
  String content = "<html><body><H2>hello, you successfully connected to esp8266!</H2><br>";
  if (server.hasHeader("User-Agent")) {
    content += "the user agent used is : " + server.header("User-Agent") + "<br><br>";
  }
  content += "You can access this page until you <a href=\"/login?DISCONNECT=YES\">disconnect</a></body></html>";
  server.send(200, "text/html", content);
}

//wait time for attacks, disconnection after a time period are to be considered!
void server_begin(){
  ensure_connect();
  server.on("/login",handleLogin);
  server.on("/",handleRoot);
  server.on("/turn/",handleTurn);
  server.on("/watch/",handleWatch);
  server.on("/finish/",handleFinish);
  server.on("/cpml/",handleCpml);
  server.on("/status/",handleStatus);
  server.on("/refresh/",handleRefresh);
  server.onNotFound(handleNotFound);
  
  const char * headerkeys[] = {"User-Agent", "Cookie"} ;
  size_t headerkeyssize = sizeof(headerkeys) / sizeof(char*);
  server.collectHeaders(headerkeys, headerkeyssize);
  server.begin();
}
