
/* qinfo -- Query (Quick) info fetches system info and displays it.
Author: Aidan Neal <decator.c@proton.me>
  qinfo is free software; you can redistribute it and/or
    modify it under the terms of the GNU Lesser General Public
    License as published by the Free Software Foundation; either
    version 3 of the License, or (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public
    License along with this program; if not, write to the Free Software
    Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301
    USA
*/

#include "qinfo.h"
#include "cpu.h"

struct uptime formatted_uptime(long uptime) {
  struct uptime upt;
  /* Calculating the number of days, hours, minutes and seconds. */
  upt.days = (unsigned int)uptime / SECOND_DAY_CONVERSION;
  upt.hours =
      (unsigned int)uptime / SECOND_HOUR_CONVERSION % HOUR_DAY_CONVERSION;
  upt.minutes =
      (unsigned int)uptime / SECOND_MINUTE_CONVERSION % MINUTE_HOUR_CONVERSION;
  upt.seconds = (unsigned int)uptime % SECOND_MINUTE_CONVERSION;
  return upt;
}

int main() {
  configuration config;
  parse_config(&config);

  unsigned int core_count = 0;
  unsigned int thread_count = 0;
  long uptime = 0;
  float available_memory;
  float used_memory = 0;
  float total_memory = 0;
  char hostname[256];
  char cpu_model[100];
  char os_name[256];
  char kernel_version[256];
  char unit[3];
  struct date rootfsage;

  core_count = get_core_count();
  thread_count = get_thread_count();
  available_memory = get_avalible_memory();
  total_memory = get_total_memory();
  uptime = get_uptime();

  used_memory = total_memory - available_memory;
  get_hostname(hostname);
  get_cpu_model(cpu_model);
  get_operating_system_name(os_name);
  if (uname(kernel_version))
  {
    strcpy(kernel_version, "Unknown");
  }
  if (get_rootfs_age(&rootfsage))
    {
      fprintf(stderr, "Error getting rootfs age\n");
      return 1;
    }

  struct uptime upt = formatted_uptime(uptime);
  /*if (strcmp(os_name, "Arch Linux"))
  {
    display_logo("arch");
  } */
  /* Checking to display the memory in gigabytes or kilobytes. */


  if (config.USE_GIGABYTES) {
    used_memory = ((total_memory - available_memory) /
                   (float)KILOBYTE_GIGABYTE_CONVERSION);
    total_memory = get_total_memory() / (float)KILOBYTE_GIGABYTE_CONVERSION;
    strcpy(unit, "GB");
  } else {
    strcpy(unit, "kB");
  }

  /* Checking if the user wants to display the CPU information. If they do, it
  will print the CPU information. */
  if (config.DISPLAY_CPU_INFO) {
    printf("%sCPU:%s\t\t%s (%u cores, %u threads)\n", BWHT, COLOR_END,
           cpu_model, core_count, thread_count);
  }

  if (config.DISPLAY_ETC_CPU_INFO) {
    printf("%sEXTRA CPU INFO:%s Model number 0x%X, Family Value: 0x%X\n", BWHT, COLOR_END,
           cpu_get_modelnum(), cpu_get_family_value());
  }

  /* Checking if the user wants to display the memory information. If they do,
  it will print the memory information. */
  if (config.DISPLAY_MEMORY_INFO) {
    printf("%sRAM:%s\t\t%.2f/%.2f %s \n", BWHT, COLOR_END, used_memory,
           total_memory, unit);
  }

  /* Checking if the user wants to display the operating system information. If
  they do, it will print the operating system information. */
  if (config.DISPLAY_OPERATING_SYSTEM) {
    printf("%sOS:%s\t\t%s (%s)\n", BWHT, COLOR_END, os_name, OPERATING_SYSTEM);
  }

  /* Checking if the user wants to display the hostname. If they do, it will
   * print the hostname. */
  if (config.DISPLAY_HOSTNAME) {
    printf("%sHostname:%s\t%s\n", BWHT, COLOR_END, hostname);
  }

  /* Parsing the rootfsage string and printing the first 3 words. */
  if (config.DISPLAY_ROOTFS_BIRTHDAY) {
    printf("%sROOTFS BIRTH:%s\t", BWHT, COLOR_END);
    if (config.DISPLAY_DATES_YYYY_MM_DD) {
      printf("%d/%d/%d\n", rootfsage.year, rootfsage.month, rootfsage.day);
    } else {
      printf("%d/%d/%d\n", rootfsage.month, rootfsage.day, rootfsage.year);
  }

  /* This is checking if the user wants to display the uptime. If they do, it
   * will print the uptime. */
  if (config.DISPLAY_UPTIME) {
    printf("%sUptime:%s\t\t", BWHT, COLOR_END);
    if (upt.days > 0) {
      printf("%u days ", upt.days);
    }
    if (upt.hours > 0) {
      printf("%u hours ", upt.hours);
    }
    if (upt.minutes > 0) {
      printf("%u minutes ", upt.minutes);
    }
    if (upt.seconds > 0) {
      printf("%u seconds", upt.seconds);
    }
    printf("\n");
  }

  /* This is checking if the operating system is Linux and if the user wants to
  display the kernel version. If both of these are true, it will print the
  kernel version. */
  if (strcmp(OPERATING_SYSTEM, "Linux") && config.DISPLAY_KERNEL_VERSION) {
    printf("%sKernel:%s\t\t%s", BWHT, COLOR_END, kernel_version);
  }

  return 0;
}
}