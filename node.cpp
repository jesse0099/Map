#include <node.h>
#include <graphwidget.h>
#include <edge.h>
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QPainter>
#include <QStyleOption>
#include <QTextItem>
#include <QGraphicsTextItem>

Node::Node(GraphWidget *graphWidget, Vertex* p_vertex)
    : graph(graphWidget)
{

    vertex = p_vertex;
    setFlag(ItemIsFocusable);
    setFlag(ItemIsSelectable);
    //setFlag(ItemIsMovable);
    setFlag(ItemSendsGeometryChanges);
    setCacheMode(DeviceCoordinateCache);
    setZValue(-1);
}

void Node::addEdge(Edge *edge)
{
    edgeList << edge;
    edge->adjust();
}

Vertex* Node::get_vertex() const
{
    return vertex;
}

QVector<Edge *> Node::edges() const
{
    return edgeList;
}

QRectF Node::boundingRect() const
{
    qreal adjust = 2;
    return QRectF( -10 - adjust, -10 - adjust, 43 + adjust, 43 + adjust);
}

QPainterPath Node::shape() const
{
    QPainterPath path;
    path.addEllipse(-10, -10, 40, 40);
    return path;
}

void Node::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *)
{
    painter->setPen(Qt::NoPen);
    painter->setBrush(Qt::darkGray);
    painter->drawEllipse(-7, -7, 40, 40);

    QRadialGradient gradient(-3, -3, 20);
    if (option->state & QStyle::State_Sunken) {
        gradient.setCenter(3, 3);
        gradient.setFocalPoint(3, 3);
        gradient.setColorAt(1, QColor(Qt::yellow).lighter(120));
        gradient.setColorAt(0, QColor(Qt::darkYellow).lighter(120));
    } else {
        gradient.setColorAt(0, Qt::yellow);
        gradient.setColorAt(1, Qt::darkYellow);
    }
    //Node Tag
    /*Auxilioo*/

    painter->setBrush(gradient);

    painter->setPen(QPen(Qt::black, 0));
    painter->drawEllipse(-10, -10, 40, 40);
}
