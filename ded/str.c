#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>

int my_puts (const char* str);

char* my_strchr (char* str, int chr);

size_t my_strlen (const char* str);

char* my_strcpy (char* destination, const char* source);

char* my_strncpy (char* destination, const char* source, size_t n);

char* my_strcat (char* str, const char* add);

char* my_strncat (char* str, const char* add, size_t n);

char* my_fgets(char* line, size_t maxline, FILE* file);

char* my_strdup(char* str);

int main(){
	//my_puts check
	const char* str1 = "I like to sleep";
	my_puts(str1);
	puts(str1);
	
	//my_strchr check
	char str[] = "I like to sleep";
	int chr = 101;
	if (my_strchr(str, chr) == strchr(str, chr))
		printf("cool\n");

	//my_strlen check
	if (my_strlen(str1) == strlen(str1))
		printf("cool\n");

	//my_strcpy check
	const char* source = "I want to sleep"; 
	char* destination = (char*) calloc(16, sizeof(char));
	my_puts(my_strcpy(destination, source));
	my_puts(strcpy(destination, source));

	//my_strncpy check
	size_t n = 6;
	my_puts(my_strncpy(destination, source, n));
	my_puts(strncpy(destination, source, n));

	//my_strcat check
	char* str2 = (char*) calloc(50, sizeof(char));
	my_strcpy(str2, str1);
	const char* add = " and eat";
	my_puts(my_strcat(str2, add));
	my_puts(strcat(str2, add));

	//my_strncat check
	my_puts(my_strncat(str2, add, n));
	my_puts(strncat(str2, add, n));
	
	//my_fgets check
	char* line = (char*) calloc(30, sizeof(char));
	size_t maxline = 10;
	FILE* file = fopen("file", "r");
	my_puts(my_fgets(line, maxline, file));

	//my_strdup check
	char* duplicate = my_strdup(str);
	my_puts(duplicate);
	

	free(line);
	free(destination);
	free(str2);
	free(duplicate);
}

int my_puts (const char* str){
	while(*str != '\0'){
		putc(*str, stdout);
		str++;
	}
	putc('\n', stdout);
	return 0;
}

char* my_strchr (char* str, int chr){
	while (*str != chr && *str != '\0')
		str++;
	return (*str == chr) ? str : NULL;
}

size_t my_strlen (const char* str){
	size_t len = 0;
	while(*str++)
		len++;
	return len;
}

char* my_strcpy (char* destination, const char* source){
	char* begin = destination;
	while (*source){
		*destination = *source;
		destination++;
		source++;
	}
	*destination = '\0';
	return begin;
}

char* my_strncpy (char* destination, const char* source, size_t n){
	for (size_t i = 0; i < n && *source != '\0'; i++){
		*destination = *source;
		destination++;
		source++;
	}	
	*destination = '\0';
	return destination - n;
}

char* my_strcat (char* str, const char* add){
	char* begin = str;
	str += my_strlen(str);
	while (*add){
		*str = *add;
		str++;
		add++;
	}
	*str = '\0';
	return begin;
}

char* my_strncat (char* str, const char* add, size_t n){
	char* begin = str;
	str += my_strlen(str);
	for (size_t i = 0; i < n && *add != '\0'; i++){
		*str= *add;
		str++;
		add++;
	}
	*str = '\0';
	return begin;
}

char* my_fgets(char* line, size_t maxline, FILE* file){
	int c;
	char* cursor = line;
	while ((c = getc(file)) != '\n' && --maxline > 1 && c != EOF){
		*cursor = (char) c;
		cursor++;
	}
	*cursor = '\0';
	if (c == EOF){
		return NULL;
	}
	else{
		return line;
	}
}

char* my_strdup(char* str){
	char* duplicate;
	duplicate = (char*) malloc(my_strlen(str) + 1);
	if (duplicate != NULL)
		my_strcpy(duplicate, str);
	return duplicate;
}
