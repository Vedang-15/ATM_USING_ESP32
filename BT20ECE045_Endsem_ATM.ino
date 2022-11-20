#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <UniversalTelegramBot.h>
#include <ArduinoJson.h>

const char* ssid = "Rodrick";
const char* password = "greg@123";

#define botToken "5570290438:AAFahqyw4dFTbY7hl6KUq0UKX68RWYz_7ow"
#define chatId "1248539986"

int pinOrder[9] = {4, 2, 15, 13, 12, 14, 27, 33, 32};
int user_array[9];
int pass_array[9];
String username = "";
String logpass = "";
int withdraw_amount[5];
int incorrect_pass_flag = 0;
int authorised_flag = 0;
int amount = 15000;
int deno = 100;


WiFiClientSecure client;
UniversalTelegramBot bot(botToken, client);

int botRequestDelay = 1000;
unsigned long lastTimeBotRan;

int getTouchValue(String val){
  // for username
  if (val == "username")
  {
    for (int x = 0; x < 9; x++){
       user_array[x] = touchRead(pinOrder[x]);
    }
    for(int i=0;i<9;i++){
      if(user_array[i] < 80){
        username+= (i + '0');
      }
    }
    Serial.println(username);
    return 0;
  }
  // for password input
  else if (val == "Password")
  {
    Serial.println("enter");
    for (int x = 0; x < 9; x++)
      pass_array[x] = touchRead(pinOrder[x]);
    for (int y = 0; y < 9; y++)
    {
      if (pass_array[y] < 60)
        logpass += (y+'0');
    }
    Serial.println(logpass);
    return 0;
  }
  // for amount_input
  else{
      
  }
}

void newCommand(int numNewMessages)
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
    Serial.println(text);
    if (text == "/start") {
      String welcome = "Welcome!!\n";
      welcome += "Press /login to login into the system\n";
      welcome += "/credit to credit into your account\n";
      welcome += "/debit to debit from your account \n";
      welcome += "/balance to check your current balance \n";
      bot.sendMessage(chatId, welcome, "");
    }
    if (text == "/login") {
        bot.sendMessage(chatId, "Please enter your username", "");
        delay(5000);
        int ff = getTouchValue("username");
        //int gg = getTouchValue("Password");
        //delay(5000);
        //Serial.println(username);
        //username verification
        String text8 = bot.messages[i].text;
        Serial.println(text8);
        if(text8 == "5569"){
           Serial.println("yes");
           bot.sendMessage(chatId, "matched", "");
        }
        else{
          bot.sendMessage(chatId, "not matched", "");
        }
          //PASSWORD VERIFICATION
    }
    if(text == "/debit"){
       bot.sendMessage(chatId, "Please enter debit amount", "");
       delay(5000);
    }
     
  }
}
void setup() {
  Serial.begin(115200);
  
  pinMode(2, INPUT);
  pinMode(4, INPUT);
  pinMode(15, INPUT);
  pinMode(13, INPUT);
  pinMode(12, INPUT);
  pinMode(14, INPUT);
  pinMode(27, INPUT);
  pinMode(33, INPUT);
  pinMode(32, INPUT);
  
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
  if (millis() > lastTimeBotRan + botRequestDelay)
  {
    int numNewMessages =bot.getUpdates(bot.last_message_received + 1);
    while (numNewMessages)
    {
      Serial.println("got response");
      newCommand(numNewMessages);
      numNewMessages = bot.getUpdates(bot.last_message_received + 1);
    }
    lastTimeBotRan = millis();
  }
  
  // put your main code here, to run repeatedly:

}
