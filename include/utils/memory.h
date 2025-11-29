#ifndef __UTILS_MEM_H__
#define __UTILS_MEM_H__

/*
 * Memory Utils
 *
 * Author: Eric Strihagen
 * Date: 2025-11-15
 *
 * file: memory.h
 *
 */

#include <stdint.h>
#include <stddef.h>

void *memset8(void *ptr, uint8_t value, size_t num);
void memset32(void *ptr, uint32_t value, size_t count_words);



#endif /* __UTILS_MEM_H__ */
