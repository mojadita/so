
lbl		([a-zA-Z]([a-zA-Z0-9-]{0,61}[a-zA-Z0-9])?)
dom		{lbl}(\.{lbl})*

%%

^{dom}$		ECHO;
.			;

%%

int main()
{
	yylex();
}

int yywrap()
{
	return -1;
}
