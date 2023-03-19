#include "debug/ErrorHandler.h"
#include "nodes/Node.h"
#include "datatypes/Object.h"
namespace CulLang {

class Program {
  public:
    Program(std::vector<Ref<Node>> nodes) : nodes(nodes) {
        // std::cout<<"build"<<'\n';
    }
    void run() {
        // std::cout<<nodes.size()<<'\n';
        for (auto &node : nodes) {
            if (ErrorHandler::anyErrors() || ErrorHandler::anyStackErrors())
                return;
            node->visit();
        }
    }

  private:
    std::vector<Ref<Node>> nodes;
};
} // namespace CulLang