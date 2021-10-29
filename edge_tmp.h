#include<string>
#include<QString>

using namespace std;

class Edge_tmp
{
public:
    Edge_tmp();
    ~Edge_tmp();
    string from;
    string tag;
    string to;
    int weight;
    bool type;
    QString convToQString(string value);
    Edge_tmp buildEdge(QString value);

private:

};
