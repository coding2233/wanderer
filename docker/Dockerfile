FROM alpine

LABEL maintain="wanderer"

RUN mkdir -p /data/build \
    && apk add cmake && apk add clang
WORKDIR /data
COPY ../ /data

RUN cmake -S /data -B /data/build && cmake --build /data/build

ENTRYPOINT ["/data/docker/docker-entrypoint.sh"]
