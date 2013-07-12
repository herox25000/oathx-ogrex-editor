#pragma once

#include "OpenGL.h"
#include "GLTexture.h"
#include "OpenglEngineHead.h"

#define	MAX_PARTICLES	500					// ��������������
struct	stuParticles						// �����������ݽṹ
{
	GLboolean	active;						// �Ƿ񼤻�
	GLfloat		life;						// ��������
	GLfloat		fade;						// ˥���ٶ�

	GLfloat		r;							// ��ɫֵ
	GLfloat		g;							// ��ɫֵ
	GLfloat		b;							// ��ɫֵ

	GLfloat		x;							// X λ��
	GLfloat		y;							// Y λ��

	GLfloat		xi;							// X ����
	GLfloat		yi;							// Y ����

	GLfloat		xg;							// X �����������ٶ�
	GLfloat		yg;							// Y �����������ٶ�

};											// �������ݽṹ



class OPENGL_ENGINE_CLASS CParticles
{

	GLboolean		m_Rainbow;							// �Ƿ�Ϊ�ʺ�ģʽ
	GLfloat			m_Slowdown;							// ��������
	GLfloat			m_XSpeed;							// X������ٶ�
	GLfloat			m_YSpeed;							// Y������ٶ�
	GLuint			m_Col;								// ��ǰ����ɫ
	GLuint			m_Delay;							// �ʺ�Ч���ӳ�
	stuParticles	m_Particle[MAX_PARTICLES];			// ����1000�����ӵ�����

public:
	static CGLTexture	m_ImageParticle;				// ����


public:
	CParticles(void);
	~CParticles(void);


public:
	GLvoid			DrawParticles(CGLDevice* pOpenGL, INT nXBegan, INT nYBegan, float nXEnd, float nYEnd);
};
