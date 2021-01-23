FROM archlinux as base

RUN pacman -Syu --noconfirm curl unzip zip bzip2 libzip fmt spdlog

FROM base as builder

RUN pacman -Syu --noconfirm base-devel cmake ninja git

COPY . /usr/src/

RUN mkdir /usr/src/build; \
    cd /usr/src/build;  \
    cmake .. -DCMAKE_BUILD_TYPE=MinSizeRel -DBUILD_SERVER=ON -DBUILD_GTK=OFF; make; make DESTDIR=/usr/local install

RUN ls /usr/local/lib

FROM base AS runtime

COPY --from=builder /usr/local/bin /usr/bin
COPY --from=builder /usr/local/lib /usr/lib

RUN chmod +x /usr/bin/big-finish-downloaderd
RUN ls /usr/lib
ENTRYPOINT ["big-finish-downloaderd"]