#ifndef BASE_ONSTARTUP_H_
#define BASE_ONSTARTUP_H_

/**
 * @file base_onStartup.h
 * @author Ed Jones (ed@kcza.net)
 * @brief Provides prototypes for functions called when Emperor starts up
 * @version 0.1
 * @date 2019-09-07
 *
 * @copyright Copyright (c) 2019
 *
 */

#include "../signal-handler/base-signal-handler.h"
#include "base_onExit.h"
#include <stdbool.h>

void base_initEmperor(void);

#endif /* BASE_ONSTARTUP_H_ */