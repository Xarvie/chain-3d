//
// Created by caspase on 8/20/2020.
//

#include "Painter.h"
#include "GraphicsContext.h"
#include "TextureMgr.h"
#include <cmath>

#define PI		3.1415926535898f
#define PI_2	6.2831853071795f

namespace Simple2D
{
    //-------------------------------------------------------------------------
    // Painter
    //-------------------------------------------------------------------------
    Painter::Painter(GraphicsContext* graphics_context)
            : pGraphicsContext(graphics_context)
            , bAntiAliased(false)
    {
        vTextureIndices[0] = 0;
        vTextureIndices[1] = 2;
        vTextureIndices[2] = 1;
        vTextureIndices[3] = 0;
        vTextureIndices[4] = 3;
        vTextureIndices[5] = 2;
    }

    Painter::~Painter()
    {

    }

    void Painter::DrawTexture(float x, float y, Texture2D* texture, const Color& color)
    {
        this->DrawTexture(x, y, texture->width, texture->height, texture, color);
    }

    void Painter::DrawTexture(float x, float y, int w, int h, Texture2D* texture, const Color& color)
    {
        float hw = w * 0.5;
        float hh = h * 0.5;

        vTextureVertices[0].position = glm::vec3(x - hw, y - hh, 0);
        vTextureVertices[1].position = glm::vec3(x - hw, y + hh, 0);
        vTextureVertices[2].position = glm::vec3(x + hw, y + hh, 0);
        vTextureVertices[3].position = glm::vec3(x + hw, y - hh, 0);

        vTextureVertices[0].texcoord = texture->uv[0];
        vTextureVertices[1].texcoord = texture->uv[1];
        vTextureVertices[2].texcoord = texture->uv[2];
        vTextureVertices[3].texcoord = texture->uv[3];

        vTextureVertices[0].color = color;
        vTextureVertices[1].color = color;
        vTextureVertices[2].color = color;
        vTextureVertices[3].color = color;

        pGraphicsContext->SetProgram(SPT_Sprite);
        pGraphicsContext->SetBlendMode(StandardBlendMode::SBM_AlphaTexture);
        pGraphicsContext->GetRenderer()->AppendRenderData(vTextureVertices, 4, vTextureIndices, 6, texture->textureUnique->id, PrimType::PT_Triangles);
    }

    void Painter::DrawTexture(float x, float y, float rot, float hscale, float vscale, Texture2D* texture, const Color& color)
    {
        float w = texture->width * hscale;
        float h = texture->height * vscale;

        float tx1 = -w * 0.5;
        float ty1 = -h * 0.5;
        float tx2 =  w * 0.5;
        float ty2 =  h * 0.5;

        if ( rot == 0.0f ) {
            vTextureVertices[0].position = glm::vec3(x + tx1, y + ty1, 0);
            vTextureVertices[1].position = glm::vec3(x + tx1, y + ty2, 0);
            vTextureVertices[2].position = glm::vec3(x + tx2, y + ty2, 0);
            vTextureVertices[3].position = glm::vec3(x + tx2, y + ty1, 0);
        }
        else {
            float cost = cosf(rot);
            float sint = sinf(rot);

            vTextureVertices[0].position = glm::vec3(x + tx1 * cost + ty1 * sint, y - tx1 * sint + ty1 * cost, 0);
            vTextureVertices[1].position = glm::vec3(x + tx1 * cost + ty2 * sint, y - tx1 * sint + ty2 * cost, 0);
            vTextureVertices[2].position = glm::vec3(x + tx2 * cost + ty2 * sint, y - tx2 * sint + ty2 * cost, 0);
            vTextureVertices[3].position = glm::vec3(x + tx2 * cost + ty1 * sint, y - tx2 * sint + ty1 * cost, 0);
        }

        vTextureVertices[0].texcoord = texture->uv[0];
        vTextureVertices[1].texcoord = texture->uv[1];
        vTextureVertices[2].texcoord = texture->uv[2];
        vTextureVertices[3].texcoord = texture->uv[3];

        vTextureVertices[0].color = color;
        vTextureVertices[1].color = color;
        vTextureVertices[2].color = color;
        vTextureVertices[3].color = color;

        pGraphicsContext->SetProgram(SPT_Sprite);
        pGraphicsContext->SetBlendMode(StandardBlendMode::SBM_AlphaTexture);
        pGraphicsContext->GetRenderer()->AppendRenderData(vTextureVertices, 4, vTextureIndices, 6, texture->textureUnique->id, PrimType::PT_Triangles);
    }

    void Painter::DrawLine(const glm::vec2& p1, const glm::vec2& p2, const Color& color, float thickness)
    {
        this->PathLineTo(p1 + 0.5f);
        this->PathLineTo(p2 + 0.5f);
        this->StrokePolyline(color, false, thickness);
        this->PathClear();
    }

    void Painter::DrawLines(const glm::vec2* points, int point_count, const Color& color, bool closed, float thickness)
    {
        for ( int i = 0; i < point_count; i++ ) {
            this->PathLineTo(points[i]);
        }
        this->StrokePolyline(color, closed, thickness);
        this->PathClear();
    }

    void Painter::DrawTriangle(const glm::vec2& p1, const glm::vec2& p2, const glm::vec2& p3, const Color& color, float thickness)
    {
        this->PathLineTo(p1);
        this->PathLineTo(p2);
        this->PathLineTo(p3);
        this->StrokePolyline(color, true, thickness);
        this->PathClear();
    }

    void Painter::FillTriangle(const glm::vec2& p1, const glm::vec2& p2, const glm::vec2& p3, const Color& color)
    {
        this->PathLineTo(p1);
        this->PathLineTo(p2);
        this->PathLineTo(p3);
        this->StrokeConvexPolyFilled(color);
        this->PathClear();
    }

    void Painter::DrawRect(const glm::vec2& tl, const glm::vec2& br, const Color& color, float rounding, float thickness)
    {
        this->PathRect(tl + glm::vec2(0.5f, 0.5f), br - glm::vec2(0.5f, 0.5f), rounding);
        this->StrokePolyline(color, true, thickness);
        this->PathClear();
    }

    void Painter::FillRect(const glm::vec2& tl, const glm::vec2& br, const Color& color, float rounding)
    {
        if ( rounding <= 0 ) {
            this->PrimRect(tl, br, color);
        }
        else {
            this->PathRect(tl, br, rounding);
            this->StrokeConvexPolyFilled(color);
            this->PathClear();
        }
    }

    void Painter::DrawCircle(const glm::vec2& center, float radius, const Color& color, int segments, float thickness)
    {
        this->PathArcTo(center, radius - 0.5f, 0, PI_2, segments);
        this->StrokePolyline(color, false, thickness);
        this->PathClear();
    }

    void Painter::FillCircle(const glm::vec2& center, float radius, const Color& color, int segments)
    {
        this->PathArcTo(center, radius, 0, PI, segments);
        this->StrokeConvexPolyFilled(color);
        this->PathClear();
    }

    void Painter::PathLineTo(const glm::vec2& pos)
    {
        vPaths.push_back(pos);
    }

    void Painter::PathArcTo(const glm::vec2& centre, float radius, float min, float max, int segments)
    {
        for ( int i = 0; i <= segments; i++ ) {
            const float a = min + (( float ) i / ( float ) segments) * (max - min);
            vPaths.push_back(glm::vec2(centre.x - sinf(a) * radius, centre.y + cosf(a) * radius));
        }
    }

    void Painter::PathArcToFast(const glm::vec2& centre, float radius, int a_min_of_12, int a_max_of_12)
    {
        static glm::vec2 circle[13];
        static bool has_build = false;

        /* 构建圆 */
        if ( has_build == false ) {
            for ( int i = 0; i <= 12; i++ ) {
                float radian = float(i) / 12 * 6.28318f;
                circle[i].x = -sinf(radian);
                circle[i].y = cosf(radian);
            }
            has_build = true;
        }

        for ( int i = a_min_of_12; i <= a_max_of_12; i++ ) {
            vPaths.push_back(glm::vec2(circle[i].x * radius + centre.x, circle[i].y * radius + centre.y));
        }
    }

    void Painter::PathRect(const glm::vec2& tl, const glm::vec2& br, float rounding)
    {
        if ( rounding <= 0.0f ) {
            this->PathLineTo(tl);
            this->PathLineTo(glm::vec2(br.x, tl.y));
            this->PathLineTo(br);
            this->PathLineTo(glm::vec2(tl.x, br.y));
        }
        else {
            this->PathArcToFast(glm::vec2(tl.x + rounding, tl.y - rounding), rounding, 0, 3);
            this->PathArcToFast(glm::vec2(tl.x + rounding, br.y + rounding), rounding, 3, 6);
            this->PathArcToFast(glm::vec2(br.x - rounding, br.y + rounding), rounding, 6, 9);
            this->PathArcToFast(glm::vec2(br.x - rounding, tl.y - rounding), rounding, 9, 12);
        }
    }

    void Painter::PrimRect(const glm::vec2& tl, const glm::vec2& br, const Color& color)
    {
        vGeometryVertices.resize(4);
        vGeometryIndices.resize(6);

        vGeometryVertices[0].position = glm::vec3(tl.x, tl.y, 0);
        vGeometryVertices[1].position = glm::vec3(br.x, tl.y, 0);
        vGeometryVertices[2].position = glm::vec3(br.x, br.y, 0);
        vGeometryVertices[3].position = glm::vec3(tl.x, br.y, 0);

        vGeometryVertices[0].color = color;
        vGeometryVertices[1].color = color;
        vGeometryVertices[2].color = color;
        vGeometryVertices[3].color = color;

        vGeometryIndices[0] = 0;
        vGeometryIndices[1] = 2;
        vGeometryIndices[2] = 1;
        vGeometryIndices[3] = 0;
        vGeometryIndices[4] = 3;
        vGeometryIndices[5] = 2;

        pGraphicsContext->SetProgram(SPT_Color);
        pGraphicsContext->SetBlendMode(StandardBlendMode::SBM_AlphaTexture);
        pGraphicsContext->GetRenderer()->AppendRenderData(&vGeometryVertices[0], 4, &vGeometryIndices[0], 6, PT_Triangles);
    }

    void Painter::StrokePolyline(const Color& color, bool closed, float thickness)
    {
        if ( vPaths.size() < 2 ) return;

        int points_count = vPaths.size();
        int count = (closed == false) ? points_count - 1 : points_count;

        const bool thick_line = thickness > 1.0f;

        /* 反走样 */
        const float AA_SIZE = 1.0f;
        const float alpha = 0.0f;

        const int idx_count = thick_line ? count * 18 : count * 12;
        const int vtx_count = thick_line ? points_count * 4 : points_count * 3;

        vGeometryVertices.resize(vtx_count);
        vGeometryIndices.resize(idx_count);

        /* 临时缓冲区 */
        glm::vec2* temp_normals = ( glm::vec2* ) alloca(points_count * (thick_line ? 5 : 3) * sizeof(glm::vec2));
        glm::vec2* temp_points = temp_normals + points_count;

        /* 计算直线的法线 */
        for ( int i1 = 0; i1 < count; i1++ ) {
            const int i2 = (i1 + 1) == points_count ? 0 : i1 + 1;
            glm::vec2 diff = vPaths[i2] - vPaths[i1];
            diff = glm::normalize(diff);

            temp_normals[i1].x = diff.y;
            temp_normals[i1].y = -diff.x;
        }

        if ( closed == false ) {
            temp_normals[points_count - 1] = temp_normals[points_count - 2];
        }

        if ( thick_line == false ) {
            if ( closed == false ) {
                temp_points[0] = vPaths[0] + temp_normals[0] * AA_SIZE;
                temp_points[1] = vPaths[0] - temp_normals[0] * AA_SIZE;
                temp_points[(points_count - 1) * 2 + 0] = vPaths[points_count - 1] + temp_normals[points_count - 1] * AA_SIZE;
                temp_points[(points_count - 1) * 2 + 1] = vPaths[points_count - 1] - temp_normals[points_count - 1] * AA_SIZE;
            }
            unsigned int idx1 = 0;

            for ( int i1 = 0; i1 < count; i1++ ) {
                const int i2 = (i1 + 1) == points_count ? 0 : i1 + 1;
                unsigned int idx2 = (i1 + 1) == points_count ? 0 : idx1 + 3;

                /* 平均法向量，即两直线交点的法向量 */
                glm::vec2 dm = (temp_normals[i1] + temp_normals[i2]) * 0.5f;
                float dmr2 = dm.x*dm.x + dm.y*dm.y;
                if ( dmr2 > 0.000001f ) {
                    float scale = 1.0f / dmr2;
                    if ( scale > 100.0f ) scale = 100.0f;
                    dm = dm * scale;
                }
                dm = dm * AA_SIZE;

                temp_points[i2 * 2 + 0] = vPaths[i2] + dm;
                temp_points[i2 * 2 + 1] = vPaths[i2] - dm;

                /* 索引数据 */
                vGeometryIndices[i1 * 12 + 0] = idx2 + 0;
                vGeometryIndices[i1 * 12 + 1] = idx1 + 0;
                vGeometryIndices[i1 * 12 + 2] = idx1 + 2;

                vGeometryIndices[i1 * 12 + 3] = idx1 + 2;
                vGeometryIndices[i1 * 12 + 4] = idx2 + 2;
                vGeometryIndices[i1 * 12 + 5] = idx2 + 0;

                vGeometryIndices[i1 * 12 + 6] = idx2 + 1;
                vGeometryIndices[i1 * 12 + 7] = idx1 + 1;
                vGeometryIndices[i1 * 12 + 8] = idx1 + 0;

                vGeometryIndices[i1 * 12 + 9] = idx1 + 0;
                vGeometryIndices[i1 * 12 + 10] = idx2 + 0;
                vGeometryIndices[i1 * 12 + 11] = idx2 + 1;

                idx1 = idx2;
            }

            /* 顶点数据 */
            for ( int i = 0; i < points_count; i++ ) {
                vGeometryVertices[i * 3 + 0].position = glm::vec3(vPaths[i], 0);
                vGeometryVertices[i * 3 + 1].position = glm::vec3(temp_points[i * 2 + 0], 0);
                vGeometryVertices[i * 3 + 2].position = glm::vec3(temp_points[i * 2 + 1], 0);

                vGeometryVertices[i * 3 + 0].color = color;
                vGeometryVertices[i * 3 + 1].color = color;
                vGeometryVertices[i * 3 + 2].color = color;

                vGeometryVertices[i * 3 + 1].color.a = alpha;
                vGeometryVertices[i * 3 + 2].color.a = alpha;
            }
        }
        else {
            const float half_inner_thickness = (thickness - AA_SIZE) * 0.5f;
            if ( closed == false ) {
                temp_points[0] = vPaths[0] + temp_normals[0] * (half_inner_thickness + AA_SIZE);
                temp_points[1] = vPaths[0] + temp_normals[0] * (half_inner_thickness);
                temp_points[2] = vPaths[0] - temp_normals[0] * (half_inner_thickness);
                temp_points[3] = vPaths[0] - temp_normals[0] * (half_inner_thickness + AA_SIZE);
                temp_points[(points_count - 1) * 4 + 0] = vPaths[points_count - 1] + temp_normals[points_count - 1] * (half_inner_thickness + AA_SIZE);
                temp_points[(points_count - 1) * 4 + 1] = vPaths[points_count - 1] + temp_normals[points_count - 1] * (half_inner_thickness);
                temp_points[(points_count - 1) * 4 + 2] = vPaths[points_count - 1] - temp_normals[points_count - 1] * (half_inner_thickness);
                temp_points[(points_count - 1) * 4 + 3] = vPaths[points_count - 1] - temp_normals[points_count - 1] * (half_inner_thickness + AA_SIZE);
            }

            unsigned int idx1 = 0;

            for ( int i1 = 0; i1 < count; i1++ ) {
                const int i2 = (i1 + 1) == points_count ? 0 : i1 + 1;
                unsigned int idx2 = (i1 + 1) == points_count ? 0 : idx1 + 4;

                /* 平均法向量，即两直线交点的法向量 */
                glm::vec2 dm = (temp_normals[i1] + temp_normals[i2]) * 0.5f;
                float dmr2 = dm.length();
                if ( dmr2 > 0.000001f ) {
                    float scale = 1.0f / dmr2;
                    if ( scale > 100.0f ) scale = 100.0f;
                    dm = dm * scale;
                }
                glm::vec2 dm_out = dm * (half_inner_thickness + AA_SIZE);
                glm::vec2 dm_in = dm * half_inner_thickness;

                /* 索引数据 */
                temp_points[i2 * 4 + 0] = vPaths[i2] + dm_out;
                temp_points[i2 * 4 + 1] = vPaths[i2] + dm_in;
                temp_points[i2 * 4 + 2] = vPaths[i2] - dm_in;
                temp_points[i2 * 4 + 3] = vPaths[i2] - dm_out;

                vGeometryIndices[i1 * 18 + 0] = idx2 + 1;
                vGeometryIndices[i1 * 18 + 1] = idx1 + 1;
                vGeometryIndices[i1 * 18 + 2] = idx1 + 2;

                vGeometryIndices[i1 * 18 + 3] = idx1 + 2;
                vGeometryIndices[i1 * 18 + 4] = idx2 + 2;
                vGeometryIndices[i1 * 18 + 5] = idx2 + 1;

                vGeometryIndices[i1 * 18 + 6] = idx2 + 1;
                vGeometryIndices[i1 * 18 + 7] = idx1 + 1;
                vGeometryIndices[i1 * 18 + 8] = idx1 + 0;

                vGeometryIndices[i1 * 18 + 9] = idx1 + 0;
                vGeometryIndices[i1 * 18 + 10] = idx2 + 0;
                vGeometryIndices[i1 * 18 + 11] = idx2 + 1;

                vGeometryIndices[i1 * 18 + 12] = idx2 + 2;
                vGeometryIndices[i1 * 18 + 13] = idx1 + 2;
                vGeometryIndices[i1 * 18 + 14] = idx1 + 3;

                vGeometryIndices[i1 * 18 + 15] = idx1 + 3;
                vGeometryIndices[i1 * 18 + 16] = idx2 + 3;
                vGeometryIndices[i1 * 18 + 17] = idx2 + 2;

                idx1 = idx2;
            }

            /* 顶点数据 */
            for ( int i = 0; i < points_count; i++ ) {
                vGeometryVertices[i * 4 + 0].position = glm::vec3(temp_points[i * 4 + 0],0); vGeometryVertices[i * 4 + 0].color = color;
                vGeometryVertices[i * 4 + 1].position = glm::vec3(temp_points[i * 4 + 1], 0); vGeometryVertices[i * 4 + 1].color = color;
                vGeometryVertices[i * 4 + 2].position = glm::vec3(temp_points[i * 4 + 2], 0); vGeometryVertices[i * 4 + 2].color = color;
                vGeometryVertices[i * 4 + 3].position = glm::vec3(temp_points[i * 4 + 3], 0); vGeometryVertices[i * 4 + 3].color = color;

                vGeometryVertices[i * 4 + 0].color.a = alpha;
                vGeometryVertices[i * 4 + 3].color.a = alpha;
            }
        }

        pGraphicsContext->SetProgram(SPT_Color);
        pGraphicsContext->SetBlendMode(StandardBlendMode::SBM_AlphaTexture);
        pGraphicsContext->GetRenderer()->AppendRenderData(&vGeometryVertices[0], vtx_count, &vGeometryIndices[0], idx_count, PT_Triangles);
    }

    void Painter::StrokeConvexPolyFilled(const Color& color)
    {
        int points_count = vPaths.size();
        int idx_count;
        int vtx_count;

        if ( bAntiAliased ) {
            const float AA_SIZE = 1.0f;
            const float alpha = 0.0f;

            idx_count = (points_count - 2) * 3 + points_count * 6;
            vtx_count = (points_count * 2);

            vGeometryVertices.resize(vtx_count);
            vGeometryIndices.resize(idx_count);

            unsigned int vtx_inner_idx = 0;
            unsigned int vtx_outer_idx = 1;

            for ( int i = 2; i < points_count; i++ ) {
                vGeometryIndices[(i - 2) * 3 + 0] = vtx_inner_idx;
                vGeometryIndices[(i - 2) * 3 + 1] = vtx_inner_idx + ((i - 1) << 1);
                vGeometryIndices[(i - 2) * 3 + 2] = vtx_inner_idx + (i << 1);
            }

            /* 计算法线 */
            glm::vec2* temp_normals = ( glm::vec2* ) alloca(points_count * sizeof(glm::vec2));
            for ( int i0 = points_count - 1, i1 = 0; i1 < points_count; i0 = i1++ ) {
                const glm::vec2& p0 = vPaths[i0];
                const glm::vec2& p1 = vPaths[i1];
                glm::vec2 diff = p1 - p0;
                diff = glm::normalize(diff);

                temp_normals[i0].x = diff.y;
                temp_normals[i0].y = -diff.x;
            }

            for ( int i0 = points_count - 1, i1 = 0; i1 < points_count; i0 = i1++ ) {
                /* 平均法向量，即两直线交点的法向量 */
                glm::vec2 dm = (temp_normals[i0] + temp_normals[i1]) * 0.5f;
                float dmr2 = dm.length();

                if ( dmr2 > 0.000001f ) {
                    float scale = 1.0f / dmr2;
                    if ( scale > 100.0f ) scale = 100.0f;
                    dm = dm * scale;
                }
                dm = dm * AA_SIZE * 0.5f;

                /* 顶点数据 */
                vGeometryVertices[i1 * 2 + 0].position = glm::vec3(vPaths[i1] - dm, 0);
                vGeometryVertices[i1 * 2 + 1].position = glm::vec3(vPaths[i1] + dm, 0);

                vGeometryVertices[i1 * 2 + 0].color = color;
                vGeometryVertices[i1 * 2 + 1].color = color;
                vGeometryVertices[i1 * 2 + 1].color.a = alpha;

                /* 索引数据 */
                vGeometryIndices[i1 * 6 + 0 + (points_count - 2) * 3] = vtx_inner_idx + (i1 << 1);
                vGeometryIndices[i1 * 6 + 1 + (points_count - 2) * 3] = vtx_inner_idx + (i0 << 1);
                vGeometryIndices[i1 * 6 + 2 + (points_count - 2) * 3] = vtx_outer_idx + (i0 << 1);
                vGeometryIndices[i1 * 6 + 3 + (points_count - 2) * 3] = vtx_outer_idx + (i0 << 1);
                vGeometryIndices[i1 * 6 + 4 + (points_count - 2) * 3] = vtx_outer_idx + (i1 << 1);
                vGeometryIndices[i1 * 6 + 5 + (points_count - 2) * 3] = vtx_inner_idx + (i1 << 1);
            }
        }
        else {
            idx_count = (points_count - 2) * 3;
            vtx_count = points_count;

            vGeometryVertices.resize(vtx_count);
            vGeometryIndices.resize(idx_count);

            for ( int i = 0; i < vtx_count; i++ ) {
                vGeometryVertices[i].position = glm::vec3(vPaths[i], 0);
                vGeometryVertices[i].color = color;
            }

            for ( int i = 2; i < points_count; i++ ) {
                vGeometryIndices[(i - 2) * 3 + 0] = 0;
                vGeometryIndices[(i - 2) * 3 + 1] = i - 1;
                vGeometryIndices[(i - 2) * 3 + 2] = i;
            }
        }

        pGraphicsContext->SetProgram(SPT_Color);
        pGraphicsContext->SetBlendMode(StandardBlendMode::SBM_AlphaTexture);
        pGraphicsContext->GetRenderer()->AppendRenderData(&vGeometryVertices[0], vtx_count, &vGeometryIndices[0], idx_count, PT_Triangles);
    }

    void Painter::PathClear()
    {
        vPaths.resize(0);
    }
}