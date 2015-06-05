#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// function for returning a dynamically allocated string from any stream
// usage: char* new_str = strdup(dynamicString(stdin));
char* dynamicString(FILE* stream);
