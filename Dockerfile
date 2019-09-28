FROM httpd
COPY ./httpd.conf /usr/local/apache2/conf/httpd.conf
COPY ./index.html /usr/local/apache2/htdocs/index.html
COPY ./login /usr/local/apache2/cgi-bin/
