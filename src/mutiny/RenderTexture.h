#ifndef MUTINY_ENGINE_RENDERTEXTURE_H
#define MUTINY_ENGINE_RENDERTEXTURE_H

#include "Texture.h"

namespace mutiny
{

namespace engine
{

class Application;
class Graphics;

class RenderTexture : public Texture
{
  friend class mutiny::engine::Application;
  friend class mutiny::engine::Graphics;

public:
  static void setActive(arc<RenderTexture> renderTexture);
  static arc<RenderTexture> getActive();

  RenderTexture(int width, int height);
  virtual ~RenderTexture();

private:
  static arc<RenderTexture> active;

  GLuint nativeFrameBuffer;
  arc<GLuint> _nativeFrameBuffer;

  GLuint nativeRenderBuffer;
  arc<GLuint> _nativeRenderBuffer;

};

}

}

#endif

