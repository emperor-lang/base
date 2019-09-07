#ifndef BASE_SIGNAL_HANDLER_H_
#define BASE_SIGNAL_HANDLER_H_

/**
 * @file base-signal-handler.h
 * @author Ed Jones (ed@kcza.net)
 * @brief Provides prototypes for a default signal handler
 * @version 0.1
 * @date 2019-09-07
 *
 * @copyright Copyright (c) 2019
 *
 */

#include <execinfo.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "../banned/base-banned.h"

/**
 * @brief The maximum depth of call stack which may be reported
 */
extern int g_base_callStackSize;

void base_registerSignals(void);

/**
 * @brief Default handler for signals
 *
 * @param signal The signal code
 */
void signalHandler(int signal);

/**
 * @brief Obtain a string representation of a signal
 *
 * @param signal The code of the signal to convert
 * @return char* A string representation of the signal
 */
char* sigToA(int signal);

#endif /* BASE_SIGNAL_HANDLER_H_ */