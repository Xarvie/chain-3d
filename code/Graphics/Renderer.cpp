//
// Created by caspase on 8/20/2020.
//

#include "Renderer.h"

#include "GraphicsContext.h"

#define MVP_NAME "MVPMatrix"

namespace Simple2D
{
    Renderer::Renderer() : primType(PrimType::PT_Unknown)
    {
#ifdef DEBUG_RENDER
        init_debug_mode = false;
#endif
    }

    Renderer::~Renderer()
    {
#ifdef DEBUG_RENDER
        delete program;
#endif
    }

#ifdef DEBUG_RENDER
    void Renderer::debug_init()
	{
		/* 设置着色器 */
		program = Program::CreateProgram("Shader/testShader.vs", "Shader/testShader.frag");

		/* 设置顶点属性 */
		program->SetVertexAttributes<ColorVertex>(0, struct_offset(ColorVertex, position));
		program->SetVertexAttributes<ColorVertex>(1, struct_offset(ColorVertex, texcoord));
		program->SetVertexAttributes<ColorVertex>(2, struct_offset(ColorVertex, color));
		program->SetVertexAttributes<ColorVertex>(3, struct_offset(ColorVertex, texindex));

		/* 绑定 uniform 数据 */
		GLuint program_handle = program->GetProgramID();
		GLuint last_program;
		glGetIntegerv(GL_CURRENT_PROGRAM, ( GLint* ) &last_program);

		glUseProgram(program_handle);
		glUniform1i(glGetUniformLocation(program_handle, "Texture0"), 0);
		glUniform1i(glGetUniformLocation(program_handle, "Texture1"), 1);
		glUniform1i(glGetUniformLocation(program_handle, "Texture2"), 2);
		glUniform1i(glGetUniformLocation(program_handle, "Texture3"), 3);
		glUniform1i(glGetUniformLocation(program_handle, "Texture4"), 4);
		glUniform1i(glGetUniformLocation(program_handle, "Texture5"), 5);
		glUniform1i(glGetUniformLocation(program_handle, "Texture6"), 6);
		glUniform1i(glGetUniformLocation(program_handle, "Texture7"), 7);
		glUniform1i(glGetUniformLocation(program_handle, "Texture8"), 8);
		glUniform1i(glGetUniformLocation(program_handle, "Texture9"), 9);
		glUniform1i(glGetUniformLocation(program_handle, "Texture10"), 10);
		glUniform1i(glGetUniformLocation(program_handle, "Texture11"), 11);
		glUniform1i(glGetUniformLocation(program_handle, "Texture12"), 12);
		glUniform1i(glGetUniformLocation(program_handle, "Texture13"), 13);
		glUniform1i(glGetUniformLocation(program_handle, "Texture14"), 14);
		glUniform1i(glGetUniformLocation(program_handle, "Texture15"), 15);
		glUseProgram(last_program);

		//program->BindProgram();

		/* 设置 MVP 变换矩阵 */
		//glUniformMatrix4fv(glGetUniformLocation(program->GetProgramID(), "MVPMatrix"), 1, GL_TRUE, mTransformMatrix._m);

		/* 绑定纹理 */
		texture1 = TexturePool::GetInstance()->GetTexture("image.png")->textureUnique;
		texture2 = TexturePool::GetInstance()->GetTexture("image.jpg")->textureUnique;

		//glActiveTexture(GL_TEXTURE0);
		//glBindTexture(GL_TEXTURE_2D, texture1->id);

		//glActiveTexture(GL_TEXTURE1);
		//glBindTexture(GL_TEXTURE_2D, texture2->id);

		this->SetTexture(texture1->id);
		this->SetTexture(texture2->id);

		auto gc = Engine::GetInstance()->GetGraphicsContext();
		gc->SetProgram(program);
	}

	void Renderer::debug_draw()
	{
		if ( init_debug_mode == false ) {
			init_debug_mode = true;
			this->debug_init();
		}

		ColorVertex vertices[4];
		vertices[0].position.set(100, 100, 0);
		vertices[1].position.set(100, 500, 0);
		vertices[2].position.set(500, 500, 0);
		vertices[3].position.set(500, 100, 0);

		vertices[0].texcoord.set(0, 0);
		vertices[1].texcoord.set(0, 1);
		vertices[2].texcoord.set(1, 1);
		vertices[3].texcoord.set(1, 0);

		vertices[0].color.set(1, 1, 1, 1);
		vertices[1].color.set(1, 1, 1, 1);
		vertices[2].color.set(1, 1, 1, 1);
		vertices[3].color.set(1, 1, 1, 1);

		vertices[0].texindex = vertices[1].texindex = vertices[2].texindex = vertices[3].texindex = 1;

		uint32 indices[6];
		indices[0] = 0;
		indices[1] = 2;
		indices[2] = 1;
		indices[3] = 0;
		indices[4] = 3;
		indices[5] = 2;

		/* 设置顶点数据 */
		//program->BindVertexDataToGPU(vertices);

		this->AppendRenderData(vertices, 4, indices, 6, PrimType::PT_Triangles);

		/* 绘制 */
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, indices);

		this->Flush();
	}
#endif

    void Renderer::AppendRenderData(SpriteVertexFormat* vertex_data, int vertex_count,
                                    unsigned int* index_data, int index_count, GLuint texture, PrimType type)
    {
        int texture_index = this->SetTexture(texture);
        for ( int i = 0; i < vertex_count; i++ ) {
            vertex_data[i].texindex = texture_index;
        }
        this->AppendRenderData(vertex_data, vertex_count, index_data, index_count, type);
    }

    int Renderer::SetTexture(GLuint texture)
    {
        int texture_index = -1;
        /* 查找是否已经保存纹理 */
        for ( int i = 0; i < nCurrentTextureCount; i++ ) {
            if ( vTextures[i] == texture ) {
                texture_index = i;
                break;
            }
        }
        /* 新的纹理？添加到纹理数组 */
        if ( texture_index == -1 && nCurrentTextureCount < nMaxNumberOfTexture) {
            vTextures[nCurrentTextureCount] = texture;
            texture_index = nCurrentTextureCount++;
        }
        /* 纹理数组已满？绘制上一批次数据，插入纹理到纹理数组 */
        if ( texture_index == -1 ) {
            this->Flush();
            texture_index = 0;
            vTextures[texture_index] = texture;
            nCurrentTextureCount = 1;
        }
        return texture_index;
    }

    void Renderer::BindTexture()
    {
        for ( int i = 0; i < nCurrentTextureCount; i++ ) {
            glActiveTexture(GL_TEXTURE0 + i);
            glBindTexture(GL_TEXTURE_2D, vTextures[i]);
        }
    }

    void Renderer::Flush()
    {
        if ( nVertexCount == 0 || nIndexCount == 0 ) return;

        this->BindTexture();
        pGraphicsContext->DrawElements(vVertexBuffer, vIndexBuffer, nIndexCount, primType);

        nVertexCount = nIndexCount = 0;
        nCurrentTextureCount = 0;
    }
}