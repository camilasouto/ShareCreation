# Use the official GCC image from Docker Hub
FROM gcc:latest

RUN apt-get -qq update
RUN apt-get -qq upgrade
RUN apt-get -qq install cmake

RUN apt-get install -y libboost-all-dev --no-install-recommends
RUN apt-get -qq install build-essential libtcmalloc-minimal4 && \
    ln -s /usr/lib/libtcmalloc_minimal.so.4 /usr/lib/libctcmalloc_minimal.so

# Copy the current directory contents into the container at /app
#COPY . /app

# Set the working directory to /app
#WORKDIR /app

# Compile the C++ source code into an executable named myapp

#WORKDIR /app/cppweb/npu_backend
# create the build folder
#RUN mkdir build
# create Makefile
#RUN cmake
# compile the app
#WORKDIR /app/cppweb/npu_backend/build
#RUN make

# Run the executable
#CMD ["./npu_backend"]