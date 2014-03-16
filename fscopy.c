#include <stdio.h>
#include <stdlib.h>

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
