#ifndef ASTEROIDS_GAME_CODE_INCLUDE_BULLET_H
#define ASTEROIDS_GAME_CODE_INCLUDE_BULLET_H

#include <SFML/Graphics.hpp>

#include "game_object.h"

namespace ag {

class Bullet : public GameObject {
 public:
  Bullet() {};
  explicit Bullet(unsigned int id, float rotation, sf::Vector2f ship_velocity,
                  sf::Vector2f ship_position);
  ~Bullet() {};

  const sf::Drawable *get_sprite() const override;
  sf::FloatRect get_bounds() const override;
  sf::Vector2f get_position() const override;
  float get_radius() const override;
  float get_rotation() const override;
  void move_to(sf::Vector2f new_position) override;
  void collide() override;
  void update(float dt) override;

 private:
  const float BULLET_SPEED = 100.0F;
  const float BULLET_SIZE = 1.0F;
  const float BULLET_LIFETIME = 5.0F;

  float m_ttl;
  sf::CircleShape m_sprite;
};

}

#endif
