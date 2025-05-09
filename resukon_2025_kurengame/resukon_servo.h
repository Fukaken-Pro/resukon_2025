#ifndef __SARVO_H__ // インクルードガード
#define __SARVO_H__
#include <Servo.h>

class Servoangle: public Servo{
public:
    int startangle=0;
    int angle=startangle;//サーボの角度
    int limit[2]={0,180};//サーボの角度上限
    int upbotan=0;//確認したいボタン
    int downbotan=0;
    int angleconfig=1;
    void change();
    void reset();
};
#endif // __SARVO_H__