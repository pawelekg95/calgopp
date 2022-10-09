FROM ubuntu:20.04

ARG DEBIAN_FRONTEND=noninteractive

ARG CMAKE_VER=3.23.2
ARG CMAKE_URL="https://github.com/Kitware/CMake/releases/download/v${CMAKE_VER}/cmake-${CMAKE_VER}-linux-aarch64.tar.gz"
ARG HADOLINT_URL="https://github.com/hadolint/hadolint/releases/download/v2.10.0/hadolint-Linux-arm64"

WORKDIR /root

# Install base packages
RUN apt-get update && \
    apt-get install -y --no-install-recommends build-essential=12.8ubuntu1.1 g++=4:9.3.0-1ubuntu2 llvm=1:10.0-50~exp1 \
    python3=3.8.2-0ubuntu2 python3-pip=20.0.2-5ubuntu1.6 shellcheck=0.7.0-2build2 git=1:2.25.1-1ubuntu3.5 make=4.2.1-1.2 \
    clang-format=1:10.0-50~exp1 clang-tidy=1:10.0-50~exp1 wget=1.20.3-1ubuntu2 xz-utils=5.2.4-1ubuntu1.1 valgrind=1:3.15.0-1ubuntu9.1 \
    lcov=1.14-2 libgpgme-dev=1.13.1-7ubuntu2 ca-certificates=20211016~20.04.1 curl=7.68.0-1ubuntu2.13 gnupg=2.2.19-3ubuntu2.2 \
    lsb-release=11.1.0ubuntu2 dpkg=1.19.7ubuntu3.2 diffutils=1:3.7-3 && \
    apt-get autoremove -y && \
    apt-get clean && \
    rm -rf /var/lib/apt/lists/*

RUN curl -o /usr/bin/hadolint -L "${HADOLINT_URL}" && \
    chmod 775 /usr/bin/hadolint

# Install custom CMake version
RUN curl -o "cmake_v${CMAKE_VER}" -L "${CMAKE_URL}" && \
    mkdir -p "/opt/cmake/${CMAKE_VER}" && \
    tar -xf "$(basename cmake_v${CMAKE_VER})" -C "/opt/cmake/${CMAKE_VER}" --strip-components=1 && \
    rm "$(basename cmake_v${CMAKE_VER})" && \
    ln -s "/opt/cmake/${CMAKE_VER}/bin/*" /usr/bin/ && \
    apt-get autoremove -y && \
    apt-get clean && \
    rm -rf /var/lib/apt/lists/*

# Install base python packages
RUN pip3 --no-cache-dir install requests==2.28.1 telnetlib3==1.0.4 pyserial==3.5 pylint==2.15.3 xmlrunner==1.7.7 \
    pandas==1.5.0 scipy==1.9.1 numpy==1.23.3 pdoc3==0.10.0 scp==0.14.4 paramiko==2.11.0 html2text==2020.1.16
