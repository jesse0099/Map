#include <vector>
#include <QGraphicsView>
#include <QTextEdit>
#include <QPushButton>


class Node;
class Vertex;
class Edge;
class Edge_tmp;
class Graph;

using namespace std;

class GraphWidget : public QGraphicsView
{
    Q_OBJECT


public:
    static int selectecNodesCount;
    static Node* sourceNode;
    static Node* destNode;
    static QTextEdit* logger;
    static QPushButton* calc;
    static QString backgroundURL;

    static void check_node_selection(Node* selectedNode);
    static void log(string message);
    static void predictTime(string transport, int w);

    GraphWidget(QWidget *parent = nullptr, vector<Vertex> *p_vertexes = nullptr);
    ~GraphWidget();

    void set_vertexes(vector<Vertex>* p_vertexes);
    void set_nodes(vector<Node*> *p_nodes);
    void set_edges(vector<Edge_tmp> *p_tmpedges);
    void set_graph(Graph* p_graph);


    vector<Node*>* get_nodes();
    vector<Vertex>* get_vertexes();
    vector<Edge*>* get_edges();
    QGraphicsScene* get_scene();
    Graph* get_graph();
    /*void itemMoved();*/



public slots:
    //void shuffle();
    void zoomIn();
    void zoomOut();

protected:
    //void keyPressEvent(QKeyEvent *event) override;
    //void timerEvent(QTimerEvent *event) override;
#if QT_CONFIG(wheelevent)
    void wheelEvent(QWheelEvent *event) override;
#endif
    void drawBackground(QPainter *painter, const QRectF &rect) override;
    void scaleView(qreal scaleFactor);

private:
    int timerId = 0;
    vector<Vertex>* vertexes;
    vector<Edge*>* edges;
    vector<Node*>* nodes;
    QGraphicsScene* scene;
    Graph* grafo;
};

