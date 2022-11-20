#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <UniversalTelegramBot.h>
#include <ArduinoJson.h>
#include <HTTPClient.h>


const char* ssid = "Rodrick";
const char* password = "greg@123";

#define botToken "5570290438:AAFahqyw4dFTbY7hl6KUq0UKX68RWYz_7ow"
#define chatId "1248539986"

int bankmoney = 15000;
int deno = 100;

String actual_password = "";
String finalB = "";
String row_val = "";
String tstring = "";

String GOOGLE_SCRIPT_ID = "AKfycbzyp7QKkSyeXv609BXQCVJh2kjHfIJeoDSS1z86Ornr7LkKKPm4rCx0Bn59AlnvSzmE";
WiFiClientSecure client;
UniversalTelegramBot bot(botToken, client);

int botRequestDelay = 1000;
unsigned long lastTimeBotRan;

void newCommand(int numNewMessages, String p_cmd)
{
  Serial.println("New Command Found");
  for (int i = 0; i < numNewMessages; i++)
  {
    String newChatId = String(bot.messages[i].chat_id);
    if (newChatId != chatId)
    {
      bot.sendMessage(chatId, "Unauthorized user", "");
      continue;
    }
    String text = bot.messages[i].text;
    //Serial.println(text);
    if (text == "/start") {
      String welcome = "Hey there!!\n";
      welcome += "Press /login to login into the system\n";
      welcome += "Press /register to register\n";
      bot.sendMessage(chatId, welcome, "");
    }
    if (text == "/login") {
        String enter = "";
        enter += "Press /username to enter your username\n";
        bot.sendMessage(chatId, enter, "");
    }
    if(text == "/register"){
      bot.sendMessage(chatId, "Enter your username", "");
    }
    if(text == "/setPassword"){
      bot.sendMessage(chatId, "Enter the password that you wish to set", "");
    }
    if(text == "/debit"){
      bot.sendMessage(chatId, "Enter the Number of 100 Rs. notes", "");
    }
    if(text == "/credit"){
      bot.sendMessage(chatId, "Enter the amount to be credited", "");
    }
    if(text == "/username"){
      bot.sendMessage(chatId, "Enter your username", "");
    }
    if(text == "/password"){
      bot.sendMessage(chatId, "Enter your password", "");
    }
    if(text == "/balance"){
      Serial.println("You have asked for balance");
      if (WiFi.status () == WL_CONNECTED) {
          Serial.println(row_val);
          String urlFinal = "https://script.google.com/macros/s/"+GOOGLE_SCRIPT_ID+
          "/exec?"+"user_row=" + String(row_val);
          Serial.print ("Making a request:");
          Serial.println (urlFinal);
          HTTPClient http;
          http.begin (urlFinal.c_str () );
          http.setFollowRedirects (HTTPC_STRICT_FOLLOW_REDIRECTS) ;
          int httpCode = http.GET () ;
          if(httpCode > 0){
            finalB = http.getString();
            Serial.println(finalB);
            bot.sendMessage(chatId, "Your balance is "+finalB, "");
          }
          else{
            Serial.println("Error on http request");
          }
        }
    }
    if(text == "/transactions"){
       if (WiFi.status () == WL_CONNECTED) {
        Serial.println("You have asked for transactions");
          String urlFinal = "https://script.google.com/macros/s/"+GOOGLE_SCRIPT_ID+
          "/exec?"+"roll_no=" + String(row_val);
          Serial.print ("Making a request:");
          Serial.println (urlFinal);
          HTTPClient http;
          http.begin (urlFinal.c_str () );
          http.setFollowRedirects (HTTPC_STRICT_FOLLOW_REDIRECTS) ;
          int httpCode = http.GET () ;
          Serial.println(httpCode);
          if(httpCode > 0){
            Serial.println(httpCode);
            tstring = http.getString();
            String output = "";
            String temp = "";
            int len = tstring.length();
            Serial.println(tstring);
            int a = 0;
            int count = 0;
            int count2 = 0;
            while(count2<5 && a<len){
              char p = tstring[a];
              if(p != ':'){
                temp+= p;
              }
              else{
                count++;
                temp+= "  ";
              }
              if(count == 3){
                output+= temp;
                output+= "\n";
                count2++;
                count = 0;
                temp = "";
              }
              a++;
            }
            if(count2 < 5){
              output = "You have only "+ String(count2) + " transactions\n\n Opening B  Transaction Current B \n" + output;
            }
            else{
              output = "Here are your last 5 transactions\n\n Opening B  Transaction Current B Date Time\n\n" + output;
            }
            Serial.println("Transaction info found");
            bot.sendMessage(chatId, output, "");
          }
          else{
            Serial.println("Error on http request");
          }
         
      }
    }
    if(p_cmd == "/register"){
      String newN = text;
      if (WiFi.status () == WL_CONNECTED) {
          String urlFinal = "https://script.google.com/macros/s/"+GOOGLE_SCRIPT_ID+
          "/exec?"+"nusr=" + String(newN);
          Serial.print ("Making a request:");
          Serial.println (urlFinal);
          HTTPClient http;
          http.begin (urlFinal.c_str () );
          http.setFollowRedirects (HTTPC_STRICT_FOLLOW_REDIRECTS) ;
          int httpCode = http.GET () ;
          Serial.println(httpCode);
          if(httpCode > 0){
            row_val = http.getString();
            http.end () ;
            int row_num = row_val.toInt();
            if(row_num ==0){
              Serial.println("Username does not exist");
            }
            else{
              bot.sendMessage(chatId, "Press /setPassword to enter your password\n", "");
            }
          }
          else{
            Serial.println("Error on http request");
          }
        }
    }
    if(p_cmd == "/setPassword"){
      String npass = text;
      if (WiFi.status () == WL_CONNECTED) {
          String urlFinal = "https://script.google.com/macros/s/"+GOOGLE_SCRIPT_ID+
          "/exec?"+"newpassrow=" + String(row_val) + "&newpass=" + String(npass);
          Serial.print ("Making a request:");
          Serial.println (urlFinal);
          HTTPClient http;
          http.begin (urlFinal.c_str () );
          http.setFollowRedirects (HTTPC_STRICT_FOLLOW_REDIRECTS) ;
          int httpCode = http.GET () ;
          Serial.println(httpCode);
          if(httpCode > 0){
            String sender = "Registered Successfully!!\n";
            sender+= "Press /login to login into the system";
            bot.sendMessage(chatId, sender , "");
          } 
          else{
            Serial.println("Error on http request");
          }
        }
    }
    if(p_cmd == "/username"){
       String user = text;
       Serial.println(user);
       if (WiFi.status () == WL_CONNECTED) {
          String urlFinal = "https://script.google.com/macros/s/"+GOOGLE_SCRIPT_ID+
          "/exec?"+"data=" + String(user);
          Serial.print ("Making a request:");
          Serial.println (urlFinal);
          HTTPClient http;
          http.begin (urlFinal.c_str () );
          http.setFollowRedirects (HTTPC_STRICT_FOLLOW_REDIRECTS) ;
          int httpCode = http.GET () ;
          Serial.println(httpCode);
          if(httpCode > 0){
            row_val = http.getString();
            http.end () ;
            int row_num = row_val.toInt();
            if(row_num ==0){
              Serial.println("Username does not exist");
            }
            else{
              bot.sendMessage(chatId, "Press /password to enter your password\n", "");
            }
          }
          else{
            Serial.println("Error on http request");
          }
        }
    }
    if(p_cmd == "/password"){
      String newpass = text;
      if (WiFi.status () == WL_CONNECTED) {
          String urlFinal = "https://script.google.com/macros/s/"+GOOGLE_SCRIPT_ID+
          "/exec?"+"passrow=" + String(row_val);
          Serial.print ("Making a request:");
          Serial.println (urlFinal);
          HTTPClient http;
          http.begin (urlFinal.c_str () );
          http.setFollowRedirects (HTTPC_STRICT_FOLLOW_REDIRECTS) ;
          int httpCode = http.GET () ;
          if(httpCode > 0){
            actual_password = http.getString();
            if(newpass == actual_password){
              Serial.println("password matched");
              String forward = "You have successfully logged in!!\n";
              forward += "Press /debit to withdraw\n";
              forward += "/credit to credit amount\n";
              forward += "/balance to view balance\n";
              forward += "/transactions to view your last 5 transactions\n";
              bot.sendMessage(chatId, forward, "");
            }
            else{
              Serial.println("password did not match");
              bot.sendMessage(chatId, "password did not match", "");
            }
          }
          else{
            Serial.println("Error on http request");
          }
      }
      
    }
    if(p_cmd == "/debit"){
       String debit_amount = bot.messages[i].text;
       int at = debit_amount.toInt();
       int amt = at*100;
       int avl_bal;
       if (WiFi.status () == WL_CONNECTED) {
          String urlFinal = "https://script.google.com/macros/s/"+GOOGLE_SCRIPT_ID+
          "/exec?"+"user_row=" + String(row_val);
          Serial.print ("Making a request:");
          Serial.println (urlFinal);
          HTTPClient http;
          http.begin (urlFinal.c_str () );
          http.setFollowRedirects (HTTPC_STRICT_FOLLOW_REDIRECTS) ;
          int httpCode = http.GET () ;
          if(httpCode > 0){
            finalB = http.getString();
            avl_bal = finalB.toInt();
          }
          else{
            Serial.println("Error on http request");
          }
          if ( httpCode>0 && WiFi.status () == WL_CONNECTED) {
            int new_balance = avl_bal - amt;
            if(new_balance < 0){
              String retval = "You have insufficient balance to perform this operation.\n Your current balance is : " + String(avl_bal);
              bot.sendMessage(chatId, retval, "");
              
            }
            else{
              String urlFinal = "https://script.google.com/macros/s/"+GOOGLE_SCRIPT_ID+
        "/exec?"+"user_row_val=" + String(row_val) + "&new_bal=" + String(new_balance) + "&action=debit" + "&amount=" + String(amt);
              Serial.print ("Making a request:");
              Serial.println (urlFinal);
              HTTPClient http;
              http.begin (urlFinal.c_str () );
              http.setFollowRedirects (HTTPC_STRICT_FOLLOW_REDIRECTS) ;
              int httpCode = http.GET () ;
              if(httpCode > 0){
                bot.sendMessage(chatId, "Transaction Successful.\n Your current balance is "+String(new_balance) , "");
              }
              else{
                Serial.println("Error on http request");
              }
            }
          }
        }
    }
    if(p_cmd == "/credit"){
       String credit_amount = bot.messages[i].text;
       int camt = credit_amount.toInt();
       int avl_bal2;
       if (WiFi.status () == WL_CONNECTED) {
          String urlFinal = "https://script.google.com/macros/s/"+GOOGLE_SCRIPT_ID+
          "/exec?"+"user_row=" + String(row_val);
          Serial.print ("Making a request:");
          Serial.println (urlFinal);
          HTTPClient http;
          http.begin (urlFinal.c_str () );
          http.setFollowRedirects (HTTPC_STRICT_FOLLOW_REDIRECTS) ;
          int httpCode = http.GET () ;
          if(httpCode > 0){
            finalB = http.getString();
            avl_bal2 = finalB.toInt();
          }
          else{
            Serial.println("Error on http request");
          }
          if (httpCode>0 && WiFi.status () == WL_CONNECTED) {
                int new_balance2 = avl_bal2 + camt;
                String urlFinal = "https://script.google.com/macros/s/"+GOOGLE_SCRIPT_ID+
            "/exec?"+"user_row_val=" + String(row_val) + "&new_bal=" + String(new_balance2) + "&action=credit" + "&amount=" + String(camt);
                Serial.print ("Making a request:");
                Serial.println (urlFinal);
                HTTPClient http;
                http.begin (urlFinal.c_str () );
                http.setFollowRedirects (HTTPC_STRICT_FOLLOW_REDIRECTS) ;
                int httpCode = http.GET () ;
                if(httpCode > 0){
                  bot.sendMessage(chatId, "Transaction Successful.\n Your current balance is "+String(new_balance2), "");
                }
                else{
                  Serial.println("Error on http request");
                }
           }
      }
    }
    
}
}
void setup() {
  Serial.begin(115200);
  // Connect to Wi−Fi
  WiFi.mode(WIFI_STA);
  Serial.flush() ;
  WiFi.begin(ssid, password);
  client.setCACert(TELEGRAM_CERTIFICATE_ROOT);
  WiFi.setSleep(false);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay (1000);
    Serial.print(".");
  }
  Serial.println("connected");
  // Print ESP32 Local IP Address
  Serial.println(WiFi.localIP());
  // put your setup code here, to run once:

}

void loop() {
  String prev_entry = bot.messages[0].text;
  if (millis() > lastTimeBotRan + botRequestDelay)
  {
    int numNewMessages =bot.getUpdates(bot.last_message_received + 1);
    while (numNewMessages)
    {
      Serial.println("got response");
      newCommand(numNewMessages, prev_entry);
      numNewMessages = bot.getUpdates(bot.last_message_received + 1);
    }
    lastTimeBotRan = millis();
  }
  
  // put your main code here, to run repeatedly:

}
