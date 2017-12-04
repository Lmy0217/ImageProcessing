
// ImageProcessingDoc.cpp : CImageProcessingDoc 类的实现
//

#include "stdafx.h"

#define BOUNDS_CHECK



// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "ImageProcessing.h"
#endif


#include "ImageProcessingDoc.h"
#include "DialogPowerParameters.h"
#include "DialogScalingFactor.h"
#include "DialogLogParameters.h"
#include "DialogLinearTransform.h"
#include "DialogBitPlane.h"
#include "DialogImageAddRatio.h"
#include "DialogImageRotation.h"
#include "DialogImageMagnifier.h"
#include "GenicAffineTranform.h"
#include "DialogNoiseParameters.h"
#include "DialogFreqFilteringParameters.h"
#include "DialogGaussLowHighPassFiltering.h"
#include "DialogSharpeningParameters.h"
#include "DialogSpatialFiltering.h"
#include "DialogMotionBlurParameters.h"


#include <math.h>
#define  PI  3.14159
#define  RANGE  100
#include <propkey.h>


#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CImageProcessingDoc

IMPLEMENT_DYNCREATE(CImageProcessingDoc, CDocument)

BEGIN_MESSAGE_MAP(CImageProcessingDoc, CDocument)
	ON_COMMAND(ID_FILE_OPEN, &CImageProcessingDoc::OnFileOpen)
	ON_COMMAND(ID_COLORTOGREY, &CImageProcessingDoc::OnColortogrey)
	ON_COMMAND(ID_RGB_RED, &CImageProcessingDoc::OnRgbRed)
	ON_COMMAND(ID_RGB_GREEN, &CImageProcessingDoc::OnRgbGreen)
	ON_COMMAND(ID_RGB_BLUE, &CImageProcessingDoc::OnRgbBlue)
	ON_COMMAND(ID_HSV_HUE, &CImageProcessingDoc::OnHsvHue)
	ON_COMMAND(ID_HSV_SATURATION, &CImageProcessingDoc::OnHsvSaturation)
	ON_COMMAND(ID_HSV_INTENSITY, &CImageProcessingDoc::OnHsvIntensity)
	ON_COMMAND(ID_YCBCR_Y, &CImageProcessingDoc::OnYcbcrY)
	ON_COMMAND(ID_YCBCR_CB, &CImageProcessingDoc::OnYcbcrCb)
	ON_COMMAND(ID_YCBCR_CR, &CImageProcessingDoc::OnYcbcrCr)
	ON_COMMAND(ID_NEAREST_INTERPOLATION_SCALING, &CImageProcessingDoc::OnNearestInterpolationScaling)
	ON_COMMAND(ID_BILINEAR_INTERPOLATION_SCALING, &CImageProcessingDoc::OnBilinearInterpolationScaling)
	ON_COMMAND(ID_COLOR_INVERSION, &CImageProcessingDoc::OnColorInversion)
	ON_COMMAND(ID_FILE_SAVE_AS, &CImageProcessingDoc::OnFileSaveAs)
	ON_COMMAND(ID_DISTOGRAMEQUALIZATION, &CImageProcessingDoc::OnHistogramequalization)
	ON_COMMAND(ID_LOG_TRANSFORM, &CImageProcessingDoc::OnLogTransform)
	ON_COMMAND(ID_POWER_TRANSFORM, &CImageProcessingDoc::OnPowerTransform)
	ON_COMMAND(ID_LINEARFORM, &CImageProcessingDoc::OnLinearform)
	ON_COMMAND(ID_BIT_PLANE, &CImageProcessingDoc::OnBitPlane)
	ON_COMMAND(ID_GREYHISTOGRAM, &CImageProcessingDoc::OnGreyhistogram)
	ON_COMMAND(ID_IMAGE_ADD, &CImageProcessingDoc::OnImageAdd)
	ON_COMMAND(ID_IMAGE_SUB, &CImageProcessingDoc::OnImageSub)
	ON_COMMAND(ID_IMAGE_AND, &CImageProcessingDoc::OnImageAnd)
	ON_COMMAND(ID_IMAGE_OR, &CImageProcessingDoc::OnImageOr)
	ON_COMMAND(ID_IMAGE_MUL, &CImageProcessingDoc::OnImageMul)
	ON_COMMAND(ID_IMAGE_DIV, &CImageProcessingDoc::OnImageDiv)
	ON_COMMAND(ID_IMAGE_ROTATION, &CImageProcessingDoc::OnImageRotation)
	ON_COMMAND(ID_IMAGE_MAGNIFIER, &CImageProcessingDoc::OnImageMagnifier)
	ON_COMMAND(ID_LOCAL_HISTOGRAM_EQUALIZATION, &CImageProcessingDoc::OnLocalHistogramEqualization)
	ON_COMMAND(ID_HISTOGRAM_STATISTICS, &CImageProcessingDoc::OnHistogramStatistics)
	ON_COMMAND(ID_HORI_CONCAVE, &CImageProcessingDoc::OnHoriConcave)
	ON_COMMAND(ID_HORI_CONVEX, &CImageProcessingDoc::OnHoriConvex)
	ON_COMMAND(ID_LADDERTYPE_DEFORMATION, &CImageProcessingDoc::OnLaddertypeDeformation)
	ON_COMMAND(ID_TRIANGLE_DEFORMATION, &CImageProcessingDoc::OnTriangleDeformation)
	ON_COMMAND(ID_STYPE_DEFORMATION, &CImageProcessingDoc::OnStypeDeformation)
	ON_COMMAND(ID_CORRUGATION_DEFORMATION, &CImageProcessingDoc::OnCorrugationDeformation)
	ON_COMMAND(ID_MAGIC_MIRROR_TRANSFORM, &CImageProcessingDoc::OnMagicMirrorTransform)
	ON_COMMAND(ID_GENERAL_AFFINE_TRANSFORM, &CImageProcessingDoc::OnGeneralAffineTransform)
	ON_COMMAND(ID_IMAGE_FAST_FOURIER_TRANSFORM, &CImageProcessingDoc::OnImageFastFourierTransform)
	ON_COMMAND(ID_IMAGE_FAST_FOURIER_TRANSFORM_CENTER, &CImageProcessingDoc::OnImageFastFourierTransformCenter)
	ON_COMMAND(ID_DCT_TRANSFORM, &CImageProcessingDoc::OnDctTransform)
	ON_COMMAND(ID_IDEA_LOW_PASS_FILTERING, &CImageProcessingDoc::OnIdeaLowPassFiltering)
	ON_COMMAND(ID_IDEA_HIGH_PASS_FILTERING, &CImageProcessingDoc::OnIdeaHighPassFiltering)
	ON_COMMAND(ID_FOURIER_TRANSFORM_APPLICATION, &CImageProcessingDoc::OnFourierTransformApplication)
	ON_COMMAND(ID_BUTTERWORTH_LOWPASS_FILTERING, &CImageProcessingDoc::OnButterworthLowpassFiltering)
	ON_COMMAND(ID_BUTTERWORTH_HIGHPASS_FILTERING, &CImageProcessingDoc::OnButterworthHighpassFiltering)
	ON_COMMAND(ID_NOTCH_FILTERING, &CImageProcessingDoc::OnNotchFiltering)
	ON_COMMAND(ID_GAUSS_LOWPASS_FILTERING, &CImageProcessingDoc::OnGaussLowpassFiltering)
	ON_COMMAND(ID_GAUSS_HIGHPASS_FILTERING, &CImageProcessingDoc::OnGaussHighpassFiltering)
	ON_COMMAND(ID_LAPLACIAN_FILTERING, &CImageProcessingDoc::OnLaplacianFiltering)
	ON_COMMAND(ID_SMOOTHING_SPATIA_FILTERING, &CImageProcessingDoc::OnSmoothingSpatiaFiltering)
	ON_COMMAND(ID_SHARPENING_SPATIAL_FILTERING, &CImageProcessingDoc::OnSharpeningSpatialFiltering)
	ON_COMMAND(ID_INVERT_FILTERING_IMAGE_RESTORATION, &CImageProcessingDoc::OnInvertFilteringImageRestoration)
	ON_COMMAND(ID_IMAGE_HORI_MOTION_BLUR, &CImageProcessingDoc::OnImageHoriMotionBlur)
	ON_COMMAND(ID_IMAGE_HORI_MOTION_BLUR_RESTORE, &CImageProcessingDoc::OnImageHoriMotionBlurRestore)
	ON_COMMAND(ID_MOTION_BLUR, &CImageProcessingDoc::OnMotionBlur)
	ON_COMMAND(ID_HOUGH_LINES_DETECT, &CImageProcessingDoc::OnLinesDetect)
	ON_COMMAND(ID_CIRCLES_DETECTION, &CImageProcessingDoc::OnCirclesDetection)
	ON_COMMAND(ID_IMAGE_NOISE_POLLUTION, &CImageProcessingDoc::OnImageNoisePollution)
END_MESSAGE_MAP()


// CImageProcessingDoc 构造/析构

CImageProcessingDoc::CImageProcessingDoc()
{
	// TODO: 在此添加一次性构造代码
}

CImageProcessingDoc::~CImageProcessingDoc()
{

}

BOOL CImageProcessingDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: 在此添加重新初始化代码
	// (SDI 文档将重用该文档)

	return TRUE;
}

// CImageProcessingDoc 序列化
void CImageProcessingDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: 在此添加存储代码
	}
	else
	{
		// TODO: 在此添加加载代码
	}
}

#ifdef SHARED_HANDLERS

// 缩略图的支持
void CImageProcessingDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// 修改此代码以绘制文档数据
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// 搜索处理程序的支持
void CImageProcessingDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// 从文档数据设置搜索内容。
	// 内容部分应由“;”分隔

	// 例如:  strSearchContent = _T("point;rectangle;circle;ole object;")；
	SetSearchContent(strSearchContent);
}

void CImageProcessingDoc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = NULL;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != NULL)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// CImageProcessingDoc 诊断

#ifdef _DEBUG
void CImageProcessingDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CImageProcessingDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

//自定义方法

//求数组中最大值
BYTE CImageProcessingDoc::Maxinum(BYTE * pData, int Num)
{
	BYTE m_max = pData[0];
	for (int i = 0; i < Num; i++)
	{
		if (m_max < pData[i])
			m_max = pData[i];
	}
	return m_max;
}

//求数组中最小值
BYTE CImageProcessingDoc::Mininum(BYTE * pData, int Num)
{
	BYTE m_min = pData[0];
	for (int i = 0; i < Num; i++)
	{
		if (m_min > pData[i])
			m_min = pData[i];
	}
	return m_min;
}

//数组起泡排序
void CImageProcessingDoc::BubbleSort(BYTE * pData, int Num)
{
	int i;
	int j;
	bool sortsucess = false;
	for (i = Num-1; i>=0; i--)
	{
		if (sortsucess)
			break;
		sortsucess = true;
		for (j = 0; j < i;j++)
		{
			if (pData[j]>pData[j+1])
			{
				int temp = pData[j];
				pData[j] = pData[j + 1];
				pData[j + 1] = temp;
				sortsucess = false;
			}
		}
	}
}

//拷贝原始图像红色分量数据
void CImageProcessingDoc::GetRedBitsFromImage(CImage *mImage, BYTE * pAreaBits)
{
	int sWidth = mImage->GetWidth();
	int sHeight = mImage->GetHeight();
	int sRowBytes = mImage->GetPitch();
	BYTE *pBits = (BYTE *)mImage->GetBits();
	int x;
	int y;
	for (y = 0; y < sHeight; y++)
	for (x = 0; x < sWidth;x++)
	{
		pAreaBits[y*sWidth + x] = pBits[y * sRowBytes + 3 * x + 2];
	}
}

//拷贝原始图像绿色分量数据
void CImageProcessingDoc::GetGreenBitsFromImage(CImage *mImage, BYTE * pAreaBits)
{
	int sWidth = mImage->GetWidth();
	int sHeight = mImage->GetHeight();
	int sRowBytes = mImage->GetPitch();
	BYTE *pBits = (BYTE *)mImage->GetBits();
	int x;
	int y;
	for (y = 0; y < sHeight; y++)
	for (x = 0; x < sWidth;x++)
	{
		pAreaBits[y*sWidth + x] = pBits[y * sRowBytes + 3 * x + 1];
	}
}

//拷贝原始图像蓝色分量数据
void CImageProcessingDoc::GetBlueBitsFromImage(CImage *mImage, BYTE * pAreaBits)
{
	int sWidth = mImage->GetWidth();
	int sHeight = mImage->GetHeight();
	int sRowBytes = mImage->GetPitch();
	BYTE *pBits = (BYTE *)mImage->GetBits();
	int x;
	int y;
	for (y = 0; y < sHeight; y++)
	for (x = 0; x < sWidth;x++)
	{
		pAreaBits[y*sWidth + x] = pBits[y * sRowBytes + 3 * x + 0];
	}
}

//拷贝原始图像灰度图像数据
void CImageProcessingDoc::GetGreyBitsFromImage(CImage *mImage, BYTE * pAreaBits)
{
	int sWidth = mImage->GetWidth();
	int sHeight = mImage->GetHeight();
	int sRowBytes = mImage->GetPitch();
	BYTE *pBits = (BYTE *)mImage->GetBits();
	int x;
	int y;
	for (y = 0; y < sHeight; y++)
	for (x = 0; x < sWidth;x++)
	{
		pAreaBits[y*sWidth + x] = (int)(0.299*pBits[y * sRowBytes + 3 * x + 2] + 0.587*pBits[y * sRowBytes + 3 * x + 1] + 0.114 *pBits[y * sRowBytes + 3 * x + 0]);
	}
}

//拷贝原始图像以(x,y)为中心高为(2m+1)和宽为(2n+1)的矩形窗口RGB数据
void CImageProcessingDoc::CopyAreaRGBFromImgBits(CImage *mImage, BYTE * pAreaBits, int x, int y, int m,int n)
{
	int sWidth = mImage->GetWidth();
	int sHeight = mImage->GetHeight();
	int sRowBytes = mImage->GetPitch();
	BYTE *pBits = (BYTE *)mImage->GetBits();
	int j;
	int i;
	int linebytes = 3*(2 * n + 1);
	for (j = -m; j <= m; j++)
	for (i = -n; i <= n; i++)
	{
		if ((j + y) < 0 && (i + x) < 0) //左上角出界
		{
			pAreaBits[(j + m)*linebytes + 3 * (i + n) + 0] = pBits[0 * sRowBytes + 3 * 0 + 0];
			pAreaBits[(j + m)*linebytes + 3 * (i + n) + 1] = pBits[0 * sRowBytes + 3 * 0 + 1];
			pAreaBits[(j + m)*linebytes + 3 * (i + n) + 2] = pBits[0 * sRowBytes + 3 * 0 + 2];
		}
		else if ((j + y) < 0 && (i + x) >= sWidth) //右上角出界
		{
			pAreaBits[(j + m)*linebytes + 3 * (i + n) + 0] = pBits[0 * sRowBytes + 3 * (sWidth - 1) + 0];
			pAreaBits[(j + m)*linebytes + 3 * (i + n) + 1] = pBits[0 * sRowBytes + 3 * (sWidth - 1) + 1];
			pAreaBits[(j + m)*linebytes + 3 * (i + n) + 2] = pBits[0 * sRowBytes + 3 * (sWidth - 1) + 2];
		}
		else if ( (j + y) >= sHeight  &&  (i + x) < 0  ) //左下角出界
		{
			pAreaBits[(j + m)*linebytes + 3 * (i + n) + 0] = pBits[(sHeight - 1) * sRowBytes + 3 * 0 + 0];
			pAreaBits[(j + m)*linebytes + 3 * (i + n) + 1] = pBits[(sHeight - 1) * sRowBytes + 3 * 0 + 1];
			pAreaBits[(j + m)*linebytes + 3 * (i + n) + 2] = pBits[(sHeight - 1) * sRowBytes + 3 * 0 + 2];
        }
		else if ((j + y) >= sHeight && (i + x) >= sWidth)  //右下角出界
		{
			pAreaBits[(j + m)*linebytes + 3 * (i + n) + 0] = pBits[(sHeight - 1) * sRowBytes + 3 * (sWidth - 1) + 0];
			pAreaBits[(j + m)*linebytes + 3 * (i + n) + 1] = pBits[(sHeight - 1) * sRowBytes + 3 * (sWidth - 1) + 1];
			pAreaBits[(j + m)*linebytes + 3 * (i + n) + 2] = pBits[(sHeight - 1) * sRowBytes + 3 * (sWidth - 1) + 2];
	    }
		else if ((j + y) < 0)  //上边出界
		{
			pAreaBits[(j + m)*linebytes + 3 * (i + n) + 0] = pBits[0 * sRowBytes + 3 * (x + i) + 0];
			pAreaBits[(j + m)*linebytes + 3 * (i + n) + 1] = pBits[0 * sRowBytes + 3 * (x + i) + 1];
			pAreaBits[(j + m)*linebytes + 3 * (i + n) + 2] = pBits[0 * sRowBytes + 3 * (x + i) + 2];
		}
		else if ((i + x) < 0)  //左边出界
		{
			pAreaBits[(j + m)*linebytes + 3 * (i + n) + 0] = pBits[(y + j) * sRowBytes + 3 * 0 + 0];
			pAreaBits[(j + m)*linebytes + 3 * (i + n) + 1] = pBits[(y + j) * sRowBytes + 3 * 0 + 1];
			pAreaBits[(j + m)*linebytes + 3 * (i + n) + 2] = pBits[(y + j) * sRowBytes + 3 * 0 + 2];
	    }
		else if ((i + x) >= sWidth) //右边出界
		{
			pAreaBits[(j + m)*linebytes + 3 * (i + n) + 0] = pBits[(y + j) * sRowBytes + 3 * (sWidth - 1) + 0];
			pAreaBits[(j + m)*linebytes + 3 * (i + n) + 1] = pBits[(y + j) * sRowBytes + 3 * (sWidth - 1) + 1];
			pAreaBits[(j + m)*linebytes + 3 * (i + n) + 2] = pBits[(y + j) * sRowBytes + 3 * (sWidth - 1) + 2];
		}
		else if ((j + y) >= sHeight) //下边出界
		{
			pAreaBits[(j + m)*linebytes + 3 * (i + n) + 0] = pBits[(sHeight - 1) * sRowBytes + 3 * (x + i) + 0];
			pAreaBits[(j + m)*linebytes + 3 * (i + n) + 1] = pBits[(sHeight - 1) * sRowBytes + 3 * (x + i) + 1];
			pAreaBits[(j + m)*linebytes + 3 * (i + n) + 2] = pBits[(sHeight - 1) * sRowBytes + 3 * (x + i) + 2];

		}
		else    //没有出界
		{
			pAreaBits[(j + m)*linebytes + 3 * (i + n) + 0] = pBits[(y + j) * sRowBytes + 3 * (x + i) + 0];
			pAreaBits[(j + m)*linebytes + 3 * (i + n) + 1] = pBits[(y + j) * sRowBytes + 3 * (x + i) + 1];
			pAreaBits[(j + m)*linebytes + 3 * (i + n) + 2] = pBits[(y + j) * sRowBytes + 3 * (x + i) + 2];
		}
	}
}

//拷贝原始图像以(x,y)为中心高为(2m+1)和宽为(2n+1)的矩形窗口蓝色分量数据
void CImageProcessingDoc::CopyAreaBlueFromImgBits(CImage *mImage, BYTE * pAreaBits, int x, int y, int m,int n)
{
	int sWidth = mImage->GetWidth();
	int sHeight = mImage->GetHeight();
	int sRowBytes = mImage->GetPitch();
	BYTE *pBits = (BYTE *)mImage->GetBits();
	int j;
	int i;
	int linebytes = 2 * n + 1;
	for (j = -m; j <= m; j++)
	for (i = -n; i <= n; i++)
	{
		if ((j + y) < 0 && (i + x) < 0) //左上角出界
		{
			pAreaBits[(j + m)*linebytes + (i + n)] = pBits[0 * sRowBytes + 3 * 0 + 0];
		}
		else if ((j + y) < 0 && (i + x) >= sWidth) //右上角出界
		{
			pAreaBits[(j + m)*linebytes + (i + n)] = pBits[0 * sRowBytes + 3 * (sWidth - 1) + 0];
		}
		else if ( (j + y) >= sHeight  &&  (i + x) < 0  ) //左下角出界
		{
			pAreaBits[(j + m)*linebytes + (i + n)] = pBits[(sHeight - 1) * sRowBytes + 3 * 0 + 0];
        }
		else if ((j + y) >= sHeight && (i + x) >= sWidth)  //右下角出界
		{
			pAreaBits[(j + m)*linebytes + (i + n)] = pBits[(sHeight - 1) * sRowBytes + 3 * (sWidth - 1) + 0];
	    }
		else if ((j + y) < 0)  //上边出界
		{
			pAreaBits[(j + m)*linebytes + (i + n)] = pBits[0 * sRowBytes + 3 * (x + i) + 0];
		}
		else if ((i + x) < 0)  //左边出界
		{
			pAreaBits[(j + m)*linebytes + (i + n)] = pBits[(y + j) * sRowBytes + 3 * 0 + 0];
	    }
		else if ((i + x) >= sWidth) //右边出界
		{
			pAreaBits[(j + m)*linebytes + (i + n)] = pBits[(y + j) * sRowBytes + 3 * (sWidth - 1) + 0];
		}
		else if ((j + y) >= sHeight) //下边出界
		{
			pAreaBits[(j + m)*linebytes + (i + n)] = pBits[(sHeight - 1) * sRowBytes + 3 * (x + i) + 0];
		}
		else    //没有出界
		{
			pAreaBits[(j + m)*linebytes + (i + n)] = pBits[(y + j) * sRowBytes + 3 * (x + i) + 0];
		}
	}
}

//拷贝原始图像以(x,y)为中心高为(2m+1)和宽为(2n+1)的矩形窗口绿色分量数据
void CImageProcessingDoc::CopyAreaGreenFromImgBits(CImage *mImage, BYTE * pAreaBits, int x, int y, int m,int n)
{
	int sWidth = mImage->GetWidth();
	int sHeight = mImage->GetHeight();
	int sRowBytes = mImage->GetPitch();
	BYTE *pBits = (BYTE *)mImage->GetBits();
	int j;
	int i;
	int linebytes = 2 * n + 1;
	for (j = -m; j <= m; j++)
	for (i = -n; i <= n; i++)
	{
		if ((j + y) < 0 && (i + x) < 0) //左上角出界
		{
			pAreaBits[(j + m)*linebytes + (i + n)] = pBits[0 * sRowBytes + 3 * 0 + 1];
		}
		else if ((j + y) < 0 && (i + x) >= sWidth) //右上角出界
		{
			pAreaBits[(j + m)*linebytes + (i + n)] = pBits[0 * sRowBytes + 3 * (sWidth - 1) + 1];
		}
		else if ( (j + y) >= sHeight  &&  (i + x) < 0  ) //左下角出界
		{
			pAreaBits[(j + m)*linebytes + (i + n)] = pBits[(sHeight - 1) * sRowBytes + 3 * 0 + 1];
        }
		else if ((j + y) >= sHeight && (i + x) >= sWidth)  //右下角出界
		{
			pAreaBits[(j + m)*linebytes + (i + n)] = pBits[(sHeight - 1) * sRowBytes + 3 * (sWidth - 1) + 1];
	    }
		else if ((j + y) < 0)  //上边出界
		{
			pAreaBits[(j + m)*linebytes + (i + n)] = pBits[0 * sRowBytes + 3 * (x + i) + 1];
		}
		else if ((i + x) < 0)  //左边出界
		{
			pAreaBits[(j + m)*linebytes + (i + n)] = pBits[(y + j) * sRowBytes + 3 * 0 + 1];
	    }
		else if ((i + x) >= sWidth) //右边出界
		{
			pAreaBits[(j + m)*linebytes + (i + n)] = pBits[(y + j) * sRowBytes + 3 * (sWidth - 1) + 1];
		}
		else if ((j + y) >= sHeight) //下边出界
		{
			pAreaBits[(j + m)*linebytes + (i + n)] = pBits[(sHeight - 1) * sRowBytes + 3 * (x + i) + 1];
		}
		else    //没有出界
		{
			pAreaBits[(j + m)*linebytes + (i + n)] = pBits[(y + j) * sRowBytes + 3 * (x + i) + 1];
		}
	}
}

//拷贝原始图像以(x,y)为中心高为(2m+1)和宽为(2n+1)的矩形窗口红色分量数据
void CImageProcessingDoc::CopyAreaRedFromImgBits(CImage *mImage, BYTE * pAreaBits, int x, int y, int m,int n)
{
	int sWidth = mImage->GetWidth();
	int sHeight = mImage->GetHeight();
	int sRowBytes = mImage->GetPitch();
	BYTE *pBits = (BYTE *)mImage->GetBits();
	int j;
	int i;
	int linebytes = 2 * n + 1;
	for (j = -m; j <= m; j++)
	for (i = -n; i <= n; i++)
	{
		if ((j + y) < 0 && (i + x) < 0) //左上角出界
		{
			pAreaBits[(j + m)*linebytes + (i + n)] = pBits[0 * sRowBytes + 3 * 0 + 2];
		}
		else if ((j + y) < 0 && (i + x) >= sWidth) //右上角出界
		{
			pAreaBits[(j + m)*linebytes + (i + n)] = pBits[0 * sRowBytes + 3 * (sWidth - 1) + 2];
		}
		else if ( (j + y) >= sHeight  &&  (i + x) < 0  ) //左下角出界
		{
			pAreaBits[(j + m)*linebytes + (i + n)] = pBits[(sHeight - 1) * sRowBytes + 3 * 0 + 2];
        }
		else if ((j + y) >= sHeight && (i + x) >= sWidth)  //右下角出界
		{
			pAreaBits[(j + m)*linebytes + (i + n)] = pBits[(sHeight - 1) * sRowBytes + 3 * (sWidth - 1) + 2];
	    }
		else if ((j + y) < 0)  //上边出界
		{
			pAreaBits[(j + m)*linebytes + (i + n)] = pBits[0 * sRowBytes + 3 * (x + i) + 2];
		}
		else if ((i + x) < 0)  //左边出界
		{
			pAreaBits[(j + m)*linebytes + (i + n)] = pBits[(y + j) * sRowBytes + 3 * 0 + 2];
	    }
		else if ((i + x) >= sWidth) //右边出界
		{
			pAreaBits[(j + m)*linebytes + (i + n)] = pBits[(y + j) * sRowBytes + 3 * (sWidth - 1) + 2];
		}
		else if ((j + y) >= sHeight) //下边出界
		{
			pAreaBits[(j + m)*linebytes + (i + n)] = pBits[(sHeight - 1) * sRowBytes + 3 * (x + i) + 2];
		}
		else    //没有出界
		{
			pAreaBits[(j + m)*linebytes + (i + n)] = pBits[(y + j) * sRowBytes + 3 * (x + i) + 2];
		}
	}
}

//均值算子
void CImageProcessingDoc::MeanOperator(CImage * pSrcImage, CImage * pDstImage, int m, int n)
{
	int x;
	int y;
	int mWidth  = pSrcImage->GetWidth();
	int mHeight = pSrcImage->GetHeight();
	int mRowBytes = pSrcImage->GetPitch();
	BYTE *rImageData = (BYTE *)pDstImage->GetBits();

	double sumB;
	double sumG;
	double sumR;
	int    nums = (2 * m + 1)*(2 * n + 1);
	BYTE * pData = NULL;
	pData = new BYTE[3 * nums];
	int lineBytes = 3 * (2 * n + 1);

	for (y = 0; y < mHeight; y++)
	for (x = 0; x < mWidth; x++)
	{
		CopyAreaRGBFromImgBits(pSrcImage, pData, x, y, m, n);
		sumB = sumG = sumR = 0;
		for (int j = -m; j <= m; j++)
		for (int i = -n; i <= n; i++)
		{
			sumB += pData[(j + m)*lineBytes + (i + n) * 3 + 0];
			sumG += pData[(j + m)*lineBytes + (i + n) * 3 + 1];
			sumR += pData[(j + m)*lineBytes + (i + n) * 3 + 2];
		}
		rImageData[y*mRowBytes + x * 3] = (int)(sumB/nums);
		rImageData[y*mRowBytes + x * 3 + 1] = (int)(sumG / nums);
   		rImageData[y*mRowBytes + x * 3 + 2] = (int)(sumR / nums);
	}

	if (pData)
		delete[] pData;
	pData = NULL;
}


//高斯算子
void CImageProcessingDoc::GaussOperator(CImage * pSrcImage, CImage * pDstImage, int m, int n, double sigma)
{
	int x;
	int y;
	int i;
	int j;
	int mWidth  = pSrcImage->GetWidth();
	int mHeight = pSrcImage->GetHeight();
	int mRowBytes = pSrcImage->GetPitch();
	BYTE *rImageData = (BYTE *)pDstImage->GetBits();

	double sumB;
	double sumG;
	double sumR;
	int    nums = (2 * m + 1)*(2 * n + 1);
	BYTE * pData = NULL;
	pData = new BYTE[3 * nums];
	int lineBytes = 3 * (2 * n + 1);

    sigma = 2 * sigma*sigma;
    int masklines = 2 * n + 1;
	double *pMask = NULL;
	pMask = new double[nums];


    //计算高斯模板参数
    double sum = 0.0;

    for (j = -m; j <= m; j++)
    for (i = -n; i <= n; i++)
    {
	    pMask[(j + m) * masklines + i + n] = exp(-(i*i + j*j) / sigma);
	    sum += pMask[(j + m) * masklines + i + n];
    }

    for (j = -m; j <= m; j++)
    for (i = -n; i <= n; i++)
	   pMask[(j + m) * masklines + i + n] /= sum;

	for (y = 0; y < mHeight; y++)
	for (x = 0; x < mWidth; x++)
	{
		CopyAreaRGBFromImgBits(pSrcImage, pData, x, y, m, n);
		sumB = sumG = sumR = 0;
		for (int j = -m; j <= m; j++)
		for (int i = -n; i <= n; i++)
		{
			sumB += pData[(j + m)*lineBytes + (i + n) * 3 + 0] * pMask[(j + m) * masklines + i + n];
			sumG += pData[(j + m)*lineBytes + (i + n) * 3 + 1] * pMask[(j + m) * masklines + i + n];
			sumR += pData[(j + m)*lineBytes + (i + n) * 3 + 2] * pMask[(j + m) * masklines + i + n];
		}
		rImageData[y*mRowBytes + x * 3] = (int)sumB;
		rImageData[y*mRowBytes + x * 3 + 1] = (int)sumG;
   		rImageData[y*mRowBytes + x * 3 + 2] = (int)sumR;
	}

    if (pMask)
    delete[] pData;
    pData = NULL;
	if (pData)
		delete[] pMask;
	pMask = NULL;
}

void CImageProcessingDoc::ImageZoomExtend(LPBYTE pSrcData, LPBYTE pDstData, int nHeight, int nWidth, int nYRadius, int nXRadius)
{
	//原始图像数据拷贝的扩充区域
	int x;
	int y;

	int lsHeight = nHeight + 2 * nYRadius;  //扩充图像高度
	int lsWidth  = nWidth  + 2 * nXRadius;  //扩充图像宽度

	for (y = 0; y < lsHeight; y++)
	for (x = 0; x < lsWidth; x++)
	{
		if (y < nYRadius && x < nXRadius)  //左上角
		{
			pDstData[y * lsWidth + x ] = pSrcData[0*nWidth + 0];
		}
		else if (y >= (nYRadius + nHeight) && x >= (nXRadius + nWidth)) //右下角
		{
			pDstData[y  * lsWidth + x] = pSrcData[(nHeight-1)*nWidth + (nWidth-1)];
		}
		else if (y < nYRadius && x >= (nXRadius + nWidth))  //左下角
		{
			pDstData[y * lsWidth + x] = pSrcData[(nHeight - 1)*nWidth + 0];
		}
		else if (y >= (nYRadius + nHeight) && x < nXRadius) //右上角
		{
			pDstData[y * lsWidth + x] = pSrcData[0*nWidth + (nWidth -1)];
		}
		else if (y < nYRadius) //上边
		{
			pDstData[y * lsWidth + x] = pSrcData[0 * nWidth + (x-nXRadius) ];
		}
		else if (x < nXRadius) //左边
		{
			pDstData[y * lsWidth + x] = pSrcData[(y-nYRadius) * nWidth + 0];
		}
		else if (x >= (nXRadius + nWidth)) //右边
		{
			pDstData[y * lsWidth + x] = pSrcData[(y-nYRadius) * nWidth + (nWidth -1)];
		}
		else if (y >= (nYRadius + nHeight)) //下边
		{
			pDstData[y * lsWidth + x] = pSrcData[(nHeight-1) * nWidth + (x-nXRadius)];
		}
		else  //中心区域
		{
			pDstData[y * lsWidth + x] = pSrcData[(y-nYRadius) * nWidth + (x - nXRadius)];
		}
	}
}

//
void  CImageProcessingDoc::CreatMedianLink(LPMEDIANLINK &psrclink,LPMEDIANLINK &pdstlink)
{

	LPMEDIANLINK p;
	LPMEDIANLINK q;
	LPMEDIANLINK s;
	if (!psrclink)
	{
		pdstlink = NULL;
		return;
	}
	p = psrclink;
	bool blinkhead = true;
	while (p)
	{
		if (blinkhead)
		{
			blinkhead = false;
			pdstlink = new MEDIANLINK;
			pdstlink->data = p->data;
			pdstlink->pNext = NULL;
			q = pdstlink;
		}
		else
		{
			s = new MEDIANLINK;
			s->data = p->data;
			s->pNext = NULL;
			q->pNext = s;
			q = q->pNext;
		}
		p = p->pNext;
	}
}

void CImageProcessingDoc::CreatMedianLink(LPMEDIANLINK &plink, LPBYTE pData, int n)
{
	if (n <= 0)
	{
		plink = NULL;
		return;
	}
	LPMEDIANLINK p;
	int i = n - 1;
	plink = new MEDIANLINK;
	plink->data = pData[i];
	plink->pNext = NULL;

	while ( (--i) >=0 )
	{
		p = new MEDIANLINK;
		p->data = pData[i];
		p->pNext = plink;
		plink = p;
	}
}

void CImageProcessingDoc::ClearMedianLink(LPMEDIANLINK &plink)
{
	LPMEDIANLINK p;
	p = plink;
	while (p)
	{
		plink = plink->pNext;
		delete p;
		p = plink;
	}
}



void CImageProcessingDoc::SortMedianLink(LPMEDIANLINK &plink)
{
	//小到大排序链表
	LPMEDIANLINK  p;
	LPMEDIANLINK  q;
	p= plink;
	while (p->pNext)
	{
		q = p->pNext;
		while (q)
		{
			if (p->data > q->data)
			{
				BYTE m_lsbyte = p->data;
				p->data = q->data;
				q->data = m_lsbyte;
			}
			q = q->pNext;
		}
		p = p->pNext;
	}
}

void   CImageProcessingDoc::DeleteElment(LPMEDIANLINK &plink, BYTE nbyte)
{
	LPMEDIANLINK p;
	LPMEDIANLINK q;

	p = plink;
	if (!p)
		return;

	if (p->data == nbyte)
	{
		plink = plink->pNext;
		delete p;
	}
	else
	{
		while (p->pNext)
		{
			q = p->pNext;
			if (q->data == nbyte)
			{
				p->pNext = q->pNext;
				delete q;
				break;
			}
			else
				p = p->pNext;
		}
	}
}

void  CImageProcessingDoc::InsertSortElment(LPMEDIANLINK &plink, BYTE nbyte)
{
	LPMEDIANLINK p;
	LPMEDIANLINK q;
	LPMEDIANLINK s;
	p = plink;
	
	if (nbyte <= p->data)
	{
		q = new MEDIANLINK;
		q->data = nbyte;
		q->pNext = p;
		plink = q;
	}
	else
	{
		while (p->pNext)
		{
			q = p->pNext;
			if (nbyte < q->data)
			{
				s = new MEDIANLINK;
				s->data = nbyte;
				s->pNext = q;
				p->pNext = s;
				break;
			}
			else
				p = p->pNext;
		}

		if (p->pNext == NULL)  //此时数据必须加到最后
		{
			s = new MEDIANLINK;
			s->data = nbyte;
			s->pNext = NULL;
			p->pNext = s;
		}
	}
}

BYTE  CImageProcessingDoc::GetElment(LPMEDIANLINK plink, int n)
{
	LPMEDIANLINK p = plink;
	int i = 0;
	while (i < n)
	{
		p = p->pNext;
		i++;
	}
	return p->data;
}




//中值算子
void CImageProcessingDoc::MedianOperator(CImage * pSrcImage, CImage * pDstImage, int m, int n)
{
	int x;
	int y;
	int mWidth  = pSrcImage->GetWidth();
	int mHeight = pSrcImage->GetHeight();
	int mRowBytes = pSrcImage->GetPitch();
	BYTE *rImageData = (BYTE *)pDstImage->GetBits();

	int    nums = (2 * m + 1)*(2 * n + 1);
	BYTE * pData = NULL;
	pData = new BYTE[nums];

	for (y = 0; y < mHeight; y++)
	for (x = 0; x < mWidth; x++)
	{
		CopyAreaBlueFromImgBits(pSrcImage, pData, x, y, m, n);
		BubbleSort(pData, nums);
		rImageData[y*mRowBytes + x * 3] = pData[nums/2];

		CopyAreaGreenFromImgBits(pSrcImage, pData, x, y, m, n);
		BubbleSort(pData, nums);
		rImageData[y*mRowBytes + x * 3 + 1] = pData[nums / 2];

		CopyAreaRedFromImgBits(pSrcImage, pData, x, y, m, n);
		BubbleSort(pData, nums);
   		rImageData[y*mRowBytes + x * 3 + 2] = pData[nums / 2];
	}
	
	if (pData)
		delete[] pData;
	pData = NULL;
}

//最大值算子
void CImageProcessingDoc::MaxinumOperator(CImage * pSrcImage, CImage * pDstImage, int m, int n)
{
	int x;
	int y;
	int mWidth  = pSrcImage->GetWidth();
	int mHeight = pSrcImage->GetHeight();
	int mRowBytes = pSrcImage->GetPitch();
	BYTE *rImageData = (BYTE *)pDstImage->GetBits();

	int    nums = (2 * m + 1)*(2 * n + 1);
	BYTE * pData = NULL;
	pData = new BYTE[nums];

	for (y = 0; y < mHeight; y++)
	for (x = 0; x < mWidth; x++)
	{
		CopyAreaBlueFromImgBits(pSrcImage, pData, x, y, m, n);
		rImageData[y*mRowBytes + x * 3] = Maxinum(pData,nums);

		CopyAreaGreenFromImgBits(pSrcImage, pData, x, y, m, n);
		BubbleSort(pData, nums);
		rImageData[y*mRowBytes + x * 3 + 1] = Maxinum(pData, nums);

		CopyAreaRedFromImgBits(pSrcImage, pData, x, y, m, n);
		BubbleSort(pData, nums);
   		rImageData[y*mRowBytes + x * 3 + 2] = Maxinum(pData, nums);
	}
	
	if (pData)
		delete[] pData;
	pData = NULL;
}

//最小值算子
void CImageProcessingDoc::MininumOperator(CImage * pSrcImage, CImage * pDstImage, int m, int n)
{
	int x;
	int y;
	int mWidth  = pSrcImage->GetWidth();
	int mHeight = pSrcImage->GetHeight();
	int mRowBytes = pSrcImage->GetPitch();
	BYTE *rImageData = (BYTE *)pDstImage->GetBits();

	int    nums = (2 * m + 1)*(2 * n + 1);
	BYTE * pData = NULL;
	pData = new BYTE[nums];

	for (y = 0; y < mHeight; y++)
	for (x = 0; x < mWidth; x++)
	{
		CopyAreaBlueFromImgBits(pSrcImage, pData, x, y, m, n);
		rImageData[y*mRowBytes + x * 3] = Mininum(pData,nums);

		CopyAreaGreenFromImgBits(pSrcImage, pData, x, y, m, n);
		BubbleSort(pData, nums);
		rImageData[y*mRowBytes + x * 3 + 1] = Mininum(pData, nums);

		CopyAreaRedFromImgBits(pSrcImage, pData, x, y, m, n);
		BubbleSort(pData, nums);
   		rImageData[y*mRowBytes + x * 3 + 2] = Mininum(pData, nums);
	}
	
	if (pData)
		delete[] pData;
	pData = NULL;
}

//中点算子
void CImageProcessingDoc::MiddleOperator(CImage * pSrcImage, CImage * pDstImage, int m, int n)
{
	int x;
	int y;
	int mWidth  = pSrcImage->GetWidth();
	int mHeight = pSrcImage->GetHeight();
	int mRowBytes = pSrcImage->GetPitch();
	BYTE *rImageData = (BYTE *)pDstImage->GetBits();

	int    nums = (2 * m + 1)*(2 * n + 1);
	BYTE * pData = NULL;
	pData = new BYTE[nums];

	for (y = 0; y < mHeight; y++)
	for (x = 0; x < mWidth; x++)
	{
		CopyAreaBlueFromImgBits(pSrcImage, pData, x, y, m, n);
		rImageData[y*mRowBytes + x * 3] = (Maxinum(pData,nums) + Mininum(pData,nums))/2;

		CopyAreaGreenFromImgBits(pSrcImage, pData, x, y, m, n);
		BubbleSort(pData, nums);
		rImageData[y*mRowBytes + x * 3 + 1] = (Maxinum(pData, nums) + Mininum(pData, nums)) / 2;

		CopyAreaRedFromImgBits(pSrcImage, pData, x, y, m, n);
		BubbleSort(pData, nums);
   		rImageData[y*mRowBytes + x * 3 + 2] = (Maxinum(pData, nums) + Mininum(pData, nums)) / 2;
	}
	
	if (pData)
		delete[] pData;
	pData = NULL;
}


//梯度算子
void CImageProcessingDoc::GradsOperator(CImage * pSrcImage, CImage * pDstImage, BOOL bCalibration, BOOL bfiltering)
{
	int x;
	int y;
	int dx;
	int dy;

	int mWidth  = pSrcImage->GetWidth();
	int mHeight = pSrcImage->GetHeight();
	int mRowBytes = pSrcImage->GetPitch();
	LPBYTE sImageData = (LPBYTE)pSrcImage->GetBits();
	LPBYTE rImageData = (LPBYTE)pDstImage->GetBits();
	
	int *pData = new int[mHeight*mWidth];
	int m_mmax;
	int m_mmin;
     
	if (bfiltering)
	{
		dx = sImageData[0] - sImageData[3];
		dy = sImageData[0] - sImageData[mRowBytes];
		m_mmax = m_mmin = (int)sqrt(dx*dx + dy*dy);
		for (y = 0; y < mHeight - 1; y++)
			for (x = 0; x < mWidth - 1; x++)
			{
				dx = sImageData[y*mRowBytes + x * 3 + 0] - sImageData[y*mRowBytes + (x + 1) * 3 + 0];
				dy = sImageData[y*mRowBytes + x * 3 + 0] - sImageData[(y + 1)*mRowBytes + x * 3 + 0];
				pData[y*mWidth + x] = (int)(sImageData[y*mRowBytes + x*3] + sqrt(dx*dx + dy*dy) + 0.5);
				if (pData[y*mWidth + x] < m_mmin)
					m_mmin = pData[y*mWidth + x];
				if (pData[y*mWidth + x] > m_mmax)
					m_mmax = pData[y*mWidth + x];
			}
		m_mmax -= m_mmin;
		if (m_mmax)
		{
			for (y = 0; y < mHeight - 1; y++)
				for (x = 0; x < mWidth - 1; x++)
					rImageData[y*mRowBytes + x * 3 + 0] = bCalibration ? ((int)((255.0*pData[y*mWidth + x]) / m_mmax)) : ((pData[y*mWidth + x]>255) ? 255 : ((pData[y*mWidth + x] < 0) ? 0 : pData[y*mWidth + x]));
		}

		dx = sImageData[1] - sImageData[4];
		dy = sImageData[1] - sImageData[mRowBytes + 1];
		m_mmax = m_mmin = (int)sqrt(dx*dx + dy*dy);
		for (y = 0; y < mHeight - 1; y++)
			for (x = 0; x < mWidth - 1; x++)
			{
				dx = sImageData[y*mRowBytes + x * 3 + 1] - sImageData[y*mRowBytes + (x + 1) * 3 + 1];
				dy = sImageData[y*mRowBytes + x * 3 + 1] - sImageData[(y + 1)*mRowBytes + x * 3 + 1];
				pData[y*mWidth + x] = (int)(sImageData[y*mRowBytes + x * 3 + 1] + sqrt(dx*dx + dy*dy) + 0.5);
				if (pData[y*mWidth + x] < m_mmin)
					m_mmin = pData[y*mWidth + x];
				if (pData[y*mWidth + x] > m_mmax)
					m_mmax = pData[y*mWidth + x];
			}
		m_mmax -= m_mmin;
		if (m_mmax)
		{
			for (y = 0; y < mHeight - 1; y++)
				for (x = 0; x < mWidth - 1; x++)
					rImageData[y*mRowBytes + x * 3 + 1] = bCalibration ? ((int)((255.0*pData[y*mWidth + x]) / m_mmax)) : ((pData[y*mWidth + x]>255) ? 255 : ((pData[y*mWidth + x] < 0) ? 0 : pData[y*mWidth + x]));
		}

		dx = sImageData[2] - sImageData[5];
		dy = sImageData[2] - sImageData[mRowBytes + 2];
		m_mmax = m_mmin = (int)sqrt(dx*dx + dy*dy);
		for (y = 0; y < mHeight - 1; y++)
			for (x = 0; x < mWidth - 1; x++)
			{
				dx = sImageData[y*mRowBytes + x * 3 + 2] - sImageData[y*mRowBytes + (x + 1) * 3 + 2];
				dy = sImageData[y*mRowBytes + x * 3 + 2] - sImageData[(y + 1)*mRowBytes + x * 3 + 2];
				pData[y*mWidth + x] = (int)(sImageData[y*mRowBytes + x * 3 + 2] + sqrt(dx*dx + dy*dy) + 0.5);
				if (pData[y*mWidth + x] < m_mmin)
					m_mmin = pData[y*mWidth + x];
				if (pData[y*mWidth + x] > m_mmax)
					m_mmax = pData[y*mWidth + x];
			}
		m_mmax -= m_mmin;
		if (m_mmax)
		{
			for (y = 0; y < mHeight - 1; y++)
				for (x = 0; x < mWidth - 1; x++)
					rImageData[y*mRowBytes + x * 3 + 2] = bCalibration ? ((int)((255.0*pData[y*mWidth + x]) / m_mmax)) : ((pData[y*mWidth + x]>255) ? 255 : ((pData[y*mWidth + x] < 0) ? 0 : pData[y*mWidth + x]));
		}
	}
	else
	{
		dx = sImageData[0] - sImageData[3];
		dy = sImageData[0] - sImageData[mRowBytes];
		m_mmax = m_mmin = (int)sqrt(dx*dx + dy*dy);
		for (y = 0; y < mHeight - 1; y++)
			for (x = 0; x < mWidth - 1; x++)
			{
				dx = sImageData[y*mRowBytes + x * 3 + 0] - sImageData[y*mRowBytes + (x + 1) * 3 + 0];
				dy = sImageData[y*mRowBytes + x * 3 + 0] - sImageData[(y + 1)*mRowBytes + x * 3 + 0];
				pData[y*mWidth + x] = (int)(sqrt(dx*dx + dy*dy) + 0.5);
				if (pData[y*mWidth + x] < m_mmin)
					m_mmin = pData[y*mWidth + x];
				if (pData[y*mWidth + x] > m_mmax)
					m_mmax = pData[y*mWidth + x];
			}
		m_mmax -= m_mmin;
		if (m_mmax)
		{
			for (y = 0; y < mHeight - 1; y++)
				for (x = 0; x < mWidth - 1; x++)
					rImageData[y*mRowBytes + x * 3 + 0] = bCalibration ? ((int)((255.0*pData[y*mWidth + x]) / m_mmax)) : ((pData[y*mWidth + x]>255) ? 255 : ((pData[y*mWidth + x] < 0) ? 0 : pData[y*mWidth + x]));
		}

		dx = sImageData[1] - sImageData[4];
		dy = sImageData[1] - sImageData[mRowBytes + 1];
		m_mmax = m_mmin = (int)sqrt(dx*dx + dy*dy);
		for (y = 0; y < mHeight - 1; y++)
			for (x = 0; x < mWidth - 1; x++)
			{
				dx = sImageData[y*mRowBytes + x * 3 + 1] - sImageData[y*mRowBytes + (x + 1) * 3 + 1];
				dy = sImageData[y*mRowBytes + x * 3 + 1] - sImageData[(y + 1)*mRowBytes + x * 3 + 1];
				pData[y*mWidth + x] = (int)(sqrt(dx*dx + dy*dy) + 0.5);
				if (pData[y*mWidth + x] < m_mmin)
					m_mmin = pData[y*mWidth + x];
				if (pData[y*mWidth + x] > m_mmax)
					m_mmax = pData[y*mWidth + x];
			}
		m_mmax -= m_mmin;
		if (m_mmax)
		{
			for (y = 0; y < mHeight - 1; y++)
				for (x = 0; x < mWidth - 1; x++)
					rImageData[y*mRowBytes + x * 3 + 1] = bCalibration ? ((int)((255.0*pData[y*mWidth + x]) / m_mmax)) : ((pData[y*mWidth + x]>255) ? 255 : ((pData[y*mWidth + x] < 0) ? 0 : pData[y*mWidth + x]));
		}

		dx = sImageData[2] - sImageData[5];
		dy = sImageData[2] - sImageData[mRowBytes + 2];
		m_mmax = m_mmin = (int)sqrt(dx*dx + dy*dy);
		for (y = 0; y < mHeight - 1; y++)
			for (x = 0; x < mWidth - 1; x++)
			{
				dx = sImageData[y*mRowBytes + x * 3 + 2] - sImageData[y*mRowBytes + (x + 1) * 3 + 2];
				dy = sImageData[y*mRowBytes + x * 3 + 2] - sImageData[(y + 1)*mRowBytes + x * 3 + 2];
				pData[y*mWidth + x] = (int)(sqrt(dx*dx + dy*dy) + 0.5);
				if (pData[y*mWidth + x] < m_mmin)
					m_mmin = pData[y*mWidth + x];
				if (pData[y*mWidth + x] > m_mmax)
					m_mmax = pData[y*mWidth + x];
			}
		m_mmax -= m_mmin;
		if (m_mmax)
		{
			for (y = 0; y < mHeight - 1; y++)
				for (x = 0; x < mWidth - 1; x++)
					rImageData[y*mRowBytes + x * 3 + 2] = bCalibration ? ((int)((255.0*pData[y*mWidth + x]) / m_mmax)) : ((pData[y*mWidth + x]>255) ? 255 : ((pData[y*mWidth + x] < 0) ? 0 : pData[y*mWidth + x]));
		}
	}

	delete pData;
}

//罗伯特算子
void CImageProcessingDoc::RobertsOperator(CImage * pSrcImage, CImage * pDstImage, BOOL bCalibration, BOOL bfiltering)
{
	int x;
	int y;
	int dx;
	int dy;

	int mWidth  = pSrcImage->GetWidth();
	int mHeight = pSrcImage->GetHeight();
	int mRowBytes = pSrcImage->GetPitch();
	LPBYTE sImageData = (LPBYTE)pSrcImage->GetBits();
	LPBYTE rImageData = (LPBYTE)pDstImage->GetBits();
	
	int *pData = new int[mHeight*mWidth];
	int m_mmax;
	int m_mmin;

	if (bfiltering)
	{
		dx = sImageData[0] - sImageData[mRowBytes + 3];
		dy = sImageData[mRowBytes] - sImageData[3];
		m_mmax = m_mmin = (int)sqrt(dx*dx + dy*dy);
		for (y = 0; y < mHeight - 1; y++)
			for (x = 0; x < mWidth - 1; x++)
			{
				dx = sImageData[y*mRowBytes + x * 3 + 0] - sImageData[(y + 1)*mRowBytes + (x + 1) * 3 + 0];
				dy = sImageData[(y + 1)*mRowBytes + x * 3 + 0] - sImageData[y*mRowBytes + (x + 1) * 3 + 0];
				pData[y*mWidth + x] = (int)(sImageData[y*mRowBytes + x * 3] + sqrt(dx*dx + dy*dy) + 0.5);
				if (pData[y*mWidth + x] < m_mmin)
					m_mmin = pData[y*mWidth + x];
				if (pData[y*mWidth + x] > m_mmax)
					m_mmax = pData[y*mWidth + x];
			}
		m_mmax -= m_mmin;
		if (m_mmax)
		{
			for (y = 0; y < mHeight - 1; y++)
				for (x = 0; x < mWidth - 1; x++)
					rImageData[y*mRowBytes + x * 3 + 0] = bCalibration ? ((int)((255.0*pData[y*mWidth + x]) / m_mmax)) : ((pData[y*mWidth + x]>255) ? 255 : ((pData[y*mWidth + x] < 0) ? 0 : pData[y*mWidth + x]));
		}

		dx = sImageData[1] - sImageData[mRowBytes + 4];
		dy = sImageData[mRowBytes + 1] - sImageData[4];
		m_mmax = m_mmin = (int)sqrt(dx*dx + dy*dy);
		for (y = 0; y < mHeight - 1; y++)
			for (x = 0; x < mWidth - 1; x++)
			{
				dx = sImageData[y*mRowBytes + x * 3 + 1] - sImageData[(y + 1)*mRowBytes + (x + 1) * 3 + 1];
				dy = sImageData[(y + 1)*mRowBytes + x * 3 + 1] - sImageData[y*mRowBytes + (x + 1) * 3 + 1];
				pData[y*mWidth + x] = (int)(sImageData[y*mRowBytes + x * 3 + 1] + sqrt(dx*dx + dy*dy) + 0.5);
				if (pData[y*mWidth + x] < m_mmin)
					m_mmin = pData[y*mWidth + x];
				if (pData[y*mWidth + x] > m_mmax)
					m_mmax = pData[y*mWidth + x];
			}
		m_mmax -= m_mmin;
		if (m_mmax)
		{
			for (y = 0; y < mHeight - 1; y++)
				for (x = 0; x < mWidth - 1; x++)
					rImageData[y*mRowBytes + x * 3 + 1] = bCalibration ? ((int)((255.0*pData[y*mWidth + x]) / m_mmax)) : ((pData[y*mWidth + x]>255) ? 255 : ((pData[y*mWidth + x] < 0) ? 0 : pData[y*mWidth + x]));
		}

		dx = sImageData[2] - sImageData[5];
		dy = sImageData[2] - sImageData[mRowBytes + 2];
		m_mmax = m_mmin = (int)sqrt(dx*dx + dy*dy);
		for (y = 0; y < mHeight - 1; y++)
			for (x = 0; x < mWidth - 1; x++)
			{
				dx = sImageData[y*mRowBytes + x * 3 + 2] - sImageData[y*mRowBytes + (x + 1) * 3 + 2];
				dy = sImageData[y*mRowBytes + x * 3 + 2] - sImageData[(y + 1)*mRowBytes + x * 3 + 2];
				pData[y*mWidth + x] = (int)(sImageData[y*mRowBytes + x * 3 + 2] + sqrt(dx*dx + dy*dy) + 0.5);
				if (pData[y*mWidth + x] < m_mmin)
					m_mmin = pData[y*mWidth + x];
				if (pData[y*mWidth + x] > m_mmax)
					m_mmax = pData[y*mWidth + x];
			}
		m_mmax -= m_mmin;
		if (m_mmax)
		{
			for (y = 0; y < mHeight - 1; y++)
				for (x = 0; x < mWidth - 1; x++)
					rImageData[y*mRowBytes + x * 3 + 2] = bCalibration ? ((int)((255.0*pData[y*mWidth + x]) / m_mmax)) : ((pData[y*mWidth + x]>255) ? 255 : ((pData[y*mWidth + x] < 0) ? 0 : pData[y*mWidth + x]));
		}
	}
	else
	{
		dx = sImageData[0] - sImageData[mRowBytes + 3];
		dy = sImageData[mRowBytes] - sImageData[3];
		m_mmax = m_mmin = (int)sqrt(dx*dx + dy*dy);
		for (y = 0; y < mHeight - 1; y++)
			for (x = 0; x < mWidth - 1; x++)
			{
				dx = sImageData[y*mRowBytes + x * 3 + 0] - sImageData[(y + 1)*mRowBytes + (x + 1) * 3 + 0];
				dy = sImageData[(y + 1)*mRowBytes + x * 3 + 0] - sImageData[y*mRowBytes + (x + 1) * 3 + 0];
				pData[y*mWidth + x] = (int)(sqrt(dx*dx + dy*dy) + 0.5);
				if (pData[y*mWidth + x] < m_mmin)
					m_mmin = pData[y*mWidth + x];
				if (pData[y*mWidth + x] > m_mmax)
					m_mmax = pData[y*mWidth + x];
			}
		m_mmax -= m_mmin;
		if (m_mmax)
		{
			for (y = 0; y < mHeight - 1; y++)
				for (x = 0; x < mWidth - 1; x++)
					rImageData[y*mRowBytes + x * 3 + 0] = bCalibration ? ((int)((255.0*pData[y*mWidth + x]) / m_mmax)) : ((pData[y*mWidth + x]>255) ? 255 : ((pData[y*mWidth + x] < 0) ? 0 : pData[y*mWidth + x]));
		}

		dx = sImageData[1] - sImageData[mRowBytes + 4];
		dy = sImageData[mRowBytes + 1] - sImageData[4];
		m_mmax = m_mmin = (int)sqrt(dx*dx + dy*dy);
		for (y = 0; y < mHeight - 1; y++)
			for (x = 0; x < mWidth - 1; x++)
			{
				dx = sImageData[y*mRowBytes + x * 3 + 1] - sImageData[(y + 1)*mRowBytes + (x + 1) * 3 + 1];
				dy = sImageData[(y + 1)*mRowBytes + x * 3 + 1] - sImageData[y*mRowBytes + (x + 1) * 3 + 1];
				pData[y*mWidth + x] = (int)(sqrt(dx*dx + dy*dy) + 0.5);
				if (pData[y*mWidth + x] < m_mmin)
					m_mmin = pData[y*mWidth + x];
				if (pData[y*mWidth + x] > m_mmax)
					m_mmax = pData[y*mWidth + x];
			}
		m_mmax -= m_mmin;
		if (m_mmax)
		{
			for (y = 0; y < mHeight - 1; y++)
				for (x = 0; x < mWidth - 1; x++)
					rImageData[y*mRowBytes + x * 3 + 1] = bCalibration ? ((int)((255.0*pData[y*mWidth + x]) / m_mmax)) : ((pData[y*mWidth + x]>255) ? 255 : ((pData[y*mWidth + x] < 0) ? 0 : pData[y*mWidth + x]));
		}

		dx = sImageData[2] - sImageData[5];
		dy = sImageData[2] - sImageData[mRowBytes + 2];
		m_mmax = m_mmin = (int)sqrt(dx*dx + dy*dy);
		for (y = 0; y < mHeight - 1; y++)
			for (x = 0; x < mWidth - 1; x++)
			{
				dx = sImageData[y*mRowBytes + x * 3 + 2] - sImageData[y*mRowBytes + (x + 1) * 3 + 2];
				dy = sImageData[y*mRowBytes + x * 3 + 2] - sImageData[(y + 1)*mRowBytes + x * 3 + 2];
				pData[y*mWidth + x] = (int)(sqrt(dx*dx + dy*dy) + 0.5);
				if (pData[y*mWidth + x] < m_mmin)
					m_mmin = pData[y*mWidth + x];
				if (pData[y*mWidth + x] > m_mmax)
					m_mmax = pData[y*mWidth + x];
			}
		m_mmax -= m_mmin;
		if (m_mmax)
		{
			for (y = 0; y < mHeight - 1; y++)
				for (x = 0; x < mWidth - 1; x++)
					rImageData[y*mRowBytes + x * 3 + 2] = bCalibration ? ((int)((255.0*pData[y*mWidth + x]) / m_mmax)) : ((pData[y*mWidth + x]>255) ? 255 : ((pData[y*mWidth + x] < 0) ? 0 : pData[y*mWidth + x]));
		}
	}

	delete pData;
}

//Sobel算子
void CImageProcessingDoc::SobelOperator(CImage * pSrcImage, CImage * pDstImage, BOOL bCalibration, BOOL bfiltering)
{
	int x;
	int y;
	int dx;
	int dy;
	int mWidth  = pSrcImage->GetWidth();
	int mHeight = pSrcImage->GetHeight();
	int mRowBytes = pSrcImage->GetPitch();
	BYTE *sImageData = (BYTE *)pSrcImage->GetBits();
	BYTE *rImageData = (BYTE *)pDstImage->GetBits();

	int *pData = new int[mHeight*mWidth];
	int m_mmax;
	int m_mmin;

	if (bfiltering)
	{
		//蓝色
		for (y = 1; y < mHeight - 1; y++)
			for (x = 1; x < mWidth - 1; x++)
			{
				dx = sImageData[(y - 1)*mRowBytes + (x - 1) * 3 + 0] - sImageData[(y + 1)*mRowBytes + (x - 1) * 3 + 0]
					+ 2 * (sImageData[(y - 1)*mRowBytes + x * 3 + 0] - sImageData[(y + 1)*mRowBytes + x * 3 + 0])
					+ sImageData[(y - 1)*mRowBytes + (x + 1) * 3 + 0] - sImageData[(y + 1)*mRowBytes + (x + 1) * 3 + 0];
				dy = sImageData[(y - 1)*mRowBytes + (x - 1) * 3 + 0] - sImageData[(y - 1)*mRowBytes + (x + 1) * 3 + 0]
					+ 2 * (sImageData[y*mRowBytes + (x - 1) * 3 + 0] - sImageData[y*mRowBytes + (x - 1) * 3 + 0])
					+ sImageData[(y + 1)*mRowBytes + (x - 1) * 3 + 0] - sImageData[(y + 1)*mRowBytes + (x + 1) * 3 + 0];
				pData[y*mWidth + x] = (int)(sImageData[y*mRowBytes + x*3] + sqrt(dx*dx + dy*dy) + 0.5);
			}

		m_mmax = m_mmin = pData[0];
		for (y = 1; y < mHeight - 1; y++)
			for (x = 1; x < mWidth - 1; x++)
			{
				if (pData[y*mWidth + x] > m_mmax)
					m_mmax = pData[y*mWidth + x];
				if (pData[y*mWidth + x] < m_mmin)
					m_mmin = pData[y*mWidth + x];
			}

		m_mmax -= m_mmin;
		if (m_mmax)
		{
			for (y = 0; y < mHeight - 1; y++)
				for (x = 0; x < mWidth - 1; x++)
					rImageData[y*mRowBytes + x * 3 + 0] = bCalibration ? ((int)((255.0*pData[y*mWidth + x]) / m_mmax)) : ((pData[y*mWidth + x]>255) ? 255 : ((pData[y*mWidth + x] < 0) ? 0 : pData[y*mWidth + x]));
		}

		//绿色
		for (y = 1; y < mHeight - 1; y++)
			for (x = 1; x < mWidth - 1; x++)
			{
				dx = sImageData[(y - 1)*mRowBytes + (x - 1) * 3 + 1] - sImageData[(y + 1)*mRowBytes + (x - 1) * 3 + 1]
					+ 2 * (sImageData[(y - 1)*mRowBytes + x * 3 + 1] - sImageData[(y + 1)*mRowBytes + x * 3 + 1])
					+ sImageData[(y - 1)*mRowBytes + (x + 1) * 3 + 1] - sImageData[(y + 1)*mRowBytes + (x + 1) * 3 + 1];
				dy = sImageData[(y - 1)*mRowBytes + (x - 1) * 3 + 1] - sImageData[(y - 1)*mRowBytes + (x + 1) * 3 + 1]
					+ 2 * (sImageData[y*mRowBytes + (x - 1) * 3 + 1] - sImageData[y*mRowBytes + (x - 1) * 3 + 1])
					+ sImageData[(y + 1)*mRowBytes + (x - 1) * 3 + 1] - sImageData[(y + 1)*mRowBytes + (x + 1) * 3 + 1];
				pData[y*mWidth + x] = (int)(sImageData[y*mRowBytes + x * 3 + 1] + sqrt(dx*dx + dy*dy) + 0.5);
			}

		m_mmax = m_mmin = pData[0];
		for (y = 1; y < mHeight - 1; y++)
			for (x = 1; x < mWidth - 1; x++)
			{
				if (pData[y*mWidth + x] > m_mmax)
					m_mmax = pData[y*mWidth + x];
				if (pData[y*mWidth + x] < m_mmin)
					m_mmin = pData[y*mWidth + x];
			}

		m_mmax -= m_mmin;
		if (m_mmax)
		{
			for (y = 0; y < mHeight - 1; y++)
				for (x = 0; x < mWidth - 1; x++)
					rImageData[y*mRowBytes + x * 3 + 1] = bCalibration ? ((int)((255.0*pData[y*mWidth + x]) / m_mmax)) : ((pData[y*mWidth + x]>255) ? 255 : ((pData[y*mWidth + x] < 0) ? 0 : pData[y*mWidth + x]));
		}

		//红色
		for (y = 1; y < mHeight - 1; y++)
			for (x = 1; x < mWidth - 1; x++)
			{
				dx = sImageData[(y - 1)*mRowBytes + (x - 1) * 3 + 2] - sImageData[(y + 1)*mRowBytes + (x - 1) * 3 + 2]
					+ 2 * (sImageData[(y - 1)*mRowBytes + x * 3 + 2] - sImageData[(y + 1)*mRowBytes + x * 3 + 2])
					+ sImageData[(y - 1)*mRowBytes + (x + 1) * 3 + 2] - sImageData[(y + 1)*mRowBytes + (x + 1) * 3 + 2];
				dy = sImageData[(y - 1)*mRowBytes + (x - 1) * 3 + 2] - sImageData[(y - 1)*mRowBytes + (x + 1) * 3 + 2]
					+ 2 * (sImageData[y*mRowBytes + (x - 1) * 3 + 2] - sImageData[y*mRowBytes + (x - 1) * 3 + 2])
					+ sImageData[(y + 1)*mRowBytes + (x - 1) * 3 + 2] - sImageData[(y + 1)*mRowBytes + (x + 1) * 3 + 2];
				pData[y*mWidth + x] = (int)(sImageData[y*mRowBytes + x * 3 + 2] + sqrt(dx*dx + dy*dy) + 0.5);
			}

		m_mmax = m_mmin = pData[0];
		for (y = 1; y < mHeight - 1; y++)
			for (x = 1; x < mWidth - 1; x++)
			{
				if (pData[y*mWidth + x] > m_mmax)
					m_mmax = pData[y*mWidth + x];
				if (pData[y*mWidth + x] < m_mmin)
					m_mmin = pData[y*mWidth + x];
			}

		m_mmax -= m_mmin;
		if (m_mmax)
		{
			for (y = 0; y < mHeight - 1; y++)
				for (x = 0; x < mWidth - 1; x++)
					rImageData[y*mRowBytes + x * 3 + 2] = bCalibration ? ((int)((255.0*pData[y*mWidth + x]) / m_mmax)) : ((pData[y*mWidth + x]>255) ? 255 : ((pData[y*mWidth + x] < 0) ? 0 : pData[y*mWidth + x]));
		}
	}
	else
	{
		//蓝色
		for (y = 1; y < mHeight - 1; y++)
			for (x = 1; x < mWidth - 1; x++)
			{
				dx = sImageData[(y - 1)*mRowBytes + (x - 1) * 3 + 0] - sImageData[(y + 1)*mRowBytes + (x - 1) * 3 + 0]
					+ 2 * (sImageData[(y - 1)*mRowBytes + x * 3 + 0] - sImageData[(y + 1)*mRowBytes + x * 3 + 0])
					+ sImageData[(y - 1)*mRowBytes + (x + 1) * 3 + 0] - sImageData[(y + 1)*mRowBytes + (x + 1) * 3 + 0];
				dy = sImageData[(y - 1)*mRowBytes + (x - 1) * 3 + 0] - sImageData[(y - 1)*mRowBytes + (x + 1) * 3 + 0]
					+ 2 * (sImageData[y*mRowBytes + (x - 1) * 3 + 0] - sImageData[y*mRowBytes + (x - 1) * 3 + 0])
					+ sImageData[(y + 1)*mRowBytes + (x - 1) * 3 + 0] - sImageData[(y + 1)*mRowBytes + (x + 1) * 3 + 0];
				pData[y*mWidth + x] = (int)(sqrt(dx*dx + dy*dy) + 0.5);
			}

		m_mmax = m_mmin = pData[0];
		for (y = 1; y < mHeight - 1; y++)
			for (x = 1; x < mWidth - 1; x++)
			{
				if (pData[y*mWidth + x] > m_mmax)
					m_mmax = pData[y*mWidth + x];
				if (pData[y*mWidth + x] < m_mmin)
					m_mmin = pData[y*mWidth + x];
			}

		m_mmax -= m_mmin;
		if (m_mmax)
		{
			for (y = 0; y < mHeight - 1; y++)
				for (x = 0; x < mWidth - 1; x++)
					rImageData[y*mRowBytes + x * 3 + 0] = bCalibration ? ((int)((255.0*pData[y*mWidth + x]) / m_mmax)) : ((pData[y*mWidth + x]>255) ? 255 : ((pData[y*mWidth + x] < 0) ? 0 : pData[y*mWidth + x]));
		}

		//绿色
		for (y = 1; y < mHeight - 1; y++)
			for (x = 1; x < mWidth - 1; x++)
			{
				dx = sImageData[(y - 1)*mRowBytes + (x - 1) * 3 + 1] - sImageData[(y + 1)*mRowBytes + (x - 1) * 3 + 1]
					+ 2 * (sImageData[(y - 1)*mRowBytes + x * 3 + 1] - sImageData[(y + 1)*mRowBytes + x * 3 + 1])
					+ sImageData[(y - 1)*mRowBytes + (x + 1) * 3 + 1] - sImageData[(y + 1)*mRowBytes + (x + 1) * 3 + 1];
				dy = sImageData[(y - 1)*mRowBytes + (x - 1) * 3 + 1] - sImageData[(y - 1)*mRowBytes + (x + 1) * 3 + 1]
					+ 2 * (sImageData[y*mRowBytes + (x - 1) * 3 + 1] - sImageData[y*mRowBytes + (x - 1) * 3 + 1])
					+ sImageData[(y + 1)*mRowBytes + (x - 1) * 3 + 1] - sImageData[(y + 1)*mRowBytes + (x + 1) * 3 + 1];
				pData[y*mWidth + x] = (int)(sqrt(dx*dx + dy*dy) + 0.5);
			}

		m_mmax = m_mmin = pData[0];
		for (y = 1; y < mHeight - 1; y++)
			for (x = 1; x < mWidth - 1; x++)
			{
				if (pData[y*mWidth + x] > m_mmax)
					m_mmax = pData[y*mWidth + x];
				if (pData[y*mWidth + x] < m_mmin)
					m_mmin = pData[y*mWidth + x];
			}

		m_mmax -= m_mmin;
		if (m_mmax)
		{
			for (y = 0; y < mHeight - 1; y++)
				for (x = 0; x < mWidth - 1; x++)
					rImageData[y*mRowBytes + x * 3 + 1] = bCalibration ? ((int)((255.0*pData[y*mWidth + x]) / m_mmax)) : ((pData[y*mWidth + x]>255) ? 255 : ((pData[y*mWidth + x] < 0) ? 0 : pData[y*mWidth + x]));
		}

		//红色
		for (y = 1; y < mHeight - 1; y++)
			for (x = 1; x < mWidth - 1; x++)
			{
				dx = sImageData[(y - 1)*mRowBytes + (x - 1) * 3 + 2] - sImageData[(y + 1)*mRowBytes + (x - 1) * 3 + 2]
					+ 2 * (sImageData[(y - 1)*mRowBytes + x * 3 + 2] - sImageData[(y + 1)*mRowBytes + x * 3 + 2])
					+ sImageData[(y - 1)*mRowBytes + (x + 1) * 3 + 2] - sImageData[(y + 1)*mRowBytes + (x + 1) * 3 + 2];
				dy = sImageData[(y - 1)*mRowBytes + (x - 1) * 3 + 2] - sImageData[(y - 1)*mRowBytes + (x + 1) * 3 + 2]
					+ 2 * (sImageData[y*mRowBytes + (x - 1) * 3 + 2] - sImageData[y*mRowBytes + (x - 1) * 3 + 2])
					+ sImageData[(y + 1)*mRowBytes + (x - 1) * 3 + 2] - sImageData[(y + 1)*mRowBytes + (x + 1) * 3 + 2];
				pData[y*mWidth + x] = (int)(sqrt(dx*dx + dy*dy) + 0.5);
			}

		m_mmax = m_mmin = pData[0];
		for (y = 1; y < mHeight - 1; y++)
			for (x = 1; x < mWidth - 1; x++)
			{
				if (pData[y*mWidth + x] > m_mmax)
					m_mmax = pData[y*mWidth + x];
				if (pData[y*mWidth + x] < m_mmin)
					m_mmin = pData[y*mWidth + x];
			}

		m_mmax -= m_mmin;
		if (m_mmax)
		{
			for (y = 0; y < mHeight - 1; y++)
				for (x = 0; x < mWidth - 1; x++)
					rImageData[y*mRowBytes + x * 3 + 2] = bCalibration ? ((int)((255.0*pData[y*mWidth + x]) / m_mmax)) : ((pData[y*mWidth + x]>255) ? 255 : ((pData[y*mWidth + x] < 0) ? 0 : pData[y*mWidth + x]));
		}
	}


	delete pData;
}

//Prewitt算子
void CImageProcessingDoc::PrewittOperator(CImage * pSrcImage, CImage * pDstImage, BOOL bCalibration, BOOL bfiltering)
{
	int x;
	int y;
	int dx;
	int dy;
	int mWidth  = pSrcImage->GetWidth();
	int mHeight = pSrcImage->GetHeight();
	int mRowBytes = pSrcImage->GetPitch();
	BYTE *sImageData = (BYTE *)pSrcImage->GetBits();
	BYTE *rImageData = (BYTE *)pDstImage->GetBits();

	int *pData = new int[mHeight*mWidth];
	int m_mmax;
	int m_mmin;
   
	if (bfiltering)
	{
		//蓝色
		for (y = 1; y < mHeight - 1; y++)
			for (x = 1; x < mWidth - 1; x++)
			{
				dx = sImageData[(y - 1)*mRowBytes + (x - 1) * 3 + 0] - sImageData[(y + 1)*mRowBytes + (x - 1) * 3 + 0]
					+ (sImageData[(y - 1)*mRowBytes + x * 3 + 0] - sImageData[(y + 1)*mRowBytes + x * 3 + 0])
					+ sImageData[(y - 1)*mRowBytes + (x + 1) * 3 + 0] - sImageData[(y + 1)*mRowBytes + (x + 1) * 3 + 0];
				dy = sImageData[(y - 1)*mRowBytes + (x - 1) * 3 + 0] - sImageData[(y - 1)*mRowBytes + (x + 1) * 3 + 0]
					+ (sImageData[y*mRowBytes + (x - 1) * 3 + 0] - sImageData[y*mRowBytes + (x - 1) * 3 + 0])
					+ sImageData[(y + 1)*mRowBytes + (x - 1) * 3 + 0] - sImageData[(y + 1)*mRowBytes + (x + 1) * 3 + 0];
				pData[y*mWidth + x] = (int)(sImageData[y*mRowBytes + x * 3] + sqrt(dx*dx + dy*dy) + 0.5);
			}

		m_mmax = m_mmin = pData[0];
		for (y = 1; y < mHeight - 1; y++)
			for (x = 1; x < mWidth - 1; x++)
			{
				if (pData[y*mWidth + x] > m_mmax)
					m_mmax = pData[y*mWidth + x];
				if (pData[y*mWidth + x] < m_mmin)
					m_mmin = pData[y*mWidth + x];
			}

		m_mmax -= m_mmin;
		if (m_mmax)
		{
			for (y = 0; y < mHeight - 1; y++)
				for (x = 0; x < mWidth - 1; x++)
					rImageData[y*mRowBytes + x * 3 + 0] = bCalibration ? ((int)((255.0*pData[y*mWidth + x]) / m_mmax)) : ((pData[y*mWidth + x]>255) ? 255 : ((pData[y*mWidth + x] < 0) ? 0 : pData[y*mWidth + x]));
		}

		//绿色
		for (y = 1; y < mHeight - 1; y++)
			for (x = 1; x < mWidth - 1; x++)
			{
				dx = sImageData[(y - 1)*mRowBytes + (x - 1) * 3 + 1] - sImageData[(y + 1)*mRowBytes + (x - 1) * 3 + 1]
					+ (sImageData[(y - 1)*mRowBytes + x * 3 + 1] - sImageData[(y + 1)*mRowBytes + x * 3 + 1])
					+ sImageData[(y - 1)*mRowBytes + (x + 1) * 3 + 1] - sImageData[(y + 1)*mRowBytes + (x + 1) * 3 + 1];
				dy = sImageData[(y - 1)*mRowBytes + (x - 1) * 3 + 1] - sImageData[(y - 1)*mRowBytes + (x + 1) * 3 + 1]
					+ (sImageData[y*mRowBytes + (x - 1) * 3 + 1] - sImageData[y*mRowBytes + (x - 1) * 3 + 1])
					+ sImageData[(y + 1)*mRowBytes + (x - 1) * 3 + 1] - sImageData[(y + 1)*mRowBytes + (x + 1) * 3 + 1];
				pData[y*mWidth + x] = (int)(sImageData[y*mRowBytes + x * 3 + 1] + sqrt(dx*dx + dy*dy) + 0.5);
			}

		m_mmax = m_mmin = pData[0];
		for (y = 1; y < mHeight - 1; y++)
			for (x = 1; x < mWidth - 1; x++)
			{
				if (pData[y*mWidth + x] > m_mmax)
					m_mmax = pData[y*mWidth + x];
				if (pData[y*mWidth + x] < m_mmin)
					m_mmin = pData[y*mWidth + x];
			}

		m_mmax -= m_mmin;
		if (m_mmax)
		{
			for (y = 0; y < mHeight - 1; y++)
				for (x = 0; x < mWidth - 1; x++)
					rImageData[y*mRowBytes + x * 3 + 1] = bCalibration ? ((int)((255.0*pData[y*mWidth + x]) / m_mmax)) : ((pData[y*mWidth + x]>255) ? 255 : ((pData[y*mWidth + x] < 0) ? 0 : pData[y*mWidth + x]));
		}

		//红色
		for (y = 1; y < mHeight - 1; y++)
			for (x = 1; x < mWidth - 1; x++)
			{
				dx = sImageData[(y - 1)*mRowBytes + (x - 1) * 3 + 2] - sImageData[(y + 1)*mRowBytes + (x - 1) * 3 + 2]
					+ (sImageData[(y - 1)*mRowBytes + x * 3 + 2] - sImageData[(y + 1)*mRowBytes + x * 3 + 2])
					+ sImageData[(y - 1)*mRowBytes + (x + 1) * 3 + 2] - sImageData[(y + 1)*mRowBytes + (x + 1) * 3 + 2];
				dy = sImageData[(y - 1)*mRowBytes + (x - 1) * 3 + 2] - sImageData[(y - 1)*mRowBytes + (x + 1) * 3 + 2]
					+ (sImageData[y*mRowBytes + (x - 1) * 3 + 2] - sImageData[y*mRowBytes + (x - 1) * 3 + 2])
					+ sImageData[(y + 1)*mRowBytes + (x - 1) * 3 + 2] - sImageData[(y + 1)*mRowBytes + (x + 1) * 3 + 2];
				pData[y*mWidth + x] = (int)(sImageData[y*mRowBytes + x * 3 + 2] + sqrt(dx*dx + dy*dy) + 0.5);
			}

		m_mmax = m_mmin = pData[0];
		for (y = 1; y < mHeight - 1; y++)
			for (x = 1; x < mWidth - 1; x++)
			{
				if (pData[y*mWidth + x] > m_mmax)
					m_mmax = pData[y*mWidth + x];
				if (pData[y*mWidth + x] < m_mmin)
					m_mmin = pData[y*mWidth + x];
			}

		m_mmax -= m_mmin;
		if (m_mmax)
		{
			for (y = 0; y < mHeight - 1; y++)
				for (x = 0; x < mWidth - 1; x++)
					rImageData[y*mRowBytes + x * 3 + 2] = bCalibration ? ((int)((255.0*pData[y*mWidth + x]) / m_mmax)) : ((pData[y*mWidth + x]>255) ? 255 : ((pData[y*mWidth + x] < 0) ? 0 : pData[y*mWidth + x]));
		}
	}
	else
	{
		//蓝色
		for (y = 1; y < mHeight - 1; y++)
			for (x = 1; x < mWidth - 1; x++)
			{
				dx = sImageData[(y - 1)*mRowBytes + (x - 1) * 3 + 0] - sImageData[(y + 1)*mRowBytes + (x - 1) * 3 + 0]
					+ (sImageData[(y - 1)*mRowBytes + x * 3 + 0] - sImageData[(y + 1)*mRowBytes + x * 3 + 0])
					+ sImageData[(y - 1)*mRowBytes + (x + 1) * 3 + 0] - sImageData[(y + 1)*mRowBytes + (x + 1) * 3 + 0];
				dy = sImageData[(y - 1)*mRowBytes + (x - 1) * 3 + 0] - sImageData[(y - 1)*mRowBytes + (x + 1) * 3 + 0]
					+ (sImageData[y*mRowBytes + (x - 1) * 3 + 0] - sImageData[y*mRowBytes + (x - 1) * 3 + 0])
					+ sImageData[(y + 1)*mRowBytes + (x - 1) * 3 + 0] - sImageData[(y + 1)*mRowBytes + (x + 1) * 3 + 0];
				pData[y*mWidth + x] = (int)(sqrt(dx*dx + dy*dy) + 0.5);
			}

		m_mmax = m_mmin = pData[0];
		for (y = 1; y < mHeight - 1; y++)
			for (x = 1; x < mWidth - 1; x++)
			{
				if (pData[y*mWidth + x] > m_mmax)
					m_mmax = pData[y*mWidth + x];
				if (pData[y*mWidth + x] < m_mmin)
					m_mmin = pData[y*mWidth + x];
			}

		m_mmax -= m_mmin;
		if (m_mmax)
		{
			for (y = 0; y < mHeight - 1; y++)
				for (x = 0; x < mWidth - 1; x++)
					rImageData[y*mRowBytes + x * 3 + 0] = bCalibration ? ((int)((255.0*pData[y*mWidth + x]) / m_mmax)) : ((pData[y*mWidth + x]>255) ? 255 : ((pData[y*mWidth + x] < 0) ? 0 : pData[y*mWidth + x]));
		}

		//绿色
		for (y = 1; y < mHeight - 1; y++)
			for (x = 1; x < mWidth - 1; x++)
			{
				dx = sImageData[(y - 1)*mRowBytes + (x - 1) * 3 + 1] - sImageData[(y + 1)*mRowBytes + (x - 1) * 3 + 1]
					+ (sImageData[(y - 1)*mRowBytes + x * 3 + 1] - sImageData[(y + 1)*mRowBytes + x * 3 + 1])
					+ sImageData[(y - 1)*mRowBytes + (x + 1) * 3 + 1] - sImageData[(y + 1)*mRowBytes + (x + 1) * 3 + 1];
				dy = sImageData[(y - 1)*mRowBytes + (x - 1) * 3 + 1] - sImageData[(y - 1)*mRowBytes + (x + 1) * 3 + 1]
					+ (sImageData[y*mRowBytes + (x - 1) * 3 + 1] - sImageData[y*mRowBytes + (x - 1) * 3 + 1])
					+ sImageData[(y + 1)*mRowBytes + (x - 1) * 3 + 1] - sImageData[(y + 1)*mRowBytes + (x + 1) * 3 + 1];
				pData[y*mWidth + x] = (int)(sqrt(dx*dx + dy*dy) + 0.5);
			}

		m_mmax = m_mmin = pData[0];
		for (y = 1; y < mHeight - 1; y++)
			for (x = 1; x < mWidth - 1; x++)
			{
				if (pData[y*mWidth + x] > m_mmax)
					m_mmax = pData[y*mWidth + x];
				if (pData[y*mWidth + x] < m_mmin)
					m_mmin = pData[y*mWidth + x];
			}

		m_mmax -= m_mmin;
		if (m_mmax)
		{
			for (y = 0; y < mHeight - 1; y++)
				for (x = 0; x < mWidth - 1; x++)
					rImageData[y*mRowBytes + x * 3 + 1] = bCalibration ? ((int)((255.0*pData[y*mWidth + x]) / m_mmax)) : ((pData[y*mWidth + x]>255) ? 255 : ((pData[y*mWidth + x] < 0) ? 0 : pData[y*mWidth + x]));
		}

		//红色
		for (y = 1; y < mHeight - 1; y++)
			for (x = 1; x < mWidth - 1; x++)
			{
				dx = sImageData[(y - 1)*mRowBytes + (x - 1) * 3 + 2] - sImageData[(y + 1)*mRowBytes + (x - 1) * 3 + 2]
					+ (sImageData[(y - 1)*mRowBytes + x * 3 + 2] - sImageData[(y + 1)*mRowBytes + x * 3 + 2])
					+ sImageData[(y - 1)*mRowBytes + (x + 1) * 3 + 2] - sImageData[(y + 1)*mRowBytes + (x + 1) * 3 + 2];
				dy = sImageData[(y - 1)*mRowBytes + (x - 1) * 3 + 2] - sImageData[(y - 1)*mRowBytes + (x + 1) * 3 + 2]
					+ (sImageData[y*mRowBytes + (x - 1) * 3 + 2] - sImageData[y*mRowBytes + (x - 1) * 3 + 2])
					+ sImageData[(y + 1)*mRowBytes + (x - 1) * 3 + 2] - sImageData[(y + 1)*mRowBytes + (x + 1) * 3 + 2];
				pData[y*mWidth + x] = (int)(sqrt(dx*dx + dy*dy) + 0.5);
			}

		m_mmax = m_mmin = pData[0];
		for (y = 1; y < mHeight - 1; y++)
			for (x = 1; x < mWidth - 1; x++)
			{
				if (pData[y*mWidth + x] > m_mmax)
					m_mmax = pData[y*mWidth + x];
				if (pData[y*mWidth + x] < m_mmin)
					m_mmin = pData[y*mWidth + x];
			}

		m_mmax -= m_mmin;
		if (m_mmax)
		{
			for (y = 0; y < mHeight - 1; y++)
				for (x = 0; x < mWidth - 1; x++)
					rImageData[y*mRowBytes + x * 3 + 2] = bCalibration ? ((int)((255.0*pData[y*mWidth + x]) / m_mmax)) : ((pData[y*mWidth + x]>255) ? 255 : ((pData[y*mWidth + x] < 0) ? 0 : pData[y*mWidth + x]));
		}
	}

}

//迷向算子
void CImageProcessingDoc::IsotropicOperator(CImage * pSrcImage, CImage * pDstImage, BOOL bCalibration, BOOL bfiltering)
{	
	int x;
	int y;
	double dx;
	double dy;
	int mWidth  = pSrcImage->GetWidth();
	int mHeight = pSrcImage->GetHeight();
	int mRowBytes = pSrcImage->GetPitch();
	BYTE *sImageData = (BYTE *)pSrcImage->GetBits();
	BYTE *rImageData = (BYTE *)pDstImage->GetBits();

	int *pData = new int[mHeight*mWidth];
	int m_mmax;
	int m_mmin;

	double sqrt2 = sqrt(2);

	if (bfiltering)
	{
		//蓝色
		for (y = 1; y < mHeight - 1; y++)
			for (x = 1; x < mWidth - 1; x++)
			{
				dx = sImageData[(y - 1)*mRowBytes + (x - 1) * 3 + 0] - sImageData[(y + 1)*mRowBytes + (x - 1) * 3 + 0]
					+ sqrt2 * (sImageData[(y - 1)*mRowBytes + x * 3 + 0] - sImageData[(y + 1)*mRowBytes + x * 3 + 0])
					+ sImageData[(y - 1)*mRowBytes + (x + 1) * 3 + 0] - sImageData[(y + 1)*mRowBytes + (x + 1) * 3 + 0];
				dy = sImageData[(y - 1)*mRowBytes + (x - 1) * 3 + 0] - sImageData[(y - 1)*mRowBytes + (x + 1) * 3 + 0]
					+ sqrt2 * (sImageData[y*mRowBytes + (x - 1) * 3 + 0] - sImageData[y*mRowBytes + (x - 1) * 3 + 0])
					+ sImageData[(y + 1)*mRowBytes + (x - 1) * 3 + 0] - sImageData[(y + 1)*mRowBytes + (x + 1) * 3 + 0];
				pData[y*mWidth + x] = (int)(sImageData[y*mRowBytes + x * 3] + sqrt(dx*dx + dy*dy) + 0.5);
			}

		m_mmax = m_mmin = pData[0];
		for (y = 1; y < mHeight - 1; y++)
			for (x = 1; x < mWidth - 1; x++)
			{
				if (pData[y*mWidth + x] > m_mmax)
					m_mmax = pData[y*mWidth + x];
				if (pData[y*mWidth + x] < m_mmin)
					m_mmin = pData[y*mWidth + x];
			}

		m_mmax -= m_mmin;
		if (m_mmax)
		{
			for (y = 0; y < mHeight - 1; y++)
				for (x = 0; x < mWidth - 1; x++)
					rImageData[y*mRowBytes + x * 3 + 0] = bCalibration ? ((int)((255.0*pData[y*mWidth + x]) / m_mmax)) : ((pData[y*mWidth + x]>255) ? 255 : ((pData[y*mWidth + x] < 0) ? 0 : pData[y*mWidth + x]));
		}

		//绿色
		for (y = 1; y < mHeight - 1; y++)
			for (x = 1; x < mWidth - 1; x++)
			{
				dx = sImageData[(y - 1)*mRowBytes + (x - 1) * 3 + 1] - sImageData[(y + 1)*mRowBytes + (x - 1) * 3 + 1]
					+ sqrt2 * (sImageData[(y - 1)*mRowBytes + x * 3 + 1] - sImageData[(y + 1)*mRowBytes + x * 3 + 1])
					+ sImageData[(y - 1)*mRowBytes + (x + 1) * 3 + 1] - sImageData[(y + 1)*mRowBytes + (x + 1) * 3 + 1];
				dy = sImageData[(y - 1)*mRowBytes + (x - 1) * 3 + 1] - sImageData[(y - 1)*mRowBytes + (x + 1) * 3 + 1]
					+ sqrt2 * (sImageData[y*mRowBytes + (x - 1) * 3 + 1] - sImageData[y*mRowBytes + (x - 1) * 3 + 1])
					+ sImageData[(y + 1)*mRowBytes + (x - 1) * 3 + 1] - sImageData[(y + 1)*mRowBytes + (x + 1) * 3 + 1];
				pData[y*mWidth + x] = (int)(sImageData[y*mRowBytes + x * 3 + 1] + sqrt(dx*dx + dy*dy) + 0.5);
			}

		m_mmax = m_mmin = pData[0];
		for (y = 1; y < mHeight - 1; y++)
			for (x = 1; x < mWidth - 1; x++)
			{
				if (pData[y*mWidth + x] > m_mmax)
					m_mmax = pData[y*mWidth + x];
				if (pData[y*mWidth + x] < m_mmin)
					m_mmin = pData[y*mWidth + x];
			}

		m_mmax -= m_mmin;
		if (m_mmax)
		{
			for (y = 0; y < mHeight - 1; y++)
				for (x = 0; x < mWidth - 1; x++)
					rImageData[y*mRowBytes + x * 3 + 1] = bCalibration ? ((int)((255.0*pData[y*mWidth + x]) / m_mmax)) : ((pData[y*mWidth + x]>255) ? 255 : ((pData[y*mWidth + x] < 0) ? 0 : pData[y*mWidth + x]));
		}

		//红色
		for (y = 1; y < mHeight - 1; y++)
			for (x = 1; x < mWidth - 1; x++)
			{
				dx = sImageData[(y - 1)*mRowBytes + (x - 1) * 3 + 2] - sImageData[(y + 1)*mRowBytes + (x - 1) * 3 + 2]
					+ sqrt2 * (sImageData[(y - 1)*mRowBytes + x * 3 + 2] - sImageData[(y + 1)*mRowBytes + x * 3 + 2])
					+ sImageData[(y - 1)*mRowBytes + (x + 1) * 3 + 2] - sImageData[(y + 1)*mRowBytes + (x + 1) * 3 + 2];
				dy = sImageData[(y - 1)*mRowBytes + (x - 1) * 3 + 2] - sImageData[(y - 1)*mRowBytes + (x + 1) * 3 + 2]
					+ sqrt2 * (sImageData[y*mRowBytes + (x - 1) * 3 + 2] - sImageData[y*mRowBytes + (x - 1) * 3 + 2])
					+ sImageData[(y + 1)*mRowBytes + (x - 1) * 3 + 2] - sImageData[(y + 1)*mRowBytes + (x + 1) * 3 + 2];
				pData[y*mWidth + x] = (int)(sImageData[y*mRowBytes + x * 3 + 2] + sqrt(dx*dx + dy*dy) + 0.5);
			}

		m_mmax = m_mmin = pData[0];
		for (y = 1; y < mHeight - 1; y++)
			for (x = 1; x < mWidth - 1; x++)
			{
				if (pData[y*mWidth + x] > m_mmax)
					m_mmax = pData[y*mWidth + x];
				if (pData[y*mWidth + x] < m_mmin)
					m_mmin = pData[y*mWidth + x];
			}

		m_mmax -= m_mmin;
		if (m_mmax)
		{
			for (y = 0; y < mHeight - 1; y++)
				for (x = 0; x < mWidth - 1; x++)
					rImageData[y*mRowBytes + x * 3 + 2] = bCalibration ? ((int)((255.0*pData[y*mWidth + x]) / m_mmax)) : ((pData[y*mWidth + x]>255) ? 255 : ((pData[y*mWidth + x] < 0) ? 0 : pData[y*mWidth + x]));
		}
	}
	else
	{
		//蓝色
		for (y = 1; y < mHeight - 1; y++)
			for (x = 1; x < mWidth - 1; x++)
			{
				dx = sImageData[(y - 1)*mRowBytes + (x - 1) * 3 + 0] - sImageData[(y + 1)*mRowBytes + (x - 1) * 3 + 0]
					+ sqrt2 * (sImageData[(y - 1)*mRowBytes + x * 3 + 0] - sImageData[(y + 1)*mRowBytes + x * 3 + 0])
					+ sImageData[(y - 1)*mRowBytes + (x + 1) * 3 + 0] - sImageData[(y + 1)*mRowBytes + (x + 1) * 3 + 0];
				dy = sImageData[(y - 1)*mRowBytes + (x - 1) * 3 + 0] - sImageData[(y - 1)*mRowBytes + (x + 1) * 3 + 0]
					+ sqrt2 * (sImageData[y*mRowBytes + (x - 1) * 3 + 0] - sImageData[y*mRowBytes + (x - 1) * 3 + 0])
					+ sImageData[(y + 1)*mRowBytes + (x - 1) * 3 + 0] - sImageData[(y + 1)*mRowBytes + (x + 1) * 3 + 0];
				pData[y*mWidth + x] = (int)(sqrt(dx*dx + dy*dy) + 0.5);
			}

		m_mmax = m_mmin = pData[0];
		for (y = 1; y < mHeight - 1; y++)
			for (x = 1; x < mWidth - 1; x++)
			{
				if (pData[y*mWidth + x] > m_mmax)
					m_mmax = pData[y*mWidth + x];
				if (pData[y*mWidth + x] < m_mmin)
					m_mmin = pData[y*mWidth + x];
			}

		m_mmax -= m_mmin;
		if (m_mmax)
		{
			for (y = 0; y < mHeight - 1; y++)
				for (x = 0; x < mWidth - 1; x++)
					rImageData[y*mRowBytes + x * 3 + 0] = bCalibration ? ((int)((255.0*pData[y*mWidth + x]) / m_mmax)) : ((pData[y*mWidth + x]>255) ? 255 : ((pData[y*mWidth + x] < 0) ? 0 : pData[y*mWidth + x]));
		}

		//绿色
		for (y = 1; y < mHeight - 1; y++)
			for (x = 1; x < mWidth - 1; x++)
			{
				dx = sImageData[(y - 1)*mRowBytes + (x - 1) * 3 + 1] - sImageData[(y + 1)*mRowBytes + (x - 1) * 3 + 1]
					+ sqrt2 * (sImageData[(y - 1)*mRowBytes + x * 3 + 1] - sImageData[(y + 1)*mRowBytes + x * 3 + 1])
					+ sImageData[(y - 1)*mRowBytes + (x + 1) * 3 + 1] - sImageData[(y + 1)*mRowBytes + (x + 1) * 3 + 1];
				dy = sImageData[(y - 1)*mRowBytes + (x - 1) * 3 + 1] - sImageData[(y - 1)*mRowBytes + (x + 1) * 3 + 1]
					+ sqrt2 * (sImageData[y*mRowBytes + (x - 1) * 3 + 1] - sImageData[y*mRowBytes + (x - 1) * 3 + 1])
					+ sImageData[(y + 1)*mRowBytes + (x - 1) * 3 + 1] - sImageData[(y + 1)*mRowBytes + (x + 1) * 3 + 1];
				pData[y*mWidth + x] = (int)(sqrt(dx*dx + dy*dy) + 0.5);
			}

		m_mmax = m_mmin = pData[0];
		for (y = 1; y < mHeight - 1; y++)
			for (x = 1; x < mWidth - 1; x++)
			{
				if (pData[y*mWidth + x] > m_mmax)
					m_mmax = pData[y*mWidth + x];
				if (pData[y*mWidth + x] < m_mmin)
					m_mmin = pData[y*mWidth + x];
			}

		m_mmax -= m_mmin;
		if (m_mmax)
		{
			for (y = 0; y < mHeight - 1; y++)
				for (x = 0; x < mWidth - 1; x++)
					rImageData[y*mRowBytes + x * 3 + 1] = bCalibration ? ((int)((255.0*pData[y*mWidth + x]) / m_mmax)) : ((pData[y*mWidth + x]>255) ? 255 : ((pData[y*mWidth + x] < 0) ? 0 : pData[y*mWidth + x]));
		}

		//红色
		for (y = 1; y < mHeight - 1; y++)
			for (x = 1; x < mWidth - 1; x++)
			{
				dx = sImageData[(y - 1)*mRowBytes + (x - 1) * 3 + 2] - sImageData[(y + 1)*mRowBytes + (x - 1) * 3 + 2]
					+ sqrt2 * (sImageData[(y - 1)*mRowBytes + x * 3 + 2] - sImageData[(y + 1)*mRowBytes + x * 3 + 2])
					+ sImageData[(y - 1)*mRowBytes + (x + 1) * 3 + 2] - sImageData[(y + 1)*mRowBytes + (x + 1) * 3 + 2];
				dy = sImageData[(y - 1)*mRowBytes + (x - 1) * 3 + 2] - sImageData[(y - 1)*mRowBytes + (x + 1) * 3 + 2]
					+ sqrt2 * (sImageData[y*mRowBytes + (x - 1) * 3 + 2] - sImageData[y*mRowBytes + (x - 1) * 3 + 2])
					+ sImageData[(y + 1)*mRowBytes + (x - 1) * 3 + 2] - sImageData[(y + 1)*mRowBytes + (x + 1) * 3 + 2];
				pData[y*mWidth + x] = (int)(sqrt(dx*dx + dy*dy) + 0.5);
			}

		m_mmax = m_mmin = pData[0];
		for (y = 1; y < mHeight - 1; y++)
			for (x = 1; x < mWidth - 1; x++)
			{
				if (pData[y*mWidth + x] > m_mmax)
					m_mmax = pData[y*mWidth + x];
				if (pData[y*mWidth + x] < m_mmin)
					m_mmin = pData[y*mWidth + x];
			}

		m_mmax -= m_mmin;
		if (m_mmax)
		{
			for (y = 0; y < mHeight - 1; y++)
				for (x = 0; x < mWidth - 1; x++)
					rImageData[y*mRowBytes + x * 3 + 2] = bCalibration ? ((int)((255.0*pData[y*mWidth + x]) / m_mmax)) : ((pData[y*mWidth + x]>255) ? 255 : ((pData[y*mWidth + x] < 0) ? 0 : pData[y*mWidth + x]));
		}
	}

	delete pData;
}

//拉普拉斯(Laplacian）算子
void CImageProcessingDoc::LaplaceOperator(CImage * pSrcImage, CImage * pDstImage, int laplacetype,BOOL bCalibration, BOOL bfiltering)
{
	int x;
	int y;
	int i;
	int j;

	int mWidth = pSrcImage->GetWidth();
	int mHeight = pSrcImage->GetHeight();
	int mRowBytes = pSrcImage->GetPitch();
	BYTE *rImageData = (BYTE *)pDstImage->GetBits();

	int *pBitData = NULL;
	pBitData = new int[3 * mHeight*mWidth];

	BYTE * pData = NULL;
	pData = new BYTE[9];

	int Laplace0[3][3] = { { 0,1,0},{1,-4,1 }, { 0,1,0 } };
	int Laplace1[3][3] = { { 1,1,1},{1,-8, 1}, { 1,1,1 } };
	int Laplace2[3][3] = { {0,-1,0},{-1,4,-1}, { 0,-1,0} };
	int Laplace3[3][3] = { {-1,-1,-1},{-1,8,-1},{-1,-1,-1} };

	int *p;
	switch (laplacetype)
	{ 
	case 1: p = (int *)Laplace0;
		    break;
	case 2: p = (int *)Laplace1;
		    break;
	case 3: p = (int *)Laplace2;
		    break;
	case 4: p = (int *)Laplace3;
		    break;
	default:
		    return;
	}

	int laplace;
	int prarm_c = (laplacetype <= 2) ? -1 : 1;
	if (bfiltering)
	{
	    for (y = 0; y < mHeight; y++)
	    for (x = 0; x < mWidth; x++)
	    {
		    CopyAreaBlueFromImgBits(pSrcImage, pData, x, y, 1, 1);
		    laplace = 0;
		    for (j = 0; j < 3; j++)
		    for (i = 0; i < 3; i++)
		    {
			    laplace += pData[j * 3 + i] * p[j*3 + i];
		    }
		    pBitData[3 *  y * mWidth + x * 3] = pData[4] + prarm_c * laplace;

		    CopyAreaGreenFromImgBits(pSrcImage, pData, x, y, 1, 1);
		    laplace = 0;

		    for (j = 0; j < 3; j++)
		    for (i = 0; i < 3; i++)
		    {
			    laplace += pData[j * 3 + i] * p[j*3 + i];
		    }
		    pBitData[3 * y * mWidth + x * 3 + 1] = pData[4] + prarm_c * laplace;

		    CopyAreaRedFromImgBits(pSrcImage, pData, x, y, 1, 1);
		    laplace = 0;

		    for (j = 0; j < 3; j++)
		    for (i = 0; i < 3; i++)
		    {
			    laplace += pData[j * 3 + i] * p[j*3 + i];
		    }	    
		    pBitData[3 * y * mWidth + x * 3 + 2] = pData[4] + prarm_c * laplace;
	    }
	}
	else
	{
		for (y = 0; y < mHeight; y++)
		for (x = 0; x < mWidth; x++)
		{
			CopyAreaBlueFromImgBits(pSrcImage, pData, x, y, 1, 1);
			laplace = 0;
			for (j = 0; j < 3; j++)
			for (i = 0; i < 3; i++)
			{
				laplace += pData[j * 3 + i] * p[j * 3 + i];
			}
			pBitData[3 * y * mWidth + x * 3] = laplace;

			CopyAreaGreenFromImgBits(pSrcImage, pData, x, y, 1, 1);
			laplace = 0;

		    for (j = 0; j < 3; j++)
			for (i = 0; i < 3; i++)
			{
				laplace += pData[j * 3 + i] * p[j * 3 + i];
			}
		    pBitData[3 * y * mWidth + x * 3 + 1] = laplace;

			CopyAreaRedFromImgBits(pSrcImage, pData, x, y, 1, 1);

			laplace = 0;

			for (j = 0; j < 3; j++)
			for (i = 0; i < 3; i++)
			{
				laplace += pData[j * 3 + i] * p[j * 3 + i];
			}
			pBitData[3 * y * mWidth + x * 3 + 2] = laplace;
		}
	}

	int minBlue;
	int maxBlue;
	minBlue = maxBlue = pBitData[0];
	int minGreen;
	int maxGreen;
	minGreen = maxGreen = pBitData[1];
	int minRed;
	int maxRed;
	minRed = maxRed = pBitData[2];

	for (y = 0; y < mHeight; y++)
	for (x = 0; x < mWidth; x++)
	{
		if (pBitData[3 * y * mWidth + x * 3] < minBlue)
			minBlue = pBitData[3 * y * mWidth + x * 3];
		if(pBitData[3 * y * mWidth + x * 3] > maxBlue)
			maxBlue = pBitData[3 * y * mWidth + x * 3];
		if (pBitData[3 * y * mWidth + x * 3 + 1] < minGreen)
			minGreen = pBitData[3 * y * mWidth + x * 3 + 1];
		if (pBitData[3 * y * mWidth + x * 3 + 1] > maxGreen)
			maxGreen = pBitData[3 * y * mWidth + x * 3 + 1];
		if (pBitData[3 * y * mWidth + x * 3 + 2] < minRed)
			minRed = pBitData[3 * y * mWidth + x * 3 + 2];
		if (pBitData[3 * y * mWidth + x * 3 + 2] > maxRed)
			maxRed = pBitData[3 * y * mWidth + x * 3 + 2];
	}
	
	maxBlue -= minBlue;
	maxGreen -= minGreen;
	maxRed -= minRed;
	if (bCalibration)
	{
		for (y = 0; y < mHeight; y++)
		for (x = 0; x < mWidth; x++)
		{
			laplace = pBitData[3 * y * mWidth + x * 3] - minBlue;
			if (maxBlue)
				rImageData[y*mRowBytes + x * 3] = (int)((255.0*laplace) / maxBlue);

			laplace = pBitData[3 * y * mWidth + x * 3 + 1] - minGreen;
			if (maxGreen)
				rImageData[y*mRowBytes + x * 3 +1] = (int)((255.0*laplace) / maxGreen);

			laplace = pBitData[3 * y * mWidth + x * 3 + 2] - minRed;
			if (maxRed)
				rImageData[y*mRowBytes + x * 3 + 2] = (int)((255.0*laplace) / maxRed);
		}
	}
	else
	{
		for (y = 0; y < mHeight; y++)
		for (x = 0; x < mWidth; x++)
		{
			laplace = pBitData[3 * y * mWidth + x * 3];
			laplace = (laplace > 255)? 255 : ((laplace < 0) ? 0 : laplace);
			rImageData[y*mRowBytes + x * 3] = laplace;

			laplace = pBitData[3 * y * mWidth + x * 3 + 1];
			laplace = (laplace > 255) ? 255 : ((laplace < 0) ? 0 : laplace);
			rImageData[y*mRowBytes + x * 3 + 1] = laplace;

			laplace = pBitData[3 * y * mWidth + x * 3 + 2];
			laplace = (laplace > 255) ? 255 : ((laplace < 0) ? 0 : laplace);
			rImageData[y*mRowBytes + x * 3 + 2] = laplace;
		}
	}

	if (pData)
		delete[] pData;
	pData = NULL;
	if (pBitData)
		delete pBitData;
	pBitData = NULL;
}

//Kirsch算子
void CImageProcessingDoc::KirschOperator(CImage * pSrcImage, CImage * pDstImage, int Kr, BOOL bCalibration)
{
	int x;
	int y;
	int i;
	int j;

	int mWidth = pSrcImage->GetWidth();
	int mHeight = pSrcImage->GetHeight();
	int mRowBytes = pSrcImage->GetPitch();
	LPBYTE rImageData = (BYTE *)pDstImage->GetBits();

	int *pBitData = NULL;
	pBitData = new int[3 * mHeight*mWidth];
	LPBYTE  pData = NULL;
	pData = new BYTE[9];

	int Kirsch0[3][3] = { { +5,+5,+5 },{ -3,0,-3 },{ -3,-3,-3 } };
	int Kirsch1[3][3] = { { -3,+5,+5 },{ -3,0,+5 },{ -3,-3,-3 } };
	int Kirsch2[3][3] = { { -3,-3,+5 },{ -3,0,+5 },{ -3,-3,+5 } };
	int Kirsch3[3][3] = { { -3,-3,-3 },{ -3,0,+5 },{ -3,+5,+5 } };
	int Kirsch4[3][3] = { { -3,-3,-3 },{ -3,0,-3 },{ +5,+5,+5 } };
	int Kirsch5[3][3] = { { -3,-3,-3 },{ +5,0,-3 },{ +5,+5,-3 } };
	int Kirsch6[3][3] = { { +5,-3,-3 },{ +5,0,-3 },{ +5,-3,-3 } };
	int Kirsch7[3][3] = { { +5,+5,-3 },{ +5,0,-3 },{ -3,-3,-3 } };

	int *p;
	switch (Kr)
	{ 
	case 1: p = (int *)Kirsch0;
		    break;
	case 2: p = (int *)Kirsch1;
		    break;
	case 3: p = (int *)Kirsch2;
		    break;
	case 4: p = (int *)Kirsch3;
		    break;
	case 5: p = (int *)Kirsch4;
		    break;
	case 6: p = (int *)Kirsch5;
		    break;
	case 7: p = (int *)Kirsch6;
		    break;
	case 8: p = (int *)Kirsch7;
		    break;
	default:
		    return;
	}

	int kirsch;
	for (y = 0; y < mHeight; y++)
	for (x = 0; x < mWidth; x++)
	{
		//蓝色
		CopyAreaBlueFromImgBits(pSrcImage, pData, x, y, 1, 1);
		kirsch = 0;
		for (j = 0; j < 3; j++)
		for (i = 0; i < 3; i++)
		{
			kirsch += pData[j * 3 + i] * p[j*3 + i];
		}
		pBitData[3 * y * mWidth + x * 3] = kirsch;

		//绿色
		CopyAreaGreenFromImgBits(pSrcImage, pData, x, y, 1, 1);
		kirsch = 0;
		for (j = 0; j < 3; j++)
		for (i = 0; i < 3; i++)
		{
			kirsch += pData[j * 3 + i] * p[j*3 + i];
		}
		pBitData[3 * y * mWidth + x * 3 + 1] = kirsch;

		//红色
		CopyAreaRedFromImgBits(pSrcImage, pData, x, y, 1, 1);
		kirsch = 0;
		for (j = 0; j < 3; j++)
		for (i = 0; i < 3; i++)
		{
			kirsch += pData[j * 3 + i] * p[j*3 + i];
		}	    

		pBitData[3 * y * mWidth + x * 3 + 2] = kirsch;
	}

	int minBlue;
	int maxBlue;
	minBlue = maxBlue = pBitData[0];
	int minGreen;
	int maxGreen;
	minGreen = maxGreen = pBitData[1];
	int minRed;
	int maxRed;
	minRed = maxRed = pBitData[2];

	for (y = 0; y < mHeight; y++)
	for (x = 0; x < mWidth; x++)
	{
		if (pBitData[3 * y * mWidth + x * 3] < minBlue)
			minBlue = pBitData[3 * y * mWidth + x * 3];
		if(pBitData[3 * y * mWidth + x * 3] > maxBlue)
			maxBlue = pBitData[3 * y * mWidth + x * 3];
		if (pBitData[3 * y * mWidth + x * 3 + 1] < minGreen)
			minGreen = pBitData[3 * y * mWidth + x * 3 + 1];
		if (pBitData[3 * y * mWidth + x * 3 + 1] > maxGreen)
			maxGreen = pBitData[3 * y * mWidth + x * 3 + 1];
		if (pBitData[3 * y * mWidth + x * 3 + 2] < minRed)
			minRed = pBitData[3 * y * mWidth + x * 3 + 2];
		if (pBitData[3 * y * mWidth + x * 3 + 2] > maxRed)
			maxRed = pBitData[3 * y * mWidth + x * 3 + 2];
	}
	
	maxBlue -= minBlue;
	maxGreen -= minGreen;
	maxRed -= minRed;
	if (bCalibration)
	{
		for (y = 0; y < mHeight; y++)
		for (x = 0; x < mWidth; x++)
		{
			kirsch = pBitData[3 * y * mWidth + x * 3] - minBlue;
			if (maxBlue)
				rImageData[y*mRowBytes + x * 3] = (int)((255.0*kirsch) / maxBlue);

			kirsch = pBitData[3 * y * mWidth + x * 3 + 1] - minGreen;
			if (maxGreen)
				rImageData[y*mRowBytes + x * 3 +1] = (int)((255.0*kirsch) / maxGreen);

			kirsch = pBitData[3 * y * mWidth + x * 3 + 2] - minRed;
			if (maxRed)
				rImageData[y*mRowBytes + x * 3 + 2] = (int)((255.0*kirsch) / maxRed);
		}
	}
	else
	{
		for (y = 0; y < mHeight; y++)
		for (x = 0; x < mWidth; x++)
		{
			kirsch = pBitData[3 * y * mWidth + x * 3];
			kirsch = (kirsch > 255)? 255 : ((kirsch < 0) ? 0 : kirsch);
			rImageData[y*mRowBytes + x * 3] = kirsch;

			kirsch = pBitData[3 * y * mWidth + x * 3 + 1];
			kirsch = (kirsch > 255) ? 255 : ((kirsch < 0) ? 0 : kirsch);
			rImageData[y*mRowBytes + x * 3 + 1] = kirsch;

			kirsch = pBitData[3 * y * mWidth + x * 3 + 2];
			kirsch = (kirsch > 255) ? 255 : ((kirsch < 0) ? 0 : kirsch);
			rImageData[y*mRowBytes + x * 3 + 2] = kirsch;
		}
	}

	if (pData)
		delete[] pData;
	pData = NULL;
	if (pBitData)
		delete pBitData;
	pBitData = NULL;
}

void CImageProcessingDoc::CreatGauss(double sigma, double** pdKernel, int* pnWidowSize)
{
	LONG i;
	//数组中心点 
	int nCenter;
	//数组中一点到中心点距离 
	double dDis;
	//中间变量 
	double dValue;
	double dSum;
	dSum = 0;
	// [-3*sigma,3*sigma] 以内数据，会覆盖绝大部分滤波系数 
	*pnWidowSize =(int)( 1 + 2 * ceil(3 * sigma));
	nCenter = (*pnWidowSize) / 2;
	*pdKernel = new double[*pnWidowSize];
	//生成高斯数据 
	for (i = 0; i < (*pnWidowSize); i++)
	{
		dDis = double(i - nCenter);
		dValue = exp(-(1 / 2) * dDis * dDis / (sigma * sigma)) /
			(sqrt(2 * 3.1415926) * sigma);
		(*pdKernel)[i] = dValue;
		dSum += dValue;
	}
	//归一化 
	for (i = 0; i < (*pnWidowSize); i++)
	{
		(*pdKernel)[i] /= dSum;
	}
}

//用高斯滤波器平滑原图像 
void CImageProcessingDoc::GaussianSmooth(int nHeight,int nWidth, LPBYTE pGray, LPBYTE pResult, double sigma)
{
	LONG x, y;
	LONG i;
	//高斯滤波器长度 
	int nWindowSize;
	//窗口长度 
	int nLen;
	//一维高斯滤波器 
	double* pdKernel;
	//高斯系数与图像数据的点乘 
	double dDotMul;
	//滤波系数总和 
	double dWeightSum;
	double* pdTemp = pdTemp = new double[nHeight * nWidth];
	//产生一维高斯数据 
	CreatGauss(sigma, &pdKernel, &nWindowSize);
	nLen = nWindowSize / 2;
	//x方向滤波 
	for (y = 0; y < nHeight; y++)
	{
		for (x = 0; x < nWidth; x++)
		{
			dDotMul = 0;
			dWeightSum = 0;
			for (i = (-nLen); i <= nLen; i++)
			{
				//判断是否在图像内部 
				if ((i + x) >= 0 && (i + x) < nWidth)
				{
					dDotMul += (double)
						pGray[y * nWidth + (i + x)] * pdKernel[nLen + i];
					dWeightSum += pdKernel[nLen + i];
				}
			}
			pdTemp[y * nWidth + x] = dDotMul / dWeightSum;
		}
	}
	//y方向滤波 
	for (x = 0; x < nWidth; x++)
	{
		for (y = 0; y < nHeight; y++)
		{
			dDotMul = 0;
			dWeightSum = 0;
			for (i = (-nLen); i <= nLen; i++)
			{
				if ((i + y) >= 0 && (i + y) < nHeight)
				{
					dDotMul += (double)
						pdTemp[(y + i) * nWidth + x] * pdKernel[nLen + i];
					dWeightSum += pdKernel[nLen + i];
				}
			}
			pResult[y * nWidth + x] = (unsigned char)(dDotMul / dWeightSum);
		}
	}
	delete[] pdKernel;
	pdKernel = NULL;
	delete[]pdTemp;
	pdTemp = NULL;
}

// 方向导数,求梯度 
void CImageProcessingDoc::Grad(int nHeight,int nWidth, LPBYTE pGray, int* pGradX, int* pGradY, int* pMag)
{
	LONG y, x;

	//x方向的方向导数 
	for (y = 1; y < nHeight - 1; y++)
	{
		for (x = 1; x < nWidth - 1; x++)
		{
			pGradX[y * nWidth + x] = (int)
				(pGray[y * nWidth + x + 1] - pGray[y * nWidth + x - 1]);
		}
	}

	//y方向方向导数 
	for (x = 1; x < nWidth - 1; x++)
	{
		for (y = 1; y < nHeight- 1; y++)
		{
			pGradY[y * nWidth + x] = (int)
				(pGray[(y + 1) * nWidth + x] - pGray[(y - 1) * nWidth + x]);
		}
	}

	//求梯度 

	//中间变量 
	double dSqt1;
	double dSqt2;

	for (y = 0; y < nHeight; y++)
	{
		for (x = 0; x < nWidth; x++)
		{
			//二阶范数求梯度 
			dSqt1 = pGradX[y * nWidth + x] * pGradX[y * nWidth + x];
			dSqt2 = pGradY[y * nWidth + x] * pGradY[y * nWidth + x];
			pMag[y * nWidth + x] = (int)(sqrt(dSqt1 + dSqt2) + 0.5);
		}
	}
}

//非最大抑制 
void CImageProcessingDoc::NonmaxSuppress(int* pMag, int* pGradX, int* pGradY, int nHeight,int nWidth, LPBYTE pNSRst)
{
	LONG y, x;
	int nPos;
	//梯度分量 
	int gx;
	int gy;
	//中间变量 
	int g1, g2, g3, g4;
	double weight;
	double dTmp, dTmp1, dTmp2;
	//设置图像边缘为不可能的分界点 
	for (x = 0; x < nWidth; x++)
	{
		pNSRst[x] = 0;
		pNSRst[(nHeight - 1) * nWidth + x] = 0;
	}
	for (y = 0; y < nHeight; y++)
	{
		pNSRst[y * nWidth] = 0;
		pNSRst[y * nWidth + nWidth - 1] = 0;
	}
	for (y = 1; y < nHeight - 1; y++)
	{
		for (x = 1; x < nWidth - 1; x++)
		{
			//当前点 
			nPos = y * nWidth + x;

			//如果当前像素梯度幅度为0，则不是边界点 
			if (pMag[nPos] == 0)
			{
				pNSRst[nPos] = 0;
			}
			else
			{
				//当前点的梯度幅度 
				dTmp = pMag[nPos];

				//x,y方向导数 
				gx = pGradX[nPos];
				gy = pGradY[nPos];

				//如果方向导数y分量比x分量大，说明导数方向趋向于y分量 
				if (abs(gy) > abs(gx))
				{
					//计算插值比例 
					weight = fabs(gx) / fabs(gy);

					g2 = pMag[nPos - nWidth];
					g4 = pMag[nPos + nWidth];

					//如果x,y两个方向导数的符号相同 
					//C 为当前像素，与g1-g4 的位置关系为： 
					//g1 g2 
					// C 
					// g4 g3 
					if (gx * gy > 0)
					{
						g1 = pMag[nPos - nWidth - 1];
						g3 = pMag[nPos + nWidth + 1];
					}

					//如果x,y两个方向的方向导数方向相反 
					//C是当前像素，与g1-g4的关系为： 
					// g2 g1 
					// C 
					// g3 g4 
					else
					{
						g1 = pMag[nPos - nWidth + 1];
						g3 = pMag[nPos + nWidth - 1];
					}
				}
				else //如果方向导数x分量比y分量大，说明导数的方向趋向于x分量
				{
					//插值比例 
					weight = fabs(gy) / fabs(gx);

					g2 = pMag[nPos + 1];
					g4 = pMag[nPos - 1];

					//如果x,y两个方向的方向导数符号相同 
					//当前像素C与 g1-g4的关系为 
					// g3 
					// g4 C g2 
					// g1 
					if (gx * gy > 0)
					{
						g1 = pMag[nPos + nWidth + 1];
						g3 = pMag[nPos - nWidth - 1];
					}
					else  //如果x,y两个方向导数的方向相反,C与g1-g4的关系为, g1 g4 C g2  g3
					{
						g1 = pMag[nPos - nWidth + 1];
						g3 = pMag[nPos + nWidth - 1];
					}
				}  //abs(gy) > abs(gx)

				   //利用 g1-g4 对梯度进行插值 

				dTmp1 = weight * g1 + (1 - weight) * g2;
				dTmp2 = weight * g3 + (1 - weight) * g4;

				//当前像素的梯度是局部的最大值 
				//该点可能是边界点 
				if (dTmp >= dTmp1 && dTmp >= dTmp2)
				{
					pNSRst[nPos] = 128;
				}
				else
				{
					//不可能是边界点 
					pNSRst[nPos] = 0;
				}
			}
		}
	}
}

// 统计pMag的直方图，判定阈值 
void CImageProcessingDoc::EstimateThreshold(int* pMag, int nHeight,int nWidth, int* pThrHigh, int* pThrLow,
	LPBYTE pGray, double dRatHigh, double dRatLow)
{
	LONG y, x, k;

	//该数组的大小和梯度值的范围有关，如果采用本程序的算法 
	//那么梯度的范围不会超过pow(2,10) 
	int nHist[256];

	//可能边界数 
	int nEdgeNum;

	//最大梯度数 
	int nMaxMag;

	int nHighCount;

	nMaxMag = 0;

	//初始化 
	for (k = 0; k < 256; k++)
	{
		nHist[k] = 0;
	}
	//统计直方图,利用直方图计算阈值 
	for (y = 0; y < nHeight; y++)
	{
		for (x = 0; x < nWidth; x++)
		{
			if (pGray[y * nWidth + x] == 128)
			{
				nHist[pMag[y * nWidth + x]]++;
			}
		}
	}

	nEdgeNum = nHist[0];
	nMaxMag = 0;

	//统计经过"非最大值抑制"后有多少像素 
	for (k = 1; k < 256; k++)
	{
		if (nHist[k] != 0)
		{
			nMaxMag = k;
		}

		//梯度为0的点是不可能为边界点的 
		//经过non-maximum suppression后有多少像素 
		nEdgeNum += nHist[k];
	}

	//梯度比高阈值*pThrHigh 小的像素点总书目 
	nHighCount = (int)(dRatHigh * nEdgeNum + 0.5);

	k = 1;
	nEdgeNum = nHist[1];

	//计算高阈值 
	while ((k < (nMaxMag - 1)) && (nEdgeNum < nHighCount))
	{
		k++;
		nEdgeNum += nHist[k];
	}

	*pThrHigh = k;

	//低阈值 
	*pThrLow = (int)((*pThrHigh) * dRatLow + 0.5);
}

//利用函数寻找边界起点 
void CImageProcessingDoc::Hysteresis(int* pMag, int nHeight,int nWidth, double dRatLow, double dRatHigh,LPBYTE pResult)
{
	LONG y, x;

	int nThrHigh, nThrLow;

	int nPos;
	//估计TraceEdge 函数需要的低阈值，以及Hysteresis函数使用的高阈值 
	EstimateThreshold(pMag, nHeight,nWidth, &nThrHigh, &nThrLow, pResult, dRatHigh,	dRatLow);

	//寻找大于dThrHigh的点，这些点用来当作边界点， 
	//然后用TraceEdge函数跟踪该点对应的边界 
	for (y = 0; y < nHeight; y++)
	{
		for (x = 0; x < nWidth; x++)
		{
			nPos = y * nWidth + x;

			//如果该像素是可能的边界点，并且梯度大于高阈值， 
			//该像素作为一个边界的起点 
			if ((pResult[nPos] == 128) && (pMag[nPos] >= nThrHigh))
			{
				//设置该点为边界点 
				pResult[nPos] = 255;
				TraceEdge(y, x, nThrLow, pResult, pMag, nHeight, nWidth);
			}
		}
	}

	//其他点已经不可能为边界点 
	for (y = 0; y < nHeight; y++)
	{
		for (x = 0; x < nWidth; x++)
		{
			nPos = y * nWidth + x;

			if (pResult[nPos] != 255)
			{
				pResult[nPos] = 0;
			}
		}
	}
}


//根据Hysteresis 执行的结果，从一个像素点开始搜索，搜索以该像素点为边界起点的一条边界的 
//一条边界的所有边界点，函数采用了递归算法 
// 从（x,y)坐标出发，进行边界点的跟踪，跟踪只考虑pResult中没有处理并且可能是边界 
// 点的像素（=128），像素值为0表明该点不可能是边界点，像素值为255表明该点已经是边界点 

void CImageProcessingDoc::TraceEdge(int y, int x, int nThrLow, LPBYTE pResult, int* pMag,int nHeight,int nWidth)
{
	//对8邻域像素进行查询 
	int xNum[8] =
	{
		1, 1, 0, -1, -1, -1, 0, 1
	};
	int yNum[8] =
	{
		0, 1, 1, 1, 0, -1, -1, -1
	};

	LONG yy, xx, k;

	for (k = 0; k < 8; k++)
	{
		yy = y + yNum[k];
		xx = x + xNum[k];

		if (pResult[yy * nWidth + xx] == 128 &&
			pMag[yy * nWidth + xx] >= nThrLow)
		{
			//该点设为边界点 
			pResult[yy * nWidth + xx] = 255;

			//以该点为中心再进行跟踪 
			TraceEdge(yy, xx, nThrLow, pResult, pMag, nHeight,nWidth);
		}
	}
}


// Canny算子 
void CImageProcessingDoc::CannyOperator(LPBYTE pGray, int nHeight,int nWidth, double sigma, double dRatLow,double dRatHigh, LPBYTE pResult)
{
	//经过高斯滤波后的图像 
	LPBYTE pGaussSmooth;
	pGaussSmooth = new unsigned char[nHeight * nWidth];
	//x方向导数的指针 
	int* pGradX;
	pGradX = new int[nHeight * nWidth];
	//y方向 
	int* pGradY;
	pGradY = new int[nHeight * nWidth];
	//梯度的幅度 
	int* pGradMag;
	pGradMag = new int[nHeight * nWidth];
	//对原图高斯滤波 
	GaussianSmooth(nHeight,nWidth, pGray, pGaussSmooth, sigma);
	//计算方向导数和梯度的幅度 
	Grad(nHeight,nWidth, pGaussSmooth, pGradX, pGradY, pGradMag);
	//应用非最大抑制 
	NonmaxSuppress(pGradMag, pGradX, pGradY, nHeight,nWidth, pResult);
	//应用Hysteresis，找到所有边界 
	Hysteresis(pGradMag, nHeight,nWidth, dRatLow, dRatHigh, pResult);
	delete[] pGradX;
	pGradX = NULL;
	delete[] pGradY;
	pGradY = NULL;
	delete[] pGradMag;
	pGradMag = NULL;
	delete[] pGaussSmooth;
	pGaussSmooth = NULL;
}

//魔镜（哈哈镜)变换
void CImageProcessingDoc::FunMirrorTransform(CImage * sImage, CImage * rImage, double degree, CPoint pt)
{
	if (sImage->IsNull())
		return;
	int nRows = sImage->GetHeight();
	int nCols = sImage->GetWidth();
	int nBPP = sImage->GetBPP();
	int nLineBytes = sImage->GetPitch();

	rImage->Destroy();
	if (!rImage->Create(nCols, nRows, nBPP))
		return;

	BYTE *sdata = (BYTE *)sImage->GetBits();
	BYTE *rdata = (BYTE *)rImage->GetBits();

	int tx;
	int ty;
	int newx;
	int newy;
	int x;
	int y;
	double  theta;
	int radius;
	int newRadius;
	for (y = 0; y < nRows; y++)
	for (x = 0; x < nCols; x++)
	{
		tx = x - pt.x;
		ty = y - pt.y;
		theta = atan2((double)ty, (double)tx);
		radius = (int)sqrt((double)(tx*tx + ty*ty));
		newRadius = (int)sqrt((double)radius*degree);
		newx = pt.x + (int)(newRadius*cos(theta));
		newy = pt.y + (int)(newRadius*sin(theta));
		if (newx < 0 || newx >= nCols)
		{
			newx = 0;
		}
		if (newy < 0 || newy >= nRows)
		{
			newy = 0;
		}
		rdata[y * nLineBytes + x * 3 + 0] = sdata[newy * nLineBytes + newx * 3 + 0];
		rdata[y * nLineBytes + x * 3 + 1] = sdata[newy * nLineBytes + newx * 3 + 1];
		rdata[y * nLineBytes + x * 3 + 2] = sdata[newy * nLineBytes + newx * 3 + 2];
	}
}


//图像脉冲噪声污染
void CImageProcessingDoc::ImagePeppperNoisePollution(CImage * pImg, double pa, double pb)
{
	int x;
	int y;
	int sWidth = pImg->GetWidth();
	int sHeight = pImg->GetHeight();
	int sRowBytes = pImg->GetPitch();
	BYTE *sImageData = (BYTE *)pImg->GetBits();
	//生成伪随机种子
	srand((unsigned)time(NULL));

    //在图像中添加脉冲噪声（椒盐噪声）
	for (y = 0; y < sHeight; y++)
	for (x = 0; x < sWidth; x++)
	{
		int srd = rand() % 100;
		if (srd > ((int)(100 * (1 - pb))))
		{
			//图像中当前点置为黑(噪声）	
			sImageData[y*sRowBytes + x * 3] = 0;
			sImageData[y*sRowBytes + x * 3 + 1] = 0;
			sImageData[y*sRowBytes + x * 3 + 2] = 0;
		}
		else if (srd < ((int)(100 * pa)))
		{
			sImageData[y*sRowBytes + x * 3] = 255;
			sImageData[y*sRowBytes + x * 3 + 1] = 255;
			sImageData[y*sRowBytes + x * 3 + 2] = 255;
		}
  	}

	return;
}

//图像均匀噪声污染
void CImageProcessingDoc::ImageUniformNoisePollution(CImage * pImg, double a, double b)
{
	int x;
	int y;
	int sWidth    = pImg->GetWidth();
	int sHeight   = pImg->GetHeight();
	int sRowBytes = pImg->GetPitch();

	BYTE *sImageData = (BYTE *)pImg->GetBits();

	int Uab = (int)(b - a);
	int grey;
	//随机噪声
	BYTE NoisePoint;

	//生成伪随机种子
	srand((unsigned)time(NULL));
	//在图像中加随机噪声
	for (y = 0; y < sHeight; y++)
	for (x = 0; x < sWidth; x++)
	{
		NoisePoint = rand() % Uab;
		grey = sImageData[y*sRowBytes + x * 3 + 0] + NoisePoint;
		grey = grey > 255 ? 255 : (grey < 0) ? 0 : grey;
		sImageData[y*sRowBytes + x * 3 + 0] = grey;
		grey = sImageData[y*sRowBytes + x * 3 + 1] + NoisePoint;
		grey = grey > 255 ? 255 : (grey < 0) ? 0 : grey;
		sImageData[y*sRowBytes + x * 3 + 1] = grey;
		grey = sImageData[y*sRowBytes + x * 3 + 2] + NoisePoint;
		grey = grey > 255 ? 255 : (grey < 0) ? 0 : grey;
		sImageData[y*sRowBytes + x * 3 + 2] = grey;
	}
	return;
}

//生成高斯分布随机数序列

double CImageProcessingDoc::generateGaussianNoise(double mu, double sigma)
{
	static const double esp = 1e-100;
	static double V1, V2, S;
	static int phase = 0;
	double X;
	double U1, U2;
	if (phase == 0) 
	{
		do {
			  U1 = (double)rand() / RAND_MAX;
			  U2 = (double)rand() / RAND_MAX;

			  V1 = 2 * U1 - 1;
			  V2 = 2 * U2 - 1;
			  S = V1 * V1 + V2 * V2;
		   } while (S >= 1 || S == 0);

		X = V1 * sqrt(-2 * log(S) / S);
	}
	else 
	{
		 X = V2 * sqrt(-2 * log(S) / S);
	}
	phase = 1 - phase;
	return mu + sigma*X;

}

//图像高斯噪声污染
void CImageProcessingDoc::ImageGauessNoisePollution(CImage * pImg, double mu, double sigma, double k)
{
	int x;
	int y;
	int sWidth = pImg->GetWidth();
	int sHeight = pImg->GetHeight();
	int sRowBytes = pImg->GetPitch();

	BYTE *sImageData = (BYTE *)pImg->GetBits();

	double NoiseValue;
	double val;
	srand((unsigned)time(NULL));
	//在图像中加高斯噪声
	for (y = 0; y < sHeight; y++)
	for (x = 0; x < sWidth; x++)
	{
		NoiseValue = generateGaussianNoise(mu, sigma);
		val = sImageData[y*sRowBytes + x * 3 + 0] + k * NoiseValue;
		val = (val > 255) ? 255 : ((val < 0) ? 0 : val);
		sImageData[y*sRowBytes + x * 3 + 0] = (int)val;

		val = sImageData[y*sRowBytes + x * 3 + 1] + k * NoiseValue;
		val = (val > 255) ? 255 : ((val < 0) ? 0 : val);
		sImageData[y*sRowBytes + x * 3 + 1] = (BYTE)val;

		val = sImageData[y*sRowBytes + x * 3 + 2] + k * NoiseValue;
		val = (val > 255) ? 255 : ((val < 0) ? 0 : val);
		sImageData[y*sRowBytes + x * 3 + 2] = (BYTE)val;
	}
	return;
}




//灰度直方图均衡化
void CImageProcessingDoc::HistogramEqualization(int * pData, int nHeight, int nWidth)
{
	int x;
	int y;
    double  shist[256];
	double  rhist[256];
	int temp;
	memset(shist, 0, 256 * sizeof(double));
	memset(rhist, 0, 256 * sizeof(double));
	

	for (y = 1; y < nHeight - 1; y++)
	for (x = 1; x < nWidth - 1; x++)
	{
		shist[pData[y*nWidth+x]]++;
	}

	for (x = 0; x < 256;x++)
	{
		for (y = 0; y < x;y++)
		  rhist[x] += shist[y];

		rhist[x] /= nHeight*nWidth;
	}


	for (y = 0; y <nHeight; y++)
	for (x = 0; x < nWidth; x++)
	{
		temp = (int) (255 * rhist[pData[y*nWidth + x]]);
		if (temp < 0)	temp = 0;
		else if (temp > 255)   temp = 255;
		pData[y*nWidth + x] = temp;
	}

	return;
}

// FFT1DandIFFT1D 一维快速傅立叶变换与逆变换函数 
// 输入时域数据实部为Tr,虚部为Ti
// 输出频域数据实部为Tr,虚部为Ti
// 序列长度N，N等于2的r次幂
// FFTorIFFT,逻辑变量，非零做正变换，零做反变换
void CImageProcessingDoc::FFT1DandIFFT1D(float * Tr, float * Ti, int N, bool bFFTorIFFT)
{
		int r;   //迭代次数
		int l, j, k;//循环变量

		int p;  //用于蝶形计算加权系数的指数
		int B;  //对偶结点距离

		float  X, Y, XX, YY;
		float  w;
		float  cosw, sinw;

		if (!bFFTorIFFT)
		{ //如果做傅立叶你变换，则必须对数列除以N
			for (l = 0; l < N; l++)
			{
				Tr[l] /= N;
				Ti[l] /= N;
			}
		}

		//计算循环次数r
		r = 0;	l = N;
		while (l /= 2)  r++;

		//倒序
		int  LH = N / 2;
		int i;
		float temp;
		j = 0;
		for (i = 1; i < N - 1; i++)
		{
			k = LH;
			while (j >= k)
			{
				j = j - k;
				k = k / 2;
			}
			j = j + k;
			if (i <= j)
			{
				temp = Tr[i]; Tr[i] = Tr[j]; Tr[j] = temp;
				temp = Ti[i]; Ti[i] = Ti[j]; Ti[j] = temp;
			}
		}


		for (l = 0; l <= r; l++)  //共r级
		{
			B = 1 << (l - 1); // 第l层对偶结点距离为2^(l-1)
			for (j = 0; j < B; j++)
			{
				p = j*(1 << (r - l));
				w = (float)(2 * PI*p / N);
				for (k = j; k < N - 1; k += (1 << l))
				{
					if (bFFTorIFFT)
					{  //若做傅立叶正变换
						cosw = cos(-w);
						sinw = sin(-w);
					}
					else
					{  //傅立叶反变换
						cosw = cos(w);
						sinw = sin(w);
					}


					X = Tr[k] + Tr[k + B] * cosw - Ti[k + B] * sinw;
					Y = Ti[k] + Tr[k + B] * sinw + Ti[k + B] * cosw;

					XX = Tr[k] - Tr[k + B] * cosw + Ti[k + B] * sinw;
					YY = Ti[k] - Tr[k + B] * sinw - Ti[k + B] * cosw;

					Tr[k] = X;
					Ti[k] = Y;

					Tr[k + B] = XX;
					Ti[k + B] = YY;
				}
			}
		}
}

// FFT2DandIFFT2D 二维快速傅立叶变换与逆变换函数 
// 输入数据实部数组inDataReal,虚部数组inDataImage
// 输出数据实部数组outDataReal,虚部数组outDataImage
// 二维数组高度M宽度N(M和N都等于2的某次幂）
// 逻辑类型变量bFFTorIFFT：0 - 进行Fourier逆变换；否则进行Fouridr变换

void CImageProcessingDoc::FFT2DandIFFT2D(float * inDataReal, float * inDataImage, float * outDataReal, float * outDataImage, int M, int N, bool bFFTorIFFT)
{
	int i, j;

	float *Tr;
	float *Ti;

	Tr = new float[N];
	Ti = new float[N];

	//每行进行傅立叶变换
	for (i = 0; i < M; i++)
	{
		for (j = 0; j < N; j++)
		{
			Tr[j] = inDataReal[i*N + j];
			Ti[j] = inDataImage[i*N + j];
		}

		if (bFFTorIFFT)
			FFT1DandIFFT1D(Tr, Ti, N, 1);
		else
			FFT1DandIFFT1D(Tr, Ti, N, 0);

		for (j = 0; j < M; j++)
		{
			outDataReal[i*N + j] = Tr[j];
			outDataImage[i*N + j] = Ti[j];
		}
	}

	delete Tr;
	delete Ti;

	Tr = new float[M];
	Ti = new float[M];


	//每列进行傅立叶变换		
	for (j = 0; j < N; j++)
	{
		for (i = 0; i < M; i++)
		{
			Tr[i] = outDataReal[i*N + j];
			Ti[i] = outDataImage[i*N + j];
		}

		if (bFFTorIFFT)
			FFT1DandIFFT1D(Tr, Ti, M, 1);
		else
			FFT1DandIFFT1D(Tr, Ti, M, 0);
		for (i = 0; i < M; i++)
		{
			outDataReal[i*N + j] = Tr[i];
			outDataImage[i*N + j] = Ti[i];
		}
	}

	delete Tr;
	delete Ti;

	return;
}


void CImageProcessingDoc::DFT1DandIDFT1D(float * Tr, float * Ti, int N, bool bDFTorIDFT)
{
	int u;
	int x;
	float * Fr = new float[N];
	float * Fi = new float[N];
	float w;
	for (u = 0; u < N; u++)
	{
		if (bDFTorIDFT)
		{
			w = (float)( -2 * PI * u);
		}
		
		else
		{		
			w = (float)(2 * PI * u);
		}

		Fr[u] = 0;
		Fi[u]= 0;
		for (x = 0; x < N; x++)
		{
			Fr[u] += Tr[x] * cos(w*x) - Ti[x] * sin(w*x);
			Fi[u] += Tr[x] * sin(w*x) + Ti[x] * cos(w*x);
		}
	}

	for (x = 0; x < N; x++)
	{
		if (bDFTorIDFT)
        { 
			Tr[x] = Fr[x];
 			Ti[x] = Fi[x];
        }
		else
		{
			Tr[x] = (float)(Fr[x]*1.0/N);
			Ti[x] = (float)(Fi[x]*1.0/N);
		}

	}

	delete[] Fr;
	delete[] Fi;
	return;
}


void CImageProcessingDoc::DFT2DandIDFT2D(float * inDataReal, float * inDataImage, float * outDataReal, float * outDataImage, int M, int N, bool bDFTorIDFT)
{
	int i, j;

	float *Tr;
	float *Ti;

	Tr = new float[N];
	Ti = new float[N];

	//每行进行傅立叶变换
	for (i = 0; i < M; i++)
	{
		for (j = 0; j < N; j++)
		{
			Tr[j] = (float)(inDataReal[i*N + j]);
			Ti[j] = (float)(inDataImage[i*N + j]);
		}

		if (bDFTorIDFT)
			DFT1DandIDFT1D(Tr, Ti, N, 1);
		else
			DFT1DandIDFT1D(Tr, Ti, N, 0);

		for (j = 0; j < M; j++)
		{
			outDataReal[i*N + j] = Tr[j];
			outDataImage[i*N + j] = Ti[j];
		}
	}

	delete Tr;
	delete Ti;

	Tr = new float[M];
	Ti = new float[M];


	//每列进行傅立叶变换		
	for (j = 0; j < N; j++)
	{
		for (i = 0; i < M; i++)
		{
			Tr[i] = outDataReal[i*N + j];
			Ti[i] = outDataImage[i*N + j];
		}

		if (bDFTorIDFT)
			DFT1DandIDFT1D(Tr, Ti, M, 1);
		else
			DFT1DandIDFT1D(Tr, Ti, M, 0);
		for (i = 0; i < M; i++)
		{
			outDataReal[i*N + j] = Tr[i];
			outDataImage[i*N + j] = Ti[i];
		}
	}

	delete Tr;
	delete Ti;

	return;
}

//复数格式；频域变换函数

void CImageProcessingDoc::DCT1DandIDCT1D(float *pfF, int N, bool bDctIDct)
{
	float *mR;
	float *mI;
	int  i;
    
	mR = new float[N*2];
	mI = new float[N*2];
	
	if(bDctIDct)
	{
		for(i=0;i<2*N;i++)
		{
			if(i<N)
				mR[i] = pfF[i];
			else
				mR[i] = 0;
			mI[i] = 0;      
		}
		
		
		FFT1DandIFFT1D(mR,mI,2*N,true);
		
		pfF[0] = (float)(mR[0]*sqrt(1.0/N));

		for(i=1;i<N;i++)
			pfF[i] = (float)((mR[i]*cos(i*PI/(2*N)) + mI[i]*sin(i*PI/(2*N))) *sqrt(2.0/N));
	}
	else
	{
		
		for(i=0;i<2*N;i++)
		{
			if(i<N)
			{
				mR[i] = (float)(pfF[i]*cos(i*PI/(2*N)));
				mI[i] = (float)(pfF[i]*sin(i*PI/(2*N)));            
			}
			else
			{
				mR[i] = 0;
				mI[i] = 0;      
			}
		}
				
		FFT1DandIFFT1D(mR,mI,2*N,false);
		
		float  temp = (float)sqrt(2.0/N);
		float d0 = (float)((sqrt(1.0/N) - temp)*pfF[0]);

		for(i=0;i<N;i++)
			pfF[i] =  (float)(d0 + 2*N*mR[i]*temp);  
	}
    
	delete mR;
	delete mI;
	return;

}

void CImageProcessingDoc::DCT2DandIDCT2D(float *inData, float *outData, int M, int N, BOOL bDCTorIDCT)
{
     
    int i,j;
    
    float *Tdata = new float[N];

	//每行进行DCT变换
	for (i=0;i<M;i++)
	{ 
	   for (j=0;j<N;j++)
	   {
		   Tdata[j] = inData[i*N + j];
	   }
	   
	   if (bDCTorIDCT)
	   	   DCT1DandIDCT1D(Tdata,N,TRUE);
	   else
		   DCT1DandIDCT1D(Tdata,N,FALSE);

	   for (j=0;j<M;j++)
	   {
			outData[i*N + j]  = Tdata[j];
	   }
	}

	delete Tdata;
			
	Tdata = new float[M];

	//每列进行DCT变换		
	for(j=0;j<N;j++)
	{  
		for (i=0;i<M;i++)
		{
			Tdata[i] = outData[i*N + j];
		}
				
		if (bDCTorIDCT)
			DCT1DandIDCT1D(Tdata,M,TRUE);
		else
		    DCT1DandIDCT1D(Tdata,M,FALSE);
		
		for (i=0;i<M;i++)
		{
			outData[i*N + j]  = Tdata[i];
		}
	}

	delete Tdata;	
	return;
}







// CImageProcessingDoc 命令


void CImageProcessingDoc::OnFileOpen()
{
	// TODO: 在此添加命令处理程序代码
	CString strFilter;
	CSimpleArray<GUID>  aguidFileTypes;
	HRESULT hResult;

	// 获取CImage支持的图像文件的过滤字符串
	hResult = m_sImage.GetExporterFilterString(strFilter,aguidFileTypes, _T( "All Image Files") );
	if (FAILED(hResult)) 
	{
		AfxMessageBox(_T("GetExporterFilter函数失败!"));
		return;
	}

	CFileDialog dlg(TRUE, NULL, NULL, OFN_FILEMUSTEXIST, strFilter);
	if(IDOK != dlg.DoModal()) 
		return;

	m_sImage.Destroy();
	m_rImage.Destroy();

	// 将外部图像文件装载到CImage对象中
	hResult = m_sImage.Load(dlg.GetPathName());
	if (FAILED(hResult)) 
	{
		AfxMessageBox(_T("图像文件加载失败！"));
		return;
	}

	if(m_sImage.GetBPP() != 24)
	{
		m_sImage.Destroy();
		AfxMessageBox(_T("只处理24位色图像！"));
		return;
	}
	
	// 设置主窗口标题栏内容
	CString str;
	str.LoadString(AFX_IDS_APP_TITLE);
	AfxGetMainWnd()->SetWindowText(str + " - " +dlg.GetFileName());
	InvalidateRect(NULL,NULL,FALSE); 
}

void CImageProcessingDoc::OnFileSaveAs()
{
	// TODO: 在此添加命令处理程序代码
	if (m_rImage.IsNull())
	{
		AfxMessageBox(_T("还未进行图像处理！"));
		return;
	}

	CString strFilter;

	strFilter = "位图文件| *.bmp | JPEG图像文件| *.jpg |GIF图像文件| *.gif | PNG图像文件| *.png || "; 
	CFileDialog dlg(FALSE, NULL, NULL, NULL, strFilter);
	if (IDOK != dlg.DoModal())
		return;

	//如果用户没有指定文件扩展名，则为其添加一个
	CString strFileName;
	CString strExtension;
	strFileName = dlg.m_ofn.lpstrFile;
	if (dlg.m_ofn.nFileExtension != 0)
	{
		switch (dlg.m_ofn.nFilterIndex)
		{
		case 1:
			strExtension = "bmp"; break;
		case 2:
			strExtension = "jpg"; break;
		case 3:
			strExtension = "gif"; break;
		case 4:
			strExtension = "png"; break;
		default:
			break;
		}
		strFileName = strFileName + '.' + strExtension;
	}
	// 图像保存
	HRESULT hResult = m_rImage.Save(strFileName);
	if (FAILED(hResult))
	   AfxMessageBox(_T("保存图像文件失败！")); 
	return;
}

void CImageProcessingDoc::OnRgbRed()
{
	// TODO: 在此添加命令处理程序代码
	if (m_sImage.IsNull())
	{
		AfxMessageBox(_T("请打开要处理的图像！"));
		return;
	}

	int x;
	int y;
	int nRows = m_sImage.GetHeight();
	int nCols = m_sImage.GetWidth();
	int nBPP =  m_sImage.GetBPP();

	BYTE  nGrey;
	m_rImage.Destroy();

	if (!m_rImage.Create(nCols, nRows, nBPP))
		return;
	BYTE *sImageData = (BYTE *)m_sImage.GetBits();
	BYTE *rImageData = (BYTE *)m_rImage.GetBits();
	int nRowBytes    = m_sImage.GetPitch();

	for (y = 0; y < nRows; y++)
	for (x = 0; x < nCols; x++)
	{
		nGrey  = *(sImageData + y * nRowBytes + x * 3 + 2);
		rImageData[y * nRowBytes + x * 3]     = nGrey;
		rImageData[y * nRowBytes + x * 3 + 1] = nGrey;
		rImageData[y * nRowBytes + x * 3 + 2] = nGrey;
	 }

	UpdateAllViews(NULL); 
}


void CImageProcessingDoc::OnRgbGreen()
{
	// TODO: 在此添加命令处理程序代码
	if (m_sImage.IsNull())
	{
		AfxMessageBox(_T("请打开要处理的图像！"));
		return;
	}

	int x;
	int y;
	int nRows = m_sImage.GetHeight();
	int nCols = m_sImage.GetWidth();
	int nBPP =  m_sImage.GetBPP();

	BYTE  nGrey;
	m_rImage.Destroy();

	if (!m_rImage.Create(nCols, nRows, nBPP))
		return;
	BYTE *sImageData = (BYTE *)m_sImage.GetBits();
	BYTE *rImageData = (BYTE *)m_rImage.GetBits();
	int nRowBytes    = m_sImage.GetPitch();

	for (y = 0; y < nRows; y++)
	for (x = 0; x < nCols; x++)
	{
		nGrey  = *(sImageData + y * nRowBytes + x * 3 + 1);
		rImageData[y * nRowBytes + x * 3]     = nGrey;
		rImageData[y * nRowBytes + x * 3 + 1] = nGrey;
		rImageData[y * nRowBytes + x * 3 + 2] = nGrey;
	 }

	UpdateAllViews(NULL); 
}


void CImageProcessingDoc::OnRgbBlue()
{
	// TODO: 在此添加命令处理程序代码
	if (m_sImage.IsNull())
	{
		AfxMessageBox(_T("请打开要处理的图像！"));
		return;
	}

	int x;
	int y;
	int nRows = m_sImage.GetHeight();
	int nCols = m_sImage.GetWidth();
	int nBPP =  m_sImage.GetBPP();

	BYTE  nGrey;
	m_rImage.Destroy();

	if (!m_rImage.Create(nCols, nRows, nBPP))
		return;
	BYTE *sImageData = (BYTE *)m_sImage.GetBits();
	BYTE *rImageData = (BYTE *)m_rImage.GetBits();
	int nRowBytes    = m_sImage.GetPitch();

	for (y = 0; y < nRows; y++)
	for (x = 0; x < nCols; x++)
	{
		nGrey  = *(sImageData + y * nRowBytes + x * 3 + 0);
		rImageData[y * nRowBytes + x * 3]     = nGrey;
		rImageData[y * nRowBytes + x * 3 + 1] = nGrey;
		rImageData[y * nRowBytes + x * 3 + 2] = nGrey;
	 }

	UpdateAllViews(NULL); 
}


void CImageProcessingDoc::OnColortogrey()
{
	// TODO: 在此添加命令处理程序代码
	if (m_sImage.IsNull())
	{
		AfxMessageBox(_T("请打开要处理的图像！"));
		return;
	}
    // 直接访问图像数据
	int x;
	int y;
	int nRows = m_sImage.GetHeight();
	int nCols = m_sImage.GetWidth();
	int nBPP =  m_sImage.GetBPP();

	BYTE nRed, nGreen, nBlue, nGrey;
	m_rImage.Destroy();

	if (!m_rImage.Create(nCols, nRows, nBPP))
		return;

	BYTE *sImageData = (BYTE *)m_sImage.GetBits();
	BYTE *rImageData = (BYTE *)m_rImage.GetBits();
	int nRowBytes    = m_sImage.GetPitch();

	for (y = 0; y < nRows; y++)
	for (x = 0; x < nCols; x++)
	{
		nBlue  = sImageData[y * nRowBytes + x * 3 + 0];
		nGreen = sImageData[y * nRowBytes + x * 3 + 1];
		nRed   = sImageData[y * nRowBytes + x * 3 + 2];
		nGrey = (BYTE)(0.299*nRed + 0.587*nGreen + 0.114*nBlue);  //这里可以用（nRed+nGreen+nBlue)/3 
		rImageData[y * nRowBytes + x * 3]     = nGrey;
		rImageData[y * nRowBytes + x * 3 + 1] = nGrey;
		rImageData[y * nRowBytes + x * 3 + 2] = nGrey;
	 }

	UpdateAllViews(NULL); 
}


void CImageProcessingDoc::OnHsvHue()
{
	// TODO: 在此添加命令处理程序代码
	if (m_sImage.IsNull())
	{
		AfxMessageBox(_T("请打开要处理的图像！"));
		return;
	}

	int x;
	int y;
	int nRows = m_sImage.GetHeight();
	int nCols = m_sImage.GetWidth();
	int nBPP =  m_sImage.GetBPP();

	BYTE nRed, nGreen, nBlue,nGrey;
	double  dHue;
	m_rImage.Destroy();

	if (!m_rImage.Create(nCols, nRows, nBPP))
		return;
	BYTE *sImageData = (BYTE *)m_sImage.GetBits();
	BYTE *rImageData = (BYTE *)m_rImage.GetBits();
	int nRowBytes    = m_sImage.GetPitch();

	for (y = 0; y < nRows; y++)
	for (x = 0; x < nCols; x++)
	{
		nBlue  = sImageData[y * nRowBytes + x * 3 + 0];
		nGreen = sImageData[y * nRowBytes + x * 3 + 1];
		nRed   = sImageData[y * nRowBytes + x * 3 + 2];
		if (nRed == nGreen && nBlue == nRed)
			dHue = 0.0;
		else
		{
			dHue = acos(0.5*((nRed - nGreen) + (nRed - nBlue)) / sqrt((nRed - nGreen)*(nRed - nGreen) + (nRed - nBlue)*(nGreen - nBlue)));
		    if( nBlue > nGreen )
				dHue   = 2 * PI  - dHue;	
		}
		nGrey = (BYTE)(255.0 * dHue / (2 * PI));
		rImageData[y * nRowBytes + x * 3]     = (BYTE) nGrey;
		rImageData[y * nRowBytes + x * 3 + 1] = (BYTE) nGrey;
		rImageData[y * nRowBytes + x * 3 + 2] = (BYTE) nGrey;
	 }

	UpdateAllViews(NULL); 
}


void CImageProcessingDoc::OnHsvSaturation()
{
	// TODO: 在此添加命令处理程序代码
	if (m_sImage.IsNull())
	{
		AfxMessageBox(_T("请打开要处理的图像！"));
		return;
	}

	int x;
	int y;
	int nRows = m_sImage.GetHeight();
	int nCols = m_sImage.GetWidth();
	int nBPP =  m_sImage.GetBPP();

	BYTE nRed, nGreen, nBlue,nGrey;
	double  dSaturation;
	m_rImage.Destroy();

	if (!m_rImage.Create(nCols, nRows, nBPP))
		return;
	BYTE *sImageData = (BYTE *)m_sImage.GetBits();
	BYTE *rImageData = (BYTE *)m_rImage.GetBits();
	int nRowBytes    = m_sImage.GetPitch();

	for (y = 0; y < nRows; y++)
	for (x = 0; x < nCols; x++)
	{
		nBlue  = sImageData[y * nRowBytes + x * 3 + 0];
		nGreen = sImageData[y * nRowBytes + x * 3 + 1];
		nRed   = sImageData[y * nRowBytes + x * 3 + 2];

		nGrey = nRed;
		if (nGrey>nGreen) nGrey = nGreen;
		if (nGrey>nBlue) nGrey = nBlue;
		dSaturation = 1.0 - 3.0*(((double)nGrey) / ((double)(nRed + nGreen + nBlue)));

		nGrey = (BYTE)(255.0 * dSaturation);
		rImageData[y * nRowBytes + x * 3]     = (BYTE) nGrey;
		rImageData[y * nRowBytes + x * 3 + 1] = (BYTE) nGrey;
		rImageData[y * nRowBytes + x * 3 + 2] = (BYTE) nGrey;
	 }

	UpdateAllViews(NULL); 
}


void CImageProcessingDoc::OnHsvIntensity()
{
	// TODO: 在此添加命令处理程序代码
	if (m_sImage.IsNull())
	{
		AfxMessageBox(_T("请打开要处理的图像！"));
		return;
	}

	int x;
	int y;
	int nRows = m_sImage.GetHeight();
	int nCols = m_sImage.GetWidth();
	int nBPP =  m_sImage.GetBPP();

	BYTE nRed, nGreen, nBlue,nGrey;
	double  dIntensity;
	m_rImage.Destroy();

	if (!m_rImage.Create(nCols, nRows, nBPP))
		return;
	BYTE *sImageData = (BYTE *)m_sImage.GetBits();
	BYTE *rImageData = (BYTE *)m_rImage.GetBits();
	int nRowBytes    = m_sImage.GetPitch();

	for (y = 0; y < nRows; y++)
	for (x = 0; x < nCols; x++)
	{
		nBlue  = sImageData[y * nRowBytes + x * 3 + 0];
		nGreen = sImageData[y * nRowBytes + x * 3 + 1];
		nRed   = sImageData[y * nRowBytes + x * 3 + 2];

		dIntensity = (nRed + nGreen + nBlue) / 3.0;

		nGrey = (BYTE)dIntensity;
		rImageData[y * nRowBytes + x * 3]     = (BYTE) nGrey;
		rImageData[y * nRowBytes + x * 3 + 1] = (BYTE) nGrey;
		rImageData[y * nRowBytes + x * 3 + 2] = (BYTE) nGrey;
	 }

	UpdateAllViews(NULL); 

}


void CImageProcessingDoc::OnYcbcrY()
{
	// TODO: 在此添加命令处理程序代码
	if (m_sImage.IsNull())
	{
		AfxMessageBox(_T("请打开要处理的图像！"));
		return;
	}

    // 直接访问图像数据
	int x;
	int y;
	int nRows = m_sImage.GetHeight();
	int nCols = m_sImage.GetWidth();
	int nBPP =  m_sImage.GetBPP();

	BYTE nRed, nGreen, nBlue, nGrey;
	double dY;
	m_rImage.Destroy();

	if (!m_rImage.Create(nCols, nRows, nBPP))
		return;
	BYTE *sImageData = (BYTE *)m_sImage.GetBits();
	BYTE *rImageData = (BYTE *)m_rImage.GetBits();
	int nRowBytes    = m_sImage.GetPitch();

	for (y = 0; y < nRows; y++)
	for (x = 0; x < nCols; x++)
	{
		nBlue  = sImageData[y * nRowBytes + x * 3 + 0];
		nGreen = sImageData[y * nRowBytes + x * 3 + 1];
		nRed   = sImageData[y * nRowBytes + x * 3 + 2];
		dY = 0.299*nRed + 0.587*nGreen + 0.114*nBlue; 
		nGrey = (BYTE)dY;
		rImageData[y * nRowBytes + x * 3]     = nGrey;
		rImageData[y * nRowBytes + x * 3 + 1] = nGrey;
		rImageData[y * nRowBytes + x * 3 + 2] = nGrey;
	 }

	UpdateAllViews(NULL);
}


void CImageProcessingDoc::OnYcbcrCb()
{
	// TODO: 在此添加命令处理程序代码
	if (m_sImage.IsNull())
	{
		AfxMessageBox(_T("请打开要处理的图像！"));
		return;
	}

    // 直接访问图像数据
	int x;
	int y;
	int nRows = m_sImage.GetHeight();
	int nCols = m_sImage.GetWidth();
	int nBPP =  m_sImage.GetBPP();

	BYTE nRed, nGreen, nBlue, nGrey;
	double dCb;
	m_rImage.Destroy();

	if (!m_rImage.Create(nCols, nRows, nBPP))
		return;
	BYTE *sImageData = (BYTE *)m_sImage.GetBits();
	BYTE *rImageData = (BYTE *)m_rImage.GetBits();
	int nRowBytes    = m_sImage.GetPitch();

	for (y = 0; y < nRows; y++)
	for (x = 0; x < nCols; x++)
	{
		nBlue  = sImageData[y * nRowBytes + x * 3 + 0];
		nGreen = sImageData[y * nRowBytes + x * 3 + 1];
		nRed   = sImageData[y * nRowBytes + x * 3 + 2];
		dCb = -0.1687*nRed - 0.3313*nGreen + 0.5*nBlue + 128; 
		nGrey = (BYTE)dCb;
		rImageData[y * nRowBytes + x * 3]     = nGrey;
		rImageData[y * nRowBytes + x * 3 + 1] = nGrey;
		rImageData[y * nRowBytes + x * 3 + 2] = nGrey;
	 }

	UpdateAllViews(NULL);
}


void CImageProcessingDoc::OnYcbcrCr()
{
	// TODO: 在此添加命令处理程序代码
	if (m_sImage.IsNull())
	{
		AfxMessageBox(_T("请打开要处理的图像！"));
		return;
	}

    // 直接访问图像数据
	int x;
	int y;
	int nRows = m_sImage.GetHeight();
	int nCols = m_sImage.GetWidth();
	int nBPP =  m_sImage.GetBPP();

	BYTE nRed, nGreen, nBlue, nGrey;
	double dCr;
	m_rImage.Destroy();

	if (!m_rImage.Create(nCols, nRows, nBPP))
		return;
	BYTE *sImageData = (BYTE *)m_sImage.GetBits();
	BYTE *rImageData = (BYTE *)m_rImage.GetBits();
	int nRowBytes    = m_sImage.GetPitch();

	for (y = 0; y < nRows; y++)
	for (x = 0; x < nCols; x++)
	{
		nBlue  = sImageData[y * nRowBytes + x * 3 + 0];
		nGreen = sImageData[y * nRowBytes + x * 3 + 1];
		nRed   = sImageData[y * nRowBytes + x * 3 + 2];
		dCr = 0.5*nRed - 0.4187*nGreen -0.0813*nBlue + 128; 
		nGrey = (BYTE)dCr;
		rImageData[y * nRowBytes + x * 3 + 0]     = nGrey;
		rImageData[y * nRowBytes + x * 3 + 1] = nGrey;
		rImageData[y * nRowBytes + x * 3 + 2] = nGrey;
	 }

	UpdateAllViews(NULL);
}


void CImageProcessingDoc::OnImageAdd()
{
	// TODO: 在此添加命令处理程序代码
	if (m_sImage.IsNull())
	{
		AfxMessageBox(_T("请打开要处理的图像！"));
		return;
	}

	CImage lsImage;
	CString strFilter;
	CSimpleArray<GUID>  aguidFileTypes;
	HRESULT hResult;

	// 获取CImage支持的图像文件的过滤字符串
	hResult = m_sImage.GetExporterFilterString(strFilter, aguidFileTypes, _T("All Image Files"));
	if (FAILED(hResult))
	{
		AfxMessageBox(_T("GetExporterFilter函数失败!"));
		return;
	}

	CFileDialog dlg(TRUE, NULL, NULL, OFN_FILEMUSTEXIST, strFilter);
	if (IDOK != dlg.DoModal())
		return;

	lsImage.Destroy();
	
	// 将外部图像文件装载到CImage对象中
	hResult = lsImage.Load(dlg.GetPathName());
	if (FAILED(hResult))
	{
		AfxMessageBox(_T("图像文件加载失败！"));
		return;
	}

	if (lsImage.GetBPP() != 24)
	{
		lsImage.Destroy();
		AfxMessageBox(_T("只处理24位色图像！"));
		return;
	}

	if( ( lsImage.GetHeight() != m_sImage.GetHeight() ) || ( lsImage.GetWidth() != m_sImage.GetWidth() ) )
	{
		lsImage.Destroy();
		AfxMessageBox(_T("本软件只处理相同大小图像的逻辑与代数运算！"));
		return;
	}

	CDialogImageAddRatio mdlg;
	if (mdlg.DoModal() != IDOK)
	{
		lsImage.Destroy();
		return;
	}

	double lambuda = mdlg.addRatio / 100.0;
	
	int x;
	int y;
	int nRows = m_sImage.GetHeight();
	int nCols = m_sImage.GetWidth();
	int nBPP  = m_sImage.GetBPP();

	m_rImage.Destroy();
	if (!m_rImage.Create(nCols, nRows, nBPP))
	{
		lsImage.Destroy();
		return;
	}

	BYTE *sImageData  = (BYTE *)m_sImage.GetBits();
	BYTE *lsImageData = (BYTE *)lsImage.GetBits();
	BYTE *rImageData  = (BYTE *)m_rImage.GetBits();
	int nRowBytes = m_sImage.GetPitch();

	int sRowBytes = m_sImage.GetPitch();
	
	for (y = 0; y < nRows; y++)
	for (x = 0; x < nCols ; x++)
	{
		rImageData[y * nRowBytes + x * 3 + 0] = (int)(lambuda * sImageData[y * nRowBytes + x * 3 + 0] + (1- lambuda) * lsImageData[y * nRowBytes + x * 3 + 0] );
		rImageData[y * nRowBytes + x * 3 + 1] = (int)(lambuda * sImageData[y * nRowBytes + x * 3 + 1] + (1 - lambuda) * lsImageData[y * nRowBytes + x * 3 + 1]);
		rImageData[y * nRowBytes + x * 3 + 2] = (int)(lambuda * sImageData[y * nRowBytes + x * 3 + 2] + (1 - lambuda) * lsImageData[y * nRowBytes + x * 3 + 2]);
	}
	
	lsImage.Destroy();
   
	UpdateAllViews(NULL);
}



void CImageProcessingDoc::OnImageSub()
{
	// TODO: 在此添加命令处理程序代码
	if (m_sImage.IsNull())
	{
		AfxMessageBox(_T("请打开要处理的图像！"));
		return;
	}

	CImage lsImage;
	CString strFilter;
	CSimpleArray<GUID>  aguidFileTypes;
	HRESULT hResult;

	// 获取CImage支持的图像文件的过滤字符串
	hResult = m_sImage.GetExporterFilterString(strFilter, aguidFileTypes, _T("All Image Files"));
	if (FAILED(hResult))
	{
		AfxMessageBox(_T("GetExporterFilter函数失败!"));
		return;
	}

	CFileDialog dlg(TRUE, NULL, NULL, OFN_FILEMUSTEXIST, strFilter);
	if (IDOK != dlg.DoModal())
		return;

	lsImage.Destroy();
	
	// 将外部图像文件装载到CImage对象中
	hResult = lsImage.Load(dlg.GetPathName());
	if (FAILED(hResult))
	{
		AfxMessageBox(_T("图像文件加载失败！"));
		return;
	}

	if (lsImage.GetBPP() != 24)
	{
		lsImage.Destroy();
		AfxMessageBox(_T("只处理24位色图像！"));
		return;
	}

	if( ( lsImage.GetHeight() != m_sImage.GetHeight() ) || ( lsImage.GetWidth() != m_sImage.GetWidth() ) )
	{
		lsImage.Destroy();
		AfxMessageBox(_T("本软件只处理相同大小图像的逻辑与代数运算！"));
		return;
	}

	CDialogImageAddRatio mdlg;
	if (mdlg.DoModal() != IDOK)
	{
		lsImage.Destroy();
		return;
	}

	double lambuda = mdlg.addRatio / 100.0;
	
	int x;
	int y;
	int nRows = m_sImage.GetHeight();
	int nCols = m_sImage.GetWidth();
	int nBPP  = m_sImage.GetBPP();

	m_rImage.Destroy();
	if (!m_rImage.Create(nCols, nRows, nBPP))
	{
		lsImage.Destroy();
		return;
	}

	BYTE *sImageData  = (BYTE *)m_sImage.GetBits();
	BYTE *lsImageData = (BYTE *)lsImage.GetBits();
	BYTE *rImageData  = (BYTE *)m_rImage.GetBits();
	int nRowBytes = m_sImage.GetPitch();

	int sRowBytes = m_sImage.GetPitch();
	int nrgb;
	for (y = 0; y < nRows; y++)
	for (x = 0; x < nCols ; x++)
	{
		nrgb = (int)(lambuda * sImageData[y * nRowBytes + x * 3 + 0] - (1 - lambuda) * lsImageData[y * nRowBytes + x * 3 + 0]);
		nrgb = (nrgb < 0) ? 0 : ((nrgb>255) ? 255 : nrgb );
		rImageData[y * nRowBytes + x * 3 + 0] = nrgb;
		nrgb = (int)(lambuda * sImageData[y * nRowBytes + x * 3 + 1] - (1 - lambuda) * lsImageData[y * nRowBytes + x * 3 + 1]);
		nrgb = (nrgb < 0) ? 0 : ((nrgb>255) ? 255 : nrgb);
		rImageData[y * nRowBytes + x * 3 + 1] = nrgb;
		nrgb = (int)(lambuda * sImageData[y * nRowBytes + x * 3 + 2] - (1 - lambuda) * lsImageData[y * nRowBytes + x * 3 + 2]);
		nrgb = (nrgb < 0) ? 0 : ((nrgb>255) ? 255 : nrgb);
		rImageData[y * nRowBytes + x * 3 + 2] = nrgb;
	}
	
	lsImage.Destroy();
  
	UpdateAllViews(NULL);
}


void CImageProcessingDoc::OnImageMul()
{
	// TODO: 在此添加命令处理程序代码
	if (m_sImage.IsNull())
	{
		AfxMessageBox(_T("请打开要处理的图像！"));
		return;
	}

	CImage lsImage;
	CString strFilter;
	CSimpleArray<GUID>  aguidFileTypes;
	HRESULT hResult;

	// 获取CImage支持的图像文件的过滤字符串
	hResult = m_sImage.GetExporterFilterString(strFilter, aguidFileTypes, _T("All Image Files"));
	if (FAILED(hResult))
	{
		AfxMessageBox(_T("GetExporterFilter函数失败!"));
		return;
	}

	CFileDialog dlg(TRUE, NULL, NULL, OFN_FILEMUSTEXIST, strFilter);
	if (IDOK != dlg.DoModal())
		return;

	lsImage.Destroy();

	// 将外部图像文件装载到CImage对象中
	hResult = lsImage.Load(dlg.GetPathName());
	if (FAILED(hResult))
	{
		AfxMessageBox(_T("图像文件加载失败！"));
		return;
	}

	if (lsImage.GetBPP() != 24)
	{
		lsImage.Destroy();
		AfxMessageBox(_T("只处理24位色图像！"));
		return;
	}

	if ((lsImage.GetHeight() != m_sImage.GetHeight()) || (lsImage.GetWidth() != m_sImage.GetWidth()))
	{
		lsImage.Destroy();
		AfxMessageBox(_T("本软件只处理相同大小图像的逻辑与代数运算！"));
		return;
	}

	int x;
	int y;
	int nRows = m_sImage.GetHeight();
	int nCols = m_sImage.GetWidth();
	int nBPP = m_sImage.GetBPP();

	m_rImage.Destroy();
	if (!m_rImage.Create(nCols, nRows, nBPP))
	{
		lsImage.Destroy();
		return;
	}

	BYTE *sImageData = (BYTE *)m_sImage.GetBits();
	BYTE *lsImageData = (BYTE *)lsImage.GetBits();
	BYTE *rImageData = (BYTE *)m_rImage.GetBits();
	int nRowBytes = m_sImage.GetPitch();

	int sRowBytes = m_sImage.GetPitch();
	int nrgb;
	for (y = 0; y < nRows; y++)
	for (x = 0; x < nCols; x++)
	{
		nrgb = (int)(sImageData[y * nRowBytes + x * 3 + 0] * lsImageData[y * nRowBytes + x * 3 + 0]);
		nrgb = (nrgb < 0) ? 0 : ((nrgb>255) ? 255 : nrgb);
		rImageData[y * nRowBytes + x * 3 + 0] = nrgb;
		nrgb = (int)(sImageData[y * nRowBytes + x * 3 + 1]  * lsImageData[y * nRowBytes + x * 3 + 1]);
		nrgb = (nrgb < 0) ? 0 : ((nrgb>255) ? 255 : nrgb);
		rImageData[y * nRowBytes + x * 3 + 1] = nrgb;
		nrgb = (int)(sImageData[y * nRowBytes + x * 3 + 2] * lsImageData[y * nRowBytes + x * 3 + 2]);
		nrgb = (nrgb < 0) ? 0 : ((nrgb>255) ? 255 : nrgb);
		rImageData[y * nRowBytes + x * 3 + 2] = nrgb;
	}

	lsImage.Destroy();

	UpdateAllViews(NULL);
}


void CImageProcessingDoc::OnImageDiv()
{
	// TODO: 在此添加命令处理程序代码
	if (m_sImage.IsNull())
	{
		AfxMessageBox(_T("请打开要处理的图像！"));
		return;
	}

	CImage lsImage;
	CString strFilter;
	CSimpleArray<GUID>  aguidFileTypes;
	HRESULT hResult;

	// 获取CImage支持的图像文件的过滤字符串
	hResult = m_sImage.GetExporterFilterString(strFilter, aguidFileTypes, _T("All Image Files"));
	if (FAILED(hResult))
	{
		AfxMessageBox(_T("GetExporterFilter函数失败!"));
		return;
	}

	CFileDialog dlg(TRUE, NULL, NULL, OFN_FILEMUSTEXIST, strFilter);
	if (IDOK != dlg.DoModal())
		return;

	lsImage.Destroy();

	// 将外部图像文件装载到CImage对象中
	hResult = lsImage.Load(dlg.GetPathName());
	if (FAILED(hResult))
	{
		AfxMessageBox(_T("图像文件加载失败！"));
		return;
	}

	if (lsImage.GetBPP() != 24)
	{
		lsImage.Destroy();
		AfxMessageBox(_T("只处理24位色图像！"));
		return;
	}

	if ((lsImage.GetHeight() != m_sImage.GetHeight()) || (lsImage.GetWidth() != m_sImage.GetWidth()))
	{
		lsImage.Destroy();
		AfxMessageBox(_T("本软件只处理相同大小图像的逻辑与代数运算！"));
		return;
	}

	int x;
	int y;
	int nRows = m_sImage.GetHeight();
	int nCols = m_sImage.GetWidth();
	int nBPP = m_sImage.GetBPP();

	m_rImage.Destroy();
	if (!m_rImage.Create(nCols, nRows, nBPP))
	{
		lsImage.Destroy();
		return;
	}

	BYTE *sImageData = (BYTE *)m_sImage.GetBits();
	BYTE *lsImageData = (BYTE *)lsImage.GetBits();
	BYTE *rImageData = (BYTE *)m_rImage.GetBits();
	int nRowBytes = m_sImage.GetPitch();

	double alpha = 0.0001;
	int sRowBytes = m_sImage.GetPitch();
	int nrgb;
	for (y = 0; y < nRows; y++)
		for (x = 0; x < nCols; x++)
		{
			nrgb = (int)(sImageData[y * nRowBytes + x * 3 + 0] / (lsImageData[y * nRowBytes + x * 3 + 0] + alpha));
			nrgb = (nrgb < 0) ? 0 : ((nrgb>255) ? 255 : nrgb);
			rImageData[y * nRowBytes + x * 3 + 0] = nrgb;
			nrgb = (int)(sImageData[y * nRowBytes + x * 3 + 1] / (lsImageData[y * nRowBytes + x * 3 + 1] + alpha));
			nrgb = (nrgb < 0) ? 0 : ((nrgb>255) ? 255 : nrgb);
			rImageData[y * nRowBytes + x * 3 + 1] = nrgb;
			nrgb = (int)(sImageData[y * nRowBytes + x * 3 + 2] / (lsImageData[y * nRowBytes + x * 3 + 2] + alpha));
			nrgb = (nrgb < 0) ? 0 : ((nrgb>255) ? 255 : nrgb);
			rImageData[y * nRowBytes + x * 3 + 2] = nrgb;
		}

	lsImage.Destroy();

	UpdateAllViews(NULL);
}

void CImageProcessingDoc::OnImageAnd()
{
	// TODO: 在此添加命令处理程序代码
	if (m_sImage.IsNull())
	{
		AfxMessageBox(_T("请打开要处理的图像！"));
		return;
	}

	CImage lsImage;
	CString strFilter;
	CSimpleArray<GUID>  aguidFileTypes;
	HRESULT hResult;

	// 获取CImage支持的图像文件的过滤字符串
	hResult = m_sImage.GetExporterFilterString(strFilter, aguidFileTypes, _T("All Image Files"));
	if (FAILED(hResult))
	{
		AfxMessageBox(_T("GetExporterFilter函数失败!"));
		return;
	}

	CFileDialog dlg(TRUE, NULL, NULL, OFN_FILEMUSTEXIST, strFilter);
	if (IDOK != dlg.DoModal())
		return;

	lsImage.Destroy();
	
	// 将外部图像文件装载到CImage对象中
	hResult = lsImage.Load(dlg.GetPathName());
	if (FAILED(hResult))
	{
		AfxMessageBox(_T("图像文件加载失败！"));
		return;
	}

	if (lsImage.GetBPP() != 24)
	{
		lsImage.Destroy();
		AfxMessageBox(_T("只处理24位色图像！"));
		return;
	}

	if( ( lsImage.GetHeight() != m_sImage.GetHeight() ) || ( lsImage.GetWidth() != m_sImage.GetWidth() ) )
	{
		lsImage.Destroy();
		AfxMessageBox(_T("本软件只处理相同大小图像的逻辑与代数运算！"));
		return;
	}


	int x;
	int y;
	int nRows = m_sImage.GetHeight();
	int nCols = m_sImage.GetWidth();
	int nBPP  = m_sImage.GetBPP();

	m_rImage.Destroy();
	if (!m_rImage.Create(nCols, nRows, nBPP))
	{
		lsImage.Destroy();
		return;
	}

	BYTE *sImageData  = (BYTE *)m_sImage.GetBits();
	BYTE *lsImageData = (BYTE *)lsImage.GetBits();
	BYTE *rImageData  = (BYTE *)m_rImage.GetBits();
	int nRowBytes = m_sImage.GetPitch();

	int sRowBytes = m_sImage.GetPitch();

	for (y = 0; y < nRows; y++)
	for (x = 0; x < nCols ; x++)
	{
		rImageData[y * nRowBytes + x * 3 + 0] = sImageData[y * nRowBytes + x * 3 + 0] & lsImageData[y * nRowBytes + x * 3 + 0];
		rImageData[y * nRowBytes + x * 3 + 1] = sImageData[y * nRowBytes + x * 3 + 1] & lsImageData[y * nRowBytes + x * 3 + 1];
		rImageData[y * nRowBytes + x * 3 + 2] = sImageData[y * nRowBytes + x * 3 + 2] & lsImageData[y * nRowBytes + x * 3 + 2];
	}
	
	lsImage.Destroy();
  
	UpdateAllViews(NULL);
}


void CImageProcessingDoc::OnImageOr()
{
	// TODO: 在此添加命令处理程序代码
	if (m_sImage.IsNull())
	{
		AfxMessageBox(_T("请打开要处理的图像！"));
		return;
	}

	CImage lsImage;
	CString strFilter;
	CSimpleArray<GUID>  aguidFileTypes;
	HRESULT hResult;

	// 获取CImage支持的图像文件的过滤字符串
	hResult = m_sImage.GetExporterFilterString(strFilter, aguidFileTypes, _T("All Image Files"));
	if (FAILED(hResult))
	{
		AfxMessageBox(_T("GetExporterFilter函数失败!"));
		return;
	}

	CFileDialog dlg(TRUE, NULL, NULL, OFN_FILEMUSTEXIST, strFilter);
	if (IDOK != dlg.DoModal())
		return;

	lsImage.Destroy();
	
	// 将外部图像文件装载到CImage对象中
	hResult = lsImage.Load(dlg.GetPathName());
	if (FAILED(hResult))
	{
		AfxMessageBox(_T("图像文件加载失败！"));
		return;
	}

	if (lsImage.GetBPP() != 24)
	{
		lsImage.Destroy();
		AfxMessageBox(_T("只处理24位色图像！"));
		return;
	}

	if( ( lsImage.GetHeight() != m_sImage.GetHeight() ) || ( lsImage.GetWidth() != m_sImage.GetWidth() ) )
	{
		lsImage.Destroy();
		AfxMessageBox(_T("本软件只处理相同大小图像的逻辑与代数运算！"));
		return;
	}


	int x;
	int y;
	int nRows = m_sImage.GetHeight();
	int nCols = m_sImage.GetWidth();
	int nBPP  = m_sImage.GetBPP();

	m_rImage.Destroy();
	if (!m_rImage.Create(nCols, nRows, nBPP))
	{
		lsImage.Destroy();
		return;
	}

	BYTE *sImageData  = (BYTE *)m_sImage.GetBits();
	BYTE *lsImageData = (BYTE *)lsImage.GetBits();
	BYTE *rImageData  = (BYTE *)m_rImage.GetBits();
	int nRowBytes = m_sImage.GetPitch();

	int sRowBytes = m_sImage.GetPitch();

	for (y = 0; y < nRows; y++)
	for (x = 0; x < nCols ; x++)
	{
		rImageData[y * nRowBytes + x * 3 + 0] = sImageData[y * nRowBytes + x * 3 + 0] | lsImageData[y * nRowBytes + x * 3 + 0];
		rImageData[y * nRowBytes + x * 3 + 1] = sImageData[y * nRowBytes + x * 3 + 1] | lsImageData[y * nRowBytes + x * 3 + 1];
		rImageData[y * nRowBytes + x * 3 + 2] = sImageData[y * nRowBytes + x * 3 + 2] | lsImageData[y * nRowBytes + x * 3 + 2];
	}
	
	lsImage.Destroy();
  
	UpdateAllViews(NULL);
}

void CImageProcessingDoc::OnImageRotation()
{
	// TODO: 在此添加命令处理程序代码

	if (m_sImage.IsNull())
	{
		AfxMessageBox(_T("请打开要处理的图像！"));
		return;
	}

	int x;
	int y;
	int x0;
	int y0;
	int nRows = m_sImage.GetHeight();
	int nCols = m_sImage.GetWidth();
	int nBPP =  m_sImage.GetBPP();

	CDialogImageRotation mdlg;
	mdlg.r_x = nRows  / 2;
	mdlg.r_y = nCols / 2;
	mdlg.r_thita = 45.0f;
	if (mdlg.DoModal() != IDOK)
	{
		return;
	}

	double alpha = mdlg.r_thita;
	double fsina = sin(alpha*PI / 180.0);
	double fcosa = cos(alpha*PI / 180.0);

	double x1 = -nCols * 0.5;
	double y1 =  nRows * 0.5;
	double x2 =  nCols * 0.5;
	double y2 =  nRows * 0.5;
	double x3 =  nCols * 0.5;
	double y3 = -nRows * 0.5;
	double x4 = -nCols * 0.5;
	double y4 = -nRows * 0.5;



	double X1 =  x1 * fcosa + y1 * fsina;
	double Y1 = -x1 * fsina + y1 * fcosa;

	double X2 =  x2 * fcosa + y2 * fsina;
	double Y2 = -x2 * fsina + y2 * fcosa;

	double X3 =  x3 * fcosa + y3 * fsina;
	double Y3 = -x3 * fsina + y3 * fcosa;

	double X4 =  x4 * fcosa + y4 * fsina;
	double Y4 = -x4 * fsina + y4 * fcosa;


	double m_max, m_min;
	m_max = m_min = X1;
	if (X2 > m_max) m_max = X2;
	if (X2 < m_min) m_min = X2;
	if (X3 > m_max) m_max = X3;
	if (X3 < m_min) m_min = X3;
	if (X4 > m_max) m_max = X4;
	if (X4 < m_min) m_min = X4;
	int rWidth = (int)(m_max - m_min + 0.5);

	m_max = m_min = Y1;
	if (Y2 > m_max) m_max = Y2;
	if (Y2 < m_min) m_min = Y2;
	if (Y3 > m_max) m_max = Y3;
	if (Y3 < m_min) m_min = Y3;
	if (Y4 > m_max) m_max = Y4;
	if (Y4 < m_min) m_min = Y4;
	int rHeight = (int)(m_max - m_min + 0.5);
	
	double a = nCols * 0.5;
	double b = nRows * 0.5;
	double c = rWidth * 0.5;
	double d = rHeight * 0.5;

	double f1 = a - c * fcosa + d * fsina;
	double f2 = b - c * fsina - d * fcosa;


	m_rImage.Destroy();
	if (!m_rImage.Create(rWidth, rHeight, nBPP))
		return;
	BYTE *sImageData = (BYTE *)m_sImage.GetBits();
	BYTE *rImageData = (BYTE *)m_rImage.GetBits();
	int nRowBytes    = m_sImage.GetPitch();
	int nLineBytes   = m_rImage.GetPitch();

	for (y = 0; y < rHeight; y++)
	for (x = 0; x < rWidth; x++)
	{
		x0 = (int) (  x*fcosa - y*fsina + f1 + 0.5);
		y0 = (int) (  x*fsina + y*fcosa + f2 + 0.5);
		if ((x0 >= 0) && (x0 < nCols) && (y0 >= 0) && (y0 < nRows))
		{
			rImageData[y * nLineBytes + x * 3 + 0] = sImageData[y0 * nRowBytes + x0 * 3 + 0];
			rImageData[y * nLineBytes + x * 3 + 1] = sImageData[y0 * nRowBytes + x0 * 3 + 1];
			rImageData[y * nLineBytes + x * 3 + 2] = sImageData[y0 * nRowBytes + x0 * 3 + 2];
		}
		else
		{
			rImageData[y * nLineBytes + x * 3 + 0] = 255;
			rImageData[y * nLineBytes + x * 3 + 1] = 255;
			rImageData[y * nLineBytes + x * 3 + 2] = 255;
		}
	 }

	UpdateAllViews(NULL); 
}

void CImageProcessingDoc::OnGeneralAffineTransform()
{
	// TODO: 在此添加命令处理程序代码
	if (m_sImage.IsNull())
	{
		AfxMessageBox(_T("请打开要处理的图像！"));
		return;
	}

	CGenicAffineTranform	 mdlg;
	if (mdlg.DoModal() == IDCANCEL)
		return;
	
	int nRows = m_sImage.GetHeight();
	int nCols = m_sImage.GetWidth();
	int nBPP =  m_sImage.GetBPP();

	m_rImage.Destroy();
	if (!m_rImage.Create(nCols, nRows, nBPP))
		return;
	BYTE *sImageData = (BYTE *)m_sImage.GetBits();
	BYTE *rImageData = (BYTE *)m_rImage.GetBits();
	int nRowBytes    = m_sImage.GetPitch();

   int x;
   int y;
   int x1;
   int y1;
   int x0 = nCols/2;
   int y0 = nRows/2;
   double a = mdlg.m_a;
   double b = mdlg.m_b;
   double c = mdlg.m_c;
   double d = mdlg.m_d;
   double e = mdlg.m_e;
   double f = mdlg.m_f;


   for (y1=0; y1<nRows; y1++)
   for (x1=0; x1<nCols; x1++)
   {
	   x = (int)((x0+d*(x1-x0-e)-b*(y1-y0-f))/(a*d-b*c));
	   y=  (int)((y0+a*(y1-y0-e)-c*(x1-x0-e))/(a*d-b*c));
	   if ((x>=0)&&(x<nCols)&&(y>=0)&&(y<nRows))
	   {
		   rImageData[y1*nRowBytes + 3 * x1 + 0] = sImageData[y*nRowBytes + 3 * x + 0];
		   rImageData[y1*nRowBytes + 3 * x1 + 1] = sImageData[y*nRowBytes + 3 * x + 1];
		   rImageData[y1*nRowBytes + 3 * x1 + 2] = sImageData[y*nRowBytes + 3 * x + 2];
	   }
	   else
	   {
		   rImageData[y1*nRowBytes + 3 * x1 + 0] = 255;
		   rImageData[y1*nRowBytes + 3 * x1 + 1] = 255;
		   rImageData[y1*nRowBytes + 3 * x1 + 2] = 255;
	   }
   }

	UpdateAllViews(NULL);
}



void CImageProcessingDoc::OnHoriConcave()
{
	// TODO: 在此添加命令处理程序代码
	if (m_sImage.IsNull())
	{
		AfxMessageBox(_T("请打开要处理的图像！"));
		return;
	}

	int x;
	int y;

	int nRows = m_sImage.GetHeight();
	int nCols = m_sImage.GetWidth();
	int nBPP =  m_sImage.GetBPP();

	m_rImage.Destroy();
	if (!m_rImage.Create(nCols, nRows, nBPP))
		return;
	BYTE *sImageData = (BYTE *)m_sImage.GetBits();
	BYTE *rImageData = (BYTE *)m_rImage.GetBits();
	int nRowBytes    = m_sImage.GetPitch();

    double tmp;
	for(y=0;y<nRows;y++)    
	{     
		tmp = RANGE*sin(y*PI/nRows);     
		for(x=(int)tmp;x<nCols-(int)tmp;x++)     
		{      
			int s=(int)((x-(int)tmp)*(nCols)/(nCols-2*(int)tmp));      
  			rImageData[y*nRowBytes + 3*x + 0]=sImageData[y*nRowBytes + 3*s + 0];
			rImageData[y*nRowBytes + 3 * x + 1] = sImageData[y*nRowBytes + 3 * s + 1];
			rImageData[y*nRowBytes + 3 * x + 2] = sImageData[y*nRowBytes + 3 * s + 2];
		} 
	}
	UpdateAllViews(NULL);
}


void CImageProcessingDoc::OnHoriConvex()
{
	// TODO: 在此添加命令处理程序代码
	if (m_sImage.IsNull())
	{
		AfxMessageBox(_T("请打开要处理的图像！"));
		return;
	}

	int x;
	int y;

	int nRows = m_sImage.GetHeight();
	int nCols = m_sImage.GetWidth();
	int nBPP =  m_sImage.GetBPP();

	m_rImage.Destroy();
	if (!m_rImage.Create(nCols, nRows, nBPP))
		return;
	BYTE *sImageData = (BYTE *)m_sImage.GetBits();
	BYTE *rImageData = (BYTE *)m_rImage.GetBits();
	int nRowBytes    = m_sImage.GetPitch();

    double tmp;
	for(y=0;y<nRows;y++)    
	{     
		tmp = RANGE*sin(y*PI / nRows + PI) + RANGE;
		for(x=(int)tmp;x<nCols-(int)tmp;x++)     
		{      
			int s=(int)((x-(int)tmp)*(nCols)/(nCols-2*(int)tmp));      
  			rImageData[y*nRowBytes + 3*x + 0]=sImageData[y*nRowBytes + 3*s + 0];
			rImageData[y*nRowBytes + 3 * x + 1] = sImageData[y*nRowBytes + 3 * s + 1];
			rImageData[y*nRowBytes + 3 * x + 2] = sImageData[y*nRowBytes + 3 * s + 2];
		} 
	}
	UpdateAllViews(NULL);
}


void CImageProcessingDoc::OnLaddertypeDeformation()
{
	// TODO: 在此添加命令处理程序代码
	if (m_sImage.IsNull())
	{
		AfxMessageBox(_T("请打开要处理的图像！"));
		return;
	}

	int x;
	int y;

	int nRows = m_sImage.GetHeight();
	int nCols = m_sImage.GetWidth();
	int nBPP =  m_sImage.GetBPP();

	m_rImage.Destroy();
	if (!m_rImage.Create(nCols, nRows, nBPP))
		return;
	BYTE *sImageData = (BYTE *)m_sImage.GetBits();
	BYTE *rImageData = (BYTE *)m_rImage.GetBits();
	int nRowBytes    = m_sImage.GetPitch();

    double tmp;
	for(y=0;y<nRows;y++)    
	{     
		tmp = (nCols - RANGE) / 2 - y*(nCols - RANGE) / (2 * nRows);
		for(x=(int)tmp;x<nCols-(int)tmp;x++)     
		{      
			int s=(int)((x-(int)tmp)*(nCols)/(nCols-2*(int)tmp));      
  			rImageData[y*nRowBytes + 3*x + 0]=sImageData[y*nRowBytes + 3*s + 0];
			rImageData[y*nRowBytes + 3 * x + 1] = sImageData[y*nRowBytes + 3 * s + 1];
			rImageData[y*nRowBytes + 3 * x + 2] = sImageData[y*nRowBytes + 3 * s + 2];
		} 
	}
	UpdateAllViews(NULL);
}


void CImageProcessingDoc::OnTriangleDeformation()
{
	// TODO: 在此添加命令处理程序代码
	if (m_sImage.IsNull())
	{
		AfxMessageBox(_T("请打开要处理的图像！"));
		return;
	}

	int x;
	int y;

	int nRows = m_sImage.GetHeight();
	int nCols = m_sImage.GetWidth();
	int nBPP = m_sImage.GetBPP();

	m_rImage.Destroy();
	if (!m_rImage.Create(nCols, nRows, nBPP))
		return;
	BYTE *sImageData = (BYTE *)m_sImage.GetBits();
	BYTE *rImageData = (BYTE *)m_rImage.GetBits();
	int nRowBytes = m_sImage.GetPitch();

	for (y = 1; y<nRows; y++)
	{
		for (x = 1; x<y*nCols/nRows; x++)
		{
			int s = (int)(nRows * x / y);
			rImageData[y*nRowBytes + 3 * x + 0] = sImageData[y*nRowBytes + 3 * s + 0];
			rImageData[y*nRowBytes + 3 * x + 1] = sImageData[y*nRowBytes + 3 * s + 1];
			rImageData[y*nRowBytes + 3 * x + 2] = sImageData[y*nRowBytes + 3 * s + 2];
		}
	}
	UpdateAllViews(NULL);
}


void CImageProcessingDoc::OnStypeDeformation()
{
	// TODO: 在此添加命令处理程序代码
	if (m_sImage.IsNull())
	{
		AfxMessageBox(_T("请打开要处理的图像！"));
		return;
	}

	int x;
	int y;

	int nRows = m_sImage.GetHeight();
	int nCols = m_sImage.GetWidth();
	int nBPP =  m_sImage.GetBPP();

	m_rImage.Destroy();
	if (!m_rImage.Create(nCols, nRows, nBPP))
		return;
	BYTE *sImageData = (BYTE *)m_sImage.GetBits();
	BYTE *rImageData = (BYTE *)m_rImage.GetBits();
	int nRowBytes    = m_sImage.GetPitch();

    double tmp;
	for(y=0;y<nRows;y++)    
	{     
		tmp = RANGE*sin(2 * y*PI / nRows + PI) + RANGE;
		for(x=(int)tmp; x<nCols - (2 * RANGE - (int)tmp);x++)
		{      
			int s = (int)((x - (int)tmp)*(nCols) / (nCols - RANGE * 2));
  			rImageData[y*nRowBytes + 3*x + 0]=sImageData[y*nRowBytes + 3*s + 0];
			rImageData[y*nRowBytes + 3 * x + 1] = sImageData[y*nRowBytes + 3 * s + 1];
			rImageData[y*nRowBytes + 3 * x + 2] = sImageData[y*nRowBytes + 3 * s + 2];
		} 
	}
	UpdateAllViews(NULL);
}


void CImageProcessingDoc::OnCorrugationDeformation()
{
	// TODO: 在此添加命令处理程序代码
	if (m_sImage.IsNull())
	{
		AfxMessageBox(_T("请打开要处理的图像！"));
		return;
	}

	int x;
	int y;

	int nRows = m_sImage.GetHeight();
	int nCols = m_sImage.GetWidth();
	int nBPP = m_sImage.GetBPP();

	m_rImage.Destroy();
	if (!m_rImage.Create(nCols, nRows, nBPP))
		return;
	BYTE *sImageData = (BYTE *)m_sImage.GetBits();
	BYTE *rImageData = (BYTE *)m_rImage.GetBits();
	int nRowBytes = m_sImage.GetPitch();

	for (y = 0; y<nRows; y++)
	{
		for (x = 1; x<nCols; x++)
		{
			int s = (int)((4 * y + nRows + nRows*sin(x * 2 * PI/nCols)) / 6);
			rImageData[s*nRowBytes + 3 * x + 0] = sImageData[y*nRowBytes + 3 * x + 0];
			rImageData[s*nRowBytes + 3 * x + 1] = sImageData[y*nRowBytes + 3 * x + 1];
			rImageData[s*nRowBytes + 3 * x + 2] = sImageData[y*nRowBytes + 3 * x + 2];
		}
	}
	UpdateAllViews(NULL);
}


void CImageProcessingDoc::OnMagicMirrorTransform()
{
	// TODO: 在此添加命令处理程序代码

	int nRows = m_sImage.GetWidth();
	int nCols = m_sImage.GetHeight();
	int nLineBytes = m_sImage.GetPitch();
	int nBPP = m_sImage.GetBPP();
	m_rImage.Destroy();
	if (!m_rImage.Create(nCols, nRows, nBPP))
		return;
	unsigned char *psBits = (unsigned char *)m_sImage.GetBits();
	unsigned char *prBits = (unsigned char *)m_rImage.GetBits();
	int centerX = nCols / 2;
	int centerY = nRows / 2;
	int radius = 200;

	float xishu = 2;

	int src_x;
	int src_y;
	int real_radius = (int)(radius / xishu);

	for (int y = 0; y < nRows; y++)
	{
		for (int x = 0; x < nCols; x++)
		{
			prBits[y*nLineBytes + 3 * x + 0] = psBits[y*nLineBytes + 3 * x + 0];
			prBits[y*nLineBytes + 3 * x + 1] = psBits[y*nLineBytes + 3 * x + 1];
			prBits[y*nLineBytes + 3 * x + 2] = psBits[y*nLineBytes + 3 * x + 2];



			int distance = (int)((centerX - x) * (centerX - x) + (centerY - y) * (centerY - y));
			//对半径范围内的图像进行处理，其余部分的图像不做处理  
			if (distance < radius * radius)
			{
				// 放大镜的凹凸效果  
				src_x = (int)((float)(x - centerX) / xishu);
				src_y = (int)((float)(y - centerY) / xishu);
				src_x = (int)(src_x * (sqrt(distance) / real_radius));
				src_y = (int)(src_y * (sqrt(distance) / real_radius));
				src_x = src_x + centerX;
				src_y = src_y + centerY;
				if (src_x >= 0 && src_x < nCols && src_y >= 0 && src_y < nRows)
				{
					prBits[y*nLineBytes + 3 * x + 0] = psBits[src_y * nLineBytes + 3 * src_x];
					prBits[y*nLineBytes + 3 * x + 1] = psBits[src_y * nLineBytes + 3 * src_x + 1];
					prBits[y*nLineBytes + 3 * x + 2] = psBits[src_y * nLineBytes + 3 * src_x + 2];
				}

			}
		}
	}
	UpdateAllViews(NULL); // 强制调用OnDraw
	return;
}


void CImageProcessingDoc::OnNearestInterpolationScaling()
{
	// TODO: 在此添加命令处理程序代码
	if (m_sImage.IsNull())
	{
		AfxMessageBox(_T("请打开要处理的图像！"));
		return;
	}

	int x;
	int y;

	CDialogScalingFactor mdlg;
	if (mdlg.DoModal() != IDOK)   //输入水平和垂直方向放大系数
	{
		return;
	}
	if (mdlg.mHoriScalingFactor < 0 || mdlg.mVeriScalingFactor < 0)
	{
		AfxMessageBox(_T("缩放参数错误！"));
		return;
	}

	int sWidth  = m_sImage.GetWidth();  //原始图像宽度
	int sHeight = m_sImage.GetHeight(); //原始图像高度

	int rWidth = (int)(sWidth * mdlg.mHoriScalingFactor + 0.5);  //目标图像宽度
	int rHeight = (int)(sHeight * mdlg.mVeriScalingFactor + 0.5);//目标图像高度
	m_rImage.Destroy();
	if (!m_rImage.Create(rWidth, rHeight, m_sImage.GetBPP(), 0))
		return;

	int sRowBytes = m_sImage.GetPitch();
	int rRowBytes = m_rImage.GetPitch();

	BYTE *sImageData = (BYTE *)m_sImage.GetBits();
	BYTE *rImageData = (BYTE *)m_rImage.GetBits();


	for (y = 1; y < rHeight - 1; y++)
	for (x = 1; x < rWidth - 1; x++)
	{
		int i = (int)(x / mdlg.mHoriScalingFactor);
		int j = (int)(y / mdlg.mVeriScalingFactor);
		rImageData[y*rRowBytes + x * 3]     = sImageData[j * sRowBytes + i * 3];
		rImageData[y*rRowBytes + x * 3 + 1] = sImageData[j * sRowBytes + i * 3 + 1];
		rImageData[y*rRowBytes + x * 3 + 2] = sImageData[j * sRowBytes + i * 3 + 2];
	}

	UpdateAllViews(NULL); // 强制调用OnDraw
	return;
}


void CImageProcessingDoc::OnBilinearInterpolationScaling()
{
	// TODO: 在此添加命令处理程序代码

	if (m_sImage.IsNull())
	{
		AfxMessageBox(_T("请打开要处理的图像！"));
		return;
	}

	int x;
	int y;

	CDialogScalingFactor mdlg;
	if (mdlg.DoModal() != IDOK)
	{
		return;
	}
	if (mdlg.mHoriScalingFactor < 0 || mdlg.mVeriScalingFactor < 0)
	{
		AfxMessageBox(_T("缩放参数错误！"));
		return;
	}

	int sWidth  = m_sImage.GetWidth();
	int sHeight = m_sImage.GetHeight();

	int rWidth = (int)(sWidth * mdlg.mHoriScalingFactor + 0.5);
	int rHeight = (int)(sHeight * mdlg.mVeriScalingFactor + 0.5);

	m_rImage.Destroy();

	if (!m_rImage.Create(rWidth, rHeight, m_sImage.GetBPP(), 0))
		return;

	int sRowBytes = m_sImage.GetPitch();
	int rRowBytes = m_rImage.GetPitch();

	BYTE *sImageData = (BYTE *)m_sImage.GetBits();
	BYTE *rImageData = (BYTE *)m_rImage.GetBits();

	for (y = 1; y < rHeight - 1; y++)
	for (x = 1; x < rWidth - 1; x++)
	{
		double u = x / mdlg.mHoriScalingFactor;
		double v = y / mdlg.mVeriScalingFactor;
		int i = (int)u;
		int j = (int)v;
		u = u - i;
		v = v - j;

		if ((i >= sWidth - 1) && (j >= sHeight - 1))
		{
			rImageData[y*rRowBytes + x * 3] = sImageData[(sHeight - 1) * sRowBytes + (sWidth - 1) * 3];
			rImageData[y*rRowBytes + x * 3 + 1] = sImageData[(sHeight - 1) * sRowBytes + (sWidth - 1) * 3 + 1];
			rImageData[y*rRowBytes + x * 3 + 2] = sImageData[(sHeight - 1) * sRowBytes + (sWidth - 1) * 3 + 2];
		}
		else if (j >= sHeight - 1)
		{
			*(rImageData + y*rRowBytes + x * 3) = sImageData[(sHeight - 1) * sRowBytes + i * 3];
			*(rImageData + y*rRowBytes + x * 3 + 1) = sImageData[(sHeight - 1) * sRowBytes + i * 3 + 1];
			*(rImageData + y*rRowBytes + x * 3 + 2) = sImageData[(sHeight - 1) * sRowBytes + i * 3 + 2];
		}
		else if (i >= sWidth - 1)
		{
			rImageData[y*rRowBytes + x * 3] = sImageData[j * sRowBytes + (sWidth - 1) * 3];
			rImageData[y*rRowBytes + x * 3 + 1] = sImageData[j * sRowBytes + (sWidth - 1) * 3 + 1];
			rImageData[y*rRowBytes + x * 3 + 2] = sImageData[j * sRowBytes + (sWidth - 1) * 3 + 2];
		}
		else
		{
			rImageData[y*rRowBytes + x * 3] = (BYTE)((1 - u)*(1 - v)*(sImageData[j * sRowBytes + i * 3])
				+ (1 - u)*v*(sImageData[(j + 1)*sRowBytes + i * 3])
				+ u*(1 - v)*(sImageData[j*sRowBytes + (i + 1) * 3])
				+ u*v*(sImageData[(j + 1)*sRowBytes + (i + 1) * 3]));
			rImageData[y*rRowBytes + x * 3 + 1] = (BYTE)((1 - u)*(1 - v)*(sImageData[j * sRowBytes + i * 3 + 1])
				+ (1 - u)*v*(sImageData[(j + 1)*sRowBytes + i * 3 + 1])
				+ u*(1 - v)*(sImageData[j*sRowBytes + (i + 1) * 3 + 1])
				+ u*v*(sImageData[(j + 1)*sRowBytes + (i + 1) * 3 + 1]));
			rImageData[y*rRowBytes + x * 3 + 2] = (BYTE)((1 - u)*(1 - v)*(sImageData[j * sRowBytes + i * 3 + 2])
				+ (1 - u)*v*(sImageData[(j + 1)*sRowBytes + i * 3 + 2])
				+ u*(1 - v)*(sImageData[j*sRowBytes + (i + 1) * 3 + 2])
				+ u*v*(sImageData[(j + 1)*sRowBytes + (i + 1) * 3 + 2]));
		}
	}
	
	UpdateAllViews(NULL); // 强制调用OnDraw
	return;
}




void CImageProcessingDoc::OnImageMagnifier()
{
	// TODO: 在此添加命令处理程序代码

	if (m_sImage.IsNull())
	{
		AfxMessageBox(_T("请打开要处理的图像！"));
		return;
	}

	int sWidth = m_sImage.GetWidth();
	int sHeight = m_sImage.GetHeight();
	int nBPP = m_sImage.GetBPP();
	int sRowBytes = m_sImage.GetPitch();

	CDialogImageMagnifier  mdlg;

	mdlg.m_Image.Destroy();
	if (!mdlg.m_Image.Create(sWidth, sHeight, nBPP, 0))
		return;

	BYTE *sImageData = (BYTE *)m_sImage.GetBits();
	BYTE *rImageData = (BYTE *)mdlg.m_Image.GetBits();

	int x;
	int y;
	for (y = 1; y < sHeight - 1; y++)
	for (x = 1; x < sWidth - 1; x++)
	{
		rImageData[y*sRowBytes + x * 3]     = sImageData[y*sRowBytes + x * 3];
		rImageData[y*sRowBytes + x * 3 + 1] = sImageData[y*sRowBytes + x * 3 + 1];
		rImageData[y*sRowBytes + x * 3 + 2] = sImageData[y*sRowBytes + x * 3 + 2];
	}

	mdlg.DoModal();
}


//图像噪声污染
void CImageProcessingDoc::OnImageNoisePollution()
{
	// TODO: 在此添加命令处理程序代码
	if (m_sImage.IsNull())
	{
		AfxMessageBox(_T("请打开要处理的图像！"));
		return;
	}

	CDialogNoiseParameters mdlg;
	if (mdlg.DoModal() != IDOK)
		return;

	CImage *pImg;

	if (mdlg.m_check1)
	{
		pImg = &m_sImage;
	}
	else
	{
		int x;
		int y;
		int nRows = m_sImage.GetHeight();
		int nCols = m_sImage.GetWidth();
		int nBPP = m_sImage.GetBPP();
		m_rImage.Destroy();
		if (!m_rImage.Create(nCols, nRows, nBPP))
			return;
		BYTE *sImageData = (BYTE *)m_sImage.GetBits();
		BYTE *rImageData = (BYTE *)m_rImage.GetBits();
		int nRowBytes = m_sImage.GetPitch();
		for (y = 0; y < nRows; y++)
		for (x = 0; x < nCols; x++)
		{
			rImageData[y * nRowBytes + x * 3]     = sImageData[y * nRowBytes + x * 3 + 0];
			rImageData[y * nRowBytes + x * 3 + 1] = sImageData[y * nRowBytes + x * 3 + 1];
			rImageData[y * nRowBytes + x * 3 + 2] = sImageData[y * nRowBytes + x * 3 + 2];
		}
		pImg = &m_rImage;
	}

	switch (mdlg.m_radio1)
	{
	case 0: //脉冲噪声（椒盐噪声）
		   ImagePeppperNoisePollution(pImg, mdlg.m_pa, mdlg.m_pb);
		   break;
	case 1: //均匀分布噪声
		   ImageUniformNoisePollution(pImg, mdlg.m_ua, mdlg.m_ub);
		   break;
	case 2:     //高斯噪声
		ImageGauessNoisePollution(pImg, mdlg.m_gauess_mu, mdlg.m_gauess_sigma, mdlg.m_gauess_k);
		break;
	case 3:     //泊松噪声
		break;
	case 4:     //伽马（爱尔兰）噪声
		break;
	case 5:     //指数噪声
		break;
	case 6:     //
		break;
	default: break;
	}
	UpdateAllViews(NULL);
}



void CImageProcessingDoc::OnColorInversion()
{
	// TODO: 在此添加命令处理程序代码
	if (m_sImage.IsNull())
	{
		AfxMessageBox(_T("请打开要处理的图像！"));
		return;
	}

	int x;
	int y;
	int nRows = m_sImage.GetHeight();
	int nCols = m_sImage.GetWidth();
	int nBPP = m_sImage.GetBPP();

	BYTE nRed, nGreen, nBlue;
	m_rImage.Destroy();

	if (!m_rImage.Create(nCols, nRows, nBPP))
		return;
	BYTE *sImageData = (BYTE *)m_sImage.GetBits();
	BYTE *rImageData = (BYTE *)m_rImage.GetBits();
	int nRowBytes = m_sImage.GetPitch();

	for (y = 0; y < nRows; y++)
	for (x = 0; x < nCols; x++)
	{
		nBlue = sImageData[y * nRowBytes + x * 3 + 0];
		nGreen = sImageData[y * nRowBytes + x * 3 + 1];
		nRed = sImageData[y * nRowBytes + x * 3 + 2];

		rImageData[y * nRowBytes + x * 3] = 255 - nBlue;
		rImageData[y * nRowBytes + x * 3 + 1] = 255 - nGreen;
		rImageData[y * nRowBytes + x * 3 + 2] = 255 - nRed;
	}

}


void CImageProcessingDoc::OnLogTransform()
{
	// TODO: 在此添加命令处理程序代码
	if (m_sImage.IsNull())
	{
		AfxMessageBox(_T("请打开要处理的图像！"));
		return;
	}
	CDialogLogParameters mdlg;
	if (mdlg.DoModal() == IDCANCEL)
		return;
	int x;
	int y;
	int nRows = m_sImage.GetHeight();
	int nCols = m_sImage.GetWidth();
	int nBPP =  m_sImage.GetBPP();

	BYTE nRed, nGreen, nBlue;
	double dGrey;
	m_rImage.Destroy();

	if (!m_rImage.Create(nCols, nRows, nBPP))
		return;
	BYTE *sImageData = (BYTE *)m_sImage.GetBits();
	BYTE *rImageData = (BYTE *)m_rImage.GetBits();
	int nRowBytes    = m_sImage.GetPitch();

	for (y = 0; y < nRows; y++)
	for (x = 0; x < nCols; x++)
	{
		nBlue  = sImageData[y * nRowBytes + x * 3 + 0];
		nGreen = sImageData[y * nRowBytes + x * 3 + 1];
		nRed   = sImageData[y * nRowBytes + x * 3 + 2];
		dGrey  =  0.299*nRed + 0.587*nGreen + 0.114*nBlue; 
		dGrey = mdlg.m_log_c * log(1+dGrey);
		
		rImageData[y * nRowBytes + x * 3]     = (BYTE) dGrey;
		rImageData[y * nRowBytes + x * 3 + 1] = (BYTE) dGrey;
		rImageData[y * nRowBytes + x * 3 + 2] = (BYTE) dGrey;
	 }

	 UpdateAllViews(NULL);
}

void CImageProcessingDoc::OnPowerTransform()
{
	// TODO: 在此添加命令处理程序代码
	if (m_sImage.IsNull())
	{
		AfxMessageBox(_T("请打开要处理的图像！"));
		return;
	}
	CDialogPowerParameters mdlg;
	if (mdlg.DoModal() == IDCANCEL)
		return;
	int x;
	int y;
	int nRows = m_sImage.GetHeight();
	int nCols = m_sImage.GetWidth();
	int nBPP = m_sImage.GetBPP();

	BYTE nRed, nGreen, nBlue;
	double dGrey;
	m_rImage.Destroy();

	if (!m_rImage.Create(nCols, nRows, nBPP))
		return;
	BYTE *sImageData = (BYTE *)m_sImage.GetBits();
	BYTE *rImageData = (BYTE *)m_rImage.GetBits();
	int nRowBytes = m_sImage.GetPitch();

	for (y = 0; y < nRows; y++)
	for (x = 0; x < nCols; x++)
	{
		nBlue  = sImageData[y * nRowBytes + x * 3 + 0];
		nGreen = sImageData[y * nRowBytes + x * 3 + 1];
		nRed   = sImageData[y * nRowBytes + x * 3 + 2];
		dGrey = 0.299*nRed + 0.587*nGreen + 0.114*nBlue;

		dGrey = 255 * mdlg.m_power_c * exp(mdlg.m_power_gama * log(dGrey / 255 + 0.00001));

		rImageData[y * nRowBytes + x * 3] = (BYTE)dGrey;
		rImageData[y * nRowBytes + x * 3 + 1] = (BYTE)dGrey;
		rImageData[y * nRowBytes + x * 3 + 2] = (BYTE)dGrey;
	}

	UpdateAllViews(NULL);
}


void CImageProcessingDoc::OnLinearform()
{
	// TODO: 在此添加命令处理程序代码
	if (m_sImage.IsNull())
	{
		AfxMessageBox(_T("请打开要处理的图像！"));
		return;
	}
	
	int x;
	int y;
	int nRows = m_sImage.GetHeight();
	int nCols = m_sImage.GetWidth();
	int nBPP = m_sImage.GetBPP();


	BYTE nRed, nGreen, nBlue;	
	BYTE nGrey;
	double hist[256];
	double avegrey;
	double mmax, mmin;
	m_rImage.Destroy();
	if (!m_rImage.Create(nCols, nRows, nBPP))
		return;
	BYTE *sImageData = (BYTE *)m_sImage.GetBits();
	BYTE *rImageData = (BYTE *)m_rImage.GetBits();
	int nRowBytes = m_sImage.GetPitch();

	bool  bColorPorcessing;
	if (AfxMessageBox(L"处理彩色图像？", MB_YESNO) == IDYES)
		bColorPorcessing = true;
	else
		bColorPorcessing = false;

	CDialogLinearTransform mdlg;
	int *pY = new int[nRows*nCols];

	if (bColorPorcessing)
	{
		int mY, mCb, mCr;
		for (x = 0; x < 256; x++)
			hist[x] = 0.0f;
		avegrey = 0;
		int *pCb = new int[nRows*nCols];
		int *pCr = new int[nRows*nCols];
		for (y = 0; y < nRows; y++)
		for (x = 0; x < nCols; x++)
		{
			nBlue = sImageData[y * nRowBytes + x * 3 + 0];
			nGreen = sImageData[y * nRowBytes + x * 3 + 1];
			nRed = sImageData[y * nRowBytes + x * 3 + 2];
			mY = (int)(0.257*nRed + 0.564*nGreen + 0.098*nBlue) + 16;
			mCb = 128 + (int)(-0.148*nRed - 0.291*nGreen + 0.439*nBlue);
			mCr = 128 + (int)(0.439*nRed - 0.368*nGreen - 0.071*nBlue);
			if (mY < 0)  mY = 0;
			else if (mY > 255)	mY = 255;
			if (mCb < 0)  mCb = 0;
			else if (mCb > 255)  mCb = 255;
			if (mCr < 0)   mCr = 0;
			else if (mCr > 255) 	mCr = 255;
			pY[y*nCols + x] = (BYTE)mY;
			pCb[y*nCols + x] = (BYTE)mCb;
			pCr[y*nCols + x] = (BYTE)mCr;
			hist[pY[y*nCols + x]] = hist[pY[y*nCols + x]] + 1;
			avegrey += pY[y*nCols + x];
		}
		avegrey = avegrey / (nRows*nCols);
		mmax = mmin = hist[0];
		for (x = 0; x < 256; x++)
		{
			if (mmax < hist[x]) mmax = hist[x];
			else if (mmin > hist[x]) mmin = hist[x];
		}

		mdlg.averagegrey = (int)avegrey;
		for (x = 0; x < 256; x++)
		{
			hist[x] = 255.0 * (hist[x] - mmin) / (mmax - mmin);
			mdlg.histogram[x] = (int)hist[x];
		}

		if (mdlg.DoModal() == IDCANCEL)
		{
			delete  pY;
			delete  pCb;
			delete  pCr;
			return;
		}

		for (y = 0; y < nRows; y++)
		for (x = 0; x < nCols; x++)
		{
			nGrey = pY[y*nCols + x];
			mdlg.plink = mdlg.pBreakPoints;
			while (mdlg.plink)
			{
				if (mdlg.plink->pNext)
				{
					if (nGrey >= mdlg.plink->m_pt.x  &&  nGrey < mdlg.plink->pNext->m_pt.x)
					{
						pY[y*nCols + x] = (int)(mdlg.plink->m_pt.y + mdlg.plink->m_k  * (nGrey - mdlg.plink->m_pt.x));
						break;
					}
					else if (nGrey == mdlg.plink->m_pt.x  &&  nGrey == mdlg.plink->pNext->m_pt.x)
					{
						pY[y*nCols + x] = (int)mdlg.plink->m_k;
						break;
					}
				}
				else
					pY[y*nCols + x] = (int)mdlg.plink->m_k;

				mdlg.plink = mdlg.plink->pNext;
			}

			nRed = (int)(1.164*pY[y*nCols + x] + 1.596 * pCr[y*nCols + x] - 222.912);
			nGreen = (int)(1.164*pY[y*nCols + x] - 0.391 * pCb[y*nCols + x] - 0.813 * pCr[y*nCols + x] + 135.488);
			nBlue = (int)(1.164*pY[y*nCols + x] + 2.018 * pCb[y*nCols + x] - 276.928);

			if (nRed < 0) nRed = 0;
			else if (nRed>255) nRed = 255;
			if (nGreen < 0) nGreen = 0;
			else if (nGreen>255) nGreen = 255;
			if (nBlue < 0) nBlue = 0;
			else if (nBlue>255) nBlue = 255;
			rImageData[y * nRowBytes + x * 3 + 2] = (BYTE)(nRed);
			rImageData[y * nRowBytes + x * 3 + 1] = (BYTE)(nGreen);
			rImageData[y * nRowBytes + x * 3 + 0] = (BYTE)(nBlue);
		}
		delete  pCb;
		delete  pCr;
	}
	else
	{
		for (x = 0; x < 256; x++)
			hist[x] = 0.0f;
		avegrey = 0;

		for (y = 0; y < nRows; y++)
		for (x = 0; x < nCols; x++)
		{
			nBlue = sImageData[y * nRowBytes + x * 3 + 0];
			nGreen = sImageData[y * nRowBytes + x * 3 + 1];
			nRed = sImageData[y * nRowBytes + x * 3 + 2];
			pY[y*nCols + x] = (int)(0.299*nRed + 0.587*nGreen + 0.114*nBlue);
			hist[pY[y*nCols + x]] = hist[pY[y*nCols + x]] + 1;
			avegrey += pY[y*nCols + x];
		}

		avegrey = avegrey / (nRows*nCols);
		mmax = mmin = hist[0];
		for (x = 0; x < 256; x++)
		{
			if (mmax < hist[x]) mmax = hist[x];
			else if (mmin > hist[x]) mmin = hist[x];
		}

		mdlg.averagegrey = (int)avegrey;
		for (x = 0; x < 256; x++)
		{
			hist[x] = 255.0 * (hist[x] - mmin) / (mmax - mmin);
			mdlg.histogram[x] = (int)hist[x];
		}

		if (mdlg.DoModal() == IDCANCEL)
		{
			delete  pY;
			return;
		}

		for (y = 0; y < nRows; y++)
		for (x = 0; x < nCols; x++)
		{
			nGrey = pY[y*nCols + x];
			mdlg.plink = mdlg.pBreakPoints;
			while (mdlg.plink)
			{
				if (mdlg.plink->pNext)
				{
					if (nGrey >= mdlg.plink->m_pt.x  &&  nGrey < mdlg.plink->pNext->m_pt.x)
					{
						pY[y*nCols + x] = (int)(mdlg.plink->m_pt.y + mdlg.plink->m_k  * (nGrey - mdlg.plink->m_pt.x));
						break;
					}
					else if (nGrey == mdlg.plink->m_pt.x  &&  nGrey == mdlg.plink->pNext->m_pt.x)
					{
						pY[y*nCols + x] = (int)mdlg.plink->m_k;
						break;
					}
				}
				else
					pY[y*nCols + x] = (int)mdlg.plink->m_k;

				mdlg.plink = mdlg.plink->pNext;
			}

			rImageData[y * nRowBytes + x * 3 + 2] = (BYTE)(pY[y*nCols + x]);
			rImageData[y * nRowBytes + x * 3 + 1] = (BYTE)(pY[y*nCols + x]);
			rImageData[y * nRowBytes + x * 3 + 0] = (BYTE)(pY[y*nCols + x]);
		}
	}
	delete pY;
	UpdateAllViews(NULL);
}


void CImageProcessingDoc::OnBitPlane()
{
	// TODO: 在此添加命令处理程序代码
	if (m_sImage.IsNull())
	{
		AfxMessageBox(_T("请打开要处理的图像！"));
		return;
	}
   	
	CDialogBitPlane mdlg;
	if (mdlg.DoModal() != IDOK)
		return;

	int x;
	int y;
	int nRows = m_sImage.GetHeight();
	int nCols = m_sImage.GetWidth();
	int nBPP =  m_sImage.GetBPP();
   	
	int nRed, nGreen, nBlue;
	int nGrey;

	m_rImage.Destroy();
	if (!m_rImage.Create(nCols, nRows, nBPP))
		return;

	BYTE *sImageData = (BYTE *)m_sImage.GetBits();
	BYTE *rImageData = (BYTE *)m_rImage.GetBits();
	int nRowBytes    = m_sImage.GetPitch();

	double hist[255];
	for (x = 0; x < 255;x++)
		hist[x] = 0.0f;

	for (y = 0; y < nRows; y++)
	for (x = 0; x < nCols; x++)
	{
		nBlue  = sImageData[y * nRowBytes + x * 3 + 0];
	    nGreen = sImageData[y * nRowBytes + x * 3 + 1];
		nRed   = sImageData[y * nRowBytes + x * 3 + 2];
		nGrey  = (int)(0.299*nRed + 0.587*nGreen + 0.114*nBlue);
		nGrey = nGrey & (0x80 >> (7 - mdlg.nBitPlane));
		rImageData[y * nRowBytes + x * 3 + 0] = nGrey;
		rImageData[y * nRowBytes + x * 3 + 1] = nGrey;
		rImageData[y * nRowBytes + x * 3 + 2] = nGrey;
     }

	 UpdateAllViews(NULL);	
}

void CImageProcessingDoc::OnGreyhistogram()
{
	// TODO: 在此添加命令处理程序代码
	if (m_sImage.IsNull())
	{
		AfxMessageBox(_T("请打开要处理的图像！"));
		return;
	}
   
	int x;
	int y;
	int nRows = m_sImage.GetHeight();
	int nCols = m_sImage.GetWidth();
	int nBPP =  m_sImage.GetBPP();
   	
	int nRed, nGreen, nBlue;
	int nGrey;

	m_rImage.Destroy();

	if (!m_rImage.Create(256, nRows, nBPP))
		return;

	BYTE *sImageData = (BYTE *)m_sImage.GetBits();
	BYTE *rImageData = (BYTE *)m_rImage.GetBits();
	int nRowBytes    = m_sImage.GetPitch();
	int nLineBytes   = m_rImage.GetPitch();
	double  mmax, mmin;
	double hist[256];

	for (x = 0; x < 256; x++)
		hist[x] = 0.0f;

	for (y = 0; y < nRows; y++)
	for (x = 0; x < nCols; x++)
	{
		 nBlue  = sImageData[y * nRowBytes + x * 3 + 0];
		 nGreen = sImageData[y * nRowBytes + x * 3 + 1];
		 nRed   = sImageData[y * nRowBytes + x * 3 + 2];
		 nGrey = (int)(0.299*nRed + 0.587*nGreen + 0.114*nBlue);
		 hist[nGrey] = hist[nGrey] + 1;
	}

	mmax = mmin = hist[0];
	for (x = 0; x < 256; x++)
	{
		if (mmax < hist[x])  mmax = hist[x];
		else if (mmin > hist[x])  mmin = hist[x];
	}

	for (x = 0; x < 256; x++)
	{
		hist[x] = nRows * (hist[x] - mmin)/(mmax - mmin);
	}

	for (x = 0; x < 256; x++)
	{
		for (y = 0; y < nRows; y++)
		{
			nGrey = (y > (int)(nRows - hist[x])) ? 0 : 255;
			rImageData[y * nLineBytes + x * 3 + 2] = nGrey;
			rImageData[y * nLineBytes + x * 3 + 1] = nGrey;
			rImageData[y * nLineBytes + x * 3 + 0] = nGrey;
			if (y == nRows - 1)
			{
				rImageData[y * nLineBytes + x * 3 + 2] = 0;
				rImageData[y * nLineBytes + x * 3 + 1] = 0;
				rImageData[y * nLineBytes + x * 3 + 0] = 255;
			}
		}
	}

	UpdateAllViews(NULL);
}

void CImageProcessingDoc::OnHistogramequalization()
{
	// TODO: 在此添加命令处理程序代码

	if (m_sImage.IsNull())
	{
		AfxMessageBox(_T("请打开要处理的图像！"));
		return;
	}
   
	int x;
	int y;
	int nRows = m_sImage.GetHeight();
	int nCols = m_sImage.GetWidth();
	int nBPP =  m_sImage.GetBPP();
   	
	int mY, mCb, mCr;
	int nRed, nGreen, nBlue;
	m_rImage.Destroy();

	if (!m_rImage.Create(nCols, nRows, nBPP))
		return;

	BYTE *sImageData = (BYTE *)m_sImage.GetBits();
	BYTE *rImageData = (BYTE *)m_rImage.GetBits();
	int nRowBytes    = m_sImage.GetPitch();

	bool  bColorPorcessing;
	if (AfxMessageBox(L"处理彩色图像？", MB_YESNO) == IDYES)
		bColorPorcessing = true;
	else
		bColorPorcessing = false;
	
	int *pY = new int[nRows*nCols];

	if (bColorPorcessing)
	{
		int *pCb = new int[nRows*nCols];
		int *pCr = new int[nRows*nCols];

		for (y = 0; y < nRows; y++)
	    for (x = 0; x < nCols; x++)
	    {
		   nBlue  = sImageData[y * nRowBytes + x * 3 + 0];
		   nGreen = sImageData[y * nRowBytes + x * 3 + 1];
		   nRed   = sImageData[y * nRowBytes + x * 3 + 2];
		   mY  = (int)(0.257*nRed + 0.564*nGreen + 0.098*nBlue) + 16;
		   mCb = 128 + (int)(-0.148*nRed - 0.291*nGreen + 0.439*nBlue);
		   mCr = 128 + (int)(0.439*nRed - 0.368*nGreen - 0.071*nBlue);
		   if (mY < 0)  mY = 0;
		   else if (mY > 255)	mY = 255;
		   if (mCb < 0)  mCb = 0;
		   else if (mCb > 255)  mCb = 255;
		   if (mCr < 0)   mCr = 0;
		   else if (mCr > 255) 	mCr = 255;
		   pY[y*nCols+x]  = (BYTE)mY; 
		   pCb[y*nCols+x] = (BYTE)mCb;
		   pCr[y*nCols+x] = (BYTE)mCr;
	    }
	    //直方图均衡化
	    HistogramEqualization(pY, nRows, nCols);
	    for (y = 0; y < nRows; y++)
	    for (x = 0; x < nCols; x++)
	    {
		   nRed   = (int)( 1.164*pY[y*nCols + x] + 1.596 * pCr[y*nCols + x]  - 222.912);
		   nGreen = (int)( 1.164*pY[y*nCols + x] - 0.391 * pCb[y*nCols + x] -0.813 * pCr[y*nCols + x] +135.488);
		   nBlue  = (int)( 1.164*pY[y*nCols + x] + 2.018 * pCb[y*nCols + x] - 276.928);

		   if (nRed < 0) nRed = 0;
		   else if (nRed>255) nRed = 255;
		   if (nGreen < 0) nGreen = 0;
		   else if (nGreen>255) nGreen = 255;
		   if (nBlue < 0) nBlue = 0;
		   else if (nBlue>255) nBlue = 255;

		   rImageData[y * nRowBytes + x * 3 + 2] = (BYTE)( nRed );
		   rImageData[y * nRowBytes + x * 3 + 1] = (BYTE)( nGreen );
		   rImageData[y * nRowBytes + x * 3 + 0] = (BYTE)( nBlue);
	     }
		delete pCb;
		delete pCr;
	 }
	 else
	 {
		for (y = 0; y < nRows; y++)
	    for (x = 0; x < nCols; x++)
	    {
		   nBlue  = sImageData[y * nRowBytes + x * 3 + 0];
		   nGreen = sImageData[y * nRowBytes + x * 3 + 1];
		   nRed   = sImageData[y * nRowBytes + x * 3 + 2];
		   pY[y*nCols + x] = (int)(0.299*nRed + 0.587*nGreen + 0.114*nBlue);
	    }

	    //直方图均衡化
	    HistogramEqualization(pY, nRows, nCols);

	    for (y = 0; y < nRows; y++)
	    for (x = 0; x < nCols; x++)
	    {
		   rImageData[y * nRowBytes + x * 3 + 2] = (BYTE)(pY[y*nCols + x]);
		   rImageData[y * nRowBytes + x * 3 + 1] = (BYTE)(pY[y*nCols + x]);
		   rImageData[y * nRowBytes + x * 3 + 0] = (BYTE)(pY[y*nCols + x]);
	     }

	 }

	 delete[] pY;
	 UpdateAllViews(NULL);
}


void CImageProcessingDoc::OnLocalHistogramEqualization()
{
	// TODO: 在此添加命令处理程序代码

}


void CImageProcessingDoc::OnHistogramStatistics()
{
	// TODO: 在此添加命令处理程序代码
}


void CImageProcessingDoc::OnSmoothingSpatiaFiltering()
{
	// TODO: 在此添加命令处理程序代码

	if (m_sImage.IsNull())
	{
		AfxMessageBox(_T("请打开要处理的图像！"));
		return;
	}

	m_rImage.Destroy();
	if (!m_rImage.Create(m_sImage.GetWidth(), m_sImage.GetHeight(), m_sImage.GetBPP(), 0))
		return;

	int x;
	int y;
	int temp;
	int nHeight = m_sImage.GetHeight();
	int nWidth = m_sImage.GetWidth();
	int nLineBytes = m_sImage.GetPitch();

	LPBYTE sImageData = (BYTE *)m_sImage.GetBits();
	LPBYTE rImageData = (LPBYTE)m_rImage.GetBits();

	LPBYTE pGrey = NULL;
	LPBYTE pEdge = NULL;
	
	CDialogSpatialFiltering mdlg;
	if (mdlg.DoModal() != IDOK)
		return; 

	switch (mdlg.m_checkImageEnhancement)
	{
	case 0: //空域平滑滤波
		    switch(mdlg.m_smooth_operator)
 	        { 
	           case 0: //均值算子
				   MeanOperator(&m_sImage, &m_rImage,mdlg.m_YRadius,mdlg.m_XRadius);
				   break;
			   case 1:  //高斯算子
				   GaussOperator(&m_sImage, &m_rImage, mdlg.m_YRadius, mdlg.m_XRadius, mdlg.m_sigma);
				   break;
			   case 2: //统计滤波算子
				   switch (mdlg.m_statistics_operator)
				   {
				        case 0:
							MedianOperator(&m_sImage, &m_rImage, mdlg.m_YRadius, mdlg.m_XRadius);
							break;
						case 1:
							MininumOperator(&m_sImage, &m_rImage, mdlg.m_YRadius, mdlg.m_XRadius);
							break;
						case 2:
							MiddleOperator(&m_sImage, &m_rImage, mdlg.m_YRadius, mdlg.m_XRadius);
							break;
						case 3:
							MaxinumOperator(&m_sImage, &m_rImage, mdlg.m_YRadius, mdlg.m_XRadius);
							break;
						default:
							return;
				   }
				   break;
			   default:
				   return;
	         }
			break;
	case 1: //空域平滑滤波图像增强
		    switch(mdlg.m_smooth_operator)
 	        { 
	           case 0: //均值算子
				   MeanOperator(&m_sImage, &m_rImage,mdlg.m_YRadius,mdlg.m_XRadius);
				   break;
			   case 1:  //高斯算子
				   GaussOperator(&m_sImage, &m_rImage, mdlg.m_YRadius, mdlg.m_XRadius, mdlg.m_sigma);
				   break;
			   case 2: //统计滤波算子
				   switch (mdlg.m_statistics_operator)
				   {
				        case 0:
							MedianOperator(&m_sImage, &m_rImage, mdlg.m_YRadius, mdlg.m_XRadius);
							break;
						case 1:
							MininumOperator(&m_sImage, &m_rImage, mdlg.m_YRadius, mdlg.m_XRadius);
							break;
						case 2:
							MiddleOperator(&m_sImage, &m_rImage, mdlg.m_YRadius, mdlg.m_XRadius);
							break;
						case 3:
							MaxinumOperator(&m_sImage, &m_rImage, mdlg.m_YRadius, mdlg.m_XRadius);
							break;
						default:
							return;
				   }
				   break;
			   default:
				   return;
	        }
           
		    for (y = 0; y < nHeight; y++)
	        for (x = 0; x < nWidth; x++)
            {   //蓝色
		        temp = sImageData[y*nLineBytes + 3 * x + 0] - rImageData[y*nLineBytes + 3 * x + 0];
		        temp = (int)(sImageData[y*nLineBytes + 3 * x + 0] + mdlg.m_para_k*temp);
		        temp = temp > 255 ? 255 : (temp < 0 ? 0 : temp);
		        rImageData[y*nLineBytes + 3 * x + 0] = temp;
                //绿色
		        temp = sImageData[y*nLineBytes + 3 * x + 1] - rImageData[y*nLineBytes + 3 * x + 1];
		        temp = (int)(sImageData[y*nLineBytes + 3 * x + 1] + mdlg.m_para_k*temp);
		        temp = temp > 255 ? 255 : (temp < 0 ? 0 : temp);
		        rImageData[y*nLineBytes + 3 * x + 1] = temp;
				//红色
		        temp = sImageData[y*nLineBytes + 3 * x + 2] - rImageData[y*nLineBytes + 3 * x + 2];
		        temp = (int)(sImageData[y*nLineBytes + 3 * x + 2] + mdlg.m_para_k*temp);
		        temp = temp > 255 ? 255 : (temp < 0 ? 0 : temp);
		        rImageData[y*nLineBytes + 3 * x + 2] = temp;
			}
		    break;
	default:return;
	}

	UpdateAllViews(NULL);
}

void CImageProcessingDoc::OnSharpeningSpatialFiltering()
{
	// TODO: 在此添加命令处理程序代码
	if (m_sImage.IsNull())
	{
		AfxMessageBox(_T("请打开要处理的图像！"));
		return;
	}

	m_rImage.Destroy();
	if (!m_rImage.Create(m_sImage.GetWidth(), m_sImage.GetHeight(), m_sImage.GetBPP(), 0))
		return;

	int x;
	int y;
	int nHeight = m_sImage.GetHeight();
	int nWidth = m_sImage.GetWidth();
	int nLineBytes = m_sImage.GetPitch();

	LPBYTE sImageData = (BYTE *)m_sImage.GetBits();
	LPBYTE rImageData = (LPBYTE)m_rImage.GetBits();

	LPBYTE pGrey = NULL;
	LPBYTE pEdge = NULL;
	
	double dx;
	int emhancement;

	double sqrt2 = sqrt(2);
	CDialogSharpeningParameters mdlg;
	if (mdlg.DoModal() != IDOK)
		return; 
	
    BOOL mbCalibration = (mdlg.bCheckSpatialSharpeningEnhancenent) ? FALSE : (mdlg.m_check_bCalibration);
	switch (mdlg.m_radio_operatorType)
	{
	case 0: GradsOperator(&m_sImage, &m_rImage, mbCalibration, mdlg.bCheckSpatialSharpeningEnhancenent);
		    break;
	case 1: RobertsOperator(&m_sImage, &m_rImage, mbCalibration,mdlg.bCheckSpatialSharpeningEnhancenent);
		    break;
	case 2: SobelOperator(&m_sImage, &m_rImage, mbCalibration, mdlg.bCheckSpatialSharpeningEnhancenent);
		    break;
	case 3: PrewittOperator(&m_sImage, &m_rImage, mbCalibration, mdlg.bCheckSpatialSharpeningEnhancenent);
		    break;
	case 4: IsotropicOperator(&m_sImage, &m_rImage, mbCalibration, mdlg.bCheckSpatialSharpeningEnhancenent);
		    break;
	case 5: LaplaceOperator(&m_sImage, &m_rImage, mdlg.m_radio_laplacian_operatorType + 1, mbCalibration,mdlg.bCheckSpatialSharpeningEnhancenent);
		    break;
	case 6: pGrey = new BYTE[nHeight*nWidth];
		    pEdge = new BYTE[nHeight*nWidth];
		    GetGreyBitsFromImage(&m_sImage, pGrey);
		    CannyOperator(pGrey, nHeight, nWidth, mdlg.sigma, mdlg.ratioLow_High, mdlg.ratioHigh_Total, pEdge);
		    for (y = 0; y < nHeight; y++)
			for (x = 0; x < nWidth; x++)
			{
				rImageData[y*nLineBytes + 3 * x + 0] = pEdge[y*nWidth + x];
				rImageData[y*nLineBytes + 3 * x + 1] = pEdge[y*nWidth + x];
				rImageData[y*nLineBytes + 3 * x + 2] = pEdge[y*nWidth + x];
			}
		    // 释放内存
		    if(pGrey)  delete pGrey;
		    pGrey = NULL;
		    if(pEdge)  delete pEdge;
		    pEdge = NULL;
  		    break;
	case 7: KirschOperator(&m_sImage, &m_rImage, mdlg.m_radio_kirschType + 1, mdlg.m_check_bCalibration);
		    break;
	case 8: for (y = 1; y < nHeight - 1; y++)
			for (x = 1; x < nWidth - 1; x++)
			{
				dx = sImageData[y*nLineBytes + x * 3 + 0] - sImageData[y*nLineBytes + (x - 1) * 3 + 0];
				emhancement = (int)(dx + 128);
				emhancement = (emhancement > 255) ? 255 : emhancement;
				rImageData[y*nLineBytes + x * 3 + 0] = emhancement;

				dx = sImageData[y*nLineBytes + x * 3 + 1] - sImageData[y*nLineBytes + (x - 1) * 3 + 1];
				emhancement = (int)(dx + 128);
				emhancement = (emhancement > 255) ? 255 : emhancement;
				rImageData[y*nLineBytes + x * 3 + 1] = emhancement;

				dx = sImageData[y*nLineBytes + x * 3 + 2] - sImageData[y*nLineBytes + (x - 1) * 3 + 2];
				emhancement = (int)(dx + 128);
				emhancement = (emhancement > 255) ? 255 : emhancement;
				rImageData[y*nLineBytes + x * 3 + 2] = emhancement;
			}
		    break;
	default:return;
	}

	UpdateAllViews(NULL);
}

//图像快速傅里叶变换
void CImageProcessingDoc::OnImageFastFourierTransform()
{
	// TODO: 在此添加命令处理程序代码

	if (m_sImage.IsNull())
	{
		return;
	}
	int sWidth = m_sImage.GetWidth();
	int sHeight = m_sImage.GetHeight();
	int sRowBytes = m_sImage.GetPitch();

	m_rImage.Destroy();
	if (!m_rImage.Create(sWidth, sHeight, m_sImage.GetBPP(), 0))
		return;

	BYTE *sImageData = (BYTE *)m_sImage.GetBits();
	BYTE *rImageData = (BYTE *)m_rImage.GetBits();

	float *inReal;
	float *inImage;
	float *outReal;
	float *outImage;

	inReal = new float[sHeight*sWidth];
	inImage = new float[sHeight*sWidth];

	outReal = new float[sHeight*sWidth];
	outImage = new float[sHeight*sWidth];

	int x;
	int y;

	int i;
	for (i = 0; i < 3; i++)
	{
		for (y = 0; y < sHeight; y++)
			for (x = 0; x < sWidth; x++)
			{
				inReal[y*sWidth + x] = (float)sImageData[y*sRowBytes + 3 * x + i];
				inImage[y*sWidth + x] = 0;
			}

		FFT2DandIFFT2D(inReal, inImage, outReal, outImage, sHeight, sWidth, TRUE);

		for (y = 0; y < sHeight; y++)
			for (x = 0; x < sWidth; x++)
			{
				//将变换后现实的原点调整在中心位置
				float tmpp = sqrt(outReal[y*sWidth + x] * outReal[y*sWidth + x] + outImage[y*sWidth + x] * outImage[y*sWidth + x]);
				rImageData[y*sRowBytes + x * 3 + i] = (int)tmpp / 100;
			}
	}

	delete inReal;
	delete inImage;
	delete outReal;
	delete outImage;

	UpdateAllViews(NULL);
}

//图像快速傅里叶变换，坐标中心平移到图像中心
void CImageProcessingDoc::OnImageFastFourierTransformCenter()
{
	// TODO: 在此添加命令处理程序代码
	if (m_sImage.IsNull())
	{
		return;
	}
	int sWidth = m_sImage.GetWidth();
	int sHeight = m_sImage.GetHeight();
    int sRowBytes = m_sImage.GetPitch();
	m_rImage.Destroy();
	if (!m_rImage.Create(sWidth, sHeight, m_sImage.GetBPP(), 0))
		return;

	BYTE *sImageData = (BYTE *)m_sImage.GetBits();
	BYTE *rImageData = (BYTE *)m_rImage.GetBits();

	float *inReal;
	float *inImage;
	float *outReal;
	float *outImage;

	inReal = new float[sHeight*sWidth];
	inImage = new float[sHeight*sWidth];

	outReal = new float[sHeight*sWidth];
	outImage = new float[sHeight*sWidth];

	int x;
	int y;

	int i;

	for (i = 0; i < 3;i++)
	{
		for (y = 0; y < sHeight;y++)
		for (x = 0; x < sWidth;x++)
        {
			if ((y < sHeight) && (x < sWidth))
			{
				int sgn = ((x + y) % 2 == 0) ? 1 : -1;
				inReal[y*sWidth + x] = (float)sgn*sImageData[y*sRowBytes + 3 * x + i] ;
			}
			else
			{
				inReal[y*sWidth + x] = 0;
			}
			inImage[y*sWidth + x] = 0;
        }

		FFT2DandIFFT2D(inReal, inImage, outReal, outImage, sHeight, sWidth, TRUE);



		for (y = 0; y < sHeight; y++)
		for (x = 0; x<sWidth; x++)
		{
			float temp = (float)sqrt(outReal[y*sWidth + x] * outReal[y*sWidth + x] + outImage[y*sWidth + x] * outImage[y*sWidth + x]);
			temp /= 300;
			temp = (temp>255.0f) ? 255.0f : temp;
			//将变换后现实的原点调整在中心位置
			rImageData[y*sRowBytes + x*3+i] = (int)temp;
		}
	}
	delete inReal;
	delete inImage;
	delete outReal;
	delete outImage;

	UpdateAllViews(NULL);
}

//离散余弦变换
void CImageProcessingDoc::OnDctTransform()
{
	// TODO: 在此添加命令处理程序代码

	if (m_sImage.IsNull())
	{
		return;
	}
	int sWidth = m_sImage.GetWidth();
	int sHeight = m_sImage.GetHeight();
    int sRowBytes = m_sImage.GetPitch();

	m_rImage.Destroy();
	if (!m_rImage.Create(sWidth, sHeight, m_sImage.GetBPP(), 0))
		return;

	BYTE *sImageData = (BYTE *)m_sImage.GetBits();
	BYTE *rImageData = (BYTE *)m_rImage.GetBits();

	float *inData = NULL;
	float *outData = NULL;

	inData = new float[sHeight*sWidth];
	outData = new float[sHeight*sWidth];

    int x;
	int y;
	int i;

	for (i = 0; i < 3;i++)
	{
		for (y = 0; y < sHeight; y++)
		for (x = 0; x < sWidth; x++)
			inData[y*sWidth + x] = (float)sImageData[y*sRowBytes + 3 * x + i];

		DCT2DandIDCT2D(inData, outData, sHeight, sWidth, TRUE);
		
		for (y = 0; y < sHeight; y++)
		for (x = 0; x<sWidth; x++)
		{
			float temp = outData[y*sWidth + x];
			temp /= 300;
			temp = (temp>255.0f) ? 255.0f : temp;
			//将变换后现实的原点调整在中心位置
			rImageData[y*sRowBytes + x*3+i] = (int)temp;
		}
	}
				
	delete inData;
	delete outData;
	UpdateAllViews(NULL);
}

//一个简单的傅里叶变换应用(教材作业P194 4.33题）
void CImageProcessingDoc::OnFourierTransformApplication()
{
	// TODO: 在此添加命令处理程序代码
	if (m_sImage.IsNull())
	{
		return;
	}
	int sWidth = m_sImage.GetWidth();
	int sHeight = m_sImage.GetHeight();

	m_rImage.Destroy();
	if (!m_rImage.Create(sWidth, sHeight, m_sImage.GetBPP(), 0))
		return;

	int sRowBytes = m_sImage.GetPitch();

	BYTE *sImageData = (BYTE *)m_sImage.GetBits();
	BYTE *rImageData = (BYTE *)m_rImage.GetBits();

	float *inReal;
	float *inImage;
	float *outReal;
	float *outImage;

	inReal = new float[sHeight*sWidth];
	inImage = new float[sHeight*sWidth];

	outReal = new float[sHeight*sWidth];
	outImage = new float[sHeight*sWidth];

	int x;
	int y;
	
	for (y = 0; y < sHeight; y++)
	for (x = 0; x < sWidth; x++)
	{
		int sgn = ((x + y) % 2 == 0) ? 1 : -1;
		inReal[y*sWidth + x] = (float)(sgn * (0.114*sImageData[y*sRowBytes + 3 * x ] + 0.587*sImageData[y*sRowBytes + 3 * x + 1] + 0.229*sImageData[y*sRowBytes + 3 * x + 2]));
		inImage[y*sWidth + x] = 0;
	}

	FFT2DandIFFT2D(inReal, inImage, outReal, outImage, sHeight, sWidth, TRUE);

	for (y = 0; y < sHeight; y++)
	for (x = 0; x < sWidth; x++)
	{
		outImage[y*sWidth + x] = -outImage[y*sWidth + x];
	}

	//对滤波后信号进行傅立叶反变换
	FFT2DandIFFT2D(outReal, outImage, inReal, inImage, sHeight, sWidth, FALSE);

	//信号f(x,y)乘以(-1)^(x+y)，消除对输入图像的乘数
	for (y = 0; y < sHeight; y++)
	for (x = 0; x < sWidth; x++)
	{
		inReal[y*sWidth + x] *= (((x + y) % 2 == 0) ? 1 : (-1));
	}

	for (y = 0; y < sHeight; y++)
	for (x = 0; x<sWidth; x++)
	{
		rImageData[y*sRowBytes + x * 3 ]    = (int)inReal[y*sWidth + x];
		rImageData[y*sRowBytes + x * 3 + 1] = (int)inReal[y*sWidth + x];
		rImageData[y*sRowBytes + x * 3 + 2] = (int)inReal[y*sWidth + x];
	}

	delete inReal;
	delete inImage;
	delete outReal;
	delete outImage;

	UpdateAllViews(NULL);
}

//图像陷波滤波器滤波
void CImageProcessingDoc::OnNotchFiltering()
{
	// TODO: 在此添加命令处理程序代码
	if (m_sImage.IsNull())
		return;

	int sWidth = m_sImage.GetWidth();
	int sHeight = m_sImage.GetHeight();
    int sRowBytes = m_sImage.GetPitch();

	m_rImage.Destroy();
	if (!m_rImage.Create(sWidth, sHeight, m_sImage.GetBPP(), 0))
		return;

	BYTE *sImageData = (BYTE *)m_sImage.GetBits();
	BYTE *rImageData = (BYTE *)m_rImage.GetBits();

	int x;
	int y;

	float *inReal;
	float *inImage;
	float *outReal;
	float *outImage;
	int filterHeight = sHeight << 1;
	int filterWidth = sWidth << 1;

	inReal = new float[filterHeight*filterWidth];
	inImage = new float[filterHeight*filterWidth];

	outReal = new float[filterHeight*filterWidth];
	outImage = new float[filterHeight*filterWidth];

	for (y = 0; y < filterHeight; y++)
	for (x = 0; x < filterWidth; x++)
	{
		if ((y < sHeight) && (x < sWidth))
		{
			int sgn = ((x + y) % 2 == 0) ? 1 : -1;
			inReal[y*filterWidth + x] = (float)(sgn*(0.114*sImageData[y*sRowBytes + 3 * x] + 0.587*sImageData[y*sRowBytes + 3 * x + 1] + 0.229*sImageData[y*sRowBytes + 3 * x + 2]));
		}
		else
			inReal[y*filterWidth + x] = 0;
		inImage[y*filterWidth + x] = 0;
	}

	FFT2DandIFFT2D(inReal, inImage, outReal, outImage, filterHeight, filterWidth, TRUE);
	

	//使用陷波滤波器进行滤波
	outReal[(filterHeight>>1)*filterWidth + (filterWidth>>1)] = 0.0f;
	outImage[(filterHeight >> 1)*filterWidth + (filterWidth >> 1)] = 0.0f;

	//对滤波后信号进行傅立叶反变换
	FFT2DandIFFT2D(outReal, outImage, inReal, inImage, filterHeight, filterWidth, FALSE);

	for (y = 0; y < sHeight; y++)
	for (x = 0; x < sWidth; x++)
	{
		float temp = inReal[y*filterWidth + x] * (((x + y) % 2 == 0) ? 1 : -1);
		temp = temp > 255 ? 255 : (temp < 0 ? 0 : temp);
		rImageData[y*sRowBytes + x * 3] = (int)temp;
		rImageData[y*sRowBytes + x * 3 + 1] = (int)temp;
		rImageData[y*sRowBytes + x * 3 + 2] = (int)temp;
	}

	delete inReal;
	delete inImage;
	delete outReal;
	delete outImage;

	UpdateAllViews(NULL);
}

//图像理想低通滤波
void CImageProcessingDoc::OnIdeaLowPassFiltering()
{
	// TODO: 在此添加命令处理程序代码
	if (m_sImage.IsNull())
	{
		return;
	}

	int sWidth = m_sImage.GetWidth();
	int sHeight = m_sImage.GetHeight();
    int sRowBytes = m_sImage.GetPitch();

	m_rImage.Destroy();
	if (!m_rImage.Create(sWidth, sHeight, m_sImage.GetBPP(), 0))
		return;

	BYTE *sImageData = (BYTE *)m_sImage.GetBits();
	BYTE *rImageData = (BYTE *)m_rImage.GetBits();

	int x;
	int y;
	CDialogFreqFilteringParameters  mdlg;
	if (mdlg.DoModal() != IDOK)
	{
		return;
	}

	float *inReal;
	float *inImage;
	float *outReal;
	float *outImage;
	int filterHeight = sHeight << 1;
	int filterWidth = sWidth << 1;

	inReal = new float[filterHeight*filterWidth];
	inImage = new float[filterHeight*filterWidth];

	outReal = new float[filterHeight*filterWidth];
	outImage = new float[filterHeight*filterWidth];

	for (y = 0; y < filterHeight; y++)
	for (x = 0; x < filterWidth; x++)
	{
		if ((y < sHeight) && (x < sWidth))
		{
			int sgn = ((x + y) % 2 == 0) ? 1 : -1;
			inReal[y*filterWidth + x] = (float)(sgn*(0.114*sImageData[y*sRowBytes + 3 * x] + 0.587*sImageData[y*sRowBytes + 3 * x + 1] + 0.229*sImageData[y*sRowBytes + 3 * x + 2]));
		}
		else
			inReal[y*filterWidth + x] = 0;
		inImage[y*filterWidth + x] = 0;
	}

	FFT2DandIFFT2D(inReal, inImage, outReal, outImage, filterHeight, filterWidth, TRUE);
	
	int m_D;
	int m_D0;

	float mPt = 0;
	float mP = 0;
	for (y = 0; y < filterHeight; y++)
	for (x = 0; x < filterWidth; x++)
	{
		mPt += outReal[y*filterWidth + x] * outReal[y*filterWidth + x] + outImage[y*filterWidth + x] * outImage[y*filterWidth + x];
	}

	mPt *= (float)(mdlg.m_alpha*0.01);

	m_D0 = (filterHeight > filterWidth) ? filterWidth / 2 : filterHeight / 2;
	for (m_D = 0; m_D < m_D0; m_D++)
	{
		mP = 0;
		for (y = -m_D; y <= m_D; y++)
		for (x = -m_D; x <= m_D; x++)
		{   if( x*x + y*y <= m_D*m_D)
			   mP += outReal[(y + filterHeight / 2)*filterWidth + (x + filterWidth / 2)] * outReal[(y + filterHeight / 2)*filterWidth + (x + filterWidth / 2)]
			      + outImage[(y + filterHeight / 2)*filterWidth + (x + filterWidth / 2)] * outImage[(y + filterHeight / 2)*filterWidth + (x + filterWidth / 2)];
		}

		if (mP>=mPt)
		{
			break;
		}
	}

	m_D0 = m_D;
	//m_D0 = mdlg.m_filteringRadius;

	//使用理想低通滤波器进行滤波
	for (y = 0; y < filterHeight; y++)
	for (x = 0; x < filterWidth; x++)
	{
		m_D = (int)(sqrt((x - filterWidth / 2) * (x - filterWidth / 2) + (y - filterHeight / 2) * (y - filterHeight / 2)));
		if (m_D > m_D0)
		{
			outReal[y*filterWidth + x] = 0.0f;
			outImage[y*filterWidth + x] = 0.0f;
		}
	}

	//对滤波后信号进行傅立叶反变换
	FFT2DandIFFT2D(outReal, outImage, inReal, inImage, filterHeight, filterWidth, FALSE);

	for (y = 0; y < sHeight; y++)
	for (x = 0; x < sWidth; x++)
	{
		float temp = inReal[y*filterWidth + x] * (((x + y) % 2 == 0) ? 1 : -1);
		temp = temp > 255 ? 255 : (temp < 0 ? 0 : temp);
		rImageData[y*sRowBytes + x * 3] = (int)temp;
		rImageData[y*sRowBytes + x * 3 + 1] = (int)temp;
		rImageData[y*sRowBytes + x * 3 + 2] = (int)temp;
	}

	delete inReal;
	delete inImage;
	delete outReal;
	delete outImage;

	UpdateAllViews(NULL);
}

//图像理想高通滤波
void CImageProcessingDoc::OnIdeaHighPassFiltering()
{
	// TODO: 在此添加命令处理程序代码
	if (m_sImage.IsNull())
	{
		return;
	}

	int sWidth = m_sImage.GetWidth();
	int sHeight = m_sImage.GetHeight();
    int sRowBytes = m_sImage.GetPitch();

	m_rImage.Destroy();
	if (!m_rImage.Create(sWidth, sHeight, m_sImage.GetBPP(), 0))
		return;

	BYTE *sImageData = (BYTE *)m_sImage.GetBits();
	BYTE *rImageData = (BYTE *)m_rImage.GetBits();

	int x;
	int y;
	CDialogFreqFilteringParameters  mdlg;
	if (mdlg.DoModal() != IDOK)
	{
		return;
	}

	float *inReal;
	float *inImage;
	float *outReal;
	float *outImage;
	int filterHeight = sHeight << 1;
	int filterWidth = sWidth << 1;

	inReal = new float[filterHeight*filterWidth];
	inImage = new float[filterHeight*filterWidth];

	outReal = new float[filterHeight*filterWidth];
	outImage = new float[filterHeight*filterWidth];

	for (y = 0; y < filterHeight; y++)
	for (x = 0; x < filterWidth; x++)
	{
		if ((y < sHeight) && (x < sWidth))
		{
			int sgn = ((x + y) % 2 == 0) ? 1 : -1;
			inReal[y*filterWidth + x] = (float)(sgn*(0.114*sImageData[y*sRowBytes + 3 * x] + 0.587*sImageData[y*sRowBytes + 3 * x + 1] + 0.229*sImageData[y*sRowBytes + 3 * x + 2]));
		}
		else
			inReal[y*filterWidth + x] = 0;
		inImage[y*filterWidth + x] = 0;
	}

	FFT2DandIFFT2D(inReal, inImage, outReal, outImage, filterHeight, filterWidth, TRUE);

	int m_D;
	int m_D0;

	float mPt = 0;
	float mP = 0;
	for (y = 0; y < filterHeight; y++)
	for (x = 0; x < filterWidth; x++)
	{
		mPt += (float)(outReal[y*filterWidth + x] * outReal[y*filterWidth + x] + outImage[y*filterWidth + x] * outImage[y*filterWidth + x]);
	}

	mPt = (float)(mPt*mdlg.m_alpha*0.01);
	m_D0 = (filterHeight > filterWidth) ? filterWidth / 2 : filterHeight / 2;
	for (m_D = 0; m_D < m_D0; m_D++)
	{
		mP = 0;
		for (y = -m_D; y <= m_D; y++)
		for (x = -m_D; x <= m_D; x++)
		{   if( x*x + y*y <= m_D*m_D)
			   mP += (float)(outReal[(y + filterHeight / 2)*filterWidth + (x + filterWidth / 2)] * outReal[(y + filterHeight / 2)*filterWidth + (x + filterWidth / 2)]
			      + outImage[(y + filterHeight / 2)*filterWidth + (x + filterWidth / 2)] * outImage[(y + filterHeight / 2)*filterWidth + (x + filterWidth / 2)]);
		}

		if (mP>=mPt)
		{
			break;
		}
	}

	//m_D0 = m_D;
	m_D0 = mdlg.m_filteringRadius;

	//使用理想高通滤波器进行滤波
	for (y = 0; y < filterHeight; y++)
	for (x = 0; x < filterWidth; x++)
	{
		m_D = (int)(sqrt((x - filterWidth / 2) * (x - filterWidth / 2) + (y - filterHeight / 2) * (y - filterHeight / 2)));
		if (m_D < m_D0)
		{
			outReal[y*filterWidth + x] = 0.0f;
			outImage[y*filterWidth + x] = 0.0f;
		}
	}

	//对滤波后信号进行傅立叶反变换
	FFT2DandIFFT2D(outReal, outImage, inReal, inImage, filterHeight, filterWidth, FALSE);

	for (y = 0; y < sHeight; y++)
	for (x = 0; x < sWidth; x++)
	{
		int temp = (int)(inReal[y*filterWidth + x] * (((x + y) % 2 == 0) ? 1 : -1));
		temp = temp > 255 ? 255 : (temp < 0 ? 0 : temp);
		rImageData[y*sRowBytes + x * 3] = (int)temp;
		rImageData[y*sRowBytes + x * 3 + 1] = (int)temp;
		rImageData[y*sRowBytes + x * 3 + 2] = (int)temp;
	}

	delete inReal;
	delete inImage;
	delete outReal;
	delete outImage;

	UpdateAllViews(NULL);
}

//图像巴特沃斯低通滤波
void CImageProcessingDoc::OnButterworthLowpassFiltering()
{
	// TODO: 在此添加命令处理程序代码
	if (m_sImage.IsNull())
	{
		return;
	}

	int sWidth = m_sImage.GetWidth();
	int sHeight = m_sImage.GetHeight();
    int sRowBytes = m_sImage.GetPitch();

	m_rImage.Destroy();
	if (!m_rImage.Create(sWidth, sHeight, m_sImage.GetBPP(), 0))
		return;

	BYTE *sImageData = (BYTE *)m_sImage.GetBits();
	BYTE *rImageData = (BYTE *)m_rImage.GetBits();

	int x;
	int y;
	CDialogFreqFilteringParameters  mdlg;
	if (mdlg.DoModal() != IDOK)
	{
		return;
	}

	float *inReal;
	float *inImage;
	float *outReal;
	float *outImage;
	int filterHeight = sHeight << 1;
	int filterWidth = sWidth << 1;

	inReal = new float[filterHeight*filterWidth];
	inImage = new float[filterHeight*filterWidth];

	outReal = new float[filterHeight*filterWidth];
	outImage = new float[filterHeight*filterWidth];

	for (y = 0; y < filterHeight; y++)
	for (x = 0; x < filterWidth; x++)
	{
		if ((y < sHeight) && (x < sWidth))
		{
			int sgn = ((x + y) % 2 == 0) ? 1 : -1;
			inReal[y*filterWidth + x] = (float)(sgn*(0.114*sImageData[y*sRowBytes + 3 * x] + 0.587*sImageData[y*sRowBytes + 3 * x + 1] + 0.229*sImageData[y*sRowBytes + 3 * x + 2]));
		}
		else
			inReal[y*filterWidth + x] = 0;
		inImage[y*filterWidth + x] = 0;
	}

	FFT2DandIFFT2D(inReal, inImage, outReal, outImage, filterHeight, filterWidth, TRUE);
	
	double m_D;
	int m_D0 = mdlg.m_filteringRadius;
	m_D0 *= m_D0;
	double m_H;

	//使用巴特沃斯(Butterworth)低通滤波器进行滤波
	for (y = 0; y < filterHeight; y++)
	for (x = 0; x < filterWidth; x++)
	{
		m_D = (x - filterWidth / 2) * (x - filterWidth / 2) + (y - filterHeight / 2) * (y - filterHeight / 2);
		m_H = 1 / (1 + m_D / m_D0);
		outReal[y*filterWidth + x]  = (float)(outReal[y*filterWidth + x] * m_H);
		outImage[y*filterWidth + x] = (float)(outImage[y*filterWidth + x] * m_H);
    }

	//对滤波后信号进行傅立叶反变换
	FFT2DandIFFT2D(outReal, outImage, inReal, inImage, filterHeight, filterWidth, FALSE);

	for (y = 0; y < sHeight; y++)
	for (x = 0; x < sWidth; x++)
	{
		float temp = inReal[y*filterWidth + x] * (((x + y) % 2 == 0) ? 1 : -1);
		temp = temp > 255 ? 255 : (temp < 0 ? 0 : temp);
		rImageData[y*sRowBytes + x * 3] = (int)temp;
		rImageData[y*sRowBytes + x * 3 + 1] = (int)temp;
		rImageData[y*sRowBytes + x * 3 + 2] = (int)temp;
	}

	delete inReal;
	delete inImage;
	delete outReal;
	delete outImage;

	UpdateAllViews(NULL);
}

//图像巴特沃斯高通滤波
void CImageProcessingDoc::OnButterworthHighpassFiltering()
{
	// TODO: 在此添加命令处理程序代码
	if (m_sImage.IsNull())
	{
		return;
	}

	int sWidth = m_sImage.GetWidth();
	int sHeight = m_sImage.GetHeight();
    int sRowBytes = m_sImage.GetPitch();

	m_rImage.Destroy();
	if (!m_rImage.Create(sWidth, sHeight, m_sImage.GetBPP(), 0))
		return;

	BYTE *sImageData = (BYTE *)m_sImage.GetBits();
	BYTE *rImageData = (BYTE *)m_rImage.GetBits();

	int x;
	int y;
	CDialogFreqFilteringParameters  mdlg;
	if (mdlg.DoModal() != IDOK)
	{
		return;
	}

	float *inReal;
	float *inImage;
	float *outReal;
	float *outImage;
	int filterHeight = sHeight << 1;
	int filterWidth = sWidth << 1;

	inReal = new float[filterHeight*filterWidth];
	inImage = new float[filterHeight*filterWidth];

	outReal = new float[filterHeight*filterWidth];
	outImage = new float[filterHeight*filterWidth];

	for (y = 0; y < filterHeight; y++)
	for (x = 0; x < filterWidth; x++)
	{
		if ((y < sHeight) && (x < sWidth))
		{
			int sgn = ((x + y) % 2 == 0) ? 1 : -1;
			inReal[y*filterWidth + x] = (float)(sgn*(0.114*sImageData[y*sRowBytes + 3 * x] + 0.587*sImageData[y*sRowBytes + 3 * x + 1] + 0.229*sImageData[y*sRowBytes + 3 * x + 2]));
		}
		else
			inReal[y*filterWidth + x] = 0;
		inImage[y*filterWidth + x] = 0;
	}

	FFT2DandIFFT2D(inReal, inImage, outReal, outImage, filterHeight, filterWidth, TRUE);
	
	double m_D;
	int m_D0 = mdlg.m_filteringRadius;
	m_D0 *= m_D0;
	double m_H;
	//使用巴特沃斯(Butterworth)低通滤波器进行滤波
	for (y = 0; y < filterHeight; y++)
	for (x = 0; x < filterWidth; x++)
	{
		m_D = (x - filterWidth / 2) * (x - filterWidth / 2) + (y - filterHeight / 2) * (y - filterHeight / 2);
		m_H = 1 / (1 + m_D0 / m_D);
		outReal[y*filterWidth + x]  = (float)(outReal[y*filterWidth + x] * m_H);
		outImage[y*filterWidth + x] = (float)(outImage[y*filterWidth + x] * m_H);
	}

	//对滤波后信号进行傅立叶反变换
	FFT2DandIFFT2D(outReal, outImage, inReal, inImage, filterHeight, filterWidth, FALSE);

	for (y = 0; y < sHeight; y++)
	for (x = 0; x < sWidth; x++)
	{
		float temp = inReal[y*filterWidth + x] * (((x + y) % 2 == 0) ? 1 : -1);
		temp = temp > 255 ? 255 : (temp < 0 ? 0 : temp);
		rImageData[y*sRowBytes + x * 3] = (int)temp;
		rImageData[y*sRowBytes + x * 3 + 1] = (int)temp;
		rImageData[y*sRowBytes + x * 3 + 2] = (int)temp;
	}

	delete inReal;
	delete inImage;
	delete outReal;
	delete outImage;
	
	UpdateAllViews(NULL);
}


void CImageProcessingDoc::OnGaussLowpassFiltering()
{
	// TODO: 在此添加命令处理程序代码
	if (m_sImage.IsNull())
	{
		return;
	}

	int sWidth = m_sImage.GetWidth();
	int sHeight = m_sImage.GetHeight();
    int sRowBytes = m_sImage.GetPitch();

	m_rImage.Destroy();
	if (!m_rImage.Create(sWidth, sHeight, m_sImage.GetBPP(), 0))
		return;

	BYTE *sImageData = (BYTE *)m_sImage.GetBits();
	BYTE *rImageData = (BYTE *)m_rImage.GetBits();

	int x;
	int y;
	CDialogGaussLowHighPassFiltering  mdlg;
	if (mdlg.DoModal() != IDOK)
		return;


	float *inReal;
	float *inImage;
	float *outReal;
	float *outImage;
	int filterHeight = sHeight << 1;
	int filterWidth = sWidth << 1;

	inReal = new float[filterHeight*filterWidth];
	inImage = new float[filterHeight*filterWidth];

	outReal = new float[filterHeight*filterWidth];
	outImage = new float[filterHeight*filterWidth];

	for (y = 0; y < filterHeight; y++)
	for (x = 0; x < filterWidth; x++)
	{
		if ((y < sHeight) && (x < sWidth))
		{
			int sgn = ((x + y) % 2 == 0) ? 1 : -1;
			inReal[y*filterWidth + x] = (float)(sgn*(0.114*sImageData[y*sRowBytes + 3 * x] + 0.587*sImageData[y*sRowBytes + 3 * x + 1] + 0.229*sImageData[y*sRowBytes + 3 * x + 2]));
		}
		else
			inReal[y*filterWidth + x] = 0;
		inImage[y*filterWidth + x] = 0;
	}

	FFT2DandIFFT2D(inReal, inImage, outReal, outImage, filterHeight, filterWidth, TRUE);
	
	double m_D;
	double m_D0 = mdlg.m_D0;
	m_D0 = 2 * m_D0 * m_D0;
	double m_H;

	//使用巴特沃斯(Butterworth)低通滤波器进行滤波
	for (y = 0; y < filterHeight; y++)
	for (x = 0; x < filterWidth; x++)
	{
		m_D = (x - filterWidth / 2) * (x - filterWidth / 2) + (y - filterHeight / 2) * (y - filterHeight / 2);
		m_H = exp(-m_D/m_D0);
		outReal[y*filterWidth + x]  = (float)(outReal[y*filterWidth + x] * m_H);
		outImage[y*filterWidth + x] = (float)(outImage[y*filterWidth + x] * m_H);
	}

	//对滤波后信号进行傅立叶反变换
	FFT2DandIFFT2D(outReal, outImage, inReal, inImage, filterHeight, filterWidth, FALSE);

	for (y = 0; y < sHeight; y++)
	for (x = 0; x < sWidth; x++)
	{
		float temp = inReal[y*filterWidth + x] * (((x + y) % 2 == 0) ? 1 : -1);
		temp = temp > 255 ? 255 : (temp < 0 ? 0 : temp);
		rImageData[y*sRowBytes + x * 3] = (int)temp;
		rImageData[y*sRowBytes + x * 3 + 1] = (int)temp;
		rImageData[y*sRowBytes + x * 3 + 2] = (int)temp;
	}

	delete inReal;
	delete inImage;
	delete outReal;
	delete outImage;

	UpdateAllViews(NULL);
}


void CImageProcessingDoc::OnGaussHighpassFiltering()
{
	// TODO: 在此添加命令处理程序代码
	if (m_sImage.IsNull())
	{
		return;
	}

	int sWidth = m_sImage.GetWidth();
	int sHeight = m_sImage.GetHeight();
    int sRowBytes = m_sImage.GetPitch();

	m_rImage.Destroy();
	if (!m_rImage.Create(sWidth, sHeight, m_sImage.GetBPP(), 0))
		return;

	BYTE *sImageData = (BYTE *)m_sImage.GetBits();
	BYTE *rImageData = (BYTE *)m_rImage.GetBits();

	int x;
	int y;
	CDialogGaussLowHighPassFiltering  mdlg;
	if (mdlg.DoModal() != IDOK)
		return;


	float *inReal;
	float *inImage;
	float *outReal;
	float *outImage;
	int filterHeight = sHeight << 1;
	int filterWidth = sWidth << 1;

	inReal = new float[filterHeight*filterWidth];
	inImage = new float[filterHeight*filterWidth];

	outReal = new float[filterHeight*filterWidth];
	outImage = new float[filterHeight*filterWidth];

	for (y = 0; y < filterHeight; y++)
	for (x = 0; x < filterWidth; x++)
	{
		if ((y < sHeight) && (x < sWidth))
		{
			int sgn = ((x + y) % 2 == 0) ? 1 : -1;
			inReal[y*filterWidth + x] = (float)(sgn*(0.114*sImageData[y*sRowBytes + 3 * x] + 0.587*sImageData[y*sRowBytes + 3 * x + 1] + 0.229*sImageData[y*sRowBytes + 3 * x + 2]));
		}
		else
			inReal[y*filterWidth + x] = 0;
		inImage[y*filterWidth + x] = 0;
	}

	FFT2DandIFFT2D(inReal, inImage, outReal, outImage, filterHeight, filterWidth, TRUE);
	
	double m_D;
	double m_D0 = mdlg.m_D0;
	m_D0 = 2 * m_D0 * m_D0;
	double m_H;

	//使用巴特沃斯(Butterworth)低通滤波器进行滤波
	for (y = 0; y < filterHeight; y++)
	for (x = 0; x < filterWidth; x++)
	{
		m_D = (x - filterWidth / 2) * (x - filterWidth / 2) + (y - filterHeight / 2) * (y - filterHeight / 2);
		m_H = 1 - exp(-m_D/m_D0);
		outReal[y*filterWidth + x]  = (float)(outReal[y*filterWidth + x] * m_H);
		outImage[y*filterWidth + x] = (float)(outImage[y*filterWidth + x] * m_H);
	}

	//对滤波后信号进行傅立叶反变换
	FFT2DandIFFT2D(outReal, outImage, inReal, inImage, filterHeight, filterWidth, FALSE);

	for (y = 0; y < sHeight; y++)
	for (x = 0; x < sWidth; x++)
	{
		float temp = inReal[y*filterWidth + x] * (((x + y) % 2 == 0) ? 1 : -1);
		temp = temp > 255 ? 255 : (temp < 0 ? 0 : temp);
		rImageData[y*sRowBytes + x * 3] = (int)temp;
		rImageData[y*sRowBytes + x * 3 + 1] = (int)temp;
		rImageData[y*sRowBytes + x * 3 + 2] = (int)temp;
	}

	delete inReal;
	delete inImage;
	delete outReal;
	delete outImage;

	UpdateAllViews(NULL);
}


void CImageProcessingDoc::OnLaplacianFiltering()
{
	// TODO: 在此添加命令处理程序代码
	if (m_sImage.IsNull())
		return;

	int sWidth = m_sImage.GetWidth();
	int sHeight = m_sImage.GetHeight();
    int sRowBytes = m_sImage.GetPitch();

	m_rImage.Destroy();
	if (!m_rImage.Create(sWidth, sHeight, m_sImage.GetBPP(), 0))
		return;

	BYTE *sImageData = (BYTE *)m_sImage.GetBits();
	BYTE *rImageData = (BYTE *)m_rImage.GetBits();

	int x;
	int y;


	float *inReal;
	float *inImage;
	float *outReal;
	float *outImage;
	int filterHeight = sHeight << 1;
	int filterWidth = sWidth << 1;

	inReal = new float[filterHeight*filterWidth];
	inImage = new float[filterHeight*filterWidth];

	outReal = new float[filterHeight*filterWidth];
	outImage = new float[filterHeight*filterWidth];

	for (y = 0; y < filterHeight; y++)
	for (x = 0; x < filterWidth; x++)
	{
		if ((y < sHeight) && (x < sWidth))
		{
			int sgn = ((x + y) % 2 == 0) ? 1 : -1;
			inReal[y*filterWidth + x] = (float)(sgn*(0.114*sImageData[y*sRowBytes + 3 * x] + 0.587*sImageData[y*sRowBytes + 3 * x + 1] + 0.229*sImageData[y*sRowBytes + 3 * x + 2]));
		}
		else
			inReal[y*filterWidth + x] = 0;
		inImage[y*filterWidth + x] = 0;
	}

	FFT2DandIFFT2D(inReal, inImage, outReal, outImage, filterHeight, filterWidth, TRUE);
	double m_D;
	double m_H;

	//使用巴特沃斯(Butterworth)低通滤波器进行滤波
	for (y = 0; y < filterHeight; y++)
	for (x = 0; x < filterWidth; x++)
	{
		m_D = (x - filterWidth / 2) * (x - filterWidth / 2) + (y - filterHeight / 2) * (y - filterHeight / 2);
		m_H = -m_D;
		outReal[y*filterWidth + x]   = (float)(outReal[y*filterWidth + x] * m_H);
		outImage[y*filterWidth + x]  = (float)(outImage[y*filterWidth + x] * m_H);
	}

	//对滤波后信号进行傅立叶反变换
	FFT2DandIFFT2D(outReal, outImage, inReal, inImage, filterHeight, filterWidth, FALSE);

	for (y = 0; y < sHeight; y++)
	for (x = 0; x < sWidth; x++)
	{
		float temp = inReal[y*filterWidth + x] * (((x + y) % 2 == 0) ? 1 : -1);
		temp = temp > 255 ? 255 : (temp < 0 ? 0 : temp);
		rImageData[y*sRowBytes + x * 3] = (int)temp;
		rImageData[y*sRowBytes + x * 3 + 1] = (int)temp;
		rImageData[y*sRowBytes + x * 3 + 2] = (int)temp;
	}

	delete inReal;
	delete inImage;
	delete outReal;
	delete outImage;

	UpdateAllViews(NULL);
}

void CImageProcessingDoc::OnInvertFilteringImageRestoration()
{
	// TODO: 在此添加命令处理程序代码
	if (m_sImage.IsNull())
		return;

	CDialogMotionBlurParameters mdlg;
	
	if (mdlg.DoModal() != IDOK)
		return;

	int sWidth = m_sImage.GetWidth();
	int sHeight = m_sImage.GetHeight();
    int sRowBytes = m_sImage.GetPitch();

	m_rImage.Destroy();
	if (!m_rImage.Create(sWidth, sHeight, m_sImage.GetBPP(), 0))
		return;

	BYTE *sImageData = (BYTE *)m_sImage.GetBits();
	BYTE *rImageData = (BYTE *)m_rImage.GetBits();

	int x;
	int y;
	int u;
	int v;

	float *inReal;
	float *inImage;
	float *outReal;
	float *outImage;


	inReal = new float[sHeight*sWidth];
	inImage = new float[sHeight*sWidth];

	outReal = new float[sHeight*sWidth];
	outImage = new float[sHeight*sWidth];

	for (y = 0; y < sHeight; y++)
	for (x = 0; x < sWidth; x++)
	{
		inReal[y*sWidth + x] = (float)(0.114*sImageData[y*sRowBytes + 3 * x] + 0.587*sImageData[y*sRowBytes + 3 * x + 1] + 0.229*sImageData[y*sRowBytes + 3 * x + 2]);
		inImage[y*sWidth + x] = 0;
	}

	FFT2DandIFFT2D(inReal, inImage, outReal, outImage, sHeight, sWidth, TRUE);
	

	float *m_Hr = new float[sHeight*sWidth];
	float *m_Hi = new float[sHeight*sWidth];
	double nA = 0.1;
	double nB = 0.1;
	double nT =  1;
	double alpha = 0.1;

	for (v = 0; v < sHeight; v++)
	for (u = 0; u < sWidth; u++)
	{
		if (u == 0 && v == 0)
		{
			m_Hr[v*sWidth  +u]   = (float)(nT*1.0);
			m_Hi[v*sWidth + u] = 0;
		}
		else
		{
			m_Hr[v*sWidth + u] = (float)( nT * sin(PI*(u*nA + v*nB)) * cos(PI*(u*nA + v*nB)) / ( PI*(u*nA + v*nB)));
			m_Hi[v*sWidth + u] = (float)(-nT * sin(PI*(u*nA + v*nB)) * sin(PI*(u*nA + v*nB)) / ( PI*(u*nA + v*nB)));
		}

	    double tempr = outReal[v*sWidth + u] * m_Hr[v*sWidth + u] - outImage[v*sWidth + u] * m_Hi[v*sWidth + u];
		double tempi = outReal[v*sWidth + u] * m_Hi[v*sWidth + u] + outImage[v*sWidth + u] * m_Hr[v*sWidth + u];
		outReal[v*sWidth + u]  = (float)tempr;
		outImage[v*sWidth + u] = (float)tempi;
	}

	//对滤波后信号进行傅立叶反变换
	FFT2DandIFFT2D(outReal, outImage, inReal, inImage, sHeight, sWidth, FALSE);

	double mmax;
	double mmin;
	mmax = mmin = inReal[0];
	
	for (y = 0; y < sHeight; y++)
	for (x = 0; x < sWidth; x++)
	{
		if (mmax < inReal[y*sWidth + x])
			mmax = inReal[y*sWidth + x];
		if (mmin > inReal[y*sWidth + x])
			mmin = inReal[y*sWidth + x];
	}
	mmax -= mmin;
		
	if (fabs(mmax) > 0.000000001)
	{
		for (y = 0; y < sHeight; y++)
	    for (x = 0; x < sWidth; x++)
	    {
		       float temp = (float)(255.0 * (inReal[y*sWidth + x] - mmin)/mmax) ;
		       rImageData[y*sRowBytes + x * 3]     = (int)temp;
		       rImageData[y*sRowBytes + x * 3 + 1] = (int)temp;
		       rImageData[y*sRowBytes + x * 3 + 2] = (int)temp;
	    }
	}

	delete inReal;
	delete inImage;
	delete outReal;
	delete outImage;
	UpdateAllViews(NULL);

/*

	int sWidth = m_sImage.GetWidth();
	int sHeight = m_sImage.GetHeight();
    int sRowBytes = m_sImage.GetPitch();

	m_rImage.Destroy();
	if (!m_rImage.Create(sWidth, sHeight, m_sImage.GetBPP(), 0))
		return;

	BYTE *sImageData = (BYTE *)m_sImage.GetBits();
	BYTE *rImageData = (BYTE *)m_rImage.GetBits();

	int x;
	int y;
	int u;
	int v;

	float *inReal;
	float *inImage;
	float *outReal;
	float *outImage;


	inReal = new float[sHeight*sWidth];
	inImage = new float[sHeight*sWidth];

	outReal = new float[sHeight*sWidth];
	outImage = new float[sHeight*sWidth];

	for (y = 0; y < sHeight; y++)
	for (x = 0; x < sWidth; x++)
	{
		inReal[y*sWidth + x] = (float)(0.114*sImageData[y*sRowBytes + 3 * x] + 0.587*sImageData[y*sRowBytes + 3 * x + 1] + 0.229*sImageData[y*sRowBytes + 3 * x + 2]);
		inImage[y*sWidth + x] = 0;
	}

	FFT2DandIFFT2D(inReal, inImage, outReal, outImage, sHeight, sWidth, TRUE);
	

	float *m_Hr = new float[sHeight*sWidth];
	float *m_Hi = new float[sHeight*sWidth];
	double nA = 10;
	double nT =  1;

	for (v = 0; v < sHeight; v++)
	for (u = 0; u < sWidth; u++)
	{
		if (u == 0)
		{
			m_Hr[v*sWidth  +u]   = 0;
			m_Hi[v*sWidth + u] = 0;
		}
		else
		{
			m_Hr[v*sWidth + u] =  nT * sin(PI*u*nA) * cos(PI*u*nA) / ( PI*u*nA);
			m_Hi[v*sWidth + u] = -nT * sin(PI*u*nA) * sin(PI*u*nA) / ( PI*u*nA) ;
		}

	    double tempr = outReal[v*sWidth + u] * m_Hr[v*sWidth + u] - outImage[v*sWidth + u] * m_Hi[v*sWidth + u];
		double tempi = outReal[v*sWidth + u] * m_Hi[v*sWidth + u] + outImage[v*sWidth + u] * m_Hr[v*sWidth + u];
		outReal[v*sWidth + u]  = tempr;
		outImage[v*sWidth + u] = tempi;
	}


	//对滤波后信号进行傅立叶反变换
	FFT2DandIFFT2D(outReal, outImage, inReal, inImage, sHeight, sWidth, FALSE);

	double mmax;
	double mmin;
	mmax = mmin = inReal[0];
	
	for (y = 0; y < sHeight; y++)
	for (x = 0; x < sWidth; x++)
	{
		if (mmax < inReal[y*sWidth + x])
			mmax = inReal[y*sWidth + x];
		if (mmin > inReal[y*sWidth + x])
			mmin = inReal[y*sWidth + x];
	}
	mmax -= mmin;
		
	if (fabs(mmax) > 0.000000001)
	{
		for (y = 0; y < sHeight; y++)
	    for (x = 0; x < sWidth; x++)
	    {
		       float temp = 255.0 * (inReal[y*sWidth + x] - mmin)/mmax ;
			  
		       rImageData[y*sRowBytes + x * 3]     = (int)temp;
		       rImageData[y*sRowBytes + x * 3 + 1] = (int)temp;
		       rImageData[y*sRowBytes + x * 3 + 2] = (int)temp;
	    }
	}
 


	delete inReal;
	delete inImage;
	delete outReal;
	delete outImage;
*/


}

void CImageProcessingDoc::OnImageHoriMotionBlur()
{
	// TODO: 在此添加命令处理程序代码
	if (m_sImage.IsNull())
		return;

	CDialogMotionBlurParameters mdlg;
	mdlg.m_bOnlyHoriMotion = true;
	if (mdlg.DoModal() != IDOK)
		return;

	int sWidth = m_sImage.GetWidth();
	int sHeight = m_sImage.GetHeight();
    int sRowBytes = m_sImage.GetPitch();

	m_rImage.Destroy();
	if (!m_rImage.Create(sWidth, sHeight, m_sImage.GetBPP(), 0))
		return;

	BYTE *sImageData = (BYTE *)m_sImage.GetBits();
	BYTE *rImageData = (BYTE *)m_rImage.GetBits();

	int x;
	int y;
	int i;
	int nt;
	int temp;
	int count;
	//总的运动时间1s
	int nT = 1;
	// x方向总的运动象素点
	int nA = mdlg.m_Xmotion;
	if (nA == 0) 
		return;
	for (i = 0; i < 3; i++)
	{ 
		for (y = 0; y < sHeight; y++)
	    for (x = 0; x < sWidth; x++)
	    {
			 //x方向累加
			 temp = 0;
			 count = 0;
			 // 象素点的象素值积累
			 for (nt = 0; nt < nA; nt++)
			 {
			     // 累加
				 if (x - nt >= 0 && x - nt < sWidth)
				 {
					 count++;
					 temp = temp + sImageData[y*sRowBytes + (x - nt) * 3 + i];
				 }
			  }

			  temp = temp/count;

			  // 使得temp的取值符合取值范围
			  temp = (temp > 255) ? 255 : ((temp < 0) ? 0 : temp);
			  rImageData[y*sRowBytes + x * 3 + i] = temp;
	     }
	}

    UpdateAllViews(NULL);
}


void CImageProcessingDoc::OnImageHoriMotionBlurRestore()
{
	// TODO: 在此添加命令处理程序代码
	if (m_sImage.IsNull())
		return;
	CDialogMotionBlurParameters mdlg;
	mdlg.m_bRestoration = true;
	if (mdlg.DoModal() != IDOK)
		return;

	int sWidth = m_sImage.GetWidth();
	int sHeight = m_sImage.GetHeight();
    int sRowBytes = m_sImage.GetPitch();

	m_rImage.Destroy();
	if (!m_rImage.Create(sWidth, sHeight, m_sImage.GetBPP(), 0))
		return;

	BYTE *sImageData = (BYTE *)m_sImage.GetBits();
	BYTE *rImageData = (BYTE *)m_rImage.GetBits();


	int x;
	int y;
	int i;
	int z;
	int k;
	int n;

	double temp;

	// 1秒内x方向总的运动象素数
	int a = mdlg.m_Xmotion;

	//原始图像平均灰度
	int A = mdlg.m_aver_grey;

	//用m_a等分区间[0,sWidth]的小区间个数
	int N = sWidth / a;
	double *phi = new double[a];  //φ(0,y),φ(1,y),...,φ(a-1,y)

	double * edge = new double[sHeight*sWidth];

	for (i = 0; i < 3; i++)  //颜色分量
	{ 
		//计算图像水平方向导数
		for (y = 0; y < sHeight; y++)
		for (x = 0; x < sWidth; x++)
		{
			if (x == 0)
				edge[y*sWidth + x] = 0;
			else
				edge[y*sWidth + x] = sImageData[y*sRowBytes + 3 * x + i] - sImageData[y*sRowBytes + 3 * (x - 1) + i];
		}

		for (y = 0; y < sHeight; y++)
		{
			//计算//φ(0,y),φ(1,y),...,φ(a-1,y)
			for (z = 0;  z < a; z++)
			{
				phi[z] = 0;
				for (n = 0; n < N; n++)
				for (k = 0; k <= n; k++)
				{
					phi[z] += edge[y*sWidth + z + k * a];
				}
				phi[z] *= a;
				phi[z] /= N;
			}

			for (x = 0; x < sWidth; x++)
			{
				n = x / a;
				z = x % a;
				temp = 0;
				for (k = 0; k < n; k++)
					temp += edge[y*sWidth + z + k*a];
				temp *= a;
				temp += A - phi[z];
				if (temp > 255)
					temp = 255;
				else if (temp < 0)
					temp = 0;
				rImageData[y*sRowBytes + 3 * x + i] =(BYTE) temp;
			}
		}
	}

    UpdateAllViews(NULL);
}


void CImageProcessingDoc::OnMotionBlur()
{
	// TODO: 在此添加命令处理程序代码
	if (m_sImage.IsNull())
		return;

	CDialogMotionBlurParameters mdlg;
	mdlg.m_bOnlyHoriMotion = true;
	if (mdlg.DoModal() != IDOK)
		return;

	int sWidth = m_sImage.GetWidth();
	int sHeight = m_sImage.GetHeight();
    int sRowBytes = m_sImage.GetPitch();

	m_rImage.Destroy();
	if (!m_rImage.Create(sWidth, sHeight, m_sImage.GetBPP(), 0))
		return;

	BYTE *sImageData = (BYTE *)m_sImage.GetBits();
	BYTE *rImageData = (BYTE *)m_rImage.GetBits();

	int x;
	int y;
	int i;
	int nt;
	int temp;
	int count;
	//总的运动时间1s
	int nT = 1;
	// x方向总的运动象素点
	int nA = mdlg.m_Xmotion;
	if (nA == 0) 
		return;
	for (i = 0; i < 3; i++)
	{ 
		for (y = 0; y < sHeight; y++)
	    for (x = 0; x < sWidth; x++)
	    {
			 //x方向累加
			 temp = 0;
			 count = 0;
			 // 象素点的象素值积累
			 for (nt = 0; nt < nA; nt++)
			 {
			     // 累加
				 if (x - nt >= 0 && x - nt < sWidth)
				 {
					 count++;
					 temp = temp + sImageData[y*sRowBytes + (x - nt) * 3 + i];
				 }
			  }

			  temp = temp/count;

			  // 使得temp的取值符合取值范围
			  temp = (temp > 255) ? 255 : ((temp < 0) ? 0 : temp);
			  rImageData[y*sRowBytes + x * 3 + i] = temp;
	     }
	}

    UpdateAllViews(NULL);
}


void CImageProcessingDoc::OnLinesDetect()
{
	// TODO: 在此添加命令处理程序代码
	if (m_sImage.IsNull())
		return;

	int sWidth = m_sImage.GetWidth();
	int sHeight = m_sImage.GetHeight();
    int sRowBytes = m_sImage.GetPitch();

	m_rImage.Destroy();
	if (!m_rImage.Create(sWidth, sHeight, m_sImage.GetBPP(), 0))
		return;

	BYTE *sImageData = (BYTE *)m_sImage.GetBits();
	BYTE *rImageData = (BYTE *)m_rImage.GetBits();
	

	int *imgData = new int[sHeight*sWidth];   //存放灰度图像
	int *imgedge = new int[sHeight*sWidth];   //存放边缘图像
	int nMaxP = (int)sqrt(sHeight*sHeight + sWidth*sWidth);  //Hough变换最大极坐标值
	int nMaxThita = 180;     //Hough变换最大角度值 

	int *pHoughTrans = new int[nMaxP*nMaxThita];   //存放HoughB变换空间图像
	

	int x;
	int y;
	int thita;
	int mp;

	for (y = 0; y < sHeight; y++)
	for (x = 0; x < sWidth; x++)
	{  //将彩色图像转换为灰度图像存放在二维数组imgData中
		imgData[y*sWidth + x] =	(int)(0.114*sImageData[y*sRowBytes + 3 * x] + 0.587*sImageData[y*sRowBytes + 3 * x + 1] + 0.299*sImageData[y*sRowBytes + 3 * x + 2]);
	}

	memset(imgedge, (BYTE)0, sHeight*sWidth*sizeof(int));  //边缘图像清0
	
	for (y = 1; y < sHeight-1; y++)
	for (x = 1; x < sWidth-1; x++)
	{     //Sobel算子计算图像边缘
		int dx = imgData[(y - 1)*sWidth + x - 1] - imgData[(y + 1)*sWidth + x - 1]
			+ 2*( imgData[(y - 1)*sWidth + x] - imgData[(y + 1)*sWidth + x])
			+ imgData[(y - 1)*sWidth + x + 1] - imgData[(y + 1)*sWidth + x + 1];
		int dy = imgData[(y - 1)*sWidth + x - 1] - imgData[(y - 1)*sWidth + x + 1]
			+ 2*(imgData[(y )*sWidth + x-1] - imgData[(y )*sWidth + x+1])
			+ imgData[(y + 1)*sWidth + x - 1] - imgData[(y + 1)*sWidth + x + 1];
		imgedge[y*sWidth + x] = (int)sqrt(dx*dx+dy*dy);
    } 

	//计算边缘图像灰度总和
	int edgesum = 0;
	for (y = 1; y < sHeight-1; y++)
	for (x = 1; x < sWidth-1; x++)
	{   
		edgesum += imgedge[y*sWidth + x];
    }
	//计算边缘图像灰度平均值
	edgesum = edgesum / (sHeight*sWidth);

	for (y = 1; y < sHeight-1; y++)
	for (x = 1; x < sWidth-1; x++)
	{   //灰度图像中大于灰度平均者取255，否则取0值进行二值化
		if (imgedge[y*sWidth + x]>edgesum)
			imgedge[y*sWidth + x] = 255;
		else
			imgedge[y*sWidth + x] = 0;
    }

	for (mp = 0; mp < nMaxP; mp++)
	for (thita = 0; thita < nMaxThita; thita++)
	{   //Hough变换域图像清0
		pHoughTrans[mp*nMaxThita + thita] = 0;
	}
   
	for (y = 0; y < sHeight; y++)
	for (x = 0; x < sWidth; x++)
	{   //将原始图像复制到目标图像
		rImageData[y*sRowBytes + 3 * x] = sImageData[y*sRowBytes + 3 * x];
		rImageData[y*sRowBytes + 3 * x + 1] = sImageData[y*sRowBytes + 3 * x + 1];
		rImageData[y*sRowBytes + 3 * x + 2] = sImageData[y*sRowBytes + 3 * x + 2];
	}

	//进行Hough变换，计算Hough变换域图像，存放在数组pHoughTrans中
	for (y = 0; y < sHeight; y++)
	for (x = 0; x < sWidth; x++)
	{
		if (imgedge[y*sWidth + x] == 255)    //如果是源图像中边界点
		{
			for (thita = 0; thita < nMaxThita; thita++)
			{
				mp = (int)(x*cos(thita *  PI / 180.0) + y*sin(thita * PI / 180.0));
				//变换域的对应点上加1
				mp = (mp + nMaxP) / 2;
				pHoughTrans[mp*nMaxThita + thita]++;
			}
		}
	}

	//查找Hough变换域图像中的最大者及其极坐标距离和角度（注意：最大者就是原图像中最长的直线）
	int maxline = pHoughTrans[0];
	int maxmp = 0;
	int maxthita = 0;
	for (mp = 0; mp < nMaxP; mp++)
	for (thita = 0; thita < nMaxThita; thita++)
	{
		if (pHoughTrans[mp*nMaxThita + thita]>maxline)
		{
			maxline = pHoughTrans[mp*nMaxThita + thita];
			maxmp = mp;
			maxthita = thita;
		}
	}
 
	for (y = 1; y<sHeight; y++) //目标图像中用蓝色显示求出的最长的直线
	for (x = 1; x<sWidth; x++)
	{
		if (imgedge[y*sWidth + x] == 255)
		{
			mp = (int)(x*cos(PI*maxthita / 180) + y*sin(PI*maxthita / 180));//pi=3.1415926
			mp = (int)(mp / 2 + nMaxP / 2);   //mp为原图对角线距离
			if (mp == maxmp) //存储图像数据 放在temp数组中
			{
				rImageData[y*sRowBytes + 3 * x] = 255;
				rImageData[y*sRowBytes + 3 * x + 1] = 0;
				rImageData[y*sRowBytes + 3 * x + 2] = 0;
			}
		}
	}

	delete imgData;
	delete imgedge;
	delete pHoughTrans;
    UpdateAllViews(NULL);
}


void CImageProcessingDoc::OnCirclesDetection()
{
	// TODO: 在此添加命令处理程序代码

	if (m_sImage.IsNull())
		return;

	int sWidth = m_sImage.GetWidth();
	int sHeight = m_sImage.GetHeight();
    int sRowBytes = m_sImage.GetPitch();

	m_rImage.Destroy();
	if (!m_rImage.Create(sWidth, sHeight, m_sImage.GetBPP(), 0))
		return;

	BYTE *sImageData = (BYTE *)m_sImage.GetBits();
	BYTE *rImageData = (BYTE *)m_rImage.GetBits();
	

	int *imgData = new int[sHeight*sWidth];   //存放灰度图像
	int *imgedge = new int[sHeight*sWidth];   //存放边缘图像

	int x;
	int y;
	int r;
	int theta;
	int ma;
	int mb;
	
	for (y = 0; y < sHeight; y++)
	for (x = 0; x < sWidth; x++)
	{  //将彩色图像转换为灰度图像存放在二维数组imgData中
		imgData[y*sWidth + x] =	(int)(0.114*sImageData[y*sRowBytes + 3 * x] + 0.587*sImageData[y*sRowBytes + 3 * x + 1] + 0.299*sImageData[y*sRowBytes + 3 * x + 2]);
	}

	memset(imgedge, (BYTE)0, sHeight*sWidth*sizeof(int));  //边缘图像清0
	
	for (y = 1; y < sHeight-1; y++)
	for (x = 1; x < sWidth-1; x++)
	{     //Sobel算子计算图像边缘
		int dx = imgData[(y - 1)*sWidth + x - 1] - imgData[(y + 1)*sWidth + x - 1]
			+ 2*( imgData[(y - 1)*sWidth + x] - imgData[(y + 1)*sWidth + x])
			+ imgData[(y - 1)*sWidth + x + 1] - imgData[(y + 1)*sWidth + x + 1];
		int dy = imgData[(y - 1)*sWidth + x - 1] - imgData[(y - 1)*sWidth + x + 1]
			+ 2*(imgData[(y )*sWidth + x-1] - imgData[(y )*sWidth + x+1])
			+ imgData[(y + 1)*sWidth + x - 1] - imgData[(y + 1)*sWidth + x + 1];
		imgedge[y*sWidth + x] = (int)sqrt(dx*dx+dy*dy);
    } 

	//计算边缘图像灰度总和
	int edgesum = 0;
	for (y = 1; y < sHeight-1; y++)
	for (x = 1; x < sWidth-1; x++)
	{   
		edgesum += imgedge[y*sWidth + x];
    }
	//计算边缘图像灰度平均值
	edgesum = edgesum / (sHeight*sWidth);

	for (y = 1; y < sHeight-1; y++)
	for (x = 1; x < sWidth-1; x++)
	{   //灰度图像中大于灰度平均者取255，否则取0值进行二值化
		if (imgedge[y*sWidth + x]>edgesum)
			imgedge[y*sWidth + x] = 255;
		else
			imgedge[y*sWidth + x] = 0;
    }

	int nMaxThita = 360;     //Hough变换最大角度值 
	int nMaxRadius = sHeight > sWidth ? sHeight / 2 : sWidth / 2; //最大半径

	int *pHoughTrans = new int[nMaxRadius*sHeight*sWidth];   //存放HoughB变换空间图像



	for (r = 0; r < nMaxRadius;r++)
	for (y = 0; y < sHeight; y++)
	for (x = 0; x < sWidth; x++)
	{   //Hough变换域图像清0
		pHoughTrans[r*sHeight*sWidth + y*sWidth + x] = 0;
	}
   
	for (y = 0; y < sHeight; y++)
	for (x = 0; x < sWidth; x++)
	{   //将原始图像复制到目标图像
		rImageData[y*sRowBytes + 3 * x] = sImageData[y*sRowBytes + 3 * x];
		rImageData[y*sRowBytes + 3 * x + 1] = sImageData[y*sRowBytes + 3 * x + 1];
		rImageData[y*sRowBytes + 3 * x + 2] = sImageData[y*sRowBytes + 3 * x + 2];
	}

	//进行Hough变换，计算Hough变换域图像，存放在数组pHoughTrans中
	for (y = 0; y < sHeight; y++)
	for (x = 0; x < sWidth; x++)
	{
		if (imgedge[y*sWidth + x] == 255)    //如果是源图像中边界点
		{
			for (r = 0; r < nMaxRadius; r++)
			for (theta = 0; theta < nMaxThita; theta++)
			{
				ma = (int)(x - r*cos(theta*PI / 180));
				mb = (int)(y - r*sin(theta*PI / 180));
				//变换域的对应点上加1
				if(ma>=0 && ma<sWidth && mb>=0 && mb<sHeight)
					pHoughTrans[r*sHeight*sWidth + mb*sWidth + ma]++;
			}
		}
	}

	//查找Hough变换域图像中的最大者及其极坐标距离和角度（注意：最大者就是原图像中最长的直线）
	int maxcircle = pHoughTrans[0];
	int maxma=  0;
	int maxmb = 0;
	int maxr = 0;
	for (r = 0; r < nMaxRadius;r++)
	for (mb = 0; mb < sHeight; mb++)
	for (ma = 0; ma < sWidth; ma++)
	{
		if (pHoughTrans[r*sHeight*sWidth + mb*sWidth + ma]>maxcircle)
		{
			maxcircle = pHoughTrans[r*sHeight*sWidth + mb*sWidth + ma];
			maxma = ma;
			maxmb = mb;
			maxr = r;
		}
	}
 

	delete imgData;
	delete imgedge;
	delete pHoughTrans;
    UpdateAllViews(NULL);	
}

