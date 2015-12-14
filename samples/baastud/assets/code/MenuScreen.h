#ifndef MENUSCREEN_H
#define MENUSCREEN_H

#include <mutiny/mutiny.h>

#include <memory>

using namespace mutiny::engine;

class MenuScreen : public Behaviour
{
public:
  static GameObject* create();

  virtual void onAwake();
  virtual void onGui();

private:
  arc<Texture2d> wwwTexture;
  arc<Texture2d> titleTexture;
  GameObject* cameraGo;

};

#endif

