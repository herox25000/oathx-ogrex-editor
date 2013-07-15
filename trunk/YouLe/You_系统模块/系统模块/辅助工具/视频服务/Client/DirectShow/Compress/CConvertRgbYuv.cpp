#include "stdafx.h"
#include ".\CConvertRgbYuv.h"

int CConvertRgbYuv::RGB2YUV_YR[256], CConvertRgbYuv::RGB2YUV_YG[256], CConvertRgbYuv::RGB2YUV_YB[256];
int CConvertRgbYuv::RGB2YUV_UR[256], CConvertRgbYuv::RGB2YUV_UG[256], CConvertRgbYuv::RGB2YUV_UBVR[256];
int CConvertRgbYuv::RGB2YUV_VG[256], CConvertRgbYuv::RGB2YUV_VB[256];

long int CConvertRgbYuv::crv_tab[256];
long int CConvertRgbYuv::cbu_tab[256];
long int CConvertRgbYuv::cgu_tab[256];
long int CConvertRgbYuv::cgv_tab[256];
long int CConvertRgbYuv::tab_76309[256];
unsigned char CConvertRgbYuv::clp[1024];	

CConvertRgbYuv::CConvertRgbYuv(void)
{
	InitLookupTable();
	InitConvertTable();
}

CConvertRgbYuv::~CConvertRgbYuv(void)
{
}

void CConvertRgbYuv::InitLookupTable()
{
	int i;
	for (i = 0; i < 256; i++) RGB2YUV_YR[i] = (int)((float)65.481 * (i<<8));
	for (i = 0; i < 256; i++) RGB2YUV_YG[i] = (int)((float)128.553 * (i<<8));
	for (i = 0; i < 256; i++) RGB2YUV_YB[i] = (int)((float)24.966 * (i<<8));
	for (i = 0; i < 256; i++) RGB2YUV_UR[i] = (int)((float)37.797 * (i<<8));
	for (i = 0; i < 256; i++) RGB2YUV_UG[i] = (int)((float)74.203 * (i<<8));
	for (i = 0; i < 256; i++) RGB2YUV_VG[i] = (int)((float)93.786 * (i<<8));
	for (i = 0; i < 256; i++) RGB2YUV_VB[i] = (int)((float)18.214 * (i<<8));
	for (i = 0; i < 256; i++) RGB2YUV_UBVR[i] = (int)((float)112 * (i<<8));
}

void CConvertRgbYuv::RGB24_YUV( int width, int height, unsigned char *pSource,unsigned char *pDest )
{
	unsigned char *u,*v,*y,*uu,*vv;
	unsigned char *pu1,*pu2,*pu3,*pu4;
	unsigned char *pv1,*pv2,*pv3,*pv4;
	unsigned char *r,*g,*b;
	int i,j;

	uu=new unsigned char[width*height];
	if(uu==NULL)
		return;
	vv=new unsigned char[width*height];
	if(vv==NULL)
	{
		delete uu;
		return;
	}

	y=pDest;
	u=uu;
	v=vv;

	// Get r,g,b pointers from bmp image data....
	r=pSource;
	g=pSource+1;
	b=pSource+2;


	//Get YUV values for rgb values...

	for(i=0;i<height;i++)
	{
		for(j=0;j<width;j++)
		{
			*y++=( RGB2YUV_YR[*r]  +RGB2YUV_YG[*g]+RGB2YUV_YB[*b]+1048576)>>16;
			*u++=(-RGB2YUV_UR[*r]  -RGB2YUV_UG[*g]+RGB2YUV_UBVR[*b]+8388608)>>16;
			*v++=( RGB2YUV_UBVR[*r]-RGB2YUV_VG[*g]-RGB2YUV_VB[*b]+8388608)>>16;

			r+=3;
			g+=3;
			b+=3;
		}
	}



	// Now sample the U & V to obtain YUV 4:2:0 format

	// Sampling mechanism...
	/*	  @  ->  Y
	#  ->  U or V

	@   @   @   @
	#       #
	@   @   @   @

	@   @   @   @
	#       #
	@   @   @   @

	*/

	// Get the right pointers...
	u=pDest+width*height;
	v=u+(width*height)/4;

	// For U
	pu1=uu;
	pu2=pu1+1;
	pu3=pu1+width;
	pu4=pu3+1;

	// For V
	pv1=vv;
	pv2=pv1+1;
	pv3=pv1+width;
	pv4=pv3+1;

	// Do sampling....
	for(i=0;i<height;i+=2)
	{

		for(j=0;j<width;j+=2)
		{
			*u++=(*pu1+*pu2+*pu3+*pu4)>>2;
			*v++=(*pv1+*pv2+*pv3+*pv4)>>2;

			pu1+=2;
			pu2+=2;
			pu3+=2;
			pu4+=2;

			pv1+=2;
			pv2+=2;
			pv3+=2;
			pv4+=2;
		}

		pu1+=width;
		pu2+=width;
		pu3+=width;
		pu4+=width;

		pv1+=width;
		pv2+=width;
		pv3+=width;
		pv4+=width;

	}
	delete uu;
	delete vv;
}

//
//Initialize conversion table for YUV420 to RGB
//
void CConvertRgbYuv::InitConvertTable()
{
	long int crv,cbu,cgu,cgv;
	int i,ind;   

	crv = 104597; cbu = 132201; 
	cgu = 25675;  cgv = 53279;

	for (i = 0; i < 256; i++)
	{
		crv_tab[i] = (i-128) * crv;
		cbu_tab[i] = (i-128) * cbu;
		cgu_tab[i] = (i-128) * cgu;
		cgv_tab[i] = (i-128) * cgv;
		tab_76309[i] = 76309*(i-16);
	}

	for (i=0; i<384; i++)
		clp[i] =0;
	ind=384;
	for (i=0;i<256; i++)
		clp[ind++]=i;
	ind=640;
	for (i=0;i<384;i++)
		clp[ind++]=255;
}

void CConvertRgbYuv::YUV_RGB24(unsigned char* pSource, unsigned char *pDest, int width, int height)
{
	int y1,y2,u,v; 
	unsigned char *py1,*py2;
	int i,j, c1, c2, c3, c4;
	unsigned char *d1, *d2;
	unsigned char*src1 = pSource + width * height;
	unsigned char*src2 = src1 + (width * height)/4;

	py1=pSource;
	py2=py1+width;
	d1=pDest;
	d2=d1+3*width;
	for (j = 0; j < height; j += 2)
	{
		for (i = 0; i < width; i += 2)
		{
			u = *src1++;
			v = *src2++;

			c1 = crv_tab[v];
			c2 = cgu_tab[u];
			c3 = cgv_tab[v];
			c4 = cbu_tab[u];

			//up-left
			y1 = tab_76309[*py1++];	
			*d1++ = clp[384+((y1 + c1)>>16)];  
			*d1++ = clp[384+((y1 - c2 - c3)>>16)];
			*d1++ = clp[384+((y1 + c4)>>16)];

			//down-left
			y2 = tab_76309[*py2++];
			*d2++ = clp[384+((y2 + c1)>>16)];  
			*d2++ = clp[384+((y2 - c2 - c3)>>16)];
			*d2++ = clp[384+((y2 + c4)>>16)];

			//up-right
			y1 = tab_76309[*py1++];
			*d1++ = clp[384+((y1 + c1)>>16)];  
			*d1++ = clp[384+((y1 - c2 - c3)>>16)];
			*d1++ = clp[384+((y1 + c4)>>16)];

			//down-right
			y2 = tab_76309[*py2++];
			*d2++ = clp[384+((y2 + c1)>>16)];  
			*d2++ = clp[384+((y2 - c2 - c3)>>16)];
			*d2++ = clp[384+((y2 + c4)>>16)];
		}
		d1 += 3*width;
		d2 += 3*width;
		py1+=   width;
		py2+=   width;
	}
}