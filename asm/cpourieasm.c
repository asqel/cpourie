#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int char_count(char *text, int c) {
	int res = 0;
	for (int i = 0; text[i] != '\0'; i++)
		if (text[i] == c)
			res++;
	return res;
}

void fix_text(char *text) {
	int len = strlen(text);
	int i = 0;

	while (i < len) {
		if (text[i] == '\r') {
			for (int k = i + 1; k < len; k++)
				text[k - 1] = text[k];
			len--;
			text[len] = '\0';
		}
		else
			i++;
	}
}

int get_line_len(char *text) {
	int res = 0;
	while (text[res] != '\0' && text[res] != '\n')
		res++;
	return res;
}

char *trim_spaces(char *str) {
	int start = 0;
	int end = strlen(str);

	while (isspace(str[start]))
		start++;
	while (isspace(str[end - 1]) && end - 1 >= 0)
		end--;

	int len = end - start;
	if (len <= 0) {
		free(str);
		return (NULL);
	}
	char *res = malloc(sizeof(char) * (len + 1));
	memcpy(res, &str[start], len);
	res[len] = '\0';
	return res;
}

void fix_lines(char **lines, int *len) {
	// trim left and right space
	// remove empty lines
	for (int i = 0; i < *len; i++)
		lines[i] = trim_spaces(lines[i]);
	int i = 0;
	while (i < *len) {
		if (lines[i] == NULL) {
			for (int k = i + 1; k < *len; k++)
				lines[k - 1] = lines[k];
			(*len)--;
		}
		else
			i++;
	}
}

char **split_lines(char *text, int *len) {
	char **res = malloc(sizeof(char *) * (1 + char_count(text, '\n')));
	int i = 0;
	*len = 0;

	fix_text(text);
	while (text[i] != '\0') {
		if (text[i] == '\n') {
			i++;
			continue;
		}
		int line_len = get_line_len(&text[i]);
		res[*len] = malloc(sizeof(char) * (1 + line_len));

		memcpy(res[*len], &text[i], line_len);
		res[*len][line_len] = '\0';
		i += line_len;
		(*len)++;
	}
	fix_lines(res, len);
	return realloc(res, sizeof(char *) * (*len));
}
