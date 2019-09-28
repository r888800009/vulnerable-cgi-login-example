# 易受危害的CGI應用程式

``` bash
mkdir cgi-bin
gcc login.c -o cgi-bin/login 
sudo docker run -p 8080:80 -v "$PWD/cgi-bin":/usr/local/apache2/cgi-bin/ -v "$PWD":/usr/local/apache2/htdocs/ my-httpd
```
