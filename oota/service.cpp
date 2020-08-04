#include "service.h"
// Current time
unsigned long currentTime = millis();
// Previous time
unsigned long previousTime = currentTime; 
// Define timeout time in milliseconds (example: 2000ms = 2s)
const long timeoutTime = 2000;
String header;// Variable to store the HTTP request //used_by:clent_refresh

//wifi/request()
String server_key = "nithin";//3f82bff4c736d594b2f74e99939c015ff5d44a1e32679b0d33479b0984d5f83577d61c958a6703bcbcec3f706d6e3c17bac11e688a118cac6b54c2030e8ed6bc";


/*
 *used_by:
 *client_print()
 */
void client_wait(WiFiClient client,int sec,String curr_page,String next_page){//,float anim_dur
    //client.print("<link href='/css/drop.css' rel='stylesheet' /></head><body onload='countDownDelay(delay);'><nav class='center'>Oota</nav><div class='row'><div class='col s3 offset-s1 card'>Automatically retry  <br/>after <b id='countdown'>0</b></div><div class='col s3 offset-s1 card'><div class='row'><div id='bottle'><div class='drop'></div></div></div></div><div class='col s2 offset-s1 orange card' onclick='retry()'>Retry Right Now</div></div><script>function countDownDelay(delay){var now = new Date().getTime();delay = delay + now;var x = setInterval(function(){var now = new Date().getTime();var distance = delay - now;var days = Math.floor(distance / (1000 * 60 * 60 * 24));var hours = Math.floor((distance % (1000 * 60 * 60 * 24)) / (1000 * 60 * 60));var minutes = Math.floor((distance % (1000 * 60 * 60)) / (1000 * 60));var seconds = Math.floor((distance % (1000 * 60)) / 1000);document.getElementById('countdown').innerHTML = days + 'd ' + hours + 'h '+ minutes + 'm ' + seconds + 's ';if(distance < 0){clearInterval(x);var hr = window.location.href;window.location.assign(hr.slice(0,hr.indexOf("+curr_page+"))+'"+next_page+"');}},1000);} delay="+sec+";</script></body></html>");
    client.print(String("<style>\n#bottle{\nbackground:#3498DB;\nwidth:100%;\nmax-width:150px;\nheight:200px;\nborder-radius:15% ;\n}\ndiv {\n  margin: 17px auto;\n}\n\n.drop {\n  position: relative;\n  width: 10px;\n  height: 10px;\n  top: 0px;\n  margin: 0 auto;\n background: #fff;\n -moz-border-radius: 10px;\n -webkit-border-radius: 10px;\n  border-radius: 10px;\n  -moz-animation-name: drip;\n  -webkit-animation-name: drip;\n  animation-name: drip;\n  -moz-animation-timing-function: cubic-bezier(1,0,.91,.19);\n  -webkit-animation-timing-function: cubic-bezier(1,0,.91,.19);\n  animation-timing-function: cubic-bezier(1,0,.91,.19);\n  -moz-animation-duration: 0.9s;\n  -webkit-animation-duration: 0.9s;\n  animation-duration: ")+sec/10+"s;\n  -moz-animation-iteration-count: infinite;\n  -webkit-animation-iteration-count: infinite;\n  animation-iteration-count: infinite;\n}\n\n.drop:before {\n  content: "";\n  position: relative;/*absolute;*/\n  width: 0;\n height: 0;\n  border-left: 5px solid transparent;\n border-right: 5px solid transparent;\n  border-bottom: 30px solid rgba(255,255,255,1);\n  top: -40px;\n}\n\n@keyframes drip {\n    to {\n      top: 190px;\n    }\n}</style>");
    client.print("</head><body onload='countDownDelay(delay);'><nav class='center'>Oota</nav><div class='row'><div class='col s3 offset-s1 card'>Automatically retry<input type='checkbox' id='automat'><br/> after <b id='countdown'>0</b></div><div class='col s3 offset-s1 card'><div class='row'><div id='bottle'><div class='drop'></div></div></div></div><div class='col s2 offset-s1 orange card' onclick='retry()'>Retry Right Now</div></div><script>\nfunction retry(){\nvar hr = window.location.href;window.location.assign(hr.replace(current_page,next_page));\n}\nfunction countDownDelay(delay){var now = new Date().getTime();delay = delay + now;var x = setInterval(function(){var now = new Date().getTime();var distance = delay - now;var days = Math.floor(distance / (1000 * 60 * 60 * 24));var hours = Math.floor((distance % (1000 * 60 * 60 * 24)) / (1000 * 60 * 60));var minutes = Math.floor((distance % (1000 * 60 * 60)) / (1000 * 60));var seconds = Math.floor((distance % (1000 * 60)) / 1000);document.getElementById('countdown').innerHTML = days + 'd ' + hours + 'h '+ minutes + 'm ' + seconds + 's ';if(distance < 0){clearInterval(x);if (document.getElementById('automat').checked === true){retry();}},1000);}\nnext_page = '/turn';current_page = '/turn';delay = 100000;//param = '';\n</script>\n");//slice(0,hr.indexOf(current_page))+
    //  client.print(String("<link rel='stylesheet' href='http://kurthi.byethost5.com/css/drop.css' /><script src='http://kurthi.byethost5.com/js/countDown.js'></script></head><body onload='countDownDelay('countdown',")+3000000+");'><nav class='center'>Oota</nav><div class='row'><div class='col s3 offset-s1 card'>Automatically retry after <br/><b id='countdown'>0</b></div><div class='col s3 offset-s1 card'><div class='row'><div id='bottle'><div class='drop'></div></div></div></div><div class='col s2 offset-s1 orange card' onclick='retry()'>Retry Right Now</div></div><script>delay = 6000;</script></body></html>");
}
/*uses:
 * WAITING_TIME
 * used by:
 * client_print(),service()
 */
void client_refresh(WiFiClient client,String page,String param){
  client.print("<script>var hr = window.location.href;var x = setInterval(function(){window.location.assign(hr.slice(0,hr.indexOf('"+page+"'))+'/refresh"+param+");},"+WAITING_TIME+");</script>");
  
}
/*
 * uses:
 * SERVICE_TURN,SERVICE_FINISH
 * used by:
 * service()
 */
void client_print(WiFiClient client,bool json,int service,String response){
  if(json){
    client.print(response);
  }else{
    client.print("<html><head><link rel='stylesheet' href='https://cdnjs.cloudflare.com/ajax/libs/materialize/1.0.0/css/materialize.min.css'>");//<link href='https://raw.githubusercontent.com/kadapallaNithin/nitandhra/master/temp/drop.css' rel='stylesheet' /><script src='https://raw.githubusercontent.com/kadapallaNithin/nitandhra/master/temp/countDown.js'></script>
    
    if(service == SERVICE_TURN){
      if(response.indexOf("{\"rem\":") >= 0){
        client_wait(client,response.substring(7, response.length()-2 ).toInt(),"/turn?","/turn?");//,10
      }else if(response.indexOf("{\"req\":")>= 0){
        client.print("</head><body>");
        //client_refresh(client,"/refresh","");
        int ha = response.indexOf("has_dispensed_for\":")+19;
        if(response.substring(ha,ha+2).toInt() == -2){
          client.print("Sorry, Invalid credentials"); 
        }else{
          //client.print(response[ha]);
          client.print("<nav class='center'> OOTA </nav><div class='row' style='padding-top:10px'><div ><button class='btn col red offset-s8 s2'  onclick='f()'>Finish</button></div></div><script>function f(){window.location.assign(window.location.href.replace(\"turn\",\"finish\"));}</script>");
        }
      }else if(response.indexOf("{\"error\":") >= 0){
        client.print("</head><body>");
        client.print(response.substring(1,response.length()-1));
      }else{
        client.print("</head><body>");
        client.print("Error please show this screenshot to admin service/client_print.TURN");
      }
    }else if(service == SERVICE_FINISH){
      client.print("</head><body>");
      client.print("<script>alert('");
      if(response[10] == '-'){
        client.print("Already finished!");//"You can finish only your task");
      }else{
        client.print(String("Dispensed ")+response.substring(10, response.length()-2 ).toInt()/count_per_ml+" ml of water. Thanks for using our service");
      }
      client.print(String("');window.location.assign('")+INDEX_PAGE+"');</script>");//window.close();
    }
    client.print("</body></html>");
  }
}
/*
 * uses:
 * currentTime,previousTime,timeoutTime,header,Serial,required_count,counter,FREQUENT_MES_DELAY,SEVICE_TURN,server_key,count_per_ml
 * refresh_client(),store_count_per_ml(),,dispense_water(req,user),client_print()
 * used by:
 * clie.../loop
 */
void service(WiFiClient client){
    Serial.println("New Client.");          // print a message out in the serial port
    String currentLine = "";                // make a String to hold incoming data from the client
    currentTime = millis();
    previousTime = currentTime;
    while (client.connected() && currentTime - previousTime <= timeoutTime) { // loop while the client's connected
      currentTime = millis();         
      if (client.available()) {             // if there's bytes to read from the client,
        char c = client.read();             // read a byte, then
        Serial.print(c);                    // print it out the serial monitor
        header += c;
        if (c == '\n') {                    // if the byte is a newline character
          // if the current line is blank, you got two newline characters in a row.
          // that's the end of the client HTTP request, so send a response:
          if (currentLine.length() == 0) {
            // HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
            // and a content-type so the client knows what's coming, then a blank line:
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println("Connection: close");
            client.println();
            Serial.println(header);
            Serial.println("GET /turn?key="+server_key);
            int wait_time = required_count - counter;
            if(frequent()){
              wait_time += FREQUENT_MES_DELAY;
            }
            int json_ind = header.indexOf("&json=");//json_ind is used below @ cash_bytes
            bool json = (json_ind != -1)&&(header[json_ind+6] == '1');
            if(header.indexOf("GET /refresh") >= 0){
              client_refresh(client,"/refresh",header.substring(header.indexOf("GET /refresh")+12));
            }else if(header.indexOf("GET /status") >= 0){
              Serial.println(wait_time);
              client.println(wait_time);
              //client.println("Accept you");
            }else if(header.indexOf("GET /turn?key="+server_key) >= 0){
              if(wait_time <= 0){
                int r = header.indexOf("&req=");
                int u = header.indexOf("&user=");
                int c = header.indexOf("&cash_bytes=");
                if(r > 0 && u > 0 && c > 0){
                  long req = header.substring(r+5,u).toInt();
                  long user = header.substring(u+6,c).toInt();
                  String cash;
                  if(json){
                    cash = header.substring(c+12,json_ind);
                  }else{
                    cash = header.substring(c+12);
                    cash = cash.substring(0,req);
                  }
                  /*if(req == 0 || user == 0 || cash == "" || req != cash.length()){
                    //STDOUT.print(String("Cash ")+header.substring(json_ind+6)+"is "+cash);
                    Serial.print("n");
                    Serial.print(json_ind+6);
                    Serial.print(header.substring(header[header.length()-1]));
                    client_print(client,json,SERVICE_TURN,"{\"error\":\"Parameters are not as expected\"}");//i.e req,user,cash_bytes,json(optional)
                  }else{*/
                    //Serial.println("Accepted ");
                    client_print(client,json,SERVICE_TURN,String("{\"req\":")+req+",\"user\":"+user+",\"has_dispensed_for\":"+dispense_water(req,user)+"}");//,cash
/*                  client.print("{\"req\":");
                  client.print(req);
                  client.print(",\"user\":");
                  client.print(user);
                  client.print(",\"has_dispensed_for\":"+String(dispense_water(req,user)));
                  client.print("}");*/
                  //}
                }else{
                  client_print(client,json,SERVICE_TURN,"{\"error\":\"Invalid Parameters\"}");
//                  client.println("-1");
                }
              }else{
                client_print(client,json,SERVICE_TURN,String("{\"rem\":")+wait_time+"}");
//                client.print("{\"rem\":");
//                client.print(wait_time);
                //client.print("}");
              }
              //refresh_client("/turn?","?key="+);
            }else if(header.indexOf("GET /finish?key="+server_key) >= 0){
                int u = header.indexOf("&user=");
                if(u > 0){
                  long user = header.substring(u+6).toInt();
                  client_print(client,json,SERVICE_FINISH,String("{\"finish\":")+stop_dispense(user)+"}");
//                  client.print("{\"finish\":");
//                  client.print(stop_dispense(user));
//                  client.print("}");
                }
            }else if(header.indexOf("GET /cpml?key="+server_key) >= 0){
                int c = header.indexOf("&cpml=");
                if(c > 0){
                  long cpml = header.substring(c+6).toInt();
                  client.print(cpml);
                  store_count_per_ml(cpml);
                  client.println(count_per_ml);
                  count_per_ml = cpml;
                  client.print(count_per_ml_fetch());
                }
            }else{
              client.println("-1");//Brute force hacker :<");
              //while(1)
              //  client.println(".");
            }
            header = "";
            client.stop();
            // Break out of the while loop
            break;
          } else { // if you got a newline, then clear currentLine
            currentLine = "";
          }
        } else if (c != '\r') {  // if you got anything else but a carriage return character,
          currentLine += c;      // add it to the end of the currentLine
        }
      }
    }
    // Clear the header variable
    header = "";
    client.stop();
    //  ssid = "kadapalla";
    //Serial.println(ssid);
    //WiFi.begin(ssid,password);
    STDLOG.println("Client disconnected.");
    STDLOG.println("");
}
