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

void print_record()
{
	FILE* pFile;
	char fileName[80];
	char readBuffer[100];
	printf("What is the name of the record? ");
	scanf("%s", fileName);
	pFile = fopen(fileName, "r");

	if (pFile == NULL) {
		perror("The following error has occurred");
		exit(EXIT_FAILURE);
	} else {
		while(fgets(readBuffer, 100, pFile) != NULL) {
			printf("%s", readBuffer);	
		}
	}
}

void write_record(field* fields, int num_fields)
{
	FILE* pFile;
	char fileName[80];
	printf("What is the name of the record? ");
	scanf("%s", fileName);
	pFile = fopen(fileName, "a+");
	
	if (pFile == NULL) {
		perror("The following error has occurred");
		exit(EXIT_FAILURE);
	} else {	
		for (int i = 0; i < num_fields; i++) 
		{
			char buffer[80];
			printf("%s: ", fields[i].name);
			scanf("%s", buffer);
			fprintf(pFile, "%s\n", buffer);
			strcpy(buffer, "");
		}
	}

	printf("done writing to record %s\n", fileName);
	fclose(pFile);
}

void delete_record()
{
	char recordName[80];
	printf("What is the name of the record(**WARNING:FILE WILL BE DELETED**)? ");
	scanf("%s", recordName);
	remove(recordName);
	printf("record successfully deleted\n");
}

void clear_record()
{
	FILE* pFile;
	char recordName[80];
	printf("What is the name of the record(the file itself will not be deleted)? ");
	scanf("%s", recordName);
	pFile = fopen(recordName, "w");
	if (pFile == NULL) {
		perror("The following error has occurred");
		exit(EXIT_FAILURE);
	} else {
		freopen(recordName, "w", pFile);
		printf("%s cleared successfully\n", recordName);
	}
	fclose(pFile);
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
		fprintf(pFile, "%s", "MOSESDB_RECORD\n");
	}
	printf("record created successfully\n");
	fclose(pFile);
}

void print_schema(field* fields, int num_fields)
{
	for (int i = 0; i < num_fields; i++)
	{
		printf("%s\n", fields[i].name);
	}
}

void clear_schema(FILE* pFile, char fileName[80])
{
	pFile = freopen(fileName, "w", pFile);
}

int main(int argc, char **argv)
{
	FILE* schemaFile; // file for holding the schema(template for the DB files)
	FILE* readFile; // the file for the record the DB is currently reading
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
