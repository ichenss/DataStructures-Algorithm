#include <iostream>
#include <list>
#include <string>
#include <string.h>
#include <vector>
#include <queue>
using namespace std;

class Digraph
{
public:
    void readFile(string filePath)
    {
        FILE *pf = fopen(filePath.c_str(), "r");
        if (pf == nullptr) 
        {
            throw filePath + "not exits";
        }

        // 占用0号位置
        vertics.emplace_back("");

        while (!feof(pf))
        {
            char line[1024] = {0};
            fgets(line, 1024, pf);
            string linestr(line);
            // 增加一个节点信息
            vertics.emplace_back(linestr.substr(0, linestr.size()-1));

            fgets(line, 1024, pf);
            char *vertic_no = strtok(line, ",");
            while (vertic_no != nullptr)
            {
                int vex = atoi(vertic_no);
                if (vex > 0)
                {
                    vertics.back().adjList_.emplace_back(vex);
                }
                
                vertic_no = strtok(nullptr, ",");
            }
        }
        fclose(pf);
    }

    // 输出邻接表信息
    void show() const
    {
        for (int i = 1; i < vertics.size(); i++)
        {
            cout << vertics[i].data_ << " : ";
            for (auto num : vertics[i].adjList_)
            {
                cout << num << " ";
            }
            cout << endl;
        }
        cout << endl;
    }

    void dfs()
    {
        vector<bool> visited(vertics.size(), false);
        dfs(1, visited);
        cout << endl;
    }

    void bfs()
    {
        vector<bool> visited(vertics.size(), false);
        queue<int> que;

        que.push(1);
        visited[1] = true;
        while (!que.empty())
        {
            int cur_no = que.front();
            que.pop();

            cout << vertics[cur_no].data_ << " ";
            
            for (auto no : vertics[cur_no].adjList_)
            {
                if (!visited[no])
                {
                    que.push(no);
                    visited[no] = true;
                }
            }
        }
        cout << endl;
    }

private:
    void dfs(int start, vector<bool>& visited)
    {
        if (visited[start])
        {
            return;
        }

        cout << vertics[start].data_ << " ";
        visited[start] = true;
        
        for (auto no : vertics[start].adjList_)
        {
            dfs(no, visited);
        }
    }

private:
    // 顶点类型
    struct Vertic
    {
        Vertic(string data) 
            : data_(data)
        {}
        string data_;
        list<int> adjList_;
    };

private:
    vector<Vertic> vertics;
};

int main()
{
    Digraph graph;
    graph.readFile("data.txt");
    graph.show();
    graph.dfs();
    graph.bfs();
    return 0;
}
