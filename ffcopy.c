#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/sendfile.h>
#include <sys/stat.h>

void copy_file(const char *src_path, const char *dst_path);

int main (int argc, char** argv)
{

  if (argc != 3) {
    fprintf(stderr, "usage: %s <source> <destination>\n", argv[0]);
    exit(1);
  }

  copy_file(argv[1], argv[2]);
  
  return 0;
}

void copy_file(const char *src_path, const char *dst_path) 
{
  int src;
  int dst;
  struct stat stat_buf;
  off_t offset = 0;
  int rc;


  src = open(src_path, O_RDONLY);
  fstat(src, &stat_buf);

  dst = open(dst_path, O_WRONLY|O_CREAT, stat_buf.st_mode);

  rc = sendfile (dst, src, &offset, stat_buf.st_size);

  if (rc != stat_buf.st_size) {
    fprintf(stderr, "incomplete transfer from sendfile: %d of %d bytes\n",
            rc,
            (int)stat_buf.st_size);
    exit(1);
  }

  close(dst);
  close(src);
}
