#include "include/spaceship.h"

#include <cmath>

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "include/helpers.h"

namespace ag {

Spaceship::Spaceship()
    : m_position{static_cast<sf::Vector2f>(DISPLAY_SIZE / 2U)},
      m_velocity{0.0F, 0.0F}, m_orientation{0.0F}, m_sprite{10.0F, 3U} {
  initialize_sprite_graphics();
  initialize_sprite_position();

  // DEBUG
  initialize_stats_string();
  // END DEBUG
}

bool Spaceship::load_resources(std::string gun_sfx,
    /*DEBUG*/ std::string font /*END DEBUG*/) {
  bool loaded = true;
  if (!m_gun_sound_buffer.loadFromFile(gun_sfx) ||
      /*DEBUG*/ !m_stats_font.loadFromFile(font) /*END DEBUG*/) {
    loaded - false;
  }
  m_gun_sound.setBuffer(m_gun_sound_buffer);

  // DEBUG
  m_ship_stats.setFont(m_stats_font);
  // END DEBUG

  return loaded;
}

void Spaceship::control_ship() {
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
    fire_weapon();
  }
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
    engage_thrusters(1.0F);
  }
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
    engage_thrusters(-0.5F);
  }
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
    m_angular_velocity = 1.0F * ROTATION_SPEED;
  }
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
    m_angular_velocity = -1.0F * ROTATION_SPEED;
  }
}

void Spaceship::update(const sf::Time &dt) {
  m_position = screen_wrap(m_position + (m_velocity * dt.asSeconds()));
  m_sprite.setPosition(m_position);
  if (m_angular_velocity != 0.0F) {
    m_orientation += (m_angular_velocity * dt.asSeconds());
    m_orientation = clamp_orientation(m_orientation);
    m_sprite.rotate(-(m_angular_velocity * dt.asSeconds()));
    m_angular_velocity = 0.0F;
  }

  // DEBUG
  update_ship_stats();
  // END DEBUG
}

void Spaceship::reset_ship() {
  m_position = static_cast<sf::Vector2f>(DISPLAY_SIZE / 2U);
  m_velocity.x = 0.0F;
  m_velocity.y = 0.0F;
  m_orientation = 0.0F;
  initialize_sprite_position();
}

const sf::CircleShape &Spaceship::get_sprite() {
  return m_sprite;
}

void Spaceship::engage_thrusters(const float magnitude) {
  sf::Vector2f direction(std::sin(m_orientation * (M_PI / 180.0F)),
                         std::cos(m_orientation * (M_PI / 180.0F)));
  m_velocity -= (normalize_vector2f(direction) * ACCELERATION * magnitude);
  if (vector2f_length(m_velocity) > MAX_SPEED) {
    sf::Vector2f normal_velocity = normalize_vector2f(m_velocity);
    m_velocity = normal_velocity * MAX_SPEED;
  }
}

void Spaceship::fire_weapon() {
  if (m_gun_sound.getStatus() == sf::Sound::Stopped) {
    m_gun_sound.play();
  }
}

float Spaceship::clamp_orientation(const float raw_orientation) {
  float clamped_orientation = raw_orientation;
  if (clamped_orientation >= 360.0F) {
    clamped_orientation -= 360.0F;
  }
  if (clamped_orientation < 0.0F) {
    clamped_orientation += 360.0F;
  }
  return clamped_orientation;
}

void Spaceship::initialize_sprite_graphics() {
  m_sprite.setOrigin(10.0F, 10.0F);
  m_sprite.setOutlineThickness(1.0F);
  m_sprite.setFillColor(sf::Color::Black);
  m_sprite.setOutlineColor(sf::Color::White);
}

void Spaceship::initialize_sprite_position() {
  m_sprite.setPosition(m_position);
  m_sprite.setRotation(-m_orientation);
}

// DEBUG
const sf::Text &Spaceship::get_ship_stats() {
  return m_ship_stats;
}

void Spaceship::update_ship_stats() {
  std::string stats_str = "X Velocity: " + std::to_string(m_velocity.x) + "\n" +
                          "Y Velocity: " + std::to_string(m_velocity.y) + "\n" +
                          "Rotation: " + std::to_string(m_orientation);
  m_ship_stats.setString(stats_str);
}

void Spaceship::initialize_stats_string() {
  m_ship_stats.setCharacterSize(20U);
  m_ship_stats.setFillColor(sf::Color::White);
  m_ship_stats.setPosition(5.0F, 5.0F);
  m_ship_stats.setString("X Velocity: 0\nY Velocity: 0\nRotation: 0");
}
// END DEBUG

}
