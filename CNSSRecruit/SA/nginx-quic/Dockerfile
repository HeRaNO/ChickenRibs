FROM alpine
MAINTAINER HeRaNO <https://github.com/HeRaNO>

RUN set -x \
# create nginx user/group first, to be consistent throughout docker variants
    && addgroup -g 101 -S nginx \
    && adduser -S -D -H -u 101 -h /var/cache/nginx -s /sbin/nologin -G nginx -g nginx nginx

RUN apk update
RUN apk upgrade
RUN apk add --no-cache --virtual .build-deps \
    go \
    gcc \
    g++ \
    git \
    bash \
    make \
    cmake \
    ninja \
    gd-dev \
    libc-dev \
    perl-dev \
    zlib-dev \
    findutils \
    geoip-dev \
    mercurial \
    alpine-sdk \
    libedit-dev \
    libxslt-dev \
    linux-headers \
    libunwind-dev

RUN apk add openssl pcre-dev

WORKDIR /tmp
RUN git clone https://boringssl.googlesource.com/boringssl
RUN hg clone -b quic https://hg.nginx.org/nginx-quic
WORKDIR /tmp/boringssl/build

RUN cmake -GNinja ..
RUN ninja

WORKDIR /tmp/nginx-quic
RUN ./auto/configure \
    --prefix=/etc/nginx \
    --sbin-path=/usr/sbin/nginx \
    --modules-path=/usr/lib/nginx/modules \
    --conf-path=/etc/nginx/nginx.conf \
    --error-log-path=/var/log/nginx/error.log \
    --http-log-path=/var/log/nginx/access.log \
    --pid-path=/var/run/nginx.pid \
    --lock-path=/var/run/nginx.lock  \
    --with-threads \
    --with-http_v2_module \
    --with-http_v3_module \
    --with-cc-opt="-I../boringssl/include"  \
    --with-ld-opt="-L../boringssl/build/ssl -L../boringssl/build/crypto"

RUN make
RUN make install

RUN apk add --no-cache tzdata
RUN apk add --no-cache curl ca-certificates

WORKDIR /etc/nginx/certs
RUN openssl genrsa -des3 -passout pass:password -out server.pass.key 2048
RUN openssl rsa -passin pass:password -in server.pass.key -out server.key
RUN rm -f server.pass.key
RUN openssl req -new -key server.key -out server.csr -subj "/CN=127.0.0.1"
RUN openssl x509 -req -days 365 -in server.csr -signkey server.key -out server.crt 

RUN ln -sf /dev/stdout /var/log/nginx/access.log
RUN ln -sf /dev/stderr /var/log/nginx/error.log
RUN rm -rf /tmp/*
RUN apk del .build-deps

RUN mkdir /docker-entrypoint.d

COPY nginx.conf /etc/nginx/nginx.conf
COPY docker-entrypoint.sh /
COPY 10-listen-on-ipv6-by-default.sh /docker-entrypoint.d
COPY 20-envsubst-on-templates.sh /docker-entrypoint.d
RUN chmod +x /docker-entrypoint.sh

ENTRYPOINT ["/docker-entrypoint.sh"]

EXPOSE 80
EXPOSE 8443

STOPSIGNAL SIGTERM

CMD ["nginx", "-g", "daemon off;"]
