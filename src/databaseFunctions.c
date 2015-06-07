#include "../include/databaseFunctions.h"

int print_record(field *fields, int num_fields)
{
	FILE* pFile;
	char *fileName;
	char *readField;
	size_t n = 10;
	size_t s = 10;
	printf("What is the name of the record? ");
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
			printf("%s: %s\n", fields[i].name, readField);
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
	printf("What is the name of the record?(the file will be overwritten) ");
	fileName = (char *) malloc(n);
	m_getline(&fileName, &n, stdin);
	writeField = (char *) malloc(s);
	pFile = fopen(fileName, "w");
	if (pFile == NULL) {
		printf("No dice. Segfault!\n");
		return FUNCTION_ERROR;
	} else {
		for (int i = 1; i <= num_fields; i++) {
			printf("%s: ", fields[i].name);
			m_getline(&writeField, &s, stdin);
			fprintf(pFile, "%s\n", writeField);
			strcpy(writeField, "");
		}
	}

	printf("done writing to record %s\n", fileName);
	fclose(pFile);
	free(fileName);
	return FUNCTION_SUCCESS;
}

int delete_record()
{
	char *recordName;
	size_t n = 10;
	printf("What is the name of the record(**WARNING:FILE WILL BE DELETED**)? ");
	recordName = (char *) malloc(n);
	m_getline(&recordName, &n, stdin);
	remove(recordName);
	printf("record successfully deleted\n");
	return FUNCTION_SUCCESS;
}

int clear_record()
{
	FILE* pFile;
	char *recordName;
	size_t n = 10;
	printf("What is the name of the record(the file itself will not be deleted)? ");
	recordName = (char *) malloc(n);
	m_getline(&recordName, &n, stdin);
	pFile = fopen(recordName, "w");
	if (pFile == NULL) {
		perror("The following error has occurred");
		return FUNCTION_ERROR;
	} else {
		freopen(recordName, "w", pFile);
		printf("%s cleared successfully\n", recordName);
	}
	fclose(pFile);
	return FUNCTION_SUCCESS;
}

int create_record()
{
	FILE* pFile;
	char *recordName;
	size_t n = 10;
	printf("What is the name of this new record(names must not overlap)? ");
	recordName = (char *) malloc(n);
	m_getline(&recordName, &n, stdin);
	pFile = fopen(recordName, "w");
	if (pFile == NULL) {
		perror("The following error has occurred");
		return FUNCTION_ERROR;
	}
	printf("record created successfully\n");
	fclose(pFile);
	return FUNCTION_SUCCESS;
}

int print_schema(field* fields, int num_fields)
{
	for (int i = 1; i <= num_fields; i++) {
		printf("%s\n", fields[i].name);
	}
	return FUNCTION_SUCCESS;
}

int clear_schema(FILE* pFile, char *pFileName)
{
	char *recordName = strdup(pFileName);
	pFile = freopen(recordName, "w", pFile);
	return FUNCTION_SUCCESS;
}
