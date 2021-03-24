#!/usr/bin/bash

cd ./docker/docker-build
docker-compose up --build
# docker rm -f wanderer-x

# cd ../run
# cd ../../build

cd ../../


mkdir out
cp -r ./docker/run ./out/
cp ./build/wanderer ./out/run/

# ./wanderer -t all --server 0.0.0.0:2233 --gate_server 0.0.0.0:2233