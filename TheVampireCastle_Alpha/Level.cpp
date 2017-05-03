#include "Level.h"

#include "tinyxml2.h"
#include <sstream>
#include "ResourceManager.h"

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


void Level::update(float elapsedTime)
{

}



/*
void Level::loadMap(std::string mapName, SDL_Renderer &renderer)
{
	//parse .tmx fiel
	XMLDocument doc;
	std::stringstream ss;
	ss << "content/levels/" << mapName << ".tmx";
	doc.LoadFile(ss.str().c_str());

	XMLElement* mapNode = doc.FirstChildElement("map");


	int width, height;
	mapNode->QueryIntAttribute("width", &width);
	mapNode->QueryIntAttribute("height", &height);
	_size = glb::Vec2i(width, height);

	int tileW, tileH;
	mapNode->QueryIntAttribute("tilewidth", &tileW);
	mapNode->QueryIntAttribute("tileheight", &tileH);
	_tileSize = glb::Vec2i(tileW, tileH);

	//Laod tileSets

	XMLElement* pTileset = mapNode->FirstChildElement("tileset");

	if (pTileset != nullptr)
		while (pTileset)
		{
			int firstgid;
			const char* source = pTileset->FirstChildElement("image")->Attribute("source");
			char* path;
			std::stringstream ss;
			ss << source;
			pTileset->QueryIntAttribute("firstgid", &firstgid);
			SDL_Texture* tex = SDL_CreateTextureFromSurface(&renderer, ResourceManager::loadImage(ss.str()));
			_tilesets.push_back(Tileset(tex, firstgid));

			pTileset = pTileset->NextSiblingElement("tileset");
		}

	//Loading layers

	XMLElement* pLayer = mapNode->FirstChildElement("layer");
	if (pLayer != nullptr)
		while (pLayer)
		{
			//loading data element
			XMLElement* pData = pLayer->FirstChildElement("data");
			if (pData != nullptr)
				while (pData)
				{
					XMLElement* pTile = pData->FirstChildElement("tile");
					if (pTile != nullptr)
					{
						int tileCount = 0;
						while (pTile)
						{

							if (pTile->IntAttribute("gid") == 0)
							{
								tileCount++;
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

							for (int i = 0; i < _tilesets.size(); i++)
							{
								if (_tilesets.at(i).FirstGid <= gid)
								{
									tls = _tilesets[i];
									break;
								}
							}

							if (tls.FirstGid == -1)
							{
								tileCount++;
								if (pTile->NextSiblingElement("tile"))
								{
									pTile->NextSiblingElement("tile");
									continue;
								}
								else
									break;
							}

							int xx = 0, yy = 0;
							xx = tileCount % width;
							xx *= tileW;
							yy += tileH * (tileCount / width);
							glb::Vec2i finalTilePos = glb::Vec2i(xx, yy);

							int tilesetWidth, tilesetHeight;
							SDL_QueryTexture(tls.Texture, nullptr, nullptr, &tilesetWidth, &tilesetHeight);
							int tsxx = gid % (tilesetWidth / tileW) - 1;
							tsxx *= tileW;
							int tsyy = 0;
							int amt = gid / (tilesetWidth / tileW);
							tsyy = tileH * amt;
							glb::Vec2i finalTilesetPos = glb::Vec2i(tsxx, tsyy);

							//Buils tile

							Tile tile;
							tile.init(tls.Texture, glb::Vec2i(tileW, tileH), finalTilesetPos, finalTilePos, 1);
							_tileList.push_back(tile);
							tileCount++;

							pTile = pTile->NextSiblingElement("tile");
						}
					}
					pData = pData->NextSiblingElement("data");
				}
			pLayer = pLayer->NextSiblingElement("layer");
		}

}*/

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
}


void Level::draw(SDL_Renderer &renderer, float scale)
{
	for (int i = 0; i < _tileList.size(); i++)
		_tileList[i].draw(renderer, scale);
}