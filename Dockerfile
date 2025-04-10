FROM ubuntu:20.04

ENV DEBIAN_FRONTEND=noninteractive

RUN apt-get update && \
    apt-get install -y \
        cmake \
        build-essential \
        libeigen3-dev \
        libcurl4-openssl-dev \
        python3 \
        python3-pip \
        netcat && \
    rm -rf /var/lib/apt/lists/*

RUN pip3 install flask
WORKDIR /usr/src/app
COPY . /usr/src/app
RUN rm -rf build && mkdir -p build && cd build && cmake .. && make

COPY entrypoint.sh /usr/local/bin/entrypoint.sh
RUN chmod +x /usr/local/bin/entrypoint.sh

EXPOSE 9000

ENTRYPOINT ["/usr/local/bin/entrypoint.sh"]