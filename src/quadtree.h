#ifndef ASTEROIDS_GAME_CODE_INCLUDE_QUADTREE_H
#define ASTEROIDS_GAME_CODE_INCLUDE_QUADTREE_H

#include <memory>

#include <SFML/Graphics.hpp>

#include "game_object.h"
#include "helpers.h"

namespace ag {

class QuadTree {
 public:
  QuadTree() {};
  explicit QuadTree(const unsigned int level, const sf::FloatRect world_area);
  ~QuadTree() {};

  void clear();
  int get_index(const sf::FloatRect bound_box);
  void insert(GameObject &object);
  std::vector<GameObject *> retrieve(sf::FloatRect object_bounds);

 private:
  const unsigned int MAX_OBJECTS = 10;
  const unsigned int MAX_LEVELS = 5;

  void split();

  unsigned int m_level;
  std::vector<GameObject *> m_collidables;
  sf::FloatRect m_bounds;
  std::vector<QuadTree> m_nodes;
};

}

#endif
