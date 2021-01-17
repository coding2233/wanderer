FROM alpine

LABEL maintain="wanderer"

RUN mkdir -p /data/files && chmod 777 /data/files
WORKDIR /data
COPY build/wanderer /data
COPY docker-entrypoint.sh /data
RUN chmod + /data/docker-entrypoint.sh

ENTRYPOINT ["/data/docker-entrypoint.sh"]
