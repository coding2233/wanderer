#!/usr/bin/bash

# copy wanderer
cp wanderer ./db
cp wanderer ./common

# run gate


# run db
cd ./db
docker-compose up -d --build
cd ../


# remove wanderer
rm ./common/wanderer
rm ./db/wanderer
rm ./wanderer


