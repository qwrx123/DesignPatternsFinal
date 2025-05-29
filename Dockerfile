FROM ghcr.io/bs-cs410/daisy-docker-image:latest

WORKDIR /app

COPY . .

RUN mkdir build && \
	cmake -DCMAKE_BUILD_TYPE=Debug -DBUILD_SHARED_LIBS=ON -DBUILD_TESTING=ON -DBUILD_DOCS=OFF \
	-DCMAKE_CXX_COMPILER=/usr/bin/clang++ -B build && \
	cmake --build build --config Debug --parallel $(nproc) && \
	cmake -DCMAKE_BUILD_TYPE=Debug -DBUILD_SHARED_LIBS=ON -DBUILD_TESTING=ON -DBUILD_DOCS=ON \
	-DCMAKE_CXX_COMPILER=/usr/bin/clang++ -B build && \
	cmake --build build --config Debug --parallel $(nproc) --target docs 


ENTRYPOINT ["/usr/bin/tini", "--"]

CMD ["xvfb-run", "ctest", "--test-dir", "build", "--output-on-failure"]
