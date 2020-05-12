g1          ([0-9]([,]?[0-9])*)
g2          ([0-9]([.]?[0-9])*)
g3          ([0-9]([ ]?[0-9])*)
r1          [+-]?({g1}([.]{g1}?)?|[.]{g1})
r2          [+-]?({g2}([,]{g2}?)?|[,]{g2})
r3          [+-]?({g3}([.,]{g3}?)?|[.,]{g3})
%%
{r3}             printf("<sep=[ ];dec=[.,]>[\033[32m%s\033[m]\n", yytext);
{r1}             printf("<sep=[,];dec=[.]> [\033[32m%s\033[m]\n", yytext);
{r2}             printf("<sep=[.];dec=[,]> [\033[32m%s\033[m]\n", yytext);
[0-9.,+-]*       printf("<invalid>         [\033[31m%s\033[m]\n", yytext);
\t               |
\n               |
.                ;
%%
int main()
{
    yylex();
}

int yywrap()
{
    return 1;
}
