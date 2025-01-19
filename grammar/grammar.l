%option c++
%option noyywrap
%option yylineno
%{
#include <iostream>
#include <string>
#include <fstream>
#include "grammar.tab.hh"

using std::cout;
using std::endl;

%}

N                       [\n]
WS                      [ \t\v\r]+
NUM2                    0b[01]+
NUM10                   [1-9][0-9]*|0
NUM16                   0x([1-9A-F][0-9A-F]|0)
NUM                     {NUM10}
COMMENT                 \/\*(.|\n)*\*\/|\/\/.*\n
NAME                    [A-Za-z_][A-Za-z0-9_]*

%s Z_COMMENT


%%

{WS}|{COMMENT}|{N}        /*do nothing*/

"+"                     {return yy::parser::token_kind_type::ADD;}
"-"                     {return yy::parser::token_kind_type::SUB;}
"*"                     {return yy::parser::token_kind_type::MUL;}
"/"                     {return yy::parser::token_kind_type::DIV;}
"%"                     {return yy::parser::token_kind_type::MOD;}

"<"                     {return yy::parser::token_kind_type::LESS;}
">"                     {return yy::parser::token_kind_type::GREATER;}
"<="                    {return yy::parser::token_kind_type::LS_EQ;}
">="                    {return yy::parser::token_kind_type::GR_EQ;}
"=="                    {return yy::parser::token_kind_type::EQ;}
"!="                    {return yy::parser::token_kind_type::NEQ;}

"||"                    {return yy::parser::token_kind_type::OR;}
"&&"                    {return yy::parser::token_kind_type::AND;}
"!"                     {return yy::parser::token_kind_type::NOT;}

"="                     {return yy::parser::token_kind_type::ASSIGN;}
";"                     {return yy::parser::token_kind_type::SCL;}

"("                     {return yy::parser::token_kind_type::LB;}
")"                     {return yy::parser::token_kind_type::RB;}
"{"                     {return yy::parser::token_kind_type::LCB;}
"}"                     {return yy::parser::token_kind_type::RCB;}

"if"                    {return yy::parser::token_kind_type::IF;}
"else"                  {return yy::parser::token_kind_type::ELSE;}
"while"                 {return yy::parser::token_kind_type::WHILE;}

"print"                 {return yy::parser::token_kind_type::PRINT;}
"input"                 {return yy::parser::token_kind_type::INPUT;}

{NUM}                   {return yy::parser::token_kind_type::INT; }
{NAME}                  {return yy::parser::token_kind_type::NAME; }

.                       {return yy::parser::token_kind_type::ERR;}

%%
