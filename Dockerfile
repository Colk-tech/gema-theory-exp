# Use an official Ubuntu runtime as a parent image
FROM ubuntu:18.04

# Set the default shell to bash
SHELL ["/bin/bash", "-c"]

# Set the working directory
WORKDIR /work/game-theory

# Install necessary tools
RUN apt-get update &&  \
    apt-get install -y --no-install-recommends \
      gcc=4:7.4.0-1ubuntu2.3 \
      make=4.1-9.1ubuntu1 \
      cmake && \
    apt-get install -y --reinstall build-essential && \
    rm -rf /var/lib/apt/lists/*

# Set the entrypoint
ENTRYPOINT ["top", "-b"]
