#include "layer/layer.h";
#include "shape/cube.h";

#include <glad/gl.h>
#include <glm/glm.hpp>

namespace graphics::layer {
const float Layer::TranslateUnit = 2.0f;
const float Layer::TranslateVector[] = {-TranslateUnit, 0, TranslateUnit};

Layer::Layer(glm::mat3 _axisTransformMatrix) : blocks(), degCounter(0), axisTransformMatrix(_axisTransformMatrix) {}
  
void Layer::draw(graphics::shape::Cube cubes[27]) {
    
  for (int i = 0; i < 9; i++) {
    glm::vec3 translate = axisTransformMatrix * glm::vec3(0, TranslateVector[i / 3], TranslateVector[i % 3]);
    glPushMatrix();
    glTranslatef(translate.x, translate.y, translate.z);
    cubes[blocks[i]].draw();
    glPopMatrix();
  }
}

int* Layer::getBlocks() { return this->blocks; }
void Layer::setBlocks(const int blocks[9]) {
  for (int i = 0; i < 9; i++) {
    this->blocks[i] = blocks[i];
  }
}

void Layer::rotate() {
  int tmp = this->blocks[0];
  this->blocks[0] = this->blocks[2];
  this->blocks[2] = this->blocks[8];
  this->blocks[8] = this->blocks[6];
  this->blocks[6] = tmp;

  tmp = this->blocks[1];
  this->blocks[1] = this->blocks[5];
  this->blocks[5] = this->blocks[7];
  this->blocks[7] = this->blocks[3];
  this->blocks[3] = tmp;
}
};