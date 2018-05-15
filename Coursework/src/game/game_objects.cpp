#include "game_objects.hpp"

void Car::update(int elapsedTime)
{
	// Move along -Z axis if car has turned
	if (turned)
	{
		transform.move({0, 0, -0.005f * elapsedTime});
	}

	// Otherwise move along X axis
	else
	{
		transform.move({0.005f * elapsedTime, 0, 0});
	}

	if (!turned && transform.position().x > 7)
	{
		// Set turned value to true
		turned = true;

		// Move the car to its new position and rotation facing along the -Z axis
		transform.move({5, 0.05f, 0});
		transform.rotations({{90}});

		for (Carlight& light : lights)
		{
			// Swap and negate the X and Z axes of the light offsets and direction
			light.pointLightOffset = vec3(-light.pointLightOffset.z, light.pointLightOffset.y, -light.pointLightOffset.x);
			light.spotLightOffset = vec3(-light.spotLightOffset.z, light.spotLightOffset.y, -light.spotLightOffset.x);
			light.spotLight->direction = vec3(-light.spotLight->direction.z, light.spotLight->direction.y, -light.spotLight->direction.x);
		}
	}
	else if (turned && transform.position().z < -20)
	{
		// Set turned value to false
		turned = false;

		// Move the car to its new position and rotation facing along the X axis
		transform.position({-20.f, 0.05f, -2});
		transform.rotations({});

		for (Carlight& light : lights)
		{
			// Swap and negate the X and Z axes of the light offsets and direction
			light.pointLightOffset = vec3(-light.pointLightOffset.z, light.pointLightOffset.y, -light.pointLightOffset.x);
			light.spotLightOffset = vec3(-light.spotLightOffset.z, light.spotLightOffset.y, -light.spotLightOffset.x);
			light.spotLight->direction = vec3(-light.spotLight->direction.z, light.spotLight->direction.y, -light.spotLight->direction.x);
		}
	}

	// Update all car lights
	for (Carlight& light : lights)
	{
		light.update();
	}
}
