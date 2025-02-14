# File_Sync_Tool
## 项目简介

`File Sync Tool` 是一个跨平台的文件同步工具，使用 C++ 和 Qt 实现。该工具允许用户将源文件夹中的文件同步到目标文件夹，支持简单的文件复制操作，并能够在 Windows、Linux 和 macOS 等平台上运行。

## 功能

- 支持从源文件夹到目标文件夹的文件同步。
- 通过比较文件的大小和修改时间来判断文件是否需要同步。
- 提供简单的图形界面，用户可以通过界面选择源文件夹和目标文件夹并触发同步操作。
- 支持 Windows、Linux 和 macOS 跨平台运行。

## 安装与使用

### 1. 克隆仓库

首先，克隆项目到本地：

```bash
git clone https://github.com/ice789ice/File_Sync_Tool.git
cd File_Sync_Tool

###


该项目使用 Qt 和 C++17，你需要安装 Qt6 和支持 C++17 的编译器。
在 Linux 上，可以通过以下命令安装依赖：
sudo apt-get install qt6-base-dev qt6-tools-dev

3. 构建项目
在项目根目录下，使用 CMake 来构建项目：

bash
复制
编辑
mkdir build
cd build
cmake ..
make
4. 运行程序
在构建成功后，运行同步工具：

bash
复制
编辑
./FileSync
5. 使用说明
启动程序后，输入源文件夹和目标文件夹路径。
点击 同步 按钮，程序会自动将源文件夹中的文件同步到目标文件夹。
同步过程中，程序会显示日志和同步进度。
项目结构
css
复制
编辑
File_Sync_Tool/
├── CMakeLists.txt
├── main.cpp
├── mainwindow.cpp
├── mainwindow.h
├── mainwindow.ui
├── FileSyncWorker.cpp
├── FileSyncWorker.h
└── resources/
main.cpp：程序入口。
mainwindow.cpp：主窗口的实现代码。
mainwindow.ui：Qt 设计的界面文件。
FileSyncWorker.cpp：文件同步的核心功能实现。
resources/：存放程序资源文件，如翻译文件等。
贡献
欢迎贡献代码！如果你有任何问题或建议，可以提交 Issue 或 Pull Request。

许可
该项目采用 MIT 许可证，详情请参阅 LICENSE 文件。
