#!/bin/bash

protoc --proto_path=../../protocol/proto/ --cpp_out=../../protocol --python_out=../../client-test wanderer.proto