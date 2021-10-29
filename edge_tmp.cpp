#include "edge_tmp.h"
#include <sstream>

Edge_tmp::Edge_tmp() {}

Edge_tmp::~Edge_tmp() {}

QString Edge_tmp::convToQString(string value) {
    return QString::fromStdString(value);
}

Edge_tmp Edge_tmp::buildEdge(QString value) {
    Edge_tmp newEdge;
    // Valores de Q string a string
    string strValues = value.toStdString();
    //stringstream de los valores
    stringstream ssValues(strValues);
    //Valores a guardar
    vector<string> edgeValues;
    //valores a tomar
    string edgeValue = "";


    while (std::getline(ssValues, edgeValue, ','))
    {
        edgeValues.push_back(edgeValue);
    }
    if (edgeValues.size() > 4) {

        newEdge.from = edgeValues[0];
        newEdge.to = edgeValues[1];
        newEdge.weight = stoi(edgeValues[2]);
        newEdge.tag = edgeValues[4];

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

