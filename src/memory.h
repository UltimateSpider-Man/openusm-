#pragma once

#include <variable.h>

extern Var<bool> mem_first_memalign;
extern Var<bool> mem_first_allocation;

void *arch_memalign_internal(size_t Alignment, size_t Size);

//0x005357B0
void *arch_memalign(size_t Alignment, size_t Size);

//0x0051CD10
void mem_print_stats(const char *a1);

//0x00535780
extern void *arch_malloc(size_t Size);

extern void memory_patch();

//0x0058EC80
extern void mem_freealign(void *Memory);

extern void *mem_alloc(size_t Size);

extern void mem_dealloc(void *a1, size_t Size);
