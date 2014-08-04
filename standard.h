/*
 * ------------------------------------------------------------------------------
 * Standard definitions and types, Bob Jenkins
 * ------------------------------------------------------------------------------
 */
#ifndef STANDARD
# define STANDARD
# ifndef STDIO
#  include <stdio.h>
#  define STDIO
# endif
# ifndef STDDEF
#  include <stddef.h>
#  define STDDEF
# endif
#include <stdint.h>

#define UB4BITS sizeof(uint32_t) * 8
typedef                 int word;   /* fastest type available */

#define bis(target, mask)  ((target) |= (mask))
#define bic(target, mask)  ((target) &= ~(mask))
#define bit(target, mask)  ((target) & (mask))
#ifndef align
# define align(a) (((uint32_t)a + (sizeof(void *) - 1)) & (~(sizeof(void *) - 1)))
#endif /* align */
#endif /* STANDARD */
