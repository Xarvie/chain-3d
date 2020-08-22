//
// Created by caspase on 8/20/2020.
//

#include "BatchSpriteScene.h"


#include <algorithm>


//-------------------------------------------------------------------------
// SpriteActionScene
//-------------------------------------------------------------------------
static const char* tween_names[31] = {
        "Linear",

        "InQuad",
        "OutQuad",
        "InOutQuad",

        "InCubic",
        "OutCubic",
        "InOutCubic",

        "InQuart",
        "OutQuart",
        "InOutQuart",

        "InQuint",
        "OutQuint",
        "InOutQunt",

        "InSine",
        "OutSine",
        "InOutSine",

        "InExpo",
        "OutExpo",
        "InOutExpo",

        "InCirc",
        "OutCirc",
        "InOutCirc",

        "InElastic",
        "OutElastic",
        "InOutElastic",

        "InBack",
        "OutBack",
        "InOutBack",

        "InBounce",
        "OutBounce",
        "InOutBounce"
};

//-------------------------------------------------------------------------
// BatchSpriteScene
//-------------------------------------------------------------------------
BatchSpriteScene::BatchSpriteScene()
{
    texture = TexturePool::GetInstance()->GetTexture("zazaka.png");
    backgorund = TexturePool::GetInstance()->GetTexture("bg2.png");

    backgorund->textureUnique->SetWrapping(TexWrapping::Wrapping_Repeat, TexWrapping::Wrapping_Repeat);
    float x = 800.0f / backgorund->width;
    float y = 600.0f / backgorund->height;
    backgorund->uv[0] = glm::vec2 (0, 0);
    backgorund->uv[1] = glm::vec2 (0, y);
    backgorund->uv[2] = glm::vec2 (x, y);
    backgorund->uv[3] = glm::vec2 (x, 0);

    for ( int i = 0; i < SPRITE_COUNT; i++ ) {
        pps[i].x = (texture->width)*(i % 9+1);
        pps[i].y = (texture->height) * (std::rand() % 9 + 1);
        pps[i].dx = 0;
        pps[i].dy = 0;
        pps[i].rot = 0.0;
        pps[i].drot = 0.0;
        pps[i].scale = 1.0;
        pps[i].dscale = 0.0;
        pps[i].color.set(1.0 * 0.8 + 0.2, 1.0 * 0.8 + 0.2, 1.0 * 0.8 + 0.2, 1);
    }

    nSpriteCount = 100;
}

BatchSpriteScene::~BatchSpriteScene()
{

}

void BatchSpriteScene::Update(float dt)
{
    for ( int i = 0; i < nSpriteCount; i++ ) {

        pps[i].x += pps[i].dx * dt;
        pps[i].y += pps[i].dy * dt;
        pps[i].scale = pps[i].scale + pps[i].dscale * dt;

        if ( pps[i].x <= 0 || pps[i].x > 750 ) pps[i].dx = -pps[i].dx;
        if ( pps[i].y <= 0 || pps[i].y > 600 ) pps[i].dy = -pps[i].dy;
        if ( pps[i].scale > 2 || pps[i].scale < 0.5 ) pps[i].dscale = -pps[i].dscale;

        pps[i].rot += pps[i].drot * dt;
    }
}

void BatchSpriteScene::Draw(Painter* painter)
{
    painter->DrawTexture(400, 300, 800, 600, backgorund);
    for ( int i = 0; i < nSpriteCount; i++ ) {
        painter->DrawTexture(pps[i].x, pps[i].y, pps[i].rot, pps[i].scale, pps[i].scale, texture, pps[i].color);
    }

    //this->DrawGui();
}

//void BatchSpriteScene::DrawGui()
//{
//    ImGui::SetNextWindowSize(ImVec2(300, 35));
//    ImGui::SetNextWindowPos(ImVec2(800 - 300 - 180 - 5, 50));
//    ImGui::Begin("Animation", 0, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove);
//    {
//        ImGui::PushItemWidth(ImGui::GetWindowContentRegionWidth());
//        if ( ImGui::InputInt("Sprite Count", &nSpriteCount, 100, 100) ) {
//            nSpriteCount = fmaxf(100, fminf(SPRITE_COUNT, nSpriteCount));
//        }
//    }
//    ImGui::End();
//}

