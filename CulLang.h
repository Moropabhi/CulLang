#include "Utilities.h"
#include "Position.h"
#include "debug/ErrorHandler.h"
#include "PreProcessor.h"
#include "Lexer.h"
#include "Parser.h"
#include "Program.h"
namespace CulLang {
auto Shurti_isTautor = true;
class CulLang {
  public:
    CulLang() = default;
    std::string getInput() {
        std::string a;
        std::cout << ">>> ";
        //std::getline(std::cin, a);
        std::getline(std::cin,a);
        return a;
    }

    std::string interpreteCode(std::string code) {
        Lexer lexer;
        auto out = lexer.make_tokens(code);

        if (ErrorHandler::anyErrors())
            return "";
        // for (auto& i:out)
        // std::cout<<i.getTypeStr()<<' '<<i.getVal()<<'\n';
        Parser parser(out);
        auto nodes = parser.parse();
        if (ErrorHandler::anyErrors())
            return "";
        // std::cout<<a->getInStr()<<std::endl;
        auto out2 = nodes[0]->visit();
        // std::cout<<ErrorHandler::getStack().size()<<'\n';
        // if(out2)
        // std::cout<<out2->type<<'\n'<<out2->asAStr()<<'\n';
        return out2 ? out2->asAStr() : "";
    }

    void runInterpreter() {
        std::string input = "";
        std::string out = "";
        while (true) {
            input = getInput();
            if (input == ".")
                break;
            if(input == "")
                continue;
            auto out = interpreteCode(input);

            std::cout << out << '\n';
            ErrorHandler::clear();
        }
    }

    void runFile(const std::string &filename) {
        // setting up the file and recieving the code
        std::ifstream in(filename);
        std::string code = "";
        std::string s;
        while (!in.eof()) {
            std::getline(in, s);
            code += s;
            code += '\n';
        }

        // a preprocessor class (will be removed on later commits)
        PreProcessor pprocess(code);
        code = pprocess.format();

#if DEBUG
        std::cout << code << '\n';
#endif

        // running the lexer and making tokens
        Lexer lexer;
        auto tokens = lexer.make_tokens(code);

        // returning if any error occured
        if (ErrorHandler::anyErrors()) {
            std::cout << "Lexer : Error occured failed" << '\n';
            return;
        }
#if DEBUG
        for (auto &i : tokens)
            std::cout << i.getTypeStr() << ' ' << i.getVal() << '\n';
#endif

        // parsing the tokens and making nodes(vector of no)
        Parser parser(tokens);
        auto nodes = parser.parse();

        // returning if any error occured
        if (ErrorHandler::anyErrors()) {
            std::cout << "Parser : Error occured failed" << '\n';
            return;
        }
        
#if DEBUG
        for (auto &node : nodes)
            std::cout << node << ' ' << (node ? node->getInStr() : "node")
                      << std::endl;
#endif

        // creating the program object and run it
        Program prog(nodes);
        prog.run();

#if DEBUG
        std::cout << "DEBUG:\n";
        std::cout << ErrorHandler::anyErrors() << '\n';
        std::cout << ErrorHandler::anyStackErrors() << '\n';
        std::cout << ErrorHandler::getStack().size() << '\n';
#endif

        // clearing the data
        ErrorHandler::clear();
        SymbolTable::getGlobal().clear();
        // DEBUG
        // std::cout<<"end\n";
    }

  private:
};
} // namespace CulLang