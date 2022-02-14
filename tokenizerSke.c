#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/* Return true (non-zero) if c is the delimiter character
   previously chosen by the user.
   Zero terminators are not printable (therefore false) */
bool delim_character(char c, char delim){
   return c == delim;
}

/* Return true (non-zero) if c is a non-delimiter
   character.
   Zero terminators are not printable (therefore false) */
bool non_delim_character(char c, char delim){
   return c != delim;
}

/* Returns a pointer to the first character of the next
   word starting with a non-delimiter character. Return a zero pointer if
   str does not contain any words.*/
char *word_start(char* str,char delim){   
   char* firstChar = '\0';
   for (int i = 0; str[i] != '\0'; i++){
      if(delim_character(str[i],delim) == true && non_delim_character(str[i+1],delim)){
         firstChar = &str[i+1];
         break;
      }
   }
   return firstChar;
}

/* Returns a pointer to the first delimiter character of the zero
   terminated string*/
char *end_word(char* str,char delim){
   char* endWord = '\0';
   for (int i = 0; str[i] != '\0'; i++){
      if(delim_character(str[i],delim)){
         endWord = &(str[i]);
         break;
      }
   }
   return endWord;
}

/* Counts the number of words or tokens*/
int count_tokens(char* str,char delim){
   int count = 0;
   if(delim_character(str[0], delim)){
      count++;
      str = word_start(str, delim);
   }
   else{
      count++;
   }
   str = end_word(str, delim);
   for (int i = 0;i<strlen(str)-1;i++){
      if (delim_character(str[i],delim) && non_delim_character(str[i+1],delim) && str[i] != '\0'){
         count++;
      }
   }
   return count;
}

/* Returns a freshly allocated new zero-terminated string
   containing <len> chars from <inStr> */
char *copy_str(char *inStr, short len, char delim){
   char* new_string = (char*) malloc((len+1) * sizeof(char));
   for (int i = 0; i < len; i++){
      if(delim_character(inStr[i], delim)){
         break;
      }
      new_string[i] = inStr[i];
   }
   new_string[len] = '\0';
   return new_string;
}

/* Returns a freshly allocated zero-terminated vector of freshly allocated
   delimiter-separated tokens from zero-terminated str.
   For example, tokenize("hello world string"), with a character delimiter
   of a space " " would result in:
     tokens[0] = "hello"
     tokens[1] = "world"
     tokens[2] = "string"
     tokens[3] = 0
*/
char** tokenize(char* str, char delim){
   int tokCount = count_tokens(str, delim);
   char** token = (char**) malloc((tokCount+1) * sizeof(char*));
   
   if(delim_character(str[0],delim)){
      str = word_start(str,delim);
   }

   for (int i = 0; i < tokCount; i++) {
      token[i] = copy_str(str, strlen(str), delim);
      if(str[0] == '\0'){
         break;
      }
      str = word_start(str,delim);
   }
   token[tokCount] = '\0';
   return token;
}

void print_all_tokens(char** tokens){ 
   for (int i = 0; tokens[i] != '\0';i++){
      printf("Token[%d] = %s\n", i, tokens[i]);
   }
}

int main()
{
   char input[] = "Hello,World";
   char *pinput = input;
   char delim = ',';
   int count = count_tokens(pinput, delim);

   char *x = word_start(pinput, delim);
   printf("The first letter is: %c\n",*x);
   x = end_word(pinput, delim);
   printf("The delimeter is: %c\n",*x);
   printf("The number of tokens is %d\n", count);
   print_all_tokens(tokenize(pinput, delim));
}