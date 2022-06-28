#pragma once

#include "arch.h"

struct mg_str {
  const char *ptr;  // Pointer to string data
  size_t len;       // String len
};

#define MG_NULL_STR \
  { NULL, 0 }

#define MG_C_STR(a) \
  { (a), sizeof(a) - 1 }

// Using macro to avoid shadowing C++ struct constructor, see #1298
#define mg_str(s) mg_str_s(s)

struct mg_str mg_str(const char *s);
struct mg_str mg_str_n(const char *s, size_t n);
int mg_lower(const char *s);
int mg_ncasecmp(const char *s1, const char *s2, size_t len);
int mg_casecmp(const char *s1, const char *s2);
int mg_vcmp(const struct mg_str *s1, const char *s2);
int mg_vcasecmp(const struct mg_str *str1, const char *str2);
int mg_strcmp(const struct mg_str str1, const struct mg_str str2);
struct mg_str mg_strstrip(struct mg_str s);
struct mg_str mg_strdup(const struct mg_str s);
const char *mg_strstr(const struct mg_str haystack, const struct mg_str needle);
bool mg_match(struct mg_str str, struct mg_str pattern, struct mg_str *caps);
bool mg_globmatch(const char *pattern, size_t plen, const char *s, size_t n);
bool mg_commalist(struct mg_str *s, struct mg_str *k, struct mg_str *v);
bool mg_split(struct mg_str *s, struct mg_str *k, struct mg_str *v, char delim);
char *mg_hex(const void *buf, size_t len, char *dst);
void mg_unhex(const char *buf, size_t len, unsigned char *to);
unsigned long mg_unhexn(const char *s, size_t len);
int mg_check_ip_acl(struct mg_str acl, uint32_t remote_ip);
int64_t mg_to64(struct mg_str str);
uint64_t mg_tou64(struct mg_str str);
size_t mg_lld(char *buf, int64_t val, bool is_signed, bool is_hex);
double mg_atod(const char *buf, int len, int *numlen);
size_t mg_dtoa(char *buf, size_t len, double d, int width);

typedef void (*mg_pc_t)(char, void *);                  // Custom putchar
typedef size_t (*mg_pm_t)(mg_pc_t, void *, va_list *);  // %M printer
void mg_putchar_realloc(char ch, void *param);          // Print to malloced str

size_t mg_vrprintf(void (*)(char, void *), void *, const char *fmt, va_list *);
size_t mg_rprintf(void (*fn)(char, void *), void *, const char *fmt, ...);
size_t mg_vsnprintf(char *buf, size_t len, const char *fmt, va_list *ap);
size_t mg_snprintf(char *, size_t, const char *fmt, ...);
size_t mg_asprintf(char **, size_t, const char *fmt, ...);
size_t mg_vasprintf(char **buf, size_t size, const char *fmt, va_list ap);
char *mg_mprintf(const char *fmt, ...);
char *mg_vmprintf(const char *fmt, va_list ap);
