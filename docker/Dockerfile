FROM alpine

LABEL maintain="wanderer"

RUN mkdir -p /data/build \
    && apk add cmake
WORKDIR /data
COPY ../ /data

RUN cmake -S /data -B /data/build && cmake --build /data/build

ENTRYPOINT [/data/docker/ENTRYPOINT.sh]
