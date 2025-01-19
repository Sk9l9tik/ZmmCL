#pragma once

#include "../grammar/grammar.tab.hh"
#if !defined(yyFlexLexerOnce)
#include <FlexLexer.h>
#endif

namespace yy
{

  class NumDriver
  {
    friend class parser;
    FlexLexer *plex_;
  public:
    NumDriver(FlexLexer *plex) : plex_(plex){};

   parser::token_type yylex(parser::semantic_type *yylval);

    bool parse();



    void switch_streams(std::istream &new_in, std::ostream &new_out);
  };

}
