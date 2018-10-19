/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   libft.h                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: tle-coza <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2017/11/24 18:28:36 by tle-coza     #+#   ##    ##    #+#       */
/*   Updated: 2018/10/03 15:16:33 by tle-coza    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef _LIBFT_H
# define _LIBFT_H

# include <string.h>
# include <wchar.h>
# include <stdlib.h>
# include "./ft_printf/ft_printf.h"

# define ALPHABET_SIZE	26

# define UN_QUOTED		0
# define S_QUOTE		1
# define D_QUOTE		2
# define BACK_SLASH		3
# define SPCH_BACKSLASH	"$`\"\\\n"

# define FILE_TRUNC			0
# define FILE_APPEND		1

typedef struct		s_list
{
	void			*content;
	size_t			content_size;
	struct s_list	*prev;
	struct s_list	*next;
}					t_list;

typedef struct		s_headlst
{
	void			*first;
	void			*last;
	int				nb_node;
}					t_headlst;

typedef struct		s_hash_table
{
	int				size;
	t_list			**table;
}					t_hash_table;

typedef struct		s_stack
{
	void			*content;
	struct s_stack	*next;
}					t_stack;

typedef struct		s_trie
{
	struct s_trie	*character[ALPHABET_SIZE];
	short			is_leaf;
}					t_trie;

void				*ft_memset(void *b, int c, size_t len);
void				ft_bzero(void *s, size_t n);
void				*ft_memcpy(void *dst, void const *src, size_t n);
void				*ft_memccpy(void *dst, void const *src, int c, size_t n);
void				*ft_memmove(void *dst, void const *src, size_t len);
void				*ft_memchr(void const *s, int c, size_t n);
int					ft_memcmp(void const *s1, void const *s2, size_t n);
int					ft_atoi(char *s);
char				*ft_itoa(int n);
char				*ft_itoa_base(int n, int base);
char				*ft_ltoa(long n);
char				*ft_ltoa_base(long long n, int base);
int					ft_isalpha(int c);
int					ft_isdigit(int c);
int					ft_isalnum(int c);
int					ft_isascii(int c);
int					ft_isprint(int c);
int					ft_is_posixname(char *str);
int					ft_is_posixname_char(char c);
int					ft_toupper(int c);
int					ft_tolower(int c);
void				*ft_memalloc(size_t size);
void				*ft_memrealloc(void *s1, void *s2, size_t size);
void				ft_memdel(void **ap);
char				**ft_strtab_alloc(size_t size);
int					ft_match(char *s1, char *s2);
size_t				ft_expand_str_part(char **str, char *ptr, size_t size,
		char *replace);

/*
** String functions
*/
size_t				ft_strlen(char const *s1);
size_t				ft_wcslen(const wchar_t *ws);
size_t				ft_wsbytelen(const wchar_t *ws);
size_t				ft_wcbytelen(wchar_t wchar);
char				*ft_strdup(char const *s1);
char				*ft_strndup(const char *s, size_t n);
int					ft_strcmp(char const *s1, char const *s2);
int					ft_strcmp_void(void *p1, void *p2);
int					ft_strncmp(char const *s1, char const *s2, size_t n);
size_t				ft_str_nbrequ(char *ref, char *cmp);
char				*ft_strcpy(char *dst, char const *src);
char				*ft_strncpy(char *dst, char const *src, size_t len);
char				*ft_strcat(char *s1, char const *s2);
char				*ft_strncat(char *s1, char const *s2, size_t n);
size_t				ft_strlcat(char *dst, char const *src, size_t dstsize);
size_t				ft_locate_char(const char *str, char c);
char				*ft_strchr(char const *s, int c);
char				*ft_strrchr(char const *s, int c);
char				*ft_strstr(char const *haystack, char const *needle);
char				*ft_strnstr(char const *haystack,
		char const			*needle, size_t len);
char				*ft_strnew(size_t size);
char				*ft_strinit(size_t size, char c);
void				ft_strdel(char **as);
void				ft_strclr(char *s);
void				ft_striter(char *s, void (*f)(char *));
void				ft_striteri(char *s, void (*f)(unsigned int, char *));
char				*ft_strmap(char const *s, char (*f)(char));
char				*ft_strmapi(char const *s, char (*f)(unsigned int, char));
int					ft_strequ(char const *s1, char const *s2);
int					ft_strnequ(char const *s1, char const *s2, size_t n);
char				*ft_strtrim(char const *s);
void				ft_strtrim_tab(char ***s);
char				*ft_strsub(char const *s, unsigned int start, size_t len);
char				*ft_strjoin(char const *s1, char const *s2);
char				*ft_triplejoin(char *s1, char *s2, char *s3);
char				*ft_triplejoin_free(char *s1, char *s2, char *s3);
char				*ft_str_joinordup(char *s1, char *s2);
char				**ft_strsplit(char const *s, char c);
t_list				*ft_strsplittolst(char const *s, int (*ft)(int c));
char				**ft_splitwhitespace(char const *s);
char				*ft_realloc(char *s1, char *s2);
char				*ft_super_realloc(char *s1, char *s2);
char				*ft_append_char(char *s1, char c);
void				ft_strcapitalize(char *s);
char				*ft_strexpand(char **str, size_t size);
void				*ft_myrealloc(void *ptr, size_t prev_size, size_t new_size);
size_t				ft_strcspn(const char *s1, const char *s2);

void				**ft_matricealloc(size_t d1, size_t d2);
void				ft_matricedel(char ***p_to_matrice);
int					ft_putchar(char c);
int					ft_putnchar(char c, int n);
void				ft_putstr(char const *s);
void				ft_putendl(char const *s);
void				ft_putstr_tab(char **tab, char separator);
void				ft_putchar_fd(char c, int fd);
void				ft_putstr_fd(char const *s, int fd);
void				ft_putendl_fd(char const *s, int fd);
void				ft_putstr_reveal_blanks(char const *s);
int					ft_putchar_term(int c);
void				ft_putnbr(int n);
void				ft_putllnbr(intmax_t n);
void				ft_putnbr_fd(int n, int fd);
void				print_bits(unsigned char octet);

/*
** List functions
*/

t_list				*ft_lstnew(void const *content, size_t content_size);
void				ft_lstdelone(t_list **alst, void (*del)(void *, size_t));
void				ft_lstdel(t_list **alst, void (*del)(void *, size_t));
void				ft_lstfree(t_list **alst);
void				ft_lstadd(t_list **alst, t_list *new);
void				ft_lstiter(t_list *lst, void (*f)(t_list *elem));
t_list				*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem));
void				ft_lstpushback(t_list **head, t_list *node);
void				ft_lst_insertionsort(t_list **head, t_list *node,
		int (*cmp)(void *a, void *b));
void				ft_lstrdel(void *content, size_t content_size);
void				ft_lststr_del(t_list **head);
t_headlst			*ft_init_headlst(void);

/*
** Stack functions
*/

void				push_stack(t_stack **head, void *content);
void				*pop_stack(t_stack **head);
void				*peek_stack(t_stack *head);

/*
** Trie functions
*/

t_trie				*ft_new_trie(void);
void				ft_push_trie(t_trie **head, char *str);
int					ft_trie_search(t_trie *head, char *str);
int					ft_trie_has_children(t_trie *node);
int					ft_del_trie(t_trie **node, char *str);
void				ft_free_trie(t_trie **head);

int					ft_isblank(int c);
int					ft_isspace(int c);
int					ft_iscntrl(int c);
int					ft_isgraph(int c);
int					ft_islower(int c);
int					ft_isupper(int c);
int					ft_isxdigit(int c);
void				ft_swap(int *a, int *b);
void				ft_sort_tab(int	*tab, unsigned int size);
size_t				ft_nbr_len(long nbr);
int					ft_str_is_lowercase(char *s);
int					ft_str_is_uppercase(char *s);
int					ft_str_is_alpha(char *s);
int					ft_str_is_numeric(char *s);
int					ft_str_is_printable(char *s);

/*
** Math functions
*/

int					ft_floorsqrt(int x);
long				ft_abs_ptr(void *ptr);
int					ft_abs_int(int nbr);
intmax_t			ft_abs(intmax_t nbr);

void				ft_putnbrbase(uintmax_t nbr, char *base);
void				print_hex(unsigned long long n);
size_t				ft_nbr_len_base(uintmax_t nb, int base);
int					printf_nbrlen_base(uintmax_t nbr, char *base);
char				*ft_get_stdout(int *pfd, int *save);
int					get_next_line(int const fd, char **line);

int					ft_is_dir(char *path);
int					ft_is_exec(char *path);
int					ft_is_binary(char *path);
int					ft_is_lnk(char *path);

/*
** Shell functions
*/

char				*get_envpath_from_file(void);
char				*ft_getenv(const char *name, char **environ);
int					ft_hash_addbin(t_hash_table *hashtable, char *key,
		char *val);
t_list				*ft_hash_getbin(t_hash_table *hashtable, char *str);
char				*ft_get_last_path_elem(char *path);
int					ft_is_quoted(char *str, char *ptr);
int					ft_ptr_is_quoted(char *str, char *ptr);
char				*ft_get_path(char *str);
int					ft_get_fd_read(char *file);
int					ft_get_fd_write(char *file, int append);

/*
** Hash functions
*/

t_hash_table		*ft_create_hash_table(int size);
unsigned int		ft_jenkins_hash(char *key, size_t len);
t_list				*ft_hash_find(t_hash_table *hashtable, char *str);
int					ft_hash_add(t_hash_table *hashtable, char *str);
t_list				*ft_hash_findkv(t_hash_table *hashtable, char *key,
		char *val);
int					ft_hash_addkv(t_hash_table *hashtable, char *key,
		char *val);
void				ft_free_hashtable(t_hash_table **hashtable);

/*
** Input functions
*/

int					ft_getc(int fd);
int					ft_getchar(void);
int					get_shell_line(int fd, char **line);
#endif
