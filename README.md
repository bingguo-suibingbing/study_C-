# C++ 学习工程

面向**软件开发**的系统化 C++ 学习笔记：62 个专题、60 个源文件、约 3 万行带注释的代码。
每个专题都是**可运行**的示例，不是纸上的伪代码。

- 标准：**C++20**
- 编译器：MSVC v145（也兼容 GCC / Clang）
- 工具链：Visual Studio 工程 + CMake + 一键构建脚本
- 全程 **`/W4` 零告警**（`/Wall` 级别之外的实用上限）

---

## 一、怎么用这个工程

### 方式 1：Visual Studio（推荐，你在用的）

直接打开 `Project2.slnx`，按 **F5** 运行。程序会打印专题列表，输入编号运行对应专题：

```
> 3          运行第 3 节
> 3,7,12     运行多节
> all        全部运行（输出约 4300 行，建议重定向到文件）
> list       重新打印列表
> q          退出
```

也可以在命令行直接指定（不进入交互菜单）：

```powershell
.\x64\Debug\Project2.exe 3        # 只看第 3 节
.\x64\Debug\Project2.exe all      # 全部跑一遍
```

### 方式 2：一键脚本（不依赖 VS，也不需要 CMake）

```powershell
.\tools\build.ps1           # 编译，产物在 build\cpp_learning.exe
.\tools\build.ps1 -Run      # 编译并运行
.\tools\build.ps1 -Run -Args all    # 编译并全部运行
.\tools\build.ps1 -Warn     # 只做语法检查，快速看告警（不生成 exe）
```

### 方式 3：CMake（跨平台 / 给 CI 用）

```bash
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build --config Release -j
./build/cpp_learning
```

---

## 二、学习路线图

按顺序读是最省力的。**加粗的是必须掌握的**，其余是按需查。

### 阶段 1：打好地基（建议 1-2 周）

| # | 专题 | 文件 | 核心收获 |
|---|------|------|---------|
| 1 | 环境与工具 | `src/00_env/01_setup.cpp` | 编译四阶段、链接错误排查、`/W4`+`/utf-8`、调试器技巧 |
| 2 | 数据类型与转换 | `src/01_basic/01_types.cpp` | **有符号/无符号坑**、浮点比较、`{}` 禁止窄化、四种 cast |
| 3 | 运算符与求值顺序 | `src/01_basic/02_operators.cpp` | **求值顺序（UB 高发区）**、位运算技巧、短路求值 |
| 4 | 控制流 | `src/01_basic/03_control_flow.cpp` | 卫语句、switch 的坑、迭代器失效 |
| 5 | 函数 | `src/01_basic/04_functions.cpp` | **参数传递决策表**、重载决议、默认参数设计 |
| 6 | 作用域与生命周期 | `src/01_basic/05_scope.cpp` | 三种悬空、`reserve`、函数内 `static` |
| 7 | 枚举与联合体 | `src/01_basic/06_enum_union.cpp` | **`enum class`**、位标志、`std::variant` 替代 union |

### 阶段 2：理解内存（1-2 周）

| # | 专题 | 文件 | 核心收获 |
|---|------|------|---------|
| 8 | 指针基础 | `src/02_pointer/01_pointer_basics.cpp` | 指针三层、步长、野指针/悬空指针 |
| 9 | 数组与指针 | `src/02_pointer/02_arrays_ptr.cpp` | **退化规则**、多维数组类型、`std::span` |
| 10 | const 与指针 | `src/02_pointer/03_const_ptr.cpp` | **四种组合的读法**、底层/顶层 const |
| 11 | 指针进阶 | `src/02_pointer/04_advanced.cpp` | 函数指针、`std::function`、`void*`、`int**` |
| 12 | 动态内存与布局 | `src/02_pointer/05_memory.cpp` | **五个内存区域**、new/delete vs malloc/free、placement new |

### 阶段 3：面向对象（2-3 周，**最重要**）

| # | 专题 | 文件 | 核心收获 |
|---|------|------|---------|
| 13 | 类与封装 | `src/03_class/01_encapsulation.cpp` | **不变量**、访问控制、接口设计 |
| 14 | 构造与析构 | `src/03_class/02_ctor_dtor.cpp` | **初始化列表**、初始化顺序、`explicit`、`= delete` |
| 15 | 拷贝与移动 | `src/03_class/03_copy_move.cpp` | **三/五法则**、copy-and-swap、深拷贝 vs 浅拷贝 |
| 16 | 运算符重载 | `src/03_class/04_operator_overload.cpp` | `+=` 实现 `+`、`<=>`、`operator[]` 成对提供 |
| 17 | **RAII** | `src/03_class/05_raii.cpp` | **C++ 最核心的资源管理思想**、ScopeGuard、事务守卫 |
| 18 | static 与友元 | `src/03_class/06_friend_static.cpp` | `inline static`、工厂方法、Meyers 单例 |
| 19 | **零法则** | `src/03_class/07_rule_of_zero.cpp` | **对象设计决策流程**、值语义 vs 引用语义、Pimpl |

### 阶段 4：继承与多态（1-2 周）

| # | 专题 | 文件 | 核心收获 |
|---|------|------|---------|
| 20 | 继承基础 | `src/04_inherit/01_inherit_basics.cpp` | is-a、**对象切片**、名字隐藏、**优先组合** |
| 21 | 虚函数 | `src/04_inherit/02_virtual.cpp` | **vtable 机制**、**virtual 析构必须**、`override`/`final` |
| 22 | 抽象类与接口 | `src/04_inherit/03_abstract.cpp` | **接口隔离**、依赖注入、可测试性设计 |
| 23 | 多重继承 | `src/04_inherit/04_multiple.cpp` | 菱形继承、虚继承、**只用于纯接口** |
| 24 | 多态设计原则 | `src/04_inherit/05_design.cpp` | **Liskov 替换原则**、访问者模式、十条检查清单 |

### 阶段 5：模板与泛型（2 周）

| # | 专题 | 文件 | 核心收获 |
|---|------|------|---------|
| 25 | 函数模板 | `src/05_template/01_function_template.cpp` | 类型推导、非类型参数、**定义必须放头文件** |
| 26 | 类模板 | `src/05_template/02_class_template.cpp` | 手写固定容量栈、嵌套类型别名、`emplace` |
| 27 | 模板特化 | `src/05_template/03_specialization.cpp` | 全特化/偏特化、函数模板用重载代替 |
| 28 | 可变参数模板 | `src/05_template/04_variadic.cpp` | **折叠表达式**、完美转发、`std::tuple` |
| 29 | 模板元编程 | `src/05_template/05_metaprogramming.cpp` | **type_traits**、**CRTP**、`constexpr` 取代递归模板 |
| 30 | **concepts** | `src/05_template/06_concepts.cpp` | **C++20 最重要的生产力提升**、取代 `enable_if` |

### 阶段 6：标准库（2 周）

| # | 专题 | 文件 | 核心收获 |
|---|------|------|---------|
| 31 | 容器选择 | `src/06_stl/01_containers.cpp` | **vector/list 实测对比**、map vs unordered_map |
| 32 | 迭代器 | `src/06_stl/02_iterators.cpp` | 五种迭代器、**失效规则速查表**、C++20 ranges |
| 33 | 算法库 | `src/06_stl/03_algorithms.cpp` | **不要手写循环**、erase-remove、二分族 |
| 34 | lambda | `src/06_stl/04_lambda.cpp` | 六种捕获、**悬空捕获四种场景**、IIFE |
| 35 | string | `src/06_stl/05_string.cpp` | SSO、**`string_view` 及其陷阱**、`from_chars` |
| 36 | 流式 IO | `src/06_stl/06_io.cpp` | **`>>` 与 `getline` 混用的坑**、stringstream 解析 |

### 阶段 7：现代 C++ 工程实践（2 周，**最有实战价值**）

| # | 专题 | 文件 | 核心收获 |
|---|------|------|---------|
| 37 | 移动语义 | `src/07_modern/01_move_semantics.cpp` | **RVO**、`std::move` 真相、**移动构造必须 noexcept** |
| 38 | 智能指针 | `src/07_modern/02_smart_pointer.cpp` | **所有权模型**、循环引用、`enable_shared_from_this` |
| 39 | const 正确性 | `src/07_modern/03_const_correctness.cpp` | 三层 const、`mutable` 的正当用途 |
| 40 | 异常安全 | `src/07_modern/04_exception_safety.cpp` | **四个保证级别**、析构绝不抛异常、`noexcept` |
| 41 | 错误处理策略 | `src/07_modern/05_error_handling.cpp` | **异常 vs 错误码 vs `expected` 决策表** |
| 42 | optional/variant/any | `src/07_modern/06_optional_variant.cpp` | `visit` + `Overloaded` 惯用法 |
| 43 | 工程构建 | `src/07_modern/07_build_cmake.cpp` | 编译四阶段、CMake 现代写法、依赖管理 |
| 44 | 调试技巧 | `src/07_modern/08_debug_tips.cpp` | **UB 清单**、内存特征值、ASan、五步调试法 |

### 阶段 8：数据结构（2-3 周，**动手写一遍**）

| # | 专题 | 文件 | 核心收获 |
|---|------|------|---------|
| 45 | 复杂度分析 | `src/08_ds/01_complexity.cpp` | **缓存友好性实测**、摊还分析、优化流程 |
| 46 | 动态数组 | `src/08_ds/02_dynamic_array.cpp` | 手写 `vector`、placement new、扩容策略 |
| 47 | 链表 | `src/08_ds/03_linked_list.cpp` | 反转、**快慢指针**、哨兵节点、双向链表 |
| 48 | 栈与队列 | `src/08_ds/04_stack_queue.cpp` | **循环队列**、两栈实现队列、单调栈 |
| 49 | 哈希表 | `src/08_ds/05_hash_table.cpp` | 拉链法 vs 开放寻址、**墓碑标记**、负载因子 |
| 50 | 二叉搜索树 | `src/08_ds/06_binary_tree.cpp` | 四种遍历、删除三情况、**不平衡问题** |
| 51 | 二叉堆 | `src/08_ds/07_heap.cpp` | 上浮/下沉、**O(n) 建堆**、top-K、双堆求中位数 |

### 阶段 9：算法（持续）

| # | 专题 | 文件 | 核心收获 |
|---|------|------|---------|
| 52 | 排序 | `src/09_algo/01_sorting.cpp` | 五种手写排序、**稳定性**、快排优化、选择指南 |
| 53 | 二分查找 | `src/09_algo/02_binary_search.cpp` | **两个模板 + 四个变体**、二分答案 |
| 54 | 双指针 | `src/09_algo/03_two_pointers.cpp` | 四种形态、单调栈、`int**` 的正确性论证 |
| 55 | 滑动窗口 | `src/09_algo/04_sliding_window.cpp` | 最长/最短模板、**元素必须非负**、单调队列 |
| 56 | 递归与回溯 | `src/09_algo/05_recursion_backtracking.cpp` | **回溯框架**、剪枝、N 皇后、从回溯到 DP |
| 57 | 动态规划 | `src/09_algo/06_dynamic_programming.cpp` | **六步法**、背包的倒序/正序、**暴力对拍** |
| 58 | 图论基础 | `src/09_algo/07_graph.cpp` | BFS/DFS/拓扑排序/Dijkstra/Bellman-Ford |
| 59 | 并查集 | `src/09_algo/08_union_find.cpp` | **路径压缩 + 按秩合并**、Kruskal 最小生成树 |

---

## 三、工程结构

```
基础学习/
├── Project2.slnx              Visual Studio 解决方案（直接打开这个）
├── Project2.vcxproj           VS 工程（已包含全部 60 个源文件）
├── CMakeLists.txt             跨平台构建脚本
├── README.md                  本文件
├── src/
│   ├── main.cpp               程序入口：只做菜单分发
│   ├── course.h               全部专题的声明 + 课程注册表
│   ├── common/lesson.h        公共工具：标题/小节/提示/目录
│   ├── 00_env/                环境与工具
│   ├── 01_basic/              基础语法（6 节）
│   ├── 02_pointer/            指针与内存（5 节）
│   ├── 03_class/              类与对象（7 节）
│   ├── 04_inherit/            继承与多态（5 节）
│   ├── 05_template/           模板与泛型（6 节）
│   ├── 06_stl/                标准库（6 节）
│   ├── 07_modern/             现代 C++ 工程实践（8 节）
│   ├── 08_ds/                 数据结构实现（7 节）
│   └── 09_algo/               算法专题（8 节）
├── tools/build.ps1            一键编译脚本（不依赖 VS/CMake）
└── build/                     构建产物（已加入 .gitignore）
```

### 设计说明（这些做法本身就值得学）

1. **一个专题一个文件**：改一处只重编一个文件；复习时直接打开对应文件。
2. **注册表模式**：`course.h` 里一张 `constexpr` 表把「菜单名 → 函数指针」关联起来，
   加新课只需两处改动，漏了会**编译报错**而不是静默失效。
3. **自动目录**：`lesson::chapter()` 在运行时累积目录，永远不会与代码不一致。
4. **零告警**：所有代码在 `/W4` 下无告警。需要演示"坏味道"的地方用
   **局部 `#pragma warning` + 注释说明原因**，而不是关闭全局告警。

---

## 四、可复用的调试/编码辅助

| 工具 | 位置 | 用途 |
|------|------|------|
| `LOG_VAR(x)` | `src/common/lesson.h` | 打印"变量名 = 值 + 文件:行号"，比 `printf` 安全 |
| `lesson::show(expr, value)` | 同上 | 打印"表达式 = 结果"的对照 |
| `lesson::note(...)` | 同上 | 打印要点（以 `>>` 开头，方便扫读） |
| `Timer` | 多个专题文件 | 简单的耗时测量（`std::chrono` 封装） |
| `BigBuffer` | `src/07_modern/01_move_semantics.cpp` | 演示拷贝/移动次数的可观测类型 |
| `ScopeGuard` | `src/03_class/05_raii.cpp` | 任意"退出时执行"的清理动作 |

---

## 五、构建过程中踩到的坑（也记录在这里）

这些是配置这个工程时实际遇到的问题，很有代表性：

1. **路径含中文 + `cl.exe` 响应文件编码**
   `cl.exe` 读取响应文件时把无 BOM 的 UTF-8 当作系统 ANSI 解码，
   导致中文路径变成乱码 → `C1083 找不到源文件`。
   **解决**：响应文件必须写为 **UTF-8 带 BOM**。
   注意 PowerShell 5.1 的 `Set-Content -Encoding utf8BOM` 会退化成 ASCII，
   要用 `[System.IO.File]::WriteAllLines(..., UTF8Encoding($true))`。

2. **PowerShell 5.1 会把无 BOM 的 UTF-8 `.ps1` 当 GBK 解码**
   中文注释被拆成乱码后吞掉了引号 → 脚本语法错误。
   **解决**：`.ps1` 文件必须写为 **UTF-8 带 BOM**。

3. **C++ 字符串字面量里不能直接嵌 ASCII 双引号**
   写 `lesson::note("这就是"迭代器失效"的含义")` 会编译失败。
   本项目统一改用中文引号 `「」`，既避免转义又更适合中文阅读。

---

## 六、几个"最值得先掌握"的点

如果时间有限，优先吃透这十条（都是真实项目里的高频问题）：

1. **RAII** —— 所有资源管理的基础（`03_class/05_raii.cpp`）
2. **零法则** —— 决定类要不要写特殊成员函数（`03_class/07_rule_of_zero.cpp`）
3. **移动语义 + `noexcept`** —— 性能静默退化的头号原因（`07_modern/01`）
4. **所有权模型（智能指针）** —— 让"谁负责释放"由类型表达（`07_modern/02`）
5. **`/W4` 零告警** —— 免费的静态分析（`00_env/01`）
6. **UB 清单** —— Debug 正常、Release 崩溃的根源（`07_modern/08`）
7. **vector 优先** —— 别凭直觉选 list（`06_stl/01` 有实测）
8. **`const` 正确性** —— 接口自解释 + 编译器帮你检查（`07_modern/03`）
9. **容器迭代器失效规则** —— 悬空指针的主要来源（`06_stl/02`）
10. **二分/滑动窗口/DP 的模板** —— 别每次重新推导边界（`09_algo/02,04,06`）

---

## 七、关于本节内容的取舍

- **只写"能用得上"的**：模板元编程只讲 `type_traits`、CRTP、`if constexpr` 这些真实会用到的部分，没有堆砌奇技淫巧。
- **每个结论都有可运行的证据**：性能对比（vector vs list、摊还分析、路径压缩、模板 vs 循环）都是**实测数字**，不是断言。
- **明确写出"什么时候不要用"**：每节都有适用边界和反模式清单。
- **手写容器/算法是为了理解原理**：生产代码请用 `std::vector` / `std::sort` / `std::map`。
