/* sm.c -- Split memory to use a second block.
 * Author: Luis Colorado <luiscoloradourcola@gmail.com>
 * Date: Fri Mar 13 18:21:46 EET 2020
 * Copyright: (C) Luis Colorado.  All rights reserved.
 * License: BSD.
 */

#include <assert.h>
#include <stdint.h>
#include <stdio.h>

typedef struct {
    void *addr;
    uint64_t size;
} memory;

unsigned char buffer[4096];

void *split_memory(memory *data, unsigned int size_desired)
{
    /* we need to test that the memory requested is <= of the total amount
     * of the original block (which counts a 8byte integer) plus another
     * 8byte integer. */
    assert(size_desired < data->size - sizeof(uint64_t));

    /* this is how much data we consume (not counting the 8byte
	 * int) from the original data */
    int data_consumed = data->size - size_desired;

    /* we divide the left amount of free memory by sizeof(uint64_t) and
     * subtract one, to locate the position in the array of 8byte
     * aligned integers where we are going to put our 8b integer */
    int pos_2_8b = data_consumed / sizeof(uint64_t);

    /* this is the size of the data unused at the end of the new
     * block due to the alignment of the 8bit integer. */
    int unused = data_consumed % sizeof(uint64_t);

    /* unused bytes we don't return, so we print them here.
     * they are lost due to alignment stuff */
    printf("unused: %d\n", unused);

    /* we don't need to cast as data->addr is a void *. */
    uint64_t *p = data->addr;

    /* here we subtract one to the index to count for the first
     * 8b integer which isn't part of the count. */
    p[0] = (pos_2_8b - 1) * sizeof(uint64_t);
    p[pos_2_8b] = size_desired + unused;

    data->size = p[0];

    return p + pos_2_8b + 1;
}

void pbytes(unsigned char *pos, int n)
{
    int i;

    printf("%08lx:", pos - buffer);
    while(n--)
        printf(" %02x", *pos++);
    puts("");
}

int main()
{
    memory mem;
    int ask = 128;

	printf("allocation: "); fflush(stdout);
    scanf("%d", &ask);

	/* init the block */
    mem.addr = buffer;
    mem.size = sizeof buffer - sizeof(uint64_t);

    /* initialising the memory block */
    uint64_t *p = (uint64_t *) buffer;
    p[0] = sizeof buffer - sizeof p[0];

#define P() do {                                            \
        printf("mem.addr = %p\n", mem.addr);                \
        printf("mem.size = %lu\n", mem.size);               \
        pbytes(mem.addr, 16);                               \
    } while(0)

    printf("BEFORE:\n");
    P();

    printf("Asking for %d bytes\n", ask);
    p = split_memory(&mem, ask);
    p[0] = 0xff;

    printf("AFTER:\n");
    P();
    pbytes(mem.addr + mem.size + sizeof(uint64_t), 16);

    printf("Value returned: %p\n", p);
}
