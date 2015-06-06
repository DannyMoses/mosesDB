#pragma once 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dynamicString.h"

typedef struct field {
	char *name; // adventures in dynamic allocation, part 1
	// TODO: make it dynamically aloocate the string for the field
} field;

void print_record();

void write_record(field* fields, int num_fields);

void delete_record();

void clear_record();

void create_record();

void print_schema(field* fields, int num_fields);

void clear_schema(FILE* pFile, char fileName[80]);
