#include "FFT.h"

FFT::FFT(std::string const& _path, int const& _bufferSize)
    : sampleRate()
    , sampleCount()
    , bufferSize()
    , mark() {
	path = _path;
	if (!buffer.loadFromFile(path))
		std::cout << "Unable to load buffer" << std::endl;

	sound.setBuffer(buffer);
	sound.setLoop(true);
	sound.play();

	VA1.setPrimitiveType(sf::LineStrip);
	VA2.setPrimitiveType(sf::Lines);
	VA3.setPrimitiveType(sf::LineStrip);

	sampleRate = buffer.getSampleRate() * buffer.getChannelCount();
	sampleCount = buffer.getSampleCount();
	if (_bufferSize < sampleCount)
		bufferSize = _bufferSize;
	else
		bufferSize = sampleCount;
	mark = 0;

	for (int i(0); i < bufferSize; i++)
		window.push_back(0.54 - 0.46 * cos(2 * PI * i / (float)bufferSize));

	sample.resize(bufferSize);
	VA1.resize(bufferSize);
}

void FFT::hammingWindow() {
	mark = sound.getPlayingOffset().asSeconds() * sampleRate;
	if (mark + bufferSize < sampleCount) {
		for (int i(mark); i < bufferSize + mark; i++) {
			sample[i - mark] = Complex(buffer.getSamples()[i] * window[i - mark], 0);
			VA1[i - mark] = sf::Vertex(sf::Vector2f(20, 250) + sf::Vector2f((i - mark) / (float)bufferSize * 700,
			                                                                sample[i - mark].real() * 0.005),
			                           sf::Color(255, 0, 0, 50));
		}
	}
}
void FFT::fft(CArray& x) {
	const int N = x.size();
	if (N <= 1)
		return;

	CArray even = x[std::slice(0, N / 2, 2)];
	CArray odd = x[std::slice(1, N / 2, 2)];

	fft(even);
	fft(odd);

	for (int k = 0; k < N / 2; k++) {
		Complex t = std::polar(1.0, -2 * PI * k / N) * odd[k];
		x[k] = even[k] + t;
		x[k + N / 2] = even[k] - t;
	}
}

void FFT::update() {
	hammingWindow();

	VA2.clear();
	VA3.clear();

	bin = CArray(sample.data(), bufferSize);
	fft(bin);
	float max = 100000000;

	lines(max);
	bars(max);
}

void FFT::bars(float const& max) {
	VA2.setPrimitiveType(sf::Lines);
	sf::Vector2f position(0, 800);
	for (float i(3); i < std::min(bufferSize / 2.f, 20000.f); i *= 1.01) {
		sf::Vector2f samplePosition(log(i) / log(std::min(bufferSize / 2.f, 20000.f)), abs(bin[(int)i]));
		VA2.append(sf::Vertex(position + sf::Vector2f(samplePosition.x * 800, -samplePosition.y / max * 500),
		                      sf::Color::White));
		VA2.append(sf::Vertex(position + sf::Vector2f(samplePosition.x * 800, 0), sf::Color::White));
		VA2.append(
		    sf::Vertex(position + sf::Vector2f(samplePosition.x * 800, 0), sf::Color(255, 255, 255, 100)));
		VA2.append(sf::Vertex(position + sf::Vector2f(samplePosition.x * 800, samplePosition.y / max * 500 / 2.f),
		                      sf::Color(255, 255, 255, 0)));
	}
}
void FFT::lines(float const& max) {
	VA3.setPrimitiveType(sf::LineStrip);
	sf::Vector2f position(0, 800);
	sf::Vector2f samplePosition;
	float colorDecay = 1;

	for (float i(std::max((double)0, cascade.size() - 3e5)); i < cascade.size(); i++) {
		cascade[i].position -= sf::Vector2f(-0.8, 1);
		if (cascade[i].color.a != 0)
			cascade[i].color = sf::Color(255, 255, 255, 20);
	}
	samplePosition = sf::Vector2f(log(3) / log(std::min(bufferSize / 2.f, 20000.f)), abs(bin[(int)3]));
	cascade.push_back(sf::Vertex(position + sf::Vector2f(samplePosition.x * 800, -samplePosition.y / max * 500),
	                             sf::Color::Transparent));
	for (float i(3); i < bufferSize / 2.f; i *= 1.02) {
		samplePosition = sf::Vector2f(log(i) / log(std::min(bufferSize / 2.f, 20000.f)), abs(bin[(int)i]));
		cascade.push_back(sf::Vertex(position + sf::Vector2f(samplePosition.x * 800, -samplePosition.y / max * 500),
		                             sf::Color(255, 255, 255, 20)));
	}
	cascade.push_back(sf::Vertex(position + sf::Vector2f(samplePosition.x * 800, -samplePosition.y / max * 500),
	                             sf::Color::Transparent));

	VA3.clear();
	for (int i(std::max((double)0, cascade.size() - 3e5)); i < cascade.size(); i++)
		VA3.append(cascade[i]);
}

void FFT::draw(sf::RenderWindow& window) {
	window.draw(VA1);
	window.draw(VA3);
	window.draw(VA2);
}
