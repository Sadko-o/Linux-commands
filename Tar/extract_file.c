/*
**
*/

#include "my_tar.h"

/*
**
*/

int parseoct(const char *p, size_t n)
{
    int i = 0;
    while ((*p < '0' || *p > '7') && n > 0)
    {
        ++p;
        --n;
    }
    while (*p >= '0' && *p <= '7' && n > 0)
    {
        i *= 8;
        i += *p - '0';
        ++p;
        --n;
    }
    return (i);
}

/* Returns true if this is 512 zero bytes. */
int is_end_of_archive(const char *p)
{
    int n;
    for (n = 511; n >= 0; --n)
        if (p[n] != '\0') return (0);
    return (1);
}

/* Create a directory, including parent directories as necessary. */
void create_dir(char *pathname, int mode)
{
    char *p;
    int r;

    /* Strip trailing '/' */
    if (pathname[strlen(pathname) - 1] == '/')
        pathname[strlen(pathname) - 1] = '\0';

    /* Try creating the directory. */
    r = mkdir(pathname, mode);

    if (r != 0)
    {
        /* On failure, try creating parent directory. */
        p = strrchr(pathname, '/');
        if (p != NULL)
        {
            *p = '\0';
            create_dir(pathname, 0755);
            *p = '/';
            r = mkdir(pathname, mode);
        }
    }
    if (r != 0) fprintf(stderr, "Could not create directory %s\n", pathname);
}

/* Create a file, including parent directory as necessary. */
FILE *create_file(char *pathname)
{
    FILE *f;
    f = fopen(pathname, "wb+");
    if (f == NULL)
    {
        /* Try creating parent dir and then creating file. */
        char *p = strrchr(pathname, '/');
        if (p != NULL)
        {
            *p = '\0';
            create_dir(pathname, 0755);
            *p = '/';
            f = fopen(pathname, "wb+");
        }
    }
    return (f);
}

int verify_checksum(const char *p)
{
    int n, u = 0;

    for (n = 0; n < 512; ++n)
    {
        if (n < 148 || n > 155)
        {
            /* Standard tar checksum adds unsigned bytes. Checksum offset range
             * is 148-155.*/
            u += ((unsigned char *)p)[n];
        }
        else
        {
            u += 0x20;  // 0x20 is space(ASCII - 32)
        }
        // The checksum is calculated by taking the sum of the unsigned byte
        // values of the header record with the eight checksum bytes taken to be
        // ascii spaces (decimal value 32).
    }

    return (u == parseoct(p + 148,
                          8));  // 148 is the offset for chksum[8] in tar_header
}

void untar(FILE *a, const char *path)
{
    char buff[512];
    FILE *f = NULL;
    size_t bytes_read;
    int filesize;

    printf("Extracting from %s\n", path);
    for (;;)
    {
        bytes_read = fread(buff, 1, 512, a);
        if (bytes_read < 512)
        {
            fprintf(stderr, "Short read on %s: expected 512, got %d\n", path,
                    (int)bytes_read);
            return;
        }
        if (is_end_of_archive(buff))
        {
            printf("End of %s\n", path);
            return;
        }
        if (!verify_checksum(buff))
        {
            fprintf(stderr, "Checksum failure\n");
            return;
        }
        filesize = parseoct(buff + 124, 12);
        switch (buff[156])
        {
            case '1':
                printf(" Ignoring hardlink %s\n", buff);
                break;
            case '2':
                printf(" Ignoring symlink %s\n", buff);
                break;
            case '3':
                printf(" Ignoring character device %s\n", buff);
                break;
            case '4':
                printf(" Ignoring block device %s\n", buff);
                break;
            case '5':
                printf(" Extracting dir %s\n", buff);
                create_dir(buff, parseoct(buff + 100, 8));
                filesize = 0;
                break;
            case '6':
                printf(" Ignoring FIFO %s\n", buff);
                break;
            default:
                printf(" Extracting file %s\n", buff);
                f = create_file(buff);
                break;
        }
        while (filesize > 0)
        {
            bytes_read = fread(buff, 1, 512, a);
            if (bytes_read < 512)
            {
                fprintf(stderr, "Short read on %s: Expected 512, got %d\n",
                        path, (int)bytes_read);
                return;
            }
            if (filesize < 512) bytes_read = filesize;
            if (f != NULL)
            {
                if (fwrite(buff, 1, bytes_read, f) != bytes_read)
                {
                    fprintf(stderr, "Failed write\n");
                    fclose(f);
                    f = NULL;
                }
            }
            filesize -= bytes_read;
        }
        if (f != NULL)
        {
            fclose(f);
            f = NULL;
        }
    }
}

int extract_archive(char **argv)
{
    FILE *a;

    ++argv; /* Skip program name */
    ++argv;
    for (; *argv != NULL; ++argv)
    {
        a = fopen(*argv, "r");
        if (a == NULL)
            fprintf(stderr, "Unable to open %s\n", *argv);
        else
        {
            untar(a, *argv);
            fclose(a);
        }
    }

    return 0;
}