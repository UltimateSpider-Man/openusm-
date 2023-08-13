#pragma once

#include <float.hpp>

//0x0058FAE0
extern char *chuck_strcpy(char *dest, const char *src, unsigned int dest_buffer_length);

extern char *chuck_strcat(char *dest, const char *src, unsigned int dest_buffer_length);

extern int chuck_itoa(int a1, char *a2, int result_size);

extern unsigned int chuck_ftoa(Float a1, int precision, char *result, int result_size);
