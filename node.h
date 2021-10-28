#include <QGraphicsItem>
#include <QVector>
#include <QTextEdit>
#include <string>

using namespace std;

class GraphWidget;
class Vertex;
class Edge;

class Node : public QGraphicsItem
{
public:
    Node(GraphWidget *graphWidget, Vertex* p_vertex);

    void addEdge(Edge *edge);
    void set_tag(string p_tag);
    void set_vertex(Vertex* p_vertex);
    QVector<Edge *> edges() const;
    Vertex* get_vertex() const;

    /*void addEdge(Edge *edge);
    QVector<Edge *> edges() const;*/

    enum { Type = UserType + 1 };
    int type() const override { return Type; }

    /*void calculateForces();
    bool advancePosition();*/

    QRectF boundingRect() const override;
    QPainterPath shape() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

protected:
    //QVariant itemChange(GraphicsItemChange change, const QVariant &value) override;

    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void consoleLog(QTextEdit &txtMapInfo);
    //void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;

private:
    QVector<Edge *> edgeList;
    QPointF newPos;
    GraphWidget *graph;
    Vertex *vertex;
};
