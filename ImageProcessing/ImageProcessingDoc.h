
// ImageProcessingDoc.h : CImageProcessingDoc 类的接口
//


#pragma once
#include <complex>
using namespace std;

typedef struct medianlink
{
	BYTE data;
	medianlink * pNext;
} MEDIANLINK;

typedef MEDIANLINK * LPMEDIANLINK;


class CImageProcessingDoc : public CDocument
{
protected: // 仅从序列化创建
	CImageProcessingDoc();
	DECLARE_DYNCREATE(CImageProcessingDoc)

// 特性
public:
	CImage  m_sImage;         //原始图像
	CImage  m_rImage;         //处理后的图像
// 操作
public:

typedef struct BreakPointRakerRatioLink
{
	CPoint m_pt;
	double m_k;
	struct BreakPointRakerRatioLink *pNext;
} BREAKPOINTRAKERATIOLINK;


// 重写
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// 实现
public:
	virtual ~CImageProcessingDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// 用于为搜索处理程序设置搜索内容的 Helper 函数
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
public:
	void ImageZoomExtend(LPBYTE pSrcData, LPBYTE pDstData, int nHeight, int nWidth, int nYRadius, int nXRadius);
	void CreatMedianLink(LPMEDIANLINK &plink, LPBYTE pData, int n);
	void CreatMedianLink(LPMEDIANLINK &psrclink, LPMEDIANLINK &pdstlink);
	void DeleteElment(LPMEDIANLINK &plink, BYTE nbyte);
	void InsertSortElment(LPMEDIANLINK &plink, BYTE nbyte);
	BYTE GetElment(LPMEDIANLINK plink, int n);
	void SortMedianLink(LPMEDIANLINK &plink);
	void ClearMedianLink(LPMEDIANLINK &plink);
	void BubbleSort(BYTE * pData, int Num);
	BYTE Maxinum(BYTE * pData, int Num);
	BYTE Mininum(BYTE * pData, int Num);
	void GetGreenBitsFromImage(CImage *mImage, BYTE * pAreaBits);
	void GetRedBitsFromImage(CImage *mImage, BYTE * pAreaBits);
	void GetBlueBitsFromImage(CImage *mImage, BYTE * pAreaBits);
	void GetGreyBitsFromImage(CImage *mImage, BYTE * pAreaBits);
	void CopyAreaRGBFromImgBits(CImage *mImage, BYTE * pAreaBits, int x, int y, int m, int n);
	void CopyAreaBlueFromImgBits(CImage *mImage, BYTE * pAreaBits, int x, int y, int m, int n);
	void CopyAreaGreenFromImgBits(CImage *mImage, BYTE * pAreaBits, int x, int y, int m, int n);
	void CopyAreaRedFromImgBits(CImage *mImage, BYTE * pAreaBits, int x, int y, int m, int n);
	void MeanOperator(CImage * pSrcImage, CImage * pDstImage, int m, int n);
	void GaussOperator(CImage * pSrcImage, CImage * pDstImage, int m, int n, double sigma);
	void MedianOperator(CImage * pSrcImage, CImage * pDstImage, int m, int n);
	void MaxinumOperator(CImage * pSrcImage, CImage * pDstImage, int m, int n);
	void MininumOperator(CImage * pSrcImage, CImage * pDstImage, int m, int n);
	void MiddleOperator(CImage * pSrcImage, CImage * pDstImage, int m, int n);
	void GradsOperator(CImage * pSrcImage, CImage * pDstImage, BOOL bCalibration, BOOL bfiltering);
	void LaplaceOperator(CImage * pSrcImage, CImage * pDstImage, int laplacetype, BOOL bCalibration, BOOL bfiltering);
	void RobertsOperator(CImage * pSrcImage, CImage * pDstImage, BOOL calibration, BOOL bfiltering);
	void SobelOperator(CImage * pSrcImage, CImage * pDstImage, BOOL bCalibration, BOOL bfiltering);
	void PrewittOperator(CImage * pSrcImage, CImage * pDstImage, BOOL bCalibration, BOOL bfiltering);
	void IsotropicOperator(CImage * pSrcImage, CImage * pDstImage, BOOL bCalibration, BOOL bfiltering);
	void KirschOperator(CImage * pSrcImage, CImage * pDstImage, int Kr, BOOL bCalibration);
	void CreatGauss(double sigma, double** pdKernel, int* pnWidowSize);
	void GaussianSmooth(int nHeight,int nWidth, LPBYTE pGray, LPBYTE pResult, double sigma);
	void Grad(int nHeight,int nWidth, LPBYTE pGray, int* pGradX, int* pGradY, int* pMag);
	void NonmaxSuppress(int* pMag, int* pGradX, int* pGradY, int nHeight,int nWidth,LPBYTE pNSRst);
	void EstimateThreshold(int* pMag, int nHeight,int nWidth, int* pThrHigh, int* pThrLow,LPBYTE pGray, double dRatHigh, double dRatLow);
	void Hysteresis(int* pMag, int nHeight,int nWidth, double dRatLow, double dRatHigh,LPBYTE pResult);
	void TraceEdge(int y, int x, int nThrLow, LPBYTE pResult, int* pMag,int nHeight,int nWidth);
	void CannyOperator(LPBYTE pGray, int nHeight, int nWidth, double sigma, double dRatLow, double dRatHigh, LPBYTE pResult);
	void FunMirrorTransform(CImage * sImage, CImage * rImage, double degree, CPoint pt);
	void HistogramEqualization(int * pData, int nHeight, int nWidth);
	void FFT1DandIFFT1D(float * Tr, float * Ti, int N, bool bFFTorIFFT);
	void FFT2DandIFFT2D(float * inDataReal, float * inDataImage, float * outDataReal, float * outDataImage, int M, int N, bool bFFTorIFFT);
	void DFT1DandIDFT1D(float * Tr, float * Ti, int N, bool bDFTorIDFT);
	void DFT2DandIDFT2D(float * inDataReal, float * inDataImage, float * outDataReal, float * outDataImage, int M, int N, bool bDFTorIDFT);
	void DCT1DandIDCT1D(float *pfF, int N, bool bDctIDct);
	void DCT2DandIDCT2D(float *inData, float *outData, int M, int N, BOOL bDCTorIDCT);
	afx_msg void OnFileOpen();
	afx_msg void OnColortogrey();
	afx_msg void OnRgbRed();
	afx_msg void OnRgbGreen();
	afx_msg void OnRgbBlue();
	afx_msg void OnHsvHue();
	afx_msg void OnHsvSaturation();
	afx_msg void OnHsvIntensity();
	afx_msg void OnYcbcrY();
	afx_msg void OnYcbcrCb();
	afx_msg void OnYcbcrCr();
	afx_msg void OnNearestInterpolationScaling();
	afx_msg void OnBilinearInterpolationScaling();
	afx_msg void OnColorInversion();
	afx_msg void OnFileSaveAs();
	afx_msg void OnHistogramequalization();
	afx_msg void OnLogTransform();
	afx_msg void OnPowerTransform();
	afx_msg void OnLinearform();
	afx_msg void OnBitPlane();
	afx_msg void OnGreyhistogram();
	afx_msg void OnImageAdd();
	afx_msg void OnImageSub();
	afx_msg void OnImageAnd();
	afx_msg void OnImageOr();
	afx_msg void OnImageMul();
	afx_msg void OnImageDiv();
	afx_msg void OnImageRotation();
	afx_msg void OnImageMagnifier();
	afx_msg void OnLocalHistogramEqualization();
	afx_msg void OnHistogramStatistics();
	afx_msg void OnHoriConcave();
	afx_msg void OnHoriConvex();
	afx_msg void OnLaddertypeDeformation();
	afx_msg void OnTriangleDeformation();
	afx_msg void OnStypeDeformation();
	afx_msg void OnCorrugationDeformation();
	afx_msg void OnMagicMirrorTransform();
	afx_msg void OnGeneralAffineTransform();
	afx_msg void OnSmoothingSpatiaFiltering();
	afx_msg void OnSharpeningSpatialFiltering();
	afx_msg void OnImageFastFourierTransform();
	afx_msg void OnImageFastFourierTransformCenter();
	afx_msg void OnDctTransform();
	afx_msg void OnIdeaLowPassFiltering();
	afx_msg void OnIdeaHighPassFiltering();
	afx_msg void OnFourierTransformApplication();
	afx_msg void OnButterworthLowpassFiltering();
	afx_msg void OnButterworthHighpassFiltering();
	afx_msg void OnNotchFiltering();
	afx_msg void OnGaussLowpassFiltering();
	afx_msg void OnGaussHighpassFiltering();
	afx_msg void OnLaplacianFiltering();
	afx_msg void OnInvertFilteringImageRestoration();
	afx_msg void OnImageHoriMotionBlur();
	afx_msg void OnImageHoriMotionBlurRestore();
	afx_msg void OnMotionBlur();
	afx_msg void OnLinesDetect();
	afx_msg void OnCirclesDetection();
	double generateGaussianNoise(double mu, double sigma);
	afx_msg void OnImageNoisePollution();
	void ImagePeppperNoisePollution(CImage * pImg, double pa, double pb);
	void ImageUniformNoisePollution(CImage * pImg, double a, double b);
	void ImageGauessNoisePollution(CImage * pImg, double mu, double sigma, double k);
};
