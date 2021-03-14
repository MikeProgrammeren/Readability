#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>

#define MAXCHAR 1000

struct TextElements{
   int Letters, Words, Sentences;
};

char* ReadFile (char* filename);
bool IsSentence (char character);
bool IsWord (char character);
bool IsLetter (char characters);
struct TextElements CountLettersWordsSentences(char Text[]);
char * ColemanLiauIndex(char Text[]);

int main(){
  char * Text = ReadFile("C:\\readability\\input\\Text.txt");
  if(Text == NULL){
    return 1;
  } 

  ColemanLiauIndex(Text);
  free(Text);
  return 0;
} 

char * ColemanLiauIndex(char* Text){
  struct TextElements textElements = CountLettersWordsSentences(Text);
  float L, S;
  int Index;

  L = (float)textElements.Letters / textElements.Words * 100;
  S = (float)textElements.Sentences / textElements.Words * 100;

  Index = (int)round (0.0588 * L - 0.296 * S - 15.8);

  if (Index > 16) 
    printf("Grade 16+");
  else if (Index < 1) 
    printf("Before Grade 1");
  else 
    printf("Grade %d", Index );
}

struct TextElements CountLettersWordsSentences(char* Text){
  int Letters = 0, Words= 1, Sentences = 0;

  for(int i = 0, n = strlen(Text); i < n ; i++){
    if (IsLetter(Text[i])) 
      Letters++; 
    else if (IsWord(Text[i])) 
      Words++;  
    else if (IsSentence(Text[i])) 
      Sentences++; 
  }
  free (Text);
  struct TextElements textElements = { Letters, Words, Sentences };
  return textElements;
}

bool IsLetter(char character){
  if( (character >= 65 && character < 91) || (character >= 97 && character < 123) ) 
    return true;
  else return false;  
}

bool IsSentence(char character){
  if(character == '!' || character == '?' || character == '.') 
    return true;
  else return false;;  
}

bool IsWord(char character){
  if(character == ' ')
    return true;
  else return false;  
}

char* ReadFile(char* filename){
  FILE *fp;
  char str[MAXCHAR];    
  fp = fopen(filename, "r");
  
  if (fp == NULL){
    printf("Could not open file %s",filename);
    return NULL;
  }
  while (fgets(str, MAXCHAR, fp) != NULL)
  fclose(fp);

  char* conv = malloc(strlen(str)+1);
  strcpy (conv, str);
  return conv;
}