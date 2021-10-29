#include "edge.h"
#include "node.h"
#include <QPainter>
#include <QString>
#include <math.h>

Edge::Edge(Node *sourceNode, Node *destNode, string p_tag, int p_peso,bool p_bidir)
    : source(sourceNode), dest(destNode)
{
    tag = p_tag;
    peso = p_peso;
    setToolTip(QString::fromStdString(tag+"("+to_string(peso)+")"));
    bidir = p_bidir;
    setAcceptedMouseButtons(Qt::NoButton);
    source->addEdge(this);
    dest->addEdge(this);
    adjust();

}

Node *Edge::sourceNode() const
{
    return source;
}

Node *Edge::destNode() const
{
    return dest;
}

void Edge::adjust()
{
    if (!source || !dest)
        return;

    QLineF line(mapFromItem(source, 0, 0), mapFromItem(dest, 0, 0));
    qreal length = line.length();

    prepareGeometryChange();

    if (length > qreal(20.)) {
        QPointF edgeOffset((line.dx() * 35) / length, (line.dy() * 35) / length);
        sourcePoint = line.p1() + edgeOffset;
        destPoint = line.p2() - edgeOffset;
    } else {
        sourcePoint = destPoint = line.p1();
    }
}

QRectF Edge::boundingRect() const
{
    if (!source || !dest)
        return QRectF();

    qreal penWidth = 4;
    qreal extra = (penWidth + arrowSize) / 2.0;

    return QRectF(sourcePoint, QSizeF(destPoint.x() - sourcePoint.x(),
                                      destPoint.y() - sourcePoint.y()))
        .normalized()
        .adjusted(-extra, -extra, extra, extra);
}

void Edge::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    if (!source || !dest)
        return;

    QLineF line(sourcePoint, destPoint);
    if (qFuzzyCompare(line.length(), qreal(0.)))
        return;

    (*sd) == 0 ? painter->setPen(QPen(Qt::red, 4, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin)) :
              (*sd) == 1 ? painter->setPen(QPen(Qt::darkGreen, 4, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin)) :
                           painter->setPen(QPen(Qt::darkGray, 4, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));

    painter->drawLine(line);

    // Draw the arrows
    double angle = std::atan2(-line.dy(), line.dx());


    QPointF destArrowP1 = destPoint + QPointF(sin(angle - M_PI / 3) * arrowSize,
                                              cos(angle - M_PI / 3) * arrowSize);
    QPointF destArrowP2 = destPoint + QPointF(sin(angle - M_PI + M_PI / 3) * arrowSize,
                                              cos(angle - M_PI + M_PI / 3) * arrowSize);

    if((*sd) != 2){
        painter->setBrush(Qt::white);
        painter->drawPolygon(QPolygonF() << line.p2() << destArrowP1 << destArrowP2);

        //Tags
        QFont font = painter->font();
        font.setPixelSize(16);
        font.setFamily("Comic Sans");
        font.setWeight(QFont::Bold);


        painter->setFont(font);

        painter->setPen(QPen(QColor(Qt::darkGray).darker(190), 4));
        painter->drawText(boundingRect(),Qt::AlignCenter,QString::fromStdString(tag));
    }

}

void Edge::set_sd(int *p_sd){
    sd = p_sd;
}

int* Edge::get_sd(){
    return sd;
}

string Edge::get_tag(){
    return tag;
}

void Edge::set_tag(string p_tag){
    tag = p_tag;
}
