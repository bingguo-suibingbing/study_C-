// =============================================================================
//  01-1 数据类型与类型转换
// =============================================================================
//  目标：搞清楚"一个变量在内存里到底是什么"，以及"什么时候会发生隐式转换"。
//  类型系统是 C++ 的地基：一半的诡异 bug 都源于类型不匹配或隐式转换。
// =============================================================================

#include "course.h"

#include <iostream>
#include <iomanip>
#include <limits>
#include <string>
#include <cstdint>
#include <cmath>
#include <ctime>
#include <type_traits>

namespace cpp_learning {

void lesson_basic_types() {

    // =========================================================================
    lesson::chapter("基本类型全景：从最小到最大");
    // =========================================================================
    //  【核心概念】C++ 标准只保证"相对大小"，不保证绝对字节数（见 00 节）。
    //  所以讲"int 是 4 字节"严格来说不准确，应该说"我这台机器上是 4 字节"。
    //  真正需要精确宽度时用 <cstdint> 的定宽类型。
    //
    //  整型家族（按宽度递增）：
    //     bool          1 字节，值为 true/false（不是 1 字节的"整数"）
    //     char          1 字节，用来存"字符"，本质是小整数
    //     short         通常 2 字节
    //     int           通常 4 字节 —— 默认的整数类型，也是效率最高的
    //     long          32位系统4字节 / Win64 4字节 / Linux64 8字节（不跨平台！）
    //     long long     至少 8 字节 —— 跨平台想用大整数就选它
    //
    //  浮点家族：
    //     float         通常 4 字节，约 7 位有效十进制数字
    //     double        通常 8 字节，约 15~16 位有效数字 【默认选它】
    //     long double   平台差异极大（8/12/16 字节），基本不用
    //
    //  字符家族：
    //     char          窄字符，1 字节
    //     wchar_t       Windows 2 字节 / Linux 4 字节（同样不跨平台）
    //     char16_t      2 字节，UTF-16 单元
    //     char32_t      4 字节，UTF-32 单元
    //     char8_t       C++20 新增，1 字节，UTF-8 单元（u8"..." 的类型）
    //
    //  【实用选择】日常写业务代码，整数就用 int / long long，
    //     小数就用 double，字符用 char / std::string。
    //     其余类型只在明确需要（协议、跨平台、字符编码）时才动用。
    std::cout << "  sizeof(bool)=" << sizeof(bool)
              << "  sizeof(char)=" << sizeof(char)
              << "  sizeof(short)=" << sizeof(short)
              << "  sizeof(int)=" << sizeof(int)
              << "  sizeof(long)=" << sizeof(long)
              << "  sizeof(long long)=" << sizeof(long long) << "\n";
    std::cout << "  sizeof(float)=" << sizeof(float)
              << "  sizeof(double)=" << sizeof(double)
              << "  sizeof(long double)=" << sizeof(long double) << "\n";
    lesson::note("sizeof(char) 恒为 1 —— 这是标准硬性规定，是所有 sizeof 的基准单位。");

    // =========================================================================
    lesson::chapter("各类型的取值范围：别背，用 <limits> 问编译器");
    // =========================================================================
    //  【实用技巧】std::numeric_limits<T> 是查范围/精度的标准工具，
    //  比背表格可靠得多，而且换平台自动跟着变。
    std::cout << "  int      最小值 " << std::numeric_limits<int>::min()
              << "   最大值 " << std::numeric_limits<int>::max() << "\n";
    std::cout << "  unsigned 最小值 " << std::numeric_limits<unsigned>::min()
              << "   最大值 " << std::numeric_limits<unsigned>::max() << "\n";
    std::cout << "  long long 最大值 " << std::numeric_limits<long long>::max() << "\n";
    lesson::show("double 有效位数 (digits10)",
                 std::numeric_limits<double>::digits10);
    lesson::show("float  有效位数 (digits10)",
                 std::numeric_limits<float>::digits10);
    lesson::note("记住 int 上限约 21 亿(2.1e9)，这是最常被撑爆的边界。");
    lesson::note("超过 int 范围请用 long long(约 9.2e18)，别用 long —— 它在 Windows 上只有 4 字节。");

    // =========================================================================
    lesson::chapter("有符号 / 无符号：最大的坑区");
    // =========================================================================
    //  【核心规则】有符号和无符号混合运算时，有符号会被【隐式转换】成无符号。
    //  这意味着 -1 会变成 4294967295，比较结果完全反直觉。
    //
    //  经典事故 1：倒序循环永不结束
    //      for (unsigned i = 10; i >= 0; --i) { ... }
    //      i 是无符号，i>=0 恒真；i 从 0 减 1 变成 4294967295，然后继续跑。
    //      -> 无符号做倒序循环必须写成 for (unsigned i = 10; i-- > 0; )
    //
    //  经典事故 2：比较被静默改写
    //      int a = -1; unsigned b = 1;  if (a < b) ...   -> 假！
    //      因为 a 被转成 4294967295，反而比 b 大。
    //
    //  【实用习惯】三条能避开 90% 的无符号坑：
    //      1. 只在"确实表示位模式/大小"时用无符号（size_t、位运算）
    //      2. 循环计数一律用 int（除非确实要跟 size() 比较）
    //      3. 与 .size() 比较时，要么把 size() 转成 int，要么两边都用 size_t
    {
        const int negative = -1;
        const unsigned positive = 1;
        lesson::show("int(-1) < unsigned(1) 的结果", negative < positive);
        lesson::show("(unsigned)(-1) 的数值", static_cast<unsigned>(negative));
        lesson::note("这就是为什么编译器会警告 signed/unsigned mismatch —— 它在救你。");

        // 正确的倒序循环写法：先判断后自减，永远不会下溢
        std::cout << "  倒序输出 (i-- > 0): ";
        for (unsigned i = 5; i-- > 0; ) std::cout << i << " ";
        std::cout << "\n";
    }

    // =========================================================================
    lesson::chapter("整数的溢出与回绕：UB 还是确定行为？");
    // =========================================================================
    //  【重要且常被搞错的一点】
    //     无符号溢出：标准明确规定为"模 2^N 回绕"，行为确定。
    //     有符号溢出：是【未定义行为 UB】！优化器可以假设它永不发生，
    //                 于是可能把你的 if 判断整个优化掉。
    //
    //  所以 `if (x + 1 < x) { 说明溢出了 }` 这种溢出检测在优化后可能失效。
    //  正确做法是用 <limits> 在运算前判断，或用 <cstdint> 的无符号类型。
    {
        unsigned wrap = std::numeric_limits<unsigned>::max();
        ++wrap;                       // 无符号溢出：确定回绕到 0
        lesson::show("unsigned 最大值 +1", wrap);
        lesson::note("无符号溢出是确定的回绕；有符号溢出是 UB，绝不要依赖它。");

        // 【实用技巧】时间戳/计数器的安全加法写法
        auto saturating_add = [](std::uint64_t a, std::uint64_t b) {
            if (a > std::numeric_limits<std::uint64_t>::max() - b) {
                return std::numeric_limits<std::uint64_t>::max();   // 饱和，不溢出
            }
            return a + b;
        };
        lesson::show("饱和加法 (10, 20)", saturating_add(10, 20));
        lesson::note("真实工程里统计计数、累加器都该考虑溢出策略（回绕/饱和/报错）。");
    }

    // =========================================================================
    lesson::chapter("浮点数：为什么 0.1 + 0.2 != 0.3");
    // =========================================================================
    //  【原理】二进制浮点无法精确表示大多数十进制小数。
    //  0.1 在二进制里是无限循环小数，存进 double 时被截断，
    //  误差小到看不见，但比较时就会暴露。
    //
    //  【正确比较浮点数的写法】用一个"容忍度"（epsilon）判断足够接近：
    //      fabs(a - b) < epsilon
    //  绝对容忍度适合数值量级已知的场合；对于跨越几个数量级的数，
    //  要用相对容忍度：fabs(a-b) <= epsilon * max(fabs(a), fabs(b))
    //
    //  【绝对不要做的事】
    //      - 用 == 比较浮点数
    //      - 用浮点数做金额计算（用整数分/厘，或用定点数库）
    //      - 用浮点数做循环计数器和数组下标
    {
        const double a = 0.1, b = 0.2;
        std::cout << std::setprecision(20);
        lesson::show("0.1 + 0.2", a + b);
        lesson::show("0.1 + 0.2 == 0.3 的结果", (a + b) == 0.3);
        std::cout << std::setprecision(6);   // 恢复默认，别影响后面所有输出

        constexpr double kEpsilon = 1e-9;
        lesson::show("fabs(0.1+0.2-0.3) < 1e-9 的结果", std::fabs(a + b - 0.3) < kEpsilon);
        lesson::note("浮点比较永远用容忍度；金额一律用整数分表示，不要用 double。");

        // 【实用技巧】浮点的特殊值：NaN 和 Infinity
        // 注意：0.0/0.0 在浮点运算里是合法的，产生 NaN，不是崩溃（整数除零才是崩溃）。
        // 但写成字面量常量表达式时编译器会直接报 "divide by zero"，
        // 所以这里用 volatile 挡一下，让除法在运行期真正发生（这本身也是一种技巧）。
        volatile double zero = 0.0;
        const double nan_value = 0.0 / zero;      // NaN：非法运算的结果
        const double inf_value = 1.0 / zero;      // +Inf：溢出上限
        lesson::show("0.0/0.0", nan_value);
        lesson::show("1.0/0.0", inf_value);
        lesson::show("NaN == NaN 的结果", nan_value == nan_value);
        lesson::note("NaN 与任何值比较都是 false，包括它自己。判断必须用 std::isnan()。");
        lesson::note("NaN 最阴险的地方：它会在计算链里悄悄传播，最后才在你意想不到的地方出错。");
    }

    // =========================================================================
    lesson::chapter("初始化：C++ 的四种写法，以及为什么推荐花括号");
    // =========================================================================
    //  需求：定义一个变量并给它初值。历史演化出四种语法：
    //
    //    int a = 5;         拷贝初始化（copy initialization）
    //    int b(5);          直接初始化（direct initialization）
    //    int c{5};          列表初始化（list initialization, C++11）【推荐】
    //    int d = {5};       带等号的列表初始化（等价于 c）
    //
    //  【为什么推荐 {}】它有一个别人都没有的能力：禁止窄化转换（narrowing）
    //      int x = 3.9;    // 编译通过，x = 3，小数部分被静默丢弃（危险！）
    //      int y{3.9};     // 编译错误！编译器直接拦住你
    //
    //  对新手来说，这个"静默丢数据"是最难发现的 bug 来源之一。
    //  用 {} 把这类错误从"运行时诡异结果"提前到"编译期报错"。
    //
    //  【补充】{} 还是唯一能"值初始化"的语法：
    //      int a;      // 未初始化，值不确定
    //      int b{};    // 初始化为 0     <- 推荐写法
    //      int c();    // 注意！这是函数声明，不是变量定义（最令人烦恼的解析）
    {
        // 【工程习惯】一段"故意演示坏味道"的代码，就用局部 pragma 明确关掉告警，
        //   并在旁边写清为什么。这样工程整体的告警数依然是 0 —— 零告警才有意义，
        //   告警洪水等于没告警（详见 00 节）。
#pragma warning(push)
#pragma warning(disable : 4244)   // 故意演示 double->int 的窄化丢精度
        int from_double = 3.9;     // 编译通过，小数部分被静默丢弃
#pragma warning(pop)
        lesson::show("不带 {} 时 int x = 3.9 的结果", from_double);

        // int bad{3.9};           // 取消注释会编译失败 —— 这正是我们想要的保护
        int good{static_cast<int>(3.9)};   // 想清楚了再显式转换，意图明确
        lesson::show("显式 static_cast<int>(3.9)", good);

        [[maybe_unused]] int zero_initialized{};      // 可靠地变成 0
        lesson::note("{} 是唯一能禁止窄化转换的初始化语法 —— 默认就用它。");
    }

    // =========================================================================
    lesson::chapter("隐式类型转换：编译器在替你做什么");
    // =========================================================================
    //  出现隐式转换的三大场景：
    //    1. 赋值/初始化时类型不一致
    //    2. 算术运算两边类型不一致（整型提升 + 寻常算术转换）
    //    3. 函数传参时实参类型与形参不一致
    //
    //  【整型提升规则】比 int 小的类型（bool/char/short）参与算术运算时，
    //  会先被"提升"为 int 再算。所以 char + char 得到的是 int，不是 char。
    //
    //  【寻常算术转换规则】两边类型不同时，向"能容纳范围更大的那个"转换：
    //      long double > double > float > 整数家族（宽度大的优先）
    //  特例：有符号遇到同宽度的无符号 -> 转成无符号（前面讲过的坑）。
    //
    //  【隐式转换导致 bug 的三个典型】
    //    1. 有符号撞无符号（前面讲过）
    //    2. 大范围转小范围静默截断：long long x = 5e9; int y = x;  // y 是垃圾
    //    3. 指针与 bool：if (ptr) 是判空，但 if (ptr = nullptr) 是赋值再判 —— 
    //       少写一个等号，编译器可能只给个告警。所以比较时常把常量写左边：
    //       if (nullptr == ptr) —— 写成 = 会直接编译错误。
    {
        const char c1 = 'A';
        const char c2 = 1;
        // c1 + c2 的类型是 int（整型提升），不是 char
        static_assert(std::is_same_v<decltype(c1 + c2), int>,
                      "char + char 的结果类型是 int");
        lesson::show("char('A') + char(1) 通过整型提升得到", c1 + c2);

        const long long big = 5'000'000'000LL;   // 数字分隔符 ' 只是给人看的
        const int truncated = static_cast<int>(big);
        lesson::show("long long 5000000000 截断成 int", truncated);
        lesson::note("静默截断是大范围转小范围时最容易忽略的问题，编译器不一定报警。");

        const double d = 3.99;
        const int from_double = static_cast<int>(d);
        lesson::show("(int)3.99 是截断不是四舍五入", from_double);
        lesson::note("想四舍五入要用 std::lround / std::round，不要靠强制转换。");
    }

    // =========================================================================
    lesson::chapter("显式转换：四种 cast，别再用 C 风格括号转换");
    // =========================================================================
    //  C 风格的 (int)x 什么都能转，什么都转得静默，出了问题也不知道是谁干的。
    //  C++ 提供四种用途明确的转换，用它们能把"意图"写在代码里。
    //
    //  1. static_cast<T>(v)          编译期可确定的合理转换
    //       最常用。数值类型互转、父类指针转子类指针（你自己负责安全性）、
    //       显式调用转换构造函数。
    //       不做运行期检查，不做无关类型之间的转换。
    //
    //  2. dynamic_cast<T>(v)         运行期检查的多态类型转换
    //       仅用于有虚函数的继承体系。父类指针 -> 子类指针，失败返回 nullptr
    //       （转引用时抛 std::bad_cast）。有运行时开销（查 RTTI）。
    //       见 04 继承篇。
    //
    //  3. const_cast<T>(v)           去掉/加上 const
    //       唯一的用途。绝大多数情况下是"设计有问题的信号"。
    //       唯一正当场景：对接 C 老接口（它接收非 const 指针但实际不修改）。
    //
    //  4. reinterpret_cast<T>(v)     重新解释二进制位，最危险
    //       指针与整数互转、无关指针类型互转。完全不检查。
    //       只在底层编程（序列化、硬件寄存器、ABI）里用，且必须非常清楚后果。
    //
    //  【实用习惯】代码里禁止出现 C 风格转换（除了个别模板库的惯用法）。
    //     用 static_cast 之类的写法，能让 code review 一眼看出"这里有转换"，
    //     也能直接用文本搜索定位所有转换点。
    {
        const double pi = 3.14159;
        const int truncated = static_cast<int>(pi);
        lesson::show("static_cast<int>(3.14159)", truncated);

        // const_cast 的唯一正当场景演示
        const char* c_str_style = "literal";
        // 对接只接受 char* 的老 C 函数时（该函数承诺不修改内容）
        auto* legacy_api_arg = const_cast<char*>(c_str_style);
        lesson::show("const_cast 后的指针与原指针相同", legacy_api_arg == c_str_style);
        lesson::note("如果发现自己需要 const_cast，先停下来问：是不是设计错了？");

        // 数字分隔符 + 二进制字面量的实用写法
        const int binary_mask = 0b1010'1010;
        const int hex_color = 0xFF'80'40;
        lesson::show("0b10101010", binary_mask);
        lesson::show("0xFF8040", hex_color);
        lesson::note("0b 二进制、0x 十六进制、' 分隔符 —— 位操作和常量场景很好用。");
    }

    // =========================================================================
    lesson::chapter("auto 与 decltype：类型推导的两把工具");
    // =========================================================================
    //  【auto】让编译器从初始值推导类型。规则基本等于"按值拷贝时推导"：
    //      auto x = expr;      -> 得到 expr 的"值类型"（数组/函数会退化，const 被丢掉）
    //      auto& y = expr;     -> 得到引用，且【保留】const
    //      const auto& z = expr; -> 万能接收，不拷贝也不改
    //
    //  【用 auto 的三条实用判据】
    //      该用：类型冗长且显而易见时
    //            auto it = map.find(key);              // 类型名长得离谱
    //            auto ptr = std::make_unique<Widget>();  // 左边写两遍没意义
    //      不该用：类型有歧义、或需要显式类型做转换时
    //            auto n = 5;         // 明明想表达 size_t
    //            auto ratio = 1 / 2;  // 想表达 0.5，实际得到 int 0
    //      绝不该用：auto 掩盖了"其实发生了拷贝"这件事（要写 auto& 或 const auto&）
    //
    //  【decltype】不求值，只问"这个表达式的类型是什么"。
    //      与 auto 不同，decltype 保留引用和 const：
    //          int n = 0; int& r = n;
    //          auto        a = r;   // int      （引用被丢掉）
    //          decltype(r) b = n;   // int&     （引用被保留）
    //      decltype 主要用在泛型代码里（见 05 模板篇）。
    {
        const int n = 42;
        auto a1 = n;            // int，const 被丢掉
        auto& a2 = n;           // const int&，const 被保留
        a1 = 100;               // 合法：a1 是 n 的副本
        // a2 = 100;            // 取消注释会编译失败：a2 是 const 引用

        static_assert(std::is_same_v<decltype(a1), int>);
        static_assert(std::is_same_v<decltype(a2), const int&>);
        lesson::show("auto a1 = n;  之后 a1", a1);
        lesson::show("a2 仍是 n 的别名，值不变", a2);

        // 【坑】auto 会把数组退化成指针
        int arr[3] = { 1, 2, 3 };
        auto arr_decayed = arr;                 // int* —— 丢失了"长度是3"这个信息
        auto& arr_ref = arr;                    // int(&)[3] —— 保留了数组类型
        static_assert(std::is_same_v<decltype(arr_decayed), int*>);
        static_assert(std::is_same_v<decltype(arr_ref), int(&)[3]>);
        lesson::show("sizeof(arr_decayed) 退化后是指针大小", sizeof(arr_decayed));
        lesson::show("sizeof(arr_ref) 保留数组大小", sizeof(arr_ref));
        lesson::note("auto 按值推导会让数组/函数退化；要保留就用 auto&。");

        // 【实用技巧】结构化绑定（C++17）：一次拆出多个值，比 .first/.second 清爽
        std::pair<std::string, int> entry{ "张三", 25 };
        const auto& [name, age] = entry;         // name="张三", age=25
        lesson::show("结构化绑定取出的 name", name);
        lesson::show("结构化绑定取出的 age", age);
        lesson::note("结构化绑定用 const auto& 接，避免不必要的拷贝。");
    }

    // =========================================================================
    lesson::chapter("const 与 constexpr：编译期能算就别留到运行期");
    // =========================================================================
    //  const        "运行期不可修改"。值可以在运行期确定。
    //  constexpr    "编译期就能确定"。既是 const，又可用于编译期上下文
    //               （数组长度、模板参数、case 标签、static_assert）。
    //
    //  【为什么 constexpr 重要，不只是"显得高级"】
    //      1. 编译期算完，运行时零开销（比如查表、常量折叠）
    //      2. 编译期就能发现错误，而不是等程序跑起来
    //      3. 能用在 const 用不了的地方（模板参数、数组大小）
    //
    //  【实用习惯】能用 constexpr 就用 constexpr；退一步用 const。
    //      真实项目里这两者还能帮编译器做更多优化（常量传播）。
    {
        const int runtime_value = static_cast<int>(std::time(nullptr) % 2);
        lesson::show("运行期才能确定的 const", runtime_value);

        constexpr int compile_time_size = 8;      // 可以当数组长度
        constexpr double kPi = 3.14159265358979;
        constexpr int factorial_5 = 5 * 4 * 3 * 2 * 1;

        int arr[compile_time_size]{};             // const 不行，constexpr 才行
        lesson::show("constexpr 数组长度", sizeof(arr) / sizeof(arr[0]));
        lesson::show("constexpr kPi", kPi);
        lesson::show("constexpr 5! 编译期算好", factorial_5);

        // constexpr 函数：既能编译期求值，也能运行期调用
        constexpr auto square = [](int x) { return x * x; };
        constexpr int sq = square(12);             // 编译期算完，汇编里直接是 144
        static_assert(sq == 144, "编译期就验证了结果");
        lesson::show("constexpr 函数编译期求值 square(12)", sq);
        lesson::note("static_assert 是免费的正确性证明：错了编译就过不去。");
    }

    // =========================================================================
    lesson::chapter("本节小结");
    // =========================================================================
    //  □ 默认用 int / long long / double，精确位宽用 <cstdint>
    //  □ 范围别背，用 std::numeric_limits<T>::max() 查
    //  □ 无符号只用于"位模式/大小"，循环计数用 int
    //  □ 有符号溢出是 UB；无符号溢出是确定的回绕
    //  □ 浮点数绝不用 == 比较，金额绝不用 double
    //  □ 初始化一律用 {}，它能拦住窄化转换这个静默杀手
    //  □ 显式转换只用 static_cast 系列，禁用 C 风格括号转换
    //  □ auto 让代码更短，但要知道它"丢 const、退化数组"的规则
    //  □ 能 constexpr 就 constexpr
    lesson::note("类型是所有后续知识的地基，这一节值得反复看几遍。");
}

}  // namespace cpp_learning
