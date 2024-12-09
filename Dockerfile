FROM ubuntu

RUN apt-get update && apt-get -y install \
    git gcc gdb \
    valgrind check make ffmpeg \
    python3.12 pkg-config

WORKDIR /tads
