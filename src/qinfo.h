#include <stdio.h>
#include <string.h>

/**
 * @brief Get the number of cores
 *
 * @return unsigned int
 */
unsigned int get_core_count()
{
  /* Opening the file /proc/cpuinfo and assigning the file pointer to cpu_info. */
  FILE *cpu_info = fopen("/proc/cpuinfo", "r");

  /* Checking if the file was opened successfully. If it was not, it prints an error message and returns 0. */
  if (cpu_info == NULL)
  {
    fprintf(stderr, "Error: Could not open /proc/cpuinfo\n");
    return 0;
  }
  unsigned int core_count;
  while (!fscanf(cpu_info, "cpu cores\t: %u", &core_count))
    fscanf(cpu_info, "%*[^c]");
  fclose(cpu_info);

  return core_count;
}

/**
 * @brief Get the thread count
 *
 * @return unsigned int
 */
unsigned int get_thread_count()
{
  /* Opening the file /proc/cpuinfo and assigning the file pointer to cpu_info. */
  FILE *cpu_info = fopen("/proc/cpuinfo", "r");

  /* Checking if the file was opened successfully. If it was not, it prints an error message and returns 0. */
  if (cpu_info == NULL)
  {
    fprintf(stderr, "Error: Could not open /proc/cpuinfo\n");
    return 0;
  }

  /* Reading the file until it finds the line that starts with "siblings:". */
  unsigned int thread_count;
  while (!fscanf(cpu_info, "siblings\t: %u", &thread_count))
    fscanf(cpu_info, "%*[^s]");
  fclose(cpu_info);

  return thread_count;
}

/**
 * @brief Get the cpu model object
 *
 * @param storage_variable
 * @return int
 */
int get_cpu_model(char *storage_variable)
{
  /* Opening the file /proc/meminfo and assigning the file pointer to mem_info. */
  FILE *cpu_info = fopen("/proc/cpuinfo", "r");

  /* Checking if the file was opened successfully. If it was not, it prints an error message and returns 0. */
  if (cpu_info == NULL)
  {
    fprintf(stderr, "Error: Could not open /proc/cpuinfo\n");
    return 1;
  }

  char buffer[100];
  /* Reading the file until it finds the line that starts with "model name:". */
  while (!fscanf(cpu_info, "model name\t: %99[^\n]", &buffer))
    fscanf(cpu_info, "%*[^m]");
  fclose(cpu_info);

  /* Copying the contents of the buffer into the storage_variable.
     This fixes the returning pointer to a non-existant variable issue
     that would occur when just returning the variable */
  strcpy(storage_variable, buffer);
  return 0;
}

/**
 * @brief Get the total memory
 *
 * @return unsigned int
 */
unsigned int get_total_memory()
{
  /* Opening the file /proc/meminfo and assigning the file pointer to mem_info. */
  FILE *mem_info = fopen("/proc/meminfo", "r");

  /* Checking if the file was opened successfully. If it was not, it prints an error message and returns 0. */
  if (mem_info == NULL)
  {
    fprintf(stderr, "Error: Could not open /proc/meminfo\n");
    return 0;
  }

  unsigned int total_memory;

  /* Reading the file until it finds the line that starts with "MemTotal:". */
  while (!fscanf(mem_info, "MemTotal:\t%u kB", &total_memory))
    fscanf(mem_info, "%*[^m]");
  fclose(mem_info);

  return total_memory;
}

/**
 * @brief Get the operating system name
 *
 * @return char*
 */
int get_operating_system_name(char *storage_variable)
{
  FILE *os_info = fopen("/etc/os-release", "r");

  if (os_info == NULL)
  {
    fprintf(stderr, "Error: Could not open /etc/os-release\n");
    return 1;
  }

  char os_name[128];

  while (!fscanf(os_info, "PRETTY_NAME=\"%[^\"]\"", &os_name))
    fscanf(os_info, "%*[^P]");
  fclose(os_info);

  strcpy(storage_variable, os_name);
  return 0;
}

/**
 * @brief Get the system hostname
 * 
 * @param storage_variable 
 * @return int 
 */
int get_hostname(char *storage_variable)
{
  FILE *hostname_file = fopen("/proc/sys/kernel/hostname", "r");

  if (hostname_file == NULL)
  {
    fprintf(stderr, "Error: Could not open /proc/sys/kernel/hostname\n");
    return 1;
  }

  char hostname[256];
  while (!fscanf(hostname_file, "%255[^\n]", &hostname))
    fscanf(hostname_file, "%*[^\n]");
  fclose(hostname_file);

  strcpy(storage_variable, hostname);
  return 0;
}