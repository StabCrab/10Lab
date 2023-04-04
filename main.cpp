#include "MyGrammarBaseListener.h"
#include "MyGrammarLexer.h"
#include "MyGrammarParser.h"
#include <ANTLRInputStream.h>
#include <antlr4-runtime.h>
#include <exception>
#include <iostream>
#include <stdexcept>
#include <string>
#include <unordered_map>

std::unordered_map<std::string, int> hashtable;

// class MyGrammarListener : public antlr4::tree::ParseTreeListener {};
class Listener : public MyGrammarBaseListener {
  void exitEe(MyGrammarParser::EeContext *ctx) override {
    // E ::= ++S E1 | S E2
    static int value = 0;
    std::string var_name;
    if (ctx->STR() != nullptr) {
      var_name = ctx->STR()->getText();
    } else if (ctx->INT() != nullptr) {
      value = stoi(ctx->INT()->toString());
      return;
    }
    hashtable[var_name] = value;

    if (ctx->e1() != nullptr) {
      // ПРЕД инкремент
      hashtable[var_name]++;
      value++;
    } else if (ctx->e2() != nullptr) {
      if (ctx->e2()->PLUSPLUS() != nullptr) {
        // ПОСТ инкремент
        hashtable[var_name]++;
      }
    }
  }
};

int main(int argc, const char *argv[]) {
  std::ifstream stream;
  if (argc > 1) {
    stream.open(argv[1]);
    std::cout << argv[1] << std::endl;
  } else {
    stream.open("../test");
  }
  antlr4::ANTLRInputStream input(stream);

  MyGrammarLexer lexer(&input);
  antlr4::CommonTokenStream tokens(&lexer);

  tokens.fill();
  for (auto token : tokens.getTokens()) {
    std::cout << token->toString() << std::endl;
  }

  MyGrammarParser parser(&tokens);
  Listener listener;
  parser.addParseListener(&listener);

  antlr4::tree::ParseTree *tree = parser.ee();

  std::cout << tree->toStringTree(&parser) << std::endl << std::endl;

  for (const auto &p : hashtable) {
    std::cout << p.first << " : " << p.second << std::endl;
  }

  return 0;
}
