#ifndef BMP_H
#define BMP_H

#include <vector>
#include <fstream>
#include <iostream>
class BitMap {

private:
	unsigned char m_bmpFileHeader[14];
	unsigned int m_pixelArrayOffset;
	unsigned char m_bmpInfoHeader[40];

	int m_height;
	int m_width;
	int m_bitsPerPixel;

	int m_rowSize;
	int m_pixelArraySize;

	unsigned char* m_pixelData;

public:
	BitMap(char* filename);
	~BitMap();

	std::vector<unsigned int> getPixel(int i, int j);

	void dispPixelData();
};

BitMap::BitMap(char* filename) {

	using namespace std;

	ifstream inf(filename);
	if (!inf) {
		cerr << "Unable to open file\n";
	}

	//unsigned char m_bmpFileHeader[14];
	unsigned char a;
	for (int i = 0; i<14; i++) {
		inf >> hex >> a;
		m_bmpFileHeader[i] = a;
	}
	if (m_bmpFileHeader[0] != 'B' || m_bmpFileHeader[1] != 'M') {
		cerr << "Your info header might be different!\nIt should start with 'BM'.\n";
	}

	/*
	THE FOLLOWING LINE ONLY WORKS IF THE OFFSET IS 1 BYTE!!!!! (it can be 4 bytes max)
	*/
	m_pixelArrayOffset = m_bmpFileHeader[10];



	//unsigned char m_bmpInfoHeader[40];
	for (int i = 0; i<40; i++) {
		inf >> hex >> a;
		m_bmpInfoHeader[i] = a;
	}
	m_width = m_bmpInfoHeader[4];
	m_height = m_bmpInfoHeader[8];

	m_bitsPerPixel = m_bmpInfoHeader[14];
	if (m_bitsPerPixel != 24) {
		cerr << "This program is for 24bpp files. Your bmp is not that\n";
	}
	int compressionMethod = m_bmpInfoHeader[16];
	if (compressionMethod != 0) {
		cerr << "There's some compression stuff going on that we might not be able to deal with.\n";
		cerr << "Comment out offending lines to continue anyways. bpm.h line: " << __LINE__ << "\n";
	}


	m_rowSize = int(floor((m_bitsPerPixel*m_width + 31.) / 32)) * 4;
	m_pixelArraySize = m_rowSize* abs(m_height);

	m_pixelData = new unsigned char[m_pixelArraySize];

	inf.seekg(m_pixelArrayOffset, ios::beg);
	for (int i = 0; i<m_pixelArraySize; i++) {
		inf >> hex >> a;
		m_pixelData[i] = a;
	}


	/*
	for(int i=0;i<m_pixelArraySize;i++) {
	std::cout<<std::hex<<(unsigned int)pixelData[i]<<" ";
	}
	/*
	for(int i=0;i<40;i++) {
	std::cout<<std::hex<<(unsigned int)m_bmpInfoHeader[i]<<" ";
	}
	*/

}

BitMap::~BitMap() {
	delete[] m_pixelData;
}

void BitMap::dispPixelData() {
	for (int i = 0; i<m_pixelArraySize; i++) {
		std::cout << (unsigned int)m_pixelData[i] << " ";
	}
	std::cout << "\n";
}

// output is in rgb order.
std::vector<unsigned int> BitMap::getPixel(int x, int y) {
	if (x<m_width && y<m_height) {
		std::vector<unsigned int> v;
		v.push_back(0);
		v.push_back(0);
		v.push_back(0);

		y = m_height - 1 - y; //to flip things
							  //std::cout<<"y: "<<y<<" x: "<<x<<"\n";
		v[0] = (unsigned int)(m_pixelData[m_rowSize*y + 3 * x + 2]); //red
		v[1] = (unsigned int)(m_pixelData[m_rowSize*y + 3 * x + 1]); //greed
		v[2] = (unsigned int)(m_pixelData[m_rowSize*y + 3 * x + 0]); //blue

		return v;
	}
	else { std::cerr << "BAD INDEX\n"; }
}




#endif