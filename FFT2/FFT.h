#pragma once

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <complex>
#include <iostream>
#include <math.h>
#include <valarray>

const double PI = 3.141592653589793238460;

typedef std::complex<double> Complex;
typedef std::valarray<Complex> CArray;

class FFT {
public:
	FFT(std::string const& _path, int const& _bufferSize);

	void hammingWindow();
	void fft(CArray& x);
	void update();

	void bars(float const& max);
	void lines(float const& max);

	void draw(sf::RenderWindow& window);

private:
	std::string path;
	sf::SoundBuffer buffer;
	sf::Sound sound;

	std::vector<Complex> sample;
	std::vector<float> window;
	CArray bin;

	sf::VertexArray VA1;
	sf::VertexArray VA2;
	sf::VertexArray VA3;
	std::vector<sf::Vertex> cascade;

	int sampleRate;
	int sampleCount;
	int bufferSize;
	int mark;
};
