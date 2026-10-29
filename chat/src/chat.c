cat > chat/src/chat.c << 'EOF'
#include "chat.h"

key_t chat_get_key(void)
{
    key_t key;

    key = ftok(CHAT_PATH, CHAT_PROJ_ID);
    if (key == (key_t)-1) {
        fprintf(stderr, "ftok failed: %s\n", strerror(errno));
        exit(EXIT_FAILURE);
    }
    return key;
}

int chat_msgget(key_t key, int create)
{
    int msqid;
    int flags = 0666;

    if (create)
        flags |= IPC_CREAT | IPC_EXCL;

    msqid = msgget(key, flags);
    if (msqid < 0) {
        if (create && errno == EEXIST) {
            fprintf(stderr, "消息队列已存在，正在复用...\n");
            msqid = msgget(key, 0666);
        }
        if (msqid < 0) {
            fprintf(stderr, "msgget failed: %s\n", strerror(errno));
            exit(EXIT_FAILURE);
        }
    }
    return msqid;
}
EOF
