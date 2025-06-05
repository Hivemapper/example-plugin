FROM node:18

ENV DEBIAN_FRONTEND=noninteractive

ARG CACHE_ARCHIVE

# Install necessary tools: curl, git, tar, build tools, etc.
RUN apt-get update && apt-get install -y \
    curl \
    git \
    ca-certificates \
    build-essential \
    python3 \
    python3-pip \
    tar \
    xz-utils

# Install Node.js 18 (official setup for Debian/Ubuntu)
RUN curl -fsSL https://deb.nodesource.com/setup_18.x | bash - && \
    apt-get install -y nodejs && \
    node -v && npm -v

# Set up working directories
WORKDIR /app

# Install git
RUN apt-get update && apt-get install -y git

# Clone the repository
RUN git clone https://github.com/Hivemapper/odc-api.git

# Set working dir to the project
WORKDIR /app/odc-api

# Comment out the 'await connectToRedisServer();' line
RUN sed -i 's/^\( *\)await connectToRedisServer();/\/\/ await connectToRedisServer();/' src/index.ts

# Comment out the 'serviceRunner.add(...)' lines
RUN sed -i '/^\s*serviceRunner\.add(/s/^/\/\/ /' src/index.ts

# Comment out the motion model and packaging function calls
RUN sed -i '/^\s*MotionModelController();/s/^/\/\/ /' src/index.ts && \
    sed -i '/^\s*FrameKmPackagingController();/s/^/\/\/ /' src/index.ts

# Comment out the 'serviceRunner.run();' line
RUN sed -i '/^\s*serviceRunner\.run();/s/^/\/\/ /' src/index.ts

# Comment out the Bonjour declaration and publish block
RUN sed -i '/const bonjour = Bonjour();/,+7 s#^#//#' src/index.ts
# RUN sed -i '/\/\/ Stop Bonjour service/,/^ *});/ s#^#//#' src/index.ts
# RUN sed -i '/\/\/ Stop Bonjour service/ {:a; s#^#//#; n; /^ *});$/!ba; ;}' src/index.ts
RUN sed -i '/\/\/ Stop Bonjour service/ {:a; s#^#//#; n; /console\.log('"'"'Graceful shutdown completed'"'"');/!ba; }' src/index.ts



RUN cat ./src/index.ts

# Install dependencies and build (target ARM64)
RUN npm ci --arch=arm64 && \
    npm run compile-gh --camera=bee

RUN mkdir -p /opt/odc-api/
RUN cp -r /app/odc-api/compiled/* /opt/odc-api/

# Create required directories
RUN mkdir -p /data/recording/redis_handler

COPY ${CACHE_ARCHIVE} .
# Copy and extract the cache archive
RUN if [ -n "$CACHE_ARCHIVE" ]; then \
        TMP_DIR="/tmp/collection_restore" && \
        rm -rf "$TMP_DIR" && \
        mkdir -p "$TMP_DIR" && \
        tar -xzf "$CACHE_ARCHIVE" -C "$TMP_DIR" && \
        echo "Archive extracted to $TMP_DIR" && \
        cp -v "$TMP_DIR"/*.log* /data/recording/ && \
        cp -v "$TMP_DIR"/odc-api.db* /data/recording/ && \
        cp -v "$TMP_DIR"/fusion*.db* /data/recording/redis_handler/ && \
        cp -rv "$TMP_DIR"/cached_observations /data/recording/ && \
        rm -rf "$TMP_DIR"; \
    fi

RUN mkdir -p /opt/dashcam/bin
COPY config.json /opt/dashcam/bin/
COPY odc-api-plugins.json /opt/odc-api/

COPY entrypoint.sh /entrypoint.sh
RUN chmod +x /entrypoint.sh
ENTRYPOINT ["/entrypoint.sh"]

