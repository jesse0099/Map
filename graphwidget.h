#include <vector>
#include <QGraphicsView>

class Node;
class Vertex;

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
    vector<Node*> *nodes;
    QGraphicsScene *scene;
};
