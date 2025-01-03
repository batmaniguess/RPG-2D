#include "Button.h"

Button::Button(float x, float y, float width, float height, sf::Font* font,
               std::string text, sf::Color idleColor, sf::Color hoverColor,
               sf::Color activeColor) {
  this->buttonState = BTN_IDLE;
  this->button.setPosition(sf::Vector2f(x, y));
  this->button.setSize(sf::Vector2f(width, height));
  this->font = font;
  this->text.setFont(*this->font);
  this->text.setString(text);
  this->text.setFillColor(sf::Color::White);
  this->text.setCharacterSize(24);
  this->text.setPosition(
      this->button.getPosition().x + (this->button.getSize().x / 2.f) -
          (this->text.getLocalBounds().width / 2.f),
      this->button.getPosition().y + (this->button.getSize().y / 2.f) -
          (this->text.getLocalBounds().height / 2.f));

  this->idleColor = idleColor;
  this->hoverColor = hoverColor;
  this->activeColor = activeColor;
  this->button.setFillColor(this->idleColor);
}

Button::~Button() {}

const bool Button::isPressed() const {
  if (this->buttonState == BTN_ACTIVE) {
    return true;
  }
  return false;
}

void Button::update(const sf::Vector2f mousePos) {
  /**
   * @brief Updates the button state based on the mouse position.
   *
   * This function checks if the mouse position is within the bounds of the
   * button. If the mouse is over the button, the button state is set to hover.
   * If the left mouse button is pressed while hovering, the button state is set
   * to active.
   *
   * @param mousePos The current position of the mouse.
   */
  this->buttonState = BTN_IDLE;
  if (this->button.getGlobalBounds().contains(mousePos)) {
    this->buttonState = BTN_HOVER;
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
      this->buttonState = BTN_ACTIVE;
    }
  }
  switch (this->buttonState) {
    case BTN_IDLE:
      this->button.setFillColor(this->idleColor);
      break;
    case BTN_HOVER:
      this->button.setFillColor(this->hoverColor);
      break;
    case BTN_ACTIVE:
      this->button.setFillColor(this->activeColor);
      break;
    default:
      this->button.setFillColor(sf::Color::Cyan);
      break;
  }
}

void Button::render(sf::RenderTarget* target) {
  target->draw(this->button);
  target->draw(this->text);
}
