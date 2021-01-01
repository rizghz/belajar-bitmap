#include "util.h"

void dump_memory(void* obj, size_t n) {

    uint8_t* v = (uint8_t*)obj;

    while (n--) {
        printf("%02x ", *v++ & 0xFF);
    }
    printf("\n");

}