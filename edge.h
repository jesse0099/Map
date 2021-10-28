#include <QGraphicsItem>

class Node;


class Edge : public QGraphicsItem
{
public:
    Edge(Node *sourceNode, Node *destNode, bool p_bidir = false);
    Edge();

    Node *sourceNode() const;
    Node *destNode() const;
    int* get_sd();

    void set_sd(int* p_sd);
    void adjust();

    enum { Type = UserType + 2 };
    int type() const override { return Type; }

protected:
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

private:
    Node *source, *dest;
    bool bidir;
    QPointF sourcePoint;
    QPointF destPoint;
    qreal arrowSize = 12;
    int* sd = new int(0);
};
