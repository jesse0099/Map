#include "graphwidget.h"
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

using namespace std;
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
    QApplication a(argc, argv);

    txtMapInfo = new QTextEdit;
    mainLayout = new QVBoxLayout;
    graphWidget = new GraphWidget;
    file = new QMenu;
    selectFile = new QAction;

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
    w->setMinimumHeight(600);
    w->show();
    return a.exec();

}

#pragma region UIFunVariables

#pragma region Edge

class Edge
{
public:
    Edge();
    ~Edge();
    string from;
    string to;
    int weight;
    bool type;

private:

};

Edge::Edge() {}
Edge::~Edge() {}

#pragma endregion

vector<QString> vertexes;
vector<Edge> edges;

#pragma endregion

#pragma region File Methods

QString convToQString(string value) {
    return QString::fromStdString(value);
}

void clearAll() {

    vertexes.clear();
    edges.clear();
}

Edge buildEdge(QString value) {

    Edge newEdge;
    /* Valores de Q string a string*/
    std::string strValues = value.toStdString();
    /*stringstream de los valores*/
    std::stringstream ssValues(strValues);
    /*Valores a guardar*/
    std::vector<string> edgeValues;
    /*valores a tomar*/
    std::string edgeValue = "";


    while (std::getline(ssValues, edgeValue, ','))
    {
        edgeValues.push_back(edgeValue);
    }
    if (edgeValues.size() > 3) {

        newEdge.from = edgeValues[0];
        newEdge.to = edgeValues[1];
        newEdge.weight = stoi(edgeValues[2]);
        if (edgeValues[3] == "true")
        {
            newEdge.type = true;
        }
        else {
            newEdge.type = false;
        }

    }

    return newEdge;
}

#pragma endregion

void on_actionSeleccionar_Mapa_triggered()
{
    QString filename = QFileDialog::getOpenFileName(w, "Open File");
    QFile file(filename);
    currentFile = filename;

    if (!file.open(QIODevice::ReadOnly | QFile::Text)) {
        QMessageBox::warning(w, "Warning", "Something went wrong: " + file.errorString());
    }
    else {
        //w->setWindowTitle(file.fileName());
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
                vertexes.push_back(value);
            }
            else
            {
                if (value != "edges") {
                    Edge newEdge = buildEdge(value);
                    edges.push_back(newEdge);
                }
            }

        }

        for (QString item : vertexes)
        {
            final += item;
        }

        for (Edge edge : edges)
        {
            QString from = QString::fromStdString(edge.from);
            QString to = QString::fromStdString(edge.to);
            QString weight = QString::fromStdString(to_string(edge.weight));
            QString type = "";
            if (edge.type)
            {
                type = "true";
            }
            else
            {
                type = "false";
            }
            QString edgeFinal = from + "," + to + "," + weight + "," + type;
            final += edgeFinal;
        }



        txtMapInfo->setText(final);
        file.close();
    }
}
