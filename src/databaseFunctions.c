#include "../include/databaseFunctions.h"

int update_record(field* fields, int num_fields)
{
  FILE* pFile;
  char *file_name;

  return FUNCTION_SUCCESS;
}

int scan_record(field* fields, int num_fields)
{
	FILE* pFile;
	char *fileName;
	char *readField;
	char *parseField;
	char *currField;
	int line = -1;
	size_t f = 10;
	size_t r = 10;
	fileName = (char *) malloc(f);
	readField = (char *) malloc(r);
	prompt("What is the name of the record? ")
	m_getline(&fileName, &f, stdin);
	pFile = fopen(fileName, "r");
	if (pFile == NULL) {
		perror("Oh boy");
		return FUNCTION_ERROR;
		free(fileName);
		free(readField);
	} else {
                prompt("Which field would you like to parse? ")
		m_getline(&readField, &r, stdin);
		for (int i = 1; i <= num_fields; i++) {
			if (strcmp(fields[i].name, readField) == 0) {
				line = i;
				currField = strdup(fields[i].name);
				break;
			} else {
			}
		}
		if (line != -1) {
			parseField = strdup(getNthLine(pFile, line));
			prompt("%s: %s", currField, parseField)
		} else {
			prompt("did you specify the wrong field?\n")
			free(fileName);
			free(readField);
			return FUNCTION_ERROR;
		}
	}

	free(fileName);
	free(readField);
	free(currField);
	free(parseField);
	return FUNCTION_SUCCESS;
}


int print_record(field *fields, int num_fields)
{
	FILE* pFile;
	char *fileName;
	char *readField;
	size_t n = 10;
	size_t s = 10;
	prompt("What is the name of the record? ")
	fileName = (char *) malloc(n);
	m_getline(&fileName, &n, stdin);
	readField = (char *) malloc(s);
	pFile = fopen(fileName, "r");
	if (pFile == NULL) {
		fprintf(stderr, "Nope, still not working. Segfault away!\n");
		return FUNCTION_ERROR;
	} else {
		for (int i = 1; i <= num_fields; i++) {
			strcpy(readField, "");
			m_getline(&readField, &s, pFile);
			prompt("%s: %s\n", fields[i].name, readField)
		}
	}

	free(readField);
	free(fileName);
	return FUNCTION_SUCCESS;
}

int write_record(field* fields, int num_fields)
{
	FILE* pFile;
	char *fileName;
	size_t n = 10;
	size_t s = 10;
	char *writeField;
	prompt("What is the name of the record?(the file will be overwritten) ")
	fileName = (char *) malloc(n);
	m_getline(&fileName, &n, stdin);
	writeField = (char *) malloc(s);
	pFile = fopen(fileName, "w");
	if (pFile == NULL) {
		prompt("No dice. Segfault!\n")
		return FUNCTION_ERROR;
	} else {
		for (int i = 1; i <= num_fields; i++) {
			prompt("%s: ", fields[i].name)
			m_getline(&writeField, &s, stdin);
			fprintf(pFile, "%s\n", writeField);
			strcpy(writeField, "");
		}
	}

	prompt("done writing to record %s\n", fileName)
	fclose(pFile);
	free(fileName);
	return FUNCTION_SUCCESS;
}

int delete_record()
{
	char *recordName;
	size_t n = 10;
	prompt("What is the name of the record(**WARNING:FILE WILL BE DELETED**)? ")
	recordName = (char *) malloc(n);
	m_getline(&recordName, &n, stdin);
	remove(recordName);
	prompt("record successfully deleted\n")
	return FUNCTION_SUCCESS;
}

int clear_record()
{
	FILE* pFile;
	char *recordName;
	size_t n = 10;
	prompt("What is the name of the record(the file itself will not be deleted)? ")
	recordName = (char *) malloc(n);
	m_getline(&recordName, &n, stdin);
	pFile = fopen(recordName, "w");
	if (pFile == NULL) {
		perror("The following error has occurred");
		return FUNCTION_ERROR;
	} else {
		freopen(recordName, "w", pFile);
		prompt("%s cleared successfully\n", recordName)
	}
	fclose(pFile);
	return FUNCTION_SUCCESS;
}

int create_record()
{
	FILE* pFile;
	char *recordName;
	size_t n = 10;
	prompt("What is the name of this new record(names must not overlap)? ")
	recordName = (char *) malloc(n);
	m_getline(&recordName, &n, stdin);
	pFile = fopen(recordName, "w");
	if (pFile == NULL) {
		perror("The following error has occurred");
		return FUNCTION_ERROR;
	}
	prompt("record created successfully\n")
	fclose(pFile);
	return FUNCTION_SUCCESS;
}

int print_schema(field* fields, int num_fields)
{
	for (int i = 1; i <= num_fields; i++) {
		prompt("%s\n", fields[i].name)
	}
	return FUNCTION_SUCCESS;
}

int clear_schema(FILE* pFile, char *pFileName)
{
	char *recordName = strdup(pFileName);
	pFile = freopen(recordName, "w", pFile);
	return FUNCTION_SUCCESS;
}
