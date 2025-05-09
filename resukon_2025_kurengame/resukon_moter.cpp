#include "resukon_moter.h"
void Moterconfig::analogpower(){
  if(convalue<0){
    moterpow[moterb]=abs(convalue);
    moterpow[moterf]=LOW;
  }
  else{
    moterpow[moterf]=abs(convalue);
    moterpow[moterb]=LOW;
  }
}
void Moterconfig::reset(){
  moterpow[moterf]=0;
  moterpow[moterb]=0;
}
void Moterconfig::digitalpower(){
  if(botanf==1){
    moterpow[moterf]=1;
    moterpow[moterb]=0;
  }
  if(botanb==1){
    moterpow[moterf]=0;
    moterpow[moterb]=1;
  }
  
}