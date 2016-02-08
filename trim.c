/*
* Filename    : trim.c
* Authors     : Michael Maxner, Nathan Bray
* Description : This file contains a trim function we made 
* as well as some test cases we made to make sure it worked
*/

#include <stdio.h>
#include <string.h>

#define SCANSETMAXSIZE 121

#define TESTCASEAMOUNT 8
#define TRIMLIST "\r\n\t"

// Prototype
char* trim(char* string);

int main(void)
{
	char test[TESTCASEAMOUNT][SCANSETMAXSIZE] = {
		"  Spaces Both Sides   ",
		"Test Tab Key\t",
		"",
		"nospaces",
		"newLineSpace \n",
		"    Only Front Spaces",
		"                                ",
		"               \n" };

	// Loop through each string to test function
	for (int i = 0; i < TESTCASEAMOUNT; i++)
	{
		printf("<%s>\n", trim(test[i]));
	}

	return 0;
}


/*
* Function    : char* trim
* Description : This function can remove the whitespace on either end of a string parameter.
*				It will also take a non-delimited list of other single characters you
*				can trim using the defined TRIMLIST string to for example, remove
*				the newline character at the end of a string.
* 
* Parameter   : char* string - This is the string to be chacked and possibly trimmed
* Returns     : char* string - This is the same string, after the trim function has completed
*/
char* trim(char* string)
{
	if (string != NULL && strlen(string) > 0)
	{
		char scanset[SCANSETMAXSIZE] = "";

#ifdef TRIMLIST		
		sprintf(scanset, "%%[%s ]", TRIMLIST);
#endif // TRIMLIST

#ifndef TRIMLIST
		sprintf(scanset, "%%[ ]");
#endif // No TRIMLIST


		char tempString[SCANSETMAXSIZE] = "";
		char* frontPtr = string;
		char* backPtr = &string[strlen(string) - 1];

		// Move pointer forward until trim character is no longer found
		while ((sscanf(frontPtr, scanset, &tempString) == 1) && frontPtr < backPtr)
		{
			frontPtr++;
		}
		// Same idea, but at the back of the string
		while ((sscanf(backPtr, scanset, &tempString) == 1) && backPtr >= frontPtr)
		{
			backPtr--;
		}

		// Move the back pointer up one and put a null terminator there, cutting off the string
		backPtr++;
		*backPtr = '\0';

		// Then just copy the string from where the front pointer stopped as the final result
		strcpy(string, frontPtr);
	}

	return string;
}