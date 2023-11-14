/*******************************************************************************************
*
*   raylib game template
*
*   <Game title>
*   <Game description>
*
*   This game has been created using raylib (www.raylib.com)
*   raylib is licensed under an unmodified zlib/libpng license (View raylib.h for details)
*
*   Copyright (c) 2021 Ramon Santamaria (@raysan5)
*
********************************************************************************************/
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>
#include <vector>
#include <filesystem>
#include <cmath>
#include "raylib.h"
#include "tinyfiledialogs.h"
#include "NTBL.h"
#include "rlgl.h"

uint16_t         swap_endian_ushort(uint16_t value) { return ((((value) >> 8) & 0xff) | (((value) & 0xff) << 8)); }
int16_t          swap_endian_sshort(int16_t value) { return (((value >> 8) & 0xFF) | ((value & 0xFF) << 8)); }
uint32_t         swap_endian_uint(uint32_t value) { return ((((value) & 0xff000000) >> 24) | (((value) & 0x00ff0000) >> 8) | (((value) & 0x0000ff00) << 8) | (((value) & 0x000000ff) << 24)); }
int32_t          swap_endian_sint(int32_t value) { return ((((value) & 0xff000000) >> 24) | (((value) & 0x00ff0000) >> 8) | (((value) & 0x0000ff00) << 8) | (((value) & 0x000000ff) << 24)); }

uint16_t PointCount = 0;
uint16_t FaceCount = 0;
uint16_t Ncnt = 0;

FXFACE  FaceList[25000] = {0};
Mesh    MeshList[25000] = {0};

Model   ModelList[25000][200] = {0};
Vector3 PointList[25000][200] = {0};
Texture TextureList[200] = {0};
Texture2D texture;
std::vector<std::string> MatNameList;
unsigned char    NormalList[25000][200] = {0};

Mesh Quad2Mesh(uint16_t PT1,uint16_t PT2, uint16_t PT3, uint16_t PT4, uint16_t Flip, uint16_t frame) {
    Mesh mesh = { 0 };
    mesh.triangleCount = 2;
    mesh.vertexCount = mesh.triangleCount * 3;
    mesh.vertices = (float*)MemAlloc(mesh.vertexCount * 3 * sizeof(float));    // 3 vertices, 3 coordinates each (x, y, z)
    mesh.texcoords = (float*)MemAlloc(mesh.vertexCount * 2 * sizeof(float));   // 3 vertices, 2 coordinates each (x, y)
    mesh.normals = (float*)MemAlloc(mesh.vertexCount * 3 * sizeof(float));     // 3 vertices, 3 coordinates each (x, y, z)

    mesh.vertices[0] = PointList[PT1][frame].x;
    mesh.vertices[1] = PointList[PT1][frame].y;
    mesh.vertices[2] = PointList[PT1][frame].z;
    mesh.normals[0] = 0;
    mesh.normals[1] = 1;
    mesh.normals[2] = 0;


    mesh.vertices[3] = PointList[PT2][frame].x;
    mesh.vertices[4] = PointList[PT2][frame].y;
    mesh.vertices[5] = PointList[PT2][frame].z;
    mesh.normals[3] = 0;
    mesh.normals[4] = 1;
    mesh.normals[5] = 0;


    mesh.vertices[6] = PointList[PT3][frame].x;
    mesh.vertices[7] = PointList[PT3][frame].y;
    mesh.vertices[8] = PointList[PT3][frame].z;
    mesh.normals[6] = 0;
    mesh.normals[7] = 1;
    mesh.normals[8] = 0;


     mesh.vertices[9] = PointList[PT3][frame].x;
    mesh.vertices[10] = PointList[PT3][frame].y;
    mesh.vertices[11] = PointList[PT3][frame].z;
    mesh.normals[9] = 0;
    mesh.normals[10] = 1;
    mesh.normals[11] = 0;


    mesh.vertices[12] = PointList[PT4][frame].x;
    mesh.vertices[13] = PointList[PT4][frame].y;
    mesh.vertices[14] = PointList[PT4][frame].z;
    mesh.normals[12] = 0;
    mesh.normals[13] = 1;
    mesh.normals[14] = 0;


    mesh.vertices[15] = PointList[PT1][frame].x;
    mesh.vertices[16] = PointList[PT1][frame].y;
    mesh.vertices[17] = PointList[PT1][frame].z;
    mesh.normals[15] = 0;
    mesh.normals[16] = 1;
    mesh.normals[17] = 0;

    if (Flip == 0) {
        mesh.texcoords[0] = 0;
        mesh.texcoords[1] = 1;

        mesh.texcoords[2] = 1.0f;
        mesh.texcoords[3] = 1.0f;

        mesh.texcoords[4] = 1.0f;
        mesh.texcoords[5] = 0.0f;

        mesh.texcoords[6] = 1;
        mesh.texcoords[7] = 0;

        mesh.texcoords[8] = 0;
        mesh.texcoords[9] = 0.0f;

        mesh.texcoords[10] = 0.0f;
        mesh.texcoords[11] = 1.0f;
    }

    if (Flip == 1) {

        mesh.texcoords[0] = 1;
        mesh.texcoords[1] = 1;

        mesh.texcoords[2] = 0.0f;
        mesh.texcoords[3] = 1.0f;

        mesh.texcoords[4] = 0.0f;
        mesh.texcoords[5] = 0.0f;

        mesh.texcoords[6] = 0;
        mesh.texcoords[7] = 0;

        mesh.texcoords[8] = 1;
        mesh.texcoords[9] = 0.0f;

        mesh.texcoords[10] = 1.0f;
        mesh.texcoords[11] = 1.0f;

    }

    if (Flip == 2) {

        mesh.texcoords[0] = 0;
        mesh.texcoords[1] = 0;

        mesh.texcoords[2] = 1.0f;
        mesh.texcoords[3] = 0.0f;

        mesh.texcoords[4] = 1.0f;
        mesh.texcoords[5] = 1.0f;

        mesh.texcoords[6] = 1;
        mesh.texcoords[7] = 1;

        mesh.texcoords[8] = 0;
        mesh.texcoords[9] = 1.0f;

        mesh.texcoords[10] = 0.0f;
        mesh.texcoords[11] = 0.0f;

    }

    if (Flip == 3) {

        mesh.texcoords[0] = 1;
        mesh.texcoords[1] = 0;

        mesh.texcoords[2] = 0.0f;
        mesh.texcoords[3] = 0.0f;

        mesh.texcoords[4] = 0.0f;
        mesh.texcoords[5] = 1.0f;

        mesh.texcoords[6] = 0;
        mesh.texcoords[7] = 1;

        mesh.texcoords[8] = 1;
        mesh.texcoords[9] = 1.0f;

        mesh.texcoords[10] = 1.0f;
        mesh.texcoords[11] = 0.0f;

    }
    // Upload mesh data from CPU (RAM) to GPU (VRAM) memory
    UploadMesh(&mesh, true);
    return (mesh);

};

typedef struct {
    std::string TexName;
    std::string MTLName;
     short id;
     char seen = 0;
} NameUndID;

NameUndID MTLNameList[2500];

int curTexID = -1;
int totalTex = -1;
int MTLLISTID = -1;



void LoadOBJ2Init(std::string filename, uint16_t frame) {


    Vector2     VTList[25000];
    unsigned char NormalUnsorted[25000] = { 0 };


    std::filesystem::path FNMTL(filename);

    FNMTL.replace_extension(".mtl");

    std::cout << FNMTL.string() << std::endl;

    std::fstream MTLIn(FNMTL.string(), std::ios_base::in);
     
    std::string MTLLine;


    while (std::getline(MTLIn, MTLLine)) {
        std::string s;
        std::istringstream iss(MTLLine);

        iss >> s;
         
        if (MTLLine.substr(0, 2) == "ne") {
         
            MTLLISTID += 1;

            std::string name;
            iss >> name;

            MTLNameList[MTLLISTID].MTLName = name;

            std::cout << "MTL NAME : " << name << std::endl;

        }

        if (MTLLine.substr(0, 2) == "ma") {
            std::string texname;

            iss >> texname;

            std::filesystem::path TexPath2Name(texname);

            MTLNameList[MTLLISTID].TexName = TexPath2Name.filename().string();
            std::cout << "TEX NAME : " << MTLNameList[MTLLISTID].TexName  << " " << MTLLISTID << std::endl;

        }
    }
    MTLIn.close();
    

    std::fstream ModelIn(filename, std::ios_base::in);
    std::string line;

    int vtCount = 0;
    while (std::getline(ModelIn, line)) {
         std::string s;
         std::istringstream iss(line);

        iss >> s;

        if (line.substr(0, 2) == "v ") {

            iss >> PointList[PointCount][frame].x >> PointList[PointCount][frame].y >> PointList[PointCount][frame].z;
            PointCount += 1;
        }
        if (line.substr(0, 2) == "vn") {
            VECTOR TestNormal;
            iss >> TestNormal[0] >> TestNormal[1] >> TestNormal[2];
            float CurrentLowest = 5000;
            int lowestNormalID;

            for (int i = 0; i < 162; i++) {
                float xsqr = (TestNormal[0] - FNORMS[i][0]) * (TestNormal[0] - FNORMS[i][0]);
                float ysqr = (TestNormal[1] - FNORMS[i][1]) * (TestNormal[1] - FNORMS[i][1]);
                float zsqr = (TestNormal[2] - FNORMS[i][2]) * (TestNormal[2] - FNORMS[i][2]);
                float dotProd = sqrt(xsqr + ysqr + zsqr);

                if (dotProd < CurrentLowest) {
                    CurrentLowest = dotProd;
                    lowestNormalID = i;
                };

            }

            NormalUnsorted[Ncnt] = lowestNormalID;

            std::cout << " Normal " << TestNormal[0] << " " << TestNormal[1] << " " << TestNormal[2] << "  is most similar to FNORM ID : " << lowestNormalID << " " << FNORMS[lowestNormalID][0] << " " << FNORMS[lowestNormalID][1] << " " << FNORMS[lowestNormalID][2] << std::endl;
            std::cout << "Dot Product is " << CurrentLowest << std::endl;
            Ncnt += 1;
        }


        if (line.substr(0, 2) == "vt") {
            float vtx, vty;
            iss >> vtx >> vty;
            VTList[vtCount].x = vtx;
            VTList[vtCount].y = vty;

            vtCount += 1;
        }

        if (line.substr(0, 2) == "us") {
            std::string name;
            iss >> name;
            bool isNew = true;
            
            for (int i = 0; i < MTLLISTID+1; i++) {
                if (name == MTLNameList[i].MTLName) {
                    if (MTLNameList[i].seen == 0) {
                        MTLNameList[i].seen = 1;
                        totalTex += 1;
                        curTexID = totalTex;
                        MTLNameList[i].id = totalTex;
                        std::cout << "TEXFOUND " << name << " " << std::endl;
                    }
                    else {
                        curTexID = MTLNameList[i].id;
                    }

                }
            }

        }

        if (line.substr(0, 2) == "f " && frame == 0) {
            if (std::count(line.begin(), line.end(), ' ') == 4) {
               // std::cout << " its a quad" << std::endl;
                std::string point;
                iss >> point;
                std::replace(point.begin(), point.end(), '/', ' ');
                std::istringstream pointStream(point);

                int vi[4];
                int vt[4];
                int vn[4];
               

                pointStream >> vi[0] >> vt[0] >> vn[0];

                iss >> point;
                std::replace(point.begin(), point.end(), '/', ' ');
                pointStream = std::istringstream(point);
                pointStream >> vi[1] >> vt[1] >> vn[1];


                iss >> point;
                std::replace(point.begin(), point.end(), '/', ' ');
                pointStream = std::istringstream(point);
                pointStream >> vi[2] >> vt[2] >> vn[2];


                iss >> point;
                std::replace(point.begin(), point.end(), '/', ' ');
                pointStream = std::istringstream(point);
                pointStream >> vi[3] >> vt[3] >> vn[3];


                uint16_t direction = 0;


              //  std::cout << "VT1 " << VTList[vt[0] - 1].x << " " << VTList[vt[0]].y << " VT2 " << VTList[vt[1] - 1].x << " " << VTList[vt[1] - 1].y << " VT3 " << VTList[vt[2] - 1].x << " " << VTList[vt[2] - 1].y << " VT4 " << VTList[vt[3] - 1].x << " " << VTList[vt[3] - 1].y << std::endl;
                if (VTList[vt[0] - 1].x == 0 && VTList[vt[0] - 1].y == 0 &&
                    VTList[vt[1] - 1].x == 1 && VTList[vt[1] - 1].y == 0 &&
                    VTList[vt[2] - 1].x == 1 && VTList[vt[2] - 1].y == 1 &&
                    VTList[vt[3] - 1].x == 0 && VTList[vt[3] - 1].y == 1)
                {
                    FaceList[FaceCount].pt1 = vi[0] - 1;
                    FaceList[FaceCount].pt2 = vi[1] - 1;
                    FaceList[FaceCount].pt3 = vi[2] - 1;
                    FaceList[FaceCount].pt4 = vi[3] - 1;
                    direction = 0;
                   // std::cout << FaceCount << " is Upright! URA!!!" << std::endl;
                }
                else if (VTList[vt[0] - 1].x == 1 && VTList[vt[0] - 1].y == 0 &&
                    VTList[vt[1] - 1].x == 0 && VTList[vt[1] - 1].y == 0 &&
                    VTList[vt[2] - 1].x == 0 && VTList[vt[2] - 1].y == 1 &&
                    VTList[vt[3] - 1].x == 1 && VTList[vt[3] - 1].y == 1)
                {
                    FaceList[FaceCount].pt1 = vi[0] - 1;
                    FaceList[FaceCount].pt2 = vi[1] - 1;
                    FaceList[FaceCount].pt3 = vi[2] - 1;
                    FaceList[FaceCount].pt4 = vi[3] - 1;
                    direction = 1;
                   // std::cout << FaceCount << " is X Flipped! URA!!!" << std::endl;
                }
                else  if (VTList[vt[0] - 1].x == 0 && VTList[vt[0] - 1].y == 1 &&
                    VTList[vt[1] - 1].x == 1 && VTList[vt[1] - 1].y == 1 &&
                    VTList[vt[2] - 1].x == 1 && VTList[vt[2] - 1].y == 0 &&
                    VTList[vt[3] - 1].x == 0 && VTList[vt[3] - 1].y == 0)
                {
                    FaceList[FaceCount].pt1 = vi[0] - 1;
                    FaceList[FaceCount].pt2 = vi[1] - 1;
                    FaceList[FaceCount].pt3 = vi[2] - 1;
                    FaceList[FaceCount].pt4 = vi[3] - 1;
                    direction = 2;
                   // std::cout << FaceCount << " is Y Flipped! URA!!!" << std::endl;
                }
                else if (VTList[vt[0] - 1].x == 1 && VTList[vt[0] - 1].y == 1 &&
                    VTList[vt[1] - 1].x == 0 && VTList[vt[1] - 1].y == 1 &&
                    VTList[vt[2] - 1].x == 0 && VTList[vt[2] - 1].y == 0 &&
                    VTList[vt[3] - 1].x == 1 && VTList[vt[3] - 1].y == 0)
                {
                    FaceList[FaceCount].pt1 = vi[0] - 1;
                    FaceList[FaceCount].pt2 = vi[1] - 1;
                    FaceList[FaceCount].pt3 = vi[2] - 1;
                    FaceList[FaceCount].pt4 = vi[3] - 1;
                    direction = 3;
                   // std::cout << FaceCount << " is XY Flipped! URA!!!" << std::endl;
                }
                else if (VTList[vt[3] - 1].x == 0 && VTList[vt[3] - 1].y == 0 &&
                    VTList[vt[0] - 1].x == 1 && VTList[vt[0] - 1].y == 0 &&
                    VTList[vt[1] - 1].x == 1 && VTList[vt[1] - 1].y == 1 &&
                    VTList[vt[2] - 1].x == 0 && VTList[vt[2] - 1].y == 1)
                {
                    FaceList[FaceCount].pt1 = vi[3] - 1;
                    FaceList[FaceCount].pt2 = vi[0] - 1;
                    FaceList[FaceCount].pt3 = vi[1] - 1;
                    FaceList[FaceCount].pt4 = vi[2] - 1;
                    direction = 0;
                    //std::cout << FaceCount << " is Right Unflipped! URA!!!" << std::endl;
                }
                else if (VTList[vt[3] - 1].x == 1 && VTList[vt[3] - 1].y == 0 &&
                    VTList[vt[0] - 1].x == 0 && VTList[vt[0] - 1].y == 0 &&
                    VTList[vt[1] - 1].x == 0 && VTList[vt[1] - 1].y == 1 &&
                    VTList[vt[2] - 1].x == 1 && VTList[vt[2] - 1].y == 1)
                {
                    FaceList[FaceCount].pt1 = vi[3] - 1;
                    FaceList[FaceCount].pt2 = vi[0] - 1;
                    FaceList[FaceCount].pt3 = vi[1] - 1;
                    FaceList[FaceCount].pt4 = vi[2] - 1;
                    direction = 1;
                   // std::cout << FaceCount << " is Right X flipped! URA!!!" << std::endl;
                }
                else if (VTList[vt[3] - 1].x == 0 && VTList[vt[3] - 1].y == 1 &&
                    VTList[vt[0] - 1].x == 1 && VTList[vt[0] - 1].y == 1 &&
                    VTList[vt[1] - 1].x == 1 && VTList[vt[1] - 1].y == 0 &&
                    VTList[vt[2] - 1].x == 0 && VTList[vt[2] - 1].y == 0)
                {
                    FaceList[FaceCount].pt1 = vi[3] - 1;
                    FaceList[FaceCount].pt2 = vi[0] - 1;
                    FaceList[FaceCount].pt3 = vi[1] - 1;
                    FaceList[FaceCount].pt4 = vi[2] - 1;
                    direction = 2;
                  //  std::cout << FaceCount << " is Right Y flipped! URA!!!" << std::endl;
                }
                else if (VTList[vt[3] - 1].x == 1 && VTList[vt[3] - 1].y == 1 &&
                    VTList[vt[0] - 1].x == 0 && VTList[vt[0] - 1].y == 1 &&
                    VTList[vt[1] - 1].x == 0 && VTList[vt[1] - 1].y == 0 &&
                    VTList[vt[2] - 1].x == 1 && VTList[vt[2] - 1].y == 0)
                {
                    FaceList[FaceCount].pt1 = vi[3] - 1;
                    FaceList[FaceCount].pt2 = vi[0] - 1;
                    FaceList[FaceCount].pt3 = vi[1] - 1;
                    FaceList[FaceCount].pt4 = vi[2] - 1;
                    direction = 3;
                   // std::cout << FaceCount << " is Right XY flipped! URA!!!" << std::endl;
                }
                else {
                    direction = 0;
                    FaceList[FaceCount].pt1 = vi[0] - 1;
                    FaceList[FaceCount].pt2 = vi[1] - 1;
                    FaceList[FaceCount].pt3 = vi[2] - 1;
                    FaceList[FaceCount].pt4 = vi[3] - 1;
                };
                NormalList[vi[0] - 1][frame] = NormalUnsorted[ vn[0] - 1];
                NormalList[vi[1] - 1][frame] = NormalUnsorted[vn[1] - 1];
                NormalList[vi[2] - 1][frame] = NormalUnsorted[ vn[2] - 1];
                NormalList[vi[3] - 1][frame] = NormalUnsorted[ vn[3] - 1];

                FaceList[FaceCount].dir = direction;

                FaceList[FaceCount].texid = curTexID;
                ModelList[FaceCount][0] = LoadModelFromMesh(Quad2Mesh(FaceList[FaceCount].pt1, FaceList[FaceCount].pt2, FaceList[FaceCount].pt3, FaceList[FaceCount].pt4, direction,frame));
                ModelList[FaceCount][0].materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = TextureList[curTexID];

                FaceCount += 1;

            }
            else if (std::count(line.begin(), line.end(), ' ') == 3) {
               // std::cout << " its a tri" << std::endl; // if its a tri, dont bother trying to figure out the rotation/texture direction, it is impossible basically.
                std::string point;
                iss >> point;
                std::replace(point.begin(), point.end(), '/', ' ');
                std::istringstream pointStream(point);

                int vi[3];
                int vt[3];
                int vn[3];


                pointStream >> vi[0] >> vt[0] >> vn[0];

                iss >> point;
                std::replace(point.begin(), point.end(), '/', ' ');
                pointStream = std::istringstream(point);
                pointStream >> vi[1] >> vt[1] >> vn[1];


                iss >> point;
                std::replace(point.begin(), point.end(), '/', ' ');
                pointStream = std::istringstream(point);
                pointStream >> vi[2] >> vt[2] >> vn[2];

                FaceList[FaceCount].pt1 = vi[0] - 1;
                FaceList[FaceCount].pt2 = vi[1] - 1;
                FaceList[FaceCount].pt3 = vi[2] - 1;
                FaceList[FaceCount].pt4 = vi[2] - 1;

                NormalList[vi[0] - 1][frame] = NormalUnsorted[vn[0] - 1];
                NormalList[vi[1] - 1][frame] = NormalUnsorted[vn[1] - 1];
                NormalList[vi[2] - 1][frame] = NormalUnsorted[vn[2] - 1];

                ModelList[FaceCount][0] = LoadModelFromMesh(Quad2Mesh(FaceList[FaceCount].pt1, FaceList[FaceCount].pt2, FaceList[FaceCount].pt3, FaceList[FaceCount].pt4, 0, frame));

                ModelList[FaceCount][0].materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = TextureList[curTexID];
                FaceList[FaceCount].dir = 0;
                FaceList[FaceCount].texid = curTexID;
                FaceCount += 1;

            };
        };

    }
};



void LoadOBJFrame(std::string filename, uint16_t frame) {
    std::fstream ModelIn(filename, std::ios_base::in);
    std::string line;

    uint16_t NNPointCount = 0;
    uint16_t NNFaceCount = 0;
    uint16_t NNNcnt = 0;
    unsigned char NormalUnsorted[5000] = { 0 };




    int vtCount = 0;
    while (std::getline(ModelIn, line)) {
        std::string s;
        std::istringstream iss(line);

        iss >> s;

        if (line.substr(0, 2) == "v ") {

            iss >> PointList[NNPointCount][frame].x >> PointList[NNPointCount][frame].y >> PointList[NNPointCount][frame].z;
            NNPointCount += 1;
        }

        if (line.substr(0, 2) == "vn") {
            VECTOR TestNormal;
            iss >> TestNormal[0] >> TestNormal[1] >> TestNormal[2];
            float CurrentLowest = 5000;
            int lowestNormalID;

            for (int i = 0; i < 162; i++) {
                float xsqr = (TestNormal[0] - FNORMS[i][0]) * (TestNormal[0] - FNORMS[i][0]);
                float ysqr = (TestNormal[1] - FNORMS[i][1]) * (TestNormal[1] - FNORMS[i][1]);
                float zsqr = (TestNormal[2] - FNORMS[i][2]) * (TestNormal[2] - FNORMS[i][2]);
                float dotProd = sqrt(xsqr + ysqr + zsqr);

                if (dotProd < CurrentLowest) {
                    CurrentLowest = dotProd;
                    lowestNormalID = i;
                };

            }

            std::cout << " Normal " << TestNormal[0] << " " << TestNormal[1] << " " << TestNormal[2] << "  is most similar to FNORM ID : " << lowestNormalID << " " << FNORMS[lowestNormalID][0] << " " << FNORMS[lowestNormalID][1] << " " << FNORMS[lowestNormalID][2] << std::endl;
            std::cout << "Dot Product is " << CurrentLowest << std::endl;

            NormalUnsorted[NNNcnt] = lowestNormalID;

            NNNcnt += 1;
        }



        if (line.substr(0, 2) == "f ") {
            if (std::count(line.begin(), line.end(), ' ') == 4) {
                std::cout << " its a quad" << std::endl;
                std::string point;
                iss >> point;
                std::replace(point.begin(), point.end(), '/', ' ');
                std::istringstream pointStream(point);

                int vi[4];
                int vt[4];
                int vn[4];


                pointStream >> vi[0] >> vt[0] >> vn[0];

                iss >> point;
                std::replace(point.begin(), point.end(), '/', ' ');
                pointStream = std::istringstream(point);
                pointStream >> vi[1] >> vt[1] >> vn[1];


                iss >> point;
                std::replace(point.begin(), point.end(), '/', ' ');
                pointStream = std::istringstream(point);
                pointStream >> vi[2] >> vt[2] >> vn[2];


                iss >> point;
                std::replace(point.begin(), point.end(), '/', ' ');
                pointStream = std::istringstream(point);
                pointStream >> vi[3] >> vt[3] >> vn[3];

                uint16_t Direction = FaceList[NNFaceCount].dir;

                NormalList[vi[0] - 1][frame] = NormalUnsorted[vn[0] - 1];
                NormalList[vi[1] - 1][frame] = NormalUnsorted[vn[1] - 1];
                NormalList[vi[2] - 1][frame] = NormalUnsorted[vn[2] - 1];
                NormalList[vi[3] - 1][frame] = NormalUnsorted[vn[3] - 1];

                ModelList[NNFaceCount][frame] = LoadModelFromMesh(Quad2Mesh(FaceList[NNFaceCount].pt1, FaceList[NNFaceCount].pt2, FaceList[NNFaceCount].pt3, FaceList[NNFaceCount].pt4, Direction, frame));
                ModelList[NNFaceCount][frame].materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = TextureList[FaceList[NNFaceCount].texid];
                NNFaceCount += 1;

            }
            else if (std::count(line.begin(), line.end(), ' ') == 3) {
                std::cout << " its a tri" << std::endl; // if its a tri, dont bother trying to figure out the rotation/texture direction, it is impossible basically.
                std::string point;
                iss >> point;
                std::replace(point.begin(), point.end(), '/', ' ');
                std::istringstream pointStream(point);

                int vi[3];
                int vt[3];
                int vn[3];


                pointStream >> vi[0] >> vt[0] >> vn[0];

                iss >> point;
                std::replace(point.begin(), point.end(), '/', ' ');
                pointStream = std::istringstream(point);
                pointStream >> vi[1] >> vt[1] >> vn[1];


                iss >> point;
                std::replace(point.begin(), point.end(), '/', ' ');
                pointStream = std::istringstream(point);
                pointStream >> vi[2] >> vt[2] >> vn[2];

                NormalList[vi[0] - 1][frame] = NormalUnsorted[vn[0] - 1];
                NormalList[vi[1] - 1][frame] = NormalUnsorted[vn[1] - 1];
                NormalList[vi[2] - 1][frame] = NormalUnsorted[vn[2] - 1];


                ModelList[NNFaceCount][frame] = LoadModelFromMesh(Quad2Mesh(FaceList[NNFaceCount].pt1, FaceList[NNFaceCount].pt2, FaceList[NNFaceCount].pt3, FaceList[NNFaceCount].pt4, 0, frame));

                ModelList[NNFaceCount][frame].materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = TextureList[FaceList[NNFaceCount].texid];
                NNFaceCount += 1;

            };
        };

    }
};

unsigned short animsCount = 0;

void MeshExport(std::string OutputName) {
    std::ofstream myFile(OutputName, std::ios::out | std::ios::binary);

    unsigned short PTCC = swap_endian_ushort(PointCount);
    unsigned short FCCC = swap_endian_ushort(FaceCount);
    unsigned short FRMC = swap_endian_ushort(animsCount);

    myFile.write((char *)&PTCC, sizeof(unsigned short));
    myFile.write((char *)&FCCC, sizeof(unsigned short));
    myFile.write((char *)&FRMC, sizeof(unsigned short ));

    for (int j = 0; j < animsCount; j++) {
        for (int i = 0; i < PointCount; i++) {
            FIXED8 Point[XYZ];
            Point[0] = swap_endian_sshort(toFIXED8(PointList[i][j].x));
            Point[1] = swap_endian_sshort(toFIXED8(PointList[i][j].y));
            Point[2] = swap_endian_sshort(toFIXED8(PointList[i][j].z));

            myFile.write((char *)&Point[0],sizeof(short));
            myFile.write((char *)&Point[1],sizeof(short));
            myFile.write((char *)&Point[2],sizeof(short));
        }
    }

    for (int i = 0; i < FaceCount; i++) {
        uint16_t dir = swap_endian_ushort(FaceList[i].dir);
        uint16_t pt1 = swap_endian_ushort(FaceList[i].pt1);
        uint16_t pt2 = swap_endian_ushort(FaceList[i].pt2);
        uint16_t pt3 = swap_endian_ushort(FaceList[i].pt3);
        uint16_t pt4 = swap_endian_ushort(FaceList[i].pt4);
        uint16_t texid = swap_endian_ushort(FaceList[i].texid);
        myFile.write((char*)&dir, sizeof(short));
        myFile.write((char*)&pt1, sizeof(short));
        myFile.write((char*)&pt2, sizeof(short));
        myFile.write((char*)&pt3, sizeof(short));
        myFile.write((char*)&pt4, sizeof(short));
        myFile.write((char*)&texid, sizeof(short));
    }
    for (int j = 0; j < animsCount; j++) {
        for (int i = 0; i < PointCount; i++) {
            myFile.write((char*)&NormalList[i][j], sizeof(char)); // these are Chars
        }
    }
    
    myFile.close();

    std::filesystem::path techPath(OutputName);
    techPath.replace_extension(".TXT");
    std::ofstream TextDoc(techPath.string(), std::ios::out | std::ios::binary);
    for (int i = 0; i < MTLLISTID+1; i++) {

        int correctMTL = -1;

        for (int j = 0; j < MTLLISTID+1; j++) {
            if(MTLNameList[j].id == i) correctMTL = j;

        };

        std::transform(MTLNameList[correctMTL].TexName.begin(), MTLNameList[correctMTL].TexName.end(), MTLNameList[correctMTL].TexName.begin(), ::toupper);
        TextDoc << "LoadTGA(\"" << MTLNameList[correctMTL].TexName << "\"); // Tex No " << i << std::endl;

    }

    TextDoc.close();

};

std::string TextureNames[38] = {
"defText/empTexture_00.png",
"defText/empTexture_01.png",
"defText/empTexture_02.png",
"defText/empTexture_03.png",
"defText/empTexture_04.png",
"defText/empTexture_05.png",
"defText/empTexture_06.png",
"defText/empTexture_07.png",
"defText/empTexture_08.png",
"defText/empTexture_09.png",
"defText/empTexture_10.png",
"defText/empTexture_11.png",
"defText/empTexture_12.png",
"defText/empTexture_13.png",
"defText/empTexture_14.png",
"defText/empTexture_15.png",
"defText/empTexture_16.png",
"defText/empTexture_17.png",
"defText/empTexture_18.png",
"defText/empTexture_19.png",
"defText/empTexture_20.png",
"defText/empTexture_21.png",
"defText/empTexture_22.png",
"defText/empTexture_23.png",
"defText/empTexture_24.png",
"defText/empTexture_25.png",
"defText/empTexture_26.png",
"defText/empTexture_27.png",
"defText/empTexture_28.png",
"defText/empTexture_29.png",
"defText/empTexture_30.png",
"defText/empTexture_31.png",
"defText/empTexture_32.png",
"defText/empTexture_33.png",
"defText/empTexture_34.png",
"defText/empTexture_35.png",
"defText/empTexture_36.png",
"defText/empTexture_37.png"
};

int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "raylib [models] example - model animation");

    rlDisableBackfaceCulling();
    // Define the camera to look into our 3d world
    Camera camera = { 0 };
    camera.position = { 0.0f, -10.0f, -10.0f }; // Camera position
    camera.target = { 0.0f, 0.0f, 0.0f };      // Camera looking at point
    camera.up = { 0.0f, -1.0f, 0.0f };          // Camera up vector (rotation towards target)
    camera.fovy = 45.0f;                                // Camera field-of-view Y
    camera.projection = CAMERA_PERSPECTIVE;             // Camera mode type

   
    Vector3 position = { 0.0f, 0.0f, 0.0f };            // Set model position

    // Load animation data
    int animFrameCounter = 0;

    SetTargetFPS(60);                   // Set our game to run at 60 frames-per-second
    
    for (int i = 0; i < 37; i++) {
        Image checked = LoadImage(TextureNames[i].c_str());
        TextureList[i] = LoadTextureFromImage(checked);
        UnloadImage(checked);
    }

    int isAnimation = tinyfd_messageBox("SSV 3.0 ", "Is this an animation?","yesno", "question", 0);


    if (isAnimation == 0) {
        animsCount = 1;
        LoadOBJ2Init(tinyfd_openFileDialog("Select a OBJ file!", NULL, NULL, NULL, NULL, 0), 0);
        std::cout << "hello " << std::endl;
    };
    if (isAnimation == 1) {
        char animCountChar[100];

        int totalFrames = atoi(tinyfd_inputBox("SSV 3.0 ", "How many frames are there in this animation? ", ""));
        animsCount = atoi(tinyfd_inputBox("SSV 3.0 ", "How many Keyframes are needed",""));

        if (animsCount > totalFrames) return -10;
        std::string ogName = tinyfd_openFileDialog("Select First Frame OBJ!", NULL, NULL, NULL, NULL, 0);
        LoadOBJ2Init(ogName, 0);

        int j = 1;
        for (int i = totalFrames/animsCount; i < totalFrames; i+=totalFrames/animsCount) {
            std::filesystem::path FF(ogName);

            std::cout << FF.string() << std::endl;
            std::string FileNameTBC(FF.filename().string());
          //  std::cout << FileNameTBC << std::endl;



            if (i < 10) {
                
                FileNameTBC.replace(FileNameTBC.end()-5, FileNameTBC.end()-4, std::to_string(i));
                std::cout << FileNameTBC << std::endl;
            }

            if (i >= 10 && i < 100) {
                FileNameTBC.replace(FileNameTBC.end() - 6, FileNameTBC.end() - 4, std::to_string(i));
                std::cout << FileNameTBC << std::endl;
            }

            if (i >= 100) {
                FileNameTBC.replace(FileNameTBC.end() - 7, FileNameTBC.end() - 4, std::to_string(i));
                std::cout << FileNameTBC << std::endl;
            };
            FF.replace_filename(FileNameTBC);
            LoadOBJFrame(FF.string(),j);
            j++;
        };


        std::cout << totalFrames << std::endl;
        std::cout << animsCount << std::endl;
    };

    Ray ray = { 0 };


    Model TestModel = { 0 };


    //TestModel = LoadModelFromMesh(Quad2Mesh(FaceList[0].pt1, FaceList[0].pt2, FaceList[0].pt3, FaceList[0].pt4, sprNoflip, texture));
    int SelectedID = -1;

    // Main game loop
    while (!WindowShouldClose())        // Detect window close button or ESC key
    {
        // Update
        UpdateCamera(&camera, CAMERA_THIRD_PERSON);

        BeginDrawing();

        ClearBackground(RAYWHITE);

        BeginMode3D(camera);

        DrawGrid(10, 1.0f);         // Draw a grid

        if (IsKeyPressed(KEY_Q) && animFrameCounter > 0) {
            animFrameCounter -= 1;
        }

        if (IsKeyPressed(KEY_E) && animFrameCounter <= animsCount) {
            animFrameCounter += 1;
        }

        Vector3 Position = { 0.0f,0.0f,0.0f };



        float NearestPT = 1000000.f;

        ray = GetMouseRay(GetMousePosition(), camera);

        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            for (int i = 0; i < FaceCount; i++) {

                RayCollision TRay = GetRayCollisionQuad(ray, PointList[FaceList[i].pt1][animFrameCounter], PointList[FaceList[i].pt2][animFrameCounter], PointList[FaceList[i].pt3][animFrameCounter], PointList[FaceList[i].pt4][animFrameCounter]);
                if (TRay.hit == true && TRay.distance < NearestPT) {
                    NearestPT = TRay.distance;
                    SelectedID = i;
                }
            }
        };
                
        if (IsKeyPressed(KEY_U) && SelectedID != -1) { /// Rotate Left
            FXFACE FaceThingOld = FaceList[SelectedID];

            FaceList[SelectedID].pt1 = FaceThingOld.pt4;
            FaceList[SelectedID].pt2 = FaceThingOld.pt1;
            FaceList[SelectedID].pt3 = FaceThingOld.pt2;
            FaceList[SelectedID].pt4 = FaceThingOld.pt3;



            for (int i = 0; i < animsCount; i++) {
                UnloadModel(ModelList[SelectedID][i]);
                ModelList[SelectedID][i] = LoadModelFromMesh(Quad2Mesh(FaceThingOld.pt4, FaceThingOld.pt1, FaceThingOld.pt2, FaceThingOld.pt3,FaceThingOld.dir,i));
                ModelList[SelectedID][i].materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = TextureList[FaceList[SelectedID].texid];
            }
        };
       
        if (IsKeyPressed(KEY_I) && SelectedID != -1) { /// Rotate Right
            FXFACE FaceThingOld = FaceList[SelectedID];

            FaceList[SelectedID].pt1 = FaceThingOld.pt2;
            FaceList[SelectedID].pt2 = FaceThingOld.pt3;
            FaceList[SelectedID].pt3 = FaceThingOld.pt4;
            FaceList[SelectedID].pt4 = FaceThingOld.pt1;



            for (int i = 0; i < animsCount; i++) {
                UnloadModel(ModelList[SelectedID][i]);
                ModelList[SelectedID][i] = LoadModelFromMesh(Quad2Mesh(FaceThingOld.pt2, FaceThingOld.pt3, FaceThingOld.pt4, FaceThingOld.pt1, FaceThingOld.dir, i));
                ModelList[SelectedID][i].materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = TextureList[FaceList[SelectedID].texid];
            }
        };
       
        if (IsKeyPressed(KEY_ONE) && SelectedID != -1) { /// 1 and 2 are now the same point

            int uniquePoints[3];
            //find the first dupe 
            if (FaceList[SelectedID].pt1 == FaceList[SelectedID].pt4 || FaceList[SelectedID].pt1 == FaceList[SelectedID].pt2) { // the first point is the dupe
                uniquePoints[0] = FaceList[SelectedID].pt2;
                uniquePoints[1] = FaceList[SelectedID].pt3;
                uniquePoints[2] = FaceList[SelectedID].pt4;


            } else 
            if (FaceList[SelectedID].pt2 == FaceList[SelectedID].pt3) { // the second point is the dupe
                uniquePoints[0] = FaceList[SelectedID].pt1;
                uniquePoints[1] = FaceList[SelectedID].pt3;
                uniquePoints[2] = FaceList[SelectedID].pt4;

            } else 
            if (FaceList[SelectedID].pt3 == FaceList[SelectedID].pt4) { // the third point is the dupe
                uniquePoints[0] = FaceList[SelectedID].pt1;
                uniquePoints[1] = FaceList[SelectedID].pt2;
                uniquePoints[2] = FaceList[SelectedID].pt4;
            };

            FaceList[SelectedID].pt1 = uniquePoints[0];
            FaceList[SelectedID].pt2 = uniquePoints[0];
            FaceList[SelectedID].pt3 = uniquePoints[1];
            FaceList[SelectedID].pt4 = uniquePoints[2];

            for (int i = 0; i < animsCount; i++) {
                UnloadModel(ModelList[SelectedID][i]);
                ModelList[SelectedID][i] = LoadModelFromMesh(Quad2Mesh(FaceList[SelectedID].pt1, FaceList[SelectedID].pt2, FaceList[SelectedID].pt3, FaceList[SelectedID].pt4, FaceList[SelectedID].dir, i));
                ModelList[SelectedID][i].materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = TextureList[FaceList[SelectedID].texid];
            }
        };
       
        if (IsKeyPressed(KEY_TWO) && SelectedID != -1) { /// 2 and 3 are now the same point
            int uniquePoints[3];
            //find the first dupe 
            if (FaceList[SelectedID].pt1 == FaceList[SelectedID].pt4 || FaceList[SelectedID].pt1 == FaceList[SelectedID].pt2) { // the first point is the dupe
                uniquePoints[0] = FaceList[SelectedID].pt2;
                uniquePoints[1] = FaceList[SelectedID].pt3;
                uniquePoints[2] = FaceList[SelectedID].pt4;


            }
            else
                if (FaceList[SelectedID].pt2 == FaceList[SelectedID].pt3) { // the second point is the dupe
                    uniquePoints[0] = FaceList[SelectedID].pt1;
                    uniquePoints[1] = FaceList[SelectedID].pt3;
                    uniquePoints[2] = FaceList[SelectedID].pt4;

                }
                else
                    if (FaceList[SelectedID].pt3 == FaceList[SelectedID].pt4) { // the third point is the dupe
                        uniquePoints[0] = FaceList[SelectedID].pt1;
                        uniquePoints[1] = FaceList[SelectedID].pt2;
                        uniquePoints[2] = FaceList[SelectedID].pt4;
                    };

            FaceList[SelectedID].pt1 = uniquePoints[0];
            FaceList[SelectedID].pt2 = uniquePoints[1];
            FaceList[SelectedID].pt3 = uniquePoints[1];
            FaceList[SelectedID].pt4 = uniquePoints[2];

            for (int i = 0; i < animsCount; i++) {
                UnloadModel(ModelList[SelectedID][i]);
                ModelList[SelectedID][i] = LoadModelFromMesh(Quad2Mesh(FaceList[SelectedID].pt1, FaceList[SelectedID].pt2, FaceList[SelectedID].pt3, FaceList[SelectedID].pt4, FaceList[SelectedID].dir, i));
                ModelList[SelectedID][i].materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = TextureList[FaceList[SelectedID].texid];
            }
        };

        if (IsKeyPressed(KEY_THREE) && SelectedID != -1) { /// 3 and 4 are now the same point
            int uniquePoints[3];
            //find the first dupe 
            if (FaceList[SelectedID].pt1 == FaceList[SelectedID].pt4 || FaceList[SelectedID].pt1 == FaceList[SelectedID].pt2) { // the first point is the dupe
                uniquePoints[0] = FaceList[SelectedID].pt2;
                uniquePoints[1] = FaceList[SelectedID].pt3;
                uniquePoints[2] = FaceList[SelectedID].pt4;


            }
            else
                if (FaceList[SelectedID].pt2 == FaceList[SelectedID].pt3) { // the second point is the dupe
                    uniquePoints[0] = FaceList[SelectedID].pt1;
                    uniquePoints[1] = FaceList[SelectedID].pt3;
                    uniquePoints[2] = FaceList[SelectedID].pt4;

                }
                else
                    if (FaceList[SelectedID].pt3 == FaceList[SelectedID].pt4) { // the third point is the dupe
                        uniquePoints[0] = FaceList[SelectedID].pt1;
                        uniquePoints[1] = FaceList[SelectedID].pt2;
                        uniquePoints[2] = FaceList[SelectedID].pt4;
                    };

            FaceList[SelectedID].pt1 = uniquePoints[0];
            FaceList[SelectedID].pt2 = uniquePoints[1];
            FaceList[SelectedID].pt3 = uniquePoints[2];
            FaceList[SelectedID].pt4 = uniquePoints[2];

            for (int i = 0; i < animsCount; i++) {
                UnloadModel(ModelList[SelectedID][i]);
                ModelList[SelectedID][i] = LoadModelFromMesh(Quad2Mesh(FaceList[SelectedID].pt1, FaceList[SelectedID].pt2, FaceList[SelectedID].pt3, FaceList[SelectedID].pt4, FaceList[SelectedID].dir, i));
                ModelList[SelectedID][i].materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = TextureList[FaceList[SelectedID].texid];
            }
        };


        if (IsKeyPressed(KEY_FOUR) && SelectedID != -1) { /// 4 and 1 are now the same point
            int uniquePoints[3];
            //find the first dupe 
            if (FaceList[SelectedID].pt1 == FaceList[SelectedID].pt4 || FaceList[SelectedID].pt1 == FaceList[SelectedID].pt2) { // the first point is the dupe
                uniquePoints[0] = FaceList[SelectedID].pt2;
                uniquePoints[1] = FaceList[SelectedID].pt3;
                uniquePoints[2] = FaceList[SelectedID].pt4;


            }
            else
                if (FaceList[SelectedID].pt2 == FaceList[SelectedID].pt3) { // the second point is the dupe
                    uniquePoints[0] = FaceList[SelectedID].pt1;
                    uniquePoints[1] = FaceList[SelectedID].pt3;
                    uniquePoints[2] = FaceList[SelectedID].pt4;

                }
                else
                    if (FaceList[SelectedID].pt3 == FaceList[SelectedID].pt4) { // the third point is the dupe
                        uniquePoints[0] = FaceList[SelectedID].pt1;
                        uniquePoints[1] = FaceList[SelectedID].pt2;
                        uniquePoints[2] = FaceList[SelectedID].pt4;
                    };

            FaceList[SelectedID].pt1 = uniquePoints[0];
            FaceList[SelectedID].pt2 = uniquePoints[1];
            FaceList[SelectedID].pt3 = uniquePoints[2];
            FaceList[SelectedID].pt4 = uniquePoints[0];

            for (int i = 0; i < animsCount; i++) {
                UnloadModel(ModelList[SelectedID][i]);
                ModelList[SelectedID][i] = LoadModelFromMesh(Quad2Mesh(FaceList[SelectedID].pt1, FaceList[SelectedID].pt2, FaceList[SelectedID].pt3, FaceList[SelectedID].pt4, FaceList[SelectedID].dir, i));
                ModelList[SelectedID][i].materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = TextureList[FaceList[SelectedID].texid];
            }
        };

        if (IsKeyPressed(KEY_J) && SelectedID != -1) { ///Horizontal
            if (FaceList[SelectedID].dir == 0) {
                FaceList[SelectedID].dir = 1;
            }else
            if (FaceList[SelectedID].dir == 1) {
                FaceList[SelectedID].dir = 0;
            }else
            if (FaceList[SelectedID].dir == 2) {
                FaceList[SelectedID].dir = 3;
            } else
            if (FaceList[SelectedID].dir == 3) {
                FaceList[SelectedID].dir = 2;
            }

            for (int i = 0; i < animsCount; i++) {
                UnloadModel(ModelList[SelectedID][i]);
                ModelList[SelectedID][i] = LoadModelFromMesh(Quad2Mesh(FaceList[SelectedID].pt1, FaceList[SelectedID].pt2, FaceList[SelectedID].pt3, FaceList[SelectedID].pt4, FaceList[SelectedID].dir, i));
                ModelList[SelectedID][i].materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = TextureList[FaceList[SelectedID].texid];
            }
        };

        if (IsKeyPressed(KEY_K) && SelectedID != -1) { ///Vertical
            if (FaceList[SelectedID].dir == 0) {
                FaceList[SelectedID].dir = 2;
            }
            else
                if (FaceList[SelectedID].dir == 1) {
                    FaceList[SelectedID].dir = 3;
                }
                else
                    if (FaceList[SelectedID].dir == 2) {
                        FaceList[SelectedID].dir = 0;
                    }
                    else
                        if (FaceList[SelectedID].dir == 3) {
                            FaceList[SelectedID].dir = 1;
                        }

            for (int i = 0; i < animsCount; i++) {
                UnloadModel(ModelList[SelectedID][i]);
                ModelList[SelectedID][i] = LoadModelFromMesh(Quad2Mesh(FaceList[SelectedID].pt1, FaceList[SelectedID].pt2, FaceList[SelectedID].pt3, FaceList[SelectedID].pt4, FaceList[SelectedID].dir, i));
                ModelList[SelectedID][i].materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = TextureList[FaceList[SelectedID].texid];
            }
        };

        for (int i = 0; i < FaceCount; i++) {
            Color MColour = WHITE;
            if (i == SelectedID) MColour = RED;
            DrawModel(ModelList[i][animFrameCounter], Position, 1.0f, MColour);
        };

        EndMode3D();


        if (IsKeyDown(KEY_LEFT_CONTROL) && IsKeyDown(KEY_S)) MeshExport(tinyfd_saveFileDialog("Save SSV to Location",0 ,0 ,0 ,0 ));

        EndDrawing();
    }

    CloseWindow();                  // Close window and OpenGL context

    return 0;
}
