#include "DrawShapes.hpp"

#include <span>

#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/ConvexShape.hpp>
#include <box2d/b2_circle_shape.h>
#include <box2d/b2_edge_shape.h>
#include <box2d/b2_polygon_shape.h>

#include <loki/physics/utils/conversions.hpp>

#include "loki/physics/shapes/PhysicsShape.hpp"

namespace loki::physics::debug {

void drawShape(sf::RenderTarget& target, const b2Shape& shape, const sf::RenderStates& states) {
  switch (shape.GetType()) {
    case b2Shape::e_circle:
      drawCircle(target, static_cast<const b2CircleShape&>(shape), states);
      return;
    case b2Shape::e_edge:
      drawEdge(target, static_cast<const b2EdgeShape&>(shape), states);
      return;
    case b2Shape::e_polygon:
      drawPolygon(target, static_cast<const b2PolygonShape&>(shape), states);
      return;
    case b2Shape::e_chain:
      drawChain(target, static_cast<const b2ChainShape&>(shape), states);
      return;
    default:
      assert(false && "Unknown shape type!");
      return;
  }
}

void drawCircle(sf::RenderTarget& target, const b2CircleShape& circleShape, const sf::RenderStates& states) {
  sf::CircleShape drawableShape;
  drawableShape.setRadius(circleShape.m_radius);
  drawableShape.setOrigin(circleShape.m_radius, circleShape.m_radius);
  drawableShape.setPosition(toSfVec2(circleShape.m_p));
  drawableShape.setFillColor(sf::Color::Transparent);
  drawableShape.setOutlineThickness(-0.1f);
  drawableShape.setOutlineColor(sf::Color::Green);
  target.draw(drawableShape, states);
}

void drawEdge(sf::RenderTarget& target, const b2EdgeShape& edgeShape, const sf::RenderStates& states) {
  sf::VertexArray vertices(sf::Lines);
  sf::Vertex vertex1;
  vertex1.color = sf::Color::Green;
  vertex1.position = toSfVec2(edgeShape.m_vertex1);
  vertices.append(vertex1);
  sf::Vertex vertex2;
  vertex2.color = sf::Color::Green;
  vertex2.position = toSfVec2(edgeShape.m_vertex2);
  vertices.append(vertex2);
  target.draw(vertices, states);
}

void drawPolygon(sf::RenderTarget& target, const b2PolygonShape& polygonShape, const sf::RenderStates& states) {
  sf::ConvexShape drawableShape;
  drawableShape.setPointCount(polygonShape.m_count);
  for (int i{polygonShape.m_count - 1}; i >= 0; --i)
    drawableShape.setPoint(i, toSfVec2(polygonShape.m_vertices[i]));
  drawableShape.setFillColor(sf::Color::Transparent);
  drawableShape.setOutlineThickness(-0.1f);
  drawableShape.setOutlineColor(sf::Color::Green);
  target.draw(drawableShape, states);
}

void drawChain(sf::RenderTarget& target, const b2ChainShape& chainShape, const sf::RenderStates& states) {
  sf::VertexArray vertices(sf::Lines);
  for (auto& v : std::span{chainShape.m_vertices, static_cast<size_t>(chainShape.m_count)}) {
    sf::Vertex vertex;
    vertex.color = sf::Color::Green;
    vertex.position = toSfVec2(v);
    vertices.append(vertex);
  }
  target.draw(vertices, states);
}

}  // namespace loki::physics::debug