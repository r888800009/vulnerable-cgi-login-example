#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

bool containChar(char c, char *list) {
  int len = strlen(list), i = 0;

  while (i < len) {
    if (c == list[i]) return true;
    i++;
  }

  return false;
}

int getString(char *dest, char *buf, int start, int length, char *breakChar) {
  int cur = start;
  while (cur < length && !containChar(buf[cur], breakChar)) cur++;
  strncpy(dest, buf + start, cur - start);
  dest[cur - start] = '\0';
  return cur;
}

char *html =
    "\
    <!DOCTYPE html>\n\
    <html>\n\
      <head>\n\
        <title>Login</title>\n\
      </head>\n\
      <body>\n\
       %s\n\
      </body>\n\
    </html>\n";

void printHTML(char *output) {
  printf("Content-type: text/html\n\n");
  printf(html, output);
}

void login() {
  char buf[512];
  char id[128];
  char pass[128];
  int length;

  // read data
  gets(buf);
  length = strlen(buf);

  // split data
  int start = 0;

  while (start < length) {
    char data[128];
    char name[64];

    start = getString(name, buf, start, length, "=&");
    if (start >= length || buf[start] == '&') {
      data[0] = '\0';
      start++;
    } else {
      start = getString(data, buf, start + 1, length, "&") + 1;
    }

    // store data
    if (strcmp(name, "id") == 0)
      strncpy(id, data, strlen(data));
    else if (strcmp(name, "pass") == 0)
      strncpy(pass, data, strlen(data));
  }

  // send result
  printHTML(id);
}

int main() {
  login();
  return 0;
}
