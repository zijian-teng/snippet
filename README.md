# zsnippet 代码片段库

该项目包含以下示例：

- 使用 clang-tidy 和 clang-format 进行代码检查及格式化
- 如何使用 github workflow，自动进行代码检查
- 如何配置 vscode，提高工作效率
- 通过 .gitignore 忽略文件
- 现代 CMake 的配置

## 开发环境

VSCode，必要插件：

- clangd
- CodeLLDB
- CMake
- CMake Tools

## cpp

- 使用 clang/lldb 编译、调试，采用 C++17 标准，开启所有警告
- 内置 launch.json 和 tasks.json 配置，单文件可以直接 F5 调用 lldb 调试
- 使用 clang-format 进行代码格式化，基于 Google 格式规范
- 使用 clang-tidy 规则检查，包括 C++ 核心指南、Google 命名规范等

## cheetsheet

```bash
# 创建 build 目录，并执行 cmake 命令，同时生成 compile_commands.json 文件
cmake -B build -DCMAKE_EXPORT_COMPILE_COMMANDS=ON
# 对 cpp 目录下所有 .cpp 和 .h 文件进行 clang-tidy 检查
find cpp -name '*.cpp' -or -name '*.h' | xargs clang-tidy -p build --quiet
```
