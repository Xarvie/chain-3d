//
// Created by caspase on 8/20/2020.
//

#include "GraphicsContext.h"

#include "Renderer.h"
#include "Data.h"

#include "glm/gtc/matrix_transform.hpp"
namespace Simple2D
{
    int ToEnum(PrimType type)
    {
        switch ( type ) {
            case PrimType::PT_Points:		return GL_POINTS;
            case PrimType::PT_Lines:		return GL_LINES;
            case PrimType::PT_Triangles:	return GL_TRIANGLES;
        }
        return GL_TRIANGLES;
    }


    GraphicsContext::GraphicsContext(int w, int h)
            : pRenderer(nullptr)
            , pTextRender(nullptr)
            , pFrameBufferTexture(nullptr)
            , cClearColor(0, 0, 0, 1)
    {

        this->UpdateMatrix(w, h);

        nDrawcall = 0;

        pProgram = nullptr;
        pProgramEffect = nullptr;
    }

    GraphicsContext::~GraphicsContext()
    {

    }

    void GraphicsContext::SetProgram(StandardProgramType type)
    {
        this->SetProgram(standardProgram.GetProgram(type));
    }

    void GraphicsContext::SetProgram(Program* program)
    {
        if ( pProgram == program ) return;

        pRenderer->Flush();
        pProgram = program;
        pProgram->BindProgram();
        pProgramEffect = nullptr;

        glUniformMatrix4fv(glGetUniformLocation(pProgram->GetProgramID(), "MVPMatrix"), 1, GL_TRUE, &mTransformMatrix[0][0]);
    }

    void GraphicsContext::SetProgramEffect(ProgramEffect* program_effect)
    {
        if ( pProgramEffect == program_effect ) {
            if ( pProgramEffect ) {
                pProgramEffect->BindUniforms();
            }
            return;
        }

        this->SetProgram(program_effect->GetProgram());

        pProgramEffect = program_effect;
        pProgramEffect->BindUniforms();
    }

    void GraphicsContext::ResetProgram()
    {
        pProgram = nullptr;
    }

    void GraphicsContext::SetBlendMode(StandardBlendMode mode)
    {
        if ( standardBlendMode == mode ) return;

        pRenderer->Flush();
        standardBlendMode = mode;

        if ( mode == StandardBlendMode::SBM_ParticleBlend ) {
            glEnable(GL_BLEND);
            glBlendEquation(GL_FUNC_ADD);
            glBlendFuncSeparate(GL_SRC_ALPHA, GL_ONE, GL_ONE, GL_ZERO);
        }
        else if ( mode == StandardBlendMode::SBM_AlphaTexture ) {
            glEnable(GL_BLEND);
            glBlendEquation(GL_FUNC_ADD);
            glBlendFuncSeparate(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_ONE, GL_ZERO);
        }
        else if ( mode == StandardBlendMode::SBM_Default ) {
            glDisable(GL_BLEND);
        }
    }

    void GraphicsContext::ResetBlendMode()
    {
        this->SetBlendMode(StandardBlendMode::SBM_Default);
    }

    void GraphicsContext::UpdateMatrix(int w, int h)
    {
        glm::mat4 ortho = glm::ortho(0, w, h, 0, -1, 1);
        //glm::mat4 tranform = glm::makeTransform(Vec3(0, h, 0), Vec3(1, -1, 1));
        glm::mat4 model(1.0);
        glm::translate(model, glm::vec3((0, h, 0)));
        model = glm::scale(model, glm::vec3(1, -1, 1));
        mTransformMatrix = ortho * model;
    }

    void GraphicsContext::DrawElements(void* vertex_data, void* index_data, int index_count, PrimType type)
    {
        pProgram->BindVertexDataToGPU(vertex_data);
        glDrawElements(ToEnum(type), index_count, GL_UNSIGNED_INT, index_data);
        nDrawcall++;
    }

    void GraphicsContext::SetScissor(int x, int y, int w, int h)
    {
        glEnable(GL_SCISSOR_TEST);
        glScissor(x, y, w, h);
    }

    void GraphicsContext::ResetScissor()
    {
        glDisable(GL_SCISSOR_TEST);
    }

    void GraphicsContext::SetViewPort(int x, int y, int w, int h)
    {
        glViewport(x, y, w, h);
    }

    void GraphicsContext::RenderToTexture(FrameBufferTexture* fbt)
    {
        pFrameBufferTexture = fbt;
    }

    FrameBufferTexture* GraphicsContext::NewFrameBufferTexture(int width, int height)
    {
        FrameBufferTexture* frame_buffer_texture = new FrameBufferTexture;
        frame_buffer_texture->width = width;
        frame_buffer_texture->height = height;

        /* 创建帧缓冲对象 */
        glGenFramebuffers(1, &frame_buffer_texture->frameBuffer);
        glBindFramebuffer(GL_FRAMEBUFFER, frame_buffer_texture->frameBuffer);

        TextureUnique* texture_unique = new TextureUnique;
        texture_unique->SetImageData(width, height, nullptr, false);
        frame_buffer_texture->textureUnique = texture_unique;

        /* 附加纹理到帧缓冲 */
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texture_unique->id, 0);
        if ( glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE ) {
            delete frame_buffer_texture;
            frame_buffer_texture = nullptr;
        }

        /* 解绑 */
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
        return frame_buffer_texture;
    }

    void GraphicsContext::BeginRender()
    {
        /* 渲染到纹理 */
        if ( pFrameBufferTexture ) {
            glBindFramebuffer(GL_FRAMEBUFFER, pFrameBufferTexture->frameBuffer);

            glClearColor(cClearColor.r, cClearColor.g, cClearColor.b, 0);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

            glGetIntegerv(GL_VIEWPORT, view_port);
            glViewport(0, 0, pFrameBufferTexture->width, pFrameBufferTexture->height);
        }
        else {
            glClearColor(cClearColor.r, cClearColor.g, cClearColor.b, cClearColor.a);
            //glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
            glClear(GL_COLOR_BUFFER_BIT);
        }
    }

    void GraphicsContext::EndRender()
    {
        /* 渲染到纹理 */
        if ( pFrameBufferTexture ) {
            pRenderer->Flush();

            glBindFramebuffer(GL_FRAMEBUFFER, 0);
            glViewport(view_port[0], view_port[1], view_port[2], view_port[3]);
        }
        else {
            pRenderer->Flush();
        }
    }
}