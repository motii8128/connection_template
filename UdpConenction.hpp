#ifndef UDP_CONNECTION_HPP_
#define UDP_CONNECTION_HPP_

#include <Ethernet.h>
#include <EthernetUdp.h>
#include <ArduinoJson.h>

#define PACKET_BUFFER_SIZE 256

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
    digitalWrite(LED_BUILTIN, HIGH);
    delay(500);
    digitalWrite(LED_BUILTIN, LOW);

    Ethernet.init(17);
    Serial.println("[EthernetHandler] Initialized Ethernet.");

    byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0x05 };
    IPAddress default_ip(192, 168, 11, 2);
    
    Ethernet.begin(mac, default_ip);

    Serial.print("[EthernetHandler] Start Ethernet on Address : ");
    Serial.println(Ethernet.localIP());

    while(udp_.begin(64205) == 0)
    {
      Serial.print(".");
    }
    Serial.println("[EthernetHandler] Start UDP on port : 64205");

    Serial.println("[EthernetHandler] EthernetHandler OK!!!!!!!");

    digitalWrite(LED_BUILTIN, HIGH);
  }

  void receive()
  {
    for(int i = 0; i < PACKET_BUFFER_SIZE; i++)
    {
      buf_[i] = 0;
    }
    int packet_size = udp_.parsePacket();

    if(packet_size > 0)
    {
      udp_.read(buf_, PACKET_BUFFER_SIZE);
    }
  }
  
  Joy GetJoyData()
  {
    auto joy = Joy();

    DeserializationError error = deserializeJson(doc_, buf_);

    if (error) {
      Serial.print(F("deserializeJson() failed: "));
      Serial.println(error.f_str());
    }

    joy.left_stick.x = doc_["left_stick"]["x"];
    joy.left_stick.y = doc_["left_stick"]["y"];
    joy.right_stick.x = doc_["right_stick"]["x"];
    joy.right_stick.y = doc_["right_stick"]["y"];
    joy.dpad.x = doc_["dpad"]["x"];
    joy.dpad.y = doc_["dpad"]["y"];
    joy.btns.circle = doc_["circle"];
    joy.btns.cross = doc_["cross"];
    joy.btns.cube = doc_["cube"];
    joy.btns.triangle = doc_["triangle"];
    joy.btns.l1 = doc_["l1"];
    joy.btns.l2 = doc_["l2"];
    joy.btns.r1 = doc_["r1"];
    joy.btns.r2 = doc_["r2"];

    return joy;
  }

  private:
  EthernetUDP udp_;
  char buf_[PACKET_BUFFER_SIZE];
  JsonDocument doc_;
};


#endif