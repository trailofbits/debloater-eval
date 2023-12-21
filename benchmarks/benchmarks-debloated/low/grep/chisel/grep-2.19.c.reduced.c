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
typedef long ptrdiff_t;
typedef unsigned long size_t;
typedef __builtin_va_list __gnuc_va_list;
typedef __gnuc_va_list va_list;
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
typedef int wchar_t;
union __anonunion___value_23 {
  unsigned int __wch;
  char __wchb[4];
};
struct __anonstruct___mbstate_t_22 {
  int __count;
  union __anonunion___value_23 __value;
};
typedef struct __anonstruct___mbstate_t_22 __mbstate_t;
typedef unsigned int wint_t;
typedef __mbstate_t mbstate_t;
struct mbchar {
  char const *ptr;
  size_t bytes;
  _Bool wc_valid;
  wchar_t wc;
  char buf[24];
};
typedef struct mbchar mbchar_t;
struct mbiter_multi {
  char const *limit;
  _Bool in_shift;
  mbstate_t state;
  _Bool next_done;
  struct mbchar cur;
};
typedef struct mbiter_multi mbi_iterator_t;
typedef long __ssize_t;
typedef __ssize_t ssize_t;
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
struct mbuiter_multi {
  _Bool in_shift;
  mbstate_t state;
  _Bool next_done;
  struct mbchar cur;
};
typedef struct mbuiter_multi mbui_iterator_t;
struct __dirstream;
struct __dirstream;
struct __dirstream;
typedef struct __dirstream DIR;
typedef unsigned int __mode_t;
typedef __mode_t mode_t;
typedef unsigned long uintptr_t;
typedef unsigned long longword;
struct preliminary_header {
  void *next;
  int magic;
};
struct __anonstruct_magic_22 {
  char room[(((sizeof(struct preliminary_header) + 16UL) - 1UL) / 16UL) * 16UL -
            sizeof(int)];
  int word;
};
union header {
  void *next;
  struct __anonstruct_magic_22 magic;
};
typedef int nl_item;
struct I_ring {
  int ir_data[4];
  int ir_default_val;
  unsigned int ir_front;
  unsigned int ir_back;
  _Bool ir_empty;
};
typedef struct I_ring I_ring;
struct hash_tuning {
  float shrink_threshold;
  float shrink_factor;
  float growth_threshold;
  float growth_factor;
  _Bool is_n_buckets;
};
typedef struct hash_tuning Hash_tuning;
struct hash_table;
struct hash_table;
struct hash_table;
typedef struct hash_table Hash_table;
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
typedef unsigned long __dev_t;
typedef unsigned int __uid_t;
typedef unsigned int __gid_t;
typedef unsigned long __ino_t;
typedef unsigned long __nlink_t;
struct __anonstruct___fsid_t_1 {
  int __val[2];
};
typedef struct __anonstruct___fsid_t_1 __fsid_t;
typedef long __time_t;
typedef long __blksize_t;
typedef long __blkcnt_t;
typedef unsigned long __fsblkcnt_t;
typedef unsigned long __fsfilcnt_t;
typedef long __fsword_t;
typedef long __syscall_slong_t;
typedef __ino_t ino_t;
typedef __dev_t dev_t;
typedef __nlink_t nlink_t;
struct timespec {
  __time_t tv_sec;
  __syscall_slong_t tv_nsec;
};
struct dirent {
  __ino_t d_ino;
  __off_t d_off;
  unsigned short d_reclen;
  unsigned char d_type;
  char d_name[256];
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
struct _ftsent;
struct _ftsent;
struct _ftsent;
struct cycle_check_state;
struct cycle_check_state;
struct cycle_check_state;
union __anonunion_fts_cycle_19 {
  struct hash_table *ht;
  struct cycle_check_state *state;
};
struct __anonstruct_FTS_18 {
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
  union __anonunion_fts_cycle_19 fts_cycle;
  I_ring fts_fd_ring;
};
typedef struct __anonstruct_FTS_18 FTS;
struct _ftsent {
  struct _ftsent *fts_cycle;
  struct _ftsent *fts_parent;
  struct _ftsent *fts_link;
  DIR *fts_dirp;
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
typedef unsigned long __re_long_size_t;
typedef unsigned long reg_syntax_t;
struct re_dfa_t;
struct re_dfa_t;
struct re_dfa_t;
struct re_pattern_buffer {
  struct re_dfa_t *buffer;
  __re_long_size_t allocated;
  __re_long_size_t used;
  reg_syntax_t syntax;
  char *fastmap;
  unsigned char *translate;
  size_t re_nsub;
  unsigned int can_be_null : 1;
  unsigned int regs_allocated : 2;
  unsigned int fastmap_accurate : 1;
  unsigned int no_sub : 1;
  unsigned int not_bol : 1;
  unsigned int not_eol : 1;
  unsigned int newline_anchor : 1;
};
typedef struct re_pattern_buffer regex_t;
typedef int regoff_t;
struct __anonstruct_regmatch_t_29 {
  regoff_t rm_so;
  regoff_t rm_eo;
};
typedef struct __anonstruct_regmatch_t_29 regmatch_t;
struct exclude;
struct exclude;
struct exclude;
union __anonunion_v_33 {
  char const *pattern;
  regex_t re;
};
struct patopts {
  int options;
  union __anonunion_v_33 v;
};
struct exclude_pattern {
  struct patopts *exclude;
  size_t exclude_alloc;
  size_t exclude_count;
};
enum exclude_type { exclude_hash = 0, exclude_pattern = 1 };
union __anonunion_v_34 {
  Hash_table *table;
  struct exclude_pattern pat;
};
struct exclude_segment {
  struct exclude_segment *next;
  enum exclude_type type;
  int options;
  union __anonunion_v_34 v;
};
struct pattern_buffer {
  struct pattern_buffer *next;
  char *base;
};
struct exclude {
  struct exclude_segment *head;
  struct pattern_buffer *patbuf;
};
struct real_pcre;
struct real_pcre;
struct real_pcre;
typedef struct real_pcre pcre;
struct real_pcre_jit_stack;
struct real_pcre_jit_stack;
struct real_pcre_jit_stack;
typedef struct real_pcre_jit_stack pcre_jit_stack;
struct pcre_extra {
  unsigned long flags;
  void *study_data;
  unsigned long match_limit;
  void *callout_data;
  unsigned char const *tables;
  unsigned long match_limit_recursion;
  unsigned char **mark;
  void *executable_jit;
};
typedef struct pcre_extra pcre_extra;
struct kwsmatch {
  size_t index;
  size_t offset[1];
  size_t size[1];
};
struct kwset;
struct kwset;
struct kwset;
typedef struct kwset *kwset_t;
typedef signed char mb_len_map_t;
struct obstack;
struct obstack;
struct obstack;
struct _obstack_chunk {
  char *limit;
  struct _obstack_chunk *prev;
  char contents[4];
};
union __anonunion_temp_56 {
  long tempint;
  void *tempptr;
};
struct obstack {
  long chunk_size;
  struct _obstack_chunk *chunk;
  char *object_base;
  char *next_free;
  char *chunk_limit;
  union __anonunion_temp_56 temp;
  int alignment_mask;
  struct _obstack_chunk *(*chunkfun)(void *, long);
  void (*freefun)(void *, struct _obstack_chunk *);
  void *extra_arg;
  unsigned int use_extra_arg : 1;
  unsigned int maybe_empty_object : 1;
  unsigned int alloc_failed : 1;
};
struct trie;
struct trie;
struct trie;
struct tree {
  struct tree *llink;
  struct tree *rlink;
  struct trie *trie;
  unsigned char label;
  char balance;
};
struct trie {
  size_t accepting;
  struct tree *links;
  struct trie *parent;
  struct trie *next;
  struct trie *fail;
  int depth;
  int shift;
  int maxshift;
};
struct kwset {
  struct obstack obstack;
  ptrdiff_t words;
  struct trie *trie;
  int mind;
  int maxd;
  unsigned char delta[256];
  struct trie *next[256];
  char *target;
  int *shift;
  char const *trans;
  char gc1;
  char gc2;
  int gc1help;
};
enum __anonenum_dirs_58 { L = 0, R = 1 };
typedef int __re_idx_t;
typedef unsigned int __re_size_t;
struct re_registers {
  __re_size_t num_regs;
  regoff_t *start;
  regoff_t *end;
};
struct dfamust {
  _Bool exact;
  _Bool begline;
  _Bool endline;
  char *must;
  struct dfamust *next;
};
struct dfa;
struct dfa;
struct dfa;
struct patterns {
  struct re_pattern_buffer regexbuf;
  struct re_registers regs;
};
enum __anonenum_mode_60 { DW_NONE = 0, DW_POSIX = 1, DW_GNU = 2 };
typedef unsigned long wctype_t;
typedef unsigned int charclass_word;
typedef charclass_word charclass[8];
typedef ptrdiff_t token;
struct __anonstruct_position_35 {
  size_t index;
  unsigned int constraint;
};
typedef struct __anonstruct_position_35 position;
struct __anonstruct_position_set_36 {
  position *elems;
  size_t nelem;
  size_t alloc;
};
typedef struct __anonstruct_position_set_36 position_set;
struct __anonstruct_leaf_set_37 {
  size_t *elems;
  size_t nelem;
};
typedef struct __anonstruct_leaf_set_37 leaf_set;
struct __anonstruct_dfa_state_38 {
  size_t hash;
  position_set elems;
  unsigned char context;
  _Bool has_backref;
  _Bool has_mbcset;
  unsigned short constraint;
  token first_end;
  position_set mbps;
};
typedef struct __anonstruct_dfa_state_38 dfa_state;
typedef ptrdiff_t state_num;
struct __anonstruct_ranges_39 {
  wchar_t beg;
  wchar_t end;
};
struct mb_char_classes {
  ptrdiff_t cset;
  _Bool invert;
  wchar_t *chars;
  size_t nchars;
  wctype_t *ch_classes;
  size_t nch_classes;
  struct __anonstruct_ranges_39 *ranges;
  size_t nranges;
  char **equivs;
  size_t nequivs;
  char **coll_elems;
  size_t ncoll_elems;
};
struct dfa {
  charclass *charclasses;
  size_t cindex;
  size_t calloc;
  token *tokens;
  size_t tindex;
  size_t talloc;
  size_t depth;
  size_t nleaves;
  size_t nregexps;
  _Bool fast;
  _Bool multibyte;
  token utf8_anychar_classes[5];
  mbstate_t mbs;
  int *multibyte_prop;
  wint_t mbrtowc_cache[256];
  struct mb_char_classes *mbcsets;
  size_t nmbcsets;
  size_t mbcsets_alloc;
  struct dfa *superset;
  dfa_state *states;
  state_num sindex;
  size_t salloc;
  position_set *follows;
  _Bool searchflag;
  state_num tralloc;
  int trcount;
  state_num **trans;
  state_num **fails;
  int *success;
  state_num *newlines;
  struct dfamust *musts;
  position_set mb_follows;
  int *mb_match_lens;
};
typedef int predicate(int);
struct dfa_ctype {
  char const *name;
  predicate *func;
  _Bool single_byte_only;
};
struct __anonstruct_stkalloc_43 {
  _Bool nullable;
  size_t nfirstpos;
  size_t nlastpos;
};
enum __anonenum_status_transit_state_44 {
  TRANSIT_STATE_IN_PROGRESS = 0,
  TRANSIT_STATE_DONE = 1,
  TRANSIT_STATE_END_BUFFER = 2
};
typedef enum __anonenum_status_transit_state_44 status_transit_state;
struct must;
struct must;
struct must;
typedef struct must must;
struct must {
  char **in;
  char *left;
  char *right;
  char *is;
  _Bool begline;
  _Bool endline;
  must *prev;
};
typedef __off_t off_t;
struct color_cap {
  char const *name;
  char const **var;
  void (*fct)(void);
};
enum directories_type {
  READ_DIRECTORIES = 2,
  RECURSE_DIRECTORIES = 3,
  SKIP_DIRECTORIES = 4
};
enum __anonenum_devices_71 {
  READ_COMMAND_LINE_DEVICES = 0,
  READ_DEVICES = 1,
  SKIP_DEVICES = 2
};
enum __anonenum_binary_files_72 {
  BINARY_BINARY_FILES = 0,
  TEXT_BINARY_FILES = 1,
  WITHOUT_MATCH_BINARY_FILES = 2
};
enum __anonenum_File_type_73 {
  UNKNOWN = 0,
  DOS_BINARY = 1,
  DOS_TEXT = 2,
  UNIX_TEXT = 3
};
typedef enum __anonenum_File_type_73 File_type;
struct dos_map {
  off_t pos;
  off_t add;
};
struct matcher {
  char const name[16];
  void (*compile)(char const *, size_t);
  size_t (*execute)(char const *, size_t, size_t *, char const *);
};
extern __attribute__((__nothrow__)) unsigned short const **__ctype_b_loc(void)
    __attribute__((__const__));
extern __attribute__((__nothrow__, __noreturn__)) void
__assert_fail(char const *__assertion, char const *__file, unsigned int __line,
              char const *__function);
extern __attribute__((__nothrow__)) int *__errno_location(void)
    __attribute__((__const__));
extern __attribute__((__nothrow__)) char *(__attribute__((__nonnull__(1)))
                                           strchr)(char const *__s, int __c)
    __attribute__((__pure__));
extern __attribute__((__nothrow__, __noreturn__)) void abort(void);
extern void error(int __status, int __errnum, char const *__format, ...);
int volatile exit_failure;
extern __attribute__((__nothrow__)) char *gettext(char const *__msgid)
    __attribute__((__format_arg__(1)));
extern __attribute__((__nothrow__)) intmax_t
strtoimax(char const *__restrict __nptr, char **__restrict __endptr,
          int __base);
strtol_error xstrtoimax(char const *s, char **ptr, int strtol_base,
                        intmax_t *val, char const *valid_suffixes);

__attribute__((__noreturn__)) void xalloc_die(void);
void *xmalloc(size_t n) __attribute__((__malloc__, __alloc_size__(1)));
void *xrealloc(void *p, size_t n) __attribute__((__alloc_size__(2)));
void *xnmalloc(size_t n, size_t s)
    __attribute__((__malloc__, __alloc_size__(1, 2)));
void *xnmalloc(size_t n, size_t s)
    __attribute__((__malloc__, __alloc_size__(1, 2)));
void *xnmalloc(size_t n, size_t s) {

  void *tmp___0;

  {

    { tmp___0 = xmalloc(n * s); }
    return (tmp___0);
  }
}
void *xnrealloc(void *p, size_t n, size_t s)
    __attribute__((__alloc_size__(2, 3)));
void *xnrealloc(void *p, size_t n, size_t s)
    __attribute__((__alloc_size__(2, 3)));
void *xnrealloc(void *p, size_t n, size_t s) {

  void *tmp___0;

  {

    { tmp___0 = xrealloc(p, n * s); }
    return (tmp___0);
  }
}
void *x2nrealloc(void *p, size_t *pn, size_t s) {
  size_t n;
  void *tmp;

  {
    n = *pn;

    { n += n / 2UL + 1UL; }
    {
      *pn = n;
      tmp = xrealloc(p, n * s);
    }
    return (tmp);
  }
}
char *xcharalloc(size_t n) __attribute__((__malloc__, __alloc_size__(1)));
char *xcharalloc(size_t n) __attribute__((__malloc__, __alloc_size__(1)));

void *xzalloc(size_t s) __attribute__((__malloc__, __alloc_size__(1)));
void *xcalloc(size_t n, size_t s)
    __attribute__((__malloc__, __alloc_size__(1, 2)));
void *x2realloc(void *p, size_t *pn);
void *xmemdup(void const *p, size_t s)
    __attribute__((__malloc__, __alloc_size__(2)));
char *xstrdup(char const *string) __attribute__((__malloc__));
extern __attribute__((__nothrow__)) void *malloc(size_t __size)
    __attribute__((__malloc__));
extern __attribute__((__nothrow__)) void *calloc(size_t __nmemb, size_t __size)
    __attribute__((__malloc__));
extern
    __attribute__((__nothrow__)) void *(__attribute__((__warn_unused_result__))
                                        realloc)(void *__ptr, size_t __size);
extern __attribute__((__nothrow__)) void free(void *__ptr);
extern __attribute__((__nothrow__)) void *(__attribute__((__nonnull__(1, 2)))
                                           memcpy)(void *__restrict __dest,
                                                   void const *__restrict __src,
                                                   size_t __n);
extern
    __attribute__((__nothrow__)) void *(__attribute__((__nonnull__(1)))
                                        memset)(void *__s, int __c, size_t __n);
extern __attribute__((__nothrow__))
size_t(__attribute__((__nonnull__(1))) strlen)(char const *__s)
    __attribute__((__pure__));
void *xmalloc(size_t n) __attribute__((__malloc__, __alloc_size__(1)));
void *xmalloc(size_t n) {
  void *p;
  void *tmp;

  {
    {
      tmp = malloc(n);
      p = tmp;
    }
    if (!p) {

      xalloc_die();
    }
    return (p);
  }
}
void *xrealloc(void *p, size_t n) __attribute__((__alloc_size__(2)));
void *xrealloc(void *p, size_t n) {

  { p = realloc(p, n); }

  return (p);
}

void *xzalloc(size_t s) __attribute__((__malloc__, __alloc_size__(1)));

void *xcalloc(size_t n, size_t s)
    __attribute__((__malloc__, __alloc_size__(1, 2)));
void *xcalloc(size_t n, size_t s) {
  void *p;

  {
    { p = calloc(n, s); }

    return (p);
  }
}
void *xmemdup(void const *p, size_t s)
    __attribute__((__malloc__, __alloc_size__(2)));
void *xmemdup(void const *p, size_t s) {
  void *tmp;
  void *tmp___0;

  {
    {
      tmp = xmalloc(s);
      tmp___0 = memcpy((void * /* __restrict  */)tmp,
                       (void const * /* __restrict  */)p, s);
    }
    return (tmp___0);
  }
}
char *xstrdup(char const *string) __attribute__((__malloc__));

__attribute__((__noreturn__)) void xalloc_die(void);
void xalloc_die(void) {
  char *tmp;

  {

    tmp = gettext("memory exhausted");
    error((int)exit_failure, 0, "%s", tmp);
  }
}
extern
    __attribute__((__nothrow__)) int(__attribute__((__nonnull__(1, 2)))
                                     strcmp)(char const *__s1, char const *__s2)
        __attribute__((__pure__));
extern struct _IO_FILE *stdout;
extern int fprintf(FILE *__restrict __stream, char const *__restrict __format,
                   ...);
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

char *trim2(char const *s, int how);
extern
    __attribute__((__nothrow__)) void *(__attribute__((__nonnull__(1, 2)))
                                        memmove)(void *__dest,
                                                 void const *__src, size_t __n);
extern __attribute__((__nothrow__)) char *(__attribute__((__nonnull__(1)))
                                           strdup)(char const *__s)
    __attribute__((__malloc__));
extern __attribute__((__nothrow__)) size_t __ctype_get_mb_cur_max(void);
extern __attribute__((__nothrow__)) int mbsinit(mbstate_t const *__ps)
    __attribute__((__pure__));
extern __attribute__((__nothrow__)) size_t mbrtowc(wchar_t *__restrict __pwc,
                                                   char const *__restrict __s,
                                                   size_t __n,
                                                   mbstate_t *__restrict __p);
extern __attribute__((__nothrow__)) int iswspace(wint_t __wc);

size_t strnlen1(char const *string, size_t maxlen) __attribute__((__pure__));
extern __attribute__((__nothrow__)) void *(__attribute__((__nonnull__(1)))
                                           memchr)(void const *__s, int __c,
                                                   size_t __n)
    __attribute__((__pure__));
size_t strnlen1(char const *string, size_t maxlen) __attribute__((__pure__));

int c_strcasecmp(char const *s1, char const *s2) __attribute__((__pure__));
extern int close(int __fd);
extern __attribute__((__nothrow__)) int fchdir(int __fd);
int set_cloexec_flag(int desc, _Bool value);
int open_safer(char const *file, int flags, ...);
size_t safe_read(int fd, void *buf, size_t count);
extern ssize_t read(int __fd, void *__buf, size_t __nbytes);
size_t safe_read(int fd, void *buf, size_t count) {
  ssize_t result;
  ssize_t tmp;

  {

    {
      ;
      {
        tmp = read(fd, buf, count);
        result = tmp;
      }
      {
        return ((size_t)result);
      }

      ;
    };
  }
}

int set_char_quoting(struct quoting_options *o, char c, int i);
char *quotearg_n_style(int n, enum quoting_style s, char const *arg);
char *quotearg_char(char const *arg, char ch);
char *quotearg_char_mem(char const *arg, size_t argsize, char ch);
char *quotearg_colon(char const *arg);

char const *quote_n_mem(int n, char const *arg, size_t argsize);
char const *quote_n(int n, char const *arg);
char const *quote(char const *arg);
char const *locale_charset(void);
extern __attribute__((__nothrow__)) int(__attribute__((__nonnull__(1, 2)))
                                        memcmp)(void const *__s1,
                                                void const *__s2, size_t __n)
    __attribute__((__pure__));
extern __attribute__((__nothrow__)) int iswprint(wint_t __wc);

static char slot0[256];
static unsigned int nslots = 1U;
static struct slotvec slotvec0 = {sizeof(slot0), slot0};
static struct slotvec *slotvec = &slotvec0;
static char *quotearg_n_options(int n, char const *arg, size_t argsize,
                                struct quoting_options const *options) {

  unsigned int n0;
  struct slotvec *sv;
  size_t n1;

  struct slotvec *tmp___1;

  char *val;

  {
    {

      n0 = (unsigned int)n;
      sv = slotvec;
    }

    if (nslots <= n0) {
      n1 = (size_t)(n0 + 1U);

      { tmp___1 = (struct slotvec *)((void *)0); }

      { sv = (struct slotvec *)xrealloc((void *)tmp___1, n1 * sizeof(*sv)); }

      { memset((void *)(sv + nslots), 0, (n1 - (size_t)nslots) * sizeof(*sv)); }
    }
    { val = (sv + n)->val; }

    return (val);
  }
}
char *quotearg_n_style(int n, enum quoting_style s, char const *arg) {
  struct quoting_options o;

  char *tmp___0;

  {
    {

      tmp___0 = quotearg_n_options(n, arg, (size_t)-1,
                                   (struct quoting_options const *)(&o));
    }
    return (tmp___0);
  }
}
char *quotearg_char_mem(char const *arg, size_t argsize, char ch) {
  struct quoting_options options;
  char *tmp;

  {
    {

      tmp = quotearg_n_options(0, arg, argsize,
                               (struct quoting_options const *)(&options));
    }
    return (tmp);
  }
}
char *quotearg_char(char const *arg, char ch) {
  char *tmp;

  {
    { tmp = quotearg_char_mem(arg, (size_t)-1, ch); }
    return (tmp);
  }
}
char *quotearg_colon(char const *arg) {
  char *tmp;

  {
    { tmp = quotearg_char(arg, (char)':'); }
    return (tmp);
  }
}
struct quoting_options quote_quoting_options = {(enum quoting_style)6,
                                                0,
                                                {0U},
                                                (char const *)((void *)0),
                                                (char const *)((void *)0)};
char const *quote_n_mem(int n, char const *arg, size_t argsize) {
  char const *tmp;

  {
    {
      tmp = (char const *)quotearg_n_options(
          n, arg, argsize,
          (struct quoting_options const *)(&quote_quoting_options));
    }
    return (tmp);
  }
}
char const *quote_n(int n, char const *arg) {
  char const *tmp;

  {
    { tmp = quote_n_mem(n, arg, (size_t)-1); }
    return (tmp);
  }
}

char const *proper_name(char const *name);
extern __attribute__((__nothrow__)) int
sprintf(char *__restrict __s, char const *__restrict __format, ...);
char *(__attribute__((__nonnull__(1, 2))) mbsstr)(char const *haystack,
                                                  char const *needle)
    __attribute__((__pure__));
extern __attribute__((__nothrow__)) int iswalnum(wint_t __wc);

void set_program_name(char const *argv0);

extern struct _IO_FILE *stderr;
extern int fputs(char const *__restrict __s, FILE *__restrict __stream);
extern __attribute__((__nothrow__)) int(__attribute__((__nonnull__(1, 2)))
                                        strncmp)(char const *__s1,
                                                 char const *__s2, size_t __n)
    __attribute__((__pure__));
extern __attribute__((__nothrow__)) char *(__attribute__((__nonnull__(1)))
                                           strrchr)(char const *__s, int __c)
    __attribute__((__pure__));
char const *program_name = (char const *)((void *)0);

int fd_safer(int fd);
extern DIR *fdopendir(int __fd);
extern int(__attribute__((__nonnull__(1))) closedir)(DIR *__dirp);
extern __attribute__((__nothrow__)) int(__attribute__((__nonnull__(1)))
                                        dirfd)(DIR *__dirp);
int dup_safer(int fd);
int openat_safer(int fd, char const *file, int flags, ...);
extern int(__attribute__((__nonnull__(2))) openat)(int __fd, char const *__file,
                                                   int __oflag, ...);
int openat_safer(int fd, char const *file, int flags, ...) {
  mode_t mode___0;

  int tmp;
  int tmp___0;

  {
    mode___0 = (mode_t)0;

    {
      tmp = openat(fd, file, flags, mode___0);
      tmp___0 = fd_safer(tmp);
    }
    return (tmp___0);
  }
}
extern int(__attribute__((__nonnull__(1))) open)(char const *__file,
                                                 int __oflag, ...);

void *memchr2(void const *s, int c1_in, int c2_in, size_t n)
    __attribute__((__pure__));
void *memchr2(void const *s, int c1_in, int c2_in, size_t n)
    __attribute__((__pure__));

extern __attribute__((__nothrow__))
size_t(__attribute__((__nonnull__(1))) strnlen)(char const *__string,
                                                size_t __maxlen)
    __attribute__((__pure__));
size_t(__attribute__((__nonnull__(1))) mbslen)(char const *string)
    __attribute__((__pure__));
void *mmalloca(size_t n);
void freea(void *p);

char *(__attribute__((__nonnull__(1, 2))) mbsstr)(char const *haystack,
                                                  char const *needle)
    __attribute__((__pure__));

size_t(__attribute__((__nonnull__(1))) mbslen)(char const *string)
    __attribute__((__pure__));

int(__attribute__((__nonnull__(1, 2)))
    mbscasecmp)(char const *s1, char const *s2) __attribute__((__pure__));
extern __attribute__((__nothrow__)) int tolower(int __c);
extern __attribute__((__nothrow__)) wint_t towlower(wint_t __wc);
int(__attribute__((__nonnull__(1, 2)))
    mbscasecmp)(char const *s1, char const *s2) __attribute__((__pure__));

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
extern int fclose(FILE *__stream);
extern __attribute__((__nothrow__)) FILE *fdopen(int __fd, char const *__modes);
extern int fscanf(FILE *__restrict __stream, char const *__restrict __format,
                  ...);
extern int getc_unlocked(FILE *__stream);
extern int ungetc(int __c, FILE *__stream);
extern
    __attribute__((__nothrow__)) char *(__attribute__((__nonnull__(1, 2)))
                                        strcpy)(char *__restrict __dest,
                                                char const *__restrict __src);
extern __attribute__((__nothrow__)) char *(__attribute__((__nonnull__(1)))
                                           getenv)(char const *__name);
extern __attribute__((__nothrow__)) char *nl_langinfo(nl_item __item);

void i_ring_init(I_ring *ir, int default_val);
int i_ring_push(I_ring *ir, int val);
int i_ring_pop(I_ring *ir);
_Bool i_ring_empty(I_ring const *ir) __attribute__((__pure__));

_Bool i_ring_empty(I_ring const *ir) __attribute__((__pure__));

void *hash_lookup(Hash_table const *table, void const *entry);
size_t hash_string(char const *string, size_t n_buckets)
    __attribute__((__pure__));
Hash_table *(__attribute__((__warn_unused_result__))
             hash_initialize)(size_t candidate, Hash_tuning const *tuning,
                              size_t (*hasher)(void const *, size_t),
                              _Bool (*comparator)(void const *, void const *),
                              void (*data_freer)(void *));
void hash_free(Hash_table *table);
_Bool(__attribute__((__warn_unused_result__)) hash_rehash)(Hash_table *table,
                                                           size_t candidate);
void *(__attribute__((__warn_unused_result__)) hash_insert)(Hash_table *table,
                                                            void const *entry);
int hash_insert_if_absent(Hash_table *table, void const *entry,
                          void const **matched_ent);
void *hash_delete(Hash_table *table, void const *entry);

size_t hash_string(char const *string, size_t n_buckets)
    __attribute__((__pure__));

static _Bool is_prime(size_t candidate) __attribute__((__const__));
static _Bool is_prime(size_t candidate) __attribute__((__const__));

static size_t next_prime(size_t candidate) __attribute__((__const__));
static size_t next_prime(size_t candidate) __attribute__((__const__));

static size_t __attribute__((__pure__))
compute_bucket_size(size_t candidate, Hash_tuning const *tuning) {

  return ((size_t __attribute__((__pure__)))candidate);
}
Hash_table *(__attribute__((__warn_unused_result__))
             hash_initialize)(size_t candidate, Hash_tuning const *tuning,
                              size_t (*hasher)(void const *, size_t),
                              _Bool (*comparator)(void const *, void const *),
                              void (*data_freer)(void *)) {
  Hash_table *table;

  {

    { table = (Hash_table *)malloc(sizeof(*table)); }

    { table->n_buckets = (size_t)compute_bucket_size(candidate, tuning); }

    {
      table->bucket = (struct hash_entry *)calloc(table->n_buckets,
                                                  sizeof(*(table->bucket)));
    }

    return (table);
  }
}
void hash_free(Hash_table *table) {

  free((void *)table->bucket);
  free((void *)table);
}

extern struct dirent *(__attribute__((__nonnull__(1))) readdir)(DIR *__dirp);
extern __attribute__((__nothrow__)) int(__attribute__((__nonnull__(1, 2)))
                                        stat)(char const *__restrict __file,
                                              struct stat *__restrict __buf);
extern __attribute__((__nothrow__)) int(__attribute__((__nonnull__(2)))
                                        fstat)(int __fd, struct stat *__buf);
extern __attribute__((__nothrow__)) int(__attribute__((__nonnull__(2, 3)))
                                        fstatat)(int __fd,
                                                 char const *__restrict __file,
                                                 struct stat *__restrict __buf,
                                                 int __flag);
extern __attribute__((__nothrow__)) int(__attribute__((__nonnull__(1, 2)))
                                        lstat)(char const *__restrict __file,
                                               struct stat *__restrict __buf);
__attribute__((__nothrow__)) int(__attribute__((__warn_unused_result__))
                                 fts_close)(FTS *sp);
__attribute__((__nothrow__))
FTS *(__attribute__((__warn_unused_result__))
      fts_open)(char *const *argv, int options,
                int (*compar)(FTSENT const **, FTSENT const **));
__attribute__((__nothrow__))
FTSENT *(__attribute__((__warn_unused_result__)) fts_read)(FTS *sp);
__attribute__((__nothrow__)) int fts_set(FTS *sp __attribute__((__unused__)),
                                         FTSENT *p, int instr);
extern void(__attribute__((__nonnull__(1, 4)))
            qsort)(void *__base, size_t __nmemb, size_t __size,
                   int (*__compar)(void const *, void const *));
static FTSENT *fts_alloc(FTS *sp, char const *name, size_t namelen);
static FTSENT *fts_build(FTS *sp, int type);
static void fts_lfree(FTSENT *head);
static void fts_load(FTS *sp, FTSENT *p);
static size_t __attribute__((__pure__)) fts_maxarglen(char *const *argv);
static void fts_padjust(FTS *sp, FTSENT *head);
static _Bool fts_palloc(FTS *sp, size_t more);
static FTSENT *fts_sort(FTS *sp, FTSENT *head, size_t nitems);
static unsigned short fts_stat(FTS *sp, FTSENT *p, _Bool follow);
static int fts_safe_changedir(FTS *sp, FTSENT *p, int fd, char const *dir);
void cycle_check_init(struct cycle_check_state *state);
_Bool cycle_check(struct cycle_check_state *state, struct stat const *sb);
static _Bool AD_compare(void const *x, void const *y) {

  int tmp;

  {

    { tmp = 1; }

    return ((_Bool)tmp);
  }
}
static size_t AD_hash(void const *x, size_t table_size) {
  struct Active_dir const *ax;

  {
    ax = (struct Active_dir const *)x;
    return ((uintmax_t)ax->ino % table_size);
  }
}
static _Bool setup_dir(FTS *fts) {

  {

    fts->fts_cycle.ht =
        hash_initialize((size_t)31, (Hash_tuning const *)((void *)0), &AD_hash,
                        &AD_compare, &free);
  }

  return ((_Bool)1);
}

static void free_dir(FTS *sp) { hash_free(sp->fts_cycle.ht); }

static DIR *opendirat(int fd, char const *dir, int extra_flags, int *pdir_fd) {
  int new_fd;
  int tmp;
  DIR *dirp;

  {
    {
      tmp = openat_safer(fd, dir, 67840 | extra_flags);
      new_fd = tmp;
    }

    { dirp = fdopendir(new_fd); }
    { *pdir_fd = new_fd; }

    return (dirp);
  }
}
static void cwd_advance_fd(FTS *sp, int fd, _Bool chdir_down_one) {

  sp->fts_cwd_fd = fd;
}

__attribute__((__nothrow__))
FTS *(__attribute__((__warn_unused_result__))
      fts_open)(char *const *argv, int options,
                int (*compar)(FTSENT const **, FTSENT const **));
FTS *(__attribute__((__warn_unused_result__))
      fts_open)(char *const *argv, int options,
                int (*compar)(FTSENT const **, FTSENT const **)) {
  register FTS *sp;
  register FTSENT *p;
  register FTSENT *root;

  FTSENT *parent;

  size_t maxarglen;
  size_t tmp___5;
  size_t tmp___6;
  _Bool tmp___7;

  size_t len;
  size_t tmp___9;

  struct _ftsent *tmp___10;
  _Bool tmp___11;

  {

    { sp = (FTS *)malloc(sizeof(FTS)); }

    { memset((void *)sp, 0, sizeof(FTS)); }

    {
      sp->fts_cwd_fd = -100;
      tmp___5 = (size_t)fts_maxarglen(argv);
      maxarglen = tmp___5;
    }
    { tmp___6 = maxarglen; }

    { tmp___7 = fts_palloc(sp, tmp___6); }

    {
      { parent = fts_alloc(sp, "", (size_t)0); }

      parent->fts_level = (ptrdiff_t)-1;
    }

    root = (FTSENT *)((void *)0);

    {
      {
        ;

        {
          tmp___9 = strlen((char const *)*argv);
          len = tmp___9;
        }

        { p = fts_alloc(sp, (char const *)*argv, len); }

        p->fts_level = (ptrdiff_t)0;
        p->fts_parent = parent;
        p->fts_accpath = p->fts_name;
        { p->fts_info = fts_stat(sp, p, (_Bool)0); }

        {
          p->fts_link = root;
          root = p;
        }
      };
    };

    {
      tmp___10 = fts_alloc(sp, "", (size_t)0);
      sp->fts_cur = tmp___10;
    }

    {
      (sp->fts_cur)->fts_link = root;
      (sp->fts_cur)->fts_info = (unsigned short)9;
      tmp___11 = setup_dir(sp);
    }

    return (sp);
  }
}
static void fts_load(FTS *sp, FTSENT *p) {
  register size_t len;

  size_t tmp;

  {

    tmp = p->fts_namelen;
    p->fts_pathlen = tmp;
    len = tmp;
    memmove((void *)sp->fts_path, (void const *)(p->fts_name), len + 1UL);
  }
}
__attribute__((__nothrow__)) int(__attribute__((__warn_unused_result__))
                                 fts_close)(FTS *sp);
int(__attribute__((__warn_unused_result__)) fts_close)(FTS *sp) {

  {
    free_dir(sp);
    free((void *)sp);
  }

  return (0);
}
extern __attribute__((__nothrow__)) int(__attribute__((__nonnull__(2)))
                                        fstatfs)(int __fildes,
                                                 struct statfs *__buf);

__attribute__((__nothrow__))
FTSENT *(__attribute__((__warn_unused_result__)) fts_read)(FTS *sp);
FTSENT *(__attribute__((__warn_unused_result__)) fts_read)(FTS *sp) {
  register FTSENT *p;
  register FTSENT *tmp;

  register char *t;

  struct _ftsent *tmp___4;

  size_t tmp___8;
  char *tmp___9;

  struct _ftsent *tmp___14;

  FTSENT *tmp___24;

  {

    p = sp->fts_cur;

    if ((int)p->fts_info == 1) {

      {

        tmp___4 = fts_build(sp, 3);
        sp->fts_child = tmp___4;
      }
      p = sp->fts_child;

      goto name;
    }

    tmp = p;

    p = p->fts_link;
    if ((unsigned long)p != (unsigned long)((void *)0)) {
      {

        free((void *)tmp);
      }
      if (p->fts_level == 0L) {

        {

          fts_load(sp, p);
        }
        goto check_for_dir;
      }

    name :

    {
      tmp___8 = (p->fts_parent)->fts_pathlen;
    }
      {
        t = sp->fts_path + tmp___8;
        tmp___9 = t;
        t++;
        *tmp___9 = (char)'/';
        memmove((void *)t, (void const *)(p->fts_name), p->fts_namelen + 1UL);
      }
    check_for_dir:
      sp->fts_cur = p;

      return (p);
    }
    {
      p = tmp->fts_parent;
      sp->fts_cur = p;
      free((void *)tmp);
    }
    if (p->fts_level == -1L) {
      {
        free((void *)p);

        tmp___14 = (struct _ftsent *)((void *)0);
      }
      return (tmp___14);
    }

    { p->fts_info = (unsigned short)6; }

    { tmp___24 = p; }
    return (tmp___24);
  }
}
__attribute__((__nothrow__)) int fts_set(FTS *sp __attribute__((__unused__)),
                                         FTSENT *p, int instr);

static FTSENT *fts_build(FTS *sp, int type) {
  register FTSENT *p;
  register FTSENT *head;

  FTSENT *tail;

  ptrdiff_t level;

  int dir_fd;
  FTSENT *cur;

  DIR *tmp___1;
  int tmp___2;
  int tmp___3;
  int tmp___4;

  int tmp___10;

  size_t d_namelen;
  struct dirent *dp___0;
  struct dirent *tmp___12;

  {
    cur = sp->fts_cur;

    {{

        tmp___2 = 0;
  }

  { tmp___3 = 262144; }

  { tmp___4 = sp->fts_cwd_fd; }

  {
    tmp___1 = opendirat(tmp___4, (char const *)cur->fts_accpath,
                        tmp___2 | tmp___3, &dir_fd);
    cur->fts_dirp = tmp___1;
  }
}

{

  { dir_fd = dup_safer(dir_fd); }

  { tmp___10 = fts_safe_changedir(sp, cur, dir_fd, (char const *)((void *)0)); }
}

level = cur->fts_level + 1L;

head = (FTSENT *)((void *)0);

{
  while (1) {
    ;
  while_continue___2:;

    {
      tmp___12 = readdir(cur->fts_dirp);
      dp___0 = tmp___12;
    }
    if ((unsigned long)dp___0 == (unsigned long)((void *)0)) {
      goto while_break___2;
    }
    {

      if (!dp___0->d_name[1]) {
        goto while_continue___2;
      } else {

        if (!dp___0->d_name[2]) {
          goto while_continue___2;
        }
      }
    }
    {
      d_namelen = strlen((char const *)(dp___0->d_name));
      p = fts_alloc(sp, (char const *)(dp___0->d_name), d_namelen);
    }

    p->fts_level = level;
    p->fts_parent = sp->fts_cur;

    { p->fts_accpath = p->fts_name; }

    { p->fts_info = (unsigned short)11; }

    p->fts_link = (struct _ftsent *)((void *)0);
    if ((unsigned long)head == (unsigned long)((void *)0)) {
      tail = p;
      head = tail;
    } else {
      tail->fts_link = p;
    }
  };
}
while_break___2:;
{
  {
    {
      ;
      { closedir(cur->fts_dirp); }
    };
  };
}

return (head);
}
}
static unsigned short fts_stat(FTS *sp, FTSENT *p, _Bool follow) {

  return ((unsigned short)1);
}

static FTSENT *fts_alloc(FTS *sp, char const *name, size_t namelen) {
  register FTSENT *p;
  size_t len;

  {
    {
      len = sizeof(FTSENT) + namelen;
      p = (FTSENT *)malloc(len);
    }

    {
      memcpy((void * /* __restrict  */)((void *)(p->fts_name)),
             (void const * /* __restrict  */)((void const *)name), namelen);
      p->fts_name[namelen] = (char)'\000';
      p->fts_namelen = namelen;

      p->fts_path = sp->fts_path;
    }
    return (p);
  }
}

static _Bool fts_palloc(FTS *sp, size_t more) {
  char *p;
  size_t new_len;

  {
    new_len = (sp->fts_pathlen + more) + 256UL;

    {
      sp->fts_pathlen = new_len;
      p = (char *)realloc((void *)sp->fts_path, sp->fts_pathlen);
    }

    sp->fts_path = p;
    return ((_Bool)1);
  }
}

static size_t __attribute__((__pure__)) fts_maxarglen(char *const *argv) {

  size_t max;

  {
    max = (size_t)0;

    return ((size_t __attribute__((__pure__)))(max + 1UL));
  }
}
static int fts_safe_changedir(FTS *sp, FTSENT *p, int fd, char const *dir) {

  _Bool is_dotdot;

  int newfd;

  {

    { is_dotdot = (_Bool)1; }
    newfd = fd;

    {
      { cwd_advance_fd(sp, newfd, (_Bool)(!is_dotdot)); }
      return (0);
    }
  }
}
extern
    __attribute__((__nothrow__)) void *(__attribute__((__nonnull__(1, 2)))
                                        mempcpy)(void *__restrict __dest,
                                                 void const *__restrict __src,
                                                 size_t __n);
int fd_safer(int fd) { return (fd); }
extern int fcntl(int __fd, int __cmd, ...);
int rpl_fcntl(int fd, int action, ...);
static int have_dupfd_cloexec = 0;
int rpl_fcntl(int fd, int action, ...) {
  va_list arg;
  int result;
  int target;
  int tmp;

  int flags;
  int tmp___1;
  int saved_errno;
  int *tmp___2;
  int *tmp___3;
  int tmp___4;
  void *p;
  void *tmp___5;

  {
    {
      result = -1;
      __builtin_va_start(arg, action);
    }
    { goto case_1030; }
    goto switch_default;
  case_1030 : {
    tmp = __builtin_va_arg(arg, int);
    target = tmp;
  }
    {{result = fcntl(fd, action, target);
  }
  { have_dupfd_cloexec = 1; }
}

{

  {
    tmp___1 = fcntl(result, 1);
    flags = tmp___1;
  }

  {
    { tmp___4 = fcntl(result, 2, flags | 1); }
    if (tmp___4 == -1) {

      tmp___2 = __errno_location();
      saved_errno = *tmp___2;
      close(result);
      tmp___3 = __errno_location();
      *tmp___3 = saved_errno;
      result = -1;
    }
  }
}
goto switch_break;
switch_default : {
  tmp___5 = __builtin_va_arg(arg, void *);
  p = tmp___5;
  result = fcntl(fd, action, p);
}
goto switch_break;
switch_break : { __builtin_va_end(arg); }
return (result);
}
}

extern FILE *fopen(char const *__restrict __filename,
                   char const *__restrict __modes);
extern __attribute__((__nothrow__)) int ferror_unlocked(FILE *__stream);
extern int regcomp(regex_t *__restrict __preg, char const *__restrict __pattern,
                   int __cflags);
extern int regexec(regex_t const *__restrict __preg,
                   char const *__restrict __string, size_t __nmatch,
                   regmatch_t *__restrict __pmatch, int __eflags);
_Bool fnmatch_pattern_has_wildcards(char const *str, int options)
    __attribute__((__pure__));
struct exclude *new_exclude(void);
void add_exclude(struct exclude *ex, char const *pattern, int options);
int add_exclude_file(void (*add_func)(struct exclude *, char const *, int),
                     struct exclude *ex, char const *file_name___1, int options,
                     char line_end);
int add_exclude_fp(void (*add_func)(struct exclude *, char const *, int,
                                    void *),
                   struct exclude *ex, FILE *fp, int options, char line_end,
                   void *data);
_Bool excluded_file_name(struct exclude const *ex, char const *f);
void exclude_add_pattern_buffer(struct exclude *ex, char *buf);
_Bool exclude_fnmatch(char const *pattern, char const *f, int options);
extern int fnmatch(char const *__pattern, char const *__name, int __flags);

_Bool fnmatch_pattern_has_wildcards(char const *str, int options)
    __attribute__((__pure__));

int dup_safer(int fd) {
  int tmp;

  {
    { tmp = rpl_fcntl(fd, 0, 3); }
    return (tmp);
  }
}

int should_colorize(void);
void init_colorize(void);
void print_start_colorize(char const *sgr_start___0, char const *sgr_seq);
void print_end_colorize(char const *sgr_end___0);

void close_stdout(void);
extern __attribute__((__noreturn__)) void _exit(int __status);
int close_stream(FILE *stream);
static char const *file_name;

void close_stdout(void) {
  char const *write_error;
  char const *tmp;
  char *tmp___0;
  int *tmp___1;

  int tmp___3;

  {
    { tmp___3 = close_stream(stdout); }
    if (tmp___3 != 0) {

      {
        tmp = (char const *)gettext("write error");
        write_error = tmp;
      }
      {

        tmp___0 = quotearg_colon(file_name);
        tmp___1 = __errno_location();
        error(0, *tmp___1, "%s: %s", tmp___0, write_error);
      }
    }
  }
}
extern __attribute__((__nothrow__)) size_t __fpending(FILE *__fp);
int close_stream(FILE *stream) {

  _Bool fclose_fail;
  int tmp___1;

  {
    {

      tmp___1 = fclose(stream);
      fclose_fail = (_Bool)(tmp___1 != 0);
    }

    {
      if (fclose_fail) {

        return (-1);
      }
    }
    return (0);
  }
}

extern __attribute__((__nothrow__)) void *(__attribute__((__nonnull__(1)))
                                           memrchr)(void const *__s, int __c,
                                                    size_t __n)
    __attribute__((__pure__));
int c_tolower(int c) __attribute__((__const__));
int c_strcasecmp(char const *s1, char const *s2) __attribute__((__pure__));

_Bool c_isspace(int c) __attribute__((__const__));
_Bool c_isspace(int c) __attribute__((__const__));

int c_tolower(int c) __attribute__((__const__));

ptrdiff_t argmatch(char const *arg, char const *const *arglist,
                   char const *vallist, size_t valsize)
    __attribute__((__pure__));

void argmatch_invalid(char const *context, char const *value,
                      ptrdiff_t problem);
void argmatch_valid(char const *const *arglist, char const *vallist,
                    size_t valsize);
ptrdiff_t __xargmatch_internal(char const *context, char const *arg,
                               char const *const *arglist, char const *vallist,
                               size_t valsize, void (*exit_fn)(void));
extern int putc_unlocked(int __c, FILE *__stream);
__attribute__((__noreturn__)) void usage(int status);
static void __argmatch_die(void) {}
void (*argmatch_die)(void) = &__argmatch_die;
ptrdiff_t argmatch(char const *arg, char const *const *arglist,
                   char const *vallist, size_t valsize)
    __attribute__((__pure__));
ptrdiff_t argmatch(char const *arg, char const *const *arglist,
                   char const *vallist, size_t valsize) {

  ptrdiff_t matchind;

  {
    { matchind = (ptrdiff_t)-1; }

    { return (matchind); }
  }
}
void argmatch_invalid(char const *context, char const *value,
                      ptrdiff_t problem) {
  char const *format;
  char *tmp;

  char *tmp___1;
  char const *tmp___2;
  char *tmp___3;

  {
    {

      tmp = gettext("invalid argument %s for %s");
      tmp___1 = tmp;
    }

    {
      format = (char const *)tmp___1;
      tmp___2 = quote_n(1, context);
      tmp___3 = quotearg_n_style(0, (enum quoting_style)6, value);
      error(0, 0, format, tmp___3, tmp___2);
    }
  }
}

ptrdiff_t __xargmatch_internal(char const *context, char const *arg,
                               char const *const *arglist, char const *vallist,
                               size_t valsize, void (*exit_fn)(void)) {
  ptrdiff_t res;
  ptrdiff_t tmp;

  {
    {
      tmp = argmatch(arg, arglist, vallist, valsize);
      res = tmp;
    }

    { argmatch_invalid(context, arg, res); }
    return ((ptrdiff_t)-1);
  }
}
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
int match_icase;
int match_words;
int match_lines;
unsigned char eolbyte;
int using_utf8(void);
void Pcompile(char const *pattern, size_t size);
size_t Pexecute(char const *buf, size_t size, size_t *match_size,
                char const *start_ptr);
extern pcre *pcre_compile(char const *, int, char const **, int *,
                          unsigned char const *);
extern int pcre_exec(pcre const *, pcre_extra const *, char const *, int, int,
                     int, int *, int);
extern int pcre_fullinfo(pcre const *, pcre_extra const *, int, void *);
extern unsigned char const *pcre_maketables(void);
extern pcre_extra *pcre_study(pcre const *, int, char const **);
extern pcre_jit_stack *pcre_jit_stack_alloc(int, int);
extern void pcre_assign_jit_stack(pcre_extra *, pcre_jit_stack *(*)(void *),
                                  void *);

void Pcompile(char const *pattern, size_t size) {}
size_t Pexecute(char const *buf, size_t size, size_t *match_size,
                char const *start_ptr) {
  int sub[300] = {0};

  {

    ;
    { return ((size_t)-1); }
  }
}
void kwsincr(kwset_t kwset___1, char const *text, size_t len);
void kwsprep(kwset_t kwset___1);
size_t(__attribute__((__nonnull__(4))) kwsexec)(kwset_t kwset___1,
                                                char const *text, size_t size,
                                                struct kwsmatch *kwsmatch);
void kwsinit(kwset_t *kwset___1);
char *mbtoupper(char const *beg, size_t *n, mb_len_map_t **len_map_p);
ptrdiff_t mb_goback(char const **mb_start, char const *cur, char const *end);
wint_t mb_prev_wc(char const *buf, char const *cur, char const *end);
wint_t mb_next_wc(char const *cur, char const *end);
void Fcompile(char const *pattern, size_t size);
size_t Fexecute(char const *buf, size_t size, size_t *match_size,
                char const *start_ptr);

static kwset_t kwset;
void Fcompile(char const *pattern, size_t size) {
  size_t total;

  char const *pat;

  char const *tmp___1;

  char const *p;
  size_t len;

  {
    total = size;

    { tmp___1 = pattern; }

    {
      pat = tmp___1;
      kwsinit(&kwset);
      p = pat;
    }
    {
      {
        ;

        { len = total; }

        { kwsincr(kwset, p, len); }
      };
    }
    { kwsprep(kwset); }
  }
}

size_t Fexecute(char const *buf, size_t size, size_t *match_size,
                char const *start_ptr) {
  char const *beg;

  char const *end;

  size_t len;
  char eol;
  struct kwsmatch kwsmatch;
  size_t ret_val;

  size_t offset;
  size_t tmp___1;

  size_t off;

  {
    { eol = (char)eolbyte; }

    { beg = buf; }

    {
      {
        ;

        {
          tmp___1 = kwsexec(kwset, beg - match_lines,
                            (size_t)(((buf + size) - beg) + (long)match_lines),
                            &kwsmatch);
          offset = tmp___1;
        }

        len = kwsmatch.size[0] - (size_t)match_lines;

        beg += offset;
      };
    };

    {
      end = (char const *)memchr((void const *)(beg + len), (int)eol,
                                 (size_t)((buf + size) - (beg + len)));
    }
    { end++; }

    len = (size_t)(end - beg);
    {
      off = (size_t)(beg - buf);

      *match_size = len;
      ret_val = off;
    }
    return (ret_val);
  }
}
kwset_t kwsalloc(char const *trans___0);
static unsigned char to_uchar(char ch) { return ((unsigned char)ch); }
extern void _obstack_newchunk(struct obstack *, int);
extern int _obstack_begin(struct obstack *, int, int, void *(*)(long),
                          void (*)(void *));

kwset_t kwsalloc(char const *trans___0) {
  struct kwset *kwset___1;
  struct kwset *tmp;
  struct obstack *__h;
  struct obstack *__o;
  int __len;
  struct obstack *__o1;
  void *__value;

  {
    {
      tmp = (struct kwset *)xmalloc(sizeof(*kwset___1));
      kwset___1 = tmp;
      _obstack_begin(&kwset___1->obstack, 0, 0, (void *(*)(long))(&xmalloc),
                     &free);

      __h = &kwset___1->obstack;
      __o = __h;
      __len = (int)sizeof(*(kwset___1->trie));
    }

    __o->next_free += __len;
    __o1 = __h;
    __value = (void *)__o1->object_base;

    __o1->object_base = __o1->next_free;
    kwset___1->trie = (struct trie *)__value;

    (kwset___1->trie)->depth = 0;

    return (kwset___1);
  }
}
void kwsincr(kwset_t kwset___1, char const *text, size_t len) {
  struct trie *trie;

  unsigned char uc;
  unsigned char label___0;
  int tmp;
  struct tree *kwset_link;
  struct tree *links[12];

  int depth___0;

  struct obstack *__h;
  struct obstack *__o;
  int __len;
  struct obstack *__o1;
  void *__value;

  struct obstack *__h___0;
  struct obstack *__o___0;
  int __len___0;
  struct obstack *__o1___0;
  void *__value___0;

  size_t tmp___8;

  {
    trie = kwset___1->trie;

    text += len;
    {
      while (1) {
        ;
        tmp___8 = len;
        len--;
        if (!tmp___8) {
          goto while_break;
        }
        text--;
        uc = (unsigned char)*text;

        { tmp = (int)uc; }
        label___0 = (unsigned char)tmp;

        links[0] = (struct tree *)(&trie->links);

        depth___0 = 1;

        {
          __h = &kwset___1->obstack;
          __o = __h;
          __len = (int)sizeof(*kwset_link);

          __o->next_free += __len;
          __o1 = __h;
          __value = (void *)__o1->object_base;

          __o1->object_base = __o1->next_free;
          kwset_link = (struct tree *)__value;

          __h___0 = &kwset___1->obstack;
          __o___0 = __h___0;
          __len___0 = (int)sizeof(*(kwset_link->trie));

          __o___0->next_free += __len___0;
          __o1___0 = __h___0;
          __value___0 = (void *)__o1___0->object_base;

          __o1___0->object_base = __o1___0->next_free;
          kwset_link->trie = (struct trie *)__value___0;

          (kwset_link->trie)->links = (struct tree *)((void *)0);

          (kwset_link->trie)->next = (struct trie *)((void *)0);

          (kwset_link->trie)->depth = trie->depth + 1;

          kwset_link->label = label___0;

          depth___0--;
          { (links[depth___0])->llink = kwset_link; }
        }
        trie = kwset_link->trie;
      };
    }
  while_break:;

    { kwset___1->mind = trie->depth; }
  }
}
static void enqueue(struct tree *tree, struct trie **last) {
  struct trie *tmp;

  {
    if (!tree) {
      return;
    }
    {

      tmp = tree->trie;
      (*last)->next = tmp;
      *last = tmp;
    }
  }
}

static void treedelta(struct tree const *tree, unsigned int depth___0,
                      unsigned char *delta) {

  if (!tree) {
    return;
  }

  { *(delta + (int const)tree->label) = (unsigned char)depth___0; }
}

void kwsprep(kwset_t kwset___1) {

  unsigned char deltabuf[256];
  unsigned char *delta;
  unsigned char *tmp;
  int tmp___0;
  struct trie *curr;
  struct trie *last;

  {

    { tmp = kwset___1->delta; }
    delta = tmp;
    { tmp___0 = kwset___1->mind; }

    {
      memset((void *)delta, tmp___0, sizeof(deltabuf));
      last = kwset___1->trie;
      curr = last;
    }
    {
      while (1) {
        ;

        if (!curr) {
          goto while_break;
        }
        {
          enqueue(curr->links, &last);

          treedelta((struct tree const *)curr->links, (unsigned int)curr->depth,
                    delta);
        }

        curr = curr->next;
      };
    }
  while_break:
    curr = (kwset___1->trie)->next;
  }
}
static _Bool bm_delta2_search(char const **tpp, char const *ep, char const *sp,
                              int len, char const *trans___0, char gc1,
                              char gc2, unsigned char const *d1,
                              kwset_t kwset___1) {
  char const *tp;

  {
    tp = *tpp;

    {
      {
        ;

        {

          ;
          {

            *tpp = tp - len;
            return ((_Bool)1);
          }
        }
      };
    }
  }
}

static size_t __attribute__((__pure__))
bmexec_trans(kwset_t kwset___1, char const *text, size_t size) {
  unsigned char const *d1;
  char const *ep;
  char const *sp;
  char const *tp;
  int d;
  int len;
  char const *trans___0;

  char gc1;
  char gc2;

  unsigned char tmp___11;
  unsigned char tmp___12;
  _Bool tmp___13;

  {
    len = kwset___1->mind;
    trans___0 = kwset___1->trans;

    d1 = (unsigned char const *)(kwset___1->delta);
    sp = (char const *)(kwset___1->target + len);
    tp = text + len;
    gc1 = kwset___1->gc1;
    gc2 = kwset___1->gc2;

    {
      ep = text + size;
      tmp___11 = to_uchar((char)*(tp + -1));
      d = (int)*(d1 + (int)tmp___11);
    }
    {
      {
        ;
      while_continue___0:;
        if (!((long)d <= ep - tp)) {
          goto while_break___0;
        }
        {
          tp += d;
          tmp___12 = to_uchar((char)*(tp + -1));
          d = (int)*(d1 + (int)tmp___12);
        }
        if (d != 0) {
          goto while_continue___0;
        }
        {
          tmp___13 =
              bm_delta2_search(&tp, ep, sp, len, trans___0, gc1, gc2,
                               (unsigned char const *)((void *)0), kwset___1);
        }
        { return ((size_t __attribute__((__pure__)))(tp - text)); }
      };
    }
  while_break___0:;
    return ((size_t __attribute__((__pure__))) - 1);
  }
}
static size_t bmexec(kwset_t kwset___1, char const *text, size_t size) {
  size_t __attribute__((__pure__)) tmp;

  size_t __attribute__((__pure__)) tmp___1;

  {
    {

      tmp = bmexec_trans(kwset___1, text, size);
      tmp___1 = tmp;
    }

    return ((size_t)tmp___1);
  }
}

size_t(__attribute__((__nonnull__(4))) kwsexec)(kwset_t kwset___1,
                                                char const *text, size_t size,
                                                struct kwsmatch *kwsmatch) {
  size_t ret;
  size_t tmp;

  {

    {
      tmp = bmexec(kwset___1, text, size);
      ret = tmp;
    }
    { kwsmatch->size[0] = (size_t)kwset___1->mind; }
    return (ret);
  }
}
extern reg_syntax_t re_set_syntax(reg_syntax_t __syntax);
extern char const *re_compile_pattern(char const *__pattern, size_t __length,
                                      struct re_pattern_buffer *__buffer);
extern regoff_t re_search(struct re_pattern_buffer *__buffer,
                          char const *__string, __re_idx_t __length,
                          __re_idx_t __start, regoff_t __range,
                          struct re_registers *__regs);
extern regoff_t re_match(struct re_pattern_buffer *__buffer,
                         char const *__string, __re_idx_t __length,
                         __re_idx_t __start, struct re_registers *__regs);
struct dfa *dfaalloc(void);
struct dfamust *__attribute__((__pure__)) dfamusts(struct dfa const *d);
void dfasyntax(reg_syntax_t bits, int fold, unsigned char eol);
void dfacomp(char const *s, size_t len, struct dfa *d, int searchflag);
char *dfaexec(struct dfa *d, char const *begin, char *end, int allow_nl,
              size_t *count, int *backref);
struct dfa *dfasuperset(struct dfa const *d) __attribute__((__pure__));
_Bool dfaisfast(struct dfa const *d) __attribute__((__pure__));
void dfawarn(char const *mesg);
__attribute__((__noreturn__)) void dfaerror(char const *mesg);
void GEAcompile(char const *pattern, size_t size, reg_syntax_t syntax_bits___0);
size_t EGexecute(char const *buf, size_t size, size_t *match_size,
                 char const *start_ptr);

static struct dfa *dfa;
static struct patterns patterns0;
static struct patterns *patterns;
static size_t pcount;

__attribute__((__noreturn__)) void dfaerror(char const *mesg);
void dfaerror(char const *mesg) {}

void dfawarn(char const *mesg) {}

static char const line_beg_bk[4] = {(char const)'^', (char const)'\\',
                                    (char const)'(', (char const)'\000'};
static char const line_end_bk[4] = {(char const)'\\', (char const)')',
                                    (char const)'$', (char const)'\000'};
static char const word_beg_bk[23] = {
    (char const)'\\', (char const)'(', (char const)'^',   (char const)'\\',
    (char const)'|',  (char const)'[', (char const)'^',   (char const)'[',
    (char const)':',  (char const)'a', (char const)'l',   (char const)'n',
    (char const)'u',  (char const)'m', (char const)':',   (char const)']',
    (char const)'_',  (char const)']', (char const)'\\',  (char const)')',
    (char const)'\\', (char const)'(', (char const)'\000'};
static char const word_end_bk[23] = {
    (char const)'\\', (char const)')',  (char const)'\\',  (char const)'(',
    (char const)'[',  (char const)'^',  (char const)'[',   (char const)':',
    (char const)'a',  (char const)'l',  (char const)'n',   (char const)'u',
    (char const)'m',  (char const)':',  (char const)']',   (char const)'_',
    (char const)']',  (char const)'\\', (char const)'|',   (char const)'$',
    (char const)'\\', (char const)')',  (char const)'\000'};
void GEAcompile(char const *pattern, size_t size,
                reg_syntax_t syntax_bits___0) {
  size_t total;
  char *motif;
  char const *p;
  size_t len;

  char const *tmp___0;

  char *n;
  char *tmp___1;
  char const *tmp___2;

  char const *tmp___4;
  char const *tmp___5;

  char const *tmp___7;
  size_t tmp___8;

  {
    total = size;

    {

      dfasyntax(syntax_bits___0, match_icase, eolbyte);
      p = pattern;
    }
    {
      {
        ;

        { len = total; }
        {
          patterns = (struct patterns *)xnrealloc(
              (void *)patterns, pcount + 1UL, sizeof(*patterns));
          *(patterns + pcount) = patterns0;
          tmp___0 = re_compile_pattern(p, len, &(patterns + pcount)->regexbuf);
        }
      };
    };

    {
      if (match_lines) {
        {

          tmp___1 = (char *)xmalloc(((sizeof(word_beg_bk) - 1UL) + size) +
                                    sizeof(word_end_bk));
          n = tmp___1;
        }
        {
          { tmp___2 = line_beg_bk; }

          tmp___4 = tmp___2;
        }

        {
          strcpy((char * /* __restrict  */)n,
                 (char const * /* __restrict  */)tmp___4);
          total = strlen((char const *)n);
          memcpy((void * /* __restrict  */)((void *)(n + total)),
                 (void const * /* __restrict  */)((void const *)pattern), size);
          total += size;
        }
        {
          { tmp___5 = line_end_bk; }

          tmp___7 = tmp___5;
        }

        {
          strcpy((char * /* __restrict  */)(n + total),
                 (char const * /* __restrict  */)tmp___7);
          tmp___8 = strlen((char const *)(n + total));
          total += tmp___8;
          motif = n;
          pattern = (char const *)motif;
          size = total;
        }
      } else {
      }
    }
    {
      dfa = dfaalloc();
      dfacomp(pattern, size, dfa, 1);
    }
  }
}
size_t EGexecute(char const *buf, size_t size, size_t *match_size,
                 char const *start_ptr) {
  char const *buflim___0;
  char const *beg;
  char const *end;
  char const *ptr;

  char eol;
  int backref;
  regoff_t start;
  size_t len;

  size_t i;

  char const *next_beg;
  char const *dfa_beg;
  size_t count;

  size_t off;

  {
    {
      eol = (char)eolbyte;

      buflim___0 = buf + size;
      end = buf;
      beg = end;
    }
    {
      {
        ;

        end = buflim___0;
        if (!start_ptr) {
          dfa_beg = beg;
          count = (size_t)0;

          {
            next_beg = (char const *)dfaexec(dfa, dfa_beg, (char *)end, 0,
                                             &count, &backref);
          }
          if ((unsigned long)next_beg == (unsigned long)((void *)0)) {
            goto __Cont;
          } else {
          }
          if (count != 0UL) {

            beg = (char const *)memrchr((void const *)buf, (int)eol,
                                        (size_t)(next_beg - buf));
            beg++;
          }
          {
            end = (char const *)memchr((void const *)next_beg, (int)eol,
                                       (size_t)(buflim___0 - next_beg));
          }
          { end++; }

          { goto success; }

        } else {
          ptr = start_ptr;
        }

        i = (size_t)0;
        {
          {
            ;

            {

              start = re_search(
                  &(patterns + i)->regexbuf, beg,
                  (__re_idx_t)((end - beg) - 1L), (__re_idx_t)(ptr - beg),
                  (regoff_t)((end - ptr) - 1L), &(patterns + i)->regs);
            }

            { len = (size_t)(*((patterns + i)->regs.end + 0) - start); }
          };
        };
        { goto success_in_len; }
      __Cont:
        beg = end;
      };
    };

  success:
    len = (size_t)(end - beg);
  success_in_len:
    off = (size_t)(beg - buf);
    *match_size = len;
    return (off);
  }
}
void dfafree(struct dfa *d);
void dfainit(struct dfa *d);
void dfaparse(char const *s, size_t len, struct dfa *d);
void dfaanalyze(struct dfa *d, int searchflag);
void dfastate(ptrdiff_t s, struct dfa *d, ptrdiff_t *trans___0);
extern __attribute__((__nothrow__)) int isalnum(int);
extern __attribute__((__nothrow__)) int isalpha(int);
extern __attribute__((__nothrow__)) int iscntrl(int);
extern __attribute__((__nothrow__)) int isdigit(int);
extern __attribute__((__nothrow__)) int islower(int);
extern __attribute__((__nothrow__)) int isgraph(int);
extern __attribute__((__nothrow__)) int isprint(int);
extern __attribute__((__nothrow__)) int ispunct(int);
extern __attribute__((__nothrow__)) int isspace(int);
extern __attribute__((__nothrow__)) int isupper(int);
extern __attribute__((__nothrow__)) int isxdigit(int);
extern __attribute__((__nothrow__)) int toupper(int __c);
extern __attribute__((__nothrow__)) int isblank(int);
extern
    __attribute__((__nothrow__)) char *(__attribute__((__nonnull__(1, 2)))
                                        strncpy)(char *__restrict __dest,
                                                 char const *__restrict __src,
                                                 size_t __n);
extern __attribute__((__nothrow__)) int(__attribute__((__nonnull__(1, 2)))
                                        strcoll)(char const *__s1,
                                                 char const *__s2)
    __attribute__((__pure__));
extern __attribute__((__nothrow__)) char *setlocale(int __category,
                                                    char const *__locale);
extern __attribute__((__nothrow__)) int wctob(wint_t __c);
extern __attribute__((__nothrow__)) size_t
wcrtomb(char *__restrict __s, wchar_t __wc, mbstate_t *__restrict __ps);
extern __attribute__((__nothrow__)) int iswalpha(wint_t __wc);
extern __attribute__((__nothrow__)) wctype_t wctype(char const *__property);
extern __attribute__((__nothrow__)) int iswctype(wint_t __wc, wctype_t __desc);
extern __attribute__((__nothrow__)) wint_t towupper(wint_t __wc);
static unsigned char to_uchar___0(char ch) { return ((unsigned char)ch); }
static void dfamust(struct dfa *d);
static void regexp(void);

static size_t mbs_to_wchar(wint_t *pwc, char const *s, size_t n,
                           struct dfa *d) {

  return ((size_t)1);
}

static void setbit(unsigned int b, charclass_word *c) {

  *(c + b / 32U) |= 1U << b % 32U;
}
static void clrbit(unsigned int b, charclass_word *c) {}
static void copyset(charclass_word *const src, charclass_word *dst) {

  memcpy((void * /* __restrict  */)((void *)dst),
         (void const * /* __restrict  */)((void const *)src),
         sizeof(charclass));
}
static void zeroset(charclass_word *s) {

  memset((void *)s, 0, sizeof(charclass));
}
static void notset(charclass_word *s) {
  int i;

  {
    i = 0;
    {
      while (1) {
        ;

        if (!(i < 8)) {
          goto while_break;
        }
        *(s + i) = (((1U << 31) << 1) - 1U) & ~*(s + i);
        i++;
      };
    }
  while_break:;
  }
}
static _Bool equal(charclass_word *const s1, charclass_word *const s2) {
  int tmp;

  {
    { tmp = memcmp((void const *)s1, (void const *)s2, sizeof(charclass)); }
    return ((_Bool)(tmp == 0));
  }
}
static void *maybe_realloc(void *ptr, size_t nitems, size_t *nalloc,
                           size_t itemsize) {
  void *tmp;

  {

    {
      *nalloc = nitems;
      tmp = x2nrealloc(ptr, nalloc, itemsize);
    }
    return (tmp);
  }
}
static size_t dfa_charclass_index(struct dfa *d, charclass_word *const s) {
  size_t i;

  {
    i = (size_t)0;
    {
      while (1) {
        ;

        if (!(i < d->cindex)) {
          goto while_break;
        }

        i++;
      };
    }
  while_break : {
    d->charclasses =
        (charclass *)maybe_realloc((void *)d->charclasses, d->cindex,
                                   &d->calloc, sizeof(*(d->charclasses)));
    (d->cindex)++;
    copyset(s, *(d->charclasses + i));
  }
    return (i);
  }
}
static struct dfa *dfa___0;
static size_t charclass_index(charclass_word *const s) {
  size_t tmp;

  {
    { tmp = dfa_charclass_index(dfa___0, s); }
    return (tmp);
  }
}
static reg_syntax_t syntax_bits;

static _Bool case_fold;
static unsigned char eolbyte___0;
static int sbit[256];
static charclass letters;
static charclass newline;
static int char_context(unsigned char c) {

  if ((int)c == (int)eolbyte___0) {
    return (4);
  }

  return (1);
}

void dfasyntax(reg_syntax_t bits, int fold, unsigned char eol) {
  unsigned int i;

  {

    syntax_bits = bits;
    case_fold = (_Bool)(fold != 0);
    eolbyte___0 = eol;
    i = 0U;
    {
      while (1) {
        ;

        if (!(i < 256U)) {
          goto while_break;
        }
        { sbit[i] = char_context((unsigned char)i); }

        i++;
      };
    }
  while_break:;
  }
}

static void setbit_case_fold_c(int b, charclass_word *c) {
  int ub;
  int tmp;
  int i;
  int tmp___0;

  {
    {
      tmp = toupper(b);
      ub = tmp;
      i = 0;
    }
    {
      while (1) {
        ;

        if (!(i < 256)) {
          goto while_break;
        }
        { tmp___0 = toupper(i); }
        if (tmp___0 == ub) {

          setbit((unsigned int)i, c);
        }
        i++;
      };
    }
  while_break:;
  }
}

static _Bool using_simple_locale(void);
static int unibyte_c = -1;
static _Bool using_simple_locale(void) { return ((_Bool)unibyte_c); }
static char const *lexptr;
static size_t lexleft;
static token lasttok;
static _Bool laststart;
static size_t parens;
static int minrep;
static int maxrep;
static int cur_mb_len = 1;
static wint_t wctok;

static struct dfa_ctype const prednames[13] = {
    {"alpha", &isalpha, (_Bool)0},
    {"upper", &isupper, (_Bool)0},
    {"lower", &islower, (_Bool)0},
    {"digit", &isdigit, (_Bool)1},
    {"xdigit", &isxdigit, (_Bool)0},
    {"space", &isspace, (_Bool)0},
    {"punct", &ispunct, (_Bool)0},
    {"alnum", &isalnum, (_Bool)0},
    {"print", &isprint, (_Bool)0},
    {"graph", &isgraph, (_Bool)0},
    {"cntrl", &iscntrl, (_Bool)0},
    {"blank", &isblank, (_Bool)0},
    {(char const *)((void *)0), (predicate *)((void *)0), (_Bool)0}};
static struct dfa_ctype const *__attribute__((__pure__))
find_pred(char const *str) {
  unsigned int i;

  {

    ;
    return ((struct dfa_ctype const * /* __attribute__((__pure__)) */)(
        &prednames[i]));
  }
}
static charclass zeroclass;
static token parse_bracket_exp(void) {
  _Bool invert;
  int c;
  int c1;
  int c2;
  charclass ccl;
  _Bool known_bracket_exp;
  int colon_warning_state;
  wint_t wc;
  wint_t wc2;
  wint_t wc1;
  struct mb_char_classes *work_mbc;
  size_t chars_al;
  size_t ranges_al;
  size_t ch_classes_al;
  size_t equivs_al;
  size_t coll_elems_al;
  size_t tmp;

  wint_t _wc;
  size_t nbytes;
  size_t tmp___2;
  unsigned char tmp___3;

  wint_t _wc___0;
  size_t nbytes___0;
  size_t tmp___6;
  unsigned char tmp___7;

  wint_t _wc___1;
  size_t nbytes___1;
  size_t tmp___10;
  unsigned char tmp___11;
  char str[33];
  size_t len;

  wint_t _wc___2;
  size_t nbytes___2;
  size_t tmp___14;
  unsigned char tmp___15;
  size_t tmp___16;

  wint_t _wc___3;
  size_t nbytes___3;
  size_t tmp___19;
  unsigned char tmp___20;
  char const *class;
  char const *tmp___23;
  int tmp___24;

  struct dfa_ctype const *pred;
  struct dfa_ctype const *tmp___26;
  char *tmp___27;
  wctype_t wt;
  wctype_t tmp___28;
  size_t tmp___29;
  int tmp___30;

  wint_t _wc___4;
  size_t nbytes___4;
  size_t tmp___33;
  unsigned char tmp___34;
  char *tmp___35;
  char *tmp___36;

  char *tmp___39;
  char *tmp___40;

  wint_t _wc___7;
  size_t nbytes___7;
  size_t tmp___45;
  unsigned char tmp___46;
  char *tmp___47;
  char *tmp___48;

  int uc;
  int tmp___57;
  int uc2;
  int tmp___58;
  int uc1;
  int tmp___59;
  _Bool tmp___60;

  wint_t _wc___9;
  size_t nbytes___9;
  size_t tmp___63;
  unsigned char tmp___64;
  int tmp___65;

  char *tmp___70;

  _Bool tmp___73;
  size_t tmp___74;

  {
    known_bracket_exp = (_Bool)1;
    wc1 = (wint_t)0;
    coll_elems_al = (size_t)0;
    equivs_al = coll_elems_al;
    ch_classes_al = equivs_al;
    ranges_al = ch_classes_al;
    chars_al = ranges_al;
    {

      dfa___0->mbcsets = (struct mb_char_classes *)maybe_realloc(
          (void *)dfa___0->mbcsets, dfa___0->nmbcsets, &dfa___0->mbcsets_alloc,
          sizeof(*(dfa___0->mbcsets)));
      tmp = dfa___0->nmbcsets;
      (dfa___0->nmbcsets)++;
      work_mbc = dfa___0->mbcsets + tmp;
      memset((void *)work_mbc, 0, sizeof(*work_mbc));
    }

    { memset((void *)(ccl), 0, sizeof(ccl)); }
    {
      {
        ;

        {
          {
            tmp___2 = mbs_to_wchar(&_wc, lexptr, lexleft, dfa___0);
            nbytes = tmp___2;
            cur_mb_len = (int)nbytes;
            wc = _wc;
          }
          {

            tmp___3 = to_uchar___0((char)*lexptr);
            c = (int)tmp___3;
          }

          lexptr += nbytes;
          lexleft -= nbytes;
        }
        goto while_break;
      };
    }
  while_break:;
    if (c == 94) {
      {
        {
          ;

          {
            {
              tmp___6 = mbs_to_wchar(&_wc___0, lexptr, lexleft, dfa___0);
              nbytes___0 = tmp___6;
              cur_mb_len = (int)nbytes___0;
              wc = _wc___0;
            }
            {

              tmp___7 = to_uchar___0((char)*lexptr);
              c = (int)tmp___7;
            }

            lexptr += nbytes___0;
            lexleft -= nbytes___0;
          }
          goto while_break___0;
        };
      }
    while_break___0 : {
      invert = (_Bool)1;
      known_bracket_exp = using_simple_locale();
    }
    } else {
      invert = (_Bool)0;
    }
    colon_warning_state = c == 58;
    {
      while (1) {
        ;
        c1 = 256;
        colon_warning_state &= -3;
        {
          {
            {
              ;

              {
                {
                  tmp___10 = mbs_to_wchar(&_wc___1, lexptr, lexleft, dfa___0);
                  nbytes___1 = tmp___10;
                  cur_mb_len = (int)nbytes___1;
                  wc1 = _wc___1;
                }
                {

                  tmp___11 = to_uchar___0((char)*lexptr);
                  c1 = (int)tmp___11;
                }

                lexptr += nbytes___1;
                lexleft -= nbytes___1;
              }
              goto while_break___2;
            };
          }
        while_break___2:;

          {

            if (c1 == 61) {

              len = (size_t)0;
              {
                {
                  ;

                  {
                    {
                      ;

                      {
                        {
                          tmp___14 =
                              mbs_to_wchar(&_wc___2, lexptr, lexleft, dfa___0);
                          nbytes___2 = tmp___14;
                          cur_mb_len = (int)nbytes___2;
                          wc = _wc___2;
                        }
                        {

                          tmp___15 = to_uchar___0((char)*lexptr);
                          c = (int)tmp___15;
                        }

                        lexptr += nbytes___2;
                        lexleft -= nbytes___2;
                      }
                      goto while_break___4;
                    };
                  }
                while_break___4:;
                  { goto while_break___3; }

                  {
                    tmp___16 = len;
                    len++;
                    str[tmp___16] = (char)c;
                  }
                };
              }
            while_break___3:
              str[len] = (char)'\000';
              {
                {
                  ;

                  {
                    {
                      tmp___19 =
                          mbs_to_wchar(&_wc___3, lexptr, lexleft, dfa___0);
                      nbytes___3 = tmp___19;
                      cur_mb_len = (int)nbytes___3;
                      wc = _wc___3;
                    }
                    {

                      tmp___20 = to_uchar___0((char)*lexptr);
                      c = (int)tmp___20;
                    }

                    lexptr += nbytes___3;
                    lexleft -= nbytes___3;
                  }
                  goto while_break___5;
                };
              }
            while_break___5:;
              { {{tmp___24 = strcmp((char const *)(str), "upper"); }
              { tmp___23 = "alpha"; }
            }

            {
              class = tmp___23;
              tmp___26 = (struct dfa_ctype const *)find_pred(class);
              pred = tmp___26;
            }
            {

              tmp___27 = gettext("invalid character class");
              dfaerror((char const *)tmp___27);
            }
            {

              tmp___28 = wctype(class);
              wt = tmp___28;
              work_mbc->ch_classes = (wctype_t *)maybe_realloc(
                  (void *)work_mbc->ch_classes, work_mbc->nch_classes,
                  &ch_classes_al, sizeof(*(work_mbc->ch_classes)));
              tmp___29 = work_mbc->nch_classes;
              (work_mbc->nch_classes)++;
              *(work_mbc->ch_classes + tmp___29) = wt;
            }
            c2 = 0;
            {
              {
                ;

                { goto while_break___6; }
                { tmp___30 = (*(pred->func))(c2); }
                { setbit((unsigned int)c2, ccl); }
                c2++;
              };
            }
          while_break___6:;
          }

          colon_warning_state |= 8;
          {
            {
              ;

              {
                {
                  tmp___33 = mbs_to_wchar(&_wc___4, lexptr, lexleft, dfa___0);
                  nbytes___4 = tmp___33;
                  cur_mb_len = (int)nbytes___4;
                  wc1 = _wc___4;
                }
                {

                  tmp___34 = to_uchar___0((char)*lexptr);
                  c1 = (int)tmp___34;
                }

                lexptr += nbytes___4;
                lexleft -= nbytes___4;
              }
              goto while_break___7;
            };
          }
        while_break___7:;
          goto __Cont;
        }
      }
    }
    {
      if (syntax_bits & 1UL) {
        {
          {
            ;

            {
              { tmp___36 = gettext("unbalanced ["); }
              {

                tmp___35 = gettext("unbalanced [");
                dfaerror((char const *)tmp___35);
              }
            }

            goto while_break___8;
          };
        }
      while_break___8:;
      }
    }
    if (c1 == 256) {
      {
        {
          ;

          {
            { tmp___40 = gettext("unbalanced ["); }
            {

              tmp___39 = gettext("unbalanced [");
              dfaerror((char const *)tmp___39);
            }
          }

          goto while_break___9;
        };
      }
    while_break___9:;
    }
    if (c1 == 45) {
      {
        {
          ;

          {
            {
              tmp___45 = mbs_to_wchar(&_wc___7, lexptr, lexleft, dfa___0);
              nbytes___7 = tmp___45;
              cur_mb_len = (int)nbytes___7;
              wc2 = _wc___7;
            }
            {

              tmp___46 = to_uchar___0((char)*lexptr);
              c2 = (int)tmp___46;
            }

            lexptr += nbytes___7;
            lexleft -= nbytes___7;
          }
          goto while_break___10;
        };
      }
    while_break___10:;
      {
        if ((int const) * lexptr == 46) {
          known_bracket_exp = (_Bool)0;
          c2 = ']';
        }
      }
      {
        {
          if (syntax_bits & 1UL) {
            {
              {
                ;

                {
                  { tmp___48 = gettext("unbalanced ["); }
                  {

                    tmp___47 = gettext("unbalanced [");
                    dfaerror((char const *)tmp___47);
                  }
                }

                goto while_break___11;
              };
            }
          while_break___11:;
          }
        }

        {
          { tmp___60 = using_simple_locale(); }
          {
            c1 = c;
            {
              {
                ;

                { goto while_break___12; }
                {
                  setbit((unsigned int)c1, ccl);
                  c1++;
                }
              };
            }
          while_break___12:;
            {
              {
                tmp___57 = toupper(c);
                uc = tmp___57;
                tmp___58 = toupper(c2);
                uc2 = tmp___58;
                c1 = 0;
              }
              {
                while (1) {
                  ;

                  if (!(c1 < 256)) {
                    goto while_break___13;
                  }
                  {
                    tmp___59 = toupper(c1);
                    uc1 = tmp___59;
                  }
                  { setbit((unsigned int)c1, ccl); }
                  c1++;
                };
              }
            while_break___13:;
            }
          }
        }
        colon_warning_state |= 8;
        {
          {
            ;

            {
              {
                tmp___63 = mbs_to_wchar(&_wc___9, lexptr, lexleft, dfa___0);
                nbytes___9 = tmp___63;
                cur_mb_len = (int)nbytes___9;
                wc1 = _wc___9;
              }
              {

                tmp___64 = to_uchar___0((char)*lexptr);
                c1 = (int)tmp___64;
              }

              lexptr += nbytes___9;
              lexleft -= nbytes___9;
            }
            goto while_break___14;
          };
        }
      while_break___14:;
        goto __Cont;
      }
      lexptr -= cur_mb_len;
      lexleft += (size_t)cur_mb_len;
    }
    { tmp___65 = 2; }

    colon_warning_state |= tmp___65;
    {

      { setbit((unsigned int)c, ccl); }
      goto __Cont;
    }
    { known_bracket_exp = (_Bool)0; }

  __Cont:
    wc = wc1;
    c = c1;
    if (!(c != 93)) {
      goto while_break___1;
    }
  };
}
while_break___1:;
{

  tmp___70 = gettext("character class syntax is [[:space:]], not [:space:]");
  dfawarn((char const *)tmp___70);
}
if (!known_bracket_exp) {
  return ((token)257);
}
if (dfa___0->multibyte) {
  {
    work_mbc->invert = invert;
    tmp___73 = equal((charclass_word * /* const  */)(ccl),
                     (charclass_word * /* const  */)(zeroclass));
  }
  { work_mbc->cset = (ptrdiff_t)-1; }

  return ((token)273);
}
if (invert) {
  if (!(!dfa___0->multibyte)) {

    __assert_fail("!dfa->multibyte",
                  "/home/khheo/project/benchmark/grep-2.19/src/dfa.c", 1232U,
                  "parse_bracket_exp");
  }
  { notset(ccl); }
  { clrbit((unsigned int)eolbyte___0, ccl); }
}
{ tmp___74 = charclass_index((charclass_word * /* const  */)(ccl)); }
return ((token)(275UL + tmp___74));
}
}
static token lex(void) {
  int c;
  int c2;
  _Bool backslash;
  charclass ccl;
  int i;
  wint_t _wc;
  size_t nbytes;
  size_t tmp;
  unsigned char tmp___0;
  char *tmp___1;

  char const *p;
  char const *lim;
  char *tmp___8;
  char const *tmp___9;
  char const *tmp___10;
  char *tmp___11;
  size_t tmp___12;
  unsigned short const **tmp___13;
  size_t tmp___14;
  char const *lexptr_saved;
  size_t lexleft_saved;
  unsigned short const **tmp___15;
  size_t tmp___16;
  size_t tmp___17;
  unsigned short const **tmp___18;

  {
    backslash = (_Bool)0;
    i = 0;
    {
      while (1) {
        ;

        if (!(i < 2)) {
          goto while_break;
        }
        {
          {
            ;

            if (!lexleft) {
              lasttok = (token)-1;
              return (lasttok);
            } else {
              {
                tmp = mbs_to_wchar(&_wc, lexptr, lexleft, dfa___0);
                nbytes = tmp;
                cur_mb_len = (int)nbytes;
                wctok = _wc;
              }
              {

                tmp___0 = to_uchar___0((char)*lexptr);
                c = (int)tmp___0;
              }

              lexptr += nbytes;
              lexleft -= nbytes;
            }
            goto while_break___0;
          };
        }
      while_break___0:;
        if (c == 92) {
          goto case_92;
        }
        if (c == 94) {
          goto case_94;
        }
        if (c == 36) {
          goto case_36;
        }
        if (c == 49) {
          goto case_49;
        }
        if (c == 50) {
          goto case_49;
        }
        if (c == 51) {
          goto case_49;
        }
        if (c == 52) {
          goto case_49;
        }
        if (c == 53) {
          goto case_49;
        }
        if (c == 54) {
          goto case_49;
        }
        if (c == 55) {
          goto case_49;
        }
        if (c == 56) {
          goto case_49;
        }
        if (c == 57) {
          goto case_49;
        }
        if (c == 96) {
          goto case_96;
        }
        if (c == 39) {
          goto case_39;
        }
        if (c == 60) {
          goto case_60;
        }
        if (c == 62) {
          goto case_62;
        }
        if (c == 98) {
          goto case_98;
        }
        if (c == 66) {
          goto case_66;
        }
        if (c == 63) {
          goto case_63;
        }
        if (c == 42) {
          goto case_42;
        }
        if (c == 43) {
          goto case_43;
        }
        if (c == 123) {
          goto case_123;
        }
        if (c == 124) {
          goto case_124;
        }
        if (c == 10) {
          goto case_10;
        }
        if (c == 40) {
          goto case_40;
        }
        if (c == 41) {
          goto case_41;
        }
        if (c == 46) {
          goto case_46;
        }
        if (c == 115) {
          goto case_115;
        }
        if (c == 83) {
          goto case_115;
        }
        if (c == 119) {
          goto case_119;
        }
        if (c == 87) {
          goto case_119;
        }
        if (c == 91) {
          goto case_91;
        }
        goto normal_char;
      case_92:
        if (backslash) {
          goto normal_char;
        }
        if (lexleft == 0UL) {

          tmp___1 = gettext("unfinished \\ escape");
          dfaerror((char const *)tmp___1);
        }
        backslash = (_Bool)1;
        goto switch_break;
      case_94:
        if (backslash) {
          goto normal_char;
        }
        {
          lasttok = (token)258;
          return (lasttok);
        }

        goto normal_char;
      case_36:
        if (backslash) {
          goto normal_char;
        }
        {
          lasttok = (token)259;
          return (lasttok);
        }

        goto normal_char;
      case_49:
        if (backslash) {

          laststart = (_Bool)0;
          lasttok = (token)257;
          return (lasttok);
        }
        goto normal_char;
      case_96 : {

        lasttok = (token)258;
        return (lasttok);
      }
        goto normal_char;
      case_39:
        if (backslash) {

          lasttok = (token)259;
          return (lasttok);
        }
        goto normal_char;
      case_60 : {

        lasttok = (token)260;
        return (lasttok);
      }
        goto normal_char;
      case_62 : {

        lasttok = (token)261;
        return (lasttok);
      }
        goto normal_char;
      case_98 : {

        lasttok = (token)262;
        return (lasttok);
      }
        goto normal_char;
      case_66 : {

        lasttok = (token)263;
        return (lasttok);
      }
        goto normal_char;
      case_63:
        if (syntax_bits &
            ((((((((((1UL << 1) << 1) << 1) << 1) << 1) << 1) << 1) << 1) << 1)
             << 1)) {
          goto normal_char;
        }
        if ((int)backslash != ((syntax_bits & (1UL << 1)) != 0UL)) {
          goto normal_char;
        }
        {
          if (laststart) {
            goto normal_char;
          }
        }
        lasttok = (token)264;
        return (lasttok);
      case_42:
        if (backslash) {
          goto normal_char;
        }
        {
          if (laststart) {
            goto normal_char;
          }
        }
        lasttok = (token)265;
        return (lasttok);
      case_43:
        if (syntax_bits &
            ((((((((((1UL << 1) << 1) << 1) << 1) << 1) << 1) << 1) << 1) << 1)
             << 1)) {
          goto normal_char;
        }
        if ((int)backslash != ((syntax_bits & (1UL << 1)) != 0UL)) {
          goto normal_char;
        }
        {
          if (laststart) {
            goto normal_char;
          }
        }
        lasttok = (token)266;
        return (lasttok);
      case_123:
        if (!(syntax_bits &
              (((((((((1UL << 1) << 1) << 1) << 1) << 1) << 1) << 1) << 1)
               << 1))) {
          goto normal_char;
        }
        if ((int)backslash !=
            ((syntax_bits &
              ((((((((((((1UL << 1) << 1) << 1) << 1) << 1) << 1) << 1) << 1)
                  << 1)
                 << 1)
                << 1)
               << 1)) == 0UL)) {
          goto normal_char;
        }
        {
          if (laststart) {
            goto normal_char;
          }
        }
        p = lexptr;
        lim = p + lexleft;
        maxrep = -1;
        minrep = maxrep;
        {
          {
            ;

            { goto while_break___1; }

            { minrep = (int)((int const) * p - 48); }

            p++;
          };
        }
      while_break___1:;
        { maxrep = minrep; }

        {
          if ((unsigned long)p != (unsigned long)lim) {
            tmp___9 = p;
            p++;
            {

              tmp___10 = p;
              p++;
              {

                if (!(minrep <= maxrep)) {
                  goto _L___4;
                }
              }
            }

          } else {
          _L___4 : { goto normal_char; }
            {
              tmp___8 = gettext("Invalid content of \\{\\}");
              dfaerror((char const *)tmp___8);
            }
          }
        }
        if (32767 < maxrep) {

          tmp___11 = gettext("Regular expression too big");
          dfaerror((char const *)tmp___11);
        }
        lexptr = p;
        lexleft = (size_t)(lim - p);
        laststart = (_Bool)0;
        lasttok = (token)267;
        return (lasttok);
      case_124:
        if (syntax_bits &
            ((((((((((1UL << 1) << 1) << 1) << 1) << 1) << 1) << 1) << 1) << 1)
             << 1)) {
          goto normal_char;
        }
        if ((int)backslash !=
            ((syntax_bits &
              (((((((((((((((1UL << 1) << 1) << 1) << 1) << 1) << 1) << 1) << 1)
                     << 1)
                    << 1)
                   << 1)
                  << 1)
                 << 1)
                << 1)
               << 1)) == 0UL)) {
          goto normal_char;
        }
        laststart = (_Bool)1;
        lasttok = (token)269;
        return (lasttok);
      case_10 : { goto normal_char; }

        laststart = (_Bool)1;
        lasttok = (token)269;
        return (lasttok);
      case_40:
        if ((int)backslash !=
            ((syntax_bits &
              (((((((((((((1UL << 1) << 1) << 1) << 1) << 1) << 1) << 1) << 1)
                   << 1)
                  << 1)
                 << 1)
                << 1)
               << 1)) == 0UL)) {
          goto normal_char;
        }
        parens++;
        laststart = (_Bool)1;
        lasttok = (token)270;
        return (lasttok);
      case_41:
        if ((int)backslash !=
            ((syntax_bits &
              (((((((((((((1UL << 1) << 1) << 1) << 1) << 1) << 1) << 1) << 1)
                   << 1)
                  << 1)
                 << 1)
                << 1)
               << 1)) == 0UL)) {
          goto normal_char;
        }
        {
          if (syntax_bits &
              (((((((((((((((((1UL << 1) << 1) << 1) << 1) << 1) << 1) << 1)
                        << 1)
                       << 1)
                      << 1)
                     << 1)
                    << 1)
                   << 1)
                  << 1)
                 << 1)
                << 1)
               << 1)) {
            goto normal_char;
          }
        }
        parens--;
        laststart = (_Bool)0;
        lasttok = (token)271;
        return (lasttok);
      case_46:
        if (backslash) {
          goto normal_char;
        }
        {
          laststart = (_Bool)0;
          lasttok = (token)272;
          return (lasttok);
        }
        {
          zeroset(ccl);
          notset(ccl);
        }
        { clrbit((unsigned int)eolbyte___0, ccl); }
        { clrbit((unsigned int)'\000', ccl); }
        {
          laststart = (_Bool)0;
          tmp___12 = charclass_index((charclass_word * /* const  */)(ccl));
          lasttok = (token)(275UL + tmp___12);
        }
        return (lasttok);
      case_115 : { goto normal_char; }

        {
          {
            zeroset(ccl);
            c2 = 0;
          }
          {
            {
              ;

              { goto while_break___3; }
              { tmp___13 = __ctype_b_loc(); }
              { setbit((unsigned int)c2, ccl); }
              c2++;
            };
          }
        while_break___3:;
          { notset(ccl); }
          {
            laststart = (_Bool)0;
            tmp___14 = charclass_index((charclass_word * /* const  */)(ccl));
            lasttok = (token)(275UL + tmp___14);
          }
          return (lasttok);
        }
        {
          {
            ;
            lexptr_saved = lexptr;
            lexleft_saved = lexleft;
            { lexptr = "[:space:]]"; }

            {
              lexleft = strlen(lexptr);
              lasttok = parse_bracket_exp();
              lexptr = lexptr_saved;
              lexleft = lexleft_saved;
            }
            goto while_break___4;
          };
        }
      while_break___4:
        laststart = (_Bool)0;
        return (lasttok);
      case_119 : { goto normal_char; }

        {
          zeroset(ccl);
          c2 = 0;
        }
        {
          {
            ;

            { goto while_break___5; }
            { tmp___15 = __ctype_b_loc(); }
            { setbit((unsigned int)c2, ccl); }

            c2++;
          };
        }
      while_break___5:;
        { notset(ccl); }
        {
          laststart = (_Bool)0;
          tmp___16 = charclass_index((charclass_word * /* const  */)(ccl));
          lasttok = (token)(275UL + tmp___16);
        }
        return (lasttok);
      case_91:
        if (backslash) {
          goto normal_char;
        }
        {
          laststart = (_Bool)0;
          lasttok = parse_bracket_exp();
        }
        return (lasttok);
      normal_char:
        laststart = (_Bool)0;
        if (dfa___0->multibyte) {
          lasttok = (token)274;
          return (lasttok);
        }
        if (case_fold) {
          {
            tmp___18 = __ctype_b_loc();
          }
          {
            {
              zeroset(ccl);
              setbit_case_fold_c(c, ccl);
              tmp___17 = charclass_index((charclass_word * /* const  */)(ccl));
              lasttok = (token)(275UL + tmp___17);
            }
            return (lasttok);
          }
        }
        lasttok = (token)c;
        return (lasttok);
      switch_break:
        i++;
      };
    }
  while_break : { abort(); }
    return ((token)-1);
  }
}
static token tok;
static size_t depth;
static void addtok_mb(token t, int mbprop) {
  size_t tmp;

  {
    if (dfa___0->talloc == dfa___0->tindex) {

      dfa___0->tokens =
          (token *)x2nrealloc((void *)dfa___0->tokens, &dfa___0->talloc,
                              sizeof(*(dfa___0->tokens)));
    }

    tmp = dfa___0->tindex;
    (dfa___0->tindex)++;
    *(dfa___0->tokens + tmp) = t;

    (dfa___0->nleaves)++;

    depth++;

    { dfa___0->depth = depth; }
  }
}
static void addtok_wc(wint_t wc);
static void addtok(token t) { addtok_mb(t, 3); }

static void add_utf8_anychar(void);
static charclass const utf8_classes[5] = {
    {(charclass_word)0, (charclass_word)0, (charclass_word)0, (charclass_word)0,
     ((1U << 31) << 1) - 1U, ((1U << 31) << 1) - 1U, (charclass_word)0,
     (charclass_word)0},
    {((1U << 31) << 1) - 1U, ((1U << 31) << 1) - 1U, ((1U << 31) << 1) - 1U,
     ((1U << 31) << 1) - 1U, (charclass_word)0, (charclass_word)0,
     (charclass_word)0, (charclass_word)0},
    {(charclass_word)0, (charclass_word)0, (charclass_word)0, (charclass_word)0,
     (charclass_word)0, (charclass_word)0,
     4294967292U & (((1U << 31) << 1) - 1U), (charclass_word)0},
    {(charclass_word)0, (charclass_word)0, (charclass_word)0, (charclass_word)0,
     (charclass_word)0, (charclass_word)0, (charclass_word)0,
     (charclass_word)65535},
    {(charclass_word)0, (charclass_word)0, (charclass_word)0, (charclass_word)0,
     (charclass_word)0, (charclass_word)0, (charclass_word)0,
     (charclass_word)16711680}};
static void add_utf8_anychar(void) {
  unsigned int n;
  unsigned int i;
  charclass c;
  size_t tmp;

  {
    n = (unsigned int)(sizeof(utf8_classes) / sizeof(utf8_classes[0]));
    {
      i = 0U;
      {
        while (1) {
          ;

          if (!(i < n)) {
            goto while_break;
          }
          { copyset(utf8_classes[i], c); }
          {{

              clrbit((unsigned int)eolbyte___0, c);
        }
        { clrbit((unsigned int)'\000', c); }
      }
      {
        tmp = charclass_index((charclass_word * /* const  */)(c));
        dfa___0->utf8_anychar_classes[i] = (token)(275UL + tmp);
        i++;
      }
    };
  }
while_break:;
}
i = 1U;
{
  {
    ;

    if (!(i < n)) {
      goto while_break___0;
    }
    {
      addtok(dfa___0->utf8_anychar_classes[i]);
      i++;
    }
  };
}
while_break___0:;
{
  {
    ;
    i--;
    { goto while_break___1; }
    {
      addtok(dfa___0->utf8_anychar_classes[0]);
      addtok((token)268);
      addtok((token)269);
    }
  };
}
while_break___1:;
return;
}
}
static void atom(void) {

  if (tok == 272L) {

    add_utf8_anychar();
    tok = lex();

  } else {

    if (tok >= 0L) {
      if (tok < 256L) {

        addtok(tok);
        tok = lex();

      } else {
        goto _L;
      }
    } else {
    _L:
      if (tok >= 275L) {

        addtok(tok);
        tok = lex();

      } else {

        if (tok == 258L) {

          addtok(tok);
          tok = lex();

        } else {
          if (tok == 259L) {

            addtok(tok);
            tok = lex();

          } else {

            {
              tok = lex();
              regexp();
            }

            { tok = lex(); }
          }
        }
      }
    }
  }
}

static void closure(void) {

  { atom(); }
  {
    {
      ;

      if (!(tok == 264L)) {
        if (!(tok == 265L)) {
          if (!(tok == 266L)) {

            goto while_break;
          }
        }
      }

      {

        addtok(tok);
        tok = lex();
      }
    };
  }
while_break:;
}
static void branch(void) {

  { closure(); }
  {
    while (1) {
      ;

      if (tok != 271L) {
        if (tok != 269L) {
          if (!(tok >= 0L)) {
            goto while_break;
          }
        } else {
          goto while_break;
        }
      } else {
        goto while_break;
      }
      {
        closure();
        addtok((token)268);
      }
    };
  }
while_break:;
}
static void regexp(void) {

  { branch(); }
  {
    {
      ;

      if (!(tok == 269L)) {
        goto while_break;
      }
      {

        branch();
        addtok((token)269);
      }
    };
  }
while_break:;
}
void dfaparse(char const *s, size_t len, struct dfa *d) {

  dfa___0 = d;
  lexptr = s;
  lexleft = len;

  {
    tok = lex();

    regexp();
  }

  {
    addtok((token)(0xffffffffffffffffUL - d->nregexps));
    addtok((token)268);
  }
}
static void copy(position_set const *src, position_set *dst) {

  {

    free((void *)dst->elems);
    dst->alloc = (size_t)src->nelem;
    dst->elems =
        (position *)x2nrealloc((void *)0, &dst->alloc, sizeof(*(dst->elems)));
  }
  {
    memcpy((void * /* __restrict  */)((void *)dst->elems),
           (void const * /* __restrict  */)((void const *)src->elems),
           (size_t)(src->nelem * (size_t const)sizeof(*(dst->elems))));
    dst->nelem = (size_t)src->nelem;
  }
}
static void alloc_position_set(position_set *s, size_t size) {

  s->elems = (position *)xnmalloc(size, sizeof(*(s->elems)));
}
static void insert(position p, position_set *s) {

  size_t lo;

  {

    lo = (size_t)0;

    *(s->elems + lo) = p;
    (s->nelem)++;
  }
}
static void merge(position_set const *s1, position_set const *s2,
                  position_set *m) {
  size_t i;
  size_t j;

  size_t tmp___6;
  size_t tmp___7;
  size_t tmp___8;
  size_t tmp___9;

  {
    i = (size_t)0;
    j = (size_t)0;

    m->nelem = (size_t)0;

    {
      {
        ;

        tmp___6 = m->nelem;
        (m->nelem)++;
        tmp___7 = i;

        *(m->elems + tmp___6) = *(s1->elems + tmp___7);
      };
    };
    {
      {
        ;

        if (!(j < (size_t)s2->nelem)) {
          goto while_break___1;
        }
        tmp___8 = m->nelem;
        (m->nelem)++;
        tmp___9 = j;

        *(m->elems + tmp___8) = *(s2->elems + tmp___9);
      };
    }
  while_break___1:;
  }
}
static void delete (position p, position_set *s) { (s->nelem)--; }
static state_num state_index(struct dfa *d, position_set const *s,
                             int context) {

  int constraint;
  state_num i;
  state_num j;

  {

    i = (state_num)0;

    {
      while (1) {
        ;

        if (!(i < d->sindex)) {
          goto while_break___0;
        }

        {

          if (context != (int)(d->states + i)->context) {
            goto __Cont;
          }
        }
        j = (state_num)0;
        {
          {
            ;

            j++;
          };
        };
        if ((size_t const)j == s->nelem) {
          return (i);
        }
      __Cont:
        i++;
      };
    }
  while_break___0 : {
    d->states = (dfa_state *)maybe_realloc((void *)d->states, (size_t)d->sindex,
                                           &d->salloc, sizeof(*(d->states)));

    alloc_position_set(&(d->states + i)->elems, (size_t)s->nelem);
    copy(s, &(d->states + i)->elems);
    (d->states + i)->context = (unsigned char)context;

    (d->states + i)->constraint = (unsigned short)0;

    j = (state_num)0;
  }
    {
      while (1) {
        ;

        if (!((size_t const)j < s->nelem)) {
          goto while_break___2;
        }
        if (*(d->tokens + (s->elems + j)->index) < 0L) {
          constraint = (int)(s->elems + j)->constraint;
          {
            (d->states + i)->constraint =
                (unsigned short)((int)(d->states + i)->constraint | constraint);
          }

        } else {
        }
        j++;
      };
    }
  while_break___2:
    (d->sindex)++;
    return (i);
  }
}
static void epsclosure(position_set *s, struct dfa const *d, char *visited) {
  size_t i;
  size_t j;
  position p;
  position old;

  {

    i = (size_t)0;
    {
      while (1) {
        ;

        if (!(i < s->nelem)) {
          goto while_break;
        }
        if (*(d->tokens + (s->elems + i)->index) >= 256L) {

          if (*(d->tokens + (s->elems + i)->index) < 275L) {

            {
              old = *(s->elems + i);
              p.constraint = old.constraint;
              delete (*(s->elems + i), s);
            }

            if (*(d->tokens + old.index) == 259L) {
              goto case_259;
            }

            p.constraint &= 1092U;
            goto switch_break;
          case_259:
            p.constraint &= 1792U;

          switch_break:
            j = (size_t)0;
            {
              {
                ;

                {
                  p.index = ((d->follows + old.index)->elems + j)->index;
                  insert(p, s);
                }
              };
            }

            i = (size_t)-1;
          }
        }

        i++;
      };
    }
  while_break:;
  }
}

void dfaanalyze(struct dfa *d, int searchflag) {
  position *posalloc;
  position *tmp;
  position *firstpos;
  position *lastpos;
  struct __anonstruct_stkalloc_43 *stkalloc;
  struct __anonstruct_stkalloc_43 *tmp___0;
  struct __anonstruct_stkalloc_43 *stk;
  position_set tmp___1;
  position_set merged;

  size_t i;
  size_t j;
  position *pos;
  char *visited;
  char *tmp___2;

  size_t tmp___5;
  size_t tmp___6;
  unsigned int tmp___7;
  int tmp___8;

  {
    {
      tmp = (position *)xnmalloc(d->nleaves, 2UL * sizeof(*posalloc));
      posalloc = tmp;
      firstpos = posalloc + d->nleaves;
      lastpos = firstpos + d->nleaves;
      tmp___0 = (struct __anonstruct_stkalloc_43 *)xnmalloc(d->depth,
                                                            sizeof(*stkalloc));
      stkalloc = tmp___0;
      stk = stkalloc;
      tmp___2 = (char *)xnmalloc(d->tindex, sizeof(*visited));
      visited = tmp___2;

      alloc_position_set(&merged, d->nleaves);
      d->follows = (position_set *)xcalloc(d->tindex, sizeof(*(d->follows)));
      i = (size_t)0;
    }
    {
      while (1) {
        ;

        if (!(i < d->tindex)) {
          goto while_break;
        }

        if (*(d->tokens + i) == 265L) {
          goto case_265;
        }
        if (*(d->tokens + i) == 266L) {
          goto case_265;
        }
        if (*(d->tokens + i) == 264L) {
          goto case_264;
        }
        if (*(d->tokens + i) == 268L) {
          goto case_268;
        }
        if (*(d->tokens + i) == 269L) {
          goto case_269;
        }
        goto switch_default;

      case_265:
        tmp___1.nelem = (stk + -1)->nfirstpos;

      case_264 : { (stk + -1)->nullable = (_Bool)1; }
        goto switch_break;
      case_268:
        tmp___1.nelem = (stk + -1)->nfirstpos;
        tmp___1.elems = firstpos;
        pos = lastpos + (stk + -1)->nlastpos;
        j = (size_t)0;
        {
          while (1) {
            ;

            if (!(j < (stk + -2)->nlastpos)) {
              goto while_break___1;
            }
            {
              merge((position_set const *)(&tmp___1),
                    (position_set const *)(d->follows + (pos + j)->index),
                    &merged);
              copy((position_set const *)(&merged),
                   d->follows + (pos + j)->index);
              j++;
            }
          };
        }
      while_break___1:;

        { firstpos += (stk + -1)->nfirstpos; }
        if ((stk + -1)->nullable) {
          (stk + -2)->nlastpos += (stk + -1)->nlastpos;
        } else {
          pos = lastpos + (stk + -2)->nlastpos;
          j = (stk + -1)->nlastpos;
          {
            {
              ;

              j--;

              *(pos + j) = *(lastpos + j);
            };
          }

          lastpos += (stk + -2)->nlastpos;
        }

        stk--;
        goto switch_break;
      case_269:
        (stk + -2)->nfirstpos += (stk + -1)->nfirstpos;
        (stk + -2)->nlastpos += (stk + -1)->nlastpos;

        stk--;
        goto switch_break;
      switch_default : {
        stk->nullable = (_Bool)(*(d->tokens + i) == 257L);
        tmp___5 = (size_t)1;
        stk->nlastpos = tmp___5;
        stk->nfirstpos = tmp___5;
        stk++;
        firstpos--;
        lastpos--;
        tmp___6 = i;
        lastpos->index = tmp___6;
        firstpos->index = tmp___6;
        tmp___7 = 1911U;

        firstpos->constraint = tmp___7;
      }

      switch_break:
        i++;
      };
    }
  while_break:
    i = (size_t)0;
    {
      while (1) {
        ;

        if (!(i < d->tindex)) {
          goto while_break___3;
        }
        if (*(d->tokens + i) < 256L) {

          copy((position_set const *)(d->follows + i), &merged);
          epsclosure(&merged, (struct dfa const *)d, visited);
          copy((position_set const *)(&merged), d->follows + i);

        } else {

          if (*(d->tokens + i) >= 275L) {

            copy((position_set const *)(d->follows + i), &merged);
            epsclosure(&merged, (struct dfa const *)d, visited);
            copy((position_set const *)(&merged), d->follows + i);
          }
        }
        i++;
      };
    }
  while_break___3:
    merged.nelem = (size_t)0;
    i = (size_t)0;
    {
      {
        ;

        { insert(*(firstpos + i), &merged); }
      };
    }
    { epsclosure(&merged, (struct dfa const *)d, visited); }
    { tmp___8 = 4; }

    {
      state_index(d, (position_set const *)(&merged), tmp___8);
      free((void *)posalloc);
      free((void *)stkalloc);
      free((void *)merged.elems);
      free((void *)visited);
    }
  }
}
void dfastate(ptrdiff_t s, struct dfa *d, ptrdiff_t *trans___0) {
  leaf_set grps[256];
  charclass labels[256];
  size_t ngrps;
  position pos;
  charclass matches;

  position_set follows;
  position_set tmp;

  state_num state_newline;
  state_num state_letter;

  size_t i;
  size_t j;
  size_t k;

  int c;

  {
    {
      ngrps = (size_t)0;

      zeroset(matches);
      i = (size_t)0;
    }
    {
      while (1) {
        ;

        if (!(i < (d->states + s)->elems.nelem)) {
          goto while_break;
        }
        pos = *((d->states + s)->elems.elems + i);
        if (*(d->tokens + pos.index) >= 0L) {
          if (*(d->tokens + pos.index) < 256L) {

            setbit((unsigned int)*(d->tokens + pos.index), matches);

          } else {
            goto _L___0;
          }
        } else {
        _L___0:
          if (*(d->tokens + pos.index) >= 275L) {

            copyset((charclass_word * /* const  */)(
                        *(d->charclasses + (*(d->tokens + pos.index) - 275L))),
                    matches);

          } else {
          }
        }
        {

          if (!((pos.constraint & 15U) &
                (unsigned int)(d->states + s)->context)) {
            j = (size_t)0;
            {
              while (1) {
                ;

                if (!(j < 8UL)) {
                  goto while_break___2;
                }
                matches[j] &= letters[j] | newline[j];
                j++;
              };
            }
          while_break___2:;
          }
        }

        ;
        {

          copyset((charclass_word * /* const  */)(matches), labels[ngrps]);
          zeroset(matches);
          grps[ngrps].elems =
              (size_t *)xnmalloc(d->nleaves, sizeof(*(grps[ngrps].elems)));

          *(grps[ngrps].elems + 0) = pos.index;
          ngrps++;
        }

        i++;
      };
    }
  while_break : {
    alloc_position_set(&follows, d->nleaves);
    alloc_position_set(&tmp, d->nleaves);
  }
    {
      { copy((position_set const *)(&(d->states + 0)->elems), &follows); }
      { state_newline = state_index(d, (position_set const *)(&follows), 4); }

      { state_letter = state_index(d, (position_set const *)(&follows), 2); }

      i = (size_t)0;
      {
        while (1) {
          ;

          if (!(i < 256UL)) {
            goto while_break___7;
          }

          { *(trans___0 + i) = state_letter; }

          i++;
        };
      }
    while_break___7:
      *(trans___0 + (int)eolbyte___0) = state_newline;
    }

    i = (size_t)0;
    {
      while (1) {
        ;

        if (!(i < ngrps)) {
          goto while_break___9;
        }

        j = (size_t)0;
        {
          {
            ;

            k = (size_t)0;
            {
              {
                ;

                if (!(k < (d->follows + *(grps[i].elems + j))->nelem)) {
                  goto while_break___11;
                }
                {
                  insert(*((d->follows + *(grps[i].elems + j))->elems + k),
                         &follows);
                }
              };
            }
          while_break___11:
            j++;
          };
        };

        {

          merge((position_set const *)(&(d->states + 0)->elems),
                (position_set const *)(&follows), &tmp);
          copy((position_set const *)(&tmp), &follows);
        }

        { state_letter = state_index(d, (position_set const *)(&follows), 2); }

        {
          while (1) {
            ;

            if (!(j < 8UL)) {
              goto while_break___13;
            }
            k = (size_t)0;
            {
              while (1) {
                ;

                if (!(k < 32UL)) {
                  goto while_break___14;
                }
                if ((labels[i][j] >> k) & 1U) {
                  c = (int)(j * 32UL + k);

                  { *(trans___0 + c) = state_letter; }
                }
                k++;
              };
            }
          while_break___14:
            j++;
          };
        }
      while_break___13:
        i++;
      };
    }
  while_break___9:
    i = (size_t)0;
    {
      while (1) {
        ;

        if (!(i < ngrps)) {
          goto while_break___15;
        }
        {
          free((void *)grps[i].elems);
          i++;
        }
      };
    }
  while_break___15 : {
    free((void *)follows.elems);
    free((void *)tmp.elems);
  }
  }
}
static void realloc_trans_if_necessary(struct dfa *d, state_num new_state) {
  state_num oldalloc;
  state_num **realtrans;
  state_num **tmp;
  size_t newalloc;
  size_t newalloc1;

  {
    oldalloc = d->tralloc;
    if (oldalloc <= new_state) {
      if (d->trans) {
        tmp = d->trans - 1;
      } else {
        tmp = (state_num **)((void *)0);
      }
      {
        realtrans = tmp;
        newalloc1 = (size_t)(new_state + 1L);
        realtrans = (state_num **)x2nrealloc((void *)realtrans, &newalloc1,
                                             sizeof(*realtrans));

        d->trans = realtrans + 1;
        newalloc = newalloc1 - 1UL;
        d->tralloc = (state_num)newalloc;
        d->fails = (state_num **)xnrealloc((void *)d->fails, newalloc,
                                           sizeof(*(d->fails)));
        d->success = (int *)xnrealloc((void *)d->success, newalloc,
                                      sizeof(*(d->success)));
      }
      {
        while (1) {
          ;

          if (!((size_t)oldalloc < newalloc)) {
            goto while_break;
          }

          *(d->fails + oldalloc) = (state_num *)((void *)0);
          oldalloc++;
        };
      }
    while_break:;
    }
  }
}
static void build_state(state_num s, struct dfa *d) {
  state_num *trans___0;
  state_num i;
  state_num maxstate;

  {

    *(d->success + s) = 0;
    if ((((int)(d->states + s)->constraint >> 8) & 15) &
        (int)(d->states + s)->context) {
      *(d->success + s) |= 4;
    }

    if (((int)(d->states + s)->constraint & 15) &
        (int)(d->states + s)->context) {
      *(d->success + s) |= 1;
    }
    {
      trans___0 = (state_num *)xmalloc(256UL * sizeof(*trans___0));
      dfastate(s, d, trans___0);
      maxstate = (state_num)-1;
      i = (state_num)0;
    }
    {
      while (1) {
        ;

        if (!(i < 256L)) {
          goto while_break___0;
        }
        if (maxstate < *(trans___0 + i)) {
          maxstate = *(trans___0 + i);
        }
        i++;
      };
    }
  while_break___0 : {
    realloc_trans_if_necessary(d, maxstate);

    *(trans___0 + (int)eolbyte___0) = (state_num)-1;
  }
    { *(d->fails + s) = trans___0; }
  }
}
static void build_state_zero(struct dfa *d) {
  int initial_tab_size;

  {

    initial_tab_size = 1;

    realloc_trans_if_necessary(d, (state_num)initial_tab_size);
  }
}

char *dfaexec(struct dfa *d, char const *begin, char *end, int allow_nl,
              size_t *count, int *backref) {
  state_num s;
  state_num s1;
  unsigned char const *p;
  unsigned char const *mbp;

  unsigned char eol;

  size_t nlcount;

  unsigned char const *tmp___4;

  {
    eol = eolbyte___0;
    nlcount = (size_t)0;
    { build_state_zero(d); }
    s1 = (state_num)0;
    s = s1;
    mbp = (unsigned char const *)begin;
    p = mbp;

    *end = (char)eol;

    {
      while (1) {
        ;

        if ((unsigned long)((char *)p) > (unsigned long)end) {
          p = (unsigned char const *)((void *)0);
          goto done;
        }
        if (s >= 0L) {
          if (*(d->fails + s)) {
            if (*(d->success + s) & sbit[*p]) {

              goto done;
            }

            {
              tmp___4 = p;
              p++;
              s = *(*(d->fails + s) + (int const) * tmp___4);
            }
            goto __Cont;
          }
        }
        if ((int const) * (p + -1) == (int const)eol) {
          if ((unsigned long)((char *)p) != (unsigned long)begin) {
            nlcount++;
          }
        }
        if (s >= 0L) {
          {

            build_state(s, d);
          }

          goto __Cont;
        }

        s = (state_num)0;
      __Cont:;
      };
    }

  done : { *count += nlcount; }

    return ((char *)p);
  }
}
struct dfa *dfasuperset(struct dfa const *d) __attribute__((__pure__));

_Bool dfaisfast(struct dfa const *d) __attribute__((__pure__));

void dfainit(struct dfa *d) { memset((void *)d, 0, sizeof(*d)); }

void dfacomp(char const *s, size_t len, struct dfa *d, int searchflag) {

  dfainit(d);

  dfaparse(s, len, d);

  dfaanalyze(d, searchflag);
}

struct dfa *dfaalloc(void) {
  struct dfa *tmp;

  {
    { tmp = (struct dfa *)xmalloc(sizeof(struct dfa)); }
    return (tmp);
  }
}

extern __attribute__((__nothrow__)) size_t
mbrlen(char const *__restrict __s, size_t __n, mbstate_t *__restrict __ps);
void build_mbclen_cache(void);

void kwsinit(kwset_t *kwset___1) {

  *kwset___1 = kwsalloc((char const *)((void *)0));
}

extern int fflush_unlocked(FILE *__stream);
extern int fputc_unlocked(int __c, FILE *__stream);
extern size_t fread_unlocked(void *__restrict __ptr, size_t __size, size_t __n,
                             FILE *__restrict __stream);
extern size_t fwrite_unlocked(void const *__restrict __ptr, size_t __size,
                              size_t __n, FILE *__restrict __stream);
extern __attribute__((__nothrow__)) __off_t lseek(int __fd, __off_t __offset,
                                                  int __whence);
extern __attribute__((__nothrow__)) int isatty(int __fd);
extern char *optarg;
extern int optind;
extern __attribute__((__nothrow__)) int getpagesize(void)
    __attribute__((__const__));
extern __attribute__((__nothrow__)) int(__attribute__((__nonnull__(1)))
                                        atexit)(void (*__func)(void));
extern __attribute__((__nothrow__, __noreturn__)) void exit(int __status);
extern __attribute__((__nothrow__)) int(__attribute__((__nonnull__(1, 2)))
                                        strcasecmp)(char const *__s1,
                                                    char const *__s2)
    __attribute__((__pure__));
extern __attribute__((__nothrow__)) char *textdomain(char const *__domainname);
extern __attribute__((__nothrow__)) char *
bindtextdomain(char const *__domainname, char const *__dirname);
extern int getopt_long(int ___argc, char *const *___argv,
                       char const *__shortopts, struct option const *__longopts,
                       int *__longind);

static int show_help;

static int suppress_errors;
static int color_option;
static int only_matching;

static char const *selected_match_color = "01;31";

static char const *line_num_color = "32";

static char const *selected_line_color = "";

static char const short_options[58] = {
    (char const)'0', (char const)'1',   (char const)'2', (char const)'3',
    (char const)'4', (char const)'5',   (char const)'6', (char const)'7',
    (char const)'8', (char const)'9',   (char const)'A', (char const)':',
    (char const)'B', (char const)':',   (char const)'C', (char const)':',
    (char const)'D', (char const)':',   (char const)'E', (char const)'F',
    (char const)'G', (char const)'H',   (char const)'I', (char const)'P',
    (char const)'T', (char const)'U',   (char const)'V', (char const)'X',
    (char const)':', (char const)'a',   (char const)'b', (char const)'c',
    (char const)'d', (char const)':',   (char const)'e', (char const)':',
    (char const)'f', (char const)':',   (char const)'h', (char const)'i',
    (char const)'L', (char const)'l',   (char const)'m', (char const)':',
    (char const)'n', (char const)'o',   (char const)'q', (char const)'R',
    (char const)'r', (char const)'s',   (char const)'u', (char const)'v',
    (char const)'w', (char const)'x',   (char const)'y', (char const)'Z',
    (char const)'z', (char const)'\000'};
static struct option const long_options[50] = {
    {"basic-regexp", 0, (int *)((void *)0), 'G'},
    {"extended-regexp", 0, (int *)((void *)0), 'E'},
    {"fixed-regexp", 0, (int *)((void *)0), 'F'},
    {"fixed-strings", 0, (int *)((void *)0), 'F'},
    {"perl-regexp", 0, (int *)((void *)0), 'P'},
    {"after-context", 1, (int *)((void *)0), 'A'},
    {"before-context", 1, (int *)((void *)0), 'B'},
    {"binary-files", 1, (int *)((void *)0), 128},
    {"byte-offset", 0, (int *)((void *)0), 'b'},
    {"context", 1, (int *)((void *)0), 'C'},
    {"color", 2, (int *)((void *)0), 129},
    {"colour", 2, (int *)((void *)0), 129},
    {"count", 0, (int *)((void *)0), 'c'},
    {"devices", 1, (int *)((void *)0), 'D'},
    {"directories", 1, (int *)((void *)0), 'd'},
    {"exclude", 1, (int *)((void *)0), 131},
    {"exclude-from", 1, (int *)((void *)0), 132},
    {"exclude-dir", 1, (int *)((void *)0), 135},
    {"file", 1, (int *)((void *)0), 'f'},
    {"files-with-matches", 0, (int *)((void *)0), 'l'},
    {"files-without-match", 0, (int *)((void *)0), 'L'},
    {"group-separator", 1, (int *)((void *)0), 136},
    {"help", 0, &show_help, 1},
    {"include", 1, (int *)((void *)0), 130},
    {"ignore-case", 0, (int *)((void *)0), 'i'},
    {"initial-tab", 0, (int *)((void *)0), 'T'},
    {"label", 1, (int *)((void *)0), 134},
    {"line-buffered", 0, (int *)((void *)0), 133},
    {"line-number", 0, (int *)((void *)0), 'n'},
    {"line-regexp", 0, (int *)((void *)0), 'x'},
    {"max-count", 1, (int *)((void *)0), 'm'},
    {"no-filename", 0, (int *)((void *)0), 'h'},
    {"no-group-separator", 0, (int *)((void *)0), 136},
    {"no-messages", 0, (int *)((void *)0), 's'},
    {"null", 0, (int *)((void *)0), 'Z'},
    {"null-data", 0, (int *)((void *)0), 'z'},
    {"only-matching", 0, (int *)((void *)0), 'o'},
    {"quiet", 0, (int *)((void *)0), 'q'},
    {"recursive", 0, (int *)((void *)0), 'r'},
    {"dereference-recursive", 0, (int *)((void *)0), 'R'},
    {"regexp", 1, (int *)((void *)0), 'e'},
    {"invert-match", 0, (int *)((void *)0), 'v'},
    {"silent", 0, (int *)((void *)0), 'q'},
    {"text", 0, (int *)((void *)0), 'a'},
    {"binary", 0, (int *)((void *)0), 'U'},
    {"unix-byte-offsets", 0, (int *)((void *)0), 'u'},
    {"version", 0, (int *)((void *)0), 'V'},
    {"with-filename", 0, (int *)((void *)0), 'H'},
    {"word-regexp", 0, (int *)((void *)0), 'w'},
    {(char const *)0, 0, (int *)0, 0}};

static char const *filename;
static size_t filename_prefix_len;

static char const *const directories_args[4] = {
    (char const * /* const  */) "read", (char const * /* const  */) "recurse",
    (char const * /* const  */) "skip",
    (char const * /* const  */)((char const *)((void *)0))};
static enum directories_type const directories_types[3] = {
    (enum directories_type const)2, (enum directories_type const)3,
    (enum directories_type const)4};
static enum directories_type directories = (enum directories_type)2;
static int fts_options = 793;

static int grepfile(int dirdesc, char const *name, int follow,
                    int command_line);
static int grepdesc(int desc, int command_line);
static void dos_binary(void);
static void dos_unix_byte_offsets(void);
static int undossify_input(char *buf, size_t buflen);

static void (*compile)(char const *, size_t);
static size_t (*execute)(char const *, size_t, size_t *, char const *);
static void suppressible_error(char const *mesg, int errnum) {

  error(0, errnum, "%s", mesg);
}
static void clean_up_stdout(void) { close_stdout(); }

static void context_length_arg(char const *str, intmax_t *out___0) {

  char *tmp___0;

  {

    tmp___0 = gettext("invalid context length argument");
    error(2, 0, "%s: %s", str, tmp___0);
  }
}

static char *buffer;
static size_t bufalloc;
static int bufdesc;
static char *bufbeg;
static char *buflim;
static size_t pagesize;

static int reset(int fd, struct stat const *st) {
  size_t tmp;

  {
    if (!pagesize) {
      {
        pagesize = (size_t)getpagesize();
      }

      { tmp = (size_t)32768; }

      {
        bufalloc = (tmp + pagesize) + 1UL;
        buffer = (char *)xmalloc(bufalloc);
      }
    }
    { buflim = buffer + 1; }

    bufbeg = buflim;
    *(bufbeg + -1) = (char)eolbyte;
    bufdesc = fd;

    return (1);
  }
}
static int fillbuf(size_t save, struct stat const *st) {
  ssize_t fillsize;
  int cc;
  char *readbuf;
  size_t readsize;

  {
    cc = 1;

    { readbuf = buflim; }

    {
      readsize = (size_t)((buffer + bufalloc) - readbuf);

      fillsize = (ssize_t)safe_read(bufdesc, (void *)readbuf, readsize);
    }

    { buflim = readbuf + fillsize; }
    return (cc);
  }
}

static int filename_mask;
static int out_quiet;
static _Bool out_invert;
static int out_file;
static int out_line;

static intmax_t out_after;
static int count_matches;
static int list_files;
static int no_filenames;

static char const *lastnl;

static uintmax_t totalnl;
static intmax_t outleft;

static int done_on_match;
static int exit_on_match;

static uintmax_t add_count(uintmax_t a, uintmax_t b) {
  uintmax_t sum;

  {
    sum = a + b;

    return (sum);
  }
}
static void nlscan(char const *lim) {
  size_t newlines;
  char const *beg;

  {
    newlines = (size_t)0;
    beg = lastnl;
    {
      while (1) {
        ;

        {
          beg = (char const *)memchr((void const *)beg, (int)eolbyte,
                                     (size_t)(lim - beg));
        }
        if (!beg) {
          goto while_break;
        }
        newlines++;
        beg++;
      };
    }
  while_break : { totalnl = add_count(totalnl, newlines); }
  }
}
static void print_filename(void) {

  fputs_unlocked((char const * /* __restrict  */)filename,
                 (FILE * /* __restrict  */) stdout);
}
static void print_sep(char sep) { fputc_unlocked((int)sep, stdout); }
static void print_offset(uintmax_t pos, int min_width, char const *color) {
  char buf[sizeof(pos) * 8UL];
  char *p;

  {
    p = buf + sizeof(buf);
    {
      while (1) {
        ;
        p--;
        *p = (char)(48UL + pos % 10UL);

        pos /= 10UL;
        if (!(pos != 0UL)) {
          goto while_break;
        }
      };
    }
  while_break:;

    {

      fwrite_unlocked((void const * /* __restrict  */)((void const *)p),
                      (size_t)1, (size_t)((buf + sizeof(buf)) - p),
                      (FILE * /* __restrict  */) stdout);
    }
  }
}
static void print_line_head(char const *beg, char const *lim, int sep) {
  int pending_sep;

  {
    pending_sep = 0;
    if (out_file) {
      {
        print_filename();
      }
      { pending_sep = 1; }
    }
    if (out_line) {
      {

        nlscan(beg);
        totalnl = add_count(totalnl, (uintmax_t)1);
        lastnl = lim;
      }

      {
        print_offset(totalnl, 4, line_num_color);
        pending_sep = 1;
      }
    }

    if (pending_sep) {

      print_sep((char)sep);
    }
  }
}
static char const *print_line_middle(char const *beg, char const *lim,
                                     char const *line_color,
                                     char const *match_color) {
  size_t match_size;
  size_t match_offset;
  char const *cur;

  char const *b;

  {
    cur = beg;

    {
      {
        ;

        {

          match_offset = (*execute)(beg, (size_t)(lim - beg), &match_size,
                                    beg + (cur - beg));
        }

        b = beg + match_offset;

        {

          {

            fwrite_unlocked((void const * /* __restrict  */)((void const *)b),
                            sizeof(char), match_size,
                            (FILE * /* __restrict  */) stdout);
          }
          {

            fputs_unlocked((char const * /* __restrict  */) "\n",
                           (FILE * /* __restrict  */) stdout);
          }
        }
      };
    };

    return (cur);
  }
}

static void prline(char const *beg, char const *lim, int sep) {

  char const *line_color;
  char const *match_color;

  {
    { print_line_head(beg, lim, sep); }

    {

      { line_color = selected_line_color; }

      { match_color = selected_match_color; }
    }

    if (only_matching) {

      goto _L___0;

    } else {

      if (color_option) {

      _L___0 : { beg = print_line_middle(beg, lim, line_color, match_color); }
      }
    }
    if (!only_matching) {

      fwrite_unlocked((void const * /* __restrict  */)((void const *)beg),
                      (size_t)1, (size_t)(lim - beg),
                      (FILE * /* __restrict  */) stdout);
    }
  }
}

static void prtext(char const *beg, char const *lim) {
  char eol;
  char const *p;

  intmax_t n;
  char const *nl___0;
  char const *tmp___1;

  {
    eol = (char)eolbyte;

    p = beg;

    {
      n = (intmax_t)0;
      {
        while (1) {
          ;

          if ((unsigned long)p < (unsigned long)lim) {

          } else {
            goto while_break___2;
          }
          {
            tmp___1 = (char const *)memchr((void const *)p, (int)eol,
                                           (size_t)(lim - p));
            nl___0 = tmp___1;
            nl___0++;
          }
          if (!out_quiet) {

            prline(p, nl___0, ':');
          }
          p = nl___0;
          n++;
        };
      }
    while_break___2:;
    }

    outleft -= n;
  }
}
static size_t do_execute(char const *buf, size_t size, size_t *match_size,
                         char const *start_ptr) {

  size_t tmp;

  {

    { tmp = (*execute)(buf, size, match_size, start_ptr); }
    return (tmp);
  }
}
static intmax_t grepbuf(char const *beg, char const *lim) {
  intmax_t outleft0;
  char const *p;
  char const *endp;
  size_t match_size;
  size_t match_offset;
  size_t tmp;
  char const *b;
  char const *prbeg;
  char const *tmp___0;
  char const *prend;
  char const *tmp___1;

  {
    outleft0 = outleft;
    p = beg;
    {
      while (1) {
        ;

        if (!((unsigned long)p < (unsigned long)lim)) {
          goto while_break;
        }
        {
          tmp = do_execute(p, (size_t)(lim - p), &match_size,
                           (char const *)((void *)0));
          match_offset = tmp;
        }
        if (match_offset == 0xffffffffffffffffUL) {

          match_offset = (size_t)(lim - p);
        }
        b = p + match_offset;
        endp = b + match_size;
        if (!out_invert) {
          if ((unsigned long)b == (unsigned long)lim) {
            goto while_break;
          }
        }

        {

          if (out_invert) {
            tmp___0 = p;
          } else {
            tmp___0 = b;
          }
          prbeg = tmp___0;
          if (out_invert) {
            tmp___1 = b;
          } else {
            tmp___1 = endp;
          }
          {
            prend = tmp___1;
            prtext(prbeg, prend);
          }
        }
        p = endp;
      };
    }
  while_break:;
    return (outleft0 - outleft);
  }
}
static intmax_t grep(int fd, struct stat const *st) {
  intmax_t nlines;

  size_t save;

  char *beg;
  char *lim;
  char eol;
  int tmp;

  int tmp___1;

  intmax_t tmp___4;

  {
    {
      eol = (char)eolbyte;
      tmp = reset(fd, st);
    }

    {

      nlines = (intmax_t)0;

      save = (size_t)0;
      tmp___1 = fillbuf(save, st);
    }

    {
      {
        ;
        lastnl = (char const *)bufbeg;

        beg = bufbeg + save;

        {

          lim = (char *)memrchr((void const *)(beg - 1), (int)eol,
                                (size_t)((buflim - beg) + 1L));
          lim++;
        }

        {

          tmp___4 = grepbuf((char const *)beg, (char const *)lim);
          nlines += tmp___4;
        }
      };
    };

    return (nlines);
  }
}
static int grepdirent(FTS *fts, FTSENT *ent, int command_line) {
  int follow;
  int dirdesc;

  int tmp___1;

  int tmp___8;

  {

    filename = (char const *)(ent->fts_path + filename_prefix_len);
    { tmp___1 = 1; }

    follow = tmp___1;

    if ((int)ent->fts_info == 11) {
      goto case_3;
    }

    {
      out_file |= 2 * !no_filenames;
      return (1);
    }

  case_3 :

  {}

    { dirdesc = fts->fts_cwd_fd; }

    {
      tmp___8 = grepfile(dirdesc, (char const *)ent->fts_accpath, follow,
                         command_line);
    }
  }
}
static int grepfile(int dirdesc, char const *name, int follow,
                    int command_line) {
  int desc;
  int tmp;
  int tmp___0;
  int *tmp___1;

  int tmp___4;

  {
    { tmp = 0; }

    {
      tmp___0 = openat_safer(dirdesc, name, tmp);
      desc = tmp___0;
    }
    if (desc < 0) {

      tmp___1 = __errno_location();
      suppressible_error(filename, *tmp___1);
    }
    { tmp___4 = grepdesc(desc, command_line); }
    return (tmp___4);
  }
}
static int grepdesc(int desc, int command_line) {
  intmax_t count;
  int status;
  struct stat st;

  int tmp___0;

  FTS *fts;
  FTSENT *ent;
  int opts;
  int tmp___2;
  char *fts_arg[2];

  int tmp___5;

  int tmp___9;

  {
    { tmp___0 = fstat(desc, &st); }

    {

      if ((st.st_mode & 61440U) == 16384U) {
        {
          tmp___2 = 0;
        }

        { opts = fts_options & ~tmp___2; }

        {
          fts_arg[0] = (char *)filename;

          fts =
              fts_open((char *const *)(fts_arg), opts,
                       (int (*)(FTSENT const **, FTSENT const **))((void *)0));
        }

        {
          while (1) {
            ;
            { ent = fts_read(fts); }
            if (!ent) {
              goto while_break;
            }
            { tmp___5 = grepdirent(fts, ent, command_line); }
          };
        }
      while_break : {}

        { tmp___9 = fts_close(fts); }

        return (status);
      }
    }

    { count = grep(desc, (struct stat const *)(&st)); }

    {
      if (count_matches) {
        {{print_filename();
      }
      { print_sep((char)':'); }
    }
    { printf((char const * /* __restrict  */) "%ld\n", count); }
  }
  status = !count;
  if (list_files == 1 - 2 * status) {

    print_filename();
    fputc_unlocked(10 & filename_mask, stdout);
  }
}
}
}
static int grep_command_line_arg(char const *arg) {

  int tmp___1;

  {

    {
      filename = arg;
      tmp___1 = grepfile(-100, arg, 1, 1);
    }
    return (tmp___1);
  }
}
__attribute__((__noreturn__)) void usage(int status);
void usage(int status) {
  char *tmp;

  {
    {

      tmp = gettext("Usage: %s [OPTION]... PATTERN [FILE]...\n");
      fprintf((FILE * /* __restrict  */) stderr,
              (char const * /* __restrict  */)((char const *)tmp),
              program_name);
    }

    { exit(status); }
  }
}
static void Gcompile(char const *pattern, size_t size) {

  GEAcompile(
      pattern, size,
      (((((1UL << 1) | ((1UL << 1) << 1)) |
         ((((((((1UL << 1) << 1) << 1) << 1) << 1) << 1) << 1) << 1)) |
        (((((((((1UL << 1) << 1) << 1) << 1) << 1) << 1) << 1) << 1) << 1)) |
       (((((((((((1UL << 1) << 1) << 1) << 1) << 1) << 1) << 1) << 1) << 1)
         << 1)
        << 1)) |
          ((((((((((((((((1UL << 1) << 1) << 1) << 1) << 1) << 1) << 1) << 1)
                  << 1)
                 << 1)
                << 1)
               << 1)
              << 1)
             << 1)
            << 1)
           << 1));
}
static void Ecompile(char const *pattern, size_t size) {

  GEAcompile(
      pattern, size,
      (((((((((((1UL << 1) << 1) | (((1UL << 1) << 1) << 1)) |
              ((((1UL << 1) << 1) << 1) << 1)) |
             ((((((((1UL << 1) << 1) << 1) << 1) << 1) << 1) << 1) << 1)) |
            (((((((((((1UL << 1) << 1) << 1) << 1) << 1) << 1) << 1) << 1) << 1)
              << 1)
             << 1)) |
           (((((((((((((1UL << 1) << 1) << 1) << 1) << 1) << 1) << 1) << 1)
                << 1)
               << 1)
              << 1)
             << 1)
            << 1)) |
          (((((((((((((((1UL << 1) << 1) << 1) << 1) << 1) << 1) << 1) << 1)
                 << 1)
                << 1)
               << 1)
              << 1)
             << 1)
            << 1)
           << 1)) |
         (((((((((1UL << 1) << 1) << 1) << 1) << 1) << 1) << 1) << 1) << 1)) |
        ((((((((((((1UL << 1) << 1) << 1) << 1) << 1) << 1) << 1) << 1) << 1)
           << 1)
          << 1)
         << 1)) |
       (((((((((((((((((((((1UL << 1) << 1) << 1) << 1) << 1) << 1) << 1) << 1)
                    << 1)
                   << 1)
                  << 1)
                 << 1)
                << 1)
               << 1)
              << 1)
             << 1)
            << 1)
           << 1)
          << 1)
         << 1)
        << 1)) |
          ((((((((((((((((1UL << 1) << 1) << 1) << 1) << 1) << 1) << 1) << 1)
                  << 1)
                 << 1)
                << 1)
               << 1)
              << 1)
             << 1)
            << 1)
           << 1));
}
static void Acompile(char const *pattern, size_t size) {}
static void GAcompile(char const *pattern, size_t size) {}
static void PAcompile(char const *pattern, size_t size) {}
static struct matcher const matchers[8] = {
    {{(char const)'g', (char const)'r', (char const)'e', (char const)'p',
      (char const)'\000'},
     &Gcompile,
     &EGexecute},
    {{(char const)'e', (char const)'g', (char const)'r', (char const)'e',
      (char const)'p', (char const)'\000'},
     &Ecompile,
     &EGexecute},
    {{(char const)'f', (char const)'g', (char const)'r', (char const)'e',
      (char const)'p', (char const)'\000'},
     &Fcompile,
     &Fexecute},
    {{(char const)'a', (char const)'w', (char const)'k', (char const)'\000'},
     &Acompile,
     &EGexecute},
    {{(char const)'g', (char const)'a', (char const)'w', (char const)'k',
      (char const)'\000'},
     &GAcompile,
     &EGexecute},
    {{(char const)'p', (char const)'o', (char const)'s', (char const)'i',
      (char const)'x', (char const)'a', (char const)'w', (char const)'k',
      (char const)'\000'},
     &PAcompile,
     &EGexecute},
    {{(char const)'p', (char const)'e', (char const)'r', (char const)'l',
      (char const)'\000'},
     &Pcompile,
     &Pexecute},
    {{(char const)'\000'},
     (void (*)(char const *, size_t))((void *)0),
     (size_t(*)(char const *, size_t, size_t *, char const *))((void *)0)}};
static void setmatcher(char const *m) {
  struct matcher const *p;

  int tmp___1;

  {

    p = matchers;
    {
      while (1) {
        ;

        { tmp___1 = strcmp(m, (char const *)(p->name)); }
        if (tmp___1 == 0) {

          compile = (void (*)(char const *, size_t))p->compile;
          execute = (size_t(*)(char const *, size_t, size_t *,
                               char const *))p->execute;
          return;
        }
        p++;
      };
    }
  }
}

static int get_nondigit_option(int argc, char *const *argv,
                               intmax_t *default_context);

static int get_nondigit_option(int argc, char *const *argv,
                               intmax_t *default_context) {

  int opt;

  {

    {
      {
        ;
        {
          opt = getopt_long(argc, (char *const *)((char **)argv), short_options,
                            long_options, (int *)((void *)0));
        }
      };
    };

    return (opt);
  }
}

int main(int argc, char **argv) {
  char *keys;
  size_t keycc;

  int with_filenames;

  int opt;

  intmax_t default_context;

  char *tmp___0;

  ptrdiff_t tmp___3;

  char *tmp___13;

  int tmp___37;

  int tmp___42;

  {
    {

      eolbyte = (unsigned char)'\n';
      filename_mask = ~0;

      atexit(&clean_up_stdout);

      compile = (void (*)(char const *, size_t))matchers[0].compile;
      execute =
          (size_t(*)(char const *, size_t, size_t *, char const *))matchers[0]
              .execute;
    }
    {
      while (1) {
        ;
        {

          opt =
              get_nondigit_option(argc, (char *const *)argv, &default_context);
        }
        if (!(opt != -1)) {
          goto while_break;
        }

        if (opt == 68) {
          goto case_68;
        }
        if (opt == 69) {
          goto case_69;
        }
        if (opt == 70) {
          goto case_70;
        }

        if (opt == 72) {
          goto case_72;
        }

        if (opt == 99) {
          goto case_99;
        }
        if (opt == 100) {
          goto case_100;
        }

        if (opt == 104) {
          goto case_104;
        }
        if (opt == 105) {
          goto case_105;
        }

        if (opt == 76) {
          goto case_76;
        }
        if (opt == 108) {
          goto case_108;
        }
        if (opt == 109) {
          goto case_109;
        }
        if (opt == 110) {
          goto case_110;
        }
        if (opt == 111) {
          goto case_111;
        }
        if (opt == 113) {
          goto case_113;
        }

        if (opt == 114) {
          goto case_114;
        }
        if (opt == 115) {
          goto case_115;
        }
        if (opt == 118) {
          goto case_118;
        }
        if (opt == 119) {
          goto case_119;
        }
        if (opt == 120) {
          goto case_120;
        }

        { context_length_arg((char const *)optarg, &out_after); }

      case_68 : {}

        {

          tmp___0 = gettext("unknown devices method");
          error(2, 0, (char const *)tmp___0);
        }

      case_69 : { setmatcher("egrep"); }
        goto switch_break;
      case_70 : { setmatcher("fgrep"); }

      case_72:
        with_filenames = 1;

        goto switch_break;
      case_99:
        count_matches = 1;
        goto switch_break;
      case_100 : {
        tmp___3 = __xargmatch_internal(
            "--directories", (char const *)optarg, directories_args,
            (char const *)(directories_types), sizeof(directories_types[0]),
            argmatch_die);
      }

      case_104:
        with_filenames = 0;
        no_filenames = 1;

      case_105:
        match_icase = 1;
        goto switch_break;
      case_76:
        list_files = -1;
        goto switch_break;
      case_108:
        list_files = 1;
        goto switch_break;
      case_109 : {}

        {
          tmp___13 = gettext("invalid max count");
          error(2, 0, (char const *)tmp___13);
        }

      case_110:
        out_line = 1;
        goto switch_break;
      case_111:
        only_matching = 1;
        goto switch_break;
      case_113:
        exit_on_match = 1;

      case_114:
        directories = (enum directories_type)3;

      case_115:
        suppress_errors = 1;
        goto switch_break;
      case_118:
        out_invert = (_Bool)1;

      case_119:
        match_words = 1;
        goto switch_break;
      case_120:
        match_lines = 1;

      switch_break:;
      };
    }
  while_break:;

    if (exit_on_match | list_files) {

      done_on_match = 1;
    }
    out_quiet = count_matches | done_on_match;

    {
      if (optind < argc) {

        keycc = strlen((char const *)*(argv + optind));
        tmp___37 = optind;
        optind++;
        keys = (char *)xmemdup((void const *)*(argv + tmp___37), keycc + 1UL);

      } else {

        usage(2);
      }
    }

    {
      (*compile)((char const *)keys, keycc);
      free((void *)keys);
    }

    if (optind < argc) {

      {
        {
          ;
          { tmp___42 = grep_command_line_arg((char const *)*(argv + optind)); }
        };
      };
    } else {
    }
  }
}
