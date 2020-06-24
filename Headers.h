


#include <iostream>
#include <fstream>
#include <math.h>
#include <cmath>
#include <algorithm>

using namespace std;

void ReadFile(char*, unsigned char*, int, int, int);
void WriteFile(char*, unsigned char*, int, int, int);
void Delete2d(unsigned char**, int);
void Delete3d(unsigned char*** , int , int );
unsigned char** Allocate2d(unsigned char**, int, int);
unsigned char*** Convert1dto3d(unsigned char*, int, int, int);
unsigned char* Convert3dTo1d(unsigned char***, int, int, int);

//unsigned char** Img1dTo2d(unsigned char*, int, int);
//unsigned char* Img2dTo1d(unsigned char**, int, int);

void ReadFile(char* FileName, unsigned char* Imagedata, int ImgHeight, int ImgWidth, int BytesPerPixel)
{
	FILE* file;

	if (!(file=fopen(FileName,"rb")))
    {
        cout << "Cannot open file: " << FileName <<endl;
		exit(1);
    }
    fread(Imagedata, sizeof(unsigned char), ImgHeight*ImgWidth*BytesPerPixel, file);
    fclose(file);
	cout << "File " << FileName << " has been read successfully! " << endl;
}

void WriteFile(char* FileName, unsigned char* Imagedata, int ImgHeight, int ImgWidth, int BytesPerPixel)
{
	FILE* file;

	if (!(file=fopen(FileName,"wb"))) {
		cout << "Cannot open file: " << FileName << endl;
		exit(1);
	}
	fwrite(Imagedata, sizeof(unsigned char), ImgHeight*ImgWidth*BytesPerPixel, file);
	fclose(file);
	cout << "File " << FileName << " has been written successfully!" << endl;
}

unsigned char** Allocate2d(unsigned char** Imagedata, int ImgHeight, int ImgWidth)
{
	Imagedata = new unsigned char *[ImgHeight]();
	for (int i = 0;i < ImgHeight;i++)
	{
		Imagedata[i] = new unsigned char[ImgWidth]();
		for (int j = 0;j < ImgWidth;j++)
		{
			Imagedata[i][j] = 0;
		}
	}
	return Imagedata;
}

void Delete2d(unsigned char** Imagedata, int ImgHeight)
{
	for (int i = 0; i < ImgHeight; i++)
	{
		delete[] Imagedata[i];
	}
	delete[] Imagedata;
}

void Delete3d(unsigned char*** Imagedata, int ImgHeight, int ImgWidth)
{
	for (int i = 0; i < ImgHeight; i++)
	{
		for (int j = 0; j < ImgWidth; j++)
			delete[] Imagedata[i][j];
		delete[] Imagedata[i];
	}
	delete[] Imagedata;
}


unsigned char*** Convert1dto3d(unsigned char* Imagedata, int ImgHeight, int ImgWidth, int BytesPerPixel)
{
	unsigned char*** Imagedata3d =  new unsigned char **[ImgHeight]();
	for (int i = 0; i < ImgHeight; i++)
	{
		Imagedata3d[i] = new unsigned char *[ImgWidth]();
		for (int j = 0; j < ImgWidth; j++)
		{
			Imagedata3d[i][j] = new unsigned char[BytesPerPixel]();
			for (int k = 0; k < BytesPerPixel; k++)
			{
				Imagedata3d[i][j][k] = 0;
			}
		}
	}

    //int m = 0 ;
	for (int i = 0; i < ImgHeight; i++)
	{
		for (int j = 0; j < ImgWidth; j++)
		{
			for (int k = 0; k < BytesPerPixel; k++)
			{
				Imagedata3d[i][j][k] = Imagedata[i * ImgWidth * BytesPerPixel + j * BytesPerPixel + k];
				//Imagedata3d[i][j][k] = Imagedata[m];
				//m = m+1;
			}
		}
	}
	return(Imagedata3d);
}


unsigned char* Convert3dTo1d(unsigned char*** Imagedata3d, int ImgHeight, int ImgWidth, int BytesPerPixel)
{
	unsigned char* Imagedata = new unsigned char[ImgHeight*ImgWidth*BytesPerPixel]();
	int m = 0;
	for (int i = 0; i < ImgHeight; i++)
	{
		for (int j = 0; j < ImgWidth; j++)
		{
			Imagedata [m] = Imagedata3d[i][j][0];
			Imagedata [m + 1] = Imagedata3d[i][j][1];
			Imagedata [m + 2] = Imagedata3d[i][j][2];
			m = m + 3;
		}
	}
	return(Imagedata);
}
