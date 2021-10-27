#include <QGraphicsView>
#include <QWheelEvent>
#include "graphwidget.h"
#include <node.h>
#include <vertex.h>
#include <edge.h>
#include <edge_tmp.h>
#include <iterator>

GraphWidget::GraphWidget(QWidget *parent, vector<Vertex>* p_vertexes)
    : QGraphicsView(parent)
{
    vertexes = p_vertexes;
    nodes = NULL;
    edges = NULL;
    scene = new QGraphicsScene(this);
    scene->setItemIndexMethod(QGraphicsScene::NoIndex);
    scene->setSceneRect(0, 0, 3000, 2000);
    scene->focusOnTouch();
    setScene(scene);
    setCacheMode(CacheBackground);
    setViewportUpdateMode(BoundingRectViewportUpdate);
    setRenderHint(QPainter::Antialiasing);
    setTransformationAnchor(AnchorUnderMouse);
    scale(qreal(0.8), qreal(0.8));
    setMinimumSize(400, 600);

}

GraphWidget::~GraphWidget(){
    centerNode = NULL;
    vertexes = NULL;
}

void GraphWidget::drawBackground(QPainter *painter, const QRectF &rect)
{
    Q_UNUSED(rect);

    // Shadow
    QRectF sceneRect = this->sceneRect();
    QRectF rightShadow(sceneRect.right(), sceneRect.top() + 5, 5, sceneRect.height());
    QRectF bottomShadow(sceneRect.left() + 5, sceneRect.bottom(), sceneRect.width(), 5);
    if (rightShadow.intersects(rect) || rightShadow.contains(rect))
        painter->fillRect(rightShadow, Qt::darkGray);
    if (bottomShadow.intersects(rect) || bottomShadow.contains(rect))
        painter->fillRect(bottomShadow, Qt::darkGray);

    // Fill
    QLinearGradient gradient(sceneRect.topLeft(), sceneRect.bottomRight());
    gradient.setColorAt(0, Qt::white);
    gradient.setColorAt(1, Qt::lightGray);
    painter->fillRect(rect.intersected(sceneRect), gradient);
    painter->setBrush(Qt::NoBrush);
    painter->drawRect(sceneRect);

    QFont font = painter->font();
    font.setBold(true);
    font.setPointSize(14);
    painter->setFont(font);
    painter->setPen(Qt::lightGray);
    painter->setPen(Qt::black);

}

void GraphWidget::wheelEvent(QWheelEvent *event)
{
    scaleView(pow(2., -event->angleDelta().y() / 240.0));
}

void GraphWidget::scaleView(qreal scaleFactor)
{
    qreal factor = transform().scale(scaleFactor, scaleFactor).mapRect(QRectF(0, 0, 1, 1)).width();
    if (factor < 0.07 || factor > 100)
        return;

    scale(scaleFactor, scaleFactor);
}

void GraphWidget::zoomIn()
{
    scaleView(qreal(1.2));
}

void GraphWidget::zoomOut()
{
    scaleView(1 / qreal(1.2));
}

void GraphWidget::set_vertexes(vector<Vertex>* p_vertexes){
    scene->clear();
    vertexes = NULL;
    nodes = NULL;
    vertexes = p_vertexes;
    nodes = new vector<Node*>();
    for(auto& x: *vertexes){
        Node* tmp = new Node(this,&x);
        tmp->setPos(x.get_coords().first,x.get_coords().second);
        nodes->push_back(tmp);
        scene->addItem(tmp);
    }
}

vector<Vertex>* GraphWidget::get_vertexes(){
    return vertexes;
}

vector<Node*>* GraphWidget::get_nodes(){
    return nodes;
}

void GraphWidget::set_edges(vector<Edge_tmp> *p_edges){
    edges = NULL;
    edges = new vector<Edge*>();
    bool bidir;
    for(vector<Edge_tmp>::iterator i = p_edges->begin(); i< p_edges->end(); i++){
        bidir = (*i).type;
        auto source_node = find_if(nodes->begin(), nodes->end(), [&i](Node* obj) {return obj->get_vertex()->get_tag() == (*i).from; });
        auto dest_node = find_if(nodes->begin(), nodes->end(), [&i](Node* obj2) {return obj2->get_vertex()->get_tag() == (*i).to; });
        Edge* tmp = new Edge((*source_node),(*dest_node),bidir);
        (**source_node).addEdge(tmp);
        (*edges).push_back(tmp);
        scene->addItem(tmp);
    }
}

void GraphWidget::set_nodes(vector<Node*> *p_nodes){
    nodes = p_nodes;
}
