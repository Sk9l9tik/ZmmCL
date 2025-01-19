%language "c++"

%require  "3.0"

%skeleton "lalr1.cc"


%param { yy::NumDriver * driver }

%define parse.trace
%define parse.lac full
%define api.value.type variant
%define parse.error verbose

%code requires{

#include <string>
#include <iostream>
#include "../AST/INode.hh"


namespace yy { class NumDriver; }

}

%code{

#include "../driver/driver.hh"


namespace yy    {
  
void yyerror(const char *);

parser::token_type yylex(parser::semantic_type* yylval, NumDriver* driver);

}

}


%token
    END                      
    
    IF                      

    ELSE                    

    THEN

    WHILE                   

    PRINT                   

    INPUT                   

    LB                      
    RB                      

    LCB                     
    RCB                     

    CL			    
    SCL                     

    ADD                     
    SUB                     
    MUL                     
    DIV                     
    MOD                     

    LESS                    
    GREATER                 
    LS_EQ                   
    GR_EQ                   
    EQ                      
    NEQ                     
    
    OR                      
    AND                     
    NOT                     
    NEG

    ERR
    
    ASSIGN
    
;


%nterm <AST::IScope_ptr>
	Scope
	OpenBracketScope
	BracketScope
	BracketStatement
;

%nterm <AST::INode_ptr>
	Statement
	StatementList
;

%nterm <AST::INode_ptr>
	IfStatement
	WhileStatement
	Print
	Assigment
  	Input
;

%nterm <AST::INode_ptr>
	Expression
	UnaryExpression
	TerminalExpression
;


%left EQ NEQ OR;
%left  AND NOT;
%left LESS GREATER LS_EQ GR_EQ;
%left ADD SUB;
%left MUL DIV MOD;
%right  NEG;
%right ELSE THEN;

%token <int>                  INT
%token <std::string>          NAME

%start Program;

%%

Program:                  StatementList {}
;

Scope:                    OpenScope StatementList CloseScope {}
;

BracketScope:		OpenBracketScope StatementList CloseScope	{$$ = $1;}
;

OpenScope:                LCB {
							auto parent = CURRENT_SCOPE;
							auto sc = AST::make_scope(parent);
							CURRENT_SCOPE = sc.get();
							if(parent) parent->push(sc);
							}
;

OpenBracketScope:	   LCB {
				$$ = AST::make_scope(CURRENT_SCOPE);
				CURRENT_SCOPE = $$.get();
				}
;

CloseScope:                RCB {CURRENT_SCOPE = CURRENT_SCOPE->reset_scope();}
;


StatementList:            Statement  {CURRENT_SCOPE->push($1);} |
                          StatementList Statement {CURRENT_SCOPE->push($2);}| 
                          Scope {}|
                          StatementList Scope {}
;


Statement:                IfStatement     {$$ = $1;}|
                          WhileStatement  {$$ = $1;}|
                          Assigment       {$$ = $1;}|
                          Print           {$$ = $1;}|
                          Input           {$$ = $1;}|
                          Expression SCL  {$$ = $1;}
;


BracketStatement:         Statement {$$ = AST::make_scope(CURRENT_SCOPE);
                                    $$->push($1);}|
                          BracketScope {$$ = $1;}
;




IfStatement:              IF LB Expression RB BracketStatement ELSE BracketStatement {$$ = AST::make_if_else($3, $5, $7);}|
                          IF LB Expression RB BracketStatement %prec THEN {$$ = AST::make_if($3, $5);}
;


WhileStatement:           WHILE LB Expression RB BracketStatement {$$ = AST::make_while($3,$5);}
;


Assigment:                NAME ASSIGN Expression SCL  {$$ = AST::make_assign($1, $3);}
;


Print:                    PRINT Expression SCL         {$$ = AST::make_print($2); }
;


Input:                    INPUT NAME SCL           	{$$ = AST::make_assign($2, AST::make_input());}
;


Expression:               Expression ADD Expression     {$$ = AST::make_operator($1,AST::Operator_t::ADD, $3);}|
                          Expression SUB Expression     {$$ = AST::make_operator($1,AST::Operator_t::SUB, $3);}|
                          Expression MUL Expression     {$$ = AST::make_operator($1,AST::Operator_t::MUL, $3);}|
                          Expression DIV Expression     {$$ = AST::make_operator($1,AST::Operator_t::DIV, $3);}|
                          Expression MOD Expression     {$$ = AST::make_operator($1,AST::Operator_t::MOD, $3);}|

                          Expression LESS Expression    {$$ = AST::make_operator($1,AST::Operator_t::LESS, $3);}|
                          Expression GREATER Expression {$$ = AST::make_operator($1,AST::Operator_t::GREATER, $3);}|
                          Expression LS_EQ Expression   {$$ = AST::make_operator($1,AST::Operator_t::LS_EQ, $3);}|
                          Expression GR_EQ Expression   {$$ = AST::make_operator($1,AST::Operator_t::GR_EQ, $3);}|
                          Expression EQ Expression      {$$ = AST::make_operator($1,AST::Operator_t::EQ, $3);}|
                          Expression NEQ Expression     {$$ = AST::make_operator($1,AST::Operator_t::NEQ, $3);}|

                          Expression OR Expression      {$$ = AST::make_operator($1,AST::Operator_t::OR, $3);}|
                          Expression AND Expression     {$$ = AST::make_operator($1,AST::Operator_t::AND, $3);}|
                    
                          UnaryExpression		  {$$ = $1;}
                    
;

UnaryExpression:    	    SUB UnaryExpression %prec NEG {$$ = AST::make_unary_operator(AST::Operator_t::NEG,$2);}|
			                    NOT	UnaryExpression %prec NOT {$$ = AST::make_unary_operator(AST::Operator_t::NOT,$2);}|
			                    TerminalExpression				    {$$ = $1;}
;

TerminalExpression: 	    LB Expression RB              {$$ = $2;}|
                    	    INT                           {$$ = AST::make_value($1);}|
                    	    NAME                          {$$ = AST::make_reference($1);}
;



%% 

namespace yy {

parser::token_type yylex(parser::semantic_type* yylval,                         
                         NumDriver* driver)
{
  return driver->yylex(yylval);
}

void parser::error(const std::string& mess){
  std::cout<<mess<<" in line "<<driver->plex_->lineno()<<std::endl;
}
}
