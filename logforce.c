#define _GNU_SOURCE
#include <dlfcn.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <fnmatch.h>
#include <unistd.h>

char* logpath;

// Define an alternative name for strcmp()
FILE *(*orig_fopen)(const char *restrict pathname, const char *restrict mode);

FILE *fopen(const char *__restrict __filename, const char *__restrict __modes) {
  if(!orig_fopen) orig_fopen = dlsym(RTLD_NEXT, "fopen");

  if (fnmatch(logpath, __filename, FNM_PATHNAME)) {
    return orig_fopen("/dev/stdout", __modes);
  } else {
    return orig_fopen(__filename, __modes);
  }
}

void __attribute__((constructor)) initialize() {
  logpath = getenv("HIJACK_LOG_PATH");
}
