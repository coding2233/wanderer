FROM ubuntu:20.04

LABEL maintain="wanderer"

# COPY sources.list /etc/apt/sources.list

RUN apt-get update && apt-get upgrade -y 
RUN apt-get install -y clang cmake make

COPY entrypoint.sh /entrypoint.sh

RUN chmod +x /entrypoint.sh

RUN mkdir /src

# ENTRYPOINT ["/entrypoint.sh"]