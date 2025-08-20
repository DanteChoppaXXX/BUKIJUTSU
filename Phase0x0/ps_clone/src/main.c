#include <dirent.h>
#include <fcntl.h>
#include <linux/limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>

// Process info struct.
typedef struct
{
    int pid;
    char comm[256];
    char state;
    int ppid;
    int tty_nr;
    unsigned long utime;
    unsigned long stime;
    unsigned long long starttime;
} proc_stat_t;

// Function Prototypes.
int is_numeric(const char *str);
long jiffies_to_time(unsigned long jiffies);
char tty_to_string(int tty_nr);
int parser(const char *path, proc_stat_t *info);

int main(int argc, char *argv[])
{

    printf("[+] Process Enumerator [Loading...]\n");
    // check for proper arguments.
    if (argc != 2)
    {
        printf("usage: <./program> <option>\noptions:\n\t-l: to list "
               "processes\n[Exiting...]\n");
        return EXIT_FAILURE;
    }
    else if (strcmp(argv[1], "-l") != 0)
    {
        printf("usage: <./program> <option>\noptions:\n\t-l: to list "
               "processes\n[Exiting...]\n");
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
            snprintf(stat_path, sizeof(stat_path), "/proc/%s/stat",
                     entry->d_name);

            // Read required fields from stat.
            proc_stat_t stat;
            if (parser(stat_path, &stat) == 0)
            {
                printf("PID: %-6d\t CMD: %-40s\t STATE: %c\t TTY: %-5d\t "
                       "UTIME: %-7lu\t STIME: %-7lu\t STARTTIME: %-7llu\n",
                       stat.pid, stat.comm, stat.state, stat.tty_nr, stat.utime,
                       stat.stime, stat.starttime);
            }
        }
    }
    closedir(proc);
    return EXIT_SUCCESS;
}

// Numeric value checker function.
int is_numeric(const char *str) { return atoi(str); }

int parser(const char *path, proc_stat_t *info)
{
    FILE *fp = fopen(path, "r");
    if (!fp)
        return -1;

    char buf[4096];
    if (!fgets(buf, sizeof(buf), fp))
    {
        fclose(fp);
        return -1;
    }
    fclose(fp);

    // Find first '(' and last ')'
    char *lparen = strchr(buf, '(');
    char *rparen = strrchr(buf, ')');
    if (!lparen || !rparen || rparen < lparen)
        return -1;

    // Extract PID (before '(')
    *lparen = '\0';
    info->pid = atoi(buf);

    // Extract comm
    *rparen = '\0';
    strncpy(info->comm, lparen + 1, sizeof(info->comm));
    info->comm[sizeof(info->comm) - 1] = '\0';

    // Continue parsing after ')'
    char *rest = rparen + 1;
    // Skip leading space
    while (*rest == ' ')
        rest++;

    // Now tokenize the rest
    // Example: state ppid pgrp session tty_nr ...
    sscanf(rest,
           "%c %d %*d %*d %d %*d %*u %*u %*u %*u %*u %*u %*u %lu %lu %*d %*d "
           "%*d %*d %llu",
           &info->state, &info->ppid, &info->tty_nr, &info->utime, &info->stime,
           &info->starttime);

    return 0;
}
