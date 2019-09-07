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
#include "../unused/base-unused.h"

/**
 * @brief The maximum depth of call stack which may be reported
 */
extern int g_base_callStackSize;

/**
 * @brief Register the default signal handlers.
 */
void base_registerSignals(void);

/**
 * @brief Register a signal handler for a particular signal, failing appropriately
 *
 * @param sig The signal for the new handler
 * @param handler The function to handle the signal
 */
void registerSignal(int sig, void (*handler)(int));

/**
 * @brief Default handler for signals which require an immediate, ungracious exit
 *
 * @param signal The signal code
 */
void abortingSignalHandler(int signal);

/**
 * @brief Default handler for signals which graciously cause an exit
 *
 * @param signal The signal code
 */
void graciousSignalHandler(int signal);

/**
 * @brief Print a stack-trace at the current point of execution
 */
void printStackTrace();

/**
 * @brief Obtain a string representation of a signal
 *
 * @param signal The code of the signal to convert
 * @return char* A string representation of the signal
 */
char* sigToA(int signal);

#endif /* BASE_SIGNAL_HANDLER_H_ */