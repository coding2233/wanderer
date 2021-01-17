FROM alpine

LABEL maintain="wanderer"

RUN apk add cmake && apk add clang && apk add git && apk add make \
    && git clone https://github.com/coding2233/wanderer.git /data  \
    && mkdir -p /data/build

WORKDIR /data

RUN cmake --no-warn-unused-cli -DWEBSERVER=1 -DCMAKE_TOOLCHAIN_FILE=/data/cmake/linux_clang.cmake -S /data -B /data/build && cmake --build /data/build

ENTRYPOINT ["/data/docker/docker-entrypoint.sh"]
