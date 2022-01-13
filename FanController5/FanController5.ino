/*扇風機を作ろう！その5
 * 内容
 * タッチセンサを押すたびにファン（モータ）のON/OFFが切り替わる
 * もう一つのタッチセンサでモータの強中弱を切り替える
 */
const int powerSwitchPin = 13; // 扇風機の電源スイッチのピン
const int changeSpeedSwitchPin = 12; // 扇風機の強さを変更する用のピン
const int motorPin = 9; // モータを動かすピン
int powerSwitchState = 0; // 扇風機の電源スイッチの状態(State) 0:オフ，1:オン
int old_powerSwitchState = 0; // 一回前の扇風機の電源スイッチの状態
int changeSpeedSwitchState = 0; // 扇風機の強さを変更する用のスイッチの状態(State) 0:オフ，1:オン
int old_changeSpeedSwitchState = 0; // 一回前の扇風機の強さを変更する用のスイッチの状態
bool isRunning = false; // モーターを動かすかどうか false:動かさない, true:動かす
int motorSpeed = 0;
int fanMode = 0; // 0:弱, 1:中, 2:強

// Arduinoが起動した時，1度だけ実行
void setup() {
 pinMode(powerSwitchPin,INPUT_PULLUP); // 扇風機の電源スイッチピンをinput pullupにする
 pinMode(changeSpeedSwitchPin, INPUT_PULLUP); // 扇風機の強さを変更する用のスイッチピンをinput pullupにする
 pinMode(motorPin,OUTPUT); // モータピンをoutputにする
 Serial.begin(9800);
}

// 起動中ずっと実行
void loop() {

  // 電源用のスイッチの設定
  powerSwitchState = digitalRead(powerSwitchPin); // powerSwitchPinの状態をpowerSwitchStateに代入 押している時:LOW 離している時:HIGH
  if(powerSwitchState == LOW && old_powerSwitchState == HIGH){ // もし「今の状態が押している時かつ前の状態が押していない時(スイッチを押した一瞬)」なら
    isRunning = !isRunning; // 動きを切り替える
  }

  // モータの強弱ボタンの設定
  changeSpeedSwitchState = digitalRead(changeSpeedSwitchPin);
  if( changeSpeedSwitchState == LOW && old_changeSpeedSwitchState == HIGH){ // もし「今の状態が押している時かつ前の状態が押していない時(スイッチを押した一瞬)」なら
    fanMode++;
    if(fanMode>2){
      fanMode = 0;
    }
  }

  //モータのモードによるモータスピードの設定
  if(fanMode == 0){ // 弱
    motorSpeed = 60;
  }else if(fanMode == 1){ // 中
    motorSpeed = 120;
  }else if(fanMode == 2){ // 強
    motorSpeed = 254;
  }

  
  if(isRunning){ // もし動かすなら
    analogWrite(motorPin,motorSpeed); // モータに電流を流す
  }
  else{ // 動かさなければ
    analogWrite(motorPin,0); // モータに電流を流さない
  }
  
  // 今回のスイッチの状態をそれぞれに代入
  old_powerSwitchState = powerSwitchState; 
  old_changeSpeedSwitchState = changeSpeedSwitchState;
  
  delay(100); //動作安定用
}
