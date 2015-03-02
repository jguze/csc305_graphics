#ifndef OBJFILEREADER_H
#define OBJFILEREADER_H

#include <trianglemesh.h>
#include <fstream>
#include <sstream>

/*
 * Designed to read in obj files and transform them into Triangle Meshes.
 * Works more or less :)
 */
class ObjFileReader
{
public:
    ObjFileReader();

    TriangleMesh * readObjFile(QString filename, bool * success);

private:
    std::vector<std::string> &split(const std::string &s, char delim, std::vector<std::string> &elems);
    std::vector<std::string> split(const std::string &s, char delim);
};

#endif // OBJFILEREADER_H
