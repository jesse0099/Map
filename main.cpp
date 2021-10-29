#include "graphwidget.h"
#include "vertex.h"
#include "graph.h"
#include "node.h"
#include "edge_tmp.h"
#include "edge.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <unordered_map>
#include <queue>
#include <fstream>
#include <sstream>
#include <QFile>
#include <QFileDialog>
#include <QVBoxLayout>
#include <QPushButton>
#include <QHBoxLayout>
#include <QAction>
#include <QVariant>
#include <QMenu>
#include <QMenuBar>
#include <QTextEdit>
#include <QMainWindow>
#include <QApplication>
#include <QVariant>
#include <QString>
#include <QWidget>
#include <QMessageBox>
#include <QTextStream>
#include <QFile>
#include <QDataStream>
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <unordered_map>
#include <queue>
#include <iterator>
#include "qlabel.h"
#include <QComboBox>

using namespace std;

typedef pair<string, string> str_pair;

vector<Vertex> vertexes;
vector<Edge_tmp> edges;
QTextEdit *txtMapInfo;
QWidget *centraWidget;
QMainWindow *w;
QMenu *file;
QPushButton* btnCalcular;
QPushButton* btnClear;
QLabel* lblTrans;
QComboBox *transportes;
QAction *selectFile;
QAction *calcDijsktra;
QString currentFile = "";
QVBoxLayout* mainLayout;
QVBoxLayout* buttonsLayout;
QHBoxLayout* mapLayout;
GraphWidget* graphWidget;


void on_actionSeleccionar_Mapa_triggered();
void on_btCalcular_pressed();
void on_btnClear_pressed();

int main(int argc, char *argv[])
{
    //Carga de vertices desde archivo de texto
    vector<Vertex> read_vertexes;

    QApplication a(argc, argv);

    btnClear = new QPushButton;
    btnCalcular = new QPushButton;
    txtMapInfo = new QTextEdit;
    /*Label y combo transportes*/
    transportes = new QComboBox;
    lblTrans = new QLabel;
    /*----------------------*/
    mapLayout = new QHBoxLayout;
    mainLayout = new QVBoxLayout;
    buttonsLayout = new QVBoxLayout;
    graphWidget = new GraphWidget;
    file = new QMenu;
    selectFile = new QAction;
    calcDijsktra = new QAction;

    //Seteando logger
    graphWidget->logger = txtMapInfo;

    w = new QMainWindow;
    centraWidget = new QWidget;

    graphWidget->centerOn(0,0);

    btnCalcular->setIcon(QIcon(":/Imgs/back_arrow_14447_.ico"));
    btnCalcular->setToolTip("Ruta más Corta");
    btnCalcular->setFixedHeight(50);
    btnCalcular->setFixedWidth(105);


    btnClear->setIcon(QIcon(":/Imgs/icons8-actualizaciones-disponibles-48.ico"));
    btnClear->setToolTip("Reiniciar Vista");
    btnClear->setFixedHeight(50);
    btnClear->setFixedWidth(105);


    selectFile->setIcon(QIcon(":/Imgs/Map_1135px_1195280_42272.ico"));
    selectFile->setText("Seleccionar Archivo (txt)");
    file = w->menuBar()->addMenu("Mapas");
    file->addAction(selectFile);

    /*label*/
    lblTrans->setText("Transporte: ");
    lblTrans->setContentsMargins(0,0,8,10);
    /*Combobox*/
    transportes->addItem(QIcon(":/Imgs/car_13260.ico"),"Carro");
    transportes->addItem(QIcon(":/Imgs/front-bus_icon-icons.com_72746.ico"),"Autobus");
    transportes->addItem(QIcon(":/Imgs/pedestrianwalking_89238.ico"),"Caminando");
    transportes->addItem(QIcon(":/Imgs/bicycle_bike_4531.ico"),"Bicicleta");

    transportes->setFixedHeight(50);
    transportes->setFixedWidth(105);



    //Signal - Slot SELECT
    QObject::connect(selectFile, &QAction::triggered, file, on_actionSeleccionar_Mapa_triggered);

    //Signal - Slot CALC
    QObject::connect(btnCalcular,&QPushButton::clicked, w, on_btCalcular_pressed);

    //Siganl - Slot CLEAR
    QObject::connect(btnClear,&QPushButton::clicked, w, on_btnClear_pressed);

    buttonsLayout->setSpacing(0);
    buttonsLayout->addWidget(btnCalcular,0,Qt::AlignTop);
    buttonsLayout->addWidget(btnClear,0,Qt::AlignTop);
    buttonsLayout->addWidget(lblTrans,0,Qt::AlignTop);
    buttonsLayout->addWidget(transportes,15,Qt::AlignTop);

    mapLayout->addWidget(graphWidget);
    mapLayout->addLayout(buttonsLayout);


    mainLayout->addLayout(mapLayout);
    mainLayout->addWidget(txtMapInfo);

    centraWidget->setLayout(mainLayout);

    w->setWindowTitle("PathFinder");
    w->setCentralWidget(centraWidget);
    w->setMinimumWidth(1000);
    w->setMinimumHeight(800);
    w->show();
    return a.exec();

}

Vertex build_vertex(QString data){
    Vertex returned;
    string strValues = data.toStdString();
    stringstream ssValues(strValues), coordx_stream, coordy_stream;
    int coordx, coordy;

    /*Valores a guardar*/
    vector<string> vertexValues;
    /*valores a tomar*/
    string vertexValue = "";
    while (getline(ssValues, vertexValue, ','))
        vertexValues.push_back(vertexValue);
    //Posicion 0 = TAG
    //Posicion 1 = x
    //Posicion 2 = y
    coordx_stream = stringstream(vertexValues[1]);
    coordy_stream = stringstream(vertexValues[2]);

    coordx_stream >> coordx;
    coordy_stream >> coordy;

    returned.set_tag(vertexValues[0]);
    returned.set_coords(make_pair(coordx,coordy));

    return returned;
}

void on_actionSeleccionar_Mapa_triggered()
{
    vertexes = vector<Vertex>();
    edges = vector<Edge_tmp>();

    QString filename = QFileDialog::getOpenFileName(w, "Open File");
    QFile file(filename);
    currentFile = filename;

    if (!file.open(QIODevice::ReadOnly | QFile::Text)) {
        QMessageBox::warning(w, "Warning", "Something went wrong: " + file.errorString());
    }
    else {

        QTextStream in (&file);
        QString final = "";
        bool edgesCap = false;

        while (!in.atEnd())
        {
            QString value = in.readLine();

            if (value == "edges")
            {
                edgesCap = true;
            }

            if (!edgesCap)
            {
                Vertex newVertex = build_vertex(value);
                vertexes.push_back(newVertex);
            }
            else
            {
                if (value != "edges") {
                   Edge_tmp newEdge = Edge_tmp();
                   newEdge= newEdge.buildEdge(value);
                   edges.push_back(newEdge);
                }
            }

        }

        txtMapInfo->setText(final);
        file.close();

        //Reset Selected nodes
        GraphWidget::sourceNode = NULL;
        GraphWidget::destNode = NULL;
        GraphWidget::selectecNodesCount =0;

        //Set vertex
        graphWidget->set_vertexes(&vertexes);
        graphWidget->set_edges(&edges);
        //Update Map
        graphWidget->update();

    }
}

void reset_selected_edges(){
    if(graphWidget->get_edges() != NULL){
        //Reset Selected nodes
        for(vector<Edge*>::iterator i = graphWidget->get_edges()->begin(); i< graphWidget->get_edges()->end(); i++){
            int* sd = new int(0);
            (*i)->set_sd(sd);
            (*i)->setZValue(-1);
            (*i)->hide();
            (*i)->show();
        }
    }
}

void on_btCalcular_pressed(){
    if(GraphWidget::sourceNode != NULL && GraphWidget::destNode != NULL){
        //Reset visual de las aristas
        reset_selected_edges();
        string org_vertex = (*GraphWidget::sourceNode).get_vertex()->get_tag();
        string dest_vertex = (*GraphWidget::destNode).get_vertex()->get_tag();

        Graph* local = graphWidget->get_graph();


        vector<wt_pair> path = (*local).hash_shortest_path(org_vertex, dest_vertex);

        /* Agarrar la  distancia total */

        int distanciaT = path[0].first;

        vector<str_pair> edges_path;

        for(unsigned int j = 1; j < (path.size()-1); j++){
            edges_path.push_back(make_pair(path[j].second,path[j+1].second));
        }


        for(vector<Edge*>::iterator i = graphWidget->get_edges()->begin(); i< graphWidget->get_edges()->end(); i++){
            int* sd;
            for(auto& x: edges_path){
                if(x.first == (*i)->sourceNode()->get_vertex()->get_tag() &&
                        x.second == (*i)->destNode()->get_vertex()->get_tag()){
                    sd = new int(1);
                    (*i)->set_sd(sd);
                    (*i)->setZValue(1);
                    (*i)->hide();
                    (*i)->show();
                }
            }

            //Arista descartada
            if((*(*i)->get_sd()) == 0){
                sd = new int(2);
                (*i)->set_sd(sd);
                (*i)->hide();
                (*i)->show();
            }

            //Arista perteneciente al camino mas corto
            if((*(*i)->get_sd()) == 1){
                for(auto edgs : (*i)->destNode()->edges()){
                    if(edgs->destNode()->get_vertex()->get_tag() == (*i)->sourceNode()->get_vertex()->get_tag())
                         edgs->hide();
                }

            }
        }

        /* Mostrar el valor de la velocidad en consola */
           if(distanciaT != 0){
             GraphWidget::predictTime(transportes->currentText().toStdString(),distanciaT);
           }
    }
}

void on_btnClear_pressed(){
    reset_selected_edges();
    if(GraphWidget::sourceNode != NULL && GraphWidget::destNode != NULL){
        GraphWidget::sourceNode->setSelected(false);
        GraphWidget::destNode->setSelected(false);
        GraphWidget::sourceNode = NULL;
        GraphWidget::destNode = NULL;
        GraphWidget::selectecNodesCount = 0 ;
    }
}
