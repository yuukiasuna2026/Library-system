# Library-system 图书馆借阅管理系统

## 目录结构

```
libarary/
├── src/        全部源码（.h 与 .cpp）
├── tests/      p1_test.cpp（实验五边界测试）、p2_test.cpp（实验六持久化测试）
├── data/       books.txt / users.txt / admins.txt 数据文件
└── libarary.slnx / libarary.vcxproj    
```

## 系统结构

Book                    图书实体类（书名/ISBN/作者/出版社/价格/页数/在馆状态/借阅人/借阅日期）
User  （抽象基类）       用户公共接口：ID/姓名/院系/已借数量/借阅与归还（虚函数）
 ├── Student            学生：最大借阅 5 本，不支持续借
 └── Teacher            教师：最大借阅 10 本，可续借 7 天
Library                 组合类：vector<Book> books + vector<User*> users
Admin                   管理员登录凭证类：账号/密码校验，多管理员由 vector<Admin> 管理
 └── main.cpp           双菜单界面：用户界面（借还查询）/ 管理员界面（后台管理）

- 组合关系：Library 拥有图书列表和用户列表。
- 依赖关系：借书 / 还书 / 打印信息等函数以 `User&` / `Book&` 为参数。
- 继承与多态：`User` 为抽象基类，`Student` / `Teacher` 公有继承并重写借阅相关虚函数，通过 `User*` 统一调用。
- 资源管理：`Library` 统一 `new/delete` 用户对象（析构函数释放、`clear()` 显式清空）

## 功能一览

用户界面（默认进入）：1 借书、2 还书、3 查询图书（ISBN/书名/作者）、4 列出全部图书、5 查询用户借阅、6 查询借阅与还书日期、7 续借（仅教师）、9 管理员登录、0 退出并保存。

管理员界面（登录后进入，无借还功能）：1 添加图书、2 删除图书、3 修改图书、4 添加用户、5 删除用户、6 修改用户、7 列出全部图书、8 返回用户界面、0 退出并保存。

其他规则：ISBN 合法性校验、重复 ISBN / 用户 ID 拒绝、日期自动获取（借书只输天数）、逾期判定与罚款、教师 7 天续借、同名图书精确匹配、有未还书拒删用户。

## 数据保存（fstream）

- 启动时从 `data/books.txt`、`data/users.txt`、`data/admins.txt` 恢复；文件缺失或为空时从空数据开始，不崩溃。
- 退出时覆盖写回三个文件。
- `users.txt` 含类型标记（Student / Teacher），读取时按标记 `new` 对应派生类对象，以 `User*` 存入 vector，保证多态不丢失；并记录借阅书名列表。
- 格式非法的行跳过并计数警告；图书借阅状态与用户记录不对应的坏数据按图书记录修正并提示。

## 实验知识点对应

| 实验 | 体现 |
| --- | --- |
| 实验一 类与对象 | Book / User / Admin 等类的封装、构造函数重载、访问控制 |
| 实验二 组合 / 依赖 | Library 组合类；借还、续借、查询函数依赖传引用 |
| 实验三 继承与派生 | User → Student / Teacher 公有继承 |
| 实验四 多态与虚函数 | 虚析构 + 借阅/续借相关虚函数（getDivisor / getRenewDays），经 `User*` 统一调用 |
| 实验五 模板与 vector | `vector<Book>`、`vector<User*>`、`vector<Admin>`，push_back / emplace_back / erase / 范围 for |
| 实验六 输入输出流 | `fstream` 存取图书、用户（含借阅书名列表）与管理员数据 |
