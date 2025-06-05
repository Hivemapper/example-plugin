#!/bin/bash

# Usage check
if [ -z "$1" ]; then
  echo "Usage: $0 <collection_archive_name.tar.gz>"
  exit 1
fi

COLLECTION_ARCHIVE="$1"

# Set up binfmt support
docker run --rm --privileged tonistiigi/binfmt --install all

# Create and use buildx builder
docker buildx create --use --name mybuilder || docker buildx use mybuilder
docker buildx inspect --bootstrap

# Build with the provided collection archive name
docker buildx build \
  --platform linux/arm64 \
  -t load-collection \
  --build-arg COLLECTION_ARCHIVE="$COLLECTION_ARCHIVE" \
  --load .

# Run the built image
docker run --platform linux/arm64 -it load-collection