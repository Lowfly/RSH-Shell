
#ifndef TOKEN_H_
# define TOKEN_H_

typedef struct s_token	t_token;
typedef union u_content	t_content;

typedef enum {S_QUOTE,
              B_SLASH,
              SEPARATOR,
              B_QUOTE,
              D_QUOTE,
              PO,
              PC,
              OR,
              AND,
              PIPE,
              VAR,
              RED_L,
              RED_R,
	      D_RED_L,
	      D_RED_R,
              BG,
	      SPACE,
	      WORD,
	      CMD,
	      GLOB,
	      BRACESO,
	      BRACESC,
	      HOME,
	      FILENAME,
	      SAVE} t_ttype;

typedef enum {DEFINE, STRING, LIST} t_value;

union u_content
{
  char		define;
  char		*str;
  t_token	*list;
};

struct s_token
{
  t_ttype                type;
  t_value		value_type;
  t_content		value;
  struct s_token	*next;
};

typedef struct s_token_func
{
  char		tokenprim;
  t_ttype	token_id;
}	t_token_func;

#endif
