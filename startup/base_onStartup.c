/**
 * @file base_onStartup.c
 * @author Ed Jones (ed@kcza.net)
 * @brief Provides functions to call at the start of every Emperor program
 * @version 0.1
 * @date 2019-09-07
 *
 * @copyright Copyright (c) 2019
 *
 */
#include "base_onStartup.h"

void base_initEmperor(void) { base_registerSignals(); }