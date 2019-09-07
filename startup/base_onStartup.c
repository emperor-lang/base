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

static bool g_startupComplete = false;

void base_initEmperor(void)
{
	if (g_startupComplete)
	{
		fprintf(stderr, "Emperor setup can only be performed once");
		exit(EXIT_FAILURE);
	}

	base_registerSignals();
	atexit(base_exitEmperor);

	g_startupComplete = true;
}