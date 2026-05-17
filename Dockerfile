FROM ubuntu:22.04

RUN apt-get update && apt-get install -y \
    g++ cmake git libssl-dev zlib1g-dev libcurl4-openssl-dev \
    && rm -rf /var/lib/apt/lists/*

RUN git clone https://github.com/jupp0r/prometheus-cpp.git /tmp/prom && \
    cd /tmp/prom && git submodule update --init && \
    mkdir build && cd build && \
    cmake -DCMAKE_BUILD_TYPE=Release \
          -DBUILD_SHARED_LIBS=OFF \
          -DENABLE_TESTING=OFF .. && \
    cmake --build . --parallel 4 && \
    cmake --install . && \
    rm -rf /tmp/prom

WORKDIR /app
COPY source/ .

RUN g++ -Wall -O2 -o matrix7 main.cpp \
    -lprometheus-cpp-pull \
    -lprometheus-cpp-core \
    -lprometheus-cpp-push \
    -lz -lpthread

EXPOSE 8080
CMD ["./matrix7", "--server"]
