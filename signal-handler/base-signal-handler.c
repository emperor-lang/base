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
	registerSignal(SIGSEGV, abortingSignalHandler);
	registerSignal(SIGINT, graciousSignalHandler);
}

void registerSignal(int sig, void (*handler)(int sig))
{
	if (signal(sig, handler))
	{
		fprintf(stderr, "Failed to register handler for signal %s\n", sigToA(sig));
		exit(EXIT_FAILURE);
	}
}

void abortingSignalHandler(int sig)
{
	fprintf(stderr, "Received signal %s\n", sigToA(sig));
	printStackTrace();
	abort();
}

void graciousSignalHandler(int UNUSED(signal)) { exit(EXIT_FAILURE); }

void printStackTrace()
{
	fprintf(stderr, "Stack trace:\n");
	void* callStack[g_base_callStackSize];
	size_t size = backtrace(callStack, g_base_callStackSize);
	backtrace_symbols_fd(callStack, size, STDERR_FILENO);
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
		// Assumes that the signal value <= 100 (Given by the <=64 indicated by `kill -l`)
		const int signalStringLength = signal > 10 ? 3 : 2;
		char* str                    = (char*)malloc(signalStringLength * sizeof(char));
		if (str == NULL)
		{
			fprintf(stderr, "Failed to allocate space while handling signal %d\n", signal);
			exit(EXIT_FAILURE);
		}

		int pos = signalStringLength - 2;
		while (signal > 0 && pos >= 0)
		{
			str[pos--] = signal % 10 + '0';
			signal /= 10;
		}
		str[signalStringLength - 1] = '\0';
		return str;
	}
}
