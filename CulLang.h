#include "Lexer.h"
#include "Parser.h"
#include "Position.h"
#include "PreProcessor.h"
#include "Program.h"
#include "Utilities.h"
#include "debug/ErrorHandler.h"
namespace CulLang {
class CulLang {
  public:
    CulLang() = default;
    std::string getInput() {
        std::string a;
        std::cout << ">>> ";
        std::getline(std::cin, a);
        return a;
    }

    std::vector<Ref<Node>> getAST(std::string code) {
        // a preprocessor class (will be removed on later commits)
        PreProcessor pprocess(code);
        code = pprocess.format();

        LOG(code);
        LOG("LEXER : START");

        // running the lexer and making tokens
        Lexer lexer;
        auto tokens = lexer.make_tokens(code);

        // returning if any error occured
        if (ErrorHandler::anyErrors()) {
            std::cout << "Lexer : Error occured failed" << '\n';
            return {};
        }

        for (auto &i : tokens)
            LOG(i.getTypeStr() + ' ' + i.getVal());

        LOG("LEXER : DONE");
        LOG("PARSER : START");
        // parsing the tokens and making nodes(vector of no)
        Parser parser(tokens);
        auto nodes = parser.parse();

        // returning if any error occured
        if (ErrorHandler::anyErrors()) {
            std::cout << "Parser : Error occured failed" << '\n';
            return {};
        }
        LOG("PARSER : DONE");

#if 0
        DEBUG_LOG(nodes[0]->getInStr());
        for (auto &node : nodes)
            std::cout << node << ' ' << (node ? node->getInStr() : "node") <<' '<< (node ? node->GetToken()->getVal() : "node")
                      << std::endl;
#endif
        return nodes;
    }

    std::string interpreteCode(std::string code) {
        code+='\n';
        std::vector<Ref<Node>> nodes = getAST(code);
        if (!nodes.size())
            std::cout << "Error occured\n";
        LOG("RUNNING");
        Ref<Object> object = nodes[0]->visit();
        LOG("DONE RUNNING");
        return object != Object::NONE ? object->asAStr() : "";
    }

    void runInterpreter() {
        std::string input = "";
        std::string out = "";
        while (true) {
            input = getInput();
            if (input == ".")
                break;
            if (input == "") {
                std::cout << '\r';
                continue;
            }
            auto out = interpreteCode(input);
            std::cout << out << '\n';
        }
        ErrorHandler::clear();
        SymbolTable::getGlobal().clear();
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
        if (!code.length())
            return;

        std::vector<Ref<Node>> nodes = getAST(code);
        // creating the program object and run it

        if (!nodes.size())
            return;

        Program prog(nodes);
        prog.run();

        LOG("DEBUG:\n");
        LOG(ErrorHandler::anyErrors());
        LOG(ErrorHandler::anyStackErrors());
        LOG(ErrorHandler::getStack().size());

        // clearing the data
        ErrorHandler::clear();
        SymbolTable::getGlobal().clear();
        // DEBUG
        // std::cout<<"end\n";
    }

  private:
};
} // namespace CulLang