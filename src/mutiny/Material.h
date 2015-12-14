#ifndef MUTINY_ENGINE_MATERIAL_H
#define MUTINY_ENGINE_MATERIAL_H

#include "Object.h"
#include "Matrix4x4.h"
#include "Vector2.h"
#include "arc.h"

#include <GL/glew.h>

#include <memory>
#include <vector>
#include <string>

namespace mutiny
{

namespace engine
{

class Resources;
class Application;
class Shader;
class MeshRenderer;
class Gui;
class Texture;
class ParticleRenderer;
class Graphics;

class Material : public Object
{
  friend class mutiny::engine::Resources;
  friend class mutiny::engine::Application;
  friend class mutiny::engine::MeshRenderer;
  friend class mutiny::engine::Gui;
  friend class mutiny::engine::ParticleRenderer;
  friend class mutiny::engine::Graphics;

public:
  Material(std::string vertContents, std::string fragContents);
  Material(arc<Shader> shader);
  Material(arc<Material> material);

  arc<Shader> getShader();
  void setShader(arc<Shader> shader);
  void setMatrix(std::string propertyName, Matrix4x4 matrix);
  Matrix4x4 getMatrix(std::string propertyName);
  void setFloat(std::string propertyName, float value);
  void setVector(std::string propertyName, Vector2 value);
  void setTexture(std::string propertyName, arc<Texture> texture);
  arc<Texture> getTexture(std::string propertyName);
  void setMainTexture(arc<Texture> texture);
  arc<Texture> getMainTexture();

  int getPassCount();
  void setPass(int pass, arc<Material> _this);

private:
  static arc<Material> current;
  static arc<Material> meshNormalTextureMaterial;
  static arc<Material> meshNormalMaterial;
  static arc<Material> guiMaterial;
  static arc<Material> particleMaterial;

  static Material* load(std::string path);

  std::vector<Matrix4x4> matrices; std::vector<GLuint> matrixIndexes; std::vector<std::string> matrixNames;
  std::vector<float> floats; std::vector<GLuint> floatIndexes; std::vector<std::string> floatNames;
  std::vector<Vector2> vector2s; std::vector<GLuint> vector2Indexes; std::vector<std::string> vector2Names;
  std::vector<arc<Texture> > textures; std::vector<GLuint> textureIndexes; std::vector<std::string> textureNames;

  arc<Shader> managedShader;
  arc<Shader> shader;

  bool indexesDirty;
  void refreshIndexes();

};

}

}

#endif

