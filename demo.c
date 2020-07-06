#include <stdio.h>
#include <string.h>
#include "md5.h"
#define INPUT_BUFFER_SIZE 100 * 1024
int main(int argc, char *argv[])
{
    FILE *file;
    if (argc == 2)
    {
        md5_byte_t digest[16];
        md5_state_t md5StateT;
        md5_init(&md5StateT);
        file = fopen(argv[1], "rb");
        if (!file)
        {
            const md5_byte_t *data = argv[1];
            md5_append(&md5StateT, data, strlen(data));
            md5_finish(&md5StateT, digest);
            char md5String[33] = { '\0' }, hexBuffer[3];
            for (size_t i = 0; i != 16; ++i)
            {
                if (digest[i] < 16)
                    sprintf(hexBuffer, "0%X", digest[i]);
                else
                    sprintf(hexBuffer, "%X", digest[i]);
                strcat(md5String, hexBuffer);
            }
            printf("can't read file.\n%s:%s\n", argv[1], md5String);
        }
        else
        {
            char buffer[INPUT_BUFFER_SIZE];
            while (!feof(file))
            {
                size_t numberOfObjects = fread(buffer, sizeof(char), INPUT_BUFFER_SIZE, file);
                md5_append(&md5StateT, buffer, numberOfObjects);
            }
            md5_finish(&md5StateT, digest);
            char md5String[33] = { '\0' }, hexBuffer[3];
            for (size_t i = 0; i != 16; ++i)
            {
                if (digest[i] < 16)
                    sprintf(hexBuffer, "0%x", digest[i]);
                else
                    sprintf(hexBuffer, "%x", digest[i]);
                strcat(md5String, hexBuffer);
            }
            fclose(file);
            printf("read file.\n%s:%s\n", argv[1], md5String);
        }
    }
    return 0;
}
