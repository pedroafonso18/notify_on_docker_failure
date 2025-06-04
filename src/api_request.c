#include "api_request.h"
#include <string.h>

int send_message(EnvVars vars) {
    CURL *curl = curl_easy_init();
    if (curl) {
        CURLcode res;
        struct curl_slist *headers = NULL;
        const char *data = "{\"channel\": \"#atualizacoes-qualidade\", \"text\": \"RABBITMQ PARADO @pedro.afonso\"}";
        
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