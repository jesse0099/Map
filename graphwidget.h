#include <vector>
#include <QGraphicsView>

class Node;
class Vertex;
class Edge;
class Edge_tmp;

using namespace std;

class GraphWidget : public QGraphicsView
{
    Q_OBJECT

public:
    GraphWidget(QWidget *parent = nullptr, vector<Vertex> *p_vertexes = nullptr);
    ~GraphWidget();
    /*void itemMoved();*/

public slots:
    //void shuffle();
    vector<Node*>* get_nodes();
    vector<Vertex>* get_vertexes();
    void zoomIn();
    void zoomOut();
    void set_vertexes(vector<Vertex>* p_vertexes);
    void set_nodes(vector<Node*> *p_nodes);
    void set_edges(vector<Edge_tmp> *p_tmpedges);
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
    Node *centerNode;
    vector<Vertex>* vertexes;
    vector<Edge*>* edges;
    vector<Node*>* nodes;
    QGraphicsScene *scene;
};
