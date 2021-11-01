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
#include <QScrollBar>


using namespace std;

typedef pair<string, string> str_pair;
typedef pair<int, string> w_pair;

int* sd;
int rotation_angle = 0;
vector<Vertex> *vertexes;
vector<Edge_tmp> *edges;
QTextEdit *txtMapInfo;
QWidget *centraWidget;
QFont *font;
QFont *mainWindowfont;
QMainWindow *w;
QMenu *file;
QPushButton* btnCalcular;
QPushButton* btnClear;
QPushButton* btnRotate;
QLabel* lblTrans;
QComboBox *transportes;
QAction *selectFile;
QAction *calcDijsktra;
QVBoxLayout* mainLayout;
QVBoxLayout* buttonsLayout;
QHBoxLayout* mapLayout;
GraphWidget* graphWidget;


void on_actionSeleccionar_Mapa_triggered();
void on_btCalcular_pressed();
void on_btnClear_pressed();
void on_btnRotate_pressed();

int main(int argc, char *argv[])
{

    QApplication a(argc, argv);

    font = new QFont;
    mainWindowfont = new QFont;
    btnClear = new QPushButton;
    btnCalcular = new QPushButton;
    btnRotate = new QPushButton;
    txtMapInfo = new QTextEdit;

    /*Label y combo transportes*/
    transportes = new QComboBox;
    lblTrans = new QLabel;

    /*Layouts y ventanas */
    mapLayout = new QHBoxLayout;
    mainLayout = new QVBoxLayout;
    buttonsLayout = new QVBoxLayout;
    graphWidget = new GraphWidget;
    centraWidget = new QWidget;
    w = new QMainWindow;

    /*Menues y acciones*/
    file = new QMenu;
    selectFile = new QAction;
    calcDijsktra = new QAction;

    //Fuentes
    font->setPixelSize(13);
    font->setFamily("Comic Sans");
    font->setWeight(QFont::Bold);

    mainWindowfont->setPixelSize(13);
    mainWindowfont->setFamily("Comic Sans");
    mainWindowfont->setWeight(QFont::Normal);


    //Seteando logger y boton de calculo
    graphWidget->logger = txtMapInfo;
    graphWidget->calc = btnCalcular;

    txtMapInfo->setFixedHeight(150);
    txtMapInfo->setReadOnly(true);
    txtMapInfo->setTextColor(QColor(Qt::darkGray).darker(170));
    txtMapInfo->setFont(*font);


    graphWidget->centerOn(0,0);

    btnCalcular->setIcon(QIcon(":/Imgs/back_arrow_14447_.ico"));
    btnCalcular->setToolTip("Ruta más Corta");
    btnCalcular->setFixedHeight(50);
    btnCalcular->setFixedWidth(105);

    btnClear->setIcon(QIcon(":/Imgs/icons8-actualizaciones-disponibles-48.ico"));
    btnClear->setToolTip("Reiniciar Vista");
    btnClear->setFixedHeight(50);
    btnClear->setFixedWidth(105);

    btnRotate->setIcon(QIcon(":/Imgs/rotate.ico"));
    btnRotate->setToolTip("Rotar Vista (90)");
    btnRotate->setFixedHeight(50);
    btnRotate->setFixedWidth(105);

    selectFile->setIcon(QIcon(":/Imgs/Map_1135px_1195280_42272.ico"));
    selectFile->setText("Seleccionar Archivo (txt)");

    file = w->menuBar()->addMenu("Mapas");
    file->addAction(selectFile);

    /*label*/
    lblTrans->setFont(*font);
    lblTrans->setStyleSheet("QLabel { color : gray; }");
    lblTrans->setText("Transporte: ");
    lblTrans->setContentsMargins(0,8,0,10);

    /*Combobox*/
    transportes->addItem(QIcon(":/Imgs/car_13260.ico"),"Carro");
    transportes->addItem(QIcon(":/Imgs/front-bus_icon-icons.com_72746.ico"),"Autobus");
    transportes->addItem(QIcon(":/Imgs/pedestrianwalking_89238.ico"),"Caminando");
    transportes->addItem(QIcon(":/Imgs/bicycle_bike_4531.ico"),"Bicicleta");

    transportes->setFixedHeight(50);
    transportes->setFixedWidth(105);

    buttonsLayout->setSpacing(0);
    buttonsLayout->addWidget(btnCalcular,0,Qt::AlignTop);
    buttonsLayout->addWidget(btnClear,0,Qt::AlignTop);
    buttonsLayout->addWidget(btnRotate,0,Qt::AlignTop);
    buttonsLayout->addWidget(lblTrans,0,Qt::AlignTop);
    buttonsLayout->addWidget(transportes,15,Qt::AlignTop);

    mapLayout->addWidget(graphWidget);
    mapLayout->addLayout(buttonsLayout);

    mainLayout->addLayout(mapLayout);
    mainLayout->addWidget(txtMapInfo);

    centraWidget->setLayout(mainLayout);

    //Signal - Slot SELECT
    QObject::connect(selectFile, &QAction::triggered, file, on_actionSeleccionar_Mapa_triggered);

    //Signal - Slot CALC
    QObject::connect(btnCalcular,&QPushButton::clicked, w, on_btCalcular_pressed);

    //Signal - Slot CLEAR
    QObject::connect(btnClear,&QPushButton::clicked, w, on_btnClear_pressed);

    //Signal - Slot ROTATE
    QObject::connect(btnRotate,&QPushButton::clicked,w,on_btnRotate_pressed);

    w->setWindowTitle("PathFinder");
    w->setCentralWidget(centraWidget);
    w->setMinimumWidth(1000);
    w->setMinimumHeight(800);
    w->show();

    a.setFont(*mainWindowfont);
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

void reset_selected_edges(){
    if(graphWidget->get_edges() != NULL){
        for(vector<Edge*>::iterator i = graphWidget->get_edges()->begin(); i< graphWidget->get_edges()->end(); i++){
            int* sd = new int(0);
            (*i)->set_sd(sd);
            (*i)->setZValue(-1);
            (*i)->hide();
            (*i)->show();
        }
    }
}

unordered_map<string, vector<vector<wt_pair>>> possible_paths(string org_vertex, string dest_vertex){
    Graph* local = graphWidget->get_graph();
    //Calculo de posibles caminos
    (*local).get_all_paths(org_vertex,dest_vertex);
    //Posibles caminos desde el vertice origen
    return (*local).get_vertexes_list()[(*local).vertex_index(org_vertex)].get_possible_paths();
}

vector<str_pair> possible_paths_key_pairs(unordered_map<string, vector<vector<wt_pair>>> p_possible_paths, string dest_vertex){
    vector<str_pair> edges_possible_paths;
    //Caminos posibles (Pares de llaves)
    for(vector<vector<pair<int,string>>>::iterator x = p_possible_paths.at(dest_vertex).begin() ;x < p_possible_paths.at(dest_vertex).end(); x++){
        for(vector<pair<int,string>>::iterator i = x->begin(); i < x->end()-1; i++){
            if((*i).second != "" && (*(i+1)).second != "")
                edges_possible_paths.push_back(make_pair((*i).second,(*(i+1)).second));
        }
    }
    return edges_possible_paths;
}

vector<wt_pair> shortest_path(string org_vertex, string dest_vertex){
    Graph* local = graphWidget->get_graph();
    return (*local).hash_shortest_path(org_vertex, dest_vertex);
}

vector<str_pair> shortest_path_key_pairs(vector<wt_pair> p_shortest_path){
    vector<str_pair> edges_path;
    //Pares de Llaves para  Camino Mas corto
    for(unsigned int j = 1; j < (p_shortest_path.size()-1); j++){
        edges_path.push_back(make_pair(p_shortest_path[j].second,p_shortest_path[j+1].second));
    }
    return edges_path;
}

string coordinate_translation(Node* sourceNode, Node* destNode){
    string coord;
    auto sinalpha = atan2((sourceNode->pos().y() - destNode->pos().y()), (destNode->pos().x() - sourceNode->pos().x())) * (180.0 / M_PI);
    //Entre 1 y 179, pasando por 90 NORTE
    if(sinalpha > 0 && sinalpha < 180 ){
        if(sinalpha == 90)
            coord = "Norte";
        if(sinalpha < 90)
            coord = "Noreste";
        if(sinalpha > 90)
            coord = "Noroeste";

    }else if(sinalpha < 0){
        if(sinalpha == -90)
            coord = "Sur";
         if(sinalpha > -90 )
             coord = "Sureste";
         if(sinalpha < -90)
             coord = "Suroeste";
    }else{
        if(sinalpha == 0)
            coord = "Este";
        else
            coord = "Oeste";
    }
    return coord;
}

void shortest_path_representation(vector<str_pair> edges_path, vector<string> *literal_path_vector){
    string from, to, coord,literal_path;
    int edges_path_idx = 0;
    //Marcado visual de camino mas corto
    for(vector<Edge*>::iterator i = graphWidget->get_edges()->begin(); i< graphWidget->get_edges()->end(); i++){
        edges_path_idx = 0;
        for(auto &x: edges_path){
            if(x.first == (*i)->sourceNode()->get_vertex()->get_tag() &&
                    x.second == (*i)->destNode()->get_vertex()->get_tag()){
                sd = new int(1);
                (*i)->set_sd(sd);
                (*i)->setZValue(1);
                (*i)->hide();
                (*i)->show();

                from =(*i)->sourceNode()->get_vertex()->get_tag();
                to = (*i)->destNode()->get_vertex()->get_tag();
                coord = coordinate_translation((*i)->sourceNode(),(*i)->destNode());

                literal_path = " Desde "+from + ", "+to_string((*i)->peso)+" (km) al "+ coord + " hacia " + to + ". " ;
                literal_path_vector->at(edges_path_idx) = literal_path;

            }
            edges_path_idx++;
        }

        //Arista descartada
        if((*(*i)->get_sd()) == 0){
            sd = new int(2);
            (*i)->set_sd(sd);
            (*i)->setZValue(-1);
            (*i)->hide();
            (*i)->show();
        }

        //Arista perteneciente al camino mas corto
        if((*(*i)->get_sd()) == 1){
            //Arista paralela bidireccional
            for(auto edgs : (*i)->destNode()->edges()){
                if(edgs->destNode()->get_vertex()->get_tag() == (*i)->sourceNode()->get_vertex()->get_tag())
                     edgs->hide();
            }

        }
    }
}

void possible_paths_representation(vector<str_pair> edges_possible_paths){
    //Posible camino
    for(vector<Edge*>::iterator i = graphWidget->get_edges()->begin(); i< graphWidget->get_edges()->end(); i++){
        for(auto& x: edges_possible_paths){
            if(x.first == (*i)->sourceNode()->get_vertex()->get_tag() &&
                    x.second == (*i)->destNode()->get_vertex()->get_tag() && (*(*i)->get_sd()) != 1){
                sd = new int(0);
                (*i)->setZValue(1);
                (*i)->set_sd(sd);
                (*i)->hide();
                (*i)->show();
            }
        }
    }

}

void on_actionSeleccionar_Mapa_triggered()
{
    try {
        reset_selected_edges();

        if(GraphWidget::sourceNode != NULL && GraphWidget::destNode != NULL){
            GraphWidget::sourceNode->setSelected(false);
            GraphWidget::destNode->setSelected(false);
            GraphWidget::sourceNode = NULL;
            GraphWidget::destNode = NULL;
            GraphWidget::selectecNodesCount = 0 ;
        }

        vertexes = new  vector<Vertex>();
        edges = new vector<Edge_tmp>();

        //bug
        QString filename = QFileDialog::getOpenFileName(w, "Open File");
        QFile file(filename);


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
                    vertexes->push_back(newVertex);
                }
                else
                {
                    if (value != "edges") {
                       Edge_tmp newEdge = Edge_tmp();
                       newEdge= newEdge.buildEdge(value);
                       edges->push_back(newEdge);
                    }
                }

            }

            txtMapInfo->setText(final);
            file.close();

            //Set vertex
            graphWidget->set_vertexes(vertexes);
            graphWidget->set_edges(edges);

            //Update Map
            graphWidget->update();

        }
    }  catch (exception &e) {
        string exception = (e.what());
        txtMapInfo->setText(txtMapInfo->toPlainText()+QString::fromStdString(exception+"\n"));
    }

}

void on_btCalcular_pressed(){
    if(GraphWidget::sourceNode != NULL && GraphWidget::destNode != NULL){
        //Reset visual de las aristas
        reset_selected_edges();

        int distanciaT;
        string literal_path;
        string org_vertex = (*GraphWidget::sourceNode).get_vertex()->get_tag();
        string dest_vertex = (*GraphWidget::destNode).get_vertex()->get_tag();
        vector<wt_pair> path;
        vector<str_pair> edges_path;
        vector<str_pair> edges_possible_paths;
        vector<string> literal_path_vector;

        //Calculo de camino mas corto
        path = shortest_path(org_vertex, dest_vertex);

        //Posibles Caminos (Pares de llaves)
        edges_possible_paths = possible_paths_key_pairs( possible_paths(org_vertex, dest_vertex), dest_vertex);

        //Camino mas corto (Pares de llaves)
        edges_path = shortest_path_key_pairs(path);

        //Distancia total del recorrido
        distanciaT = path[0].first;

        //Inicializacion del vector con la direccion en palabras
        literal_path_vector =  vector<string>(edges_path.size(),"");

        //Marcado visual de camino mas corto
        shortest_path_representation(edges_path, &literal_path_vector);

        //Marcado visual de los posibles caminos
        possible_paths_representation(edges_possible_paths);

        //Armando direccion del camino mas corto
        literal_path = "Camino más corto: -> ";
        for(auto &path : literal_path_vector){
            literal_path += path;
        }
        literal_path += "\n";

        // Mostrar el valor de tiempo estimado en la consola
        if(distanciaT != 0){
             GraphWidget::predictTime(transportes->currentText().toStdString(), distanciaT);
        }

        //Mostrar direccion del camino mas corto
        GraphWidget::log(literal_path);
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

void on_btnRotate_pressed(){
    graphWidget->rotate(90);
}
