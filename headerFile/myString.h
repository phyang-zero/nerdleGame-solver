#ifndef STRING_FUNCTION_H
#define STRING_FUNCTION_H
#include <stdio.h>

char* Strcpy(char* des, const char* source) {
	char* r = des;
	//assert((des != NULL) && (source != NULL));
	while ((*r++ = *source++) != '\0');
	return des;
}

size_t Strlen(const char* str) {
	size_t count = 0;
	while (*str != '\0') {
		str++;
		count++;
	}
	return count;
}

char* Strncpy(char* dest, const char* src, size_t len) {
	char* ret = dest;
	int offset = 0;
//	assert(dest != NULL);
//	assert(src != NULL);
	if (Strlen(src) < len) {
		offset = len - Strlen(src);
		len = Strlen(src);
	}
	while (len) {
		*dest++ = *src++;
		len--;
	}
	while (offset) {
		*dest++ = '\0';
		offset--;
	}
	return ret;
}

int Strcmp(char a[9], char b[9]) {
	for (int i = 0; i < 9; i++) if (a[i] != b[i]) return 0;
	return 1;
}

char* Strchr(char *s, char c) {
	while (*s != '\0' && *s != c) ++s;
	return *s == c ? s : NULL;
}

#endif
