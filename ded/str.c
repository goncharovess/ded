#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

int my_puts (const char* s){
	printf("%s\n", s);
	return 0;
}

char* my_strchar (char* s, int c){
	while (*s != c && *s != '\0')
		s++;
	return (*s == c) ? s : NULL;
}

int my_strlen (const char* s){
	int len = 0;
	while(*s++)
		len++;
	return len;
}

char* my_strcpy (char* s, const char* ct){
	int len = my_strlen(ct);
	while (*ct){
		*s = *ct;
		s++;
		ct++;
	}
	*s = '\0';
	return s - len;
}

char* my_strncpy (char* s, const char* ct, size_t n){
	for (int i = 0; i < n && *ct != '\0'; i++){
		*s = *ct;
		s++;
		ct++;
	}	
	*s = '\0';
	return s - n;
}

char* my_strcat (char* s, const char* ct){
	int len = my_strlen(s) + my_strlen(ct);
	s += my_strlen(s);
	while (*ct){
		*s = *ct;
		s++;
		ct++;
	}
	*s = '\0';
	return s - len;
}

int main(){
	const char* ct = "sleep";
	const char* s = "I like to ";
	char* s1 = malloc(my_strlen(ct) + my_strlen(s));
	s1 = my_strcpy(s1, s);
	s1 = my_strcat(s1, ct);
	printf("%s\n", s1);
}
