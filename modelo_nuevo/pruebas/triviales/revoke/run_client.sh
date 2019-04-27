#!/usr/bin/
valgrind --track-origins=yes ./client 127.0.0.1 8080 revoke "Federico Manuel Gomez Peter.cert" client0.keys server.pubkeys
