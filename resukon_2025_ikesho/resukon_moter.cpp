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
  if(botanf==true){
    moterpow[moterf]=1;
    moterpow[moterb]=0;
  }
  if(botanb==true){
    moterpow[moterf]=0;
    moterpow[moterb]=1;
  }
  
}