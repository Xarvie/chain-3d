//
// Created by caspase on 8/20/2020.
//

#ifndef INC_3D_PAINTER_H
#define INC_3D_PAINTER_H


#include <vector>
#include "Program.h"
#include "GraphicsContext.h"

namespace Simple2D
{
    class Renderer;
    class Texture2D;

    //-------------------------------------------------------------------------
    // Painter
    //-------------------------------------------------------------------------
    class Painter
    {
    public:
        Painter(GraphicsContext* renderer);
        ~Painter();

        void DrawTexture(float x, float y, Texture2D* texture, const Color& color = Color(1, 1, 1, 1));

        void DrawTexture(float x, float y, float rot, float hscale, float vscale, Texture2D* texture, const Color& color = Color(1, 1, 1, 1));

        void DrawTexture(float x, float y, int w, int h, Texture2D* texture, const Color& color = Color(1, 1, 1, 1));

        void DrawLine(const glm::vec2& p1, const glm::vec2& p2, const Color& color, float thickness = 1.0f);

        void DrawLines(const glm::vec2* points, int point_count, const Color& color, bool closed, float thickness = 1.0f);

        void DrawTriangle(const glm::vec2& p1, const glm::vec2& p2, const glm::vec2& p3, const Color& color, float thickness = 1.0f);

        void FillTriangle(const glm::vec2& p1, const glm::vec2& p2, const glm::vec2& p3, const Color& color);

        void DrawRect(const glm::vec2& tl, const glm::vec2& br, const Color& color, float rounding = 0, float thickness = 1.0f);

        void FillRect(const glm::vec2& tl, const glm::vec2& br, const Color& color, float rounding = 0);

        void DrawCircle(const glm::vec2& center, float radius, const Color& color, int segments = 12, float thickness = 1.0f);

        void FillCircle(const glm::vec2& center, float radius, const Color& color, int segments = 12);

        void SetAntiAlaised(bool anti_aliased = true) { bAntiAliased = anti_aliased; }

    private:
        void PathLineTo(const glm::vec2& pos);

        void PathArcTo(const glm::vec2& centre, float radius, float min, float max, int segments = 10);

        void PathArcToFast(const glm::vec2& centre, float radius, int a_min_of_12, int a_max_of_12);

        void PathRect(const glm::vec2& tl, const glm::vec2& br, float rounding = 0.0f);

        void PrimRect(const glm::vec2& tl, const glm::vec2& br, const Color& color);

        void StrokePolyline(const Color& color, bool closed, float thickness);

        void StrokeConvexPolyFilled(const Color& color);

        void PathClear();

    private:
        std::vector<glm::vec2> vPaths;

        GraphicsContext* pGraphicsContext;

        SpriteVertexFormat vTextureVertices[4];
        unsigned int vTextureIndices[6];

        std::vector<ColorVertexFormat> vGeometryVertices;
        std::vector<unsigned int> vGeometryIndices;

        bool bAntiAliased;
    };
}

#endif //INC_3D_PAINTER_H
