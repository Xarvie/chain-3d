#include "StandardProgram.h"

namespace Simple2D
{
    /* 颜色着色器 */
    const char* Color_Vertex = R"(
		#version 330 core

		layout(location = 0) in vec3 Position;
		layout(location = 1) in vec4 Color;

		uniform mat4x4 MVPMatrix;

		out vec4 color;

		void main()
		{
			gl_Position = MVPMatrix * vec4(Position, 1.0f);
			color = Color;
		}
	)";

    const char* Color_Fragment = R"(
		#version 330 core

		out vec4 Color;
		in vec4 color;

		void main()
		{
			Color = color;
		}
	)";

    /* 精灵着色器 */
    const char* Sprite_Vertex = R"(
		#version 330 core

		layout(location = 0) in vec3 Position;
		layout(location = 1) in vec2 Texcoord;
		layout(location = 2) in vec4 Color;
		layout(location = 3) in float Texindex;

		uniform mat4x4 MVPMatrix;

		out vec2 texcoord;
		out vec4 color;
		flat out int texindex;

		void main()
		{
			gl_Position =  MVPMatrix * vec4(Position, 1.0f);
			color = Color;
			texcoord = Texcoord;
			texindex = int(Texindex);
		}
	)";

    const char* Sprite_Fragment = R"(
		#version 330 core

		in vec2 texcoord;
		in vec4 color;
		flat in int texindex;

		uniform sampler2D Texture0;
		uniform sampler2D Texture1;
		uniform sampler2D Texture2;
		uniform sampler2D Texture3;
		uniform sampler2D Texture4;
		uniform sampler2D Texture5;
		uniform sampler2D Texture6;
		uniform sampler2D Texture7;
		uniform sampler2D Texture8;
		uniform sampler2D Texture9;
		uniform sampler2D Texture10;
		uniform sampler2D Texture11;
		uniform sampler2D Texture12;
		uniform sampler2D Texture13;
		uniform sampler2D Texture14;
		uniform sampler2D Texture15;

		vec4 SampleTexture(int index)
		{
			switch( index )
			{
			case 0: return texture(Texture0, texcoord);
			case 1: return texture(Texture1, texcoord);
			case 2: return texture(Texture2, texcoord);
			case 3: return texture(Texture3, texcoord);
			case 4: return texture(Texture4, texcoord);
			case 5: return texture(Texture5, texcoord);
			case 6: return texture(Texture6, texcoord);
			case 7: return texture(Texture7, texcoord);
			case 8: return texture(Texture8, texcoord);
			case 9: return texture(Texture9, texcoord);
			case 10: return texture(Texture10, texcoord);
			case 11: return texture(Texture11, texcoord);
			case 12: return texture(Texture12, texcoord);
			case 13: return texture(Texture13, texcoord);
			case 14: return texture(Texture14, texcoord);
			case 15: return texture(Texture15, texcoord);
			default: return vec4(1.0, 1.0, 1.0, 1.0);
			}
		}

		void main()
		{
			gl_FragColor = SampleTexture(texindex) * color;
		}
	)";


    StandardProgram::StandardProgram()
    {
        Program* program = nullptr;

        /* 颜色着色器 */
        program = Program::CreateProgramWithSource(Color_Vertex, Color_Fragment);
        program->SetVertexAttributes<ColorVertexFormat>(0, struct_offset(ColorVertexFormat, position));
        program->SetVertexAttributes<ColorVertexFormat>(1, struct_offset(ColorVertexFormat, color));
        vStandardPrograms[StandardProgramType::SPT_Color] = program;

        /* 精灵着色器 */
        program = Program::CreateProgramWithSource(Sprite_Vertex, Sprite_Fragment);
        program->SetVertexAttributes<SpriteVertexFormat>(0, struct_offset(SpriteVertexFormat, position));
        program->SetVertexAttributes<SpriteVertexFormat>(1, struct_offset(SpriteVertexFormat, texcoord));
        program->SetVertexAttributes<SpriteVertexFormat>(2, struct_offset(SpriteVertexFormat, color));
        program->SetVertexAttributes<SpriteVertexFormat>(3, struct_offset(SpriteVertexFormat, texindex));
        vStandardPrograms[StandardProgramType::SPT_Sprite] = program;

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
    }

    StandardProgram::~StandardProgram()
    {
        delete vStandardPrograms[SPT_Color];
        delete vStandardPrograms[SPT_Sprite];
        delete vStandardPrograms[SPT_Particle];
    }

    Program* StandardProgram::GetProgram(StandardProgramType type)
    {
        return vStandardPrograms[type];
    }
}