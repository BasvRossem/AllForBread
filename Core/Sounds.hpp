#pragma once
#include <SFML/Audio.hpp>
#include <iostream>
#include <unordered_map>

enum class MusicType {
	none,
	menu,
	overworld,
	battle,
	boss,
	town,
	avengers,
	unicorns
};

enum class SoundEffect {
	error,
	levelUp,
	scrollOpen,
	scrollClose,
	battleStart,
	battleClose,
	menuOpen,
	menuClose,
	buttonHover,
	buttonBack,
	weakAttack, 
	strongAttack,
	key,
	armorEquip,
	weaponEquip,
	bagClose, 
	bagOpen,
	consumable,
	playerDeath,
	monsterDeath,
	purchase,
	gameStart,
	threaten,
	laugh,
	partyLeader
};

class Sounds {
private:
	std::string soundName;
	MusicType currentMusicType;

	sf::SoundBuffer buffer;
	sf::Sound currentSound;
	sf::Music currentMusic;

	std::unordered_map<MusicType, std::string> songs = {
		{MusicType::none,			"Empty, you nosey programmer"},
		{MusicType::menu,			"GameMusic/Menu.wav"},
		{MusicType::overworld,		"GameMusic/OverworldMap.wav"},
		{MusicType::battle,			"GameMusic/Battle.wav"},
		{MusicType::boss,			"GameMusic/TheGrandFinale.wav"},
		{MusicType::town,			"GameMusic/Town.wav"},
		{MusicType::avengers,		"GameMusic/Avengers.wav"},
		{MusicType::unicorns,		"GameMusic/PinkFluffyUnicorns.wav"}
	};

	std::unordered_map<SoundEffect, std::string> soundEffects{
		{SoundEffect::error,		"SoundEffects/Error.wav"},
		{SoundEffect::levelUp,		"SoundEffects/LevelUp.wav"},
		{SoundEffect::scrollOpen,	"SoundEffects/ScrollOpen1.wav"},
		{SoundEffect::scrollClose,	"SoundEffects/ScrollClose1.wav"},
		{SoundEffect::battleStart,	"SoundEffects/BattleStart.wav"},
		{SoundEffect::battleClose,	"SoundEffects/"},
		{SoundEffect::menuOpen,		"SoundEffects/"},
		{SoundEffect::menuClose,	"SoundEffects/"},
		{SoundEffect::buttonHover,	"SoundEffects/ButtonHover.wav"},
		{SoundEffect::buttonBack,	"SoundEffects/BackButton.wav"},
		{SoundEffect::weakAttack,	"SoundEffects/WeakAttack.wav"},
		{SoundEffect::strongAttack,	"SoundEffects/StrongAttack.wav"},
		{SoundEffect::key,			"SoundEffects/Key.wav"},
		{SoundEffect::armorEquip,	"SoundEffects/ArmorEquip.wav"},
		{SoundEffect::weaponEquip,	"SoundEffects/WeaponEquip.wav"},
		{SoundEffect::bagClose,		"SoundEffects/BagClose.wav"},
		{SoundEffect::bagOpen,		"SoundEffects/BagOpen.wav"},
		{SoundEffect::consumable,	"SoundEffects/Consumable.wav"},
		{SoundEffect::playerDeath,	"SoundEffects/PlayerDeath.wav"},
		{SoundEffect::monsterDeath,	"SoundEffects/MonsterDeath.wav"},
		{SoundEffect::purchase,		"SoundEffects/Purchase.wav"},
		{SoundEffect::gameStart,	"SoundEffects/GameStart.wav"},
		{SoundEffect::threaten,		"SoundEffects/DeathIsImminent.wav"},
		{SoundEffect::laugh,		"SoundEffects/Laugh.wav"},
		{SoundEffect::partyLeader,	"SoundEffects/PartyLeader.wav"}
	};

public:
	Sounds(const MusicType & musicType, const float & volume = 100.0f, const float & pitch = 1.0f);
	Sounds(const std::string & soundName, const float & volume = 100.0f, const float & pitch = 1.0f);
	Sounds(const float & volume = 100.0f, const float & pitch = 1.0f);

	//============================================================================================
	//-Music
	//============================================================================================

	/// \brief
	/// Plays a music type from the enum class on the sf::Music object
	void playMusicType(const MusicType & musicType);

	/// \brief
	/// Sets a new music type on the sf::Music object but doesn't autoplay
	void setMusic(const MusicType & musicType);

	/// \brief
	/// Plays the currently loaded song on the sf::Music object
	void playMusic();

	/// \brief
	/// Pauses the currently loaded song on the sf::Music object
	void pauseMusic();

	/// \brief
	/// Stops the currently loaded song on the sf::Music object
	void stopMusic();

	/// \brief
	/// Sets the music on the sf::Music object to loop when it is finished
	void setMusicLoop(const bool & loop);

	/// \brief
	/// Sets the volume of the sf::Music object
	void setMusicVolume(const float & volume);

	/// \brief
	/// Returns the volume of the sf::Music object
	float getMusicVolume();

	/// \brief
	/// Sets the pitch of the sf::Music object
	void setMusicPitch(const float & pitch);

	/// \brief
	/// Returns the pitch of the sf::Music object
	float getMusicPitch();

	//============================================================================================
	//-Sound Effects
	//============================================================================================

	/// \brief
	/// Plays sound effect from the sound effect enum class
	void playSoundEffect(const SoundEffect & effectName);

	/// \brief
	/// Loads the given filename into the buffer and plays the sound on the sf::Sound object
	void playSoundFile(const std::string & fileName);

	/// \brief
	/// Sets the buffer of the sf::Sound object
	void setSoundBuffer(const std::string & fileName);

	/// \brief
	/// Plays the buffered sound on the sf::Sound object
	void playSound();

	/// \brief
	/// Pauses the sound being played on the sf::Sound object
	void pauseSound();

	/// \brief
	/// Stops the sound being played on the sf::Sound object
	void stopSound();

	/// \brief
	/// Sets the sound on the sf::Sound object to loop
	void setSoundLoop(const bool & loop);

	/// \brief
	/// Sets the volume of the sf::Sound object
	void setSoundVolume(const float & volume);

	/// \brief
	/// Returns the volume of the sf::Sound object
	float getSoundVolume();

	/// \brief
	/// Sets the pitch of the sf::Sound object
	void setSoundPitch(const float & pitch);

	/// \brief
	/// Returns the pitch of the sf::Sound object
	float getSoundPitch();
};