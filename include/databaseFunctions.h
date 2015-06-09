#pragma once 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "errorCodes.h"
#include "getline.h"
#include "scanline.h"
#include "macros.h"

typedef struct field {
	char *name; // adventures in dynamic allocation, part 1
	// TODO: make it dynamically aloocate the string for the field
} field;

int scan_record(field* fields, int num_fields);

int print_record(field *fields, int num_fields);

int write_record(field* fields, int num_fields);

int delete_record();

int clear_record();

int create_record();

int print_schema(field* fields, int num_fields);

int clear_schema(FILE* pFile, char *pFileName);
