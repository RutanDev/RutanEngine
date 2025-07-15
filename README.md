# Welcome to RutanEngine
Hobby 3D-renderer. Ses i rutan 13:00?

# Tested platforms
| OS        | Version   | Compilation using   | Graphics API |
|-----------|-----------|---------------------|--------------|
| Windows   | 10        | Visual Studio 2022  | DirectX 11   |
| Windows   | 11        | Visual Studio 2022  | DirectX 11   |

# How to download
You can download it using Git with the command:
> git clone --recursive https://github.com/RutanEngine/RutanEngine.git

# Build project on Windows
1. cmd in RutanEngine-directory
2. Run: BuildProject/Windows/BuildVS2022.bat
3. Open RutanEngine.sln
4. Go bananas!

# Libraries and 3rd-parties
* [premake](https://github.com/premake/premake-core/) Simple build configuration.
* [spdlog](https://github.com/gabime/spdlog) Very fast logging library.
* [imgui](https://github.com/ocornut/imgui) Debugging GUI.
* [stb](https://github.com/nothings/stb) Loading in images.
* [glfw](https://github.com/glfw/glfw) Window creation and input.
* [glm](https://github.com/icaven/glm) Math library for 3d-graphics.


# Future plan
| OS        | Version   | Compilation using   | Graphics API |
|-----------|-----------|---------------------|--------------|
| Linux     | Mint?     | ...                 | Vulkan       |
| Windows   | 10 / 11   | Visual Studio 2022  | DirectX 12   |

# Build project Linux (NOT SUPPORTED YET)
1. > BuildProject/Linux/BuildGMake.sh
2. > make
3. Go bananas!
