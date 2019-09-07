/**
 * @file base-signal-handler.c
 * @author Ed Jones (ed@kcza.net)
 * @brief Defines a default signal handler
 * @version 0.1
 * @date 2019-09-07
 *
 * @copyright Copyright (c) 2019
 *
 */
#include "base-signal-handler.h"

int g_base_callStackSize = 25;

void base_registerSignals(void)
{
	printf("Initialising Emperor\n");
	signal(SIGINT, signalHandler);
	signal(SIGSEGV, signalHandler);
}

void signalHandler(int signal)
{
	void* callStack[g_base_callStackSize];
	size_t size = backtrace(callStack, g_base_callStackSize);

	char* rep = sigToA(signal);
	fprintf(stderr, "\nReceived signal %s!\n", rep);
	fprintf(stderr, "Printing stack trace\n");
	backtrace_symbols_fd(callStack, size, STDERR_FILENO);
	fprintf(stderr, "Ejecting core\n");
	exit(EXIT_FAILURE);
}

char* sigToA(int signal)
{
	if (signal == SIGSEGV)
	{
		return "SIGSEGV";
	}
	else if (signal == SIGINT)
	{
		return "SIGINT";
	}
	else
	{
		const int signalStringLength = 6;
		char* str                    = (char*)malloc(signalStringLength * sizeof(char));
		int pos                      = signalStringLength - 2;
		while (signal > 0 && pos >= 0)
		{
			str[pos--] = signal % 10;
			signal /= 10;
		}
		str[signalStringLength - 1] = '\0';
		return str;
	}
}
