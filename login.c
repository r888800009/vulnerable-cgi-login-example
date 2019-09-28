#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

bool containChar(char c, char *list) {
  while (*list != '\0') {
    if (c == *list) return true;
    list++;
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
  puts("");
}

void verify(char *id, char *pass) {
  if (strcmp(id, "root") == 0 && strcmp(pass, "password") == 0)
    printHTML("hello, root");
  else
    printHTML(
        "<script>\
          alert('try again');\
          history.go(-1);\
        </script>");
}

void login() {
  char buf[512];
  char id[128] = {0};
  char pass[128] = {0};
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
    //    int dataLength = strlen(data);
    if (strcmp(name, "id") == 0)
      strcpy(id, data);
    else if (strcmp(name, "pass") == 0)
      strcpy(pass, data);
  }

  // send result
  verify(id, pass);
}

int main() {
  login();
  return 0;
}
