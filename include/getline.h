#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <assert.h>
#include <errno.h>

int
getstr (char **lineptr, size_t *n, FILE *stream, char terminator, int offset);

int
m_getline (char **lineptr, size_t *n, FILE *stream);
