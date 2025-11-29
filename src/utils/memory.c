/* Memory Utils
 *
 * File: memory.c
 * Author: Eric Strihagen
 * Date: 2025-11-15
 *
 * Declaration file: utils/memory.h
*/

#include <stddef.h>
#include <stdint.h>

void *memset8(void *ptr, uint8_t value, size_t num) {
    uint8_t *p = (uint8_t*)ptr;
    while (num--) *p++ = value;
    return ptr;
}

void memset32(void *ptr, uint32_t value, size_t count_words) {
    uint32_t *p = (uint32_t*)ptr;
    for (size_t i = 0; i < count_words; i++) {
        p[i] = value;
    }
}
