#!/bin/bash
set -e

if [ "$TEST_MODE" == "1" ]; then
  echo "TEST_MODE is enabled; setting DASHCAM_HOST=127.0.0.1 and DASHCAM_PORT=9000"
  export DASHCAM_HOST="127.0.0.1"
  export DASHCAM_PORT="9000"
  python3 /usr/src/app/test_server.py &
  
  # Wait until the test server port is open
  echo "Waiting for the test server to start..."
  while ! nc -z 127.0.0.1 9000; do
    sleep 0.5
  done
fi

echo "Starting main C++ application..."
exec /usr/src/app/build/src/HerePlugin
