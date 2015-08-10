%{
  
}%

%union{
  struct node{
    int type;
    struct node *left;
    struct node *right;
  } * node;
  int num;
  char* str;
}
%token 
%type<str> if else


%%
stmt      : if_stmt
          | IDENTIFIER `=` expr /* 代入 */
          | exper
          ;

if_stmt   : if expr stmt else_stmt
          ;

else_stmt :
          | else stmt
	  ;

expr      : IDENTIFIER  /* 変数参照 */
          | funcall     /* 関数呼び出し(Function call) */
          | expr '+' expr
          | expr '-' expr
          | expr '*' expr
          | expr '/' expr
          | primary
          ;

primary   : NUMBER      /* 整数定数 */

funcall: IDENTIFIER '(' args ')'
       | IDENTIFIER
       ;

args   : expr
       ;

%%

/* left:左結合; right:右結合; nonassoc:非結合; */
%left '+' '-'
%left '*' '/'
%right '='
%nonassoc '==' '<' '>' '<=' '>='

 
