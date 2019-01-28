#include "Sounds.hpp"

Sounds::Sounds(const MusicType & musicType, const float & volume, const float & pitch) :
	soundName(""),
	currentMusicType(musicType)
{
	currentSound.setBuffer(buffer);
	currentMusic.setVolume(volume);
	currentMusic.setPitch(pitch);
	setMusic(musicType);
}

Sounds::Sounds(const std::string & soundName, const float & volume, const float & pitch) :
	soundName(soundName),
	currentMusicType(MusicType::none)
{
	currentSound.setBuffer(buffer);
	currentSound.setVolume(volume);
	currentSound.setPitch(pitch);
}

//=====================================================================================================================================
//-Music Functions
//=====================================================================================================================================


void Sounds::playMusicType(const MusicType & musicType) {
	if (!currentMusic.openFromFile(songs[musicType])) {
		std::cout << "Music - Failed to load file: " << songs[musicType] << "\n";
	}

	currentMusic.play();
}

void Sounds::setMusic(const MusicType & musicType) {
	if (!currentMusic.openFromFile(songs[musicType])) {
		std::cout << "Music - Failed to load file: " << songs[musicType] << "\n";
	}
}

void Sounds::playMusic() {
	currentMusic.play();
}

void Sounds::pauseMusic() {
	currentMusic.pause();
}

void Sounds::stopMusic() {
	currentMusic.stop();
}

void Sounds::setMusicLoop(const bool & loop) {
	currentMusic.setLoop(loop);
}

void Sounds::setMusicVolume(const float & volume) {
	currentMusic.setVolume(volume);
}

float Sounds::getMusicVolume() {
	return currentMusic.getVolume();
}

void Sounds::setMusicPitch(const float & pitch) {
	currentMusic.setPitch(pitch);
}

float Sounds::getMusicPitch() {
	return currentMusic.getPitch();
}

//=====================================================================================================================================
//-SoundEffect Functions
//=====================================================================================================================================

void Sounds::playSoundEffect(const SoundEffect & effectName) {
	if (!buffer.loadFromFile(soundEffects[effectName])) {
		std::cout << "Sound - Failed to load file: " << soundEffects[effectName] << "\n";
	}

	currentSound.setBuffer(buffer);
	currentSound.play();
}

void Sounds::playSoundFile(const std::string & fileName) {
	if (!buffer.loadFromFile(fileName)) {
		std::cout << "Sound - Failed to load file: " << fileName << "\n";
	}

	currentSound.setBuffer(buffer);
	currentSound.play();
}

void Sounds::setSoundBuffer(const std::string & fileName) {
	if (!buffer.loadFromFile(fileName)) {
		std::cout << "Sound - Failed to load file: " << fileName << "\n";
	}

	currentSound.setBuffer(buffer);
}

void Sounds::playSound() {
	currentSound.play();
}

void Sounds::pauseSound() {
	currentSound.pause();
}

void Sounds::stopSound() {
	currentSound.stop();
}

void Sounds::setSoundLoop(const bool & loop) {
	currentSound.setLoop(loop);
}

void Sounds::setSoundVolume(const float & volume) {
	currentSound.setVolume(volume);
}

float Sounds::getSoundVolume() {
	return currentSound.getVolume();
}

void Sounds::setSoundPitch(const float & pitch) {
	currentSound.setPitch(pitch);
}

float Sounds::getSoundPitch() {
	return currentSound.getPitch();
}