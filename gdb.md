1. **ptrace 系统调用**: 
  
   `ptrace` 不是一个独立的程序，而是一个系统调用。系统调用是操作系统内核提供的一组函数，充当用户态程序和内核态之间的桥梁。`ptrace` 允许一个进程（例如 GDB）控制另一个进程（被调试程序）的执行，并检查和修改其内存和寄存器。GDB 使用 `ptrace` 来实现断点、单步执行、查看变量等功能。

2. **调试信息**:
  
   调试信息是编译器在使用 `-g` 选项编译程序时生成的数据，它将程序的内部结构和源代码关联起来，使调试器（如 GDB）能够理解程序的状态并提供有用的信息。

   **调试信息的内容**：
   
   - **行号表**: 将可执行文件的机器指令地址映射回源代码的行号。这使得 GDB 可以设置断点并在源代码级别单步执行。
   
   - **符号表**: 包含程序中所有变量、函数、类型等的名称和地址。GDB 使用符号表来显示变量的值、查找函数的地址以及理解程序的结构。
   
   - **类型信息**: 描述程序中使用的各种数据类型的结构，例如结构体、类、枚举等。这使得 GDB 可以正确地解释复杂数据结构的值。
   
   - **宏定义**: 存储预处理器宏的定义，以便 GDB 可以显示宏展开后的代码。需要注意的是，GDB 对宏的支持有限，具体取决于编译器和调试信息格式。
   
   - **源代码信息**: 可能包含源代码文件的路径，甚至部分源代码本身，以便 GDB 可以在调试时显示源代码。
   
   - **DWARF 信息**: DWARF 是一种标准的调试信息格式，它以一种结构化的方式存储上述所有信息。大多数现代编译器都使用 DWARF 格式。

3. **如果没有调试信息会发生什么**：
  
   - **无法设置源代码级别的断点**: GDB 只能在机器指令地址上设置断点，而无法在源代码的行号上设置断点。
   
   - **无法单步执行源代码**: GDB 只能单步执行机器指令，而无法单步执行源代码行。
   
   - **无法显示变量名和值**: GDB 无法将内存地址与变量名关联起来，因此无法显示变量的值。你只能看到原始的内存地址和其中的数据。
   
   - **无法查看函数调用栈**: GDB 难以理解函数调用关系，因此无法显示完整的函数调用栈。
   
   - **无法理解程序的结构**: GDB 无法理解程序中使用的类型、结构体、类等，因此无法有效地显示复杂数据结构的值。

4. **GDB 在不同操作系统上的支持**:
  
   - **Windows**: GDB 实际上是有原生的 Windows 版本的，通过 MinGW 或 Cygwin 等项目提供支持。此外，GDB 也可以在 Windows 子系统 Linux (WSL) 中使用。
   
   - **Docker**:
     ```bash
     docker run --cap-add=SYS_PTRACE -it <image_name>
     ```
   
   - **Linux**:
     默认情况下，Linux 不完全开启 `ptrace` 权限。要修改 `ptrace` 的权限设置，可以编辑 `/etc/sysctl.d/10-ptrace.conf`（或者 `/etc/sysctl.conf`，取决于发行版）文件，在文件中添加或修改以下行：
     
     ```bash
     kernel.yama.ptrace_scope = 0  # 或 1, 2
     ```
     - `0` (unrestricted): 完全禁用 `ptrace` 的安全限制，允许所有用户 `ptrace` 任何进程。
     - `1` (restricted): 默认设置，一个进程只能 `ptrace` 它拥有或其父进程拥有的进程。
     - `2` (admin-only): 允许具有 `CAP_SYS_PTRACE` 能力的进程 `ptrace` 任何进程。实际操作中，这意味着只有 root 用户（或具有相应能力的用户）才能 `ptrace` 其他进程。
     
     保存文件后，运行以下命令使修改生效：
     ```bash
     sudo sysctl -p
    ```
  
5. **开启调试信息**:
  
   - **编译器**:
     ```bash
     g++ -g -o myprogram myprogram.cpp
     ```
   
   - **CMakeLists.txt**:
     ```cmake
     set(CMAKE_BUILD_TYPE Debug)
     ```

6. **构建类型**:
  
   - **Debug (调试)**: 编译器会禁用大多数优化，并生成包含调试信息的二进制文件。使得调试器（如 GDB）可以有效地工作，例如设置断点、单步执行代码、检查变量值等。生成的二进制文件通常较大且运行速度较慢，因为它包含了大量的调试信息，并且没有进行优化。
   
   - **Release (发布)**: 最终发布的构建类型。编译器会启用优化，以提高程序的性能和减小二进制文件的大小。调试信息通常会被移除，因此调试器功能会受到限制。生成的二进制文件通常较小且运行速度较快。
   
   - **RelWithDebInfo (发布，带调试信息)**: 这是 Release 和 Debug 之间的折衷方案。编译器会启用大多数优化，但仍然会生成包含调试信息的二进制文件。这允许在发布版本中进行一些调试，生成的二进制文件大小和运行速度介于 Debug 和 Release 之间。
   
   - **MinSizeRel (最小尺寸发布)**: 这种构建类型优先考虑减小二进制文件的大小，即使以牺牲一些性能为代价。编译器会启用针对减小代码大小的优化，并移除调试信息。生成的二进制文件通常是最小的，但运行速度可能不如 Release 构建类型。

7. **GDB 基本使用**:
  
   - **启动和附加进程**:
     - `gdb <program>`: 启动程序 `<program>` 并进入调试模式。
     - `gdb <program> <core_dump>`: 调试程序 `<program>` 的核心转储文件 `core_dump`。
     - `gdb -p <pid>`: 附加到正在运行的进程，进程 ID 为 `<pid>`。
     - `gdb --args <program> <arg1> <arg2> ...`: 启动程序 `<program>` 并传递参数 `arg1`, `arg2` 等。
     
    - **线程:**
        - info threads: (i threads)列出所有线程，并显示它们的ID、状态（例如运行、睡眠、停止）以及当前正在执行的函数。 GDB会用一个星号 (*) 标记当前正在调试的线程。
thread 
        - thread id: 切换到指定的线程。 例如，thread 2 会切换到线程 2。
        - thread apply all <command>: 对所有线程应用指定的 GDB 命令。 例如，thread apply all bt 会打印所有线程的回溯。
        - thread apply <thread_id_list> <command> :<thread_id_list> 是一个或多个线程 ID，用空格分隔。 例如，thread apply 2 3 bt 会打印线程 2 和线程 3 的回溯。
   
   - **断点**:
     - `break <location>`: 在指定位置设置断点。`location` 可以是函数名、行号或内存地址。例如：`break main`、`break 12`、`break *0x400080`。通过输出可以查看断点编号，例如：
       ```
       (gdb) break main
       Breakpoint 1 at 0x400526: file main.c, line 6.
       ```
     - `break <location> if <condition>`: 设置条件断点。只有当条件 `<condition>` 为真时才会触发断点。例如：`break main if i == 10`。
     - `info breakpoints`: 列出所有断点。
     - `delete <breakpoint_number>`: 删除指定编号的断点。
     - `disable <breakpoint_number>`: 禁用指定编号的断点。
     - `enable <breakpoint_number>`: 启用指定编号的断点。
   
   - **执行控制**:
     - `run`: 开始执行程序。
     - `continue`: 继续执行程序，直到遇到下一个断点或程序结束。
     - `next`: 执行下一行代码，如果当前行是函数调用，则将整个函数调用视为一行。
     - `step`: 执行下一行代码，如果当前行是函数调用，则进入函数内部。
     - `finish`: 执行完当前函数并返回到调用者。
     - `until <location>`: 继续执行程序，直到到达指定位置。
     - `kill`: 终止正在调试的程序。
   
   - **变量检查**:
     - `print <expression>`: 打印表达式的值。例如：`print i`、`print a[0]`、`print *ptr`。
     - `display <expression>`: 每次程序停止时都打印表达式的值。
     - `undisplay <display_number>`: 取消显示指定编号的表达式。
     - `whatis <variable>`: 打印变量的数据类型。例如，`whatis myVector` 会输出 `type = std::vector<int>`。
     - `ptype <variable>`: 打印变量的详细类型信息。例如：
       ```
       ptype myVector
       type = std::vector<int, std::allocator<int> >
       {
         // 详细类型定义
       }
       ```
     - `x/<nfu> <address>`: >: 检查内存. n 是要显示的单元格数量，f 是格式（例如 x - 十六进制, d - 十进制, c - 字符），u 是单元格大小（例如 b - 字节,通常是 8 位， h - 半字, w - 字,在 32 位系统上通常是 32 位， 64 位系统上通常是 64 位， g - giant word，双字）,  例如：从特定地址开始的 2 个 giant words (8 字节) 的内容 (十六进制)：
       ```
       (gdb) x/2xg 0x7fffffffdf70
       0x7fffffffdf70: 0x6f77202c6f6c6c65	0x0000000000003039......
       ```
   
   - **调用栈**:
     - `backtrace`: 打印调用栈。
     - `frame <frame_number>`: 切换到指定的栈帧。
     - `up`: 向上移动一个栈帧，不执行程序。
     - `down`: 向下移动一个栈帧，不执行程序。
   
   - **其他**:
     - `set args <arg1> <arg2> ...`: 设置程序的参数。在进入程序后设置程序输入参数。
       
       ```
       gdb myprogram
       (gdb) set args t.txt 10
       ```
       这会将 `t.txt` 和 `10` 设置为 `myprogram` 的参数。
     - `show args`: 显示程序启动时将要使用的参数列表。如果没有使用 `set args` 设置参数，`show args` 会显示程序启动时的默认参数（如果有的话），或者一个空的参数列表。
     - `help <command>`: 获取指定命令的帮助信息。
       ```
       (gdb) help set args
       Set argument list to give program being debugged when it is started.
       Follow this command with any number of args, to be passed to the program.
       ```
     - `quit`: 退出 GDB。
     
**GDB 常用命令及缩写对照表**
| 命令全称 | 缩写 | 描述 |
|---|---|---|
| `break` | `b` | 设置断点 |
| `continue` | `c` | 继续执行程序 |
| `run` | `r` | 运行程序 |
| `next` | `n` | 执行下一行代码（单步执行，不进入函数） |
| `step` | `s` | 执行下一行代码（单步执行，进入函数） |
| `finish` | `fin` | 继续执行到当前函数返回 |
| `until` | `u` | 继续执行到指定行或地址 |
| `print` | `p` | 打印变量或表达式的值 |
| `display` | `disp` | 每次程序停止时都打印变量或表达式的值 |
| `undisplay` | `undisp` | 取消 `display` 命令设置的显示 |
| `info` | `i` | 显示信息 |
| `delete` | `d` | 删除 |
| `disable` | `dis` | 禁用 |
| `enable` | `en` | 启用 |
| `backtrace` | `bt` | 打印函数调用栈 |
| `frame` | `f` | 选择栈帧 |
| `up` | `up` | 向上移动栈帧 |
| `down` | `down` | 向下移动栈帧 |
| `thread` | `thread` | 切换到指定线程 |
| `set args` | `set args` | 设置程序参数 |
| `show args` | `show args` | 显示程序参数 |
| `quit` | `q` | 退出 GDB |
| `help` | `h` | 显示帮助信息 |
| `whatis` | `whatis` | 显示变量的类型 |
| `ptype` | `ptype` | 显示变量更详细的类型信息 |
| `list` | `l` | 显示源代码 |
| `set listsize` | `set listsize` | 设置显示源代码的行数 |
| `info locals` | `i locals` | 显示当前栈帧中的局部变量 |
| `info variables` | `i variables` | 显示全局变量和静态变量 |
| `watch` | `watch` | 设置监视点 (当变量值改变时停止) |
| `set variable` | `set var` | 修改一个变量的值 |

