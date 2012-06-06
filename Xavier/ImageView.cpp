#include "stdafx.h"
#include "Xavier.h"
#include "ImageView.h"
#include "GraphDC.h"
#include <atlimage.h>

IMPLEMENT_DYNAMIC(CImageView, CImageListBox)

CImageView::CImageView()
{

}

CImageView::~CImageView()
{
}


BEGIN_MESSAGE_MAP(CImageView, CImageListBox)
	ON_WM_PAINT()
END_MESSAGE_MAP()

#define THUMBNAIL_WIDTH		100
#define THUMBNAIL_HEIGHT	100

/**
 *
 */
void CImageView::OnPaint()
{

}
