
/**
 * Precondition: N/A
 * Postcondition: Input is gathered from the user.
 * Return: An integer that the user put in or an error message.
 */int getInt(char *prompt);

/**
 * Precondition: N/A
 * Postcondition: Input is gathered from the user.
 * Return: Number of long type that the user put in or an error message.
 */long getLong(char *prompt);

/**
 * Precondition: N/A
 * Postcondition: Input is gathered from the user.
 * Return: An unsigned number that the user put in or an error message.
 */unsigned getUnsigned(char *prompt);


/**
 * Precondition: N/A
 * Postcondition: Input is gathered from the user.
 * Return: Character(s) that the user put in or an error message.
 */
char* getInput(char *prompt);