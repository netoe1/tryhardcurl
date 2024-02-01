#include <stdio.h>
#include <stdlib.h>
#include <curl/curl.h>
#include <string.h>
#define TIMEOUT_AMOUNT 1
CURL *curl = NULL;
int times = -5;

size_t write_callback(void *contents, size_t size, size_t nmemb, void *userp)
{
    size_t total_size = size * nmemb;
    printf("%.*s", (int)total_size, (char *)contents);
    return total_size;
}
int main(int argc, char **argv)
{
    if (argc != 4)
    {
        printf("\ntryhardcurl> Invalid Syntax. Type help to see valid commands\n");
        exit(EXIT_FAILURE);
    }

    if (strcmp("try", argv[1]) == 0)
    {
        if (argv[2] != NULL || argv[2][0] != '\0')
        {
            if (argv[3] != NULL && argv[3][0] != '\0')
            {

                curl_global_init(CURL_GLOBAL_DEFAULT);
                curl = curl_easy_init();
                times = atoi(argv[3]);

                if (times <= 0)
                {
                    fprintf(stderr, "\ntryhardcurl> Invalid value to times buffer.\n");
                    return -1;
                }
                if (!curl)
                {
                    fprintf(stderr, "\ntryhardcurl> Error to init libcurl module.\n");
                    return -1;
                }

                curl_easy_setopt(curl, CURLOPT_URL, argv[2]);
                curl_easy_setopt(curl, CURLOPT_CONNECTTIMEOUT, 30);
                curl_easy_setopt(curl, CURLOPT_TIMEOUT, 1);
                //curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
                int counter = 0;
                CURLcode res;
                while (counter < times)
                {
                    res = curl_easy_perform(curl);
                    printf("\ntryhardcurl> Trying hard req[%d]...\n", counter + 1);
                    counter++;
                }

                // Verifica se houve algum erro
                if (res != CURLE_OK)
                {
                    fprintf(stderr, "\nError on requisition: %s\n", curl_easy_strerror(res));
                }

                // Libera os recursos
                curl_easy_cleanup(curl);

                // Finaliza o libcurl
                curl_global_cleanup();
                times = atoi(argv[3]);
            }
            else
            {
                fprintf(stderr, "\ntryhardcurl> You didn't set times.");
                return -1;
            }
        }
        else
        {
            fprintf(stderr, "\ntryhardcurl> You didn't set IP address.");
            return -1;
        }
    }
    else if (strcmp("help", argv[1]) == 0)
    {
        printf("\ntryhardcurl> Valid commands below!");
        exit(EXIT_SUCCESS);
    }
    else
    {
        fprintf(stderr, "\ntryhardcurl> You set an invalid command.");
        return -1;
    }
    return 0;
}
