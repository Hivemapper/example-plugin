#!/bin/bash

set -e

# find example-plugin directory and cd into it
PARENT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
cd $PARENT_DIR
rm -fv $PARENT_DIR/cross-compile/ExamplePlugin

# docker build --progress=plain -f $PARENT_DIR/cross-compile/Dockerfile --no-cache -t example-plugin $PARENT_DIR
docker build -f $PARENT_DIR/cross-compile/Dockerfile -t example-plugin $PARENT_DIR




# remove previous example-plugin containers if they exist
docker rm -f example-plugin 2>/dev/null || true
# run container to be able to copy files from it
docker run --name example-plugin example-plugin
docker cp example-plugin:/app/example-plugin/build/src/ExamplePlugin $PARENT_DIR/cross-compile
