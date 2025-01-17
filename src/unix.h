/*
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

#ifndef UNIX_H
#define UNIX_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct date {
  unsigned int day;
  unsigned int month;
  unsigned int year;
};


/**
 * @brief Get the number of cores
 *
 * @return unsigned int
 */
unsigned int get_core_count();

/**
 * @brief Get the thread count
 *
 * @return unsigned int
 */
unsigned int get_thread_count();

/**
 * @brief Get the total memory
 *
 * @return unsigned int
 */
int get_total_memory();

/**
 * @brief Get the avalible memory
 *
 * @return int
 */
int get_avalible_memory();

long get_uptime();

/**
 * @brief Get the cpu model object
 *
 * @param storage_variable
 * @return int
 */
int get_cpu_model(char *storage_variable);

/**
 * @brief Get the operating system name
 *
 * @return char*
 */
int get_operating_system_name(char *storage_variable);

/**
 * @brief Get the system hostname
 *
 * @param storage_variable
 * @return int
 */
int get_hostname(char *storage_variable);

/**
 * @brief return the output of the uname --kernel-name --kernel-release command
 *
 * @param storage_variable
 * @return int
 */
int uname(char *storage_variable);
int get_rootfs_age(struct date *storage_variable);


#endif // UNIX_H