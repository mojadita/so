dig		[0-9]
af0		{dig}{0,2}
af1     {dig}{1,3}
grp     {dig}{3}

e01      [+-]?{af1}([ ]{grp})*([,.]({grp}[ ])*{af1})?
e02      [+-]?{af1}([ ]{grp})*([,.]{af0})?
e03      [+-]?{af0}([,.]({grp}[ ])*{af1})?

e04      [+-]?{af1}([,]{grp})*([.]({grp}[,])*{af1})?
e05      [+-]?{af1}([,]{grp})*([.]{af0})?
e06      [+-]?{af0}([.]({grp}[,])*{af1})?

e07      [+-]?{af1}([.]{grp})*([,]({grp}[.])*{af1})?
e08      [+-]?{af0}([,]({grp}[.])*{af1})?
e09      [+-]?{af1}([.]{grp})*([,]{af0})?

e10		 [+-]?{dig}*[,.]{dig}+
e11		 [+-]?{dig}+[,.]{dig}*
e12		 [+-]?{dig}+

%%

{e01}       |
{e02}		|
{e03}		printf("<sep=[ ];dec=[.,]>[\033[32m%s\033[m]\n", yytext);

{e04}       |
{e05}		|
{e06}		printf("<sep=[,];dec=[.]> [\033[32m%s\033[m]\n", yytext);

{e07}       |
{e08}		|
{e09}		printf("<sep=[.];dec=[,]> [\033[32m%s\033[m]\n", yytext);

{e10}		|
{e11}		|
{e12}		printf("<sep=[];dec[,.]>  [\033[32m%s\033[m]\n", yytext);

[0-9.,+-]*  printf("<invalid>         [\033[31m%s\033[m]\n", yytext);

\t          |
\n          |
.           ;

%%
int main()
{
    yylex();
}

int yywrap()
{
    return 1;
}