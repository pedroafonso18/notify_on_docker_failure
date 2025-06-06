#include "api_request.h"
#include <string.h>
#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <netdb.h>

static char* get_local_ip() {
    static char ip[INET_ADDRSTRLEN];
    int sock = socket(AF_INET, SOCK_DGRAM, 0);
    if (sock < 0) {
        return "unknown";
    }

    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(53);
    addr.sin_addr.s_addr = inet_addr("8.8.8.8");

    if (connect(sock, (struct sockaddr*)&addr, sizeof(addr)) < 0) {
        close(sock);
        return "unknown";
    }

    struct sockaddr_in local_addr;
    socklen_t len = sizeof(local_addr);
    if (getsockname(sock, (struct sockaddr*)&local_addr, &len) < 0) {
        close(sock);
        return "unknown";
    }

    close(sock);
    inet_ntop(AF_INET, &local_addr.sin_addr, ip, INET_ADDRSTRLEN);
    return ip;
}

int send_message(EnvVars vars, const char* container_name) {
    CURL *curl = curl_easy_init();
    if (curl) {
        CURLcode res;
        struct curl_slist *headers = NULL;
        char data[512];
        const char* local_ip = get_local_ip();
        
        snprintf(data, sizeof(data), 
                "{\"channel\": \"#atualizacoes-containers\", \"text\": \"Container %s PARADO @pedro.afonso (IP: %s)\"}", 
                container_name, local_ip);
        
        char auth_header[100];
        char user_header[100];
        snprintf(auth_header, sizeof(auth_header), "X-Auth-Token: %s", vars.xauth);
        snprintf(user_header, sizeof(user_header), "X-User-Id: %s", vars.xuser);
        
        headers = curl_slist_append(headers, auth_header);
        headers = curl_slist_append(headers, user_header);
        headers = curl_slist_append(headers, "Content-Type: application/json");
        
        curl_easy_setopt(curl, CURLOPT_URL, "http://meuconsig.app.br/api/v1/chat.postMessage");
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, data);
        
        res = curl_easy_perform(curl);
        
        curl_slist_free_all(headers);
        curl_easy_cleanup(curl);
        
        if (res != CURLE_OK) {
            printf("curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
            return 0;
        }
        return 1;
    }
    return 0;
}