/*扇風機を作ろう！その3
 * 内容
 * タッチセンサを押すたびにファン（モータ）のON/OFFが切り替わる
 * モータの回転数を割合変数を使って変える
 */
const int switchPin = 13; // タクトスイッチのピン
const int motorPin = 3; // モータを動かすピン
int switchState = 0; // タクトスイッチの状態(State) 0:オフ，1:オン
int old_switchState = 0; // 一回前のタクトスイッチの状態
bool isRunning = false; // モーターを動かすかどうか false:動かさない, true:動かす
int motorSpeedRate = 10; // モータスピードの割合 0~100

// Arduinoが起動した時，1度だけ実行
void setup() {
 pinMode(switchPin,INPUT_PULLUP); // スイッチピンをinput pullupにする
 pinMode(motorPin,OUTPUT); // モータピンをoutputにする
 Serial.begin(9800);
}

// 起動中ずっと実行
void loop() {
  switchState = digitalRead(switchPin); // switchPinの状態をswitchStateに代入 押している時:LOW 離している時:HIGH
  if(switchState == LOW && old_switchState == HIGH){ // もし「今の状態が押している時かつ前の状態が押していない時(スイッチを押した一瞬)」なら
    isRunning = !isRunning; // 動きを切り替える
    delay(10); // チャタリング用
  }else if(switchState == HIGH && old_switchState == LOW){ // もし「今の状態が押している時」かつ「前の状態が押していない時」(スイッチを離したら)なら
    delay(10); // チャタリング用
  }
  if(isRunning){ // もし動かすなら
    analogWrite(motorPin,map(motorSpeedRate,0,100,0,254)); // モータに電流を流す 0~100の値を0~254に変更する
  }
  else{ // 動かさなければ
    analogWrite(motorPin,0); // モータに電流を流さない
  }
  old_switchState = switchState; // 今回のスイッチの状態を代入
}
