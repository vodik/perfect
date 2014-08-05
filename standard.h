/*
 * ------------------------------------------------------------------------------
 * Standard definitions and types, Bob Jenkins
 * ------------------------------------------------------------------------------
 */

#pragma once

#include <stdio.h>
#include <stddef.h>
#include <stdint.h>

#define UB4BITS sizeof(uint32_t) * 8

#define bis(target, mask)  ((target) |= (mask))
#define bic(target, mask)  ((target) &= ~(mask))
#define bit(target, mask)  ((target) & (mask))
#define align(a) (((uint32_t)a + (sizeof(void *) - 1)) & (~(sizeof(void *) - 1)))
