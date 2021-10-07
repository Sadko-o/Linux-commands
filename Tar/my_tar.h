/*
**
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdbool.h>
#include <tar.h>
#include <pwd.h>
#include <grp.h>
#include <dirent.h>
#include <time.h>

#define OCTAL_BASE 8
#define DEC_BASE 10
#define BLOCKSIZE 512

#define TMAGIC   "ustar"        /* ustar and a null */
#define TMAGLEN  6
#define TVERSION "00"           /* 00 and no null */
#define TVERSLEN 2

#define REGTYPE  '0'            /* regular file */
#define AREGTYPE '\0'           /* regular file */
#define LNKTYPE  '1'            /* link */
#define SYMTYPE  '2'            /* reserved */
#define CHRTYPE  '3'            /* character special */
#define BLKTYPE  '4'            /* block special */
#define DIRTYPE  '5'            /* directory */
#define FIFOTYPE '6'            /* FIFO special */
#define CONTTYPE '7'            /* reserved */

/*
**
*/

typedef struct posix_header
{                              /* byte offset */
  char name[100];               /*   0 */
  char mode[8];                 /* 100 */
  char uid[8];                  /* 108 */ 
  char gid[8];                  /* 116 */ 
  char size[12];                /* 124 */  
  char mtime[12];               /* 136 */ 
  char chksum[8];               /* 148 */  
  char typeflag;                /* 156 */  
  char linkname[100];           /* 157 */  
  char magic[6];                /* 257 */  
  char version[2];              /* 263 */  
  char uname[32];               /* 265 */  
  char gname[32];               /* 297 */   
  char devmajor[8];             /* 329 */  
  char devminor[8];             /* 337 */  
  char prefix[155];             /* 345 */  
                                /* 500 */
} tar_header;

typedef struct s_node
{
    tar_header value;
    bool should_add; // true by default, false when file should not be added into tar
    struct s_node *next;
} header_node;

typedef struct s_opt
{
    bool create;
    bool extract;
    bool add;
    bool list;
    bool add_if_u;
    char *archive_name;
    struct s_argument *args;
} tar_options;

typedef struct s_argument
{
    char *filename;
    struct s_argument *next;
} t_argument;


//my.c
char* my_strncpy(char* dest, char* src, int num);
void my_memset(char* buff, char c, int size);
void my_bzero(char* buff, int size);
char* my_init(int size);
int my_strcmp(char* first, char* second);
int my_strlen(char* input);
char* my_strdup(char* input);
char* my_join(char* first_part, char* second_part, char* third_part);
char* my_copy_and_join(char* dest, char* first_part, char* second_part, char* third_part);

//converter.c
long my_atoi(char *str);
long my_atol(const char *str, int size);
char *my_itoa_base(char *res, unsigned int number, int size, int base);
int my_iterative_pow(int a, int b);
long dec_to_oct(long dec);
long oct_to_dec(long oct);

//creat_file.c
tar_header *init_tar_header();
tar_header *get_metadata(char *filename);
int get_permission(int mode);
char get_typeflag(int mode);
int get_file_size(int fd);
int check_sum(tar_header *header);
char *chksum_str(char *number_str, char *dest, int num);
int write_file_content(int fd_archive, char *filename);
void end_of_archive(int fd);
int create_archive(int fd_archive, tar_options *options);

// get_opt.c
tar_options *get_opt(int, char **);
void delete_options(tar_options *);

// list.c
void list_archive(tar_options *options);
void print_args_in_arch(tar_options *options);
void print_list(tar_options *options);
void print_unfound_files(header_node* args_list);
void print_args_in_arch(tar_options *options);
void init_should_add(header_node* args_list);
void check_arg_in_archive(header_node* args_list, tar_header arch_current_header);

// file_manipulation.c
int is_directory(char* name);
int open_archive_file(tar_options *options);

// arg_manipulation.c
t_argument *init_argument();
void add_to_list(t_argument **t_arg, char *current_file);
void put_file_to_list(t_argument **t_arg, char *filename);
void delete_argument_list(t_argument **ptr);

// add to archive.c
int number_from_oct(char* oct_str);
header_node* prepend_to_list(tar_header node, header_node* head);
header_node* options_to_headers(tar_options* options);
bool should_skip(tar_header origin, tar_header for_replace);
int calc_next_position(int position, tar_header header); // <<<<<< POINTER
void free_list(header_node* head);
void mark_for_skip(tar_header header, header_node* list);
int add_to_archive(int fd_archive, tar_options *options);
int add_if_modifided(int fd_archive, tar_options *options);

// extract_file.c
int parseoct(const char *p, size_t n);
int is_end_of_archive(const char *p);
void create_dir(char *pathname, int mode);
FILE * create_file(char *pathname);
int verify_checksum(const char *p);
void untar(FILE *a, const char *path);
int extract_archive(char **argv);