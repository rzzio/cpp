#include "animation.h"

animation::animation(sf::Texture * texture, sf::Vector2u imagecount, float switchtime)
{
	this->imagecount = imagecount;
	this->switchtime = switchtime;
	
	totaltime = 0.0f;

	uvrect.width = texture->getSize().x / float(imagecount.x);
	uvrect.height = texture->getSize().x / float(imagecount.y);
	 

}
  

animation::~animation()
{
}
void animation::Update(int row, float deltatime)
{
	currentimage.y = row;
	
	if (totaltime >= switchtime)
	{
		totaltime -= switchtime;
		currentimage++;
		 
		if (currentimage.x >= imagecount.x)
		{
			currentimage.x = 0;
		}

	}
	uvrect.left = currentimage.x*uvrect.width;
	uvrect.top = currentimage.y*uvrect.height;

}
