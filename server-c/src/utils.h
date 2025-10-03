#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>

#ifdef _WIN32
  #include <winsock2.h>
  #include <ws2tcpip.h>
#else
  #include <netinet/in.h>
  #include <arpa/inet.h>
#endif

void gen_token(char* out, size_t n);
void now_ts(char* out, size_t n);
void log_line(FILE* f, const char* dir, struct sockaddr_in* addr, const char* line);

#endif
