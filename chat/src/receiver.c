cat > chat/src/receiver.c << 'EOF'
#include "chat.h"

int main(void)
{
    key_t key;
    int msqid;
    struct chat_msg msg;

    key = chat_get_key();
    msqid = chat_msgget(key, 0);

    printf("[接收端] 启动，等待对方消息...\n");
    printf("[接收端] msqid = %d\n", msqid);

    while (1) {
        if (msgrcv(msqid, &msg, CHAT_MSG_SIZE, CHAT_PEER_TYPE, 0) < 0) {
            fprintf(stderr, "msgrcv failed: %s\n", strerror(errno));
            break;
        }

        printf("\r[对方] %s\n", msg.mtext);
        printf("[我] ");
        fflush(stdout);

        if (strstr(msg.mtext, "对方已退出聊天"))
            break;
    }

    printf("\n[接收端] 退出\n");
    return 0;
}
EOF
