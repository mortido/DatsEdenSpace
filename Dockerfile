FROM ubuntu:22.04

# Update packages and install necessary dependencies
RUN apt-get update && apt-get install -y \
    build-essential \
    cmake

#RUN apt-get install -y \
#    libcurl4-openssl-dev \
#    curl

# Set the working directory
WORKDIR /app

# Copy the source code into the container
COPY . .

# Create a build directory
RUN mkdir build

# Build the project with CMake
RUN cmake -Bbuild -H. && \
    cmake --build build -- -j$(nproc)

# Run the executable
CMD ["./build/dats_eden_space"]