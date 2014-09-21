/*
 * ------------------------------------------------------------------------------
 * By Bob Jenkins, September 1996.
 * lookupa.h, a hash function for table lookup, same function as lookup.c.
 * Use this code in any way you wish.  Public Domain.  It has no warranty.
 * Source is http://burtleburtle.net/bob/c/lookupa.h
 * ------------------------------------------------------------------------------
 */

#pragma once

#include <stdlib.h>
#include <stdint.h>

#define CHECKSTATE 8
#define hashsize(n) ((uint32_t)1 << (n))
#define hashmask(n) (hashsize(n) - 1)

uint32_t lookup(uint8_t *k, uint32_t length, uint32_t level);
void checksum(uint8_t *k, uint32_t length, uint32_t *state);
