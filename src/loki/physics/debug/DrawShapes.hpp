#pragma once

#if 0

#include <SFML/Graphics/RenderTarget.hpp>
#include <box2d/box2d.h>

namespace loki::physics::debug {

void drawCircle(sf::RenderTarget& target, const b2Circle& circleShape, const sf::RenderStates& states);
void drawEdge(sf::RenderTarget& target, const b2& edgeShape, const sf::RenderStates& states);
void drawPolygon(sf::RenderTarget& target, const b2PolygonShape& polygonShape, const sf::RenderStates& states);
void drawChain(sf::RenderTarget& target, const b2ChainShape& chainShape, const sf::RenderStates& states);

}  // namespace loki::physics::debug

#endif