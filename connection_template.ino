#include "UdpConenction.hpp"

EthernetHandler eth;

void setup() {
  // 通信のセットアップを行う
  eth.setup();
}

void loop() {
  // 受信を行う
  eth.receive();

  // コントローラーデータを取得する
  Joy controller_data = eth.GetJoyData();

  //　左スティック
  // 右に倒すと正
  float left_x = controller_data.left_stick.x;
  //　上に倒すと正
  float left_y = controller_data.left_stick.y;

  //　右スティック
  float right_x = controller_data.right_stick.x;
  float right_y = controller_data.right_stick.y;

  //　十字ボタン
  //　上が正
  float up_down = controller_data.dpad.y;
  // 右が正
  float left_right = controller_data.dpad.x;

  // 各ボタン
  //　押されていると１で押されてないと０
  int circle = controller_data.btns.circle;
  int cross = controller_data.btns.cross;
  int cube = controller_data.btns.cube;
  int triangle = controller_data.btns.triangle;
  int r1 = controller_data.btns.r1;
  int r2 = controller_data.btns.r2;
  int l1 = controller_data.btns.l1;
  int l2 = controller_data.btns.l2;
}

