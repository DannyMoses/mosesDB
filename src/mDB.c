/*
** Simple database written for fun
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/dynamicString.h"
#include "../include/databaseFunctions.h"

int main(int argc, char **argv)
{
	FILE* schemaFile; // file for holding the schema(template for the DB files)
	char readRecord[] = "PRINT_R";
	char writeRecord[] = "WRITE_R";
	char clearRecord[] = "CLEAR_R";
	char createRecord[] = "CREATE_R";
	char deleteRecord[] = "DELETE_R";
	char printSchema[] = "PRINT_S";
	char clearSchema[] = "CLEAR_S";
	char command[100];
	field* pFields; // dynamic allocation of fields anyone?
	int numFields; // the number of fields

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
	
	/* coverity[+alloc] */
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
			print_record();
		} else if (strcmp(command, writeRecord) == 0) {
			write_record(pFields, numFields);
		} else if (strcmp(command, clearRecord) == 0) {
			clear_record();
		} else if (strcmp(command, createRecord) == 0) {
			create_record();
		} else if (strcmp(command, printSchema) == 0) {
			print_schema(pFields, numFields);
		} else if (strcmp(command, clearSchema) == 0) {
			clear_schema(schemaFile, argv[1]);
		} else if (strcmp(command, deleteRecord) == 0) {
			delete_record();
		}else if (strcmp(command, "HELP") == 0) {
				printf("TODO: make a help function\n");
		} else if (strcmp(command, "EXIT") == 0) {
			printf("Exiting...\n");
			exit(EXIT_SUCCESS);
		} else {
			printf("Command not recognized, please try again.\n");
		}
	}

	return 0;
}
