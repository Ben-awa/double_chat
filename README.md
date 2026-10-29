# 基于 System V 消息队列的双终端本地聊天程序
鲁班猫 1 · 嵌入式 Linux 应用开发作业。

## 简介

本项目使用 System V IPC 中的**消息队列（Message Queue）**实现同一台主机上两个终端之间的实时文本通信。

两个终端进程通过 `ftok` 生成同一个 key，访问同一个消息队列，利用 `mtype` 字段区分消息方向，避免自己收到自己发出的消息。

## 目录结构

```
chat/
├── Makefile
├── include/
│   └── chat.h
└── src/
    ├── chat.c
    ├── sender.c
    └── receiver.c
```

| 文件 | 职责 |
|------|------|
| `include/chat.h` | 头文件，定义 key、消息结构体、函数声明 |
| `src/chat.c` | 公共逻辑：`ftok`、`msgget` 封装 |
| `src/sender.c` | 发送端，读取标准输入并发送 |
| `src/receiver.c` | 接收端，阻塞等待并回显 |

## 编译

```bash
cd chat
make
```

编译产物位于 `bin/`：`bin/chat_sender` 与 `bin/chat_receiver`。

清理构建产物：

```bash
make clean
```

## 运行

开两个终端。终端一（接收端）先启动：

```bash
cd chat
./bin/chat_receiver
```

终端二（发送端）：

```bash
cd chat
./bin/chat_sender
```

发送端输入文字回车发送，输入 `quit` 退出。

## 设计说明

### key 的生成

```c
#define CHAT_PATH    "/tmp"
#define CHAT_PROJ_ID 'C'
```

`ftok` 要求该路径真实存在，否则返回 -1。两个进程必须使用相同的路径与项目号，才能得到同一个 key。

### 消息类型区分方向

```c
#define CHAT_MY_TYPE    1
#define CHAT_PEER_TYPE  2
```

发送端发出的消息 `mtype` 设为 1，接收端只接收 `mtype` 为 2 的消息。这样消息不会回流到发送方自身。

### 消息结构体

```c
struct chat_msg {
    long mtype;            // 消息类型，必须第一个成员
    char mtext[CHAT_MSG_SIZE];
};
```

`msgsnd` 的第三个参数长度只算 `mtext`，不含 `mtype`，故为 `strlen(msg.mtext) + 1`。

### 核心 API

| 函数 | 作用 |
|------|------|
| `ftok()` | 路径 + 项目号 → key |
| `msgget()` | 创建或获取队列 |
| `msgsnd()` | 发送消息 |
| `msgrcv()` | 接收指定类型消息（默认阻塞） |
| `msgctl()` | 控制队列，如 `IPC_RMID` 删除 |

## 注意事项

消息队列生命周期独立于进程，**程序退出后队列仍在内存中**。

```bash
ipcs -q              # 查看所有消息队列
ipcrm -Q /tmp/C      # 按 key 删除
ipcrm -q <msqid>     # 按 id 删除
```

每次运行前建议清理残留队列，否则可能由于已存在而触发 `EEXIST` 导致 `msgget` 失败。

## 开发环境

- 板卡：鲁班猫 1（LubanCat-1）
- 系统：Ubuntu（出厂镜像）
- 编译器：gcc
- 依赖：glibc、System V IPC（`sys/msg.h`）
