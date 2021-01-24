FROM debian:unstable-slim as base

RUN apt-get -y update; \
    apt-get -y upgrade; \
    apt-get -y install curl unzip zip bzip2 libzip-dev libfmt-dev libspdlog-dev;

FROM base as builder

RUN apt-get -y install gcc-10 g++-10 cmake ninja-build git pkg-config libglib2.0-dev libsecret-1-dev
ENV CXX=g++-10
ENV CX=gcc-10

COPY . /usr/src/

RUN mkdir /usr/src/build;
WORKDIR /usr/src/build
RUN cmake .. -DCMAKE_BUILD_TYPE=MinSizeRel -DBUILD_SERVER=ON -DBUILD_GTK=OFF; make; make DESTDIR=/usr/local install

RUN ls /usr/local/lib

FROM base AS runtime

COPY --from=builder /usr/local/bin /usr/bin
COPY --from=builder /usr/local/lib /usr/lib

RUN chmod +x /usr/bin/big-finish-downloaderd
RUN ls /usr/lib
ENTRYPOINT ["big-finish-downloaderd"]
EXPOSE 8000