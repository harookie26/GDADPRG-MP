#include "Renderer.h"

#include "AirplanePlayer.h"

Renderer::Renderer(std::string name) : AbstractComponent(name, AbstractComponent::Renderer)
{
	this->renderStates = sf::RenderStates::Default;
	this->drawable = nullptr;
	this->targetWindow = nullptr;
}

Renderer::~Renderer()
{
	AbstractComponent::~AbstractComponent();
}

void Renderer::assignTargetWindow(sf::RenderWindow* window)
{
	this->targetWindow = window;
}

void Renderer::assignDrawable(sf::Drawable* drawable)
{
	this->drawable = drawable;
}

void Renderer::setRenderStates(sf::RenderStates renderStates)
{
	this->renderStates = renderStates;
}
void Renderer::perform()
{
    if (this->drawable != nullptr && this->owner->isEnabled())
    {
        this->targetWindow->draw(*this->drawable, this->renderStates);

        // Draw heart sprites if the owner is AirplanePlayer
        AirplanePlayer* player = dynamic_cast<AirplanePlayer*>(this->owner);
        if (player)
        {
            for (auto heart : player->heartSprites)
            {
                this->targetWindow->draw(*heart);
            }
        }
    }
}

