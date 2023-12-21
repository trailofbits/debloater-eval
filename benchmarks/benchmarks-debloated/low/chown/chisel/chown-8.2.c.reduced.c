typedef unsigned long size_t;
typedef long __off_t;
typedef long __off64_t;
struct _IO_FILE;
struct _IO_FILE;
struct _IO_FILE;
typedef struct _IO_FILE FILE;
typedef void _IO_lock_t;
struct _IO_marker {
  struct _IO_marker *_next;
  struct _IO_FILE *_sbuf;
  int _pos;
};
struct _IO_FILE {
  int _flags;
  char *_IO_read_ptr;
  char *_IO_read_end;
  char *_IO_read_base;
  char *_IO_write_base;
  char *_IO_write_ptr;
  char *_IO_write_end;
  char *_IO_buf_base;
  char *_IO_buf_end;
  char *_IO_save_base;
  char *_IO_backup_base;
  char *_IO_save_end;
  struct _IO_marker *_markers;
  struct _IO_FILE *_chain;
  int _fileno;
  int _flags2;
  __off_t _old_offset;
  unsigned short _cur_column;
  signed char _vtable_offset;
  char _shortbuf[1];
  _IO_lock_t *_lock;
  __off64_t _offset;
  void *__pad1;
  void *__pad2;
  void *__pad3;
  void *__pad4;
  size_t __pad5;
  int _mode;
  char _unused2[(15UL * sizeof(int) - 4UL * sizeof(void *)) - sizeof(size_t)];
};
typedef long __time_t;
typedef unsigned long __dev_t;
typedef unsigned int __uid_t;
typedef unsigned int __gid_t;
typedef unsigned long __ino_t;
typedef unsigned int __mode_t;
typedef unsigned long __nlink_t;
typedef long __blksize_t;
typedef long __blkcnt_t;
typedef long __syscall_slong_t;
typedef __mode_t mode_t;
struct timespec {
  __time_t tv_sec;
  __syscall_slong_t tv_nsec;
};
struct stat {
  __dev_t st_dev;
  __ino_t st_ino;
  __nlink_t st_nlink;
  __mode_t st_mode;
  __uid_t st_uid;
  __gid_t st_gid;
  int __pad0;
  __dev_t st_rdev;
  __off_t st_size;
  __blksize_t st_blksize;
  __blkcnt_t st_blocks;
  struct timespec st_atim;
  struct timespec st_mtim;
  struct timespec st_ctim;
  __syscall_slong_t __glibc_reserved[3];
};
typedef __ino_t ino_t;
typedef __dev_t dev_t;
struct hash_table;
struct hash_table;
struct hash_table;
typedef struct hash_table Hash_table;
struct F_triple {
  char *name;
  ino_t st_ino;
  dev_t st_dev;
};
struct __dirstream;
struct __dirstream;
struct __dirstream;
typedef struct __dirstream DIR;
typedef int wchar_t;
union __anonunion___value_4 {
  unsigned int __wch;
  char __wchb[4];
};
struct __anonstruct___mbstate_t_3 {
  int __count;
  union __anonunion___value_4 __value;
};
typedef struct __anonstruct___mbstate_t_3 __mbstate_t;
typedef unsigned int wint_t;
struct hash_tuning {
  float shrink_threshold;
  float shrink_factor;
  float growth_threshold;
  float growth_factor;
  _Bool is_n_buckets;
};
typedef struct hash_tuning Hash_tuning;
typedef __mbstate_t mbstate_t;
struct mbchar {
  char const *ptr;
  size_t bytes;
  _Bool wc_valid;
  wchar_t wc;
  char buf[24];
};
struct mbuiter_multi {
  _Bool in_shift;
  mbstate_t state;
  _Bool next_done;
  struct mbchar cur;
};
typedef struct mbuiter_multi mbui_iterator_t;
typedef __gid_t gid_t;
typedef __uid_t uid_t;
typedef unsigned long uintmax_t;
struct dev_ino {
  ino_t st_ino;
  dev_t st_dev;
};
struct cycle_check_state {
  struct dev_ino dev_ino;
  uintmax_t chdir_counter;
  int magic;
};
typedef long ptrdiff_t;
struct dirent {
  __ino_t d_ino;
  __off_t d_off;
  unsigned short d_reclen;
  unsigned char d_type;
  char d_name[256];
};
typedef __builtin_va_list __gnuc_va_list;
typedef __gnuc_va_list va_list;
enum quoting_style {
  literal_quoting_style = 0,
  shell_quoting_style = 1,
  shell_always_quoting_style = 2,
  c_quoting_style = 3,
  c_maybe_quoting_style = 4,
  escape_quoting_style = 5,
  locale_quoting_style = 6,
  clocale_quoting_style = 7,
  custom_quoting_style = 8
};
enum strtol_error {
  LONGINT_OK = 0,
  LONGINT_OVERFLOW = 1,
  LONGINT_INVALID_SUFFIX_CHAR = 2,
  LONGINT_INVALID_SUFFIX_CHAR_WITH_OVERFLOW = 3,
  LONGINT_INVALID = 4
};
typedef enum strtol_error strtol_error;
struct option {
  char const *name;
  int has_arg;
  int *flag;
  int val;
};
typedef long intmax_t;
typedef __nlink_t nlink_t;
struct I_ring {
  int ir_data[4];
  int ir_default_val;
  unsigned int ir_front;
  unsigned int ir_back;
  _Bool ir_empty;
};
typedef struct I_ring I_ring;
struct _ftsent;
struct _ftsent;
struct _ftsent;
union __anonunion_fts_cycle_29 {
  struct hash_table *ht;
  struct cycle_check_state *state;
};
struct __anonstruct_FTS_28 {
  struct _ftsent *fts_cur;
  struct _ftsent *fts_child;
  struct _ftsent **fts_array;
  dev_t fts_dev;
  char *fts_path;
  int fts_rfd;
  int fts_cwd_fd;
  size_t fts_pathlen;
  size_t fts_nitems;
  int (*fts_compar)(struct _ftsent const **, struct _ftsent const **);
  int fts_options;
  struct hash_table *fts_leaf_optimization_works_ht;
  union __anonunion_fts_cycle_29 fts_cycle;
  I_ring fts_fd_ring;
};
typedef struct __anonstruct_FTS_28 FTS;
struct _ftsent {
  struct _ftsent *fts_cycle;
  struct _ftsent *fts_parent;
  struct _ftsent *fts_link;
  long fts_number;
  void *fts_pointer;
  char *fts_accpath;
  char *fts_path;
  int fts_errno;
  int fts_symfd;
  size_t fts_pathlen;
  FTS *fts_fts;
  ptrdiff_t fts_level;
  size_t fts_namelen;
  nlink_t fts_n_dirs_remaining;
  unsigned short fts_info;
  unsigned short fts_flags;
  unsigned short fts_instr;
  struct stat fts_statp[1];
  char fts_name[1];
};
typedef struct _ftsent FTSENT;
struct passwd {
  char *pw_name;
  char *pw_passwd;
  __uid_t pw_uid;
  __gid_t pw_gid;
  char *pw_gecos;
  char *pw_dir;
  char *pw_shell;
};
struct group {
  char *gr_name;
  char *gr_passwd;
  __gid_t gr_gid;
  char **gr_mem;
};
typedef unsigned long reg_syntax_t;
struct quoting_options;
struct quoting_options;
struct quoting_options;
struct quoting_options {
  enum quoting_style style;
  int flags;
  unsigned int quote_these_too[255UL / (sizeof(int) * 8UL) + 1UL];
  char const *left_quote;
  char const *right_quote;
};
struct slotvec {
  size_t size;
  char *val;
};
struct hash_entry {
  void *data;
  struct hash_entry *next;
};
struct hash_table {
  struct hash_entry *bucket;
  struct hash_entry const *bucket_limit;
  size_t n_buckets;
  size_t n_buckets_used;
  size_t n_entries;
  Hash_tuning const *tuning;
  size_t (*hasher)(void const *, size_t);
  _Bool (*comparator)(void const *, void const *);
  void (*data_freer)(void *);
  struct hash_entry *free_entry_list;
};
struct __anonstruct___fsid_t_1 {
  int __val[2];
};
typedef struct __anonstruct___fsid_t_1 __fsid_t;
typedef unsigned long __fsblkcnt_t;
typedef unsigned long __fsfilcnt_t;
typedef long __fsword_t;
struct Active_dir {
  dev_t dev;
  ino_t ino;
  FTSENT *fts_ent;
};
struct statfs {
  __fsword_t f_type;
  __fsword_t f_bsize;
  __fsblkcnt_t f_blocks;
  __fsblkcnt_t f_bfree;
  __fsblkcnt_t f_bavail;
  __fsfilcnt_t f_files;
  __fsfilcnt_t f_ffree;
  __fsid_t f_fsid;
  __fsword_t f_namelen;
  __fsword_t f_frsize;
  __fsword_t f_flags;
  __fsword_t f_spare[4];
};
struct LCO_ent {
  dev_t st_dev;
  _Bool opt_ok;
};
enum Change_status {
  CH_NOT_APPLIED = 1,
  CH_SUCCEEDED = 2,
  CH_FAILED = 3,
  CH_NO_CHANGE_REQUESTED = 4
};
enum Verbosity { V_high = 0, V_changes_only = 1, V_off = 2 };
struct Chown_option {
  enum Verbosity verbosity;
  _Bool recurse;
  struct dev_ino *root_dev_ino;
  _Bool affect_symlink_referent;
  _Bool force_silent;
  char *user_name;
  char *group_name;
};
enum RCH_status {
  RC_ok = 2,
  RC_excluded = 3,
  RC_inode_changed = 4,
  RC_do_ordinary_chown = 5,
  RC_error = 6
};
extern __attribute__((__nothrow__)) int *(
    __attribute__((__leaf__)) __errno_location)(void)__attribute__((__const__));
extern int close(int __fd);
extern int(__attribute__((__nonnull__(1))) open)(char const *__file,
                                                 int __oflag, ...);
extern __attribute__((__nothrow__)) int(__attribute__((__leaf__))
                                        tolower)(int __c);
extern __attribute__((__nothrow__))
size_t(__attribute__((__nonnull__(1), __leaf__)) strlen)(char const *__s)
    __attribute__((__pure__));
extern int fclose(FILE *__stream);
int dup_safer(int fd);
extern __attribute__((__nothrow__)) int(
    __attribute__((__nonnull__(1, 2), __leaf__))
    strcmp)(char const *__s1, char const *__s2) __attribute__((__pure__));
extern __attribute__((__nothrow__)) int(
    __attribute__((__nonnull__(1, 2), __leaf__))
    strncmp)(char const *__s1, char const *__s2, size_t __n)
    __attribute__((__pure__));
__attribute__((__noreturn__)) void xalloc_die(void);
extern __attribute__((__nothrow__)) void *(__attribute__((__leaf__))
                                           malloc)(size_t __size)
    __attribute__((__malloc__));
char *last_component(char const *name);
extern __attribute__((__nothrow__)) char *(__attribute__((__leaf__))
                                           gettext)(char const *__msgid)
    __attribute__((__format_arg__(1)));
void *hash_lookup(Hash_table const *table___0, void const *entry);
void *(__attribute__((__warn_unused_result__))
       hash_insert)(Hash_table *table___0, void const *entry);
void triple_free(void *x);
void *xmalloc(size_t n) __attribute__((__malloc__));
char *xstrdup(char const *string) __attribute__((__malloc__));
extern DIR *fdopendir(int __fd);
DIR *rpl_fdopendir(int fd);
extern
    __attribute__((__nothrow__)) int(__attribute__((__nonnull__(2), __leaf__))
                                     fstat)(int __fd, struct stat *__buf);
DIR *rpl_fdopendir(int fd) {

  DIR *tmp___1;

  {

    tmp___1 = fdopendir(fd);
    return (tmp___1);
  }
}
int fd_safer(int fd);
int fd_safer(int fd) { return (fd); }

int volatile exit_failure = (int volatile)1;
extern __attribute__((__nothrow__)) unsigned short const **(
    __attribute__((__leaf__)) __ctype_b_loc)(void)__attribute__((__const__));
extern __attribute__((__nothrow__)) int(__attribute__((__leaf__))
                                        ferror_unlocked)(FILE *__stream);
extern __attribute__((__nothrow__))
size_t(__attribute__((__leaf__)) __ctype_get_mb_cur_max)(void);
extern __attribute__((__nothrow__)) void(__attribute__((__leaf__))
                                         free)(void *__ptr);
extern __attribute__((__nothrow__, __noreturn__)) void(__attribute__((__leaf__))
                                                       abort)(void);
extern
    __attribute__((__nothrow__)) void *(__attribute__((__nonnull__(1),
                                                       __leaf__))
                                        memset)(void *__s, int __c, size_t __n);
extern __attribute__((__nothrow__)) char *(__attribute__((__nonnull__(1),
                                                          __leaf__))
                                           strchr)(char const *__s, int __c)
    __attribute__((__pure__));
extern __attribute__((__nothrow__)) char *(__attribute__((__nonnull__(1),
                                                          __leaf__))
                                           strrchr)(char const *__s, int __c)
    __attribute__((__pure__));
int mbscasecmp(char const *s1, char const *s2);
extern __attribute__((__nothrow__))
wint_t(__attribute__((__leaf__)) towlower)(wint_t __wc);
size_t hash_string(char const *string, size_t n_buckets);
Hash_table *(__attribute__((__warn_unused_result__))
             hash_initialize)(size_t candidate, Hash_tuning const *tuning,
                              size_t (*hasher)(void const *, size_t),
                              _Bool (*comparator)(void const *, void const *),
                              void (*data_freer)(void *));
void hash_free(Hash_table *table___0);
extern __attribute__((__nothrow__, __noreturn__)) void(__attribute__((
    __leaf__)) __assert_fail)(char const *__assertion, char const *__file,
                              unsigned int __line, char const *__function);
extern __attribute__((__nothrow__)) int(__attribute__((__leaf__))
                                        mbsinit)(mbstate_t const *__ps)
    __attribute__((__pure__));
extern __attribute__((__nothrow__))
size_t(__attribute__((__leaf__))
       mbrtowc)(wchar_t *__restrict __pwc, char const *__restrict __s,
                size_t __n, mbstate_t *__restrict __p);

size_t strnlen1(char const *string, size_t maxlen);

void *xrealloc(void *p, size_t n);
extern int fcntl(int __fd, int __cmd, ...);
int dup_safer(int fd) {
  int tmp;

  {
    tmp = fcntl(fd, 0, 3);
    return (tmp);
  }
}
extern __attribute__((__nothrow__)) void *(
    __attribute__((__nonnull__(1, 2), __leaf__))
    memcpy)(void *__restrict __dest, void const *__restrict __src, size_t __n);
extern __attribute__((__nothrow__)) int(
    __attribute__((__nonnull__(1, 2), __leaf__))
    stat)(char const *__restrict __file, struct stat *__restrict __buf);
extern __attribute__((__nothrow__)) int(__attribute__((__leaf__))
                                        fchown)(int __fd, __uid_t __owner,
                                                __gid_t __group);

void cycle_check_init(struct cycle_check_state *state);
_Bool cycle_check(struct cycle_check_state *state, struct stat const *sb);

extern void error(int __status, int __errnum, char const *__format, ...);
char const *quote(char const *name);
void close_stdout(void);

extern __attribute__((__noreturn__)) void _exit(int __status);
int close_stream(FILE *stream);
char *quotearg_colon(char const *arg);

void close_stdout(void) {
  char const *write_error;
  char const *tmp;

  int *tmp___2;

  {

    tmp = (char const *)gettext("write error");
    write_error = tmp;

    {
      tmp___2 = __errno_location();
      error(0, *tmp___2, "%s", write_error);
    }
  }
}
extern __attribute__((__nothrow__))
size_t(__attribute__((__leaf__)) __fpending)(FILE *__fp);

int set_cloexec_flag(int desc, _Bool value);

extern __attribute__((__nothrow__)) int(__attribute__((__leaf__))
                                        fchdir)(int __fd);
extern int(__attribute__((__nonnull__(2))) openat)(int __fd, char const *__file,
                                                   int __oflag, ...);
extern __attribute__((__nothrow__)) void *(
    __attribute__((__nonnull__(1), __leaf__))
    memchr)(void const *__s, int __c, size_t __n) __attribute__((__pure__));
extern __attribute__((__nothrow__)) void *(
    __attribute__((__nonnull__(1, 2), __leaf__))
    memmove)(void *__dest, void const *__src, size_t __n);
extern __attribute__((__nothrow__)) int(
    __attribute__((__nonnull__(1, 2), __leaf__))
    lstat)(char const *__restrict __file, struct stat *__restrict __buf);
size_t triple_hash(void const *x, size_t table_size);
_Bool triple_compare_ino_str(void const *x, void const *y);

extern __attribute__((__nothrow__)) int(
    __attribute__((__nonnull__(1, 2), __leaf__))
    memcmp)(void const *__s1, void const *__s2, size_t __n)
    __attribute__((__pure__));
extern int(__attribute__((__nonnull__(1))) closedir)(DIR *__dirp);
extern struct dirent *(__attribute__((__nonnull__(1))) readdir)(DIR *__dirp);
DIR *opendir_safer(char const *name);

extern int fprintf(FILE *__restrict __stream, char const *__restrict __format,
                   ...);
char *quotearg_n_style(int n, enum quoting_style s, char const *arg);
char const *quote_n(int n, char const *name);
__attribute__((__noreturn__)) void usage(int status);
extern
    __attribute__((__nothrow__)) void *(__attribute__((__warn_unused_result__,
                                                       __leaf__))
                                        realloc)(void *__ptr, size_t __size);
__inline static void *xnmalloc(size_t n, size_t s) __attribute__((__malloc__));
__inline static void *xnmalloc(size_t n, size_t s) __attribute__((__malloc__));

strtol_error xstrtoul(char const *s, char **ptr, int strtol_base,
                      unsigned long *val, char const *valid_suffixes);
extern __attribute__((__nothrow__)) unsigned long(__attribute__((
    __nonnull__(1), __leaf__)) strtoul)(char const *__restrict __nptr,
                                        char **__restrict __endptr, int __base);

void *xmemdup(void const *p, size_t s) __attribute__((__malloc__));
extern
    __attribute__((__nothrow__)) void *(__attribute__((__leaf__))
                                        calloc)(size_t __nmemb, size_t __size)
        __attribute__((__malloc__));
void *xmalloc(size_t n) __attribute__((__malloc__));
void *xmalloc(size_t n) {
  void *p;
  void *tmp;

  {
    tmp = malloc(n);
    p = tmp;
    if (!p) {

      xalloc_die();
    }
    return (p);
  }
}

void *xmemdup(void const *p, size_t s) __attribute__((__malloc__));
void *xmemdup(void const *p, size_t s) {
  void *tmp;
  void *tmp___0;

  {
    tmp = xmalloc(s);
    tmp___0 = memcpy(tmp, p, s);
    return (tmp___0);
  }
}
char *xstrdup(char const *string) __attribute__((__malloc__));
char *xstrdup(char const *string) {
  size_t tmp;
  char *tmp___0;

  {
    tmp = strlen(string);
    tmp___0 = (char *)xmemdup((void const *)string, tmp + 1UL);
    return (tmp___0);
  }
}
__attribute__((__nothrow__))
FTS *(__attribute__((__warn_unused_result__, __leaf__))
      fts_open)(char *const *argv, int options,
                int (*compar)(FTSENT const **, FTSENT const **));
FTS *xfts_open(char *const *argv, int options,
               int (*compar)(FTSENT const **, FTSENT const **));
_Bool cycle_warning_required(FTS const *fts, FTSENT const *ent);
FTS *xfts_open(char *const *argv, int options,
               int (*compar)(FTSENT const **, FTSENT const **)) {
  FTS *fts;
  FTS *tmp;

  {
    tmp = fts_open(argv, options | 512, compar);
    fts = tmp;

    return (fts);
  }
}

__attribute__((__noreturn__)) void xalloc_die(void);
void xalloc_die(void) {
  char *tmp;

  {
    tmp = gettext("memory exhausted");
    error((int)exit_failure, 0, "%s", tmp);
  }
}
extern int printf(char const *__restrict __format, ...);
extern int fputs_unlocked(char const *__restrict __s,
                          FILE *__restrict __stream);

void version_etc_arn(FILE *stream, char const *command_name,
                     char const *package, char const *version,
                     char const *const *authors, size_t n_authors);
void version_etc_va(FILE *stream, char const *command_name, char const *package,
                    char const *version, va_list authors);
void version_etc(FILE *stream, char const *command_name, char const *package,
                 char const *version, ...) __attribute__((__sentinel__));

void version_etc(FILE *stream, char const *command_name, char const *package,
                 char const *version, ...) __attribute__((__sentinel__));

char const *parse_user_spec(char const *spec, uid_t *uid, gid_t *gid,
                            char **username, char **groupname);
extern void endpwent(void);
extern struct passwd *getpwnam(char const *__name);
extern void endgrent(void);
extern struct group *getgrgid(__gid_t __gid);
extern struct group *getgrnam(char const *__name);
char *(__attribute__((__warn_unused_result__)) umaxtostr)(uintmax_t i,
                                                          char *buf___1);
static char const *parse_with_separator(char const *spec, char const *separator,
                                        uid_t *uid, gid_t *gid, char **username,
                                        char **groupname);
static char const *E_invalid_user = "invalid user";

static char const *parse_with_separator(char const *spec, char const *separator,
                                        uid_t *uid, gid_t *gid, char **username,
                                        char **groupname) {
  char const *error_msg;
  struct passwd *pwd;
  struct group *grp;
  char *u;
  char const *g;

  gid_t gnum;

  size_t ulen;
  struct passwd *tmp___0;

  struct group *tmp___6;

  char const *tmp___9;

  {

    error_msg = (char const *)((void *)0);

    if ((unsigned long)separator == (unsigned long)((void *)0)) {

      u = xstrdup(spec);

    } else {
      ulen = (size_t)(separator - spec);
      {
        u = (char *)xmemdup((void const *)spec, ulen + 1UL);
        *(u + ulen) = (char)'\000';
      }
    }

    { g = separator + 1; }
    {

      {
        tmp___0 = getpwnam((char const *)u);
        pwd = tmp___0;
      }
      if ((unsigned long)pwd == (unsigned long)((void *)0)) {

        error_msg = E_invalid_user;

      } else {
      }
    }
    {
      if ((unsigned long)error_msg == (unsigned long)((void *)0)) {

        {
          tmp___6 = getgrnam(g);
          grp = tmp___6;
        }

        { gnum = grp->gr_gid; }
      }
    }
    { *gid = gnum; }

    free((void *)u);
    tmp___9 = (char const *)gettext(error_msg);
    return (tmp___9);
  }
}
char const *parse_user_spec(char const *spec, uid_t *uid, gid_t *gid,
                            char **username, char **groupname) {
  char const *colon;
  char const *tmp;
  char const *error_msg;
  char const *tmp___0;

  {
    tmp = (char const *)strchr(spec, ':');
    colon = tmp;
    tmp___0 = parse_with_separator(spec, colon, uid, gid, username, groupname);
    error_msg = tmp___0;

    return (error_msg);
  }
}

#pragma weak pthread_key_create
#pragma weak pthread_getspecific
#pragma weak pthread_setspecific
#pragma weak pthread_key_delete
#pragma weak pthread_self
#pragma weak pthread_cancel

int open_safer(char const *file, int flags, ...);
struct dev_ino *get_root_dev_ino(struct dev_ino *root_d_i);

int set_char_quoting(struct quoting_options *o, char c, int i);
char *quotearg_char(char const *arg, char ch);
char *quotearg_char_mem(char const *arg, size_t argsize, char ch);
__inline static char *xcharalloc(size_t n) __attribute__((__malloc__));
__inline static char *xcharalloc(size_t n) __attribute__((__malloc__));

extern __attribute__((__nothrow__)) int(__attribute__((__leaf__))
                                        iswprint)(wint_t __wc);

static char const *gettext_quote(char const *msgid, enum quoting_style s) {
  char const *translation;
  char const *tmp;

  {
    tmp = (char const *)gettext(msgid);
    translation = tmp;

    return (translation);
  }
}
static size_t
quotearg_buffer_restyled(char *buffer, size_t buffersize, char const *arg,
                         size_t argsize, enum quoting_style quoting_style,
                         int flags, unsigned int const *quote_these_too,
                         char const *left_quote, char const *right_quote) {
  size_t i;
  size_t len;
  char const *quote_string;

  unsigned char c;

  int tmp___6;

  {
    len = (size_t)0;

    {
      left_quote = gettext_quote("`", quoting_style);
      right_quote = gettext_quote("\'", quoting_style);
    }
    {
      quote_string = left_quote;
      {

        { *(buffer + len) = (char)*quote_string; }
        len++;
      };
    }

    quote_string = right_quote;

    i = (size_t)0;
    while (1) {

      {
        tmp___6 = (int const) * (arg + i) == 0;
      }

      if (tmp___6) {
        goto while_break___3;
      }

      c = (unsigned char)*(arg + i);

      {

        { *(buffer + len) = (char)c; }
        len++;
      };

      i++;
    }
  while_break___3:;

    {

      { *(buffer + len) = (char)*quote_string; };
    }

    return (len);
  }
}
static char slot0[256];

static struct slotvec slotvec0 = {sizeof(slot0), slot0};
static struct slotvec *slotvec = &slotvec0;
static char *quotearg_n_options(int n, char const *arg, size_t argsize,
                                struct quoting_options const *options) {

  struct slotvec *sv;

  size_t size;
  char *val;
  int flags;

  size_t tmp___2;

  {

    sv = slotvec;

    size = (sv + n)->size;
    val = (sv + n)->val;
    flags = (int)(options->flags | 1);
    tmp___2 = quotearg_buffer_restyled(
        val, size, arg, argsize, (enum quoting_style)options->style, flags,
        (unsigned int const *)(options->quote_these_too),
        (char const *)options->left_quote, (char const *)options->right_quote);

    return (val);
  }
}
char *quotearg_n_style(int n, enum quoting_style s, char const *arg) {
  struct quoting_options o;

  char *tmp___0;

  {

    tmp___0 = quotearg_n_options(n, arg, (size_t)-1,
                                 (struct quoting_options const *)(&o));
    return (tmp___0);
  }
}

char const *quote_n(int n, char const *name) {
  char const *tmp;

  {
    tmp = (char const *)quotearg_n_style(n, (enum quoting_style)6, name);
    return (tmp);
  }
}
char const *quote(char const *name) {
  char const *tmp;

  {
    tmp = quote_n(0, name);
    return (tmp);
  }
}

void set_program_name(char const *argv0);

extern int fputs(char const *__restrict __s, FILE *__restrict __stream);

extern __attribute__((__nothrow__)) char *(
    __attribute__((__nonnull__(1, 2), __leaf__))
    stpcpy)(char *__restrict __dest, char const *__restrict __src);
extern DIR *(__attribute__((__nonnull__(1))) opendir)(char const *__name);
extern
    __attribute__((__nothrow__)) int(__attribute__((__nonnull__(1), __leaf__))
                                     dirfd)(DIR *__dirp);

int openat_safer(int fd, char const *file, int flags, ...);
int openat_safer(int fd, char const *file, int flags, ...) {
  mode_t mode;

  int tmp;
  int tmp___0;

  {
    mode = (mode_t)0;

    tmp = openat(fd, file, flags, mode);
    tmp___0 = fd_safer(tmp);
    return (tmp___0);
  }
}

extern __attribute__((__nothrow__, __noreturn__)) void(__attribute__((__leaf__))
                                                       exit)(int __status);
extern int optind;
extern __attribute__((__nothrow__)) int(__attribute__((__leaf__)) getopt_long)(
    int ___argc, char *const *___argv, char const *__shortopts,
    struct option const *__longopts, int *__longind);
#pragma weak pthread_mutex_init
#pragma weak pthread_mutex_lock
#pragma weak pthread_mutex_unlock
#pragma weak pthread_mutex_destroy
#pragma weak pthread_rwlock_init
#pragma weak pthread_rwlock_rdlock
#pragma weak pthread_rwlock_wrlock
#pragma weak pthread_rwlock_unlock
#pragma weak pthread_rwlock_destroy
#pragma weak pthread_once
#pragma weak pthread_cond_init
#pragma weak pthread_cond_wait
#pragma weak pthread_cond_signal
#pragma weak pthread_cond_broadcast
#pragma weak pthread_cond_destroy
#pragma weak pthread_mutexattr_init
#pragma weak pthread_mutexattr_settype
#pragma weak pthread_mutexattr_destroy
#pragma weak pthread_self
#pragma weak pthread_cancel
extern struct passwd *getpwuid(__uid_t __uid);
void i_ring_init(I_ring *ir, int default_val);
int i_ring_push(I_ring *ir, int val);
int i_ring_pop(I_ring *ir);
_Bool i_ring_empty(I_ring const *ir);

_Bool(__attribute__((__warn_unused_result__))
      hash_rehash)(Hash_table *table___0, size_t candidate);
void *hash_delete(Hash_table *table___0, void const *entry);

size_t hash_pjw(void const *x, size_t tablesize);

extern __attribute__((__nothrow__)) char *(__attribute__((__leaf__))
                                           setlocale)(int __category,
                                                      char const *__locale);
extern __attribute__((__nothrow__)) int(
    __attribute__((__nonnull__(2, 3), __leaf__))
    fstatat)(int __fd, char const *__restrict __file,
             struct stat *__restrict __buf, int __flag);
__attribute__((__nothrow__)) int(__attribute__((__warn_unused_result__,
                                                __leaf__)) fts_close)(FTS *sp);
__attribute__((__nothrow__))
FTSENT *(__attribute__((__warn_unused_result__, __leaf__)) fts_read)(FTS *sp);
__attribute__((__nothrow__)) int(__attribute__((__leaf__))
                                 fts_set)(FTS *sp __attribute__((__unused__)),
                                          FTSENT *p, int instr);
extern void(__attribute__((__nonnull__(1, 4)))
            qsort)(void *__base, size_t __nmemb, size_t __size,
                   int (*__compar)(void const *, void const *));
static FTSENT *fts_alloc(FTS *sp, char const *name, size_t namelen);
static FTSENT *fts_build(FTS *sp, int type);
static void fts_lfree(FTSENT *head);
static void fts_load(FTS *sp, FTSENT *p);
static size_t fts_maxarglen(char *const *argv);
static void fts_padjust(FTS *sp, FTSENT *head);
static _Bool fts_palloc(FTS *sp, size_t more);
static FTSENT *fts_sort(FTS *sp, FTSENT *head, size_t nitems);
static unsigned short fts_stat(FTS *sp, FTSENT *p, _Bool follow);
static int fts_safe_changedir(FTS *sp, FTSENT *p, int fd, char const *dir);

__inline static DIR *opendirat(int fd, char const *dir) {
  int new_fd;
  int tmp;
  DIR *dirp;

  {
    tmp = openat_safer(fd, dir, 67840);
    new_fd = tmp;

    dirp = rpl_fdopendir(new_fd);

    return (dirp);
  }
}
static void cwd_advance_fd(FTS *sp, int fd, _Bool chdir_down_one) {

  sp->fts_cwd_fd = fd;
}

__attribute__((__nothrow__))
FTS *(__attribute__((__warn_unused_result__, __leaf__))
      fts_open)(char *const *argv, int options,
                int (*compar)(FTSENT const **, FTSENT const **));
FTS *(__attribute__((__warn_unused_result__, __leaf__))
      fts_open)(char *const *argv, int options,
                int (*compar)(FTSENT const **, FTSENT const **)) {
  FTS *sp;
  FTSENT *p;
  FTSENT *root;

  FTSENT *parent;

  size_t len;
  size_t tmp___8;
  struct _ftsent *tmp___9;

  {

    sp = (FTS *)malloc(sizeof(FTS));

    memset((void *)sp, 0, sizeof(FTS));

    sp->fts_cwd_fd = -100;

    {
      parent = fts_alloc(sp, "", (size_t)0);

      parent->fts_level = (ptrdiff_t)-1;
    }

    root = (FTSENT *)((void *)0);

    {

      tmp___8 = strlen((char const *)*argv);
      len = tmp___8;
      p = fts_alloc(sp, (char const *)*argv, len);

      p->fts_level = (ptrdiff_t)0;
      p->fts_parent = parent;
      p->fts_accpath = p->fts_name;
      { p->fts_info = fts_stat(sp, p, (_Bool)0); }

      {
        p->fts_link = root;
        root = p;
      }
    };

    tmp___9 = fts_alloc(sp, "", (size_t)0);
    sp->fts_cur = tmp___9;

    (sp->fts_cur)->fts_link = root;
    (sp->fts_cur)->fts_info = (unsigned short)9;

    return (sp);
  }
}

__attribute__((__nothrow__)) int(__attribute__((__warn_unused_result__,
                                                __leaf__)) fts_close)(FTS *sp);
int(__attribute__((__warn_unused_result__, __leaf__)) fts_close)(FTS *sp) {

  free((void *)sp);

  return (0);
}
extern
    __attribute__((__nothrow__)) int(__attribute__((__nonnull__(2), __leaf__))
                                     fstatfs)(int __fildes,
                                              struct statfs *__buf);

__attribute__((__nothrow__))
FTSENT *(__attribute__((__warn_unused_result__, __leaf__)) fts_read)(FTS *sp);
FTSENT *(__attribute__((__warn_unused_result__, __leaf__)) fts_read)(FTS *sp) {
  FTSENT *p;
  FTSENT *tmp;
  unsigned short instr;

  struct _ftsent *tmp___4;

  struct _ftsent *tmp___18;

  FTSENT *tmp___32;

  {

    p = sp->fts_cur;
    instr = p->fts_instr;

    if ((int)p->fts_info == 1) {
      if ((int)instr == 4) {
        goto _L___0;
      } else {
        if (sp->fts_options & 64) {

        _L___0 : {}

          p->fts_info = (unsigned short)6;

          return (p);
        }
      }

      {
        tmp___4 = fts_build(sp, 3);
        sp->fts_child = tmp___4;
      }
      p = sp->fts_child;
    }

    tmp = p;
    p = p->fts_link;
    if ((unsigned long)p != (unsigned long)((void *)0)) {

      free((void *)tmp);

      sp->fts_cur = p;

      return (p);
    }
    p = tmp->fts_parent;

    free((void *)tmp);
    if (p->fts_level == -1L) {
      free((void *)p);

      tmp___18 = (struct _ftsent *)((void *)0);

      return (tmp___18);
    }

    { p->fts_info = (unsigned short)6; }

    { tmp___32 = p; }
    return (tmp___32);
  }
}
__attribute__((__nothrow__)) int(__attribute__((__leaf__))
                                 fts_set)(FTS *sp __attribute__((__unused__)),
                                          FTSENT *p, int instr);
int(__attribute__((__leaf__)) fts_set)(FTS *sp __attribute__((__unused__)),
                                       FTSENT *p, int instr) {

  {

    if (instr != 4) {

      return (1);
    }
  }
  p->fts_instr = (unsigned short)instr;
}

static FTSENT *fts_build(FTS *sp, int type) {
  struct dirent *dp;
  FTSENT *p;
  FTSENT *head;

  FTSENT *cur;
  FTSENT *tail;
  DIR *dirp;

  DIR *tmp___0;

  int dir_fd;
  int tmp___5;

  int tmp___7;

  size_t tmp___9;

  {
    cur = sp->fts_cur;
    {

      tmp___0 = opendirat(sp->fts_cwd_fd, (char const *)cur->fts_accpath);
      dirp = tmp___0;
    }

    {

      tmp___5 = dirfd(dirp);
      dir_fd = tmp___5;
      { dir_fd = dup_safer(dir_fd); }

      {
        tmp___7 =
            fts_safe_changedir(sp, cur, dir_fd, (char const *)((void *)0));
      }
    }

    {

      { dp = readdir(dirp); }

      tmp___9 = strlen((char const *)(dp->d_name));
      p = fts_alloc(sp, (char const *)(dp->d_name), tmp___9);

      p->fts_parent = sp->fts_cur;

      p->fts_link = (struct _ftsent *)((void *)0);
      {
        tail = p;
        head = tail;
      }
    };
    { closedir(dirp); }

    return (head);
  }
}
static unsigned short fts_stat(FTS *sp, FTSENT *p, _Bool follow) {

  return ((unsigned short)1);
}

static FTSENT *fts_alloc(FTS *sp, char const *name, size_t namelen) {
  FTSENT *p;
  size_t len;

  {
    len = sizeof(FTSENT) + namelen;
    p = (FTSENT *)malloc(len);

    memmove((void *)(p->fts_name), (void const *)name, namelen);
    p->fts_name[namelen] = (char)'\000';

    p->fts_instr = (unsigned short)3;

    return (p);
  }
}

static int fts_safe_changedir(FTS *sp, FTSENT *p, int fd, char const *dir) {

  _Bool is_dotdot;

  int newfd;

  {

    { is_dotdot = (_Bool)1; }
    newfd = fd;

    {
      cwd_advance_fd(sp, newfd, (_Bool)(!is_dotdot));
      return (0);
    }
  }
}
#pragma weak pthread_key_create
#pragma weak pthread_getspecific
#pragma weak pthread_setspecific
#pragma weak pthread_key_delete
#pragma weak pthread_self
#pragma weak pthread_cancel
#pragma weak pthread_mutex_init
#pragma weak pthread_mutex_lock
#pragma weak pthread_mutex_unlock
#pragma weak pthread_mutex_destroy
#pragma weak pthread_rwlock_init
#pragma weak pthread_rwlock_rdlock
#pragma weak pthread_rwlock_wrlock
#pragma weak pthread_rwlock_unlock
#pragma weak pthread_rwlock_destroy
#pragma weak pthread_once
#pragma weak pthread_cond_init
#pragma weak pthread_cond_wait
#pragma weak pthread_cond_signal
#pragma weak pthread_cond_broadcast
#pragma weak pthread_cond_destroy
#pragma weak pthread_mutexattr_init
#pragma weak pthread_mutexattr_settype
#pragma weak pthread_mutexattr_destroy
#pragma weak pthread_self
#pragma weak pthread_cancel

extern
    __attribute__((__nothrow__)) int(__attribute__((__nonnull__(2), __leaf__))
                                     fchownat)(int __fd, char const *__file,
                                               __uid_t __owner, __gid_t __group,
                                               int __flag);
__inline static int chownat(int fd, char const *file, uid_t owner,
                            gid_t group) {
  int tmp;

  {
    tmp = fchownat(fd, file, owner, group, 0);
    return (tmp);
  }
}
__inline static int lchownat(int fd, char const *file, uid_t owner,
                             gid_t group) {
  int tmp;

  {
    tmp = fchownat(fd, file, owner, group, 256);
    return (tmp);
  }
}
extern void chopt_init(struct Chown_option *chopt);
extern void chopt_free(struct Chown_option *chopt __attribute__((__unused__)));
extern char *gid_to_name(gid_t gid);
extern char *uid_to_name(uid_t uid);
extern _Bool chown_files(char **files, int bit_flags, uid_t uid, gid_t gid,
                         uid_t required_uid, gid_t required_gid,
                         struct Chown_option const *chopt);

extern void chopt_init(struct Chown_option *chopt) {

  chopt->recurse = (_Bool)0;
}

static _Bool change_file_owner(FTS *fts, FTSENT *ent, uid_t uid, gid_t gid,
                               uid_t required_uid, gid_t required_gid,
                               struct Chown_option const *chopt) {

  char const *file;

  _Bool ok;

  int tmp___28;

  int tmp___31;

  {

    file = (char const *)ent->fts_accpath;
    ok = (_Bool)1;

    {
      if (!chopt->affect_symlink_referent) {
        tmp___28 = lchownat(fts->fts_cwd_fd, file, uid, gid);

      } else {

        tmp___31 = chownat(fts->fts_cwd_fd, file, uid, gid);
      }
    }

    if (!chopt->recurse) {
      fts_set(fts, ent, 4);
    }
    return (ok);
  }
}
extern _Bool chown_files(char **files, int bit_flags, uid_t uid, gid_t gid,
                         uid_t required_uid, gid_t required_gid,
                         struct Chown_option const *chopt) {
  _Bool ok;
  int stat_flags;
  int tmp;
  FTS *fts;
  FTS *tmp___0;
  FTSENT *ent;

  _Bool tmp___4;

  int tmp___7;

  {
    ok = (_Bool)1;
    { tmp = 0; }

    stat_flags = tmp;
    tmp___0 = xfts_open((char *const *)files, bit_flags | stat_flags,
                        (int (*)(FTSENT const **, FTSENT const **))((void *)0));
    fts = tmp___0;
    while (1) {
      ent = fts_read(fts);
      if ((unsigned long)ent == (unsigned long)((void *)0)) {

        goto while_break;
      }
      tmp___4 = change_file_owner(fts, ent, uid, gid, required_uid,
                                  required_gid, chopt);
    }
  while_break:
    tmp___7 = fts_close(fts);

    return (ok);
  }
}
extern char *optarg;
extern
    __attribute__((__nothrow__)) int(__attribute__((__nonnull__(1), __leaf__))
                                     atexit)(void (*__func)(void));
extern
    __attribute__((__nothrow__)) char *(__attribute__((__leaf__))
                                        textdomain)(char const *__domainname);
extern __attribute__((__nothrow__)) char *(__attribute__((
    __leaf__)) bindtextdomain)(char const *__domainname, char const *__dirname);

static struct option const long_options___1[14] = {
    {"recursive", 0, (int *)((void *)0), 'R'},
    {"changes", 0, (int *)((void *)0), 'c'},
    {"dereference", 0, (int *)((void *)0), 128},
    {"from", 1, (int *)((void *)0), 129},
    {"no-dereference", 0, (int *)((void *)0), 'h'},
    {"no-preserve-root", 0, (int *)((void *)0), 130},
    {"preserve-root", 0, (int *)((void *)0), 131},
    {"quiet", 0, (int *)((void *)0), 'f'},
    {"silent", 0, (int *)((void *)0), 'f'},
    {"reference", 1, (int *)((void *)0), 132},
    {"verbose", 0, (int *)((void *)0), 'v'},
    {"help", 0, (int *)((void *)0), -130},
    {"version", 0, (int *)((void *)0), -131},
    {(char const *)((void *)0), 0, (int *)((void *)0), 0}};
__attribute__((__noreturn__)) void usage(int status);
void usage(int status) { exit(status); }

int main(int argc, char **argv) {

  uid_t uid;
  gid_t gid;
  uid_t required_uid;
  gid_t required_gid;
  int bit_flags;
  int dereference;
  struct Chown_option chopt;
  _Bool ok;
  int optc;
  char *u_dummy;
  char *g_dummy;

  char const *tmp;

  char const *tmp___3;
  char *tmp___4;
  int tmp___5;

  char const *e___0;
  char const *tmp___10;
  char const *tmp___11;

  {

    uid = (uid_t)-1;

    bit_flags = 16;
    dereference = -1;

    atexit(&close_stdout);
    chopt_init(&chopt);
    {
      optc = getopt_long(argc, (char *const *)argv, "HLPRcfhv",
                         long_options___1, (int *)((void *)0));
      if (!(optc != -1)) {
        goto while_break;
      }

      if (optc == 104) {
        goto case_104;
      }

      { goto case_82; }

    case_104:
      dereference = 0;
      goto switch_break;

      tmp = parse_user_spec((char const *)optarg, &required_uid, &required_gid,
                            &u_dummy, &g_dummy);

    case_82:
      chopt.recurse = (_Bool)1;

    switch_break:;
    }
  while_break:;

    chopt.affect_symlink_referent = (_Bool)(dereference != 0);

    { tmp___5 = 2; }
    if (argc - optind < tmp___5) {

      {
        tmp___3 = quote((char const *)*(argv + (argc - 1)));
        tmp___4 = gettext("missing operand after %s");
        error(0, 0, (char const *)tmp___4, tmp___3);
      }
      usage(1);
    }

    {
      tmp___10 = parse_user_spec((char const *)*(argv + optind), &uid, &gid,
                                 &chopt.user_name, &chopt.group_name);
      e___0 = tmp___10;
      if (e___0) {
        tmp___11 = quote((char const *)*(argv + optind));
        error(1, 0, "%s: %s", e___0, tmp___11);
      }

      optind++;
    }

    ok = chown_files(argv + optind, bit_flags, uid, gid, required_uid,
                     required_gid, (struct Chown_option const *)(&chopt));
  }
}
