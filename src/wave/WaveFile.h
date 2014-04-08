/*
 * WaveFile.h
 *
 *  Created on: 2 kwi 2014
 *      Author: mj
 */

#ifndef WAVEFILE_H_
#define WAVEFILE_H_
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <cstring>

class WaveFile {
public:

	WaveFile(char * filename);
	virtual ~WaveFile();
	virtual char * getChunkID();
	virtual unsigned int getChunkSize();
	virtual char * getFormat();
	virtual char * getSubchunk1Id();
	virtual unsigned int getSubchunk1Size();
	virtual unsigned int getAudioFormat();
	virtual unsigned int getNumberOfChanels();
	virtual unsigned int getSampleRate();
	virtual unsigned int getByteRate();
	virtual unsigned int getBlockAlign();
	virtual unsigned int getBitsPerSample();
	virtual char * getSubchunk2Id();
	virtual unsigned int getSubchunk2Size();
	virtual int getSample(int i);
	virtual inline int get8BitSample(int i);
	virtual inline int getHighBitSample(int i);
	virtual unsigned int getNumberOfSamples();
	void loadFromFile(char* filename);
protected:
	WaveFile();
	//chunk descriptor
	char chunkID[4] = { 0 };
	unsigned int chunkSize = 0;
	char format[4] = { 0 };
	// subchunk 1
	char subchunk1Id[4] = { 0 };
	unsigned int subchunk1Size = 0;
	unsigned int audioFormat = 0;
	unsigned int numberOfChanels = 0;
	unsigned int sampleRate = 0;
	unsigned int byteRate = 0;
	unsigned int blockAlign = 0;
	unsigned int bitsPerSample = 0;
	unsigned int bytePerSample = 0;
	//subchunk 2
	char subchunk2Id[4] = { 0 };
	unsigned int subchunk2Size = 0;
	unsigned int numberOfSamples = 0;

	char * data = NULL;

	void readRIFFChunkDescriptor(FILE* file);
	void readFmtSubchunk(FILE* file);
	void ReadDataSubchunk(FILE* file);


	void validateRIFFChunkDescriptor();
	void validateFmtSubchunk();
	void validateDataSubchunk();
	void freeDataIfNotNull();
};

#endif /* WAVEFILE_H_ */