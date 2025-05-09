#include "resukon_moter.h"
#include "resukon_servo.h"


Servoangle servo_1;
Servoangle servo_2;
Servoangle servo_3;
Moterconfig lmoter;
Moterconfig rmoter;
Moterconfig widthmoter;
Moterconfig varticalmoter;
Moterconfig nankamoter;
Moterconfig snankamoter;

#define SV_PIN_1  2
#define SV_PIN_2  3
#define SV_PIN_3  5

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
#define RIGHTMOTER_F 7//右モーターの正転
#define RIGHTMOTER_B 8//右モーターの逆転
#define LEFTMOTER_F 12//左モーターの正転
#define LEFTMOTER_B 11//左モーターの逆転
#define WIDTHMOTER_F 30//右モーターの正転
#define WIDTHMOTER_B 32//右モーターの逆転
#define VARTICALMOTER_F 38//左モーターの正転
#define VARTICALMOTER_B 40//左モーターの逆転
#define NANKAMOTER_F 42//左モーターの正転
#define NANKAMOTER_B 44//左モーターの逆転
#define SNANKAMOTER_F 34//左モーターの正転
#define SNANKAMOTER_B 36//左モーターの逆転
#define FRONT 0
#define BACK 1

void setup() {
  Serial.flush();
  servo_1.attach(SV_PIN_1, 500, 2400);
  servo_2.attach(SV_PIN_2, 500, 2400);
  servo_3.attach(SV_PIN_3, 500, 2400);
  servo_1.write(servo_1.startangle);
  servo_2.write(servo_2.startangle);
  servo_3.write(servo_3.startangle);
  pinMode(WIDTHMOTER_F,OUTPUT);
  pinMode(WIDTHMOTER_B,OUTPUT);
  pinMode(VARTICALMOTER_F,OUTPUT);
  pinMode(VARTICALMOTER_B,OUTPUT);
  pinMode(NANKAMOTER_F,OUTPUT);
  pinMode(NANKAMOTER_B,OUTPUT);
  pinMode(SNANKAMOTER_F,OUTPUT);
  pinMode(SNANKAMOTER_B,OUTPUT);
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
  servo_2.upbotan=botan[X];
  servo_3.upbotan=botan[LS];
  servo_1.downbotan=botan[B];
  servo_2.downbotan=botan[Y];
  servo_3.downbotan=botan[RS];
  servo_1.change();
  servo_2.change();
  servo_3.change();
  lmoter.convalue=stick[L][VARTICAL];
  rmoter.convalue=stick[R][VARTICAL];
  lmoter.analogpower();
  rmoter.analogpower();
  widthmoter.botanf=botan[X];
  widthmoter.botanb=botan[Y];
  varticalmoter.botanf=botan[A];
  varticalmoter.botanb=botan[B];
  nankamoter.botanf=botan[A];
  nankamoter.botanb=botan[B];
  snankamoter.botanf=botan[X];
  snankamoter.botanb=botan[Y];
  widthmoter.digitalpower();
  varticalmoter.digitalpower();
  nankamoter.digitalpower();
  nankamoter.digitalpower();
  snankamoter.digitalpower();
  snankamoter.digitalpower();

  analogWrite(LEFTMOTER_F,lmoter.moterpow[FRONT]);
  analogWrite(LEFTMOTER_B,lmoter.moterpow[BACK]);
  analogWrite(RIGHTMOTER_F,rmoter.moterpow[FRONT]);
  analogWrite(RIGHTMOTER_B,rmoter.moterpow[BACK]);
  digitalWrite(VARTICALMOTER_F,varticalmoter.moterpow[FRONT]?HIGH:LOW);
  digitalWrite(VARTICALMOTER_B,varticalmoter.moterpow[BACK]?HIGH:LOW);
  digitalWrite(WIDTHMOTER_F, widthmoter.moterpow[FRONT]?HIGH:LOW);
  digitalWrite(WIDTHMOTER_B,widthmoter.moterpow[BACK]?HIGH:LOW);
  digitalWrite(NANKAMOTER_F,nankamoter.moterpow[FRONT]?HIGH:LOW);
  digitalWrite(NANKAMOTER_B,nankamoter.moterpow[BACK]?HIGH:LOW);
  digitalWrite(SNANKAMOTER_F,snankamoter.moterpow[FRONT]?HIGH:LOW);
  digitalWrite(SNANKAMOTER_B,snankamoter.moterpow[BACK]?HIGH:LOW);

  servo_1.write(servo_1.angle);
  servo_2.write(servo_2.angle);
  servo_3.write(servo_3.angle);
  delay(10);
}
