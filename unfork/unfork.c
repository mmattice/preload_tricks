#define _GNU_SOURCE
#include <dlfcn.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>

int count = 0;
int forkcount = 2;

// Define an alternative name for overridden functions
int (*orig_fork)(void);

int fork(void) {
  if(orig_fork == NULL) {
    orig_fork = dlsym(RTLD_NEXT, "fork");
    if (orig_fork == NULL) {
      fprintf(stderr, "dlsym failed on fork: %s\n", dlerror());
      exit(1);
      return 0;
    }
  }

  if (count >= forkcount) {
    return orig_fork();
  } else {
    return 0;
  }
}

void __attribute__((constructor)) initialize() {
  char* sfc = getenv("HIJACK_FORK_COUNT");
  if (sfc != NULL) {
    forkcount = atoi(sfc);
  }
}
