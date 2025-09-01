/*
 * adder.c - a minimal CGI program that adds two numbers together
 */
/* $begin adder */
#include "csapp.h"

int main(void) {

  char *buf, *p;
  char arg1[MAXLINE], arg2[MAXLINE], content[MAXLINE];
  int n1 = 0, n2 = 0;

  /* Extract the two arguments */
  if ((buf = getenv("QUERY_STRING")) != NULL) {
    p = strchr(buf, '&');
    *p = '\0';
    strcpy(arg1, buf);
    strcpy(arg2, p + 1);
    n1 = atoi(strchr(arg1, '=') + 1);
    n2 = atoi(strchr(arg2, '=') + 1);
  }

  /* Make the response body */
  int n = 0;
  n += snprintf(content + n, MAXBUF - n, "<h1>Welcome to add.com:</h1>\r\n");
  n += snprintf(content + n, MAXBUF - n, "<p>THE Internet addition portal.</p>\r\n");
  n += snprintf(content + n, MAXBUF - n, "<p>The answer is: %d + %d = %d</p>\r\n", n1, n2, n1 + n2);
  n += snprintf(content + n, MAXBUF - n, "<h1>ADD HTML TAG</h1>\r\n");
  n += snprintf(content + n, MAXBUF - n, "arg1:<input type=""text"" id=""arg1"" value=""%d"" /><br>\r\n", n1);
  n += snprintf(content + n, MAXBUF - n, "arg2:<input type=""text"" id=""arg2"" value=""%d"" /><br>\r\n", n2);
  n += snprintf(content + n, MAXBUF - n, "total:<input type=""text"" id=""total"" value=""%d"" /><br>\r\n", n1 + n2);
  n += snprintf(content + n, MAXBUF - n, "Thanks for visiting!\r\n");
  
  /* Generate the HTTP response */
  printf("Connection: close\r\n");
  printf("Content-length: %d\r\n", (int)strlen(content));
  printf("Content-type: text/html\r\n\r\n");

  /* 11.11 HTTP HEAD */
  if (!strcasecmp(getenv("METHOD"), "HEAD")) {
    printf("%s", "");
  } else {
    printf("%s", content);
  }

  fflush(stdout);
  exit(0);
}
/* $end adder */
