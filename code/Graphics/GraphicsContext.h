//
// Created by caspase on 8/20/2020.
//

#ifndef INC_3D_GRAPHICSCONTEXT_H
#define INC_3D_GRAPHICSCONTEXT_H


#include "TextureMgr.h"
#include <vector>
#include "StandardProgram.h"
#include "Program.h"
#include <Renderer.h>

namespace Simple2D {
    class RenderWindow;

    class Renderer;

    class TextRender;

    struct FrameBufferTexture {
        FrameBufferTexture() : frameBuffer(-1), width(0), height(0) {}

        ~FrameBufferTexture() {
            glDeleteFramebuffers(1, &frameBuffer);
            delete textureUnique;
        }

        TextureUnique *textureUnique;
        GLuint frameBuffer;

        int width;
        int height;
    };

    enum StandardBlendMode {
        SBM_ParticleBlend,
        SBM_AlphaTexture,
        SBM_Default
    };

    //------------------------------------------------------------------------------
    // GraphicsContext
    //------------------------------------------------------------------------------
    class GraphicsContext {
    public:
        GraphicsContext(int w, int d);

        ~GraphicsContext();

        void SetProgram(StandardProgramType type);

        void SetProgram(Program *program);

        void SetProgramEffect(ProgramEffect *program_effect);

        void ResetProgram();

        void SetBlendMode(StandardBlendMode mode);

        void ResetBlendMode();

        void UpdateMatrix(int w, int h);

        void DrawElements(void *vertex_data, void *index_data, int index_count, PrimType type);

        void RenderToTexture(FrameBufferTexture *fbt);

        void SetScissor(int x, int y, int w, int h);

        void ResetScissor();

        void SetViewPort(int x, int y, int w, int h);

        FrameBufferTexture *NewFrameBufferTexture(int width, int height);

        void BeginRender();

        void EndRender();

        void SetRenderer(Renderer *renderer) { pRenderer = renderer; }

        Renderer *GetRenderer() { return pRenderer; }

        void SetClearColor(const Color &color) { cClearColor = color; }

        Program *GetProgram() { return pProgram; }

        void ResetDrawcall() { nDrawcall = 0; }

        int GetDrawcall() { return nDrawcall; }

    private:
        Renderer *pRenderer;
        TextRender *pTextRender;
        RenderWindow *pRenderWindow;
        FrameBufferTexture *pFrameBufferTexture;
        GLint view_port[4];

        glm::mat4 mTransformMatrix;

        StandardProgram standardProgram;
        Program *pProgram;
        ProgramEffect *pProgramEffect;

        StandardBlendMode standardBlendMode;

        Color cClearColor;

        int nDrawcall;
    };
}
#endif //INC_3D_GRAPHICSCONTEXT_H
