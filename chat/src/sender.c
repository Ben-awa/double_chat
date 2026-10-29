cat > chat/src/sender.c << 'EOF'
#include "chat.h"

int main(void)
{
    key_t key;
    int msqid;
    struct chat_msg msg;

    key = chat_get_key();
    msqid = chat_msgget(key, 1);

    printf("[发送端] 启动，输入文本后回车发送，输入 quit 退出\n");
    printf("[发送端] msqid = %d\n", msqid);

    while (1) {
        printf("[我] ");
        fflush(stdout);

        if (!fgets(msg.mtext, CHAT_MSG_SIZE, stdin))
            break;

        msg.mtext[strcspn(msg.mtext, "\n")] = '\0';

        if (strcmp(msg.mtext, "quit") == 0) {
            strcpy(msg.mtext, "对方已退出聊天");
            msg.mtype = CHAT_PEER_TYPE;
            msgsnd(msqid, &msg, strlen(msg.mtext) + 1, 0);
            break;
        }

        msg.mtype = CHAT_MY_TYPE;
        if (msgsnd(msqid, &msg, strlen(msg.mtext) + 1, 0) < 0) {
            fprintf(stderr, "msgsnd failed: %s\n", strerror(errno));
            break;
        }
    }

    printf("[发送端] 退出\n");
    return 0;
}
EOF
