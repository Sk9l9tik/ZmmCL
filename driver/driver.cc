#include <iostream>

#include "driver.hh"

AST::IScope *CURRENT_SCOPE = nullptr;


namespace yy
{
  bool NumDriver::parse()
  {
    parser parser(this);
    bool res = parser.parse();
    return !res;
  }

  parser::token_type NumDriver::yylex(parser::semantic_type *yylval)
  {
    parser::token_type tt = static_cast<parser::token_type>(plex_->yylex());
    if (tt == parser::token_type::INT)
        try {
            yylval->emplace<int>(std::stoi(plex_->YYText()));
        }
        catch (std::out_of_range& err) {
            throw std::runtime_error("Int out of range");
        }
      
    if (tt == parser::token_type::NAME)
      yylval->emplace<std::string>(std::string{plex_->YYText()});
    return tt;
  }

      void NumDriver::switch_streams(std::istream &new_in, std::ostream &new_out){
        plex_->switch_streams(new_in,new_out);
      }
}