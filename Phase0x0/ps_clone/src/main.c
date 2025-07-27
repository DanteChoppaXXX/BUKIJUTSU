#include <linux/limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/types.h>
#include <fcntl.h>

// Process info struct.
typedef struct ProcInfo
{
  unsigned long pid;
  const char *tty;
  char state;
  unsigned long time;
  const char *cmd;
} ProcInfo;

// Function Prototypes.
int is_numeric(const char *str);
long jiffies_to_time(unsigned long jiffies);
char tty_to_string(int tty_nr);
void parser(char *buffer);

int main(int argc, char *argv[])
{

  printf("[+] Process Enumerator [Loading...]\n");
  // check for proper arguments.
  if (argc < 2)
  {
    printf("usage: <./program> <option>\noptions:\n\t-l: to list processes\n[Exiting...]\n");
    return EXIT_FAILURE;
  }

  // Open /proc Directory.
  DIR *proc = opendir("/proc");
  if (proc == NULL)
  {
    perror("Failed to open \"/proc\"");
    return EXIT_FAILURE;  
  }
  
  // Declare a directory entry (dirent) struct.
  struct dirent *entry;


  // Loop over /proc Entries.
  while ((entry = readdir(proc)) != NULL)
  {
    if (is_numeric(entry->d_name))
    {
      // Construct the path to /proc/<pid>/stat.
      char stat_path[PATH_MAX];
      snprintf(stat_path, sizeof(stat_path), "/proc/%s/stat", entry->d_name);

      // Open /proc/<pid>/stat.
      FILE *stat_file = fopen(stat_path, "r");
      if (!stat_file)
      {
        continue;
      }

      // Read required fields from stat.
      char buffer[PATH_MAX];
      fread(buffer, PATH_MAX, 1, stat_file);

      fclose(stat_file);

      printf("%s\n", buffer);

      // printf("%s\n", entry->d_name);
    }
    
  }

  closedir(proc);
  return EXIT_SUCCESS;
}

// Numeric value checker function.
int is_numeric(const char *str)
{
  return atoi(str);
}

