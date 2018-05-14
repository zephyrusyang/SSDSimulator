#include <stdio.h>

#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>

#include "nvme.h"

int wait_tcp_connect(int port)
{
    int sockfd;
    struct sockaddr_in addr;

    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    addr.sin_addr.s_addr = INADDR_ANY;
    bind(sockfd, (struct sockaddr*)&addr, sizeof(addr));

    listen(sockfd, 5);

    return sockfd;
}

int accept_tcp_connect(int sockfd)
{
    int sessionfd;
    struct sockaddr_in client;
    socklen_t len;

    len = sizeof(client);
    sessionfd = accept(sockfd, (struct sockaddr*)&client, &len);
    char str[INET_ADDRSTRLEN];
    inet_ntop(AF_INET, &client.sin_addr, str, INET_ADDRSTRLEN);
    printf("accept [%s, %d]\n", str, len);

    return sessionfd;
}

void nvme_polling_io(void) {
    int sockfd = wait_tcp_connect(5001);
    int sessionfd = accept_tcp_connect(sockfd);
    
    while(1) {
        struct nvme_command cmd;
        recv(sessionfd, &cmd, sizeof(cmd), 0);

        switch(cmd.common.opcode){
        case nvme_cmd_flush:
            printf("flush\n");
            break;

        case nvme_cmd_write:
            printf("write\n");
            break;

        case nvme_cmd_read:
            printf("read\n");
            break;

        case nvme_cmd_write_uncor:
            printf("write_unc\n");
            break;

        case nvme_cmd_compare:
            printf("compare\n");
            break;

        case nvme_cmd_write_zeroes:
            printf("write_zeroes\n");
            break;

        case nvme_cmd_dsm:
            printf("dsm\n");
            break;

        default:
            printf("default\n");
            break;
        }
    }
}

void nvme_polling_admin(void) {
    int sockfd = wait_tcp_connect(5000);
    int sessionfd = accept_tcp_connect(sockfd);
    
    while(1) {
        struct nvme_command cmd;
        recv(sessionfd, &cmd, sizeof(cmd), 0);

        switch(cmd.common.opcode){
        case nvme_admin_delete_sq:
            printf("default\n");
            break;
        case nvme_admin_create_sq:
            printf("default\n");
            break;
        case nvme_admin_get_log_page:
            printf("default\n");
            break;
        case nvme_admin_delete_cq:
            printf("default\n");
            break;
        case nvme_admin_create_cq:
            printf("default\n");
            break;
        case nvme_admin_identify:
            printf("default\n");
            break;
        case nvme_admin_abort_cmd:
            printf("default\n");
            break;
        case nvme_admin_set_features:
            printf("default\n");
            break;
        case nvme_admin_get_features:
            printf("default\n");
            break;
        case nvme_admin_async_event:
            printf("default\n");
            break;
        case nvme_admin_ns_mgmt:
            printf("default\n");
            break;
        case nvme_admin_activate_fw:
            printf("default\n");
            break;
        case nvme_admin_download_fw:
            printf("default\n");
            break;
        case nvme_admin_ns_attach:
            printf("default\n");
            break;
        case nvme_admin_keep_alive:
            printf("default\n");
            break;
        case nvme_admin_directive_send:
            printf("default\n");
            break;
        case nvme_admin_directive_recv:
            printf("default\n");
            break;
        case nvme_admin_dbbuf:
            printf("default\n");
            break;
        case nvme_admin_format_nvm:
            printf("default\n");
            break;
        case nvme_admin_security_send:
            printf("default\n");
            break;
        case nvme_admin_security_recv:
            printf("default\n");
            break;
        case nvme_admin_sanitize_nvm:
            printf("default\n");
            break;

        default:
            printf("default\n");
            break;
        }
    }
}

int main()
{
    nvme_polling_admin();
    nvme_polling_io();
}
