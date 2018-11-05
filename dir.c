#include <stdlib.h>
#include <stdio.h>
#include <sys/stat.h>
#include <dirent.h>
#include <sys/types.h>
#include <errno.h>
#include <string.h>

int main(int argc, char * argv[]) {

  char *s;
  int size = 0;
  struct stat buffer;

  s = argv[1];

  if (argc == 1) {
    char *temp;
    printf("Please enter a directory: ");
    fgets(temp, 100, stdin);
    temp[strlen(temp)-1] = 0;
    s = temp;
  }

  DIR* directory = opendir(s);
  if (errno > 0) {
    printf("Error: %s\n",strerror(errno));
    return 0;
  }
  
  DIR* directory1 = opendir(s);
  struct dirent *entry1;
  entry1 = readdir(directory1);
  printf("Directories: \n");
  while (entry1) {
    if (entry1 -> d_type == DT_DIR) {
      printf("\t%s\n", entry1 -> d_name);
      stat(entry1 -> d_name, &buffer);
      size += buffer.st_size;
    }
    entry1 = readdir(directory1);
  }

  DIR* directory2 = opendir(s);
  struct dirent *entry2;
  entry2 = readdir(directory2);
  printf("Regular Files: \n");
  while (entry2) {
    if (entry2 -> d_type == DT_REG) {
      printf("\t%s\n", entry2 -> d_name);
      stat(entry2 -> d_name, &buffer);
      size += buffer.st_size;
    }
    entry2 = readdir(directory2);
  }

  printf("Size: %d bytes\n", size);
  
  return 0;
}
