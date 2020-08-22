#pragma once
#include "Math.h"
#include "Program.h"
#include "StandardProgram.h"

//#define DEBUG_RENDER

namespace Simple2D
{
    class GraphicsContext;

    enum PrimType
    {
        PT_Points,
        PT_Lines,
        PT_Triangles,
        PT_Unknown
    };

    //---------------------------------------------------------------
    // Renderer
    //---------------------------------------------------------------
    class Renderer
    {
    public:
        Renderer();
        ~Renderer();

#ifdef DEBUG_RENDER
        void debug_init();

		void debug_draw();
#endif

        void AppendRenderData(SpriteVertexFormat* vertex_data, int vertex_count,
                              unsigned int* index_data, int index_count, GLuint texture, PrimType type);

        template<class Type>
        void AppendRenderData(Type* vertex_data, int vertex_count, unsigned int* index_data, int index_count, PrimType type)
        {
            int total_vertex_count = vertex_buffer_size / sizeof(Type);
            if ( total_vertex_count - nVertexCount < vertex_count || index_buffer_size - nIndexCount < index_count ) {
                this->Flush();
            }

            for ( int i = 0; i < index_count; i++ ) {
                vIndexBuffer[nIndexCount + i] = nVertexCount + index_data[i];
            }

            char* data_header = vVertexBuffer + nVertexCount * sizeof(Type);
            memcpy(data_header, ( char* ) vertex_data, vertex_count * sizeof(Type));

            nVertexCount += vertex_count;
            nIndexCount += index_count;
            primType = type;
        }

        void Flush();

        void SetGraphicsContext(GraphicsContext* gc) { pGraphicsContext = gc; }

    private:
        int SetTexture(GLuint texture);

        void BindTexture();

    private:
        GraphicsContext* pGraphicsContext;
        PrimType primType;

        int nVertexCount;
        int nIndexCount;

        int nCurrentTextureCount;
        static const int nMaxNumberOfTexture = 16;
        GLuint vTextures[nMaxNumberOfTexture];

        static const int vertex_buffer_size = 1024 * 1024;
        static const int index_buffer_size = 40000;
        char vVertexBuffer[vertex_buffer_size];		/* 用于合并顶点的缓冲区 */
        unsigned int vIndexBuffer[index_buffer_size];		/* 用于合并索引的缓冲区 */

#ifdef DEBUG_RENDER
        bool init_debug_mode;
		Program* program;
		TextureUnique* texture1;
		TextureUnique* texture2;

		struct ColorVertex
		{
			Vec3 position;
			Vec2 texcoord;
			Color color;
			float texindex;
		};
#endif
    };
}