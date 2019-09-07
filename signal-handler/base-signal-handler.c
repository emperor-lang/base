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

/**
 * @brief Register a signal handler for a particular signal, failing appropriately
 *
 * @param sig The signal for the new handler
 * @param handler The function to handle the signal
 */
static void registerSignal(int sig, void (*handler)(int));

/**
 * @brief Default handler for signals which require an immediate, ungracious exit
 *
 * @param signal The signal code
 */
static void abortingSignalHandler(int signal);

/**
 * @brief Default handler for signals which graciously cause an exit
 *
 * @param signal The signal code
 */
static void graciousSignalHandler(int signal);

/**
 * @brief Print a stack-trace at the current point of execution
 */
static void printStackTrace();

/**
 * @brief Obtain a string representation of a signal
 *
 * @param signal The code of the signal to convert
 * @return char* A string representation of the signal
 */
static char* sigToA(int signal);

int g_base_callStackSize = 25;

void base_registerSignals(void)
{
	registerSignal(SIGSEGV, abortingSignalHandler);
	registerSignal(SIGINT, graciousSignalHandler);
}

static void registerSignal(int sig, void (*handler)(int))
{
	if (signal(sig, handler))
	{
		fprintf(stderr, "Failed to register handler for signal %s\n", sigToA(sig));
		exit(EXIT_FAILURE);
	}
}

static void abortingSignalHandler(int sig)
{
	fprintf(stderr, "Received signal %s\n", sigToA(sig));
	printStackTrace();
	abort();
}

static void graciousSignalHandler(int UNUSED(signal)) { exit(EXIT_FAILURE); }

static void printStackTrace()
{
	fprintf(stderr, "Stack trace:\n");
	void* callStack[g_base_callStackSize];
	size_t size = backtrace(callStack, g_base_callStackSize);
	backtrace_symbols_fd(callStack, size, STDERR_FILENO);
}

static char* sigToA(int signal)
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
