/*扇風機を作ろう！その0
 * 内容
 * モーターを回転させる
 */
const int motorPin = 3; // モータを動かすピン

// Arduinoが起動した時，1度だけ実行
void setup() {
 pinMode(motorPin,OUTPUT); // モータピンをoutputにする
}

// 起動中ずっと実行
void loop() {
    digitalWrite(motorPin,HIGH); // モータに電流を流す
}
