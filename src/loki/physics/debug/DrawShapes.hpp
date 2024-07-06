#pragma once

#include <SFML/Graphics/RenderTarget.hpp>
#include <box2d/b2_shape.h>

class b2ChainShape;

namespace loki::physics::debug {

void drawShape(sf::RenderTarget& target, const b2Shape& shape, const sf::RenderStates& states);
void drawCircle(sf::RenderTarget& target, const b2CircleShape& circleShape, const sf::RenderStates& states);
void drawEdge(sf::RenderTarget& target, const b2EdgeShape& edgeShape, const sf::RenderStates& states);
void drawPolygon(sf::RenderTarget& target, const b2PolygonShape& polygonShape, const sf::RenderStates& states);
void drawChain(sf::RenderTarget& target, const b2ChainShape& chainShape, const sf::RenderStates& states);

}  // namespace loki::physics::debug