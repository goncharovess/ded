#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>

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

int my_strlen (const char* str){
	int len = 0;
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

int main(){
	//my_puts check
	const char* str1 = "I like to sleep";
	my_puts(str1);
	puts(str1);
	
	//my_strchr check
	char* str = "I'd like to sleep";
	int chr = 101;
	if (my_strchr(str, chr) == strchr(str, chr))
		printf("cool\n");

	//my_strlen check
	if (my_strlen(str1) == strlen(str1))
		printf("cool\n");

	//my_strcpy check
	const char* source = "I want to sleep"; 
	char* destination = calloc(16, sizeof(char));
	my_puts(my_strcpy(destination, source));
	my_puts(strcpy(destination, source));

	//my_strncpy check
	size_t n = 6;
	my_puts(my_strncpy(destination, source, n));
	my_puts(strncpy(destination, source, n));

	//my_strcat check
	char* str2 = calloc(30, sizeof(char));
	my_strcpy(str2, str1);
	const char* add = " and eat";
	my_puts(my_strcat(str2, add));
	my_puts(strcat(str2, add));

	//my_strncat check
	my_puts(my_strncat(str2, add, n));
	my_puts(strncat(str2, add, n));

	free(destination);
	free(str2);
	
}
