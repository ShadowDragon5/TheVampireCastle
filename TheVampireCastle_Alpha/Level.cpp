#include "Level.h"

#include "tinyxml2.h"
#include <sstream>
#include <cmath>
#include "ResourceManager.h"
#include "Vampire1.h"

using namespace tinyxml2;

Level::Level():
	_size(glb::Vec2i(0, 0))
{
}


Level::~Level()
{
}


void Level::init(std::string mapName, glb::Vec2f spawnPoint, SDL_Renderer &renderer, float scale)
{
	_mapName = mapName;
	_spawnPoint = spawnPoint;
	_size = glb::Vec2i(0, 0);

	loadMap(mapName, renderer, scale);
}


void Level::update(float elapsedTime, Player &player)
{
	for (int i = 0; i < _enemies.size(); i++)
		_enemies[i]->update(elapsedTime, player);
}


void Level::draw(SDL_Renderer &renderer, float scale)
{
	for (int i = 0; i < _tileList.size(); i++)
		_tileList[i].draw(renderer, scale);

	for (int i = 0; i < _enemies.size(); i++)
		_enemies[i]->draw(renderer, scale);
}


void Level::loadMap(std::string mapName, SDL_Renderer &renderer, float scale)
{
	XMLDocument doc;
	std::stringstream ss;
	ss << "content/levels/" << mapName << ".tmx";
	doc.LoadFile(ss.str().c_str());

	XMLElement* mapNode = doc.FirstChildElement("map");

	int width, height;
	mapNode->QueryIntAttribute("width", &width);
	mapNode->QueryIntAttribute("height", &height);
	this->_size = glb::Vec2i(width, height);

	int tileWidth, tileHeight;
	mapNode->QueryIntAttribute("tilewidth", &tileWidth);
	mapNode->QueryIntAttribute("tileheight", &tileHeight);
	this->_tileSize = glb::Vec2i(tileWidth, tileHeight);

	XMLElement* pTileset = mapNode->FirstChildElement("tileset");
	if (pTileset != NULL)
	{
		while (pTileset)
		{
			int firstgid;
			const char* source = pTileset->FirstChildElement("image")->Attribute("source");
			char* path;
			std::stringstream ss;
			ss << source;
			pTileset->QueryIntAttribute("firstgid", &firstgid);
			SDL_Texture* tex = SDL_CreateTextureFromSurface(&renderer, ResourceManager::loadImage("content" + ss.str().erase(0, 1)));
			this->_tilesets.push_back(Tileset(tex, firstgid));

			pTileset = pTileset->NextSiblingElement("tileset");
		}
	}

	XMLElement* pLayer = mapNode->FirstChildElement("layer");
	if (pLayer != NULL)
	{
		while (pLayer)
		{
			XMLElement* pData = pLayer->FirstChildElement("data");
			if (pData != NULL)
			{
				while (pData)
				{
					XMLElement* pTile = pData->FirstChildElement("tile");
					if (pTile != NULL)
					{
						int tileCounter = 0;
						while (pTile)
						{
							if (pTile->IntAttribute("gid") == 0)
							{
								tileCounter++;
								if (pTile->NextSiblingElement("tile"))
								{
									pTile = pTile->NextSiblingElement("tile");
									continue;
								}
								else
								{
									break;
								}
							}

							int gid = pTile->IntAttribute("gid");
							Tileset tls;
							for (int i = 0; i < this->_tilesets.size(); i++)
							{
								if (this->_tilesets[i].FirstGid <= gid)
								{
									tls = this->_tilesets.at(i);
									break;
								}
							}

							if (tls.FirstGid == -1)
							{
								tileCounter++;
								if (pTile->NextSiblingElement("tile"))
								{
									pTile = pTile->NextSiblingElement("tile");
									continue;
								}
								else
								{
									break;
								}
							}

							int xx = 0;
							int yy = 0;
							xx = tileCounter % width;
							xx *= tileWidth;
							yy += tileHeight * (tileCounter / width);
							glb::Vec2f finalTilePosition = glb::Vec2f(xx, yy);

							int tilesetWidth, tilesetHeight;
							SDL_QueryTexture(tls.Texture, NULL, NULL, &tilesetWidth, &tilesetHeight);
							int tsxx = gid % (tilesetWidth / tileWidth) - 1;
							tsxx *= tileWidth;
							int tsyy = 0;
							int amt = (gid / (tilesetWidth / tileWidth));
							tsyy = tileHeight * amt;
							glb::Vec2f finalTilesetPosition = glb::Vec2f(tsxx, tsyy);

							Tile tile(tls.Texture, glb::Vec2i(tileWidth, tileHeight),
								finalTilesetPosition, finalTilePosition, scale);
							this->_tileList.push_back(tile);
							tileCounter++;

							pTile = pTile->NextSiblingElement("tile");
						}
					}

					pData = pData->NextSiblingElement("data");
				}
			}

			pLayer = pLayer->NextSiblingElement("layer");
		}
	}

	XMLElement* pObjectGroup = mapNode->FirstChildElement("objectgroup");
	if (pObjectGroup != NULL)
	{
		while (pObjectGroup)
		{
			const char* name = pObjectGroup->Attribute("name");
			std::stringstream ss;
			ss << name;

			//collision
			if (ss.str() == "collisions")
			{
				XMLElement* pObject = pObjectGroup->FirstChildElement("object");
				if (pObject != NULL)
				{
					while (pObject)
					{
						float x, y, width, height;
						x = pObject->FloatAttribute("x");
						y = pObject->FloatAttribute("y");
						width = pObject->FloatAttribute("width");
						height = pObject->FloatAttribute("height");
						_collRects.push_back(Rectangle(
							std::ceil(x) * scale,
							std::ceil(y) * scale,
							std::ceil(width) * scale,
							std::ceil(height) * scale
						));

						pObject = pObject->NextSiblingElement("object");
					}
				}
			}

			//spawn points
			else if (ss.str() == "spawnPoints")
			{
				XMLElement* pObject = pObjectGroup->FirstChildElement("object");
				if (pObject != NULL)
				{
					while (pObject)
					{
						float x = pObject->FloatAttribute("x");
						float y = pObject->FloatAttribute("y");
						const char* name = pObject->Attribute("name");
						std::stringstream ss;
						ss << name;
						if (ss.str() == "player")
						{
							_spawnPoint = glb::Vec2f(x * scale, y * scale);
						}


						pObject = pObject->NextSiblingElement("object");
					}
				}
			}

			else if (ss.str() == "enemies")
			{
				XMLElement* pObject = pObjectGroup->FirstChildElement("object");
				if (pObject != NULL)
				{
					while (pObject)
					{
						float x = pObject->FloatAttribute("x");
						float y = pObject->FloatAttribute("y");
						const char* name = pObject->Attribute("name");
						std::stringstream ss;
						ss << name;
						if (ss.str() == "vampire1")
						{
							_enemies.push_back(new Vampire1(renderer, glb::Vec2f(x * scale, y * scale), scale));
						}

						pObject = pObject->NextSiblingElement("object");
					}
				}


			}

			//other objects go here

			pObjectGroup = pObjectGroup->NextSiblingElement("objectgroup");
		}
	}
}


std::vector<Rectangle> Level::checkTileColisions(const Rectangle &other)
{
	std::vector<Rectangle> others;
	for (int i = 0; i < _collRects.size(); i++)
		if (_collRects[i].collidesWith(other))
			others.push_back(_collRects[i]);
	return others;
}