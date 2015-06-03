/*
** Simple database written for fun
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct field {
	char name[1000]; // a decent max length for the name of the field right?
	// TODO: make it dynamically aloocate the string for the field
} field;

void read_record(field* fields)
{
}

void write_record(field* fields)
{
}

void clear_record()
{
}

void create_record()
{
	FILE* pFile;
	char recordName[80];
	printf("What is the name of this new record(names must not overlap)? ");
	scanf("%s", recordName);
	pFile = fopen(recordName, "w");
	if (pFile == NULL) {
		perror("The following error has occurred");
		exit(EXIT_FAILURE);
	} else {
		fprintf(pFile, "%s", "MOSESDB_RECORD");
	}
	printf("record created successfully\n");
}

void print_schema(FILE* pFile)
{
	char buffer[80];
	if (pFile != NULL) {
		while (fscanf(pFile, "%s", buffer)) {
		printf("%s", buffer);
			if (feof(pFile))  break; 
		}
} else {
	perror("The following error has accurred");
			exit(EXIT_FAILURE);
	}
}

void clear_schema(FILE* pFile)
{
}

int main(int argc, char **argv)
{
	FILE* schemaFile; // file for holding the schema(template for the DB files)
	FILE* readFile; // the file for the record the DB is currently reading
	char readRecord[] = "READ_R";
	char writeRecord[] = "WRITE_R";
	char clearRecord[] = "CLEAR_R";
	char createRecord[] = "CREATE_R";
	char printSchema[] = "PRINT_S";
	char clearSchema[] = "CLEAR_S";
	char command[10];
	field* pFields; // dynamic allocation of fields anyone?
	int numFields; // the number of fields
	char newline[1];
	fpos_t pos; // our position in the schema file

	// begin DB startup sequence
	// open up the schema
	// store the fields and their line numbers
	// close the schema unless its still needed

	printf("Opening up the schema file...\n");
	schemaFile = fopen(argv[1], "r");
	if (schemaFile == NULL) {
		fprintf(stderr, "Error opening file!\n");
		exit(EXIT_FAILURE);
	} else {
		printf("schema file opened successfully...parsing fields now...\n");
	}

	fscanf(schemaFile, "%d", &numFields);
	printf("Found %d fields\n", numFields);

	pFields = (field*) calloc(numFields, numFields * sizeof(field)); // here goes the dynamic allocation

	for (int i = 0; i < numFields; i++) {
		fscanf(schemaFile, "%s", pFields[i].name);
		printf("Field %d: %s\n", i, pFields[i].name);
	}

	// and now begins the database part

	while (1) { // can you think of a better way? TODO: Find a better way
		strcpy(command, "");
		scanf("%s", command);
		if (strcmp(command, readRecord) == 0) {
			read_record(pFields);
		} else if (strcmp(command, writeRecord) == 0) {
			write_record(pFields);
		} else if (strcmp(command, clearRecord) == 0) {
			clear_record();
		} else if (strcmp(command, createRecord) == 0) {
			create_record();
		} else if (strcmp(command, printSchema) == 0) {
			print_schema(schemaFile);
		} else if (strcmp(command, clearSchema) == 0) {
			clear_schema(schemaFile);
		}
	}

	return 0;
}
