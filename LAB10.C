#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct message
{
    long msg_type;
    char msg_text[100];
};

int main()
{
    FILE *fp;
    struct message msg;

    /* Producer */
    msg.msg_type = 1;
    strcpy(msg.msg_text, "Hello, message queue!");

    fp = fopen("message_queue.txt", "w");
    if (fp == NULL)
    {
        printf("Error creating file!\n");
        return 1;
    }

    fprintf(fp, "%ld\n%s", msg.msg_type, msg.msg_text);
    fclose(fp);

    printf("Producer: Data sent: %s\n", msg.msg_text);

    /* Consumer */
    fp = fopen("message_queue.txt", "r");
    if (fp == NULL)
    {
        printf("Error opening file!\n");
        return 1;
    }

    fscanf(fp, "%ld\n", &msg.msg_type);
    fgets(msg.msg_text, sizeof(msg.msg_text), fp);

    fclose(fp);

    printf("Consumer: Data received: %s\n", msg.msg_text);

    return 0;
}