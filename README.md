# Library-system 图书馆借阅管理系统

## 系统结构

Book                    图书实体类（书名/ISBN/作者/出版社/价格/页数/在馆状态/借阅人/借阅日期）
User  （抽象基类）       用户公共接口：ID/姓名/院系/已借数量/借阅与归还（虚函数）
 ├── Student            学生：最大借阅 5 本
 └── Teacher            教师：最大借阅 10 本，可续借 7 天
Library                 组合类：vector<Book> books + vector<User*> users
 └── main.cpp           菜单化接口

- 组合关系：Library 拥有图书列表和用户列表。
- 依赖关系：借书 / 还书 / 打印信息等函数以 `User&` / `Book&` 为参数。
- 继承与多态：`User` 为抽象基类，`Student` / `Teacher` 公有继承并重写借阅相关虚函数，通过 `User*` 统一调用。
- 资源管理：`Library` 统一 `new/delete` 用户对象（析构函数释放、`clear()` 显式清空），禁止拷贝构造与赋值，避免双重释放。

## 功能一览

| 选项 | 功能 | 权限 |
| --- | --- | --- |
| 1 / 2 | 添加 / 删除图书 | 管理员 |
| 3 / 4 | 查询图书（按 ISBN）/ 列出全部图书 | 公开 |
| 5 / 6 | 添加 / 删除用户（有未还图书时拒绝删除） | 管理员 |
| 7 / 8 | 修改图书 / 用户信息 | 管理员 |
| 9 / 10 | 借书 / 还书（输入用户 ID 即时验证，不保留登录状态） | 公开 |
| 11 | 查看用户信息与借阅记录 | 公开 |
| 12 / 13 | 管理员登录 / 登出（账号 admin，密码 123456，错 3 次锁定本次登录） | — |
| 0 | 退出并保存数据 | — |

其他规则：ISBN 合法性校验、重复 ISBN / 用户 ID 拒绝、日期合法性及借还顺序检查、逾期判定与罚款提示、同名图书精确匹配。

## 数据保存（fstream）

- 启动时从 `books.txt`、`users.txt` 恢复；文件缺失或为空时从空数据开始，不崩溃。
- 退出时覆盖写回两个文件。
- `users.txt` 含类型标记（Student / Teacher），读取时按标记 `new` 对应派生类对象，以 `User*` 存入 vector，保证多态不丢失。
- 格式非法的行跳过并计数警告；图书借阅状态与用户记录不对应的坏数据跳过并提示。

## 实验知识点对应

| 实验 | 体现 |
| --- | --- |
| 实验一 类与对象 | Book / User 等类的封装、构造函数重载、访问控制 |
| 实验二 组合 / 依赖 | Library 组合类；借还函数依赖传引用 |
| 实验三 继承与派生 | User → Student / Teacher 公有继承 |
| 实验四 多态与虚函数 | 虚析构 + 借阅相关虚函数，经 `User*` 统一调用 |
| 实验五 模板与 vector | `vector<Book>`、`vector<User*>`，push_back / emplace_back / erase / 范围 for |
| 实验六 输入输出流 | `fstream` 存取图书与用户数据 |

## 构建与运行

- Visual Studio：打开 `libarary.slnx`，直接编译运行（main.cpp 为入口）
- 命令行（MinGW）：`g++ -std=c++17 main.cpp book.cpp library.cpp User.cpp Student.cpp Teacher.cpp -o main.exe`

## 测试

- `p1_test.cpp`：实验五边界测试（空 vector 查找、增删、多态输出等）
- `p2_test.cpp`：实验六持久化测试（加载、保存、坏数据容错、类型恢复等）