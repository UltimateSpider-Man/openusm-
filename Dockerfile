FROM ubuntu:20.04

RUN apt-get update && \
    apt-get install -y --no-install-recommends cmake make mingw-w64 && \
    rm -rf /var/cache/apt

WORKDIR /home/devel

