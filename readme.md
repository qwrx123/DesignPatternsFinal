# General Dependencies

1. **CMake**: Open source, cross-platform build system for C++.
2. **GLFW**: Open source, cross-platform library for creating windows.
3. **OpenGL**: Open source, cross-platform API for rendering.
4. **clang-tidy**: Open source, cross-platform tool for static code analysis.
5. **clang-format**: Open source, cross-platform code formatter for C++.
6. **Google-test**: Open source, cross-platform testing framwork for C++.
7. **VCPKG**: Open source, cross-platform C++ package manager.

---

### Compiling Steps Windows

#### 1. Installing LLVM

1. Open a terminal.
2. Install LLVM using Winget:
	```bash
	winget install --id LLVM.LLVM
	```
3. Add the LLVM executables to your system path:
	- In Windows, search for **"Edit the system environment variables"**.
	- Open the program.
	- Click **Environment Variables**.
	- Double-click **Path**.
	- Click **New**.
	- Add the path (default: `C:\Program Files\LLVM\bin`).
	- Click **OK** for all windows.
4. Restart your terminal.

#### 2. Installing GLFW

1. Clone the git repository:
	```bash
	git clone https://github.com/glfw/glfw
	```
2. Change directory into the project:
	```bash
	cd glfw
	```
3. Create the build directory:
	```bash
	mkdir build
	```
4. Configure the project:
	```bash
	cmake -DCMAKE_BUILD_TYPE=release -DBUILD_SHARED_LIBS=ON -DCMAKE_GENERATOR_PLATFORM=x64 -B build
	```
5. Build the project:
	```bash
	cmake --build build --config release
	```
6. From an ***Administrator terminal***, install the project:
	```bash
	cmake --install build
	```
7. Add the DLL to the system path:
	- In Windows, search for **"Edit the system environment variables"**.
	- Open the program.
	- Click **Environment Variables**.
	- Double-click **Path**.
	- Click **New**.
	- Add the path (default: `C:\Program Files\GLFW\bin`).
	- Click **OK** for all windows

#### 3. Install VCPKG

1. Navigate to desired VCPKG location:
	```bash
	cd C:\
	```

2. Clone VCPKG repository:
	```bash
	git clone https://github.com/microsoft/vcpkg.git
	```

3. Enter VCPKG directory:
	```bash
	cd vcpkg
	```

4. Run bootstrapper:
	```bash
	.\bootstrap-vcpkg.bat
	```

5. Configure environment variables:
	- In Windows, search for **"Edit the system environment variables"**
	- Open the program
	- Click **Environment Variables**
	- Double-click **Path**
	- Click **New**
	- Add the path (default: `C:\vcpkg`)
	- Click **OK**
	- Click **New** again
	- Add **VCPKG_ROOT** as key
	- Set value to VCPKG path (default: `C:\vcpkg`)

#### 4. Restart Terminal

#### 5. install gtest
```bash
vcpkg install gtest
```

#### 6. Restart your IDE

#### 7. Configure the project
```bash
cmake -B build
```

#### 8. Build the project
```bash
cmake --build build
```

#### 9. Test the project
```bash
ctest --test-dir build --output-on-failure
```

#### 10. From an ***Administrator terminal***, install the project:
```bash
cmake --install build
```

---

### Compiling steps on Linux

#### 1. **Install dependencies**  

- On **Debian/Ubuntu**:
	```bash
	sudo apt install libglfw3 libglfw3-wayland libglfw3-dev clang-tidy clang-format cmake libgtest-dev libgmock-dev
	```

- On **Arch**:
	```bash
	pacman -S glfw clang cmake gtest
	```

- On **Gentoo**:
	```bash
	emerge --ask dev-libs/glfw3 dev-libs/clang-tools dev-util/cmake dev-cpp/gtest
	```

#### 2. **Configure the project**
```bash
cmake -B build
```
Optionally you can add `-DENABLE_RELOCATABLE=TRUE` for easy portability:
```bash
cmake -B build -DENABLE_RELOCATABLE=TRUE
```

#### 3. **Build the project**
```bash
cmake --build build
```

#### 4. Test the project
```bash
ctest --test-dir build --output-on-failure
```

#### 5. Install the project
```bash
sudo cmake --install build
```

---

### Compiling Steps on macOS

#### 1. Install Homebrew
```bash
/bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"
```

#### 2. Install Dependencies
```bash
brew install llvm lld cmake glfw googletest
```

#### 3. Verify Installation
Ensure clang-tidy is in your path:
```bash
clang-tidy --version
```

#### 4. **Configure the project**
```bash
cmake -B build
```

#### 5. **Build the project**
```bash
cmake --build build
```

#### 6. Test the project
```bash
ctest --test-dir build --output-on-failure
```

#### 7. Install the project
```bash
sudo cmake --install build
```

---

### Compiling Steps on Docker

#### 1. **Install docker**

- On **Debian/Ubuntu**:
	https://docs.docker.com/engine/install/debian/

- On **Arch**:
	```bash
	pacman -S docker docker-buildx
	```

- On **Gentoo**:
	```bash
	emerge --ask app-containers/docker app-containers/docker-cli app-containers/docker-buildx
	```
- On **Windows**:
	```bash
	winget install --id=Docker.DockerCLI  -e
	docker buildx install
	```

- On **Mac**
	```bash
	brew install docker docker-buildx
	```

#### 2. **Build the image**
```bash
docker buildx build --no-cache -t daisy .
```

#### 3. **Run the tests**
```bash
docker run --rm daisy
```

---

### Generating documentation with doxygen

#### 1. **Install doxygen**

- On **Debian/Ubuntu**:
	```bash
	apt install doxygen
	```

- On **Arch**:
	```bash
	pacman -S doxygen
	```

- On **Gentoo**:
	```bash
	emerge --ask app-text/doxygen
	```

- On **Windows**:
	```bash
	winget install -e --id DimitriVanHeesch.Doxygen
	```

- On **Mac**
	```bash
	brew install doxygen
	```

#### 2. **Build as normal**