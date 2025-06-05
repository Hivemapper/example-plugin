#!/bin/bash


node /opt/odc-api/odc-api-bee.js > /data/recording/odc-api-test.log 2>&1 &

# node /opt/odc-api/odc-api-bee.js &

cd /data/recording

exec /bin/bash