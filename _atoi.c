#include "shell.h"

/**
 * isInteractive - returns true if shell is in interactive mode
 * @infoStruct: struct address
 *
 * Return: 1 if interactive mode, 0 otherwise
 */
int isInteractive(custom_info_t *infoStruct)
{
	return (isatty(STDIN_FILENO) && infoStruct->readFileDescriptor <= 2);
}

/**
 * isDelimiter - checks if character is a delimiter
 * @character: the char to check
 * @delimiterString: the delimiter string
 * Return: 1 if true, 0 if false
 */
int isDelimiter(char character, char *delimiterString)
{
	while (*delimiterString)
		if (*delimiterString++ == character)
			return (1);
	return (0);
}

/**
 * isAlpha - checks for alphabetic character
 * @character: The character to input
 * Return: 1 if character is alphabetic, 0 otherwise
 */
int isAlpha(int character)
{
	if ((character >= 'a' && character <= 'z') ||
			(character >= 'A' && character <= 'Z'))
		return (1);
	else
		return (0);
}

/**
 * stringToInteger - converts a string to an integer
 * @inputString: the string to be converted
 * Return: 0 if no numbers in string, converted number otherwise
 */
int stringToInteger(char *inputString)
{
	int index, sign = 1, flag = 0, result;
	unsigned int integerValue = 0;

	for (index = 0; inputString[index] != '\0' && flag != 2; index++)
	{
		if (inputString[index] == '-')
			sign *= -1;

		if (inputString[index] >= '0' && inputString[index] <= '9')
		{
			flag = 1;
			integerValue *= 10;
			integerValue += (inputString[index] - '0');
		}
		else if (flag == 1)
			flag = 2;
	}

	if (sign == -1)
		result = -integerValue;
	else
		result = integerValue;

	return (result);
}

