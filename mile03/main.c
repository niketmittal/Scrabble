/*
This file corresponds to the Milestone 3 of the DSA Project
This project belongs to Group 13.
Members:-
1. SHREYASH YADAV: 19UEC135
2. NIKET MITTAL: 19UCS090
3. ADITYA BADONI: 19UCC139
4. VINAYAK SINGH: 19UCS165
5. HARSH KUMAR: 19UCS185
6. RAJAN JAIN: 19UME004
7. NISHANT KATARA: 19UCC100
FILE SUBMISSION DATE: 10/04/2020
*/

#include<stdio.h>
#include<string.h>
#include <ctype.h>
#include<stdlib.h>
#include<time.h>
#define SIZE 100000

int maxn(int a, int b)
{
    //This function computes the maximum of two given numbers.
    if(a>b)
        return a;
    else if (b>a)
        return b;
    else
        return a;
}
int score(char word[], int s)
{
    //This function computes the score of the given word.
    int weight=0;
    for(int i=0 ; i < strlen(word) ; i++)
    {
        if((word[i]=='Q')||(word[i]=='Z'))
            weight=weight+10;
        else if((word[i]=='J')||(word[i]=='X'))
            weight=weight+8;
        else if(word[i]=='K')
            weight=weight+5;
        else if((word[i]=='F')||(word[i]=='H')||(word[i]=='V')||(word[i]=='W')||(word[i]=='Y'))
            weight=weight+4;
        else if((word[i]=='B')||(word[i]=='C')||(word[i]=='M')||(word[i]=='P'))
            weight=weight+3;
        else if((word[i]=='D')||(word[i]=='G'))
            weight=weight+2;
        else if((word[i]=='E')||(word[i]=='A')||(word[i]=='I')||(word[i]=='O')||(word[i]=='N')||(word[i]=='R')||(word[i]=='T')||(word[i]=='L')||(word[i]=='S')||(word[i]=='U'))
            weight=weight+1;
        else
            weight=weight+0;
    }
      int word_length=strlen(word);
      int good = (s - 1) * word_length;
      int bad = maxn((3 * (s + 1 - word_length)), 1);
      int mult = good-bad;
      int score = mult*weight;
      return score;
}

int scoreofstar(char letter[], char word[], int s){
    //This function helps in calculation of the word when stars are included in that.
    int n1 = strlen(letter);
    int n2 = strlen(word);
    int weight=0;

    for(int i=0; i<n2; i++){
        for(int j=0; j<n1; j++){
            if(word[i] == letter[j]){
                if((letter[j]=='Q')||(letter[j]=='Z'))
                    weight=weight+10;
                else if((letter[j]=='J')||(letter[j]=='X'))
                    weight=weight+8;
                else if(letter[j]=='K')
                    weight=weight+5;
                else if((letter[j]=='F')||(letter[j]=='H')||(letter[j]=='V')||(letter[j]=='W')||(letter[j]=='Y'))
                    weight=weight+4;
                else if((letter[j]=='B')||(letter[j]=='C')||(letter[j]=='M')||(letter[j]=='P'))
                    weight=weight+3;
                else if((letter[j]=='D')||(letter[j]=='G'))
                    weight=weight+2;
                else if((letter[j]=='E')||(letter[j]=='A')||(letter[j]=='I')||(letter[j]=='O')||(letter[j]=='N')||(letter[j]=='R')||(letter[j]=='T')||(letter[j]=='L')||(letter[j]=='S')||(letter[j]=='U'))
                    weight=weight+1;
                else
                    weight=weight+0;
                letter[j] = 0;
                break;
            }
        }
    }
    int word_length = strlen(word);
    int good = (s - 1) * word_length;
    int bad = maxn((3 * (s + 1 - word_length)), 1);
    int mult = good-bad;
    int score = mult*weight;
    return score;
}

int check(char word[], char letter[]){
    //This function checks if word[] can be made up of letter[].
    //It returns 1 in case of true and 0 in case of false.
    int flag = 0;
    int n1 = strlen(letter);
    int n2 = strlen(word);
	for(int i=0; i<n2; i++){
        for(int j=0; j<n1; j++){
            if(word[i] == letter[j]){
                flag++;
                letter[j] = 0;
                break;
            }
        }
	}

	if(flag==n2)
        return 1;
    else
        return 0;
}

int flag = 0, score_of_word[SIZE];

int multiplestars(char letter[], int no_of_stars, char word[], char letter2[], char maximum_word[], int* maximum_score)
{
    //This function works in case '*' is given in the bag of letters.
    char vowels[5] = {'A','E','I','O','U'};
    int n = strlen(letter);
    char temp[SIZE], temp2[SIZE], temp3[SIZE];
    int count = 0;

    FILE *fptr;
    fptr = fopen("dic.txt","r");

    for(int i=0; i<n; i++){

        strcpy(temp,letter);

        if(temp[i] == '*'){
            count++;
            for(int j=0; j<5; j++){
                temp[i] = vowels[j];
                if(no_of_stars > count){
                    multiplestars(temp, no_of_stars - count, word, letter2, maximum_word, maximum_score); //The recursion used here is to check for all possible permutations in between the stars.
                }
                int flag1 = 0;
                for(int k=0; k<n; k++)
                    if(temp[k] != '*')
                        flag1++;
                if(flag1 == n){

                    strcpy(temp2, temp);

                    if(check(word,temp2) == 1){
                        score_of_word[flag] = scoreofstar(letter2, word, n);
                        if(flag == 0){
                            strcpy(maximum_word, word);
                            (*maximum_score) = score_of_word[flag];
                            flag++;
                        }
                        else if(score_of_word[flag] > score_of_word[flag-1]){
                            strcpy(maximum_word, word);
                            (*maximum_score) = score_of_word[flag];
                            flag++;
                        }
                    }
                return flag;  //flag returns the number of printed words.
                }
            }
        }
    }
}

int main(){
    time_t start, end;
    start = time(NULL);
    flag = 0;
	char word[SIZE], letter1[SIZE], letter[SIZE], letter2[SIZE];

    printf("Enter Bag of Letters : ");
	scanf("%[^\n]", letter1);
	int n2 = strlen(letter1);   //n2 is the variable that tells the number of letters in a bag.

	int s = 0;
	for(int i=0; i<n2; i++){
        //This loop ignores any other character than alphabet or '*' in the bag of letters.
        if(isalpha(letter1[i]) || letter1[i] == '*'){
            letter[s] = letter1[i];
            s++;
        }
	}
	int n1 = strlen(letter);    //n1 is the variable that tells the UPDATED number of letters in bag of letters.
    printf("\n");

	for(int i=0; i<SIZE; i++){
            //This loop converts all the characters to upper case.
            if(islower(letter[i]))
                letter[i] = toupper(letter[i]);
    }

    int n3 = 0;
	for(int i=0; i<n1; i++) //This loop counts the number of '*'s in the letter.
        if(letter[i] == '*')
            n3++;

    FILE *fptr;
    fptr = fopen("dic.txt","r");
    char temp[SIZE], maximum_word[SIZE];
    int a = 0;
    int* maximum_score;

    if(n3>0){
            //It works in case * is present.
            while(!feof(fptr)){
                fscanf(fptr, "%s", word);
                strcpy(letter2, letter);
                a = multiplestars(letter2,n3,word,letter2,maximum_word,&maximum_score);
            }
            if(a == 0)
                printf("--> Word Not Found in the Dictionary.\n\n");
            else{
                printf("--> %s can be made out of the letters in the bag.\n", maximum_word);
                printf("--> Score of the word %s = %d\n\n", maximum_word, maximum_score);
            }
    }
    else{
        while(!feof(fptr)){
            //This loop checks if any word (from the dictionary) can be made from the bag of letters entered.
            fscanf(fptr, "%s", word);
            strcpy(temp, letter);

            if(check(word,temp) == 1){
                score_of_word[flag] = score(word, n1);
                if(flag == 0){
                    strcpy(maximum_word, word);
                    maximum_score = score_of_word[flag];
                    flag++;
                }
                else if(score_of_word[flag] > score_of_word[flag-1]){
                    strcpy(maximum_word, word);
                    maximum_score = score_of_word[flag];
                    flag++;
                }
            }
        }
        if(flag == 0)
            printf("--> Word Not Found in the Dictionary.\n\n");
        else{
            printf("--> %s can be made out of the letters in the bag.\n", maximum_word);
            printf("--> Score of the word %s = %d\n\n", maximum_word, maximum_score);
        }
    }

    fclose(fptr);
    end = time(NULL);
    printf("Time taken : %.2f seconds.\n", difftime(end, start));//This tells us the runtime of the code.
}
