/*
 * WaveFile.cpp
 *
 *  Created on: 2 kwi 2014
 *      Author: mj
 */

#include "wave/Samples.h"
#include "utils/ataboxexception.h"
#include <sstream>      // std::ostringstream

#include <fstream>
void WaveFile::readRIFFChunkDescriptor(FILE* file) {
	fread(chunkID, 1, 4, file);
	fread(&chunkSize, 1, 4, file);
	fread(format, 1, 4, file);
}

void WaveFile::readFmtSubchunk(FILE* file) {
	fread(&subchunk1Id, 1, 4, file);
	fread(&subchunk1Size, 1, 4, file);
	fread(&audioFormat, 1, 2, file);
	fread(&numberOfChanels, 1, 2, file);
	fread(&sampleRate, 1, 4, file);
	fread(&byteRate, 1, 4, file);
	fread(&blockAlign, 1, 2, file);
	fread(&bitsPerSample, 1, 2, file);
	bytePerSample = bitsPerSample / 8;
}

void WaveFile::ReadDataSubchunk(FILE* file) {
	skipExtraParams(file);
	fread(&subchunk2Size, 1, 4, file);
	freeDataIfNotNull();
	data = new char[subchunk2Size];
	numberOfSamples = subchunk2Size / (bytePerSample * numberOfChanels);
	fread(data, 1, subchunk2Size, file);
}
WaveFile::WaveFile() {
}

void WaveFile::loadFromFile(const char* filename) {
	FILE* file = fopen(filename, "r");
	if (file == NULL) {
		throw ataboxExeption("File not found!");
	}
	readRIFFChunkDescriptor(file);
	validateRIFFChunkDescriptor();
	readFmtSubchunk(file);
	validateFmtSubchunk();
	ReadDataSubchunk(file);
	validateDataSubchunk();
	fclose(file);
}

WaveFile::WaveFile(const char * filename) {
	loadFromFile(filename);
}

WaveFile::WaveFile(uint8_t * tmpdata, uint32_t content_len) {
	loadFromMemory(tmpdata, content_len);

}

void WaveFile::loadFromMemory(uint8_t *tmpData, uint32_t content_len) {


	uint32_t currentIndex = 0;
	std::memcpy(chunkID, tmpData + currentIndex, 4);
	currentIndex += 4;
	std::memcpy(&chunkSize, tmpData + currentIndex, 4);
	currentIndex += 4;
	std::memcpy(format,  tmpData, 4);
	currentIndex += 4;
	std::memcpy(&numberOfChanels, tmpData + 22, 2);
	std::memcpy(&subchunk1Id, tmpData + 12, 4);
	std::memcpy(&subchunk1Size, tmpData + 16, 4);
	std::memcpy(&audioFormat, tmpData + 20, 2);
	std::memcpy(&numberOfChanels, tmpData + 22, 2);
	std::memcpy(&sampleRate, tmpData + 24, 4);
	std::memcpy(&byteRate, tmpData + 28, 4);
	std::memcpy(&blockAlign, tmpData + 32, 2);
	currentIndex = 34;
	std::memcpy(&bitsPerSample, tmpData + currentIndex, 2 );
	currentIndex += 2;
	bytePerSample = bitsPerSample / 8;
	std::memcpy(subchunk2Id, tmpData + currentIndex, 4 );
	currentIndex += 4;
	//TODO: throw error after x attemp find data
	while (strncmp(subchunk2Id, "data", 4) != 0 && currentIndex < content_len){
		currentIndex -= 3;
		std::memcpy(subchunk2Id, tmpData + currentIndex, 4);
		currentIndex += 4;
	}
	freeDataIfNotNull();
	std::memcpy(&subchunk2Size, &tmpData[currentIndex], 4);
	currentIndex += 4;
	data = new char[subchunk2Size];
	if (numberOfChanels == 0 )
		numberOfChanels = 1;
	if (bytePerSample == 0) {
		std::ostringstream ss;
		ss<<currentIndex;
		throw ataboxExeption(std::string("Wrong wave byte per sample 0. Current index ") + ss.str());
	}
	numberOfSamples = subchunk2Size / (bytePerSample * numberOfChanels);
	if (currentIndex + subchunk2Size > content_len )
		throw ataboxExeption("Error. Wrong wave file?");
	std::memcpy(data, tmpData + currentIndex, subchunk2Size);

}

void WaveFile::freeDataIfNotNull() {
	if (data != nullptr) {
		delete[] data;
		data = nullptr;
	}
}

WaveFile::~WaveFile() {
	freeDataIfNotNull();
}

char * WaveFile::getChunkID() {
	return chunkID;
}
unsigned int WaveFile::getChunkSize() {
	return chunkSize;
}
char * WaveFile::getFormat() {
	return format;
}
char * WaveFile::getSubchunk1Id() {
	return subchunk1Id;
}

uint32_t WaveFile::getSubchunk1Size() {
	return subchunk1Size;
}
uint16_t WaveFile::getAudioFormat() {
	return audioFormat;
}
uint16_t WaveFile::getNumberOfChanels() {
	return numberOfChanels;
}
uint32_t WaveFile::getSampleRate() {
	return sampleRate;
}
uint32_t WaveFile::getByteRate() {
	return byteRate;
}
uint16_t WaveFile::getBlockAlign() {
	return blockAlign;
}
uint16_t WaveFile::getBitsPerSample() {
	return bitsPerSample;
}

uint32_t WaveFile::getSubchunk2Size() {
	return subchunk2Size;
}

char * WaveFile::getSubchunk2Id() {
	return subchunk2Id;
}

int32_t WaveFile::getRawSample(unsigned int i) {
	int32_t result = 0;
	memcpy(&result, data + (i * bytePerSample), bytePerSample);
	return result;
}

uint32_t WaveFile::getNumberOfSamples() {
	return numberOfSamples;
}

void WaveFile::validateDataSubchunk() const{

}

void WaveFile::validateFmtSubchunk() const{
	if (numberOfChanels != 1) {
		throw "Only mono files are supported";
	}
}
void WaveFile::validateRIFFChunkDescriptor() const{
	if (strncmp(chunkID, "RIFF", 4) != 0) {
		throw "This is not WAVE file.";
	}
}

void WaveFile::skipExtraParams(FILE* file) {
	fread(&subchunk2Id, 1, 4, file);
	while (strncmp(subchunk2Id, "data", 4) != 0) {
		fseek(file, -3, SEEK_CUR);
		fread(&subchunk2Id, 1, 4, file);
	}
}
double WaveFile::operator[](unsigned int i) {
	return data[i];
}
WaveFile::operator Samples()  const {
	return Samples(*this);

}
/*
WaveFile& WaveFile::operator=(WaveFile&& other) {


	other.chunkID =  chunkID;
	other.chunkSize = chunkSize;
	other.format = format;
	other.subchunk1Id = subchunk1Id;
	other.subchunk1Size = subchunk1Size;
	other.audioFormat = audioFormat;
	other.numberOfChanels = numberOfChanels;
	other.sampleRate = sampleRate;
	other.byteRate = byteRate;
	other.blockAlign = blockAlign;
	other.bitsPerSample = bitsPerSample;
	other.subchunk2Id = subchunk2Id;
	other.subchunk2Size = subchunk2Size;
	other.numberOfSamples = numberOfSamples;
	other.data = data;
}
*/
