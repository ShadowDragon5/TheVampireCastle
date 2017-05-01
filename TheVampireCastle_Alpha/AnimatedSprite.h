#pragma once
#include "Sprite.h"
#include <map>
#include <string>
#include <vector>
#include "Globals.h"

class AnimatedSprite: Sprite
{
public:
	AnimatedSprite();
	~AnimatedSprite();

	void init(glb::Vec4i source, glb::Vec2f pos, const std::string &filePath, SDL_Renderer &renderer, float updateTime);

	void playAnimation(std::string animation, bool once = false);

	void update(int elapsedTime);

	void draw(SDL_Renderer &renderer, glb::Vec2i destination);

	virtual void setUpAnimations();

private:

	std::map<std::string, std::vector<SDL_Rect>> _animations;
	

	int _frameIndex;
	double _time;
	bool _visible;

protected:

	double _timeToUpdate;
	std::string _curAnim;
	bool _once;

	void addAnimation(std::string name, glb::Vec4i src, int frames);

	void resetAnimations();

	void stopAnimation();

	inline void setVisible(bool visible) { this->_visible = visible; }
};

