#include <node.h>
#include <vertex.h>
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
    setZValue(2);
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
    return QRectF( -10 - adjust, -10 - adjust, 343 + adjust, 43 + adjust);
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

    if(this->isSelected()){
        gradient.setCenter(3, 3);
        gradient.setFocalPoint(3, 3);
        gradient.setColorAt(1, QColor(Qt::yellow).lighter(120));
        gradient.setColorAt(0, QColor(Qt::darkYellow).lighter(120));
    } else {
        //gradient.setColorAt(1,  QColor(Qt::white));
        gradient.setColorAt(0,  QColor(Qt::blue).lighter(150));
    }
    //Node Tag



    painter->setBrush(gradient);
    painter->setPen(QPen(Qt::black, 0));
    painter->drawEllipse(-10, -10, 40, 40);

    //Tags
    QFont font = painter->font();
    font.setPixelSize(18);
    font.setFamily("Comic Sans");
    font.setWeight(QFont::Bold);


    painter->setFont(font);

    painter->setPen(QPen(Qt::darkRed, 3));
    painter->drawText(boundingRect(),Qt::AlignTop,QString::fromStdString(vertex->get_tag()));

}

void Node::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    GraphWidget::selectecNodesCount++;
    update();
    QGraphicsItem::mousePressEvent(event);
    GraphWidget::check_node_selection(this);
    graph->update();
}

void Node::set_vertex(Vertex *p_vertex){
    vertex = p_vertex;
}
