// Ruan ZongCai's DIB class for Win32.
// Copyright 1998-2000, Ruan ZongCai.

#ifndef RDIB_H 
#define RDIB_H


// !!! Because the HANDLE definition is diffrent
// between <windows.h> and "stdafx.h" by Microsoft
//{{
#ifndef R_HANDLE
	#define R_HANDLE void*
#endif
//}}


class DIB
{

///////////////////////////////////////////////
// interface	
public:
	enum { VERSION=0x0007 };
	char* LastError();
	
	// construction
	DIB( int cx=0, int cy=0,  int bitcount=8, 
		RGBQUAD* palette=NULL );
	DIB( BITMAPINFO* bmi );
	DIB( DIB& dib );
	DIB( char* szfile );
	
	// operator
	 DIB& operator = ( DIB& dib );	// assign
	 BOOL Change( int cx=0, int cy=0,  int bitcount=8, 
		RGBQUAD* palette=NULL );	// change
	 void BottomToTop();	// make Height positive	or flip
	 DIB* MakeGray();		// only 24-bit

	// iuput/output
	 // BITMAPINFO + RGBQUAD[?-1] + DATA
	 BOOL Import( BYTE* dibpack, int data_offset=0 ); 
	 // RGB RAW DATA
	 BOOL Import( BYTE* rgb, int cx, int cy ); 
	 BOOL Export( BYTE*& rgb, int& cx, int& cy ); 
	// support .BMP, .JPG
	 BOOL Load( char* szfile );
	// support .BMP, .JPG
	 BOOL Save( char* szfile, int quality=75);

	// display
	// paint to hdc
	 void Paint( R_HANDLE hdc, RECT* to=NULL, RECT* from=NULL,
						DWORD rop=SRCCOPY );
	 void PaintCenter( R_HANDLE hdc, RECT* to, RECT* from=NULL );
	 double PaintFit( R_HANDLE hdc, RECT* to, RECT* from=NULL );
	 void PaintMosaic( R_HANDLE hdc, RECT* to, RECT* from=NULL );
	// show to window
	 void Show( R_HANDLE hwnd=NULL, RECT* from=NULL );
	 void ShowCenter( R_HANDLE hwnd=NULL, RECT* from=NULL );
	 double ShowFit( R_HANDLE hwnd=NULL, RECT* from=NULL );
	 void ShowStretch( R_HANDLE hwnd=NULL, RECT* from=NULL ); 
	 void ShowMosaic( R_HANDLE hwnd=NULL, RECT* from=NULL ); 
	// paste to dib
	 void Paste( DIB& dib, RECT* from=NULL );
	 void PasteCenter( DIB& dib, RECT* from=NULL );
	 double PasteFit( DIB& dib, RECT* from=NULL );
	 void PasteStretch( DIB& dib, RECT* from=NULL );
	 void PasteMosaic( DIB& dib, RECT* from=NULL );
	// change palette
	 R_HANDLE SetHpalette( R_HANDLE hpal );
	static R_HANDLE CreateHpalette(int ncolor, RGBQUAD* palette);

	// properties
	 RGBQUAD* Palette() ;
	 R_HANDLE Hpalette() ;
	 R_HANDLE Hbitmap() ;
	 DWORD Compression() ;
	 int BitCount() ;
	 int CX() ;
	 int Pitch() ;
	 int CY() ;
	 BITMAPINFO* BitmapInfo() ;
	static int ColorUsed(BITMAPINFO* bmi);

	// GDI gateway
	 R_HANDLE Hdc();
	
	// access buffer
	 BYTE* Buffer();	//format: color_index(1,2,4,8-bit) or BGR(15,16,24,32-bit)
	 int BufferSize();
	 BYTE* Pixel( int x, int y ); // y-down
	 BYTE* Point( int x, int y ); // y-up 
	 void Clear( int c );
	 void ClearColor( int color_bgr ); // >=8-bit


///////////////////////////////////////////////
// implementation	
public:
	 ~DIB();

protected:
	char m_error[100];
	
	int m_cx, m_cy;
	int m_bitcount;
	BOOL m_bfrom_struct;

	struct
	{
		BITMAPINFO bmi;		// include 1 RGBQUAD 
		RGBQUAD more_bmiColors[255];
		void* data;	   // only a reference
	}	
		m_bitmap;
	HPALETTE m_hpal;
	HDC m_hdc;
	HBITMAP m_hbm;	// dib section handle
	HBITMAP m_oldhbm;

	 void _Initialize();
	 void _Finalize();
	 void _SetupPalette();
	 void _PrePaint( HDC hdc );
	
	 BOOL _LoadBMP( char* szfile );
	 BOOL _SaveBMP( char* szfile );
	 BOOL _LoadJPG( char* szfile );
	 BOOL _SaveJPG( char* szfile, int quality );

};

#endif //RDIB_H