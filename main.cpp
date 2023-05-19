#include "tasks_rk2.h"

void task_1(void) {
#ifdef MEMORY_LEAK
    while (true) {                                    //memory leak test
        Graph* gr = new Graph(5);
        delete gr;
    }
#endif
    {                                                   //build from constructor, output, search test
        Graph* gr = new Graph(5);                       //console output: 33 8 1 0; file output is tree from nameNode = 5
        gr->BFS();
        std::pair<bool, std::list<int>> way;
        way = gr->searchBFS(100);
        if (way.first == false) {
            std::cout << "Element not found" << std::endl;
        }
        std::list<int>::iterator it = way.second.begin();
        while (it != way.second.end()) {
            std::cout << *it << std::endl;
            it++;
        }
        std::cout << std::endl;
        delete gr;
    }

    {                                                    //build without constructor from nameNode = 1, output, wrong search
        Graph* gr = new Graph;                           //console output: NO; file output is tree from nameNode = 1
        gr->buildTreeBFS(1);
        gr->BFS();
        std::pair<bool, std::list<int>> way = gr->searchBFS(5);
        if (way.first == false) {
            std::cout << "NO" << std::endl;
        }
        std::list<int>::iterator it = way.second.begin();
        while (it != way.second.end()) {
            std::cout << *it << std::endl;
            it++;
        }
        std::cout << std::endl;
        delete gr;
    }

    {                                                   //build from wrong input, graph wasn't build, output wont't work
        Graph* gr = new Graph;
        gr->buildTreeBFS(-10);
        gr->BFS();
    }

}

int main()
{
    task_1();
    return 0;
}