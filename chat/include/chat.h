cd ~
mkdir -p chat/include chat/src
cat > chat/include/chat.h << 'EOF'
#ifndef CHAT_H
#define CHAT_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

#define CHAT_PATH      "/tmp"
#define CHAT_PROJ_ID   'C'

#define CHAT_MSG_SIZE  1024
#define CHAT_TYPE_SEND 1
#define CHAT_TYPE_RECV 2

#define CHAT_MY_TYPE   1
#define CHAT_PEER_TYPE 2

struct chat_msg {
    long mtype;
    char mtext[CHAT_MSG_SIZE];
};

key_t  chat_get_key(void);
int    chat_msgget(key_t key, int create);
void   chat_msgrm(int msqid);

#endif
EOF
