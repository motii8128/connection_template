#ifndef UDP_CONNECTION_HPP_
#define UDP_CONNECTION_HPP_

#include <Ethernet.h>
#include <EthernetUdp.h>
#include <ArduinoJson.h>

#define PACKET_BUFFER_SIZE 1024

struct Axis
{
  float x;
  float y;

  Axis():x(0.0),y(0.0){}
};

struct Button
{
  int circle;
  int triangle;
  int cube;
  int cross;
  int r1;
  int l1;
  int r2;
  int l2;

  Button():circle(0),triangle(0),cube(0),cross(0),r1(0),l1(0),r2(0),l2(0){}
};

struct Joy
{
  Axis left_stick;
  Axis right_stick;
  Axis dpad;
  Button btns;

  Joy():
  left_stick(Axis()),
  right_stick(Axis()),
  dpad(Axis()),
  btns(Button())
  {}
};

class EthernetHandler
{
  public:
  void setup()
  {
    pinMode(LED_BUILTIN, OUTPUT);
    digitalWrite(LED_BUILTIN, HIGH);
    digitalWrite(LED_BUILTIN, LOW);
    delay(500);
    // Ethernet.init(17);
    // Serial.println("[EthernetHandler] Initialized Ethernet.");

    // byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0x05 };
    // IPAddress default_ip(192, 168, 11, 1);
    
    // Ethernet.begin(mac, default_ip);

    // Serial.print("[EthernetHandler] Start Ethernet on Address : ");
    // Serial.println(Ethernet.localIP());

    // while(udp_.begin(64205) == 0)
    // {
    //   Serial.print(".");
    //   delay(50);
    // }
    // Serial.println("[EthernetHandler] Start UDP on port : 64205");

    // Serial.println("[EthernetHandler] EthernetHandler OK!!!!!!!");

    digitalWrite(LED_BUILTIN, HIGH);
  }

  void receive()
  {
    // int i = 0;
    // for(int i = 0; i < PACKET_BUFFER_SIZE; i++)
    // {
    //   buf_[i] = 0;
    // }
    // if(Serial.available())
    // {
    //   buf_[i] = Serial.read();
    //   if(buf_[i] == '\n')
    //   {
    //     i = 0;
    //     // Serial.println(buf_);
    //   }
    //   else
    //   {
    //     i++;
    //   }
    // }
  }
  
  Joy GetJoyData()
  {
    auto joy = Joy();

    DeserializationError error = deserializeJson(doc_, Serial);

    if (error) {
      // Serial.print(F("deserializeJson() failed: "));
      // Serial.println(error.f_str());
      Serial.println(buf_);
    }

    joy.left_stick.x = doc_["left_stick"]["x"];
    joy.left_stick.y = doc_["left_stick"]["y"];
    joy.right_stick.x = doc_["right_stick"]["x"];
    joy.right_stick.y = doc_["right_stick"]["y"];
    joy.dpad.x = doc_["dpad"]["x"];
    joy.dpad.y = doc_["dpad"]["y"];
    joy.btns.circle = doc_["btns"]["circle"];
    joy.btns.cross = doc_["btns"]["cross"];
    joy.btns.cube = doc_["btns"]["cube"];
    joy.btns.triangle = doc_["btns"]["triangle"];
    joy.btns.l1 = doc_["btns"]["l1"];
    joy.btns.l2 = doc_["btns"]["l2"];
    joy.btns.r1 = doc_["btns"]["r1"];
    joy.btns.r2 = doc_["btns"]["r2"];


    return joy;
  }

  private:
  EthernetUDP udp_;
  char buf_[PACKET_BUFFER_SIZE];
  JsonDocument doc_;
};


#endif
