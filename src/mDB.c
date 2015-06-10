/*
** Simple database written for fun
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/databaseFunctions.h"
#include "../include/errorCodes.h"
#include "../include/getline.h"
#include "../include/macros.h"

int main(int argc, char **argv)
{
	FILE* schemaFile; // file for holding the schema(template for the DB files)
	static char readRecord[] = "PRINT_R";
	static char writeRecord[] = "WRITE_R";
	static char clearRecord[] = "CLEAR_R";
	static char createRecord[] = "CREATE_R";
	static char deleteRecord[] = "DELETE_R";
	static char printSchema[] = "PRINT_S";
	static char clearSchema[] = "CLEAR_S";
	static char scanRecord[] = "SCAN_R";
	static char updateRecord[] = "UPDATE_R";
	char *command;
	size_t commandSize = 10;
	field* pFields; // dynamic allocation of fields anyone?
        size_t n = 10; // more dynamic fun! TODO: find a better naem for this
	int numFields; // the number of fields
	static int functionCode; // the code any executed function returns

	// begin DB startup sequence
	// open up the schema
	// store the fields and their line numbers
	// close the schema unless its still needed

	prompt("Opening up the schema file...\n")
	schemaFile = fopen(argv[1], "r");
	if (schemaFile == NULL) {
		fprintf(stderr, "Error opening file!\n");
		exit(EXIT_FAILURE);
	} else {
		prompt("schema file opened successfully...parsing fields now...\n")
	}

	fscanf(schemaFile, "%d", &numFields);
	prompt("Found %d fields\n", numFields)

	/* coverity[+alloc] */
	pFields = (field*) calloc(numFields, numFields * sizeof(field)); // here goes the dynamic allocation

	for (int i = 0; i <= numFields; i++) {
                pFields[i].name = (char *) malloc(n);
		m_getline(&pFields[i].name, &n, schemaFile); 
		if (i != 0) { 
			prompt("Field %d: %s\n", i, pFields[i].name)
		} else {
		}
	}

	prompt("Initializing command sequence...\n")
	command = (char *) malloc(commandSize);

	// and now begins the database part

	while (1) { // can you think of a better way? TODO: Find a better way
                 
                printf("mosesdb> ");
		functionCode = 5;
		strcpy(command, "");
		m_getline(&command, &commandSize, stdin);
		
		if (memcmp(command, readRecord, sizeof(readRecord)) == 0) {
			functionCode = print_record(pFields, numFields);
		} else if (memcmp(command, writeRecord, sizeof(writeRecord)) == 0) {
			functionCode = write_record(pFields, numFields);
		} else if (memcmp(command, clearRecord, sizeof(clearRecord)) == 0) {
			functionCode = clear_record();
		} else if (memcmp(command, createRecord, sizeof(createRecord)) == 0) {
			functionCode = create_record();
		} else if (memcmp(command, printSchema, sizeof(printSchema)) == 0) {
			functionCode = print_schema(pFields, numFields);
		} else if (memcmp(command, clearSchema, sizeof(clearSchema)) == 0) {
			functionCode = clear_schema(schemaFile, argv[1]);
		} else if (memcmp(command, deleteRecord, sizeof(deleteRecord)) == 0) {
			functionCode = delete_record();
		} else if (memcmp(command, scanRecord, sizeof(scanRecord)) == 0) {
			functionCode = scan_record(pFields, numFields);
		} else if (memcmp(command, updateRecord, sizeof(updateRecord)) == 0) {
			functionCode = update_record(pFields, numFields);
		}else if (memcmp(command, "HELP", sizeof("HELP")) == 0) {
			prompt("Commands: \n")
			prompt("%s: prints out the contents of a record\n", readRecord)
			prompt("%s: creates a new record and lets you write to it\n", writeRecord)
			prompt("%s: clears a record of all its contents without deleting it\n", clearRecord)
			prompt("%s: creates an empty record\n", createRecord)
			prompt("%s: prints out the contents of the schema\n", printSchema)
			prompt("%s: clears the contents of the schema\n", clearSchema)
			prompt("%s: permanently deletes a record and all its contents\n", deleteRecord)
		} else if (memcmp(command, "EXIT", sizeof("EXIT")) == 0) {
			break;
		} else {
			prompt("Command not recognized, please try again.\n")
		}

		switch(functionCode) {
		case FUNCTION_SUCCESS:
			prompt("Command executed successfully. Carry on.\n")
			break;
		case FUNCTION_POSSIBLE_UNDEF:
			prompt("WARNING: POSSIBLE UNDEFINED BEHAVIOR HAS OCCURRED WITH THE PREVIOUSLY EXITED COMMAND. PLEASE CHECK.\n")
			break;
		case FUNCTION_ERROR:
			prompt("ERROR: LAST COMMAND DID NOT EXECUTE PROPERLY. PLEASE CHECK YOU SYSTEM.\n")
			break;
		case FUNCTION_FATAL_ERROR:
			prompt("FATAL ERROR: A MAJOR FSCKUP HAS OCCURRED. PLEASE EXIT THE PROGRAM AND FRANTICALLY CHECK YOU SYSTEM FOR DAMAGE.\n")
			break;
		default:
			break;
		}
	}

	prompt("Beginning exit sequence...\n")
	prompt("Deallocating fields...\n")

	for (int i = 0; i <= numFields; i++) {
		free(pFields[i].name);
	}

	free(pFields);

	prompt("Closing schema file...\n")

	fclose(schemaFile);

	prompt("Exiting...\n")

	return 0;
}
