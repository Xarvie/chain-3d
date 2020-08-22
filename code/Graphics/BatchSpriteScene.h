//
// Created by caspase on 8/20/2020.
//

#ifndef INC_3D_BATCHSPRITESCENE_H
#define INC_3D_BATCHSPRITESCENE_H

#include "GraphicsContext.h"
#include "Painter.h"

using namespace Simple2D;

class DemoScene
{
public:
    virtual ~DemoScene() {}

    virtual void Update(float dt) {}

    virtual void Draw(GraphicsContext* gc, Painter* painter = nullptr) {}
};

//-------------------------------------------------------------------------
// BatchSpriteScene
//-------------------------------------------------------------------------

#define SPRITE_COUNT 4000

class BatchSpriteScene : public DemoScene
{
    struct SpritePos
    {
        float x, y;
        float dx, dy;
        float rot, drot;
        float scale, dscale;
        Simple2D::Color color;
    };

public:
    BatchSpriteScene();

    ~BatchSpriteScene();

    void Update(float dt);

    void Draw(Painter* painter);

    void DrawGui();

private:
    int nSpriteCount;
    Texture2D* texture;
    Texture2D* backgorund;

    SpritePos pps[SPRITE_COUNT];
};


#endif //INC_3D_BATCHSPRITESCENE_H
