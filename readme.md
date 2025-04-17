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
    cmake -DCMAKE_BUILD_TYPE=release -DBUILD_SHARED_LIBS=true -DCMAKE_GENERATOR_PLATFORM=x64 -B build
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

#### 3. Restart your IDE

#### 4. Configure the project
    ```bash
    cmake -B build
    ```

#### 5. Build the project
    ```bash
    cmake --build build
    ```

---

### Compiling steps on Linux

#### 1. **Install dependencies**  

- On **Debian/Ubuntu**:
    ```bash
    sudo apt install libglfw3 libglfw3-wayland libglfw3-dev clang-tidy clang-format cmake
    ```

- On **Arch**:
    ```bash
    pacman -S glfw clang cmake
    ```

- On **Gentoo**:
    ```bash
    emerge --ask dev-libs/glfw3 dev-libs/clang-tools dev-util/cmake
    ```

#### 2. **Configure the project**
    ```bash
    cmake -B build
    ```

#### 3. **Build the project**
    ```bash
    cmake --build build
    ```

---

### Compiling Steps on macOS

#### 1. Install Homebrew
```bash
/bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"
```

#### 2. Install Dependencies
```bash
brew install llvm lld cmake glfw
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