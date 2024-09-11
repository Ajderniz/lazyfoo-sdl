#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void)
{
	char arr1[] = "abc";
	char arr2[] = "def";

	char *str1 = NULL;
	char *str2 = NULL;
	char *temp = NULL;

	str1 = calloc(strlen(arr1) + 1, sizeof(char));
	str2 = calloc(strlen(arr2) + 1, sizeof(char));

	strcpy(str1, arr1);
	strcpy(str2, arr2);
	printf("%s\n%s\n", str1, str2);

	temp = calloc((strlen(str1) + 1) + (strlen(str2) + 1), sizeof(char));
	strcat(temp, str1);
	strcat(temp, str2);

	free(str1);
	str1 = calloc(strlen(temp) + 1, sizeof(char));
	str1 = temp;
	temp = NULL;
	printf("%s\n", str1);

	free(str1);
	free(str2);

	return 0;
}
