#include "Animation.h"
#include "Shaders.h"
#include "Models.h"
#include "Camera.h"
#include "Texture.h"

Animation::Animation(std::shared_ptr<Models> model, std::shared_ptr<Shaders> shader, std::shared_ptr<Texture> texture,int numFrames, float frameTime,int type,int numLines):Sprite2D(model,shader,texture), m_numFrames(numFrames),m_frameTime(frameTime),m_currentFrame(0),m_currentTime(0.0f),m_typeAnim(type),m_currentLine(numLines-1),m_numLines(numLines),m_isExist(true),m_isProtected(false)
{
}
void Animation::Init()
{
	Sprite2D::Init();
}
void Animation::Draw()
{

	if (isPlayer)
	{
		if (m_isProtected&&m_currentTime < m_frameTime / 2)
		{
			// not draw
			return;
		}
		else
		{
			
		}
	}
	glUseProgram(m_pShader->program);
	glBindBuffer(GL_ARRAY_BUFFER, m_pModel->GetVertexObject());
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_pModel->GetIndiceObject());

	GLuint iTempShaderVaribleGLID = -1;
	Matrix matrixWVP;

	matrixWVP = m_WorldMat;//* m_pCamera->GetLookAtCamera();

	if (m_pTexture != nullptr)
	{
		glActiveTexture(GL_TEXTURE0);
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, m_pTexture->Get2DTextureAdd());
		if (m_pShader->iTextureLoc[0] != -1)
			glUniform1i(m_pShader->iTextureLoc[0], 0);
	}
	


	iTempShaderVaribleGLID = -1;
	iTempShaderVaribleGLID = m_pShader->GetAttribLocation((char*)"a_posL");
	if (iTempShaderVaribleGLID != -1)
	{
		glEnableVertexAttribArray(iTempShaderVaribleGLID);
		glVertexAttribPointer(iTempShaderVaribleGLID, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), VETEX_POSITION);
	}

	iTempShaderVaribleGLID = -1;
	iTempShaderVaribleGLID = m_pShader->GetAttribLocation((char*) "a_uv");
	if (iTempShaderVaribleGLID != -1)
	{
		glEnableVertexAttribArray(iTempShaderVaribleGLID);
		glVertexAttribPointer(iTempShaderVaribleGLID, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), VETEX_UV);
	}

	

	iTempShaderVaribleGLID = -1;
	iTempShaderVaribleGLID = m_pShader->GetUniformLocation((char*)"u_matMVP");
	if (iTempShaderVaribleGLID != -1)
		glUniformMatrix4fv(iTempShaderVaribleGLID, 1, GL_FALSE, matrixWVP.m[0]);

	iTempShaderVaribleGLID = -1;
	iTempShaderVaribleGLID = m_pShader->GetUniformLocation((char*)"u_numFrames");
	if (iTempShaderVaribleGLID != -1)
	{
		glUniform1f(iTempShaderVaribleGLID, m_numFrames);
	}
	iTempShaderVaribleGLID = -1;
	iTempShaderVaribleGLID = m_pShader->GetUniformLocation((char*)"u_currentFrame");
	if (iTempShaderVaribleGLID != -1)
	{
		glUniform1f(iTempShaderVaribleGLID, m_currentFrame);
	}
	iTempShaderVaribleGLID = -1;
	iTempShaderVaribleGLID = m_pShader->GetUniformLocation((char*)"u_numLines");
	if (iTempShaderVaribleGLID != -1)
	{
		glUniform1f(iTempShaderVaribleGLID, m_numLines);
	}
	iTempShaderVaribleGLID = -1;
	iTempShaderVaribleGLID = m_pShader->GetUniformLocation((char*)"u_currentLine");
	if (iTempShaderVaribleGLID != -1)
	{
		glUniform1f(iTempShaderVaribleGLID, m_currentLine);
	}



	glDrawElements(GL_TRIANGLES, m_pModel->GetNumIndiceObject(), GL_UNSIGNED_INT, 0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindTexture(GL_TEXTURE_2D, 0);
}
void Animation::Update(GLfloat deltatime)
{
	
	if (m_typeAnim != TYPE_SPRITE) {
		
		m_currentTime += deltatime;
		if (m_currentTime >= m_frameTime) {

			m_currentFrame += 1;
			if (m_currentFrame == m_numFrames) 
			{
				if (m_typeAnim == TYPE_LOOP) 
				{
					m_currentFrame = 0;
				}
				if (m_typeAnim == TYPE_NORMAL)
				{
					m_isExist = false;
				}
				
			}
			m_currentTime -= m_frameTime;

		}
	}
	else {
		m_currentTime += deltatime;
		if (m_currentTime >= m_frameTime) 
		{
			m_currentTime -= m_frameTime;
		}

	}
}
void Animation::ChangedLine(int line) 
{
	m_currentLine = line;
}
void Animation::ChangedType(int type) 
{
	m_typeAnim = type;
}
void Animation::StopAnim()
{
	m_currentFrame = 0;
}