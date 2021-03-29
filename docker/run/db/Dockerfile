FROM ubuntu:20.04

LABEL maintain="wanderer"

RUN apt-get update && apt-get upgrade -y 
RUN apt-get install -y mongodb
# RUN mkdir /config
RUN mkdir /log

COPY entrypoint.sh /
COPY wanderer /
COPY conf/database.yml /

RUN chmod +x /entrypoint.sh chmod +x /wanderer

ENTRYPOINT [ "/entrypoint.sh" ]
