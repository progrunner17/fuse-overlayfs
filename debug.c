#define _GNU_SOURCE
#include <errno.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <pwd.h>
#include "utils.h"


FILE* logfp = NULL;

void init_log(void) {
  int ret;
  cleanup_free char *log_path = NULL;
  const char* env_path = getenv("FUSE_OVERLAY_LOG_PATH");
  if (env_path == NULL)
    {
      const char *homedir = getenv("HOME");
      if (homedir == NULL) {
        perror("init log: homedir");
        exit(1);
      }
      ret = asprintf(&log_path, "%s/fuse-overlayfs.log", homedir);
      if (ret < 0) {
        perror("init log: opening file");
        exit(1);
      }
    }
  else
    {
      log_path = strdup(env_path);
    }

  ret = access(log_path, W_OK);
  if (ret < 0 && errno != ENOENT)
    {
      perror("init log: access to log path");
      exit(1);
    }

  if (logfp == NULL)
    {
      logfp = fopen(log_path, "a");
      if (logfp == NULL)
        {
          perror("init log: opening file");
          exit(1);
        }
      setbuf(logfp, NULL);
    }
  else
    {
      fprintf(stderr, "log  file is already set\n");
          exit(1);
    }
}
