// MagicPen.cpp
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <malloc.h>
#include <string.h>

#define FILE_NAME_LENGTH 20

// Function prototypes
void AddText(char** iopszText);
void UpdateText(char** iopszText);
void DeleteText(char** iopszText);
void WriteToFile(char** ipszText);
void ReadFromFile(char** iopszText);

//-----------------------------------------------------------------------------
//								Magic Pen
//								---------
//
// General : The program is editing a text.
//
// Input : A text to edit, file with text.
//
// Process : Adding a text to a string, updating a string, saving text in file.
//
// Output : Edited text
//
//-----------------------------------------------------------------------------
// Programmer : Yuval Sarig
// Student No : 322875816
// Date : 20.11.2019
//-----------------------------------------------------------------------------
void main()
{
	// Array definition
	char* szText = NULL;

	// Variable definition
	int nMenu;

	// Code section

	printf("Insert number between 1-6\n");
	scanf("%d", &nMenu);

	// Check if menu nuber equal 6 that means exit
	while (nMenu != 6)
	{
		// Check what menu type is it
		switch (nMenu)
		{
		case 1:
			AddText(&szText);
			break;
		case 2:
			UpdateText(&szText);
			break;
		case 3:
			DeleteText(&szText);
			break;
		case 4:
			printf("The text is: %s\n", szText);
			break;
		case 5:
			WriteToFile(&szText);
			break;
		case 7:
			ReadFromFile(&szText);
			break;
		default:
			break;
		}
		printf("Insert number between 1-6\n");
		scanf("%d", &nMenu);
	}
}

//-----------------------------------------------------------------------------
//									Add Text
//									--------
//
// General : Added text to the main text.
//
// Parameters :
//			   iopszText - A pointer to a main text (In/Out)
//
// Return Value : None
//
//-----------------------------------------------------------------------------
void AddText(char** iopszText)
{
	// Array definition
	char* szAddText;

	// Variable definition 
	int nTextLength;

	// Code section
	printf("Insert text length\n");
	scanf("%d", &nTextLength);
	
	// Check if iopszText is NULL
	if (!*iopszText)
	{
		// Allocates memory to main text
		*iopszText = (char*)malloc((nTextLength + 1) * sizeof(char));
		printf("Insert text to add\n");
		scanf("%s", *iopszText);
	}
	else
	{
		// Allocates memory to added text
		szAddText = (char*)malloc((nTextLength + 1) * sizeof(char));
		printf("Insert text to add\n");
		scanf("%s", szAddText);

		// Allocates memory to main text and added text
		*iopszText = (char*)realloc(*iopszText, (nTextLength + strlen(*iopszText) - 1) *
								    sizeof(char));

		// Add the added text to the end of the text
		strcat(*iopszText, szAddText);

		// Free memory of added text
		free(szAddText);
	}
}

//-----------------------------------------------------------------------------
//									Update Text
//									-----------
//
// General : Update the main text.
//
// Parameters :
//			   iopszText - A pointer to a main text (In/Out)
//
// Return Value : none
//
//-----------------------------------------------------------------------------
void UpdateText(char** iopszText)
{
	// Array definition
	char* szUpdateText;

	// Variable definition 
	int nUpdateStart;
	int nTextLength;
	int nDifference;

	// Code section
	printf("Insert start point to update\n");
	scanf("%d", &nUpdateStart);
	printf("Insert text length\n");
	scanf("%d", &nTextLength);

	// Allocates memory to update text 
	szUpdateText = (char*)malloc((nTextLength + 1) * sizeof(char));
	printf("Insert text to update\n");
	scanf("%s", szUpdateText);
	
	// Fits the first letter to update to the string
	nUpdateStart--;
	nDifference = (nUpdateStart + nTextLength) - strlen(*iopszText);
	
	// Check if the update text exceeds from main text range
	if (nDifference <= 0)
	{
		
		// Changing update text in main text 
		for (int i = 0; i < nTextLength; i++)
		{
			// Set in update text in main text char by char
			*(*iopszText + (i + nUpdateStart)) = szUpdateText[i];
		}
	}
	else
	{
		// Allocates memory to text and update text that exceeds from main text range
		*iopszText = (char*)realloc(*iopszText, (nDifference + strlen(*iopszText) - 1) *
									sizeof(char));

		// Set null terminator in update start point
		*(*iopszText + (nUpdateStart)) = 0;

		// Changing update text in main text from null terminator
		strcat(*iopszText, szUpdateText);
	}
	// Free memory of update text
	free(szUpdateText);
}

//-----------------------------------------------------------------------------
//									Delete Text
//									-----------
//
// General : Delete number of letters from the ens of main text.
//
// Parameters :
//			   iopszText - A pointer to a main text (In/Out)
//
// Return Value : None
//
//-----------------------------------------------------------------------------
void DeleteText(char** iopszText)
{
	// Variable definition 
	int nDeleteLength;
	int nMainTextLength;

	// Code section

	printf("Insert start point to delete\n");
	scanf("%d", &nDeleteLength);
	nMainTextLength = strlen(*iopszText);

	// Set null terminator from where delete should start
	*(*iopszText + (nMainTextLength - nDeleteLength)) = '\0';

	// Allocates memory to main text after delete number of letters
	*iopszText = (char*)realloc(*iopszText, (nMainTextLength - nDeleteLength + 1) *
								sizeof(char));
}

//-----------------------------------------------------------------------------
//									Write To File
//									-------------
//
// General : Save the main text in a file.
//
// Parameters :
//			   ipszText - A pointer to a main text (In)
//
// Return Value : None
//
//-----------------------------------------------------------------------------
void WriteToFile(char** ipszText)
{
	// Array definition
	char szFileName[FILE_NAME_LENGTH];

	// File definition
	FILE* fsFileSaveText;
	printf("Insert file name\n");
	scanf("%s", szFileName);

	// Open file to insert the main text
	fsFileSaveText = fopen(szFileName, "wt");

	// Write in file the main text
	fwrite(*ipszText, sizeof(char) , strlen(*ipszText), fsFileSaveText);

	// Close file
	fclose(fsFileSaveText);
}

//-----------------------------------------------------------------------------
//								Read From File
//								--------------
//
// General : Insert text to main text from a file.
//
// Parameters :
//			   iopszText - A pointer to a main text (In / Out)
//
// Return Value : None
//
//-----------------------------------------------------------------------------
void ReadFromFile(char** iopszText)
{
	// Array definition
	char szFileName[FILE_NAME_LENGTH];
	char cLastReadFromFile;
	int  nReadenCharsConter = 0;

	// File definition
	FILE* fsFileGetText;
	// Check if main text isn't null
	if (!*iopszText)
	{
		// Free memory of main text
		free(*iopszText);
	}

	printf("Insert file name\n");
	scanf("%s", szFileName);

	// Open file to insert the main text
	fsFileGetText = fopen(szFileName, "rt");

	// Read char by char from file,
	// if the char equal to (-1) -> end of file than exit while
	while ((cLastReadFromFile = fgetc(fsFileGetText)) != EOF)
	{

		// Allocates memory to main text for another char that was read from file
		*iopszText = (char*)realloc(*iopszText, (nReadenCharsConter + 1) * sizeof(char));

		// Insert the last readen char from file to the main text
		(*iopszText)[nReadenCharsConter++] = cLastReadFromFile;
	}	

	// Set null terminator in the end of string
	(*iopszText)[nReadenCharsConter] = 0;

	// Close file
	fclose(fsFileGetText);
}