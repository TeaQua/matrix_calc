FROM ubuntu:22.04 AS builder

ENV DEBIAN_FRONTEND=noninteractive

RUN apt-get update \
    && apt-get install --no-install-recommends -y cmake g++ make ca-certificates \
    && rm -rf /var/lib/apt/lists/*

WORKDIR /app
COPY . .

RUN cmake -S . -B build -DCMAKE_BUILD_TYPE=Release -DBUILD_TESTING=OFF \
    && cmake --build build --parallel 2

FROM ubuntu:22.04

WORKDIR /app
COPY --from=builder /app/build/matrix_calculator /app/matrix_calculator

CMD ["/app/matrix_calculator"]
