#ifndef PROTOCOL_H
#define PROTOCOL_H
#include <stddef.h>

typedef struct {
    int is_admin;
    int subscribed;
    char token[64];
} session_t;

int parse_auth(const char* line, char* user, size_t um, char* pass, size_t pm);
int parse_command(const char* line, char* cmd, size_t cm, char* token, size_t tm);
int starts_with(const char* s, const char* pfx);

#endif

