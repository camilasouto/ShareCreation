# Use the official GCC image from Docker Hub
FROM gcc:latest

RUN apt-get -qq update
RUN apt-get -qq upgrade
RUN apt-get -qq install cmake

RUN apt-get install -y libboost-all-dev libgtest-dev --no-install-recommends
RUN apt-get -qq install build-essential libtcmalloc-minimal4 && \
    ln -s /usr/lib/libtcmalloc_minimal.so.4 /usr/lib/libctcmalloc_minimal.so

# Build GTest library
RUN cd /usr/src/googletest && \
    cmake . && \
    cmake --build . --target install

# Build application
COPY . /usr/src/ShareCreation
WORKDIR /usr/src/ShareCreation/npu_backend
RUN mkdir -p build
WORKDIR /usr/src/ShareCreation/npu_backend/build
RUN cmake .. && \
    make

# Build test application
COPY . /usr/src/ShareCreation
WORKDIR /usr/src/ShareCreation/tests
RUN mkdir -p build
WORKDIR /usr/src/ShareCreation/tests/build
RUN cmake .. && \
    make

# Run the executable
#CMD ["./npu_backend"]


