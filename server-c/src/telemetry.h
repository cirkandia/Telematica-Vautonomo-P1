#ifndef TELEMETRY_H
#define TELEMETRY_H

typedef struct {
  double speed;
  int battery;
  double temp;
  int heading_idx; // 0:N,1:E,2:S,3:W
} vehicle_t;

void telemetry_init(vehicle_t* v);
void telemetry_step(vehicle_t* v);
const char* heading_of(int idx);

#endif

