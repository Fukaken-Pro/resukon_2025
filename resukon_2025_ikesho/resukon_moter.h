#ifndef __MOTOR_H__ // インクルードガード
#define __MOTOR_H__
#include "Arduino.h"
class Moterconfig{
  public:
    int moterpow[2]={0,0};
    int moterf=0;
    int moterb=1;
    int convalue=0;
    int botanf=0;
    int botanb=0;
    void analogpower();
    void reset();
    void digitalpower();
};
#endif // __MOTOR_H__