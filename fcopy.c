#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/sendfile.h>
#include <sys/stat.h>
#include <string.h>

void copy(const char *src_path, const char *dst_path);
void zero_copy(const char *src_path, const char *dst_path);

int main (int argc, char** argv)
{

  if (argc != 4) {
    printf("usage: %s <source> <destination> <mode>\n", argv[0]);
    exit(1);
  }
 
  if(strcmp(argv[3], "1") == 0) {
    copy(argv[1], argv[2]);
  } else {
    zero_copy(argv[1], argv[2]);
  }

  return 0;
}

void zero_copy(const char *src_path, const char *dst_path) 
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

  // Sync to avoid dirty memory
  fdatasync(dst);

  close(dst);
  close(src);
}

void copy(const char *src_path, const char *dst_path) 
{
  FILE *src, *dst;
  int buffer_size = 8 * 1024;
  char buffer[buffer_size];
  size_t length;

  
  src = fopen(src_path, "rb");
  dst = fopen(dst_path, "wb");
  
  while(!feof(src)) {
    length = fread(buffer, 1, buffer_size, src);
    fwrite(buffer, 1, length, dst);
  }

  fclose(src);
  fclose(dst);
}
