# FROM ubuntu:22.04
FROM --platform=linux/amd64 ubuntu:22.04

# Fast Node Manager
RUN curl -fsSL https://fnm.vercel.app/install | bash

# Install curl and unzip for later
RUN apt-get update
RUN apt-get install -y curl unzip

# Install Node JS
RUN curl -fsSL https://deb.nodesource.com/setup_lts.x | bash - && apt-get install -y nodejs

# Setup rust vars because the rustup script doesn't do it for some reason.
ENV RUSTUP_HOME=/opt/rust CARGO_HOME=/opt/cargo PATH=/opt/cargo/bin:$PATH


RUN curl -fsSL https://deno.land/x/install/install.sh | sh && echo 0 || echo 1 > /tmp/deno_pre.output

# Try to use a prebuilt binary: if it doesn't exist, build from source
RUN if [ $(cat /tmp/deno_pre.output) = "0" ]; \
then echo "Using prebuilt binary"; \
else echo "Building from source"; \
fi

RUN if [ $(cat /tmp/deno_pre.output) != "0" ]; \
then echo "Creating directories"; \
    mkdir /opt; \
    mkdir ${CARGO_HOME}; \
    touch ${CARGO_HOME}/config.toml; \
fi

RUN if [ $(cat /tmp/deno_pre.output) != "0" ]; \
then echo "Installing Rust"; \
    apt-get install -y build-essential; \
    echo '\n\n[registries.crates-io]\nprotocol = "sparse"' >> ${CARGO_HOME}"/config.toml"; \
    curl --proto '=https' --tlsv1.2 -sSf https://sh.rustup.rs | bash -s -- -y; \
fi


RUN if [ $(cat /tmp/deno_pre.output) != "0" ]; \
then echo "installing Deno"; \
    cargo install deno; \
fi

RUN rm /tmp/deno_pre.output || true

# Deno doesn't fix the path, annoyingly enough
ENV PATH="${PATH}:/root/.deno/bin"


# Binary setup done, moving onto building the package


ARG POWER_PRIME=1933n
ARG MOD_PRIME=261557n

# Workdir!
WORKDIR /app/temp
COPY ./build.bash ./build.bash
COPY ./flag.txt ./flag.txt
COPY ./package.json ./package.json
COPY ./tsconfig.json ./tsconfig.json
COPY ./base ./base
COPY ./chall ./chall
COPY ./server ./server
COPY ./solve ./solve

RUN chmod +x ./build.bash
RUN ./build.bash

RUN cp -r ./build/* ../
WORKDIR /app
RUN rm -r temp

EXPOSE 8080
CMD npx ts-node ./server/index.ts
