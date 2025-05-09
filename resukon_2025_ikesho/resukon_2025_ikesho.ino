#include "resukon_moter.h"
#include "resukon_servo.h"


Servoangle servo_1;
Moterconfig lmoter;
Moterconfig rmoter;
Moterconfig widthmoter;
Moterconfig varticalmoter;
Moterconfig nankamoter;

#define SV_PIN_1  2


int x = 0; // aの変数
int y = 0; // bの変数
int z = 0; // cの変数

int stick[3][2]={{0}};
int botan[16]={0};
#define RMF 0
#define RMB 1
#define LMF 2
#define LMB 3
#define X 0
#define Y 1
#define A 2
#define B 3
#define LB 4
#define RB 5
#define LS 8
#define RS 9
#define LT 6
#define RT 7
#define L 0
#define R 1
#define H 2
#define BOTAN 3
#define VARTICAL 1
#define WIDTH 0
#define HAT_NUMBER 2
#define RIGHTMOTER_F 3//右モーターの正転
#define RIGHTMOTER_B 2//右モーターの逆転
#define LEFTMOTER_F 5//左モーターの正転
#define LEFTMOTER_B 6//左モーターの逆転
#define WIDTHMOTER_F 7//右モーターの正転
#define WIDTHMOTER_B 8//右モーターの逆転
#define VARTICALMOTER_F 11//左モーターの正転
#define VARTICALMOTER_B 12//左モーターの逆転
#define FRONT 0
#define BACK 1

void setup() {
  Serial.flush();
  servo_1.attach(SV_PIN_1, 500, 2400);
  servo_1.write(servo_1.startangle);
  pinMode(WIDTHMOTER_F,OUTPUT);
  pinMode(WIDTHMOTER_B,OUTPUT);
  pinMode(VARTICALMOTER_F,OUTPUT);
  pinMode(VARTICALMOTER_B,OUTPUT);
  Serial.begin(115200);
}
int moter[4]={0};
void Serialget(){
  // 受信データがあるか確認
  if (Serial.available() > 0) {
    String input = Serial.readStringUntil('\n'); // 改行までの文字列を読み込む
    // 受信した文字列をカンマで分割
    int commaIndex1 = input.indexOf(',');
    int commaIndex2 = input.indexOf(',', commaIndex1 + 1);

    // 文字列からa, b, cを抽出
    if (commaIndex1 > 0 && commaIndex2 > commaIndex1) {
      String a_str = input.substring(0, commaIndex1);
      String b_str = input.substring(commaIndex1 + 1, commaIndex2);
      String c_str = input.substring(commaIndex2 + 1);

      // 文字列を整数に変換
      x = a_str.toInt();
      y = b_str.toInt();
      z = c_str.toInt();

    }
    if(x==BOTAN){
    botan[y]=z;
    Serial.println(z);
  }
  else{
    stick[x][y]=z;
    Serial.println(z);
  }
  }
}


void loop() {
  Serialget();
  servo_1.upbotan=botan[A];
  servo_1.downbotan=botan[B];
  servo_1.change();
  lmoter.convalue=stick[L][VARTICAL];
  rmoter.convalue=stick[R][VARTICAL];
  lmoter.analogpower();
  rmoter.analogpower();
  widthmoter.botanf=botan[X];
  widthmoter.botanb=botan[Y];
  varticalmoter.botanf=botan[Y];
  varticalmoter.botanf=botan[X];
  widthmoter.digitalpower();
  varticalmoter.digitalpower();


  
  widthmoter.analogpower();
  varticalmoter.analogpower();

  analogWrite(LEFTMOTER_F,lmoter.moterpow[FRONT]);
  delay(10);
  analogWrite(LEFTMOTER_B,lmoter.moterpow[BACK]);
  delay(10);
  analogWrite(RIGHTMOTER_F,rmoter.moterpow[FRONT]);
  delay(10);
  analogWrite(RIGHTMOTER_B,rmoter.moterpow[BACK]);
  delay(10);
  digitalWrite(VARTICALMOTER_F,varticalmoter.moterpow[FRONT]);
  delay(10);
  digitalWrite(VARTICALMOTER_B,varticalmoter.moterpow[BACK]);
  delay(10);
  digitalWrite(WIDTHMOTER_F,widthmoter.moterpow[FRONT]);
  delay(10);
  analogWrite(WIDTHMOTER_B,widthmoter.moterpow[BACK]);
  delay(10);
  servo_1.write(servo_1.angle);
  delay(10);
}
