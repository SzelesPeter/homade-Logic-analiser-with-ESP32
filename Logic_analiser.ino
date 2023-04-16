#include "BluetoothSerial.h"

int ledPin = 13;
int ledState = 0;
int run = 0;
int timeoutMS = 10;
int starttime;
String stringRead;
String charRead;

unsigned long previousMillis = 0;  // will store last time LED was updated

// constants won't change:
const long interval = 10;  // interval at which to blink (milliseconds)

BluetoothSerial SerialBT;

void setup() {
  // set the digital pin as output:
  pinMode(ledPin, OUTPUT);
  SerialBT.begin("Peter");
  SerialBT.register_callback(btCallback);
  SerialBT.setTimeout(timeoutMS);
}

void btCallback(esp_spp_cb_event_t event, esp_spp_cb_param_t *param){
  if(event == ESP_SPP_SRV_OPEN_EVT){
  }
  else if(event == ESP_SPP_DATA_IND_EVT)
  {
      //stringRead = param->data_ind.len;
      int i = 0;
      stringRead = "";
      while(i < param->data_ind.len)
       {
        stringRead = stringRead + char(*(param->data_ind.data+i));
        i++;
      }
      stringRead.trim();
      SerialBT.println(stringRead);
      if (stringRead == String("START"))
      {
        stringRead = "";
        digitalWrite(ledPin, 1);
        run = 1; 
        starttime = millis();
        previousMillis = millis();
      }
      else if (stringRead == String("STOP"))
      {
        stringRead = "";
        digitalWrite(ledPin, 0);
        run = 0;
      }
    }
  }


void loop() 
{
  // here is where you'd put code that needs to be running all the time.

  // check to see if it's time to blink the LED; that is, if the difference
  // between the current time and last time you blinked the LED is bigger than
  // the interval at which you want to blink the LED.


  unsigned long currentMillis = millis();
  if ((currentMillis - previousMillis >= interval) && (run == 1))
  {
    // save the last time you blinked the LED
    previousMillis = currentMillis;
    SerialBT.print("bamenet:  ");
    SerialBT.print("00001111");    
    SerialBT.print("idő: ");
    SerialBT.println(millis() - starttime);
  }
}