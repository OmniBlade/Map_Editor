#pragma once
class GenericLoader
{
public:
	GenericLoader();
	~GenericLoader();

	/*
	Loads the audio stuff from the game, this includes EVA speeches (Eva, Sofia), themes (music) and sound effects
	*/
	void loadAudioVisual();
	void reloadAudioVisual();
};

