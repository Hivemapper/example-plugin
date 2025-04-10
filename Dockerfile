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
        netcat \
        git \
        build-essential \
        cmake \
        && rm -rf /var/lib/apt/lists/*


WORKDIR /app
RUN git clone https://github.com/Hivemapper/hive-cpp.git
WORKDIR /app/hive-cpp
RUN rm -rf build && mkdir -p build && cd build && cmake .. && make && make install

RUN pip3 install flask
WORKDIR /usr/src/app
COPY . /usr/src/app
RUN rm -rf build && mkdir -p build && cd build && cmake .. && make

COPY entrypoint.sh /usr/local/bin/entrypoint.sh
RUN chmod +x /usr/local/bin/entrypoint.sh

EXPOSE 9000

ENTRYPOINT ["/usr/local/bin/entrypoint.sh"]