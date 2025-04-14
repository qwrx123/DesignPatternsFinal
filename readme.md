### Compiling Steps

#### 1. Installing GLFW

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

8. Restart your IDE or terminal and build as normal.