#include "level.hpp"


std::pair<std::vector<GLfloat>, std::vector<GLuint>> Level::GenerateVertices() {
 GLuint count = 0;

 //Wall vertices
 std::vector<GLfloat> vertices;
 std::vector<GLuint> indices;
 for(int i = 0; i < levelWidth; i++) {
      for(int j = 0; j < levelHeight; j++) {
          int curTile = map[i][j];
          int ii = i * 2;
          int jj = j * 2;

          if(curTile == 1) {

            std::vector<GLfloat> tempVerts {
                    -1.0+ii, -1.0, 1.0+jj,0, 0, 1,0, 1,
                    1.0+ii, -1.0, 1.0+jj,0, 0, 1,1, 1,
                    1.0+ii, 1.0, 1.0+jj,0, 0, 1, 1, 0,
                    -1.0+ii, 1.0, 1.0+jj,0, 0, 1,0, 0,
                    1.0+ii, -1.0, 1.0+jj,1, 0, 0,0, 1,
                    1.0+ii, -1.0, -1.0+jj,1, 0, 0,1, 1,
                    1.0+ii, 1.0, -1.0+jj,1, 0, 0,1, 0,
                    1.0+ii, 1.0, 1.0+jj, 1, 0, 0,0, 0,
                    1.0+ii, -1.0, -1.0+jj,0, 0, -1,0, 1,
                    -1.0+ii, -1.0, -1.0+jj,0, 0, -1,1, 1,
                    -1.0+ii, 1.0, -1.0+jj,0, 0, -1, 1, 0,
                    1.0+ii, 1.0, -1.0+jj,0, 0, -1,0, 0,
                    -1.0+ii, -1.0, -1.0+jj,-1, 0, 0, 0, 1,
                    -1.0+ii, -1.0, 1.0+jj,-1, 0, 0,1, 1,
                    -1.0+ii, 1.0, 1.0+jj,-1, 0, 0, 1, 0,
                    -1.0+ii, 1.0, -1.0+jj,-1, 0, 0,0, 0,
                    -1.0+ii, 1.0, 1.0+jj,0, 1, 0,0, 1,
                    1.0+ii, 1.0, 1.0+jj,0, 1, 0,1, 1,
                    1.0+ii, 1.0, -1.0+jj,0, 1, 0,1, 0,
                    -1.0+ii, 1.0, -1.0+jj,0, 1, 0,0, 0,
                    1.0+ii, -1.0, 1.0+jj,0, -1, 0,0, 1,
                    -1.0+ii, -1.0, 1.0+jj,0, -1, 0,1, 1,
                    -1.0+ii, -1.0, -1.0+jj,0, -1, 0,1, 0,
                    1.0+ii, -1.0, -1.0+jj,0, -1, 0,0, 0,

            };

            std::vector<GLuint> tempIndices {
                    // Font face
                    0+count, 1+count, 2+count, 2+count, 3+count, 0+count,
                    // Right face
                    7+count, 6+count, 5+count, 5+count, 4+count, 7+count,
                    // Back face
                    11+count, 10+count, 9+count, 9+count, 8+count, 11+count,
                    // Left face
                    15+count, 14+count, 13+count, 13+count, 12+count, 15+count,
                    // Top Face
                    19+count, 18+count, 17+count, 17+count, 16+count, 19+count,
                    // Bottom Face
                    23+count, 22+count, 21+count, 21+count, 20+count, 23+count,
            };

            count += 24;

            vertices.insert(vertices.end(), tempVerts.begin(), tempVerts.end());
            indices.insert(indices.end(), tempIndices.begin(), tempIndices.end());
           }


          std::vector<GLfloat> tempVerts {
              //Floor
              -1.0+ii, -1.0, 1.0+jj,0, 1, 0, 0, 1,
              1.0+ii, -1.0, 1.0+jj,0, 1, 0, 1, 1,
              1.0+ii, -1.0, -1.0+jj,0, 1, 0, 1, 0,
              -1.0+ii, -1.0, -1.0+jj,0, 1, 0, 0, 0,

              //Ceiling
              -1.0+ii, 1.0, 1.0+jj, 0, -1, 0, 0, 1,
              1.0+ii, 1.0, 1.0+jj, 0, -1, 0, 1, 1,
              1.0+ii, 1.0, -1.0+jj, 0, -1, 0, 1, 0,
              -1.0+ii, 1.0, -1.0+jj, 0, -1, 0, 0, 0,
          };

          std::vector<GLuint> tempIndices {
              // Floor
              0+count, 1+count, 2+count, 2+count, 3+count, 0+count,
              // Ceiling
              7+count, 6+count, 5+count, 5+count, 4+count, 7+count,
          };

          count += 8;
          vertices.insert(vertices.end(), tempVerts.begin(), tempVerts.end());
          indices.insert(indices.end(), tempIndices.begin(), tempIndices.end());

      };
 };
return std::make_pair(vertices, indices);
}


void Level::Construct(Shader *shader) {
    for(int i = 0; i < levelWidth; i++) {

        for(int j = 0; j < levelHeight; j++) {
            if( ((double) rand() / (RAND_MAX)) < 0.3) {
                map[i][j] = 1;
            }

            if(i == 0 || i == levelWidth - 1 || j == 0 || j == levelHeight - 1) {
                map[i][j] = 1;
            }
        }
    }

    map[1][1] = 0;

    std::pair<std::vector<GLfloat>, std::vector<GLuint>> vertexData = GenerateVertices();
    levelMesh = new Mesh(vertexData.first, vertexData.second, shader->get());
    levelMesh->setup();
    levelMesh->bind();
}

int Level::checkCollision(glm::vec3 positionVector) {
    positionVector *= 0.5;

    int ceiledX = (int) ceil(positionVector.x - 0.35);
    int ceiledY = (int) ceil(positionVector.z - 0.35);

    int flooredX = (int) floor(positionVector.x + 0.35);
    int flooredY = (int) floor(positionVector.z + 0.35);

    int tright = map[ceiledX][ceiledY];
    int bright = map[ceiledX][flooredY];

    int tleft =  map[flooredX][ceiledY];
    int bleft =  map[flooredX][flooredY];

    int top = map[flooredX][flooredY];
    int bottom = map[ceiledX][ceiledY];

    if(tright || bright || tleft || bleft || top || bottom) {
        return 1;
    }

    return 0;

}





