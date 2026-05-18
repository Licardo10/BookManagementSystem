# 图书管理系统 (Book Management System)

基于 C++ 和 EasyX 图形库开发的图书管理系统，支持图书的查找、修改、借阅和统计功能。

## 🚀 快速运行

双击 **`BookManagementSystem.exe`** 即可运行（无需安装任何环境）。

## 🔧 自行编译

### 前提条件

1. **Visual Studio**（Community 免费版即可）
   - 下载: https://visualstudio.microsoft.com/zh-hans/downloads/
   - 安装时勾选 **「使用 C++ 的桌面开发」**
2. **EasyX 图形库** — 已内置在 `easyx/` 文件夹中，无需额外安装

### 编译方式

#### Visual Studio
1. 打开 Visual Studio → 「创建新项目」→ 选择「空项目」
2. 将 `Book.cpp`、`Graphics.cpp`、`main.cpp`、`Book.h`、`Graphics.h` 添加到项目
3. 配置 EasyX（或直接使用已配置好的项目属性）

## 📁 项目结构

```
BookManagementSystem/
├── BookManagementSystem.exe   ← 可直接运行的程序
├── main.cpp                   ← 主程序入口（界面逻辑）
├── Book.h / Book.cpp          ← 图书数据模型与文件读写
├── Graphics.h / Graphics.cpp  ← 图形界面绘制
├── books.txt                  ← 图书数据文件（UTF-8 编码）
├── easyx/                     ← EasyX 图形库（编译用）
│   ├── include/
│   │   ├── graphics.h
│   │   └── easyx.h
│   └── lib/x64/
│       ├── EasyXa.lib
│       └── EasyXw.lib
├── README.md                  ← 本文件
└── .gitignore
```

## ✨ 功能

- 🔍 **查找图书** — 按书名、出版社查找，支持组合查询
- ✏️ **修改图书** — 按 ISBN/书名修改信息，添加/删除图书
- 📖 **借阅归还** — 按 ISBN 借出/归还图书
- 📊 **信息统计** — 查看所有图书、出版社分布、价格区间统计
