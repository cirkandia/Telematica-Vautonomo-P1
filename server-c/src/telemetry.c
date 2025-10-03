#include "telemetry.h"

void telemetry_init(vehicle_t* v){
  v->speed=0.8; v->battery=100; v->temp=34.5; v->heading_idx=0;
}
void telemetry_step(vehicle_t* v){
  if (v->battery>0) v->battery -= 1;
  v->temp += 0.05; if (v->temp>38) v->temp=34.5;
  v->speed += 0.05; if (v->speed>2.0) v->speed=0.6;
  v->heading_idx = (v->heading_idx+1)%4;
}
const char* heading_of(int i){
  static const char* H[4]={"N","E","S","W"}; return H[i%4];
}

