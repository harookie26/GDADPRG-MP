#include "AGameObject.h"

#include "GenericInputController.h"
#include "Renderer.h"

/**
 * @brief Construct a new AGameObject object
 *
 * @param name The name of the game object
 */
AGameObject::AGameObject(std::string name)
    : name(name)
{
}

/**
 * @brief Destroy the AGameObject object
 *
 */
AGameObject::~AGameObject()
{
    if (this->sprite != NULL)
    {
        delete this->sprite;
    }

	for (int i = 0; i < this->componentList.size(); i++)
	{
		delete this->componentList[i];
	}

	for (int i = 0; i < this->childList.size(); i++)
	{
		delete this->childList[i];
	}
}

/**
 * @brief Get the name of the game object
 *
 * @return std::string The name of the game object
 */
std::string AGameObject::getName()
{
    return name;
}

/**
 * @brief Get the transformable object of the game object
 *
 * @return sf::Transformable* Pointer to the transformable object
 */
sf::Transformable* AGameObject::getTransformable()
{
    return &this->transformable;
}

/**
 * @brief Draw the game object and its children
 *
 * @param targetWindow The window to draw the object on
 * @param renderStates The render states to use for drawing
 */
void AGameObject::draw(sf::RenderWindow* targetWindow, sf::RenderStates renderStates)
{
    if (!this->isEnabled()) return;

    renderStates.transform = renderStates.transform * this->transformable.getTransform();

    std::vector<AbstractComponent*> componentList = this->getComponentsOfType(AbstractComponent::ComponentType::Renderer);

    for (int j = 0; j < componentList.size(); j++)
    {
        Renderer* renderer = (Renderer*)componentList[j];
        renderer->assignTargetWindow(targetWindow);
        renderer->setRenderStates(renderStates);
        renderer->perform();
    }

    for (int i = 0; i < this->childList.size(); i++)
    {
        AGameObject* child = this->childList[i];
        child->draw(targetWindow, renderStates);
    }
}

/**
 * @brief Attach a child game object
 *
 * @param child The child game object to attach
 */
void AGameObject::attachChild(AGameObject* child)
{
    this->childList.push_back(child);
    child->setParent(this);
    child->initialize();
}

/**
 * @brief Detach a child game object
 *
 * @param child The child game object to detach
 */
void AGameObject::detachChild(AGameObject* child)
{
    int index = -1;

    for (int i = 0; i < this->childList.size(); i++)
    {
        if (this->childList[i] == child)
        {
            index = 1;
        }
    }

    if (index != 1)
    {
        this->childList.erase(this->childList.begin() + index);
        this->childList.shrink_to_fit();
    }
}

/**
 * @brief Set the position of the game object
 *
 * @param x The x-coordinate of the position
 * @param y The y-coordinate of the position
 */
void AGameObject::setPosition(float x, float y)
{
    this->transformable.setPosition(x, y);
}

/**
 * @brief Process input events for the game object and its children
 *
 * @param event The input event to process
 */
void AGameObject::processInput(sf::Event event)
{
    if (!this->isEnabled()) return;

    std::vector<AbstractComponent*> componentList = this->getComponentsOfType(AbstractComponent::ComponentType::Input);
    for (int j = 0; j < componentList.size(); j++)
    {
        ((GenericInputController*)componentList[j])->assignEvent(event);
        componentList[j]->perform();
    }

    for (int i = 0; i < this->childList.size(); i++)
    {
        childList[i]->processInput(event);
    }
}

/**
 * @brief Update the game object and its children
 *
 * @param deltaTime The time elapsed since the last update
 */
void AGameObject::update(sf::Time deltaTime)
{
    if (!this->isEnabled()) return;

    std::vector<AbstractComponent*> componentList = this->getComponentsOfType(AbstractComponent::ComponentType::Script);

    for (int j = 0; j < componentList.size(); j++)
    {
        componentList[j]->setDeltaTime(deltaTime);
        componentList[j]->perform();
    }

    for (int i = 0; i < this->childList.size(); i++)
    {
        childList[i]->update(deltaTime);
    }
}

/**
 * @brief Attach a component to the game object
 *
 * @param component The component to attach
 */
void AGameObject::attachComponent(AbstractComponent* component)
{
    this->componentList.push_back(component);
    component->attachOwner(this);
}

/**
 * @brief Detach a component from the game object
 *
 * @param component The component to detach
 */
void AGameObject::detachComponent(AbstractComponent* component)
{
    int index = -1;
    for (int i = 0; i < this->componentList.size(); i++)
    {
        if (this->componentList[i] == component)
        {
            index = i;
            this->componentList.erase(this->componentList.begin() + i);
            break;
        }
    }

    if (index != 1)
    {
        this->componentList.erase(this->componentList.begin() + index);
    }
}

/**
 * @brief Find a component by its name
 *
 * @param name The name of the component
 * @return AbstractComponent* Pointer to the found component, or nullptr if not found
 */
AbstractComponent* AGameObject::findComponentByName(std::string name)
{
    for (int i = 0; i < this->componentList.size(); i++)
    {
        if (this->componentList[i]->getName() == name)
        {
            return this->componentList[i];
        }
    }
    return nullptr;
}

/**
 * @brief Find a component of a specific type and name
 *
 * @param type The type of the component
 * @param name The name of the component
 * @return AbstractComponent* Pointer to the found component, or nullptr if not found
 */
AbstractComponent* AGameObject::findComponentOfType(AbstractComponent::ComponentType type, std::string name)
{
    for (int i = 0; i < this->componentList.size(); i++)
    {
        if (this->componentList[i]->getType() == type && this->componentList[i]->getName() == name)
        {
            return this->componentList[i];
        }
    }
    return nullptr;
}

/**
 * @brief Get all components of a specific type
 *
 * @param type The type of the components
 * @return std::vector<AbstractComponent*> A vector containing the found components
 */
std::vector<AbstractComponent*> AGameObject::getComponentsOfType(AbstractComponent::ComponentType type)
{
    std::vector<AbstractComponent*> foundList;
    for (int i = 0; i < this->componentList.size(); i++)
    {
        if (this->componentList[i]->getType() == type)
        {
            foundList.push_back(this->componentList[i]);
        }
    }
    return foundList;
}

/**
 * @brief Recursively get all components of a specific type from the game object and its children
 *
 * @param object The game object to start the search from
 * @param type The type of the components
 * @param foundList A vector to store the found components
 * @return std::vector<AbstractComponent*> A vector containing the found components
 */
std::vector<AbstractComponent*> AGameObject::getComponentsRecursiveProper(AGameObject* object, AbstractComponent::ComponentType type, std::vector<AbstractComponent*> foundList)
{
    std::vector<AbstractComponent*> foundListCopy = foundList;
    std::vector<AbstractComponent*> componentList = object->getComponentsOfType(type);
    for (int i = 0; i < componentList.size(); i++)
    {
        foundListCopy.push_back(componentList[i]);
    }
    for (int i = 0; i < object->childList.size(); i++)
    {
        foundListCopy = getComponentsRecursiveProper(object->childList[i], type, foundListCopy);
    }
    return foundListCopy;
}

/**
 * @brief Set the enabled state of the game object
 *
 * @param flag The enabled state to set
 */
void AGameObject::setEnabled(bool flag)
{
    this->enabled = flag;
}

/**
 * @brief Check if the game object is enabled
 *
 * @return true If the game object is enabled
 * @return false If the game object is not enabled
 */
bool AGameObject::isEnabled()
{
    return this->enabled;
}

AGameObject* AGameObject::getParent()
{
	return this->mParent;
}

void AGameObject::setParent(AGameObject* parent)
{
	this->mParent = parent;
}

sf::Transform AGameObject::getGlobalTransform()
{
    AGameObject* parentObj = this;
	std::vector<AGameObject*> parentList;
	while (parentObj != nullptr)
	{
		parentList.push_back(parentObj);
		parentObj = parentObj->getParent();
	}

    sf::Transform transform = sf::Transform::Identity;
	int startIdx = parentList.size() - 1;
	for (int i = startIdx; i >= 0; i--)
	{
		transform = transform * parentList[i]->getTransformable()->getTransform();
	}
	return transform;
}
