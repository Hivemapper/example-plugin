FROM ubuntu:20.04

ENV DEBIAN_FRONTEND=noninteractive

# Install dependencies
RUN apt-get update && \
    apt-get install -y \
        cmake \
        git \
        openssh-client \
        libcurl4-openssl-dev \
        wget \
        unzip \
        python3 \
        python3-pip \
        build-essential \
        autoconf \
        automake \
        libtool \
        perl \
        pkg-config \
        gcc-aarch64-linux-gnu \
        g++-aarch64-linux-gnu \
        libeigen3-dev \
        libsqlite3-dev \
        libpthread-stubs0-dev \
        netcat \
        libssl-dev \
        libc6-dev-arm64-cross \
        && rm -rf /var/lib/apt/lists/*

# Build Protobuf for aarch64
WORKDIR /opt
RUN git clone --depth 1 --branch v3.21.12 https://github.com/protocolbuffers/protobuf.git
WORKDIR /opt/protobuf/cmake/build-aarch64
RUN cmake ../.. \
    -DCMAKE_SYSTEM_NAME=Linux \
    -DCMAKE_SYSTEM_PROCESSOR=aarch64 \
    -DCMAKE_C_COMPILER=aarch64-linux-gnu-gcc \
    -DCMAKE_CXX_COMPILER=aarch64-linux-gnu-g++ \
    -DCMAKE_INSTALL_PREFIX=/opt/protobuf-aarch64 \
    -Dprotobuf_BUILD_TESTS=OFF && \
    make -j$(nproc) && \
    make install

# add protoc
# Clone and build just protoc
RUN git clone -b v3.21.12 --depth 1 https://github.com/protocolbuffers/protobuf.git /protobuf && \
    cd /protobuf && \
    ./autogen.sh && \
    ./configure && \
    make -j$(nproc) && \
    make install && \
    ldconfig

# Build libcurl for aarch64
WORKDIR /opt
RUN git clone --depth 1 --branch curl-7_76_1 https://github.com/curl/curl.git
WORKDIR /opt/curl
RUN autoreconf -fi && \
    ./configure \
      --host=aarch64-linux-gnu \
      --prefix=/opt/curl-aarch64 \
      --disable-shared \
      --enable-static \
      --without-ssl && \
    make -j$(nproc) && \
    make install

WORKDIR /app
RUN git clone https://github.com/Hivemapper/hive-cpp.git
WORKDIR /app/hive-cpp
RUN rm -rf build && mkdir -p build && cd build && cmake .. && make && make install

# Copy over example-plugin
WORKDIR /app
COPY . /app/example-plugin
# Modify CMakeLists.txt to include pthread and dl
RUN sed -i '/target_link_libraries(ExamplePlugin/,/)/ s/)/    pthread\n    dl\n)/' /app/example-plugin/src/CMakeLists.txt
RUN cat /app/example-plugin/src/CMakeLists.txt
# add in docker compile message for transperancy
RUN sed -i '/int counter = 0;/a\    std::cout << "+++++ CROSS COMPILED IN DOCKER +++++" << std::endl;' /app/example-plugin/src/ExamplePlugin.cpp

WORKDIR /app/example-plugin
# Build your project for aarch64 using cross-compiled Protobuf
RUN rm -rfv build/ && mkdir -p build
WORKDIR /app/example-plugin/build
RUN cmake .. \
    -DCMAKE_SYSTEM_NAME=Linux \
    -DCMAKE_SYSTEM_PROCESSOR=aarch64 \
    -DCMAKE_C_COMPILER=aarch64-linux-gnu-gcc \
    -DCMAKE_CXX_COMPILER=aarch64-linux-gnu-g++ \
    -DProtobuf_INCLUDE_DIR=/opt/protobuf-aarch64/include \
    -DProtobuf_LIBRARY=/opt/protobuf-aarch64/lib/libprotobuf.a \
    -DCURL_INCLUDE_DIR=/opt/libcurl-aarch64/include \
    -DCURL_LIBRARY=/opt/libcurl-aarch64/lib/libcurl.a \
    -DCMAKE_EXE_LINKER_FLAGS="-lpthread -ldl" \
    -DCMAKE_CXX_FLAGS="-lpthread -ldl" \
    && make -j$(nproc)

# Runtime entrypoint (only for demo, update as needed)
CMD ["/bin/bash"]
