/*扇風機を作ろう！その１
 * 内容
 * タッチセンサを押している間，ファン（モータ）が動くようにする
 */
const int switchPin = 13; // タクトスイッチのピン
const int motorPin = 3; // モータを動かすピン
int switchState = 0; // タクトスイッチの状態(State) 0:オフ，1:オン

// Arduinoが起動した時，1度だけ実行
void setup() {
 pinMode(switchPin,INPUT_PULLUP); // スイッチピンをinput pullupにする
 pinMode(motorPin,OUTPUT); // モータピンをoutputにする
}

// 起動中ずっと実行
void loop() {
  switchState = digitalRead(switchPin); // switchPinの状態をswitchStateに代入 押している時:LOW 離している時:HIGH
  if(switchState == LOW){ // もしスイッチが押されたら
    digitalWrite(motorPin,HIGH); // モータに電流を流す
  }
  else{ // 押していない時
    digitalWrite(motorPin,LOW); // モータに電流を流さない
  }
}
