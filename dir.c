#include <stdlib.h>
#include <stdio.h>
#include <sys/stat.h>
#include <dirent.h>
#include <sys/types.h>


char * get_size(char * buffer, double size) {
  if (size < 1024){
    sprintf(buffer, "%f B", size);
    return buffer;
  }
  
  size /= 1024.0;
  if (size < 1024) {
    sprintf(buffer, "%f KB", size);
    return buffer;
  }
  size /= 1024.0;
  if (size < 1024) {
    sprintf(buffer, "%f MB", size);
    return buffer;
  }
  size /= 1024.0;
  sprintf(buffer, "%f GB", size);

  return buffer;
}

int main() {
  char * info;
  struct stat buffer;
  
  double size = 0;
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

  printf("Size: %f\n", size);

  //printf("Total Directory Size: %s\n", get_size(info, size)); 
  
  return 0;
}
