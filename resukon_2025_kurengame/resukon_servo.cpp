#include "resukon_servo.h"

void Servoangle::change(){
    int max_limit=1;
    int min_limit=0;
    if(upbotan==true&&angle<=limit[max_limit]-angleconfig){
        angle+=angleconfig;
    }
    if(downbotan==true&&angle>=limit[min_limit]+angleconfig){
        angle-=angleconfig;
    }
}
void Servoangle::reset(){
    angle=startangle;
}