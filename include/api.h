#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include "macros.h"
#include "errorCode.h"
#include "getline.h"
#include "scanline.h"

// this is going to form the core functionality of the database(basically all
// the CRUD). This should only depend on stuff like custom data types and
// important functions like getline and getNthLine

typedef struct field {
	char *name; // adventures in dynamic allocation, part 1
} field;

// just to make arrays of strings a bit easier(I know this way works)
typedef struct str_array {
	char *store_str; 
} str_array;

// looks up a specific field in an array of field. TODO: make this a hashmap
int lookup_field(field* fields, int num_fields, char* field_to_lookup);

// initializes(or reinitializes) an array of fields according to the contents of a schema file
int init_schema(field* fields, int num_fields, char* file_name);

// oh look, it spells CRUD
// USAGE: 
// fmt - the format of the object
// 's': schema object
// 'r': record object
// (optional) 'f': field object
// followed by:
// the names of the corresponding objects
// if you update: also add the new name
// if you choose to do anything with a schema, add the number of fields as well
// example usage update_object("srf", "schema.mdb", "10", "record.mdb",
// "field", "update"); will update field "field" with "update" in record
// "record.mdb according to the schema "schema.mdb"

int create_object(char* fmt, ...);

int read_object(char* fmt, ...);

int update_object(char* fmt, ...);

int delete_object(char* fmt, ...);



