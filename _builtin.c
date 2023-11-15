#include "shell.h"

/**
 * exitShell - exits the shell
 * @shellInfo: Structure containing potential arguments. Used to maintain
 * constant function prototype.
 * Return: exits with a given exit status
 * (0) if shellInfo.argv[0] != "exit"
 */
int exitShell(custom_info_t *shellInfo)
{
	int exitCheck;

	if (shellInfo->argv[1]) /* If there is an exit argument */
	{
		exitCheck = _errorStringToInteger(shellInfo->argv[1]);
		if (exitCheck == -1)
		{
			shellInfo->status = 2;
			printError(shellInfo, "Illegal number: ");
			_errorPuts(shellInfo->argv[1]);
			_errorPutchar('\n');
			return (1);
		}
		shellInfo->errorNumber = _errorStringToInteger(shellInfo->argv[1]);
		return (-2);
	}
	shellInfo->errorNumber = -1;
	return (-2);
}

/**
 * changeDirectory - changes the current directory of the process
 * @shellInfo: Structure containing potential arguments. Used to maintain
 * constant function prototype.
 * Return: Always 0
 */
int changeDirectory(custom_info_t *shellInfo)
{
	char *currentDir, *newDir, buffer[1024];
	int chdirReturn;

	currentDir = getcwd(buffer, 1024);
	if (!currentDir)
		_puts("TODO: >>getcwd failure emsg here<<\n");
	if (!shellInfo->argv[1])
	{
		newDir = _getEnvironmentVariable(shellInfo, "HOME=");
		if (!newDir)
			chdirReturn = /* TODO: what should this be? */
				chdir((newDir = _getEnvironmentVariable
				(shellInfo, "PWD=")) ? newDir : "/");
		else
			chdirReturn = chdir(newDir);
	}
	else if (_strcmp(shellInfo->argv[1], "-") == 0)
	{
		if (!_getEnvironmentVariable(shellInfo, "OLDPWD="))
		{
			_puts(currentDir);
			_putchar('\n');
			return (1);
		}
		_puts(_getEnvironmentVariable(shellInfo, "OLDPWD=")), _putchar('\n');
		chdirReturn = /* TODO: what should this be? */
			chdir((newDir = _getEnvironmentVariable
			(shellInfo, "OLDPWD=")) ? newDir : "/");
	}
	else
		chdirReturn = chdir(shellInfo->argv[1]);
	if (chdirReturn == -1)
	{
		printError(shellInfo, "can't cd to ");
		_errorPuts(shellInfo->argv[1]), _errorPutchar('\n');
	}
	else
	{
		_setEnvironmentVariable
		(shellInfo, "OLDPWD", _getEnvironmentVariable(shellInfo, "PWD="));
		_setEnvironmentVariable(shellInfo, "PWD", getcwd(buffer, 1024));
	}
	return (0);
}

/**
 * showHelp - displays help information
 * @shellInfo: Structure containing potential arguments. Used to maintain
 * constant function prototype.
 * Return: Always 0
 */
int showHelp(custom_info_t *shellInfo)
{
	char **argumentArray;

	argumentArray = shellInfo->argv;
	_puts("help call works. Function not yet implemented \n");
	if (0)
		_puts(*argumentArray); /* temp att_unused workaround */
	return (0);
}
