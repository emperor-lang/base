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

#endif /* BASE_SIGNAL_HANDLER_H_ */