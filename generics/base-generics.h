#ifndef BASE_GENERICS_H_
#define BASE_GENERICS_H_

/**
 * @file base-generics.h
 * @author Ed Jones (ed@kcza.net)
 * @brief Defines Emperor values in a generic way and provides handler function prototypes
 * @version 0.1
 * @date 2019-09-06
 *
 * @copyright Copyright (c) 2019
 *
 */

#include <stdbool.h>

/**
 * @brief Holds a single emperor value so it may be reasoned about in a generic way
 */
typedef struct base_any
{
	/**
	 * @brief An integer value
	 */
	int intV;
	/**
	 * @brief A character value
	 */
	char charV;
	/**
	 * @brief A boolean value
	 */
	bool boolV;
	/**
	 * @brief A real value
	 */
	double doubleV;
	/**
	 * @brief An arbitrary referenced value
	 */
	void* voidV;
} base_Any_t;

#endif /* BASE_GENERICS_H_ */