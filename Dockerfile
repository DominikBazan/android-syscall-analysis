#Base image
FROM ubuntu:16.04

#Labels and Credits
LABEL \
   name="docker-android-kernel" \
   author="Aleksanderl Lewandowski <alek.lewandowski2@gmail.com>" \
   maintainer="Dominik Bazan <dominik.f.bazan@gmail.com>" \
   contributor_1="Marcin Nowiński <marcin.nowinski25@gmail.com>" \
   description="Docker image for building Android common 4.14 kernel."

RUN apt-get update && apt-get install -y --no-install-recommends apt-utils

RUN apt-get update && \
  apt-get install -y bc build-essential make python-lunch qt4-default gcc-multilib distcc ccache

RUN apt-get install -y linux-generic

RUN apt-get install -y libelf-dev

#RUN apt-get install -y libelf-devel
