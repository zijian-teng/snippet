# zsnippet 代码片段库

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
cd cpp/time_and_chrono
clang-tidy *.cpp -p ../../build --quiet
```