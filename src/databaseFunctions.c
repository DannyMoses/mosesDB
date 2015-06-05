#include "../include/databaseFunctions.h"

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
