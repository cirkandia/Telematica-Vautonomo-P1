#include "protocol.h"
#include <string.h>
#include <stdio.h>

int starts_with(const char* s, const char* pfx){ return strncmp(s,pfx,strlen(pfx))==0; }

static void trim_word(char* s){
  for(char* p=s; *p; ++p) if(*p==','||*p=='\r'||*p=='\n') { *p=0; break; }
}

int parse_auth(const char* line, char* user, size_t um, char* pass, size_t pm){
  // "AUTH username=<u> password=<p>"
  int n = sscanf(line, "AUTH username=%63s password=%63s", user, pass);
  if(n==2){ trim_word(user); trim_word(pass); return 1; }
  return 0;
}

int parse_command(const char* line, char* cmd, size_t cm, char* token, size_t tm){
  // "COMMAND <CMD> token=<tkn>"
  char tbuf[128]={0};
  int n = sscanf(line, "COMMAND %63s token=%127s", cmd, tbuf);
  if(n>=1){
    if(n==2){
      // token puede venir con terminadores
      strncpy(token, tbuf, tm-1); token[tm-1]=0;
      for(char* p=token; *p; ++p) if(*p=='\r'||*p=='\n') { *p=0; break; }
    } else token[0]=0;
    return 1;
  }
  return 0;
}

