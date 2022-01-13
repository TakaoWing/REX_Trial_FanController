/*扇風機を作ろう！その5
   内容
   タッチセンサを押すたびにファン（モータ）のON/OFFが切り替わる
   もう一つのタッチセンサでモータの強中弱を切り替える
   配列を用いてプログラムを整理
*/
const int switchPins[] = {13, 12}; // スイッチのピンの配列
const int motorPin = 9; // モータを動かすピン
int switchState = 0; // スイッチの今の状態
int old_switchStates[] = {0, 0}; // 一回前のスイッチの状態
bool isRunning = false; // モータを動かすかどうか false:動かさない, true:動かす
int motorSpeeds[] = {60, 120, 254}; // モータスピードを格納
int fanMode = 0;

// Arduinoが起動した時，1度だけ実行
void setup() {
  for (int i = 0; i < 2; i++) { // 2回繰り返す
    pinMode(switchPins[i], INPUT_PULLUP);
  }
  pinMode(motorPin, OUTPUT); // モータピンをoutputにする
}

// 起動中ずっと実行
void loop() {
  for (int i = 0; i < 2; i++) {
    switchState =  digitalRead(switchPins[i]); // 今の状態を取得
    if (switchState == LOW && old_switchStates[i] == HIGH) {
      if (i == 0) { // 電源用ピンの場合
        isRunning = !isRunning; // 動きを切り替える
      } else if (i == 1) { // ファンの強さ制御ピンの場合
        fanMode++;
        if (fanMode > 2) fanMode = 0; // fanModeが3の場合，0に切り替える
      }
    }
    old_switchStates[i] = switchState; // 前の情報に今の情報を上書き
  }

  if (isRunning) { // もし動かすなら
    analogWrite(motorPin, motorSpeeds[fanMode]); // モータに電流を流す
  }
  else { // 動かさなければ
    analogWrite(motorPin, 0); // モータに電流を流さない
  }

  delay(100); //動作安定用
}
