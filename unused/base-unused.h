#ifndef BASE_UNUSED_H_
#define BASE_UNUSED_H_

/**
 * @file base-unused.h
 * @author Ed Jones (ed@kcza.net)
 * @brief Defines macros to mark parameters as unused. Cleanly avoids warnings
 * @version 0.1
 * @date 2019-09-06
 *
 * @copyright Copyright (c) 2019
 *
 */

// Thankyou, ideasman42! https://stackoverflow.com/questions/3599160/how-to-suppress-unused-parameter-warnings-in-c
#ifdef __GNUC__
/**
 * @brief Defines a variable as unused
 */
#	define UNUSED(x) UNUSED_##x __attribute__((__unused__))
#else
/**
 * @brief Defines a variable as unused
 */
#	define UNUSED(x) UNUSED_##x
#endif

// Thankyou, ideasman42! https://stackoverflow.com/questions/3599160/how-to-suppress-unused-parameter-warnings-in-c
#ifdef __GNUC__
/**
 * @brief Defines a function as unused
 */
#	define UNUSED_FUNCTION(x) __attribute__((__unused__)) UNUSED_##x
#else
/**
 * @brief Defines a function as unused
 */
#	define UNUSED_FUNCTION(x) UNUSED_##x
#endif

#endif /* BASE_UNUSED_H_ */