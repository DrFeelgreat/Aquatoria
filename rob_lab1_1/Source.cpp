#include "Screen.h"



Screen::Screen()
{
}


Screen::~Screen()
{
}

bool Screen::load(const std::string & textureFile, sf::FloatRect textureCoord, sf::Vector2u size, sf::Vector2f position)
{
	if (!m_texture.loadFromFile(textureFile))
		return false;

	m_vertices.setPrimitiveType(sf::Quads);
	m_vertices.resize(4);
	m_frameSize = textureCoord;
	m_texture.setSmooth(true);
	m_vertices[0].position = position;
	m_vertices[1].position = sf::Vector2f(position.x + size.x, position.y);
	m_vertices[2].position = sf::Vector2f(position.x + size.x, position.y + size.y);
	m_vertices[3].position = sf::Vector2f(position.x, position.y + size.y);

	m_vertices[0].texCoords = sf::Vector2f(textureCoord.left, textureCoord.top);
	m_vertices[1].texCoords = sf::Vector2f(textureCoord.left + textureCoord.width, textureCoord.top);
	m_vertices[2].texCoords = sf::Vector2f(textureCoord.left + textureCoord.width, textureCoord.top + textureCoord.height);
	m_vertices[3].texCoords = sf::Vector2f(textureCoord.left, textureCoord.top + textureCoord.height);


	return true;
}

void Screen::setMaxFrame(int frameNumber)
{
	animation_step_max = frameNumber;
}

void Screen::nextFrame()
{
	animation_step++;
	if (animation_step >= animation_step_max)
		animation_step = 0;

	m_vertices[0].texCoords = sf::Vector2f(m_frameSize.left + m_frameSize.width*animation_step, m_frameSize.top);
	m_vertices[1].texCoords = sf::Vector2f(m_frameSize.left + m_frameSize.width*(animation_step + 1), m_frameSize.top);
	m_vertices[2].texCoords = sf::Vector2f(m_frameSize.left + m_frameSize.width*(animation_step + 1), m_frameSize.top + m_frameSize.height);
	m_vertices[3].texCoords = sf::Vector2f(m_frameSize.left + m_frameSize.width*animation_step, m_frameSize.top + m_frameSize.height);

}

void Screen::visibility(bool visible)
{
	vis = visible;
}

void Screen::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	if (vis)
	{
		states.texture = &m_texture;
		target.draw(m_vertices, states);
	}
}