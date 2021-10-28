#include "graphwidget.h"
#include "vertex.h"
#include "edge_tmp.h"
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
#include <QHBoxLayout>
#include <QAction>
#include <QVariant>
#include <QMenu>
#include <QMenuBar>
#include <QTextEdit>
#include <QMainWindow>
#include <QApplication>
#include <QVariant>
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

using namespace std;

vector<Vertex> vertexes;
QTextEdit *txtMapInfo;
QWidget *centraWidget;
QMainWindow *w;
QMenu *file;
QAction *selectFile;
QString currentFile = "";
QVBoxLayout* mainLayout;
GraphWidget* graphWidget;


void on_actionSeleccionar_Mapa_triggered();

int main(int argc, char *argv[])
{
    //Carga de vertices desde archivo de texto
    vector<Vertex> read_vertexes;



    QApplication a(argc, argv);

    txtMapInfo = new QTextEdit;
    mainLayout = new QVBoxLayout;
    graphWidget = new GraphWidget;
    file = new QMenu;
    selectFile = new QAction;

    //Seteando logger
    graphWidget->logger = txtMapInfo;

    w = new QMainWindow;
    centraWidget = new QWidget;

    selectFile->setIcon(QIcon(":/Imgs/Map_1135px_1195280_42272.ico"));
    selectFile->setText("Seleccionar Archivo (txt)");
    file = w->menuBar()->addMenu("Mapas");
    file->addAction(selectFile);

    //Signal - Slot
    QObject::connect(selectFile, &QAction::triggered, file, on_actionSeleccionar_Mapa_triggered);

    mainLayout->addWidget(graphWidget);
    mainLayout->addWidget(txtMapInfo);

    centraWidget->setLayout(mainLayout);

    w->setCentralWidget(centraWidget);
    w->setMinimumWidth(1000);
    w->setMinimumHeight(900);
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
    vector<Edge_tmp> edges;

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
        //Set vertex
        graphWidget->set_vertexes(&vertexes);
        graphWidget->set_edges(&edges);
        //Update Map
        graphWidget->update();

    }
}
