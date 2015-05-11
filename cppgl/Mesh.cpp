/*
 Copyright (c) 2015 chenbingfeng (iichenbf#gmail.com)

 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:

 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 */

#include "Mesh.h"
#include "inter.h"
#include <fstream>

NS_CPPGL_BEGIN

enum mode
{
    MODE_NONE,
    MODE_UNKNOWN,
    MODE_NORMAL,
    MODE_VERTEX,
    MODE_TEXTURE,
    MODE_FACE
};

struct face
{
    int v1, v2, v3;
    int t1, t2, t3;
    int n1, n2, n3;
};

inline bool isWhitespace(char c)
{
    return c== ' ' || c == '\n' || c == '\t';
}

inline int readInt(char* buf, int& out)
{
    int l = 0;
    bool neg = false;
    if (buf[0] == '-') {neg = true; buf++;}
    while (buf[l] >= '0' && buf[l] <='9') l++;

    int n = 0;
    int p = 1;
    for (int i = l - 1; i >= 0; i--){
        n += (buf[i] - '0') * p;
        p *= 10;
    }

    if (neg){
        out = -n;
        l++;
    } else {
        out = n;
    }
    return l;
}

inline int readFloat(char* buf, float& out)
{
    bool neg = buf[0] == '-';
    int nat, frac;
    int ln = readInt(buf, nat);

    buf += ln + 1;
    int lf = readInt(buf, frac);
    int p = 1;
    for (int i = 0; i < lf; i++) p *= 10;

    if (neg)
        out = nat - frac / (float)p;
    else
        out = nat + frac / (float)p;

    return ln + lf + 1;
}

int readVector(char* buf, glm::vec3& out)
{
    int i = 0;
    while (isWhitespace(*buf)) {
        buf++; i++;
    }
    buf += readFloat(buf, out.x);
    while (isWhitespace(*buf)) {
        buf++; i++;
    }
    buf += readFloat(buf, out.y);
    while (isWhitespace(*buf)) {
        buf++; i++;
    }
    buf += readFloat(buf, out.z);
    return i;
}

int readFace(char* buf, face& out)
{
    int i = 0;
    while ( isWhitespace( *buf ) ) { buf++; i++; };
    buf += readInt( buf, out.v1 ) + 1;
    buf += readInt( buf, out.t1 ) + 1;
    buf += readInt( buf, out.n1 ) + 1;
    while ( isWhitespace( *buf ) ) { buf++; i++; }
    buf += readInt( buf, out.v2 ) + 1;
    buf += readInt( buf, out.t2 ) + 1;
    buf += readInt( buf, out.n2 ) + 1;
    while ( isWhitespace( *buf ) ) { buf++; i++; }
    buf += readInt( buf, out.v3 ) + 1;
    buf += readInt( buf, out.t3 ) + 1;
    buf += readInt( buf, out.n3 ) + 1;
    return i;
}

Mesh::Mesh(const std::string& objfilename)
{
    std::ifstream file(objfilename.c_str(), std::ios::in || std::ios::ate);
    assert(file.is_open());
    auto fileLen = file.tellg();
    file.seekg(0, std::ios::beg);
    std::vector<char> buf(fileLen);
    file.read(&buf[0], fileLen);
    file.close();

    int approxMem = 295 + fileLen / 1024 * 11;
    std::vector<glm::vec3> vectors;
    vectors.reserve(approxMem);
    std::vector<glm::vec3> normals;
    normals.reserve(approxMem);
    std::vector<glm::vec2> texcoords;
    texcoords.reserve(approxMem);
    _vertices.reserve(approxMem);

    bool inComment = false;
    int mode = MODE_NONE;
    glm::vec3 v3;
    face f;

    for (int i = 0; i < fileLen; i++) {
        if (buf[i] == '#') {
            inComment = true;
            continue;
        } else if(inComment && buf[i] != '\n'){
            continue;
        } else if ( inComment && buf[i] == '\n') {
            inComment = false;
            continue;
        }

        if (mode == MODE_NONE && !isWhitespace(buf[i])){
            if (buf[i] == 'f') {
                mode = MODE_FACE;
            } else if (buf[i] == 'v') {
                char tmp = buf[i+1];
                mode = isWhitespace(tmp) ? MODE_VERTEX :
                    tmp == 'n' ? MODE_NORMAL :
                    tmp == 't' ? MODE_TEXTURE : MODE_UNKNOWN;
                i++;
            } else {
                mode = MODE_UNKNOWN;
            }
        } else if (mode != MODE_NONE) {
            switch (mode) {
                case MODE_UNKNOWN:
                    if (buf[i] == '\n'){
                        mode = MODE_NONE;
                    }
                    break;
                case MODE_VERTEX:
                    i += readVector(&buf[i], v3);
                    vectors.push_back(v3);
                    mode = MODE_NONE;
                    break;
                case MODE_NORMAL:
                    i += readVector( &buf[i], v3 );
                    normals.push_back( v3 );
                    mode = MODE_NONE;
                    break;

                case MODE_TEXTURE:
                    i += readVector( &buf[i], v3 );
                    texcoords.push_back( glm::vec2( v3.x, v3.y ) );
                    mode = MODE_NONE;
                    break;

                case MODE_FACE:
                    i += readFace( &buf[i], f );

                    Vertex vertex = {
                        vectors[f.v1 - 1],
                        texcoords[f.t1 - 1],
                        normals[f.n1 - 1]
                    };
                    _vertices.push_back( vertex );

                    vertex.position = vectors[f.v2 - 1];
                    vertex.texcoord = texcoords[f.t2 - 1];
                    vertex.normal = normals[f.n2 - 1];
                    _vertices.push_back( vertex );
                    
                    vertex.position = vectors[f.v3 - 1];
                    vertex.texcoord = texcoords[f.t3 - 1];
                    vertex.normal = normals[f.n3 - 1];
                    _vertices.push_back( vertex );
                    
                    mode = MODE_NONE;
                    break;
            }
        }

    }

}

const Vertex* Mesh::vertices() const
{
    return &_vertices[0]; //没搞错？？
}

std::size_t Mesh::vertexCount() const
{
    return _vertices.size();
}

SPMesh Mesh::create(const std::string &objfilename)
{
    return SPMesh(new Mesh(objfilename));
}

NS_CPPGL_END