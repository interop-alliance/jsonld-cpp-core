#!/bin/bash

./configure --with-ssl=/usr/local/opt/openssl@1.1 --disable-ldap --without-libidn2 --without-zlib
make
make install
