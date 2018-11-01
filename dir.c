#include <stdlib.h>
#include <stdio.h>
#include <sys/stat.h>
#include <dirent.h>
#include <sys/types.h>

int main() {

  struct stat buffer;
  
  int size = 0;
  DIR* directory1 = opendir(".");
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

  DIR* directory2 = opendir(".");
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

  printf("Total Directory Size: %d bytes\n", size); 
  
  return 0;
}
