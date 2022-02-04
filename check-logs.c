/*
 */

#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <linux/magic.h>
#include <sys/stat.h>
#include <sys/vfs.h>

#define FILENAME "/tmp/logs-GWVruEfT1Rtgy0zG1oXFpDHiniMtKm1h/foo.log"

int main(void) {
  FILE *log;
  int r;

  log = fopen(FILENAME, "ab+");
  if (log == NULL) {
    fprintf(stderr, "failure: log file opening shouldn't fail\n");
  }

  r = chmod(FILENAME, 0640);
  if (r != 0) {
    fprintf(stderr, "failure: log file chmod shouldn't fail\n");
  }

  if (log != NULL) {
    fprintf(log, "This should get logged to the terminal\n");
  } else {
    exit(1);
  }
  
  exit(0);
}

