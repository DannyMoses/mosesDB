#include "../include/api.h"

int lookup_field(field* fields, int num_fields, char* field_to_lookup) 
{
	// LOG("Beginning function call to lookup_field\n")
	// yay null checking
	if (fields == NULL || field_to_lookup == NULL) {
		// DEBUG("Looks like we got a null pointer somewhere boys\n")
		// LOG("Function call to lookup_field failed. Reason: ya dun fscked up with a null pointer somewhere\n")
	} else {
		// carry on
	}
	
	int line_of_field = -1;
	// TODO: change this a hashmap or something better
	for (int i = 1; i <= num_fields; i++) {
		if (strcmp(fields[i].name, field_to_lookup) == 0) {
			line_of_field = i;
			break;
		} else {
		}
	}

	if (line_of_field == -1) {
		// DEBUG("Did you specify the correct field?\n")
		// LOG("Function call to lookup_field failed. Reason: bad field name\n")
		return FUNCTION_ERROR;
	} else {
		// hell of a shot kid, that was one in a million
	}
	
	// LOG("Function call to lookup_field returned success\n")
	return line_of_field; // I don't thnk I need to explain what's happening here
}

int init_schema(field* fields, int num_fields, char* file_name)
{
	// LOG("Beginning function call to init_schema\n")
	FILE* schema_file;
	
	schema_file = fopen(file_name, "r");
	
	if (schema_file == NULL) {
		// LOG("Function call to init_schema failed. Reason: bad file name\n")
		// DEBUG("Did you specify the correct file name?\n")
		return FUNCTION_FAILURE;
	} else {
		// LOG("new schema file opened successfully\n")
	}
	
	if (fields != NULL) {
		for (int i = 0; i <= num_fields; i++) {
			free(fields[i].name);
		}

		free(fields);
	} else {
	}

	fields = (field *) calloc(num_fields, sizeof(field));

	if (fields == NULL) {
		// LOG("The function call to init_schema failed. Reason: bad memory allocation.\n")
		// DEBUG("big bad memory problem\n")
		return FUNCTION_FAILURE;
	} else {
		// LOG("In function call to init_schema: the new fields array has been allocated successfully\n")
	}

	for (int i = 0; i <= num_fields; i++) {
		fields[i].name = (char *) malloc(n);
		m_getline(&fields[i].name, &n, schema_file);
	}
	
	// LOG("Function call to init_schema returned success\n")
	
	return num_fields;
}

