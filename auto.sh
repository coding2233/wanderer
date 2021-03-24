#!/usr/bin/bash

cd ./docker/build
docker-compose up --build

# cd ../run
# cd ../../build

cd ../../

cp -r ./docker/run ./build/

cp ./build/wanderer ./build/run/

# ./wanderer -t all --server 0.0.0.0:2233 --gate_server 0.0.0.0:2233