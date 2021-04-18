#!/usr/bin/bash

cd ./build-run/docker-build
docker-compose up --build
# docker rm -f wanderer-x

# cd ../run
# cd ../../build

cd ../../

# 判断文件夹是否存在
outdir=out
if [ ! -d $outdir ]
then
    mkdir $outdir
fi

cp -r ./build-run/run ./out/
cp ./build/docker-build/wanderer ./out/run/

# ./wanderer -t all --server 0.0.0.0:2233 --gate_server 0.0.0.0:2233