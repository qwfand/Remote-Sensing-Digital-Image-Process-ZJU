
// 3170106249SX15Dlg.cpp : implementation file
//

#include "stdafx.h"
#include "3170106249SX15.h"
#include "3170106249SX15Dlg.h"
#include "afxdialogex.h"
#include<iostream>
#include <time.h>
#include<fstream>

#define DataType unsigned long 


#include"gdal/include/gdal_priv.h"
#include"gdal/include/gdalwarper.h"
#include"gdal/include/ogrsf_frmts.h"
//#include"gadl/include/cpl_conv.h"
#pragma comment(lib,"gdal/gdal_i.lib")

using namespace std;


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CMy3170106249SX15Dlg dialog



CMy3170106249SX15Dlg::CMy3170106249SX15Dlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MY3170106249SX15_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMy3170106249SX15Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMy3170106249SX15Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(K_MEAN, &CMy3170106249SX15Dlg::OnBnClickedMean)
	ON_BN_CLICKED(BT_INFILE, &CMy3170106249SX15Dlg::OnBnClickedInfile)
	ON_BN_CLICKED(BT_OUTFILE, &CMy3170106249SX15Dlg::OnBnClickedOutfile)
END_MESSAGE_MAP()


// CMy3170106249SX15Dlg message handlers

BOOL CMy3170106249SX15Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	//初始化gdal
	GDALAllRegister();
	CPLSetConfigOption("GDAL_FILENAME_IS_UTF8", "NO");//使GDAL不默认utf8，以支持中文路径
	
	if (!AllocConsole()) return FALSE; //控制台调试窗口开启

	freopen("CONOUT$", "w", stdout);//开启中文控制台输出支持
	
	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CMy3170106249SX15Dlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CMy3170106249SX15Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CMy3170106249SX15Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMy3170106249SX15Dlg::OnBnClickedInfile()
{
	// TODO: Add your control notification handler code here
	//定义GDAL操作句
	//获取要打开的图像文件路径
	CFileDialog Dlg(TRUE);
	
	//CString strFileName;
	if (Dlg.DoModal() == IDOK)
		imgInputPath = Dlg.GetPathName();
	
}


void CMy3170106249SX15Dlg::OnBnClickedOutfile()
{
	// TODO: Add your control notification handler code here
	CFileDialog Dlg(TRUE);
	CString strFileName;

	if (Dlg.DoModal() == IDOK)
		strFileName = Dlg.GetPathName();
	imgOutputPath = strFileName;
}



void CMy3170106249SX15Dlg::OnBnClickedMean()
{
	
	int numOfClass=6;
	CString str;
	//获取输入的数值
	this->GetDlgItemTextA(NUM_CLASS, str);//str赋值
	numOfClass = atoi(str);

	//numOfClass = 12;
	cout << "the input image path:" << imgInputPath << endl;
	cout << "the output imge path:" << imgOutputPath << endl;
	cout << "the number of class:" << numOfClass << endl;
	GDALDataset *poDataset = (GDALDataset*)GDALOpen(imgInputPath, GA_ReadOnly);
	if (!poDataset)
	{
		MessageBox("open image err");
		return;
	}

	//获取并输出图像信息
	int iCols = poDataset->GetRasterXSize();
	int iRows = poDataset->GetRasterYSize();
	int nBands = poDataset->GetRasterCount();
	GDALRasterBand *poBand = poDataset->GetRasterBand(1);
	GDALDataType DataType1 = poBand->GetRasterDataType();

	unsigned long p[100][4];  //
	double sum[100][4];
	int count[100];
	double J=0;

	//GByte out2[1525][2371] ;//tif 输出

	GByte * out3 = (GByte*)malloc(sizeof(GByte)*iRows*iCols);                          // store the classification result
	DataType *pabyScanline =(DataType *)(malloc(nBands * iCols*iRows*sizeof(DataType)));//stor imge data

	//read date from file to memmory
	poDataset->RasterIO(GF_Read,
		 0, 0, 
		iCols, iRows, 
		pabyScanline, 
		iCols, iRows, GDT_UInt32,
		nBands, 0,
		nBands * sizeof(DataType), nBands*iCols * sizeof(DataType), 
		sizeof(DataType));
	
	
	/*
	for (int iLine = 0; iLine < iRows; iLine++)
	{
		for (int iBand = 0; iBand < nBands; iBand++)
		{
			GDALRasterBand * poBand = poDataset->GetRasterBand(iBand + 1);
			const CPLErr eErr =
				poBand->RasterIO(GF_Read, 0, iLine, iCols, 1,
					pabyScanline + iBand, iCols, 1, GDT_UInt32,
					nBands* sizeof(unsigned long), nBands * iCols*sizeof(unsigned long));
			// TODO: Handle error.
		}
	}*/
		
	//初始化聚类中心
	// position   coordinate  (k,l) 
	srand((unsigned)time(NULL));
	for (int j = 0; j < numOfClass; j++)
	{
		int k,l;
		l = rand() % iRows + 1;
		k = rand() % iCols + 1;
		for (int x = 0; x < nBands; x++)
		{
			p[j][x] = pabyScanline[l * iCols*nBands + k * nBands + x];// pMemDataB[x][l][k]; 
		}
		//out2[l][k] = (GByte)j;//初始的类赋值
		out3[l*iCols + k] = j;   // position (l,k) is assigned to class j 

	}
	int time;
	for ( time = 0; time < 10 ; time++) {
		for (int i = 0; i < numOfClass; i++)
		{
			count[i] = 0;
			sum[i][0] = sum[i][1] = sum[i][2] = sum[i][3] = 0;//
		}

		double tmpJ = 0;

		for (int i = 0; i < iRows; i++)//x
		{
			for (int j = 0; j < iCols; j++)//y
			{
				//归类  取出（i，j）j行i列处的数据
				unsigned long sour[4] = { pabyScanline[0 + i * iCols*nBands + j * nBands],
										   pabyScanline[1 + i * iCols*nBands + j * nBands],
											pabyScanline[2 + i * iCols*nBands + j * nBands],
											pabyScanline[3 + i * iCols*nBands + j * nBands] };
				int Kind = 0;//类别
				double minDis = dis(sour, p[0],4);  //the distance between sour and p[0]
				for (int k = 1; k < numOfClass; k++)//(i,j)处的类别为Kind
				{
					double tmp = dis(sour, p[k],4);
					if (tmp < minDis)
					{
						minDis = tmp;
						Kind = k;
					}
				}

				tmpJ += minDis;
				
				
				//out2[i][j] =(GByte) Kind;
				out3[i*iCols + j] = Kind;
				for (int y = 0; y < 4; y++)
					sum[Kind][y] += pabyScanline[y + i * iCols*nBands + j * nBands];//更新每一个类的平均值
				count[Kind]++;
			}
			
		}
		//判断是否满足条件，更新类中心
		
		double sumDisDif = 0;
		unsigned long tmpp[100][4];
		for (int i = 0; i < numOfClass; i++)
			for (int j = 0; j < 4; j++)
				tmpp[i][j] = sum[i][j] / count[j];
		for (int i = 0; i < numOfClass; i++)
			sumDisDif += dis(p[i], tmpp[i],4);
		if (J == tmpJ || sumDisDif < 0.0001)
			break;
		else
		{
			J = tmpJ;
			for (int i = 0; i < numOfClass; i++)
				for (int j = 0; j < 4; j++)
					p[i][j] = sum[i][j] / count[i];
		}

	}
	
	GDALDriver* pDriver = GetGDALDriverManager()->GetDriverByName("GTiff");
	GDALDataset* pResult = pDriver->Create(imgOutputPath, iCols, iRows, 1, GDT_Byte, NULL);
	GDALRasterBand* poBandR = pResult->GetRasterBand(1);
	

	//获取图像投影信息
	double GeoTrans[6] = { 0 };
	poDataset->GetGeoTransform(GeoTrans);
	pResult->SetGeoTransform(GeoTrans);
	
	//设置辐射参数
	pResult->SetProjection(poDataset->GetProjectionRef());
	
	poBandR->RasterIO(GF_Write, 0, 0, iCols, iRows, 
		out3,
		iCols,iRows,
		GDT_Byte,
		sizeof(unsigned char), iCols*sizeof(unsigned char));
	//poBandR1->RasterIO(GF_Write, 0, 0, iCols, iRows, out2, iCols,iRows, GDT_Byte, 0, 0);
	
	std::cout << "done  times:"<<time<<endl;
	for (int i = 0; i < numOfClass; i++)

		std::cout << count[i] << "！count["<<i<<"]"<<endl;


	//CPLFree(pMemDadaB);
	free(pabyScanline);
	free(out3);
	GDALClose(pResult);
	GDALClose(poDataset);
	GDALDestroyDriverManager();
	

}

double CMy3170106249SX15Dlg::dis(unsigned long source[], unsigned long p[],int nBands)
{
	int difB1 = source[0] - p[0];
	int difB2 = source[1] - p[1];
	int difB3 = source[2] - p[2];
	int difB4 = source[3] - p[3];
	return sqrt(difB1*difB1 + difB2 * difB2 + difB3 * difB3 + difB4 * difB4);
}
