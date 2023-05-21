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
        std::cout << "BFS Tree from countNodes = 5 is in file" << std::endl << "Search BFS (100)" << std::endl << "Parent line from 100:" << std::endl;
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
        std::cout << "BFS tree from countNodes = 1 is in file" << std::endl << "Search BFS (5): " << std::endl;
        std::pair<bool, std::list<int>> way = gr->searchBFS(5);
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

    {                                                   //build from wrong input, graph wasn't build, output wont't work
        Graph* gr = new Graph;
        gr->buildTreeBFS(-10);
        gr->BFS();
        delete gr;
        std::cout << "BFS graph wasn't build from wrong input (-10), output also didn't work" << std::endl << std::endl;
    }

    {
        Graph* gr = new Graph(0);                       //build and output from nameNode = 0
        gr->BFS();                                      //file output is tree from nameNode = 0
        delete gr;
        std::cout << "BFS Tree from countNodes = 0 is in file" << std::endl << std::endl;
    }
}

void task_2(void) {
    {                                                    //build without constructor from nameNode = 3
        Graph* gr = new Graph;                           //console output: 2, 1, 0; file output is tree from nameNode = 3
        gr->buildTreeDFS(3);
        gr->DFS();
        std::pair<bool, std::list<int>> way = gr->searchDFS(3);
        if (way.first == false) {
            std::cout << "NO" << std::endl;
        }
        std::cout << "DFS Tree from countNodes = 3 is in file" << std::endl << "Search DFS (3)" << std::endl << "Parent line from 3:" << std::endl;
        std::list<int>::iterator it = way.second.begin();
        while (it != way.second.end()) {
            std::cout << *it << std::endl;
            it++;
        }
        std::cout << std::endl;
        delete gr;
    }

    {
        Graph* gr = new Graph;                            //build without constructor from nameNode = 1
        gr->buildTreeDFS(1);                              //file output is tree from nameNode = 1
        gr->DFS();
        delete gr;
        std::cout << "DFS Tree from countNodes = 1 is in file" << std::endl << std::endl;
    }

    {
        Graph* gr = new Graph;                            //build from wrong input, graph wasn't build, output wont't work
        gr->buildTreeDFS(-10);                            
        gr->DFS();
        delete gr;
        std::cout << "DFS graph wasn't build from wrong input (-10), output also didn't work" << std::endl << std::endl;
    }

    {
        Graph* gr = new Graph;                            //build without constructor from nameNode = 0
        gr->buildTreeDFS(0);                              //file output is tree from nameNode = 0
        gr->DFS();
        delete gr;
        std::cout << "DFS Tree from countNodes = 0 is in file" << std::endl;
    }
}

int main()
{
    task_1();
    task_2();
    return 0;
}