/*
   Zachary Ikpefua
   ECE 2220
   Project 5
   Spring 2018
   Purpose: See the properites of words given by a certain dictionary
   Estimations: I estimated that this project will take 5 days, but only took
            around 2 days
   Known Bugs: NONE
 */
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define MAX_LENGTH 256
int checkRight(char);
int checkLeft(char);
int checkTop(char);
int checkMiddle(char);
int checkBottom(char);
int findDous(char[]);
int checkVowel(char []);
int isChar(char);
int samewrdCheck(char[],int,int);

int main(int argc, char *argv[]) {
        char **Words;
        FILE *diction;
        FILE *out;
        char trash[MAX_LENGTH]; //trash var to read in dictionary
        char lower = '\a'; //iniitalize to unseen var

        int length =  0; //standard strlen for multiple words
        int a = 0;
        int b = 0;
	int c = 0;
        int i = 0;
        int lengthwoNull = 0;
        int complen = 0;
        int numDous = 0;
        int palCheck = 0;
        int vowel = 0;
        int leftChars = 0;
        int totChars = 0;
        int findWord = 0;
        int numWords = 0;

        float percentLeft = 0.0;
//Initialze all maxes to make sure complen increases
        int longestRight = -1;
        int longestLeft = -1;
        int longestTop = -1;
        int longestMid = -1;
        int longestBot = -1;
        int longestDous = -1;
        int longestVowel = -1;

        int leftside = 0;
        int rightside = 0;
        int toprow = 0;
        int midrow = 0;
        int lowrow = 0;

        diction = fopen(*(argv + 1),"r");
        out = fopen(*(argv + 2), "w");

        if (argc != 3)
        {
                //No input or output
                fprintf (stderr, "Please enter 1 input file and 1 output file\n");
                exit (1);
        }
//Check to see if each input file exists
        if (*(argv + 1) == NULL)
        {
                fprintf (stderr, "File open error. Exiting program\n");
                exit (1);
        }

        while (fscanf (diction, "%s", trash) != -1)
        {
                numWords++;
        }

        //Pointer mallocing
        Words = (char **) malloc (numWords * sizeof (char*));

        rewind(diction);
        //Point to the words after mallocing

        for(i = 0; i < numWords; i++) {
                fscanf(diction,"%s",trash);
                length = strlen(trash);
                Words[i] = (char *)malloc(length * sizeof(char) + 1);
                strcpy(Words[i],trash);
        }
        //Tell user that analysis has begun
        printf("\aStarting \"%s\" word analysis....\n",*(argv + 1));
        sleep(2);
        //Go through switch case to accomplish each analysis step
        for(i = 1; i <= 9; i++) {
                switch (i) {
                case 1: //Words written w/ Right hand only
                        fprintf(out,"Longest Word(s) typed only with right hand:\n");
			printf("Longest Word(s) typed only with right hand:\n");
                        for(a = 0; a < numWords; a++) {
                                length = strlen(Words[a]);
                                rightside = 0;
                                for(b = 0; b < length; b++) {
                                        //lowercase words
                                        lower = tolower(Words[a][b]);
                                        rightside += checkRight(lower);
                                }
                                if(rightside == length) {
                                  //Method for finding max index
                                        complen = strlen(Words[a]);
                                        if(complen >= longestRight) {
                                                longestRight = complen;
                                        }
                                }
                        }
                        if(longestRight == -1) {
                          //If the max never changed then there was no word that matched category
                                fprintf(out,"No words in this category\n");
				printf("No words in this category\n");
                        }
                        else{
                                fprintf(out,"-Longest word had %d letters-\n",longestRight);
				printf("-Longest word had %d letters-\n",longestRight);
                                for(b = 0; b < numWords; b++) {
                                        findWord = samewrdCheck(Words[b],longestRight,1);
                                        if(findWord == 1) {
                                                fprintf(out,"%s\n",Words[b]);
					 	printf("%s\n",Words[b]);
                                        }
                                }
                        }
                        break;
                case 2:
                        fprintf(out,"\nLongest Word(s) typed only with left hand:\n");
			printf("\nLongest Word(s) typed only with left hand:\n");
                        complen = 0;
                        //Words written w/ left hand only
                        for(a = 0; a < numWords; a++) {
                                length = strlen(Words[a]);
                                leftside = 0;
                                for(b = 0; b < length; b++) {
                                        lower = tolower(Words[a][b]);
                                        leftside += checkLeft(lower);
                                }
                                if(leftside == length) {
                                        complen = strlen(Words[a]);
                                        if(complen >= longestLeft) {
                                                longestLeft = complen;
                                        }
                                }
                        }
                        if(longestLeft == -1) {
                                fprintf(out,"No words in this category\n");
				printf("No words in this category\n");
                        }
                        else{
                                fprintf(out,"-Longest word had %d letters-\n",longestLeft);
				printf("-Longest word had %d letters-\n",longestLeft);
                                for(b = 0; b < numWords; b++) {
                                        findWord = samewrdCheck(Words[b],longestLeft,2);
                                        if(findWord == 1) {
                                                fprintf(out,"%s\n",Words[b]);
						printf("%s\n",Words[b]);
                                        }
                                }
                        }
                        break;
                case 3:
                        //Words typed with first row on keyboard (top)
                        complen = 0;
                        fprintf(out,"\nLongest Word(s) typed on the first row:\n");
			printf("\nLongest Word(s) typed on the first row:\n");
                        for(a = 0; a < numWords; a++) {
                                length = strlen(Words[a]);
                                toprow = 0;
                                for(b = 0; b < length; b++) {
                                        lower = tolower(Words[a][b]);
                                        toprow += checkTop(lower);
                                }
                                if(toprow == length) {
                                        complen = strlen(Words[a]);
                                        if(complen >= longestTop) {
                                                longestTop = complen;
                                        }
                                }
                        }
                        if(longestTop == -1) {
                                fprintf(out,"No words in this category\n");
				printf("No words in this category\n");
                        }
                        else{
                                fprintf(out,"-Longest word had %d letters-\n",longestTop);
				printf("-Longest word had %d letters-\n",longestTop);
                                for(b = 0; b < numWords; b++) {
                                        findWord = samewrdCheck(Words[b],longestTop,3);
                                        if(findWord == 1) {
                                                fprintf(out,"%s\n",Words[b]);
						printf("%s\n",Words[b]);
                                        }
                                }
                        }
                        break;
                case 4:
                        //Words typed with second row on keyboard (middle)
                        complen = 0;
                        fprintf(out,"\nLongest Word(s) typed on the second row:\n");
			printf("\nLongest Word(s) typed on the second row:\n");
                        for(a = 0; a < numWords; a++) {
                                length = strlen(Words[a]);
                                midrow = 0;
                                for(b = 0; b < length; b++) {
                                        lower = tolower(Words[a][b]);
                                        midrow += checkMiddle(lower);
                                }
                                if(midrow == length) {
                                        complen = strlen(Words[a]);
                                        if(complen >= longestMid) {
                                                longestMid = complen;
                                        }
                                }
                        }
                        if(longestMid == -1) {
                                fprintf(out,"No words in this category\n");
				printf("No words in this category\n");
                        }
                        else{
                                fprintf(out,"-Longest word had %d letters-\n",longestMid);
				printf("-Longest word had %d letters-\n",longestMid);
                                for(b = 0; b < numWords; b++) {
                                        findWord = samewrdCheck(Words[b],longestMid,4);
                                        if(findWord == 1) {
                                                fprintf(out,"%s\n",Words[b]);
						printf("%s\n",Words[b]);
                                        }
                                }
                        }
                        break;
                case 5:
                        //Words typed with third row on keyboard (bottom)
                        complen = 0;
                        fprintf(out,"\nLongest Word(s) typed on the third row:\n");
			printf("\nLongest Word(s) typed on the third row:\n");
                        for(a = 0; a < numWords; a++) {
                                length = strlen(Words[a]);
                                lowrow = 0;
                                for(b = 0; b < length; b++) {
                                        lower = tolower(Words[a][b]);
                                        lowrow += checkBottom(lower);
                                }
                                if(lowrow == length) {
                                        complen = strlen(Words[a]);
                                        if(complen >= longestBot) {
                                                longestBot = complen;
                                        }
                                }
                        }
                        if(longestBot == -1) {
                                fprintf(out,"No words in this category\n");
				printf("No words in this category\n");
                        }
                        else{
                                fprintf(out,"-Longest word had %d letters-\n",longestBot);
				printf("-Longest word had %d letters-\n",longestBot);
                                for(b = 0; b < numWords; b++) {
                                        findWord = samewrdCheck(Words[b],longestBot,5);
                                        if(findWord == 1) {
                                                fprintf(out,"%s\n",Words[b]);
						printf("%s\n",Words[b]);
                                        }
                                }
                        }
                        break;
                case 6:
                        fprintf(out,"\nAll words and the longest words ending in \"dous\":\n");
			printf("\nAll words and the longest words ending in \"dous\":\n");
                        //Words ending in 'dous' from dictionary
                        for(a = 0; a < numWords; a++) {
                                numDous = findDous(Words[a]);
                                if(numDous == 1) {
                                        fprintf(out,"%s\n",Words[a]);
					printf("%s\n",Words[a]);
                                        complen = strlen(Words[a]);
                                        if(complen >= longestDous) {
                                                longestDous = complen;
                                        }
                                }
                        }
                        if(longestDous == -1) {
                                fprintf(out,"No words in category\n");
				printf("No words in category\n");
                        }
                        else{
                                fprintf(out,"\nLongest \"dous\" words (%d letters):\n",longestDous);
				printf("\nLongest \"dous\" words (%d letters):\n",longestDous);
                                for(b = 0; b < numWords; b++) {
                                        findWord = samewrdCheck(Words[b],longestDous,6);
                                        if(findWord == 1) {
                                                fprintf(out,"%s\n",Words[b]);
						printf("%s\n",Words[b]);
                                        }
                                }
                        }
                        break;
                case 7:
                        //Words that are palindromes
                        fprintf(out,"\nAll palindromes:\n");
			printf("\nAll palindromes:\n");
			c = 0;
                        for(a = 0; a < numWords; a++) {
                                palCheck = 0;
                                lengthwoNull = strlen(Words[a]) - 1;
                                length = lengthwoNull;
                                for(b = 0; b < length; b++) {
                                        if(Words[a][b] == Words[a][lengthwoNull]) {
                                                palCheck++;
                                        }
                                        lengthwoNull--;
                                }
                                if(palCheck == length) {
                                        fprintf(out,"%s\n",Words[a]);
					printf("%s\n",Words[a]);
					c++;
                                }
                        }
			if(c == 0) {
				fprintf(out,"No words in category\n");
				printf("No words in category\n");
			}
                        break;
                case 8:
                        //All words and longest word that has all five vowels in order
                        fprintf(out,"\nAll words and longest word with all voewls together:\n");
			printf("\nAll words and longest word with all voewls together:\n");
                        for(a = 0; a < numWords; a++) {
                                vowel = checkVowel(Words[a]);
                                if(vowel == 1) {
                                        fprintf(out,"%s\n",Words[a]);
					printf("%s\n",Words[a]);
                                        complen = strlen(Words[a]);
                                        if(complen >= longestVowel) {
                                                longestVowel = complen;
                                        }
                                }
                        }
                        if(longestVowel == -1) {
                                fprintf(out,"No words in category\n");
				printf("No words in category\n");
                        }
                        else{
                                fprintf(out,"\nLongest vowel words (%d letters):\n",longestVowel);
				printf("\nLongest vowel words (%d letters):\n",longestVowel);
                                for(b = 0; b < numWords; b++) {
                                        findWord = samewrdCheck(Words[b],longestVowel,7);
                                        if(findWord == 1) {
                                                fprintf(out,"%s\n",Words[b]);
						printf("%s\n",Words[b]);
                                        }
                                }
                        }
                        break;
                case 9:
                        //The percentage of time the left hand is used to type all dictionary
                        //words in order
                        fprintf(out,"\nPercentage of left hand is used to type all \"%s\" words:\n",*(argv + 1));
			printf("\nPercentage of left hand is used to type all \"%s\" words:\n",*(argv + 1));
                        for(a = 0; a < numWords; a++) {
                                length = strlen(Words[a]);
                                for(b = 0; b < length; b++) {
                                        //Incrementing leters to find percentage
                                        leftChars += checkLeft(Words[a][b]);
                                        totChars += isChar(Words[a][b]);
                                }
                        }
                        //Change int to float so percent is not int/rounded down
                        percentLeft = (float)leftChars / totChars;
                        percentLeft *= 100;
                        fprintf(out, "Percentage is: %.2f%%\n",percentLeft);
			printf("Percentage is: %.2f%%\n",percentLeft);
                        break;
                }
        }
        printf("Finished analyzing...Open \"%s\" file to see results again\n",*(argv + 2));
        return 0;
}
/*
   Function: checkRight
   Inputs:   letter from word currently observed in loop
   Outputs:  1 or 0, depending on if the letter is present
   Purpose:  To see if the letter exists on the left hand leftside
          of the keyboard
 */
int checkRight(char letter){
        char list[] = "yhnujmiklop";
        char *search;

        search = strchr(list,letter);
        //If search is NULL, that means comdition is not present in the word
        if(search != NULL) {
                return 1;
        }
        else{
                return 0;
        }
}
/*
   Function: checkLeft
   Inputs:   letter from word currently observed in loop
   Outputs:  1 or 0, depending on if the letter is present
   Purpose:  To see if the letter exists on the right hand side
          of the keyboard
 */
int checkLeft(char letter){
        char list[] = "qazwsxedcrfvtgb";
        char *search;

        search = strchr(list,letter);
        if(search != NULL) {
                return 1;
        }
        else{
                return 0;
        }
}
/*
   Function: checkTop
   Inputs:   letter from word currently observed in loop
   Outputs:  1 or 0, depending if letter is present
   Purpose:  To see if the letter exists on the first row
          of the keyboard
 */
int checkTop(char letter){
        char list[] = "qwertyuiop";
        char *search;

        search = strchr(list,letter);
        if(search != NULL) {
                return 1;
        }
        else{
                return 0;
        }
}
/*
   Function: checkMidde
   Inputs:   letter from word currently observed in loop
   Outputs:  1 or 0, depending if letter is present
   Purpose:  To see if the letter exists on the second row
          of the keyboard
 */
int checkMiddle(char letter){
        char list[] = "asdfghjkl";
        char *search;

        search = strchr(list,letter);
        if(search != NULL) {
                return 1;
        }
        else{
                return 0;
        }
}
/*
   Function: checkBottom
   Inputs:   letter from word currently observed in loop
   Outputs:  1 or 0, depending if letter is present
   Purpose:  To see if the letter exists on the third row
          of the keyboard
 */
int checkBottom(char letter){
        char list[] = "zxcvbnm";
        char *search;

        search = strchr(list,letter);
        if(search != NULL) {
                return 1;
        }
        else{
                return 0;
        }
}
/*
   Function: findDous
   Inputs:   word being currently observed in loop
   Outputs:  1 or 0, depending if word dous is present
   Purpose:  To see if the phrase 'dous' is present at the end
          of the word itself
 */
int findDous(char word[]){
        char *search;
        int a = 0;

        search = strstr(word, "dous");
        a = strlen(word);
        if(search == NULL) {
                return 0;
        }
        else{
                if(word[a - 1] != 's' || word[a - 2] != 'u' || word[a - 3] != 'o' || word[a - 4] != 'd') {
                        return 0;
                }
                else{
                        return 1;
                }
        }
}
/*
   Function: checkVowel
   Inputs:   word currently observed in loop
   Outputs:  1 or 0, depending if five voewls are present consistently
          (not exactly in order)
   Purpose:  To check and see if the there is a word that
          has all five vowels 'aeiou' IN ORDER
 */
int checkVowel(char word[]){
        char *search1;
        char *search2;
        char *search3;
        char *search4;
        char *search5;
        int i = 0;

        for(i = 0; word[i]; i++) {
                word[i] = tolower(word[i]);
        }
        for(i = 0; i < strlen(word); i++) {
                search1 = strchr(&word[i], 'a');
                if(search1 != NULL) {
                        search2 = strchr(&word[i], 'e');
                        if(search2 != NULL) {
                                search3 = strchr(&word[i], 'i');
                                if(search3 != NULL) {
                                        search4 = strchr(&word[i],'o');
                                        if(search4 != NULL) {
                                                search5 = strchr(&word[i],'u');
                                                if(search5 != NULL) {
                                                        if(search1 < search2 && search2 < search3 && search3 < search4 && search4 < search5) {
                                                                return 1;
                                                        }
                                                }
                                        }
                                }
                        }
                }
        }
        return 0;
}
/*
   Function: isChar
   Inputs:   letter from word currently observed in loop
   Outputs:  1 or 0, depending if letter
   Purpose:  To see if the character presnted is a character
          in order to increment the totChars variable (in main)
 */
int isChar(char chr){
        int a = 0;
        a = isalpha(chr);
        if(a != 0) {
                return 1;
        }
        else{
                return 0;
        }
}
/*
   Function: samewrdCheck
   Inputs:   current word, length of longest word from loop,
          number for identifing which function to call
   Outputs:  1 or 0, depending on if the word satisfies the
          condition of the previous function and is equal to
          length of longest word
   Purpose:  This function was created to see if other words are (1)
          the same length of the max word from the loop for the
          certain conditions and (2) send each word back to the
          original function to verify if that particular word is
          acceptable to be displayed in output file
 */
int samewrdCheck(char word[],int longLen,int process){
        int currLen = 0;
        int i = 0;
        int a = 0;

        currLen = strlen(word);
        for(i = 0; i < currLen; i++) {
                word[i] = tolower(word[i]);
        }
        switch (process) {
        case 1:
                //Return to Right function
                for(i = 0; i < currLen; i++) {
                        a += checkRight(word[i]);
                }
                if(a == currLen && a == longLen) {
                        return 1;
                }
                else{
                        return 0;
                }

                break;
        case 2:
                //Return to left function
                for(i = 0; i < currLen; i++) {
                        a += checkLeft(word[i]);
                }
                if(a == currLen && a == longLen) {
                        return 1;
                }
                else{
                        return 0;
                }
                break;
        case 3:
                //Return to Top function
                for(i = 0; i < currLen; i++) {
                        a += checkTop(word[i]);
                }
                if(a == currLen && a == longLen) {
                        return 1;
                }
                else{
                        return 0;
                }
                break;
        case 4:
                //Return to Middle fucntion
                for(i = 0; i < currLen; i++) {
                        a += checkMiddle(word[i]);
                }
                if(a == currLen && a == longLen) {
                        return 1;
                }
                else{
                        return 0;
                }
                break;
        case 5:
                //Return to Botom function
                for(i = 0; i < currLen; i++) {
                        a += checkBottom(word[i]);
                }
                if(a == currLen && a == longLen) {
                        return 1;
                }
                else{
                        return 0;
                }
                break;
        case 6:
                //Return to Dous function
                if(currLen == longLen) {
                        a = findDous(word);
                        if(a == 1) {
                                return 1;
                        }
                        else{
                                return 0;
                        }
                }
                else{
                        return 0;
                }
                break;
        case 7:
                //Return to vowel function
                if(currLen == longLen) {
                        a = checkVowel(word);
                        if(a == 1) {
                                return 1;
                        }
                        else{
                                return 0;
                        }
                }
                else {
                        return 0;
                }
                break;
        }
        return 0;
}
