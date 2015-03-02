#include "objfilereader.h"
#include <QDebug>

ObjFileReader::ObjFileReader()
{
}

TriangleMesh * ObjFileReader::readObjFile(QString filename, bool *success)
{
    std::ifstream infile;
    infile.open(filename.toStdString().c_str());
    *success = true;
    if (!infile.is_open())
    {
        *success = false;
        return NULL;
    }

    TriangleMesh * triangleMesh = new TriangleMesh();
    std::string line;
    std::vector<std::string> tokens;
    std::vector<std::string> faceTokens;
    QVector3D max;
    double maxLength = 0;
    double tempLength;
    QVector3D temp;
    while (std::getline(infile, line))
    {
        if (line.size() <= 0)
        {
            continue;
        }
        if (line[0] == '\n')
        {
            continue;
        }

        tokens = split(line, ' ');

//        if (tokens.size() < 4)
//        {
//            *success = false;
//            qDebug() << QByteArray(line.c_str());
//            delete triangleMesh;
//            return NULL;
//        }

        if (tokens[0] == "v")
        {
            triangleMesh->vertices.push_back(QByteArray(tokens[1].c_str()).toFloat());
            triangleMesh->vertices.push_back(QByteArray(tokens[2].c_str()).toFloat());
            triangleMesh->vertices.push_back(QByteArray(tokens[3].c_str()).toFloat());
            temp = QVector3D(QByteArray(tokens[1].c_str()).toFloat(), QByteArray(tokens[2].c_str()).toFloat(), QByteArray(tokens[3].c_str()).toFloat());
            tempLength = temp.length();
            qDebug() << tokens[0].c_str();

            if (tempLength > maxLength)
            {
                max = temp;
                maxLength = tempLength;
            }
        } else if (tokens[0] == "f")
        {
            faceTokens = split(tokens[1], '/');
            triangleMesh->indices.push_back(QByteArray(faceTokens[0].c_str()).toUShort() - 1);
            triangleMesh->normalIndices.push_back(QByteArray(faceTokens[1].c_str()).toUShort() - 1);
            faceTokens = split(tokens[2], '/');
            triangleMesh->indices.push_back(QByteArray(faceTokens[0].c_str()).toUShort() - 1);
            triangleMesh->normalIndices.push_back(QByteArray(faceTokens[1].c_str()).toUShort() - 1);
            faceTokens = split(tokens[3], '/');
            triangleMesh->indices.push_back(QByteArray(faceTokens[0].c_str()).toUShort() - 1);
            triangleMesh->normalIndices.push_back(QByteArray(faceTokens[1].c_str()).toUShort() - 1);
        } else if (tokens[0] == "vn"){
            triangleMesh->normalsSet = true;
            triangleMesh->normals.push_back(QByteArray(tokens[1].c_str()).toFloat());
            triangleMesh->normals.push_back(QByteArray(tokens[2].c_str()).toFloat());
            triangleMesh->normals.push_back(QByteArray(tokens[3].c_str()).toFloat());
        } else {
            //pass
        }
    }
//    qDebug() << "Normal indices size: " << normalIndices.size();
//    qDebug() << "Normals size: " << normals
    qDebug() << "Max length" << maxLength;
    triangleMesh->completeGeometry(maxLength + 1);
    return triangleMesh;

}

// Tokenizing strings found from here: http://stackoverflow.com/questions/236129/split-a-string-in-c
std::vector<std::string> & ObjFileReader::split(const std::string &s, char delim, std::vector<std::string> &elems)
{
    std::stringstream ss(s);
    std::string item;
    while (std::getline(ss, item, delim)) {
        elems.push_back(item);
    }
    return elems;
}

std::vector<std::string> ObjFileReader::split(const std::string &s, char delim) {
    std::vector<std::string> elems;
    split(s, delim, elems);
    return elems;
}

