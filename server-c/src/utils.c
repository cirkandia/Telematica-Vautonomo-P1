#include "utils.h"
#include <time.h>
#include <string.h>
#include <stdlib.h>

static int seeded = 0;

void gen_token(char* out, size_t n){
  if(!seeded){ srand((unsigned)time(NULL)); seeded = 1; }
  unsigned long a = (unsigned long)time(NULL);
  unsigned long b = (unsigned long)rand();
  snprintf(out,n,"%lu%lu", a, b);
}

void now_ts(char* out, size_t n){
  time_t now=time(NULL);
  strftime(out,n,"%Y-%m-%d %H:%M:%S", localtime(&now));
}

void log_line(FILE* f, const char* dir, struct sockaddr_in* addr, const char* line){
  char ts[32]; now_ts(ts,sizeof(ts));
  fprintf(f,"[%s] %s %s:%d %s\n", ts, dir,
    inet_ntoa(addr->sin_addr), ntohs(addr->sin_port), line);
  fflush(f);
}
