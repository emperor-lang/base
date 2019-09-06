#ifndef UNUSED_H_
#define UNUSED_H_

// Thankyou, ideasman42! https://stackoverflow.com/questions/3599160/how-to-suppress-unused-parameter-warnings-in-c
#ifdef __GNUC__
#	define UNUSED(x) UNUSED_##x __attribute__((__unused__))
#else
#	define UNUSED(x) UNUSED_##x
#endif

// Thankyou, ideasman42! https://stackoverflow.com/questions/3599160/how-to-suppress-unused-parameter-warnings-in-c
#ifdef __GNUC__
#	define UNUSED_FUNCTION(x) __attribute__((__unused__)) UNUSED_##x
#else
#	define UNUSED_FUNCTION(x) UNUSED_##x
#endif

#endif /* UNUSED_H_ */