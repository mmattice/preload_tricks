#define _GNU_SOURCE
#include <dlfcn.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <fnmatch.h>
#include <unistd.h>
#include <sys/stat.h>
#include <errno.h>
#include <asm-generic/errno-base.h>

char* logpath;

// Define an alternative name for overridden functions
FILE *(*orig_fopen)(const char *restrict pathname, const char *restrict mode);
int (*orig_chmod)(const char *pathname, mode_t mode);

FILE *fopen(const char *__restrict __filename, const char *__restrict __modes) {
  if(orig_fopen == NULL) {
    orig_fopen = dlsym(RTLD_NEXT, "fopen");
    if (orig_fopen == NULL) {
      fprintf(stderr, "dlsym failed on fopen: %s\n", dlerror());
      errno = ENFILE;
      return NULL;
    }
  }

  if (logpath != NULL && fnmatch(logpath, __filename, FNM_PATHNAME) == 0) {
    return orig_fopen("/dev/stdout", __modes);
  } else {
    return orig_fopen(__filename, __modes);
  }
}

int chmod(const char *pathname, mode_t mode) {
  if (orig_chmod == NULL) {
    orig_chmod = dlsym(RTLD_NEXT, "chmod");
    if (orig_chmod == NULL) {
      fprintf(stderr, "dlsym failed on chmod: %s\n", dlerror());
      return -1;
    }
  }

  if (logpath != NULL && fnmatch(logpath, pathname, FNM_PATHNAME) == 0) {
    return 0;
  } else {
    return orig_chmod(pathname, mode);
  }
}

void __attribute__((constructor)) initialize() {
  logpath = getenv("HIJACK_LOG_PATH");
}
