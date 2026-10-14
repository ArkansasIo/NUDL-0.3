#include "nudl/lexer.hpp"
#include "nudl/parser.hpp"
#include <fstream>
#include <iostream>
#include <sstream>
using namespace nudl;
int main(int argc,char**argv){if(argc<2){std::cerr<<"usage: nudlc <file.nudl>\n";return 2;}std::ifstream f(argv[1]);if(!f){std::cerr<<"nudlc: cannot open "<<argv[1]<<"\n";return 2;}std::stringstream ss;ss<<f.rdbuf();auto tokens=lex(ss.str());Diagnostics d;Parser p(std::move(tokens),d);auto program=p.parse();if(!d.ok()){for(auto&e:d.errors())std::cerr<<argv[1]<<":"<<e.line<<":"<<e.column<<": error: "<<e.message<<"\n";return 1;}std::cout<<"NUDL parsed successfully: "<<program->functions.size()<<" function(s), "<<program->statements.size()<<" top-level statement(s)\n";return 0;}