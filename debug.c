#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

FILE* logfp = NULL;

void init_log(void) {
  char cwd[PATH_MAX] = "";
  if (getcwd(cwd, sizeof(cwd)) == NULL) {
    perror("getcwd() error");
    exit(1);
  }
  // cwd == $HOME/.local/share/containers/storage/overlay
  strcat(cwd, "-logs");
  mkdir(cwd, 0755);
  strcat(cwd, "/fuse-overlayfs.log");

  if (logfp == NULL) {
    logfp = fopen(cwd, "a");
  }
  setbuf(logfp, NULL);

  if (logfp == NULL) {
    perror("init log");
    exit(1);
  }
}
