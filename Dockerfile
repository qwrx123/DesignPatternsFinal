 FROM ubuntu:latest

 RUN apt-get update && \
 	apt-get upgrade -y && \
	apt-get install -y --no-install-recommends \
	build-essential \
	cmake \
	libglfw3 \
	libglfw3-dev \
	libgtest-dev \
	libgmock-dev \
	libfreetype6 \
	libfreetype6-dev \
	libglew-dev \
	xorg \
	xvfb \
	xfonts-100dpi \
	xfonts-75dpi \
	xfonts-scalable \
	tini

WORKDIR /app

COPY . .

RUN mkdir build && \
	cmake -DCMAKE_BUILD_TYPE=Debug -DBUILD_SHARED_LIBS=ON -DBUILD_TESTING=ON -B build && \
	cmake --build build --config Debug --parallel $(nproc)


ENTRYPOINT ["/usr/bin/tini", "--"]

CMD ["xvfb-run", "ctest", "--test-dir", "build", "--output-on-failure"]
