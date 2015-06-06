#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define CHUNK 1

// function for returning a dynamically allocated string from any stream
// usage: char* new_str = strdup(dynamicString(stdin));
// WARNING: THERE IS A BUG WHERE A NEWLINE FSCKS THIS FUNCTION UP SO IT NEEDS
// TO BE FIXED UP A LITTLE BIT BUT FOR NOW EVERY USE OF THIS FUNCTION HAS A
// WORKAROUND TODO:FIX FUNCTION
char* dynamicString(FILE* stream);
