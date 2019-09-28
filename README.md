# 易受危害的CGI應用程式

``` bash
gcc login.c -o login 
sudo docker build -t my-httpd . 
sudo docker run -p 8080:80 my-httpd
```
