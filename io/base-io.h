#ifndef BASE_IO_H_
#define BASE_IO_H_

/**
 * @file base-io.h
 * @author Ed Jones (ed@kcza.net)
 * @brief Provides prototypes for basic I/O operations for Emperor
 * @version 0.1
 * @date 2019-09-06
 *
 * @copyright Copyright (c) 2019
 *
 */

#include "../unused/base-unused.h"
#include <stdio.h>
#include <stdlib.h>

/**
 * @brief @brief Write a C string to stdout
 *
 * @param str The string to print
 */
void printString(char* str);

#endif /* BASE_IO_H_ */